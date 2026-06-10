"""
Generate an annotated diffraction image showing single-slit and double-slit
intensity patterns and slit geometry. Saves to images/diffraction_annotated.png
"""
import os
import numpy as np
import matplotlib.pyplot as plt

OUT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'images'))
os.makedirs(OUT_DIR, exist_ok=True)

wavelength = 500e-9
slit_width = 10e-6
screen_distance = 1.0
screen_width = 0.04
x = np.linspace(-screen_width/2, screen_width/2, 2000)
theta = np.arctan(x / screen_distance)
k = 2 * np.pi / wavelength

def single_slit_intensity(slit_w):
    beta = k * slit_w * np.sin(theta) / 2.0
    I = (np.sinc(np.where(beta==0, 1e-16, beta) / np.pi))**2
    return I / I.max()

def double_slit_intensity(slit_w, slit_spacing):
    single = single_slit_intensity(slit_w)
    alpha = k * slit_spacing * np.sin(theta) / 2.0
    inter = (np.cos(alpha))**2
    I = single * inter
    return I / I.max()

# Parameters for single/double
I_single = single_slit_intensity(slit_width)
I_double = double_slit_intensity(slit_width, 100e-6)

fig, axes = plt.subplots(2, 2, figsize=(10,6), gridspec_kw={'height_ratios':[1,1]})

# Top row: intensity plots
axes[0,0].imshow(np.tile(I_single, (300,1)), cmap='inferno', aspect='auto', extent=[x[0]*1e3, x[-1]*1e3, 0, 1])
axes[0,0].set_title('Single-slit intensity (normalized)')
axes[0,0].set_ylabel('')
axes[0,0].set_xticks([])

axes[0,1].imshow(np.tile(I_double, (300,1)), cmap='inferno', aspect='auto', extent=[x[0]*1e3, x[-1]*1e3, 0, 1])
axes[0,1].set_title('Double-slit intensity (normalized)')
axes[0,1].set_xticks([])

# Bottom row: geometry sketches
for ax in axes[1]:
    ax.set_xlim(-1, 1)
    ax.set_ylim(-0.6, 0.6)
    ax.axis('off')

# Single slit geometry (left)
ax = axes[1,0]
ax.set_title('Single slit geometry')
# Draw barrier
ax.add_patch(plt.Rectangle((-0.05, -0.6), 0.02, 1.2, color='black'))
# Draw slit opening
ax.add_patch(plt.Rectangle((-0.05, -slit_width*5e4/2), 0.02, slit_width*5e4, color='white'))
ax.text(0.1, 0.4, 'Incoming wave\\nfronts →', fontsize=9)
for sx in np.linspace(-0.4, -0.06, 6):
    ax.plot([sx, -0.06], [0, 0], color='blue', alpha=0.6)

# Double slit geometry (right)
ax = axes[1,1]
ax.set_title('Double slit geometry (spacing = 100 μm)')
ax.add_patch(plt.Rectangle((-0.05, -0.6), 0.02, 1.2, color='black'))
# two slits
spacing = 100e-6
scale = 5e4
ax.add_patch(plt.Rectangle((-0.05, 0.08), 0.02, slit_width*scale, color='white'))
ax.add_patch(plt.Rectangle((-0.05, -0.08-slit_width*scale), 0.02, slit_width*scale, color='white'))
ax.text(0.1, 0.4, 'Incoming wave\\nfronts →', fontsize=9)
for sx in np.linspace(-0.4, -0.06, 6):
    ax.plot([sx, -0.06], [0.05, 0.05], color='blue', alpha=0.6)

plt.tight_layout()
out_path = os.path.join(OUT_DIR, 'diffraction_annotated.png')
plt.savefig(out_path, dpi=150)
plt.close()
print('Wrote', out_path)

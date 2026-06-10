"""
Simple renderer to reproduce visuals from the WinForms C++/CLI simulation:
- Diffraction pattern for a double-slit (Fraunhofer approximation)
- Superposition of two 1D waves and their sum

Outputs: images/diffraction.png, images/superposition.png
"""
import os
import numpy as np
import matplotlib.pyplot as plt

os.makedirs(os.path.join(os.path.dirname(__file__), "..", "images"), exist_ok=True)
OUT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "images"))

# Diffraction (double-slit) parameters
wavelength = 500e-9  # 500 nm
slit_width = 10e-6   # 10 µm
slit_spacing = 100e-6  # center-to-center 100 µm
screen_distance = 1.0  # 1 m
screen_width = 0.04  # 4 cm

# compute angular positions
x = np.linspace(-screen_width/2, screen_width/2, 2000)
theta = np.arctan(x / screen_distance)

k = 2 * np.pi / wavelength

# single-slit envelope: sinc(ka*sin(theta)/2)
beta = k * slit_width * np.sin(theta) / 2.0
single = (np.sinc(beta / np.pi))**2

# double-slit interference term: cos(k * d * sin(theta) / 2)^2
alpha = k * slit_spacing * np.sin(theta) / 2.0
inter = (np.cos(alpha))**2

intensity = single * inter
intensity /= intensity.max()

# make a 2D image by repeating vertical
img = np.tile(intensity, (400,1))

plt.figure(figsize=(8,2))
plt.imshow(img, cmap='inferno', extent=[x[0]*1e3, x[-1]*1e3, 0, 1], aspect='auto')
plt.xlabel('Screen position (mm)')
plt.yticks([])
plt.title('Double-slit diffraction (normalized intensity)')
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'diffraction.png'), dpi=150)
plt.close()

# Superposition of two waves
width = 1200
x2 = np.linspace(0, 4*np.pi, width)

A1 = 1.0
A2 = 0.8
f1 = 2.0
f2 = 3.2
phi1 = 0.0
phi2 = 0.7

y1 = A1 * np.sin(f1 * x2 + phi1)
y2 = A2 * np.sin(f2 * x2 + phi2)
ys = y1 + y2

plt.figure(figsize=(10,3))
plt.plot(x2, y1, label='Wave 1', color='deepskyblue')
plt.plot(x2, y2, label='Wave 2', color='forestgreen')
plt.plot(x2, ys, label='Superposition', color='hotpink')
plt.legend()
plt.xlabel('x (arb)')
plt.ylabel('Amplitude')
plt.title('Wave superposition')
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'superposition.png'), dpi=150)
plt.close()

print('Rendered images to:', OUT_DIR)

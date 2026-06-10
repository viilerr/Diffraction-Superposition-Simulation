# Diffraction-Superposition-Simulation
 Interactive C++ simulation of diffraction and superposition phenomena, implementing computational physics models with real-time visualisation.
# Diffraction-Superposition-Simulation

Interactive C++ simulation of diffraction and superposition phenomena, implementing computational physics models with real-time visualisation.

---

## Diffraction.h

Summary
- Purpose: `Diffraction` is a C++/CLI Windows Forms `Form` that simulates multiple-slit diffraction and provides interactive controls for wavelength, slit height, spacing, and toggles for adding a second slit.
- Key rendering: `OnPaint(PaintEventArgs^ e)` — draws incoming wavefronts, slit barrier(s), and diffracted arcs.
- Interaction: trackbars and buttons wired in `InitializeComponent()` control parameters and animation.

## Superposition.h

Summary
- Purpose: `Superposition` is a C++/CLI Windows Forms `Form` that visualizes two waves and their superposition, supports animation, and exposes UI controls for amplitudes, frequencies, phases, and toggles.

---

## Visuals & Interactive Demo

This repository includes generated visuals and a simple interactive demo to explore single-slit and double-slit diffraction.

### Annotated image
![Annotated diffraction (single vs double slit)](images/diffraction_annotated.png)

### Static images
![Diffraction pattern (normalized intensity)](images/diffraction.png)
![Wave superposition](images/superposition.png)

Physics explanation (brief)

- Single-slit diffraction: a finite slit width produces a diffraction envelope described by a sinc^2 term. The first minima approximately satisfy $a\sin\theta = m\lambda$ (integer $m$), where $a$ is the slit width and $\lambda$ the wavelength.

- Double-slit interference: two coherent slits separated by $d$ produce interference fringes given by $d\sin\theta = n\lambda$ (integer $n$). The observed pattern is the interference fringes modulated by the single-slit envelope: bright fringes occur where path differences equal integer wavelengths, but their amplitude follows the single-slit envelope.

Interactive demo

Run the interactive demo (matplotlib) locally to explore slit spacing and toggle a second slit:

```bash
python3 scripts/interactive_diffraction.py
```

The interactive window provides a slider for slit spacing (μm), a checkbox to toggle the second slit, and a button to save a PNG snapshot.

---

How to reproduce visuals

```bash
python3 -m pip install --user numpy matplotlib
python3 scripts/generate_annotated_diffraction.py
python3 scripts/render_visuals.py
```

To run the interactive demo:

```bash
python3 scripts/interactive_diffraction.py
```

---

Files of interest

- `Diffraction.h`, `Superposition.h` — C++/CLI WinForms components
- `scripts/interactive_diffraction.py` — interactive matplotlib demo
- `scripts/generate_annotated_diffraction.py` — annotated figure generator
- `scripts/render_visuals.py` — quick renderer for static images
- `images/` — generated PNGs (diffraction, annotated, superposition)

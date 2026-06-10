# Diffraction.h

Summary
- Purpose: `Diffraction` is a C++/CLI Windows Forms `Form` that simulates multiple-slit diffraction. It draws incoming wavefronts, slit barriers, and diffracted patterns. UI controls let the user change wavelength, slit height, slit spacing, add slits, and toggle animation.

Key members
- Constructor: `Diffraction()` — sets defaults (wavelength, slitHeight), initializes controls (trackbars, textboxes, buttons), starts the timer.
- Drawing: `OnPaint(PaintEventArgs^ e) override` — draws incoming wavefronts, slit barrier, and diffracted arcs representing wave propagation from slit sources.
- Event handlers: `trackBar1_Scroll`, `trackBar2_Scroll`, `trackBar3_Scroll`, `timer1_Tick`, `button1_Click`, `button2_Click`, `button3_Click`, `button4_Click`, and `ToggleSecondSlit`.

Notable fields (from header)
- `double wavelength` — wavelength (tracked in nm via UI)
- `double slitHeight` — slit height (µm via UI)
- `double phaseShift` — used to animate incoming wavefronts
- `TrackBar^ trackBar1, trackBar2, trackBar3` — UI controls for wavelength, slit height, slit spacing
- `Timer^ timer1` — animation timer
- `bool showSecondSlit` — toggle second slit

Build & run
- Environment: Visual Studio (Windows) with C++/CLI support (/clr) and Windows Forms.
- To run: open the Visual Studio solution containing this `Form`, ensure the project uses `/clr`, build and run.

Usage notes (UI controls)
- `trackBar1` — set wavelength (displayed in nm). `textBox1` accepts a custom wavelength.
- `trackBar2` — set slit height (µm). `textBox2` accepts a custom slit height.
- `trackBar3` — set slit spacing (µm) for double-slit setups.
- Buttons: `refresh` resets defaults, `add slit` toggles second slit, `set value` buttons apply custom values from textboxes.
- Tooltips in the form give explanatory notes for most controls.

Where to look in code
- UI wiring and defaults: `InitializeComponent()` in `Diffraction.h`.
- Core rendering: `OnPaint` (draws wavefronts and diffraction arcs).
- Interaction: event handlers for the trackbars and buttons.

Notes & limitations
- This is a Windows-only WinForms component requiring Microsoft C++/CLI (not cross-platform).
- The simulation focuses on a visual/educational display rather than high-precision physics modeling.


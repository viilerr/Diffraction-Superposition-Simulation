# Diffraction-Superposition-Simulation
 Interactive C++ simulation of diffraction and superposition phenomena, implementing computational physics models with real-time visualisation.


<!-- Header summaries added below -->



## Diffraction.h

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



## Superposition.h

# Superposition.h

Summary
- Purpose: `Superposition` is a C++/CLI Windows Forms `Form` that visualizes wave superposition (two waves and their superposed result). It renders waves on a grid, supports animation, and exposes controls (checkboxes, scrollbars, text boxes) to toggle and adjust individual waves and the superposition display.

Key members
- Constructor: `Superposition()` — initializes UI, default parameters, and timer.
- Drawing: `OnPaint(PaintEventArgs^ e) override` — draws grid, individual waves, and superposition using helper functions (`wave`, `waveSup`).
- Animation: `animationTimer` and `OnAnimationTick` — advances `globalTimewave1` / `globalTimewave2` and triggers `Invalidate()`.
- Controls: several `HScrollBar`, `CheckBox`, `TextBox`, and `Panel` controls handle interactive parameters such as amplitudes, frequencies, phases, and toggles for drawing waves.

Notable fields (from header)
- `double amplitude1, amplitude2` — amplitudes of waves
- `double frequency1, frequency2` — frequencies
- `double phase1, phase2` — phase offsets
- `int gridRows, gridColumns` — drawing grid size
- `Timer^ animationTimer` — drives animation
- `bool drawWaves, animatingwave1, animatingwave2` — flags to control rendering and animation

Build & run
- Environment: Visual Studio (Windows) with C++/CLI support (/clr) and Windows Forms. The code is C++/CLI — it requires the Microsoft toolchain and .NET/WinForms runtime.
- To run: open the Visual Studio solution/project containing this form, ensure `/clr` is enabled for the project, build and run.

Usage notes
- Use the checkboxes to toggle Wave 1, Wave 2, and the Superposition wave.
- Adjust scrollbars to change frequencies/amplitudes; the `animationTimer` drives motion.
- The painting code uses a fixed grid and draws lines for each wave and the combined result.

Where to look in code
- UI and event wiring: `InitializeComponent()` in `Superposition.h`.
- Wave math and drawing: `OnPaint`, `OnAnimationTick`, and helper `wave`/`waveSup` calls.

Limitations & tips
- This is a Windows-only UI component (WinForms). To run cross-platform, port the simulation logic to a cross-platform GUI or a headless renderer.
- Performance: painting is done manually in `OnPaint`; for large windows or high-frequency updates consider optimizing drawing or using double-buffered bitmaps.


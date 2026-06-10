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


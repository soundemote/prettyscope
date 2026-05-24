# Salvage Notes

Prettyscope is being rebuilt from scratch. The existing root-level JUCE project,
installer files, presets, color maps, and `Source/` directory are treated as
PrettyScope Graveyard reference material.

## Initial Salvage

- `Shared/glad/3.2`: reused directly as the OpenGL 3.2 function loader. This is
  a small, well-scoped dependency that lets the first renderer run without
  reviving the old JUCE/plugin architecture.
- `LICENSE`: the repository is MIT licensed. Keep this license with any reused
  material.

No large old rendering or plugin code has been copied into the new `src/`
application path.

## Oscilloscope Beam Reference

- `https://m1el.github.io/woscope-how/`: renderer technique reference for
  drawing oscilloscope traces as beam-segment quads with additive blending and
  Gaussian integrated intensity in the fragment shader. The implementation in
  `src/visual/scope_renderer.cpp` is adapted to native OpenGL 3.2, pixel-space
  beam sizing, and Prettyscope's 1D signal path.
- `https://madebyevan.com/shaders/fast-rounded-rectangle-shadows/`: cited by
  the woscope article as the source of the GLSL `erf` / Gaussian approximation
  family. Prettyscope uses an `erfApprox` helper for the beam integral.

## Phosphor Decay

- `src/visual/shaders.cpp`: current Prettyscope phosphor decay shader and beam
  shader. This is new Prettyscope code, not copied from PrettyScope Graveyard.
  See `docs/PHOSPHOR_DECAY.md` for the current math and WebGL port notes.

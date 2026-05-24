# Plugin Roadmap

Prettyscope stays standalone-first until the OpenGL visual core is worth hosting
inside a plugin. The current standalone app is the visual reference and should
remain the fastest place to test beam shape, persistence, glow, controls, and
signal behavior.

## Foundation

Architect has selected `baconpaul/sidequest-startingpoint` as the likely CLAP
plugin foundation. The expected shape is:

- Use the sidequest/JUCE project as the plugin shell.
- Keep Prettyscope rendering code in a reusable core library.
- Host that core from a JUCE OpenGL component or equivalent plugin view.
- Feed plugin audio buffers into `ExternalSignalSource`.
- Keep the standalone executable alive as the golden-look development lab.

Do not vendor or port the plugin foundation into this repository until the
foundation repository is available locally and Architect confirms the dependency
direction.

## Current Prettyscope Side

- `prettyscope_core` contains the OpenGL visual renderer and signal abstractions.
- `prettyscope` contains only the Win32 standalone app shell, controls, presets,
  and windowing.
- `SignalSource` is the boundary between generated/demo signals and future host
  audio.
- `ExternalSignalSource` is the first bridge for copied mono/stereo buffers from
  a host or runtime.
- Plugin shells should include `prettyscope.hpp` and avoid depending on internal
  renderer headers unless they are actively extending the renderer.
- Float controls should bind through `VisualFloatParameterId` and
  `VisualFloatParameter` descriptors so standalone controls, presets, and plugin
  automation share one range model.
- Plugin automation should use the normalized visual parameter helpers rather
  than duplicating 0..1 conversion in the plugin wrapper.

## First Plugin Milestone

1. Open a JUCE/CLAP editor window with an OpenGL context.
2. Initialize `ScopeRenderer` inside that context.
3. Reserve and copy plugin audio input into `ExternalSignalSource` using host
   channel pointers.
4. Render using the golden phosphor preset defaults.
5. Add minimal plugin parameters only after the hosted visual path is real.

The first plugin target should prove that Prettyscope can draw live host audio
with the same look as the standalone scope. Preset management, richer controls,
and Syphon/Spout output can follow after that rendering path exists.

See `docs/HOST_INTEGRATION.md` for the current core API shape the plugin shell
should call.

## When Sidequest Is Needed

Further standalone/core work can continue without the plugin foundation, but
actual CLAP development should wait until `baconpaul/sidequest-startingpoint` is
available locally.

Tracer needs the sidequest project to:

- inspect its existing audio/UI handoff pattern
- choose between `ExternalSignalSource`, `SignalSnapshot`, or a dedicated
  sidequest adapter
- identify the expected JUCE OpenGL component lifecycle
- map Prettyscope descriptors to the foundation's parameter model
- add the first plugin/editor target without guessing at repository structure

# Host Integration Notes

This is the current integration shape for a future JUCE/CLAP shell.

`examples/host_bridge_example.cpp` is a small compiled example of the public
core API without creating an OpenGL window.

`FrameStats` provides the shared FPS smoothing used by the standalone title bar.
Plugin editors may use host/editor timing directly, or use `FrameStats` if they
want matching overlay/readout behavior.

## Public Include

Use:

```cpp
#include "prettyscope.hpp"
```

Avoid including internal renderer headers from the plugin shell unless the shell
is actively extending renderer internals.

## OpenGL Lifecycle

Create one `prettyscope::ScopeEngine` for the editor/view that owns the OpenGL
context.

```cpp
prettyscope::ScopeEngine scope(1024);
scope.initialize();
// render callbacks...
scope.shutdown();
```

Call `initialize()` and `shutdown()` while the OpenGL context is current.
Both calls are idempotent. `renderCurrentSignal()` returns without drawing until
the engine is initialized.

## Audio Handoff

Use `ExternalSignalSource` as the first bridge from copied host audio buffers.
It is a simple core adapter, not the final DAW audio-thread architecture.

```cpp
prettyscope::ExternalSignalSource source;
source.reserve(maxBlockSize);
source.setInputChannels(channels, channelCount, sampleCount);
scope.advance(source, dt);
```

`ExternalSignalSource` synchronizes access internally, so a first plugin build can
feed it from a host callback while the editor renders on another callback. Call
`reserve()` during prepare/setup to avoid routine vector growth.

For the sidequest/JUCE/CLAP plugin, prefer the foundation's existing audio/UI
handoff if it has one. In that case, copy into `ExternalSignalSource` only from
the UI/editor side, or replace it with a host-specific `SignalSource`
implementation. Do not treat the mutex bridge as a hard realtime audio-thread
contract.

If the plugin foundation already provides an editor-safe audio snapshot, copy it
into `SignalSnapshot` and render from that. `SignalSnapshot` is a simple
render-side `SignalSource` that owns drawable samples and does not imply any
audio-thread behavior.

If the plugin adapter already has a `SignalBuffer`, it can skip the source
interface and set the engine's current render signal directly:

```cpp
scope.setSignal(editorSafeSignalBuffer);
scope.renderCurrentSignal(width, height);
```

When audio and OpenGL arrive on different callbacks, update the source from the
audio side, then render the current signal from the OpenGL/editor side:

```cpp
scope.renderCurrentSignal(width, height);
```

## Controls

Bind float controls through `VisualFloatParameterId` and the normalized helpers:

```cpp
prettyscope::setNormalizedVisualFloatParameter(
    scope.params(),
    prettyscope::VisualFloatParameterId::TraceGain,
    normalizedValue);
```

Bind toggles through `VisualBoolParameterId`, and menu/choice controls through
`VisualChoiceParameterId`. Choice setters update `clearRevision` where the
persistence buffer needs a visual reset.

Descriptors are host-ready, not host-owned. Core descriptors carry:

- stable string identity, such as `signal.gain` or `phosphor.persistence`
- manually assigned stable numeric IDs for host adapters
- category and role metadata
- `automatable` and `visible` flags
- display names, short names, descriptions, units, and precision
- float minimum, midpoint, maximum, and default values

Adapters can enumerate descriptor arrays with `visualFloatParameters()`,
`visualBoolParameters()`, and `visualChoiceParameters()`. They can resolve saved
or host-facing identities with the `findVisual*ParameterByStableId()` and
`findVisual*ParameterByNumericId()` helpers.

The current visual state version is `kVisualParameterStateVersion`.
See `docs/VISUAL_STATE.md` for the current preset/state keys.

State compatibility rules:

- Descriptor string IDs are stable across versions.
- Numeric IDs are never reused for a different parameter.
- Removed numeric IDs are retired.
- Missing parameters should use descriptor defaults.
- Unknown parameters should be ignored until a future state container can
  preserve them.
- Renamed parameters require an explicit migration table later.

Normalized value means transport/automation value. Raw value means visual/render
value. The descriptor is the source of mapping rules; mapping is linear for now.

## Palettes

Use `visualPalettes()` to list named palettes and `applyVisualPalette()` to
apply one. The standalone `C` key uses the same palette list.

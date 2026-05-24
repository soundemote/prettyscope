# Visual State Format

Prettyscope visual state uses descriptor stable IDs as its primary keys.

The current state version is:

```cpp
prettyscope::kVisualParameterStateVersion == 1
```

## Current Preset Keys

The default preset now writes visual parameters with stable descriptor IDs:

- `scope.trace_mode`
- `phosphor.decay_style`
- `signal.gain`
- `beam.glow_intensity`
- `beam.thickness`
- `beam.glow_width`
- `phosphor.persistence`
- `phosphor.fast_decay`
- `phosphor.afterglow`
- `phosphor.enabled`
- `overlay.fps_enabled`
- `overlay.grid_enabled`

Signal demo selection remains `signalMode` for now because it is standalone demo
state rather than a visual renderer descriptor.

Color values currently remain explicit RGB state:

- `traceColor`
- `glowColor`
- `backgroundColor`

Palette identity can be added later once preset semantics for palette vs custom
colors are decided.

## Compatibility

The loader still accepts legacy keys such as `traceGain`, `glowStrength`,
`decayStyle`, and `showGrid`. New saves use stable descriptor IDs.

Rules:

- Stable string IDs are the primary persisted identity.
- Stable numeric IDs are for host adapters and must not be reused.
- Missing parameters use current defaults.
- Unknown parameters are ignored until a future state container preserves them.
- Renamed parameters require an explicit migration table later.

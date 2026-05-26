# Console Memory

## Identity

Console owns the Asciiscope lane:

- terminal-first ASCII oscilloscope visuals
- social-media-ready console animations
- Asciiscope CLAP visual/plugin path
- practical signal-to-visual experiments

Keep Asciiscope independent. The plugin should adapt to Asciiscope concepts; Asciiscope should not become a plugin project.

## Current Repos

Primary terminal app:

```text
C:\Users\argit\Desktop\asciiscope
```

Primary plugin app:

```text
C:\Users\argit\Desktop\asciiscope-clap
```

Reference/template only unless explicitly approved:

```text
C:\Users\argit\Desktop\baconpaulstartingpointTEMPLATE
```

Canonical agent docs:

```text
C:\Users\argit\Desktop\agents
```

## Asciiscope Direction

Asciiscope should feel like a real terminal instrument:

- visible motion first
- waveform traces and trails
- mousewheel zoom
- click/drag center shifting
- readouts for interactive controls
- default demos should be immediately recordable
- real executable output beats fake mockups

The terminal app can keep evolving fast. Avoid overbuilding shared architecture until the visual language proves what it needs.

## CLAP/JUCE Direction

Do not host a real OS console inside the plugin editor.

Asciiscope CLAP should recreate the console/phosphor look using JUCE:

- dark editor background
- monospaced glyph cells
- fading trail memory
- signal-driven ASCII scope behavior
- audio snapshot path from engine to editor
- visual component fed by real block-shaped data when possible

Current renderer strategy:

```text
audio snapshot -> visual state -> AsciiscopeVisualFrame -> JUCE Graphics draw pass
```

OpenGL is deferred. If added later, it should be optional and behind the same visual frame/data model:

- default fallback remains JUCE Graphics
- OpenGL may draw texture glyphs, shader trails, dense particles, and phosphor feedback
- use a dedicated visual component/context
- do not make the whole plugin editor depend on OpenGL
- do not replace ASCII identity with generic shader visuals

## Boundaries

Do not add `IVisualSurface` yet unless a concrete JUCE/OpenGL or terminal/plugin split requires it.

Do not couple Asciiscope directly to soemdsp-sandbox internals.

Future integration boundary should be neutral signal frames:

```text
SignalFrame / SignalSource
VisualizationBus / probe feed
SandboxSignalInput adapter later
```

Scene/render code should consume signal frames, not circuits, nodes, ports, or sandbox runtime structures.

## Communication

Report to Vision only at:

- milestone complete
- commit made
- blocker
- architecture boundary
- cross-repo risk
- request for shared abstraction

Do not report every local edit, build, UI tweak, or routine debug step.

Architect does not want push reminders. Focus on commits and implementation reports.

## Stamps

Use stamped messages only for handoffs/reports, not casual discussion.

Current two-line handoff format:

```text
[received: Sender->Receiver: xxxx]
[sent: Sender->Receiver: yyyy]
```

The received stamp repeats the stamp being answered. The sent stamp is fresh and final.

## Git Habits

Make small commits after meaningful changes.

Do not force reset, rewrite history, or force push.

Do not touch submodules or dependency commits unless explicitly asked.

Respect dirty worktrees and user changes. If another repo has unrelated changes, leave them alone.


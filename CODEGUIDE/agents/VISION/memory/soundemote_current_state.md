# Soundemote Current State

Durable state snapshot for Vision.

This file exists so Vision can reload the current Soundemote operating map without depending only on chat context.

## Current Date Context

Current push context:

* 58 days left in the current runway/push
* Architect is actively coordinating multiple agents
* Codex is the main big-ticket technical focus
* Console, Tracer, DIRECTOR, and Void are active but should not overload Vision routing

## Soundemote Short Description

Soundemote is an audio-visual DSP technology company creating multiplatform audio plugins and video FX generators with analog aesthetics for modern multiplatform frameworks.

## Core Company Direction

Soundemote is becoming a creative audio-visual technology ecosystem.

The ecosystem includes:

* `soemdsp`
* `soemdsp-sandbox`
* `asciiscope`
* `asciiscope-clap`
* `prettyscope`
* `prettyscope-clap`
* Soundemote website
* browser-native creative sketches
* future Hydrus work
* future finished music, audiovisual, and creative products

Soundemote should become a center of gravity for:

* plugin development
* audio FX
* visual FX
* DSP tools
* creative audio technology
* audio-reactive visuals
* modular prototyping
* analog-aesthetic video generators
* multiplatform plugin and visual frameworks

## Strategic Frame

The ecosystem is gravity, not the fenced-off product.

The tools should generate:

* attention
* trust
* adoption
* awe
* proof of taste
* proof of technical power
* proof of long-term seriousness

The money should come from:

* finished music
* audiovisual releases
* commissioned audiovisual pieces
* sound design
* sound packs
* sample packs
* custom visuals
* plugin-powered art
* visual loops
* release visuals
* artist branding visuals
* Hydrus when it is ready
* creative products made with the ecosystem

Do not rush Hydrus.

Do not frame Soundemote as desperation.

Do not use shallow hype.

## Agent Map

Architect:

* Argi
* final authority
* manual router
* owns final taste, direction, and decisions

Vision:

* architecture
* sequencing
* cross-project coherence
* next smallest useful task
* boundary protection
* stamp hygiene

Codex:

* `soemdsp`
* `soemdsp-sandbox`
* core runtime and DSP execution
* currently the big-ticket spine

Console:

* `asciiscope`
* `asciiscope-clap`
* terminal/ASCII visual lane
* Asciiscope plugin visual path

Tracer:

* `prettyscope`
* `prettyscope-clap`
* OpenGL/phosphor visual lane
* Prettyscope plugin visual path

Void:

* Soundemote website
* browser-native creative sandbox
* separate from normal routed agent workflow
* works directly with Architect

DIRECTOR:

* business
* money
* audience
* public strategy
* social media
* YouTube
* offers
* finished creative product strategy

## CODEGUIDE State

Canonical guidance now lives in:

```
https://github.com/soundemote/prettyscope-revival/tree/main/CODEGUIDE
```

Important CODEGUIDE areas:

* `AGENTS.md`
* `agents/*.md`
* `protocols/stamps.md`
* `protocols/communication_cadence.md`
* `protocols/push_policy.md`
* `templates/task.md`
* `templates/completion_report.md`
* `templates/cross_agent_handoff.md`
* `agents/VISION/memory/*.md`

Old repo-local `.codex/AGENTS.md` in `soemdsp` is obsolete/removed.

## soemdsp / soemdsp-sandbox State

Owner: Codex.

Current focus:

* `soemdsp` core runtime
* DSP binding
* runtime graph foundation
* future `soemdsp-sandbox`

Current runtime foundation includes:

* Circuit runtime
* nodes
* ports
* connections
* audio/control/trigger routing
* stable IDs
* reflection metadata
* layout/editor metadata
* debug printing
* runtime query helpers
* parameter lifecycle helpers
* normalized parameter transport
* parameter snapshots
* CircuitSnapshot
* CircuitReport
* validation diagnostics
* text export helpers
* ControlGraph
* ControlGraph reports/snapshots/exports
* ControlGraph target validation
* safe ControlGraph apply to Circuit
* curve/scale settings
* midpoint curve support
* parameter `midValue`
* DSP object contract docs
* DSP binding metadata
* DSP binding validation
* DSP binding target validation
* DSP binding reports
* DSP binding apply result reports
* DSP binding apply summaries

Important proven DSP binding path:

```
Circuit parameter
    -> DspParameterBinding
    -> external memory slot
    -> low-level DSP object reads that memory
```

Recent proven demos include:

* parameter sync into external memory
* missing target failure
* null memory slot failure
* apply result text export
* contract-style DSP object sync
* repeated resync after Circuit parameter change
* multi-parameter DSP object sync
* multi-node DSP object sync
* multi-node failure all-or-nothing proof
* apply summaries
* sequential caller-level batch apply
* mixed caller-level batch apply
* caller-level batch aggregate demo
* manual DSP object processing chain demo
* manual DSP object processing chain resync demo
* manual DSP object block processing demo
* manual DSP object block resync demo
* manual DSP object block preflight failure demo
* manual DSP object block phase report demo
* DSP execution questions doc

Recent completion:

```
fe267bb Document DSP execution questions
```

The execution questions doc records scheduler, batch API, and sandbox questions that must be answered before demo-local proofs become production execution machinery.

No scheduler, production batch API, graph-owned DSP state, plugin/UI code, or Circuit-owned DSP objects were added.

## Vision Takeover / Codex Context

Architect is moving Vision into the primary `soemdsp` / `soemdsp-sandbox` implementation role.

Current working model:

```
Vision = Soundemote DSP/sandbox mind, task author, and bounded direct editor when Architect assigns implementation work.
Codex = optional historical context / helper agent if Architect pastes Codex reports or asks Vision to consult Codex.
```

Current stance:

* Vision should inspect and edit `soemdsp` directly when Architect asks.
* Architect may paste Codex context into Vision when useful.
* Vision should ask Architect only when Codex context is actually needed.
* Architect remains final authority.
* Codex may be phased out once Vision has absorbed enough code context.

## Current Codex Repo State To Remember

Codex resolved a divergence involving old `.codex/AGENTS.md`.

Resolution:

* remote had `2295339 Update AGENTS.md`
* local had `a7cf626 moving AGENTS.md out of repository`
* local removal won
* merge commit created: `e437f77 Merge remote-tracking branch 'origin/main'`
* canonical agent docs now live in CODEGUIDE
* repo was clean afterward
* main was ahead of origin by local commits and no longer behind

Do not revive `.codex/AGENTS.md` as canonical.

## Asciiscope / Console State

Owner: Console.

Repos:

* `asciiscope`
* `asciiscope-clap`

Asciiscope current concepts:

* terminal-first visual instrument
* ASCII oscilloscope/social animations
* `ISignalInput`
* `SignalFrame`
* `SignalSource`
* `SignalSample`
* `SignalStats`
* `DemoSignalInput`
* `AnimationScene`
* `ConsoleRenderer`

Boundary:

```
ISignalInput
    -> SignalFrame
    -> AnimationScene
    -> ConsoleRenderer
```

Asciiscope CLAP current state:

* plugin identity renamed to Asciiscope CLAP
* CMake project/product identity updated
* bundle/plugin ID updated
* manufacturer metadata updated
* README updated
* patch extension changed to `.ascope`
* JUCE visual component added
* `ui::AsciiscopeVisualComponent`
* visual component owned by `MainPanel`
* ticked by existing `PluginEditor::idle()` at 60 Hz
* currently fed by existing `UPDATE_VU` left/right values
* draws dark console-style glyph waveform/grid

Console should work in milestone chunks.

Do not force shared `IVisualSurface` yet.

## Prettyscope / Tracer State

Owner: Tracer.

Repos:

* `prettyscope`
* `prettyscope-clap`

Prettyscope direction:

* OpenGL/phosphor/GPU visualizer
* golden standalone renderer look
* plugin path through CLAP/JUCE

Prettyscope CLAP current state:

* renamed CLAP/JUCE shell
* stereo input/output
* host audio passthrough
* engine stores `scopeInput`
* `ScopeAudioSnapshot`
* `ScopeAudioSnapshotQueue`
* editor subscribes while alive
* editor drains newest snapshot during idle
* visual descriptor registry exists
* descriptor-to-Sidequest Patch/Param adapter exists
* descriptor string IDs preserved
* descriptor numeric IDs used as plugin/host parameter IDs
* tests added for descriptor mapping and roundtrip
* editor-visible `Visual Parameters` panel exists
* parameters include:

  * `phosphor_decay`
  * `beam_intensity`
  * `input_gain`
  * `time_scale`
* `ScopeSnapshotInspector` exists
* `ScopeOpenGLView` exists
* simple XY line-strip renderer fed from snapshot
* first OpenGL lifecycle proof complete
* renderer adapter boundary was recommended/active

Tracer should not port golden renderer blindly.

Descriptors are truth.

Sidequest/JUCE/CLAP plumbing adapts to descriptors.

## Void State

Void is separate from normal routed agent workflow.

Void works directly with Architect.

Void owns:

* Soundemote website
* browser-native visuals
* web-native DSP/audio-visual sketches
* Prettyscope-like web experiments
* future WebAudio/WebGL/WebGPU ideas

Void has created a Prettyscope-like web plugin / web visual experiment.

Void is a creative sketchpad while the actual `soemdsp-sandbox` does not exist yet.

Void can inspire other projects, but does not define core runtime architecture.

## DIRECTOR State

DIRECTOR owns business/public strategy.

DIRECTOR should mostly speak directly with Architect.

DIRECTOR helps with:

* social media
* YouTube
* public strategy
* offers
* commissions
* money path
* audience growth
* finished creative products

DIRECTOR should contact Vision only when cross-agent alignment or technical accuracy is needed.

Important DIRECTOR strategy:

* tools create gravity
* finished works make money
* no begging
* no shallow hype
* do not rush Hydrus

## Push Policy State

Push bandwidth is limited.

Architect / DIRECTOR push every little while.

Agents should not recommend pushes by default.

Agents report repo status only:

* working tree clean / dirty
* ahead of origin by N commits
* behind origin by N commits
* conflicts if any

Mention push only when Architect asks or when a task explicitly requires remote state.

## Current Risk Focus

Highest coding risks:

* premature scheduler
* production batch API too early
* graph-owned DSP object storage
* plugin abstraction creeping into core runtime
* ControlGraph shaping leaking into DSP binding
* repo behind/divergence states

Highest agent risks:

* unclear active stamp thread
* old local docs conflicting with CODEGUIDE
* agents over-reporting
* stale Codex context being mistaken for current repo truth
* Director accidentally becoming engineering router
* Void sketches being mistaken for runtime architecture

Current mitigation:

* small proofs
* clear stamps
* CODEGUIDE canonical docs
* Vision direct inspection before implementation
* no push recommendations by default
* abstraction freeze rule
* Codex tight cadence
* Console/Tracer milestone cadence
* Void separate
* DIRECTOR mostly direct with Architect

## Current Success Standard

The current push does not require everything to be finished.

The goal is for Soundemote to become undeniable.

Undeniable means people can see, hear, run, follow, trust, and eventually buy into what Architect is building.

Keep Soundemote becoming harder to ignore.

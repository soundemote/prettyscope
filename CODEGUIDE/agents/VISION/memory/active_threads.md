# Active Threads

Durable active-thread memory for Vision.

This file tracks the current agent tasks, active stamps, repo states, and open loops that Vision should remember across chat context loss.

Update this file when an active task changes, a major report arrives, or a thread is closed.

## How To Use This File

This is not a full history.

This is the current operating board.

Keep it compact.

Track:

* active task per agent
* latest relevant stamp
* current repo state if important
* blockers
* next expected report
* decisions that should not be forgotten

## Stamp Rule

Formal threads use:

```
[received: Sender→Receiver: xxxx]
[sent: Sender→Receiver: xxxx]
```

The active stamp for a task is usually the last Vision→Agent task instruction.

Side acknowledgments do not automatically replace the active task thread.

If unsure, ask Architect which thread is active.

## Codex Active Thread

Agent:

```
Codex
```

Repo:

```
C:\Users\argit\Desktop\soemdsp
C:\Users\argit\Desktop\soemdsp-sandbox
```

Ownership:

* `soemdsp`
* `soemdsp-sandbox`
* core runtime
* DSP binding
* ControlGraph
* validation/reporting/export
* first local sandbox shell
* future full sandbox spine

Current focus:

```
DSP binding proof ladder moving toward caller-owned manual processing,
while avoiding scheduler/API/plugin creep.
```

Current transition model:

```
Vision = Soundemote DSP/sandbox mind, task author, and bounded direct editor when Architect assigns implementation work.
Codex = optional historical context / helper agent if Architect pastes Codex reports or asks Vision to consult Codex.
```

Vision should take over direct `soemdsp` inspection and implementation.

Architect will copy/paste Codex context if useful.

Vision should ask for Codex only when it would materially reduce uncertainty.

Architect hands-on testing threshold:

* do not ask Architect to test CLI-only demos
* Vision handles command-line build/run/proof verification
* ask Architect for hands-on testing when there is mouse interaction, audible output, or visual inspection value

Vision thought-processing stance:

* Extra High / maximum processing is currently useful and approved
* use it especially for proof sequencing and abstraction-boundary decisions
* mechanical edits do not inherently require maximum processing

Recent completed work:

* DSP binding apply batch aggregate demo
* DSP binding null memory all-or-nothing apply demo
* DSP binding unsupported target all-or-nothing apply demo
* DSP binding validation demo now distinguishes unsupported target-kind validation from null-memory validation
* manual DSP object processing chain demo
* manual DSP object processing chain resync demo
* manual DSP object block processing demo
* manual DSP object block resync demo
* manual DSP object block resync demo now reports separate first/resynced block phases through DspBlockPhaseReport
* manual DSP object block preflight failure demo
* manual DSP object block preflight recovery demo
* manual DSP object block null-memory recovery demo
* manual DSP object block phase report demo
* reusable DSP block phase report value type and print helper
* DSP block phase report text export helper
* DSP block preflight failure demo now reports failed preflight and skipped processing through DspBlockPhaseReport
* DSP execution questions doc clarified around reusable report helpers versus blocked execution machinery
* DSP execution questions doc records independent phase reports for resync block passes
* DSP execution questions doc
* runtime audio sine WAV demo
* runtime Circuit audio path can render a short mono WAV artifact through SineOscillator -> AudioOutput
* bound DSP object WAV demo
* synced Circuit frequency/amplitude parameters can drive a caller-owned DSP object that renders an audible WAV artifact
* bound DSP object WAV resync demo
* changed Circuit frequency/amplitude parameters can resync into external DSP memory between two halves of an audible WAV artifact
* bound DSP object WAV resync demo now reports each render half through DspBlockPhaseReport
* examples-only mono WAV writer helper
* audible demos share `examples/WriteMono16Wav.hpp` without making it a runtime API
* audible demos can print and write compact WAV artifact metadata reports
* bound DSP object WAV resync demo writes a combined render summary with setter status, both phase reports, and WAV artifact metadata
* bound DSP object WAV resync demo writes a demo-local HTML audio report with browser-native audio controls and status sections
* bound DSP object WAV resync demo writes a demo-local JSON artifact manifest for inspection
* bound DSP object WAV resync HTML report links the generated WAV, manifest, text summary, WAV metadata report, and phase reports as one local inspection packet
* root-level runtime demo reports and inspection artifacts are gitignored so hands-on demo runs do not dirty source status
* bound DSP object WAV resync manifest includes a demo-local sandbox handoff contract naming the HTML entry point and WAV artifact for mouse-and-ears inspection
* docs/SANDBOX_HANDOFF_CONTRACT.md documents the versioned read-only sandbox handoff contract and its non-meanings
* bound DSP object WAV resync manifest includes display-ready artifact links for read-only sandbox shells
* docs/SANDBOX_HANDOFF_CONSUMER_CHECKLIST.md records accept/display/reject rules for a future read-only sandbox manifest consumer
* first local `soemdsp-sandbox` repo exists as a read-only manifest shell
* sandbox shell displays status, contract, boundary flags, phases, artifact links, and a browser-native WAV player
* sandbox shell visibly applies the consumer checklist and shows warning states for unsafe/unsupported manifest values
* sandbox shell draws a read-only waveform from the generated WAV
* sandbox shell overlays manifest-derived phase regions on the waveform and exposes phase view controls
* sandbox shell derives phase time ranges, durations, and WAV share from manifest phase sample counts and WAV metadata
* sandbox shell displays the current waveform phase in the waveform header and highlights the active phase button
* waveform controls are decoupled from native audio seeking to avoid slider/audio reset loops; native audio playback can still drive waveform position
* sandbox shell displays first/second frequency and amplitude from the generated summary artifact
* sandbox shell displays frequency/amplitude resync deltas and ratios from the generated summary artifact

Important recent repo event:

* `.codex/AGENTS.md` divergence resolved
* local removal won
* canonical docs now live in CODEGUIDE
* merge commit: `e437f77 Merge remote-tracking branch 'origin/main'`
* repo became no longer behind origin

Last completed Vision task:

```
Decouple waveform view from audio seek.
```

Task goal:

```
Stop the waveform slider and phase buttons from writing into the native audio
element on every move, so the browser audio control cannot snap the waveform
inspection cursor back to 0 through a seek/timeupdate feedback loop.
```

Added:

* waveform slider now controls only the read-only waveform inspection cursor
* waveform phase buttons now control only the read-only waveform inspection cursor
* native audio playback/timeupdate still drives the waveform position while audio plays
* README language changed from phase seek controls to phase view controls

Verification note:

* live browser reload reported current phase `first`
* live browser reload reported waveform position `0.000s`
* live browser reported `Waveform: Drawn`
* live browser still reported `Checklist: Accepted`
* browser check found no console errors and no horizontal overflow
* Architect reported the original bug by mouse: audio playback matched waveform, but waveform slider movement reset to 0 and also reset the primary audio player

Boundary preserved:

* read-only shell
* no audio engine
* no executor
* no scheduler
* no production batch API
* no plugin layer
* no runtime-owned UI layer
* no graph-owned DSP object state
* no Circuit mutation
* no project serialization

Completion commit:

```
bebb928 Decouple waveform view from audio seek
```

Reported repo status:

* working tree clean
* initial local repo commit
* behind origin by 0 commits
* conflicts: none

Watch for:

* scheduler temptation
* production batch API temptation
* graph-owned DSP object storage
* plugin abstraction creep
* ControlGraph shaping leaking into DSP binding
* behind-origin divergence

## Console Active Thread

Agent:

```
Console
```

Repos:

* `asciiscope`
* `asciiscope-clap`

Ownership:

* Asciiscope terminal visuals
* Asciiscope CLAP plugin visual path
* ASCII/terminal visual lane
* SignalFrame / SignalSource concepts

Current pressure level:

```
light / milestone-based
```

Current state:

* Asciiscope remains independent and terminal-first
* Asciiscope CLAP identity rename completed
* JUCE visual component added
* `ui::AsciiscopeVisualComponent` exists
* component is owned by `MainPanel`
* ticked by `PluginEditor::idle()` at 60 Hz
* currently fed from existing VU/scalar data
* audio snapshot path was recommended as next major milestone

Likely next Console milestone:

```
Add lightweight audio-to-visual snapshot boundary for Asciiscope CLAP.
```

Guidance:

* Console does not need to report every local edit
* report milestones, blockers, commits, repo unsafe state, or boundary decisions
* no premature `IVisualSurface`
* no direct `soemdsp-sandbox` coupling
* no collision with Tracer

Relevant shared guidance:

```
Console and Tracer may diverge freely inside their own repos.
The key is preserving extraction seams:
- where signal enters
- where state updates
- where drawing/rendering happens
- what is reusable core
- what is plugin/editor shell
```

Latest known Console stamp:

```
[received: Console→Vision: y7d4m]
[sent: Vision→Console: p4s8]
```

This may be stale if Console has since received light-guidance messages.

## Tracer Active Thread

Agent:

```
Tracer
```

Repos:

* `prettyscope`
* `prettyscope-clap`

Ownership:

* Prettyscope OpenGL/phosphor visual lane
* Prettyscope CLAP plugin path
* visual parameter descriptors
* audio snapshot queue
* OpenGL editor view
* renderer adapter path
* future golden renderer port

Current pressure level:

```
light / milestone-based
```

Current state:

* descriptor-owned visual parameters proven
* Sidequest Patch/Param adapter exists
* editor parameter panel exists
* snapshot inspector exists
* first OpenGL scope view exists
* simple XY line-strip renderer fed from ScopeAudioSnapshot
* renderer adapter boundary was recommended next

Likely next Tracer milestone:

```
Add scope renderer adapter boundary around current OpenGL XY proof renderer.
```

Guidance:

* Tracer does not need to report every local edit
* report milestones, blockers, commits, repo unsafe state, or boundary decisions
* descriptors remain source of truth
* Sidequest/JUCE/CLAP plumbing adapts to descriptors
* do not port golden renderer blindly
* do not remove inherited synth/MIDI/voice concepts too early

Relevant shared guidance:

```
Console and Tracer code divergence is acceptable.
The concern is not sameness.
The concern is extraction seams.
```

Latest known Tracer stamp:

```
[received: Tracer→Vision: t3k7]
[sent: Vision→Tracer: h5m2]
```

This may be stale if Tracer has since received light-guidance messages.

## Void Active Thread

Agent:

```
Void
```

Role:

```
Separate browser-native creative sandbox and Soundemote website lane.
```

Normal routing:

```
Void works directly with Architect.
```

Void is not part of the normal routed agent mesh.

Current state:

* Void is working happily with Architect on the Soundemote website
* Void created a Prettyscope-like web plugin / web visual experiment
* Void acts as a sketchpad for DSP/audio-visual interaction while the real `soemdsp-sandbox` does not exist yet

Guidance:

* Void can explore freely
* Void does not need to wait for the real sandbox
* Void should not define core runtime architecture
* Void discoveries can later be routed into Codex/Console/Tracer/DIRECTOR if Architect decides they are useful

No active formal stamp required unless Architect routes a Void discovery into the formal system.

## DIRECTOR Active Thread

Agent:

```
DIRECTOR
```

Role:

* business
* money
* audience
* public strategy
* social media
* YouTube
* offers
* commissions
* finished creative product strategy

Normal routing:

```
DIRECTOR mostly speaks directly with Architect.
```

Current strategy:

```
Soundemote tools are gravity, not the fenced-off product.
```

Money path:

* finished music
* audiovisual releases
* commissioned audiovisual pieces
* sound design
* sound packs
* sample packs
* custom visuals
* plugin-powered art
* Hydrus when ready
* creative products made with the ecosystem

Guidance:

* no begging
* no shallow hype
* do not rush Hydrus
* do not interrupt engineering agents unless Architect/Vision routes a bounded request
* help Architect create practical offers and public proof

Potential next DIRECTOR output:

* simple commission / offer menu
* first public positioning statement
* 7-day content plan
* concrete “what can be posted today” plan

Latest known DIRECTOR formal stamp:

```
[received: DIRECTOR→Vision: center-strategy]
[sent: Vision→DIRECTOR: g8r4]
```

DIRECTOR does not need stamps for ordinary business discussion with Architect.

## CODEGUIDE Active Thread

Repo:

```
https://github.com/soundemote/prettyscope-revival/tree/main/CODEGUIDE
```

Purpose:

```
canonical company/agent/code guidance
```

Current state:

* AGENTS overview exists
* agent files exist
* protocols exist
* templates exist
* push policy simplified
* communication cadence updated
* completion report template updated
* task template updated
* cross-agent handoff template corrected
* Vision file updated
* Vision memory bank being created

Current Vision memory files planned:

* `soundemote_current_state.md`
* `architecture_invariants.md`
* `active_threads.md`
* `business_strategy.md`
* `glossary.md`

This file is the third of those five.

Guidance:

* CODEGUIDE is company infrastructure, not overhead
* it is currently housed in `prettyscope-revival` for tactical/public reasons
* avoid stale duplicated local agent docs
* old `.codex/AGENTS.md` should not become canonical again

## Open Management Decisions

Current big-ticket technical focus:

```
Vision / soemdsp / soemdsp-sandbox
```

Other agents:

```
light pressure, milestone cadence
```

Void:

```
separate/private creative sandbox with Architect
```

Pushes:

```
Architect / DIRECTOR push every little while
agents report repo status only
```

Abstractions:

```
freeze production abstractions until repeated proofs make the shape unavoidable
```

## Active Risks

High:

* premature scheduler in `soemdsp`
* production batch API too early
* repo divergence/behind-origin states
* old local docs conflicting with CODEGUIDE
* stale Codex context being mistaken for current repo truth

Medium:

* Director pulling engineering agents into public work too early
* Console/Tracer adding shared abstractions too soon
* Void sketches being mistaken for runtime architecture
* stale active stamps

Low:

* Console/Tracer visual code divergence by itself
* high routing load when stamps are clean

## Current Priority

Vision takes over direct `soemdsp` inspection and implementation.

Continue the runtime proof ladder toward `soemdsp-sandbox`.

Keep CODEGUIDE usable as Vision memory.

Keep other agents light.

Keep Soundemote becoming harder to ignore.

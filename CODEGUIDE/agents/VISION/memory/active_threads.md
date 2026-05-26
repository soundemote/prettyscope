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

## ¤CODEX¤ Codex Active Thread

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
* keep using Architect for difficult-to-confirm widget interactions, browser-native media behavior, mouse behavior, and audible/visual matching

Vision time-awareness rule:

* Vision is aware of time only when checking a clock or when Architect reports time
* whenever Architect gives an important time/runway update, record it in durable memory
* latest Architect time update: Day 2, 11:39 PM
* Day 2 means 58 days left
* local machine clock near that update: 2026-05-25 23:40:20 -07:00
* Architect may continue having Vision work through part of the night because continuing can be driven by simple `continue` prompts

Vision / business boundary:

* the business pressure is real: Soundemote needs to become a functional business so Architect does not have to take another low-paying job and waste life potential
* DIRECTOR and other business/money agents own business strategy, money path, offers, audience, and public strategy
* Vision should not absorb the business lane
* Vision should stay focused on `soemdsp`, `soemdsp-sandbox`, and the technical proof ladder unless Architect explicitly asks for cross-agent alignment

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
* sandbox shell displays status, contract, boundary flags, phases, artifact links, artifact reachability, artifact-packet status, and a browser-native WAV player
* sandbox shell visibly applies the consumer checklist and shows warning states for unsafe/unsupported manifest values
* sandbox shell draws a read-only waveform from the generated WAV
* sandbox shell overlays manifest-derived phase regions on the waveform and exposes phase view controls
* sandbox shell derives phase time ranges, durations, and WAV share from manifest phase sample counts and WAV metadata
* sandbox shell displays the current waveform phase in the waveform header and highlights the active phase button
* sandbox shell displays the current waveform cursor frame and decoded sample value
* waveform controls are decoupled from native audio seeking to avoid slider/audio reset loops; native audio playback can still drive waveform position
* waveform header has a Follow Audio / Free View toggle so Architect can choose audio-following transport view or independent waveform inspection
* sandbox shell displays first/second frequency and amplitude from the generated summary artifact
* sandbox shell displays frequency/amplitude resync deltas and ratios from the generated summary artifact
* sandbox shell displays producer proof flags from the manifest: demo identity, artifact kind, non-runtime API status, non-scheduler status, non-audio-engine status, and expected frequency/amplitude setter support
* sandbox shell displays source file metadata from the manifest response: manifest bytes and manifest modified time
* sandbox shell displays phase coverage status proving manifest phase sample totals match WAV frame count
* sandbox shell displays artifact coverage status proving the manifest names the expected display artifact kinds before reachability checks
* sandbox shell displays read-only inline text reports for the combined summary, WAV metadata report, and phase reports
* sandbox shell displays the artifact manifest as pretty-printed read-only JSON in the same document viewer
* sandbox shell clears stale dependent UI surfaces when manifest loading fails
* sandbox shell displays served artifact modified times from HTTP Last-Modified metadata
* sandbox shell checks artifact reachability with metadata-only HTTP HEAD requests
* sandbox shell labels artifact table columns: Label, Kind, Path, Modified, Status
* sandbox server sends no-store headers for local JSON and file responses
* sandbox shell displays browser-side manifest response load time
* sandbox shell displays manifest response cache headers in the Source panel
* sandbox shell displays the artifact reachability method as `HEAD`
* sandbox shell guards malformed-but-readable manifest JSON before rendering

Important recent repo event:

* `.codex/AGENTS.md` divergence resolved
* local removal won
* canonical docs now live in CODEGUIDE
* merge commit: `e437f77 Merge remote-tracking branch 'origin/main'`
* repo became no longer behind origin

Last completed Vision task:

```
Guard malformed manifest shape.
```

Task goal:

```
Fail visibly and clear stale UI when `/api/manifest` returns valid JSON that is
not the expected sandbox manifest shape, instead of throwing during render.
```

Added:

* minimal manifest shape guard before render
* checks for manifest object, sandbox handoff, WAV metadata, WAV frame count, artifact links array, and phases array
* malformed shape failures reuse the existing Check-state cleanup path
* README note for malformed manifest shape checks

Verification note:

* `python -m py_compile server.py` passed
* browser runtime parsed `public/app.js`
* normal live browser load still reported `Manifest: OK`, `Source: Loaded`, `Documents: 5 Loaded`, artifact packet `7/7 OK 92.88 KB`, `Artifact Coverage: Complete`, and `Phase Coverage: Complete`
* temporary malformed-manifest server with valid JSON but missing sandbox handoff reported `Manifest: Check` and `sandbox handoff missing`
* malformed shape path cleared artifact rows, checklist rows, phase rows, and waveform metadata rows
* browser returned to 8765 with the normal green state restored
* browser console error log was empty

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
72a11ad Guard malformed manifest shape
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

## ¤CONSOLE¤ Console Active Thread

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
* Console wrote `C:\Users\argit\Desktop\asciiscope\docs\CLAP_STARTINGPOINT_HANDOFF.md`
* handoff says the reusable middle is `audio/plugin input -> SignalFrame -> visual scene / renderer`
* scenes should keep asking for named signal sources, latest samples, stats, and timing
* scenes should not know about CLAP, JUCE, plugin processors, ports, buses, or host callbacks
* Asciiscope CLAP identity rename completed
* JUCE visual component added
* `ui::AsciiscopeVisualComponent` exists
* component is owned by `MainPanel`
* ticked by `PluginEditor::idle()` at 60 Hz
* currently fed from existing VU/scalar data
* audio snapshot path was recommended as next major milestone

Likely next Console milestone:

```
Inspect baconpaul/sidequest-startingpoint, keep its JUCE/CLAP/CMake structure intact,
and make a minimal Asciiscope CLAP startingpoint without pulling sandbox internals.
```

Guidance:

* Console does not need to report every local edit
* report milestones, blockers, commits, repo unsafe state, or boundary decisions
* `IVisualSurface` is now a likely extraction before/during plugin work, but only when the CLAP/editor split needs it
* do not force `IVisualSurface` before the startingpoint/template shape is understood
* keep the base renderer CPU-first and sample-aware
* do not make OpenGL the implied migration target for the core Asciiscope renderer
* no direct `soemdsp-sandbox` coupling
* no collision with Tracer
* do not reuse terminal input polling, Windows console buffer output, command-line capture flags, thread sleeps as timing, or stdout rendering in the plugin path

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

## ¤TRACER¤ Tracer Active Thread

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

## ¤DIRECTOR¤ DIRECTOR Active Thread

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

Vision boundary:

```
DIRECTOR owns business/money strategy.
Vision stays focused on soemdsp / soemdsp-sandbox technical proof unless Architect explicitly asks for alignment.
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

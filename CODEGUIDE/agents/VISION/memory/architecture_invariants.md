# Architecture Invariants

Durable architecture rules for Vision.

This file exists to preserve Soundemote’s core technical and organizational invariants across chats, agents, repo moves, and context loss.

If any task conflicts with these rules, stop and ask Architect/Vision before continuing.

## Highest-Level Rule

Soundemote is an ecosystem.

Do not collapse the ecosystem into one repo, one framework, one plugin wrapper, one UI model, one runtime assumption, or one agent’s taste.

Each lane should remain healthy in its own right.

Shared architecture should emerge only after repeated proofs show the shape clearly.

## Core Soundemote Principles

* BYOD DSP
* NO STRINGS ATTACHED
* runtime correctness first
* reflection-heavy architecture
* editor-ready metadata
* serialization-ready semantics
* avoid framework lock-in
* beautiful + musical UX matters
* low-level DSP objects are not graph nodes
* runtime graph nodes wrap, describe, bind, and eventually schedule DSP atoms
* binding connects layers
* do not merge layers

## Codex / soemdsp Invariants

Codex owns `soemdsp` and `soemdsp-sandbox`.

The core runtime must remain clean, small, and reusable.

Do not contaminate core runtime with:

* plugin host assumptions
* JUCE assumptions
* CLAP assumptions
* website assumptions
* social/media assumptions
* UI rendering assumptions
* business/Director assumptions

## Circuit / DSP Object Boundary

This is the most important technical invariant:

```
Circuit does not own concrete DSP objects.
DSP objects do not know Circuit.
Binding is the bridge.
```

Correct layering:

```
Circuit / runtime graph
    -> node/parameter metadata
    -> DSP binding metadata
    -> externally owned DSP memory/state
    -> low-level DSP object
```

Do not collapse this.

Do not make low-level DSP objects graph nodes.

Do not make `Circuit` store concrete DSP object instances.

Do not make DSP objects know about:

* Circuit
* Node
* Port
* Connection
* ControlGraph
* editor state
* UI state
* plugin host state
* serialization format
* CLAP/JUCE/web state

## DSP Object Contract

Low-level DSP objects should be:

* plain structs
* realtime-safe
* no heap allocation in hot paths
* no exceptions in hot paths
* no virtual dispatch in hot paths
* externally owned memory/state where appropriate
* base-offset-friendly where appropriate
* small semantic accessors
* clear methods like `next()`, `reset()`, `process()`, `processSample()`
* free of editor/graph/plugin/UI ownership

Externally owned memory is allowed.

Hidden ownership is not.

## DSP Binding Invariants

DSP binding is a parameter/state bridge.

DSP binding is not:

* a scheduler
* a plugin abstraction
* a graph executor
* a DSP object owner
* a ControlGraph curve engine
* a normalized transport system
* a UI system
* a serialization authority by itself

Important proven path:

```
Circuit parameter
    -> DspParameterBinding
    -> external memory slot
    -> low-level DSP object reads that memory
```

DSP binding apply should:

* validate first
* write second
* fail safely
* preserve all-or-nothing behavior inside a single `DspObjectBinding`
* report clearly
* allow callers to apply multiple bindings sequentially
* avoid production batch API until the shape is proven

DSP binding apply should not:

* run DSP processing
* schedule graph execution
* mutate Circuit
* perform ControlGraph shaping
* perform normalized parameter transport
* own DSP memory
* own DSP objects
* know plugin or host concepts

## ControlGraph Invariants

ControlGraph owns musical/perceptual shaping.

`Circuit::setParameterNormalizedValue` is raw linear transport.

`midValue` is preserved metadata and may be used to generate ControlGraph curves, but it must not contaminate raw parameter assignment.

Important proven ControlGraph path:

```
macro knob
    -> ControlGraph
    -> curve/midpoint shaping
    -> validation
    -> target validation
    -> safe apply
    -> Circuit parameter mutation
```

Do not move curve shaping into DSP binding apply.

Do not make DSP binding depend on ControlGraph.

Do not make raw Circuit parameter assignment musical/perceptual by default.

## Scheduler Invariant

Do not introduce a scheduler just because manual processing demos are succeeding.

Manual caller-owned demos are allowed.

Demo-local chains are allowed.

Caller-owned processing order is allowed.

A production scheduler requires explicit Architect/Vision approval.

Before scheduler design, know:

* what is being scheduled
* what owns DSP object state
* what owns memory
* how nodes map to DSP atoms
* how audio/control/trigger rates interact
* how validation protects execution
* how realtime safety is preserved
* how graph/editor/plugin boundaries stay clean

Until then:

```
caller-owned manual proof first
repeated proof second
scheduler later
```

## Batch API Invariant

Do not introduce production batch APIs just because sequential apply demos exist.

Allowed:

* demo-local aggregation
* caller-owned sequential apply
* per-binding summaries
* report helpers
* proof demos

Not allowed without explicit approval:

* production batch apply API
* scheduler-like batch executor
* graph-owned batch state
* hidden partial apply semantics

Current rule:

```
apply one DspObjectBinding safely
let callers sequence multiple bindings manually
aggregate locally in demos until the real shape emerges
```

## Plugin Boundary Invariant

Core runtime should not depend on plugin frameworks.

Do not add to `soemdsp` core unless explicitly approved:

* JUCE dependency
* CLAP dependency
* plugin processor assumptions
* plugin editor assumptions
* host automation assumptions
* plugin parameter wrapper as source of truth

Plugin layers may adapt to runtime concepts.

Runtime should not become plugin-shaped prematurely.

## Serialization Invariant

Serialization should preserve runtime/editor meaning without forcing one UI or plugin implementation.

Stable IDs matter.

Type names matter.

Metadata matters.

Avoid serialization formats that only work for one frontend.

Serialization should eventually support:

* runtime graph state
* node/port/connection identity
* parameter state
* ControlGraph state
* layout/editor metadata
* DSP binding metadata where appropriate

But do not let serialization dictate hot-path DSP structure.

## Reflection / Metadata Invariant

Reflection metadata is part of the architecture.

Runtime objects should be inspectable enough for:

* editor UI
* validation
* reporting
* serialization
* debugging
* future scripting
* future plugin/export paths

But reflection must not pollute low-level DSP hot paths.

## Console / Asciiscope Invariants

Console owns:

* Asciiscope
* Asciiscope CLAP
* terminal-first visuals
* ASCII visual identity
* SignalFrame / SignalSource direction
* Asciiscope plugin visual path

Asciiscope should remain independent.

Do not make Asciiscope depend directly on `soemdsp-sandbox` internals.

Do not treat `CircuitSnapshot` as a live signal API.

Do not force `IVisualSurface` or another shared abstraction until the concrete JUCE/plugin path proves what is needed.

Console and Tracer may diverge.

Divergence is acceptable if extraction seams remain clear:

* where signal enters
* where state updates
* where drawing/rendering happens
* what is reusable core
* what is plugin/editor shell

## Tracer / Prettyscope Invariants

Tracer owns:

* Prettyscope
* Prettyscope CLAP
* OpenGL/phosphor visual lane
* descriptor-owned parameters
* renderer adapter path
* future golden renderer port

Prettyscope descriptors are source of truth.

Sidequest/JUCE/CLAP plumbing adapts to descriptors.

Do not let host/plugin parameter wrappers become the design authority.

Do not port the golden renderer blindly.

Correct order:

```
plugin shell builds
descriptor parameters adapt into host/plugin path
editor-visible visual parameter controls exist
audio snapshot queue/editor feed exists
first simple OpenGL view proves lifecycle
renderer adapter boundary exists
golden renderer ports through the boundary
```

Do not remove inherited synth/MIDI/voice/Sidequest concepts until replacement truth is stable.

## Console / Tracer Divergence Invariant

Do not worry about Console and Tracer code looking different.

The concern is not sameness.

The concern is extractability.

Acceptable divergence:

* visual experiments
* renderer code that can be reread and extracted
* duplicated proof code
* separate plugin paths
* different UI structures
* experiments that reveal the core

Bad divergence:

* accidental dependency tangles
* unclear ownership
* hidden assumptions
* plugin shell hacks that become permanent
* cross-repo coupling without approval

Key review questions:

```
Where does signal enter?
Where does state update?
Where does drawing happen?
What part is reusable core?
What part is plugin/editor shell?
```

## Void Invariants

Void is separate from the normal routed agent mesh.

Void works directly with Architect.

Void owns:

* Soundemote website
* browser-native creative sandbox
* web visual experiments
* Prettyscope-like web sketches
* DSP/audio-visual interaction playground

Void can explore freely.

Void does not need to wait for the real sandbox.

Void should not define core runtime architecture.

Void sketches can inspire, but they should not become runtime law without Vision/Architect routing.

## DIRECTOR Invariants

DIRECTOR owns:

* business
* money
* audience
* public strategy
* social media
* YouTube
* offers
* commissions
* finished creative product strategy

DIRECTOR does not own:

* runtime architecture
* code execution
* Codex task assignment
* plugin architecture
* DSP binding design

Business principle:

```
The ecosystem is gravity, not the fenced-off product.
```

Tools create:

* attention
* trust
* adoption
* awe
* proof of taste
* proof of technical power

Money comes from:

* finished works
* commissions
* music
* audiovisual pieces
* sound design
* sound packs
* Hydrus when ready
* creative products made with the ecosystem

Do not rush Hydrus.

Do not beg.

Do not use shallow hype.

## Agent Routing Invariants

Architect is the manual router.

There is no live multi-agent room.

Agents should not assume another agent has seen anything unless Architect relays it.

Vision is taking over direct `soemdsp` / `soemdsp-sandbox` implementation.

Codex is optional historical context when Architect pastes Codex reports or asks Vision to consult Codex.

Vision's first direct `soemdsp` proof after takeover was:

```
aaf4d9b Add manual DSP object block resync demo
```

Latest direct `soemdsp` proof:

```
fe267bb Document DSP execution questions
```

Console and Tracer report by milestone/boundary.

DIRECTOR mostly speaks directly with Architect.

Void works directly with Architect and is separate.

Vision routes only when routing protects:

* architecture
* sequence
* boundaries
* repo safety
* money/public accuracy
* momentum

## Stamp Invariant

Formal handoffs and reports use:

```
[received: Sender→Receiver: xxxx]
[sent: Sender→Receiver: xxxx]
```

The `received` line points backward.

The `sent` line points forward.

The sent stamp must be the last stamp line.

If the Attention Convention is used, the final `Attention: Architecth` line goes after the stamps.

Casual conversation does not require stamps.

Stamps are a distributed working-memory checksum.

## Attention Convention Invariant

When an agent needs to get Architect's attention, the next report or reply starts and ends with:

```
Attention: Architecth
```

At the top, one blank line appears before any additional text.

At the bottom, one blank line appears after the final normal line, then the attention line repeats as the final line.

Use this only for blockers, ambiguity, conflict, stale state, missing files, unsafe repo state, cross-boundary decisions, or other items requiring explicit Architect attention.

## Push Policy Invariant

Push bandwidth is limited.

Agents should not recommend pushes by default.

Agents report repo status only:

* working tree clean/dirty
* ahead of origin by N commits
* behind origin by N commits
* conflicts if any

Architect / DIRECTOR push every little while.

If a repo is behind origin, pause risky new coding until the divergence is understood.

## Abstraction Freeze Rule

Do not introduce major shared abstractions just because current proofs are successful.

Agents must ask Architect/Vision before adding:

* scheduler
* production batch API
* shared visual surface
* shared renderer interface
* plugin abstraction layer
* graph-owned DSP object storage
* cross-repo dependency
* common framework used by multiple agents

Default rule:

```
prove behavior first
repeat the proof
observe the shape
only then extract the abstraction
```

## Success Standard

The current push does not require everything to be finished.

The goal is:

```
Soundemote becomes undeniable.
```

Undeniable means people can see, hear, run, follow, trust, and eventually buy into what Architect is building.

Build small proofs.

Preserve boundaries.

Keep the work alive.

Keep Soundemote becoming harder to ignore.

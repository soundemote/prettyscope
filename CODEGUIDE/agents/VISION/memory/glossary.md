# Glossary

Durable glossary for Vision.

This file preserves important Soundemote terms, project names, agent names, and architectural language so future chats do not lose meaning.

## Soundemote

Soundemote is an audio-visual DSP technology company creating multiplatform audio plugins and video FX generators with analog aesthetics for modern multiplatform frameworks.

Soundemote is also the broader ecosystem around:

* DSP/runtime systems
* visualizers
* modular audio tools
* plugin prototyping
* browser-native creative sketches
* finished audiovisual works
* sound design
* music
* creative products

## Architect

Argi.

The human center of the system.

Final authority.

Manual router between agents.

Owns final taste, direction, decisions, and priorities.

## Vision

Architecture / sequencing / cross-project coherence agent.

Vision may edit code, docs, and task files directly when Architect assigns Vision to do so.

Vision gives bounded instructions, preserves boundaries, tracks active threads, and chooses the next smallest useful task.

When Vision edits code, Vision must preserve repo ownership boundaries, inspect existing patterns, build/test when appropriate, and report repo status.

## Codex

Execution agent for `soemdsp` and `soemdsp-sandbox`.

Owns the core runtime/DSP spine.

Codex works in tight bounded proofs:

```
one proof
one demo
one commit
one report
```

Codex may also be used as optional historical context while Vision takes over direct `soemdsp` / `soemdsp-sandbox` implementation.

Architect may paste Codex reports into Vision when useful.

## Console

Execution agent for Asciiscope and Asciiscope CLAP.

Owns terminal-first ASCII visuals and the Asciiscope plugin visual lane.

## Tracer

Execution agent for Prettyscope and Prettyscope CLAP.

Owns OpenGL/phosphor/GPU visuals, descriptor parameters, plugin visual path, and future golden renderer port.

## Void

Website and browser-native creative sandbox agent.

Void works directly with Architect and is separate from the normal routed agent mesh.

Void can freely sketch web-native DSP/audio-visual interactions.

## DIRECTOR

Business / money / audience / public strategy agent.

DIRECTOR helps Architect with:

* money strategy
* social media
* YouTube
* offers
* commissions
* public positioning
* finished creative product strategy

DIRECTOR mostly speaks directly with Architect.

## CODEGUIDE

Canonical guidance folder for Soundemote company, agent, code, protocol, template, and Vision-memory docs.

Current location:

```
https://github.com/soundemote/prettyscope-revival/tree/main/CODEGUIDE
```

CODEGUIDE is company infrastructure.

It is not process noise.

Architect remains the router when Codex context is needed.

## soemdsp

Core DSP/runtime library.

Owned by Vision, with Codex available only as optional pasted historical context.

Contains the runtime spine that future Soundemote systems may build on.

## soemdsp-sandbox

Local sandbox environment built on `soemdsp`.

Intended to evolve into:

* DSP sandbox
* visual modular editor
* plugin prototyping environment
* shader/signal graph environment
* scripting environment
* exportable/open modular platform

The first local repo now exists at:

```text
C:\Users\argit\Desktop\soemdsp-sandbox
```

Current first shell:

* read-only manifest consumer
* Python stdlib server
* static browser UI
* consumes generated `soemdsp` bound WAV resync manifest
* displays status, boundary flags, phases, artifact links, and source paths
* visibly applies the read-only consumer checklist
* displays first/second frequency and amplitude from the generated summary artifact
* displays frequency/amplitude resync deltas and ratios from the generated summary artifact
* draws a read-only waveform from the generated WAV
* overlays manifest-derived phase regions on the waveform
* derives phase time ranges, durations, and WAV share from manifest phase sample counts and WAV metadata
* displays the current waveform phase and highlights the active phase button
* displays the current waveform cursor frame and decoded sample value
* keeps waveform view controls separate from native audio seeking to avoid slider/audio reset loops
* exposes a Follow Audio / Free View toggle for choosing audio-following transport view or independent waveform inspection
* plays the generated WAV with browser-native audio controls

The full modular sandbox does not exist yet.

Void currently acts as a creative web sketchpad while this is being built.

## Asciiscope

Terminal-first ASCII visual instrument.

Owned by Console.

Used for:

* terminal visuals
* ASCII oscilloscope-style output
* social/capture/reel visuals
* signal-reactive animation scenes

## asciiscope-clap

CLAP/JUCE plugin path for Asciiscope visuals.

Owned by Console.

Current direction:

* preserve Asciiscope identity
* add plugin visual component
* add audio-to-visual snapshot path
* avoid premature shared visual abstraction

## Prettyscope

OpenGL/phosphor/GPU visualizer.

Owned by Tracer.

The standalone renderer is the golden visual reference.

## prettyscope-clap

CLAP/JUCE plugin path for Prettyscope visuals.

Owned by Tracer.

Current direction:

* descriptor-owned visual parameters
* audio snapshot queue
* editor-visible controls
* OpenGL view
* renderer adapter boundary
* future golden renderer port

## Hydrus

Important future Soundemote creative/product work.

Hydrus should not be rushed.

Hydrus should arrive with gravity behind it.

DIRECTOR may prepare the audience over time, but Hydrus should not become a panic product.

## Ecosystem As Gravity

Core business principle.

The tools are not primarily the fenced-off product.

The tools create:

* attention
* trust
* adoption
* awe
* proof of taste
* proof of technical power

Money comes from finished works, commissions, music, sound design, audiovisual products, Hydrus when ready, and creative products made with the ecosystem.

## Undeniable

Current success standard.

Soundemote does not need to be finished immediately.

It needs to become undeniable.

Undeniable means people can:

* see it
* hear it
* run it
* follow it
* trust it
* understand that something real is forming
* eventually buy or commission finished work from it

## Circuit

Core runtime graph container in `soemdsp`.

Holds runtime graph structure such as nodes, ports, connections, and parameters.

Circuit should not own concrete low-level DSP objects.

## Node

Runtime graph unit inside a Circuit.

Nodes describe graph structure and interface points.

Low-level DSP objects are not themselves graph nodes.

## Port

Input/output interface on a node.

Ports may represent audio, control, trigger, or other signal types depending on runtime design.

## Connection

Runtime relationship between ports/nodes.

Connections are part of the Circuit graph structure.

## Parameter

Runtime value associated with a node.

Parameters may have:

* value
* defaultValue
* minValue
* midValue
* maxValue
* metadata

## midValue

Parameter metadata representing a meaningful midpoint.

Used to preserve musical/perceptual control feel.

`midValue` may be used to generate ControlGraph curves.

`midValue` must not contaminate raw parameter assignment.

## Normalized Parameter Transport

Raw normalized value pathway in Circuit.

`Circuit::setParameterNormalizedValue` is raw linear transport.

It does not own musical/perceptual shaping.

## ControlGraph

Control/macro mapping system.

Owns musical/perceptual shaping.

Can evaluate control values, curves, scales, and target application.

Important path:

```
macro knob
    -> ControlGraph
    -> curve/midpoint shaping
    -> validation
    -> target validation
    -> safe apply
    -> Circuit parameter mutation
```

## Curve / Scale

ControlGraph shaping concepts.

Used to transform macro/control values before applying them to Circuit parameters.

## ParameterTarget

ControlGraph metadata identifying a target Circuit parameter.

Used for safe target validation and apply.

## CircuitSnapshot

Snapshot of Circuit state for inspection/export.

Metadata/reporting concept.

Not a live signal API.

Do not treat CircuitSnapshot as a realtime visualization feed.

## CircuitReport

Combined report/inspection helper for Circuit state and validation.

Used for debug, text export, and correctness checking.

## DSP Object

Low-level DSP struct or object.

Should be:

* plain
* realtime-safe
* externally owned where needed
* no heap allocation in hot paths
* no exceptions in hot paths
* no virtual dispatch in hot paths
* independent from graph/editor/plugin/UI ownership

DSP objects should not know Circuit.

## DSP Object Contract

Rules for low-level DSP object shape.

Key idea:

```
DSP objects are atoms.
Runtime graph nodes describe/wrap/bind/schedule them later.
Binding connects layers.
```

## DspObjectBinding

Metadata describing how a runtime/Circuit object connects to low-level DSP object state.

A `DspObjectBinding` can contain one or more `DspParameterBinding` entries.

## DspParameterBinding

Binding entry mapping a Circuit parameter to an external DSP memory slot.

Important path:

```
Circuit parameter
    -> DspParameterBinding
    -> external memory slot
```

## External Memory Slot

Memory owned outside Circuit and outside DSP binding metadata.

Example:

```
float gainMemory = 0.0f;
```

A DSP object may point at this memory.

DspBinding apply may write current Circuit parameter values into it.

## DSP Binding Apply

Operation that copies current Circuit parameter values into external memory slots described by `DspParameterBinding`.

DSP binding apply is:

* validation-first
* all-or-nothing inside a single `DspObjectBinding`
* not a scheduler
* not DSP processing
* not graph execution
* not plugin code
* not ControlGraph shaping

## DspBindingApplyResult

Full result of applying DSP parameter bindings.

Tracks:

* ok
* parametersApplied
* messages

## DspBindingApplySummary

Compact summary of a `DspBindingApplyResult`.

Tracks:

* ok
* parametersApplied
* messageCount

## All-Or-Nothing Apply

Invariant for applying a single `DspObjectBinding`.

If validation fails, no memory slots should be written.

Validation first.

Writes second.

## Caller-Owned Manual Chain

Demo/proof where the caller manually owns DSP object processing order.

Example:

```
input
    -> TinyGainDsp
    -> TinyBiasDsp
    -> output
```

This is allowed.

It is not a scheduler.

## Scheduler

Future runtime component that may eventually execute DSP graph processing order.

Not designed yet.

Do not introduce scheduler abstractions just because manual chain demos work.

## Production Batch API

Future possible API for applying multiple DSP bindings or processing batches.

Not designed yet.

Current sequential apply/aggregation demos are caller-owned proofs only.

Do not introduce production batch API without explicit approval.

## DSP Block Phase Report

Small runtime DSP report value for caller-owned block proofs.

Captures:

* preflight ok
* apply ok
* process ok
* bindings checked
* preflight messages
* parameters applied
* apply messages
* samples processed

It is reporting/status only.

It has a print helper and a text-file write helper.

It should not:

* own DSP objects
* own DSP memory
* process audio
* become a scheduler
* become a production batch API

## SignalFrame

Asciiscope signal frame concept.

Represents signal data consumed by visual scenes/renderers.

Owned by Console / Asciiscope lane.

## SignalSource

Source of signal data for Asciiscope visuals.

## ISignalInput

Asciiscope input abstraction.

Current Asciiscope-style boundary:

```
ISignalInput
    -> SignalFrame
    -> AnimationScene
    -> ConsoleRenderer
```

## AnimationScene

Asciiscope scene logic consuming `SignalFrame`.

## ConsoleRenderer

Asciiscope terminal renderer.

Draws terminal/ASCII visuals.

## AsciiscopeVisualComponent

JUCE visual component in `asciiscope-clap`.

Owned by Console.

Plugin-side proof of Asciiscope visual rendering.

## ScopeAudioSnapshot

Prettyscope CLAP audio snapshot shape.

Captures audio block data for editor/visual use.

Owned by Tracer / Prettyscope CLAP lane.

## ScopeAudioSnapshotQueue

Audio-to-editor snapshot queue in `prettyscope-clap`.

Used by editor to receive latest scope audio snapshot.

## ScopeSnapshotInspector

Tiny editor panel showing audio snapshot levels.

Owned by Tracer.

## ScopeOpenGLView

JUCE/OpenGL component in `prettyscope-clap`.

First plugin OpenGL scope view proof.

## Visual Parameter Descriptor

Prettyscope parameter truth object.

Should include:

* stable string ID
* stable numeric ID
* display name
* category
* default value
* min value
* mid value
* max value
* automatable flag
* visible flag

Descriptors are source of truth.

Plugin/host systems adapt to descriptors.

## Sidequest Patch/Param

Inherited plugin parameter system used in `prettyscope-clap`.

Adapter target, not truth.

Prettyscope descriptors should drive Sidequest patch params, not the other way around.

## Renderer Adapter Boundary

Prettyscope CLAP boundary that should let the current simple OpenGL XY renderer and future golden phosphor renderer occupy the same slot.

Golden renderer should port through this boundary.

## Golden Renderer

Standalone Prettyscope renderer look.

Phosphor/OpenGL visual identity that should be preserved.

Do not copy blindly into plugin shell before boundary exists.

## IVisualSurface

Possible future shared visual surface abstraction.

Do not introduce prematurely.

Console should not add it until Asciiscope terminal and JUCE/plugin paths prove the required drawing interface.

## Browser-Native Creative Sandbox

Void’s lane.

Web-based creative sketchpad for DSP/audio-visual interaction.

Can produce ideas that later inform other projects.

Does not define core runtime architecture.

## Agent

A role/persona/process helping Architect with a specific lane.

Agents are not assumed to communicate directly.

Architect routes messages manually.

## Stamp

Two-line trace marker for formal handoffs and reports.

Format:

```
[received: Sender→Receiver: xxxx]
[sent: Sender→Receiver: xxxx]
```

The received line points backward.

The sent line points forward.

Stamps are a distributed working-memory checksum.

## Attention Convention

Report/reply wrapper used when an agent needs Architect to notice something explicitly.

Exact first and final line:

```
Attention: Architect
```

At the top, one blank line follows before additional text.

At the bottom, one blank line comes before the final repeated attention line.

If Architect does not respond after the first attention-marked reply, keep using the same top-and-bottom attention convention on later reports/replies until Architect sees it or the issue is cleared.

Use for blockers, ambiguity, stale state, missing files, unsafe repo state, boundary conflicts, or other items requiring Architect's explicit attention.

## Active Thread

Currently active task/report chain for an agent.

Usually identified by the latest task stamp.

Side acknowledgments do not automatically replace active task threads.

## Handoff

A formal message routed from one agent to another through Architect.

Should be paste-ready, bounded, and clear.

## Milestone

Meaningful completed unit of work.

Examples:

* demo completed
* plugin visual component added
* descriptor adapter proven
* snapshot path added
* docs updated
* commission menu drafted

## Local Work

Implementation detail inside an approved milestone.

Examples:

* small UI tweak
* compile fix
* include adjustment
* variable rename
* small refactor

Agents should not report every piece of local work.

## Abstraction Freeze

Rule against introducing major shared abstractions too early.

Agents must ask before adding:

* scheduler
* production batch API
* shared visual surface
* shared renderer interface
* plugin abstraction layer
* graph-owned DSP object storage
* cross-repo dependency
* common framework used by multiple agents

## Push Policy

Push bandwidth is limited.

Agents should report repo status only unless Architect asks about pushes.

Architect / DIRECTOR push every little while.

## Repo Status

Report shape:

```
working tree clean/dirty
ahead of origin by N commits
behind origin by N commits
conflicts if any
```

If behind origin, pause risky work until understood.

## Boundary

Ownership and architecture line that should not be crossed casually.

Examples:

* Codex owns core runtime
* Console owns Asciiscope
* Tracer owns Prettyscope
* Void owns browser sketches
* DIRECTOR owns business
* Vision owns sequencing

## Extraction Seam

A clear place where useful core logic can later be extracted.

For visual systems, important seams are:

* where signal enters
* where state updates
* where drawing/rendering happens
* what is reusable core
* what is plugin/editor shell

## Multiplatform Frameworks

Target environment concept for Soundemote tools.

Includes frameworks and contexts where audio plugins, video FX, visualizers, or creative tools can be built across platforms.

Do not hard-lock Soundemote identity to one framework too early.

## Analog Aesthetics

Visual/audio taste direction emphasizing analog-like feeling, such as:

* scopes
* phosphor
* glow
* drift
* imperfection
* signal motion
* hardware-like response
* tactile controls
* musical behavior

## Finished Works

Sellable creative outputs made with the ecosystem.

Examples:

* music
* audiovisual pieces
* commissioned visuals
* sound packs
* visual loops
* release assets
* sound design
* Hydrus when ready

## Public Proof

Visible artifact showing Soundemote is real.

Examples:

* clip
* demo
* screenshot
* plugin editor
* web sketch
* audiovisual piece
* code milestone
* public repo activity

Public proof should be truthful and concrete.

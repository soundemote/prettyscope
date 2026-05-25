Vision should fill out the **protocols** and **templates** because those are coordination machinery.

DIRECTOR should fill out or refine the **business/public-facing** files later:

* `projects/BUSINESS.md`
* public positioning docs
* offer docs
* social/content templates
* YouTube strategy docs
* commission menu docs

Void can help with website/public presentation docs.

Codex/Console/Tracer should only fill project docs when their technical lane needs exact current state.

Next minimal useful file: `protocols/STAMPS.md`

# Stamp Protocol

Shared stamp protocol for Soundemote agent handoffs, task instructions, completion reports, and cross-agent coordination.

Stamps exist to keep manually routed agent messages traceable.

They do not carry architecture meaning.

They do not indicate priority.

They do not replace clear communication.

## Attention Convention

When an agent needs to get Architect's attention, put this exact line at the very top of the next report or reply:

```text
Attention: Architecth
```

Then leave one blank line before any additional text.

## Why Stamps Exist

There is no live multi-agent chat.

Architect manually copies messages between agents.

A stamp helps identify:

* which message is being answered
* which agent sent the current message
* whether a message is part of a formal handoff/report
* whether a thread has accidentally forked
* whether an old message is being answered by mistake

## When to Use Stamps

Use stamps on:

* task instructions
* completion reports
* formal handoffs
* cross-agent coordination messages
* milestone reports
* architecture decision replies
* formal read-only inspection reports

Do not use stamps on:

* casual discussion
* ordinary brainstorming
* quick clarifications
* ordinary Director/Architect business discussion
* ordinary Void/Architect sketch discussion
* messages that are not meant as handoffs or reports

## Current Format

Use two lines:

```
[received: Sender→Receiver: xxxx]
[sent: Sender→Receiver: xxxx]
```

Example:

```
[received: Codex→Vision: r8k2]
[sent: Vision→Codex: v4m9]
```

Another example:

```
[received: Vision→Console: b6r2]
[sent: Console→Vision: m8r5q]
```

## Sender and Receiver Names

Use the agent names exactly:

* Architect
* Vision
* Codex
* Console
* Tracer
* Void
* DIRECTOR

Do not invent alternate names in stamps.

Use `DIRECTOR` in all caps.

## Received Line

The `received` line repeats the stamp from the message being answered.

If Vision sent:

```
[sent: Vision→Codex: v4m9]
```

Then Codex’s reply should end with:

```
[received: Vision→Codex: v4m9]
[sent: Codex→Vision: fresh1]
```

The received stamp should not be changed.

It is the anchor to the prior message.

## Sent Line

The `sent` line is the new stamp for the current message.

It must be fresh.

It must be the final line of the message.

Example:

```
[received: Vision→Codex: v4m9]
[sent: Codex→Vision: k2p7]
```

## Stamp Format

Stamp IDs should be:

* 4–6 characters
* lowercase letters and/or numbers
* visually simple
* not reused nearby

Good stamps:

```
q5r7
m8r5q
h6q3
c9v2
z2m6
```

Bad stamps:

```
THIS_IS_A_STAMP
Q5R7
hello-world
q5 r7
q5r7!
1234567890
```

## Placement Rules

Both stamp lines go at the very end of a formal message.

The `sent` stamp must be the final line.

Do not place commentary after the `sent` stamp.

Correct:

```
Report body...

[received: Vision→Codex: q5r7]
[sent: Codex→Vision: b2m9]
```

Incorrect:

```
[received: Vision→Codex: q5r7]
[sent: Codex→Vision: b2m9]

Also, one more thing...
```

## Old Format

The old one-line format is obsolete:

```
[Console→Vision: q4n8t]
```

If an agent uses old format, Vision should interpret it as equivalent to:

```
[sent: Console→Vision: q4n8t]
```

Then Vision should correct the agent gently and move on.

## Repeated Stamps

Do not reuse nearby stamps.

If a stamp appears repeated, tell Architect/Vision.

Repeated stamps are not catastrophic, but they reduce traceability.

## Forked Threads

Sometimes Architect may send a clarification after a task is already active.

That can create a side branch.

If the side branch is only an acknowledgment, it does not replace the active task thread.

Example:

1. Vision sends active task:

   ```
   [received: Codex→Vision: b2m9]
   [sent: Vision→Codex: q5r7]
   ```

2. Vision later sends cadence clarification:

   ```
   [received: Codex→Vision: t4n8]
   [sent: Vision→Codex: z2m6]
   ```

3. Codex acknowledges:

   ```
   [received: Vision→Codex: z2m6]
   [sent: Codex→Vision: c8r4]
   ```

The active task still uses `q5r7`.

The acknowledgment branch does not automatically replace the active task thread.

If unsure, ask Vision which stamp is active.

## Casual Conversation

Architect does not need to stamp ordinary conversation.

DIRECTOR does not need to stamp ordinary business discussion with Architect.

Void does not need to stamp ordinary website sketch discussion with Architect.

Stamps are for handoffs and reports, not for every utterance.

## Responsibility

All agents should follow the protocol.

Vision is responsible for noticing stamp drift.

Architect may ask Vision to resolve confusing stamp state.

## Minimal Rule

When in doubt, end formal handoffs/reports with:

```
[received: Sender→Receiver: previous]
[sent: Sender→Receiver: fresh]
```

The `received` line points backward.

The `sent` line points forward.

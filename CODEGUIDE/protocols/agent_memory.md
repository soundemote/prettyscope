# Agent Memory

Agent operating memory lives in CODEGUIDE.

Each active agent owns a memory directory:

```text
CODEGUIDE/agents/VISION/memory/
CODEGUIDE/agents/CODEX/memory/
CODEGUIDE/agents/CONSOLE/memory/
CODEGUIDE/agents/TRACER/memory/
CODEGUIDE/agents/DIRECTOR/memory/
```

## Ownership

Agents may read any agent memory when they need context.

Agents should edit only their own memory unless Architect or Vision explicitly asks them to update another agent's memory.

Vision may read and maintain cross-agent memory for routing, coherence, and reboot continuity.

Architect may override any memory rule.

## What Belongs Here

Agent memory is for:

- current active threads
- stable operating context
- repo status that affects routing
- handoff summaries
- durable decisions
- unresolved blockers
- reboot notes

Keep memory compact and current. Prefer the latest useful state over full history.

## What Does Not Belong Here

Project implementation docs belong in the project repo.

Examples:

```text
soemdsp/docs/
soemdsp-sandbox/README.md
asciiscope/docs/
prettyscope-clap/docs/
```

Do not use random project working directories as agent memory spaces.

Do not store private scratchpad drift in product repos.

## Cross-Agent Use

Other agents may read an agent's memory for orientation.

Reading does not transfer ownership.

If an agent finds stale, missing, or conflicting memory outside its own directory, it should report the issue instead of silently rewriting another agent's memory.

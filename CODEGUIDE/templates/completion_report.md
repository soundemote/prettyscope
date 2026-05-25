# Completion Report Template

Use this template when an agent finishes a bounded task, milestone, inspection, or committed change.

If the report needs Architect's attention, put this exact line before the report title and repeat it as the final line of the report:

```text
Attention: Architecth

# Completed: `<task title>`

...

Attention: Architecth
```

Use that attention line only when the report includes a blocker, ambiguity, conflict, stale state, missing file, unsafe repo state, cross-boundary decision, or other item that needs explicit attention.

A completion report should make it easy for Architect and Vision to understand:

* what changed
* what did not change
* whether the work built/ran
* whether it was committed
* what the repo state is
* what stamp thread it belongs to

## Basic Shape

# Completed: `<task title>`

## Files Changed

* `path/to/file1`
* `path/to/file2`
* `path/to/file3`

## What Changed

* change 1
* change 2
* change 3

## What Was Intentionally Not Changed

Use this section when boundary preservation matters.

Examples:

* No scheduler added.
* No plugin code added.
* No shared abstraction introduced.
* No submodules changed.
* No inherited architecture removed.
* No cross-repo dependencies added.
* No production batch API added.
* No graph-owned DSP state added.

## Behavior / Demo Summary

Describe what the task now proves or enables.

Include exact output when the task includes a demo.

Example:

```
gain memory before: 0
apply result: ok: true, parameters applied: 1
gain memory after: 2
processSample(0.25): 0.5
```

## Generated Files

If generated files were written:

* list generated files
* list verification markers
* say whether they were removed before commit

Example:

Generated:

* `runtime_demo.report.txt`

Verified:

* `[DSP BINDING REPORT]`
* `ok: true`

Removed before commit:

* yes

If no generated files were written:

```
No generated files were written.
```

## Docs Updated

List docs updated:

* `docs/STATUS.md`
* `docs/PLAN.md`

Or:

```
No docs were updated.
```

## Build Result

Command:

```
`<build command>`
```

Result:

```
passed / failed
```

Include relevant failure details if failed.

## Run / Test Result

Command:

```
`<run or test command>`
```

Result:

```
passed / failed
```

Include output summary if useful.

## Commit

Commit:

```
`<hash> <message>`
```

Or:

```
Not committed.
```

## Repo Status

Report repo status only.

Include:

* working tree clean / dirty
* branch ahead/behind origin
* conflict state if any

Example:

```
Working tree clean.
main is ahead of origin/main by 1 commit.
main is behind origin/main by 0 commits.
```

If the repo is behind origin or conflicted, report it clearly and pause risky new work until Architect/Vision decides the safe next step.

Do not include push recommendations unless Architect explicitly asks.

## Risks / Notes

Optional.

Use only if something needs attention.

Examples:

* This required a small validation change.
* This revealed a naming inconsistency.
* This confirms existing behavior was already all-or-nothing.
* This leaves the next likely task as `<task>`.
* Repo is behind origin and needs inspection before more coding.

## Stamp

End with:

```
[received: Sender→Receiver: previous]
[sent: Sender→Receiver: fresh]
```

# Copy/Paste Completion Report Skeleton

# Completed: `<task title>`

## Files Changed

* `<file>`
* `<file>`

## What Changed

* `<change>`
* `<change>`

## What Was Intentionally Not Changed

* `<non-change>`
* `<non-change>`

## Behavior / Demo Summary

`<summary>`

Exact output summary:

```
`<line>`
`<line>`
`<line>`
```

## Generated Files

`<generated file status>`

## Docs Updated

* `<doc>`

## Build Result

Command:

```
`<build command>`
```

Result:

```
`<passed/failed>`
```

## Run / Test Result

Command:

```
`<run/test command>`
```

Result:

```
`<passed/failed>`
```

## Commit

`<hash> <message>`

## Repo Status

* working tree: `<clean/dirty>`
* ahead of origin: `<N>`
* behind origin: `<N>`
* conflicts: `<none/list>`

## Risks / Notes

`<optional>`

[received: `<Sender→Receiver: previous>`]
[sent: `<Sender→Receiver: fresh>`]

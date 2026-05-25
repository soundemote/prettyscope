# Push Policy

Do not mention pushes in normal agent reports unless Architect explicitly asks.

Push bandwidth is limited.

Architect / DIRECTOR will push every little while as needed.

Agents should focus on:

* doing bounded work
* building/testing
* committing clean checkpoints
* reporting repo status

## Agent Rule

Agents should not recommend pushes by default.

Agents should not include “push recommended” in every report.

Agents should not run `git push` unless Architect explicitly tells them to.

## Report Rule

Instead of saying:

```
Push recommended.
```

Say only:

```
Repo status:
- working tree clean
- branch is ahead of origin/main by N commits
```

That gives Architect / DIRECTOR enough information to decide when to push.

## When Pushes May Be Mentioned

Mention push only when:

* Architect asks whether to push
* Architect explicitly requests push instructions
* a task explicitly says to push
* a remote checkpoint is required before risky work
* another agent cannot continue without remote state

Otherwise, do not mention pushes.

## Default Workflow

Agent workflow:

```
edit
build/test
commit
report repo status
```

Architect / DIRECTOR workflow:

```
push every little while when bandwidth allows
```

## Minimal Rule

Commit cleanly.

Report ahead/behind status.

Do not talk about pushes unless asked.

# Push Policy

Do not mention pushes in normal agent reports unless Architect explicitly asks.

Push bandwidth is limited.

Architect / DIRECTOR will push every little while as needed.

Agents should focus on:

* doing bounded work
* building/testing
* committing clean checkpoints
* reporting repo status

## Agent Rule

Agents should not recommend pushes by default.

Agents should not include “push recommended” in every report.

Agents should not run `git push` unless Architect explicitly tells them to.

## Report Rule

Instead of saying:

    Push recommended.

Say only:

    Repo status:
    - working tree clean
    - branch is ahead of origin/main by N commits

That gives Architect / DIRECTOR enough information to decide when to push.

## When Pushes May Be Mentioned

Mention push only when:

* Architect asks whether to push
* Architect explicitly requests push instructions
* a task explicitly says to push
* a remote checkpoint is required before risky work
* another agent cannot continue without remote state

Otherwise, do not mention pushes.

## Default Workflow

Agent workflow:

    edit
    build/test
    commit
    report repo status

Architect / DIRECTOR workflow:

    push every little while when bandwidth allows

## Minimal Rule

Commit cleanly.

Report ahead/behind status.

Do not talk about pushes unless asked.

# Repository Guidelines

## Persistent project memory

The shared memory service is Basic Memory.

- Memory project: `second-brain`
- Vault path: `~/SecondBrain`
- This project's notes: `projects/c-programming-exercises`

Two files govern how memory is used. Read them rather than relying on what is
summarised here:

- **Rules** — `~/SecondBrain/AGENTS.md`. What may and may not be recorded, and
  how claims must be written. These apply to any work, at any time.
- **Procedure** — `~/SecondBrain/knowledge/oturum-protokolu.md`. What to load
  at the start of a session, what to propose at the end, and when to commit
  the vault.

At the start of a session, follow the protocol's session-start section: report
the current state and the smallest next action before changing any file.

At the end of meaningful work, follow its session-close section. During the
pilot, propose the updates and wait for the user's approval before writing.

One rule is repeated here on purpose, because getting it wrong cannot be
undone: never store secrets, credentials, tokens, private keys, or sensitive
personal data in memory.

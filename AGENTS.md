# Repository Guidelines

## Persistent project memory

The shared memory service is Basic Memory.

- Memory project: `second-brain`
- Project path: `projects/c-programming-exercises`

At the beginning of a session:

1. Read the project's `state` and `next-actions` notes from Basic Memory.
2. Report the current state and the smallest next action before changing files.
3. Search older memory only when past decisions are relevant; return at most five
   results and identify their source notes.

At the end of meaningful work:

1. Propose updates to the project `state`, `next-actions`, and `last-session`
   notes.
2. During the pilot, do not write durable memory until the user approves the
   proposed update.
3. Never record speculation as fact. Preserve `source` and `confidence`
   metadata and surface conflicts for confirmation.
4. Never store secrets, credentials, tokens, private keys, or sensitive personal
   data in memory.

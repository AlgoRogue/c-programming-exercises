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

How to write memory:

1. Edit the markdown files under `~/SecondBrain` directly. The MCP `write_note`
   tool matches notes by title rather than by file path, so even with
   `overwrite: true` it mints a duplicate entity, suffixes its permalink, and
   leaves the canonical permalink unresolvable — which breaks every note the
   session protocol asks for by name.
2. A note's `source` field records only the session that last edited it. When a
   note carries a claim inherited from an earlier session, keep that claim's own
   origin beside it rather than restamping it as your own observation.
3. Revising a note is not superseding it. Use `supersedes` only when a different
   note invalidates another; git already carries version history.

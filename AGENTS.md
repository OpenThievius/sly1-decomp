# Instructions for agents

This file is for AI agents (Claude, Codex or others) working in this repository. Read it
completely before changing anything, then README.md, CONTRIBUTING.md, LEGAL.md and
docs/ROADMAP.md. The repository follows the structure and conventions of the OpenRAC
decompilations (rac3-decomp, rac2-decomp), the sister project of the same maintainers: keep it
that way.

## What this repository is

A matching decompilation of *Sly Cooper and the Thievius Raccoonus* (PS2). The primary target
is the NTSC-U `SCUS_971.98`; PAL `SCES_509.17` comes second. The May 2002 prototype is
recognised by the tools and nothing is ever taken from it (docs/PROTOTYPE.md). The game is **C++** built with Sony's GNU EE GCC
2.9-ee-991111b (docs/TOOLCHAIN.md).

The project is being set up: nothing is matched yet, and there is no linked build yet.

| Path | What it is | Who writes it |
| --- | --- | --- |
| `config/versions.json` | every version: serial, role, disc and executable checksums | by hand, rarely |
| `config/splat/<version>.yaml` | splat's configuration | by hand |
| `config/<version>/symbol_addrs.txt` | names for retail addresses | by hand |
| `tools/`, `tests/` | setup, split, checks | by hand |
| `docs/` | research notes and decisions | by hand |
| `baserom/`, `asm/`, `assets/`, `build/`, `include/*.inc`, `include/include_asm.h` | your discs, and what is generated from them | never committed |

Every tool takes `--version us|eu|may19` where it makes sense, and reads its paths from
`tools/versions.py`.

## Commands

| Command | What it does |
| --- | --- |
| `python3 tools/setup.py [PATH ...]` | recognises disc images and writes `baserom/<version>/<executable>` |
| `venv/bin/python tools/setup_asm.py --version us` | runs splat; writes `asm/us/` and `build/us/` |
| `python3 tools/toolchain.py` | finds the compiler (`SLY1_TOOLCHAIN`) and its runner (`SLY1_RUNNER`, wibo, wine) and compiles a test unit |
| `python3 -m unittest discover -s tests` | the tools' unit tests (CI) |
| `python3 tools/proprietary.py` | scans what git would commit for game data and proprietary material |
| `python3 tests/check_repository.py` | `proprietary.py`, licence headers (CI) |

## Matching rules (from the first matched function on)

- **A match is retail's bytes in a build that equals retail.** Not a compiled object on its
  own, not a masked comparison, not a model's claim. Report exactly what you ran and what it
  printed.
- **Plain C++.** No inline assembly in functions, no register pins, no artificial barriers.
- **One flag set per source file**, never per function.
- **Globals are `extern`** until the data layout is modelled.
- **Our own names and types.** Retail is stripped: every function, type, field and file name
  is chosen by us from what retail's code does.
- If you get close but not exact, keep the attempt in `nonmatching/` with what still differs,
  and move on. Stop on a function after about ten compiles without getting closer.

## Rules

- **Derive everything ourselves.** Work from the retail executable of your own disc and public
  hardware documentation. Take nothing from anyone else: no code, symbol maps, splits, names or
  notes from other decompilations or ports of this game, and no third-party code. Never Sony's
  SDK source, samples or headers, or leaked or NDA material, not even as a reference.
- **OpenRAC is the exception.** Its own work (tools, build code, docs, toolchain research) may be
  used, openly credited: name it in the commit body and list it in THIRD_PARTY_NOTICES.md
  (LEGAL.md, "OpenRAC"). Not what OpenRAC took from others, and no Ratchet & Clank game code.
- **Nothing from the prototype.** No code, data, symbol names, signatures, types, field names
  or file lists from it, and no tool that extracts them. Looking at it to understand a function
  is allowed only if what you then write is entirely your own, reasoned from retail's bytes
  (docs/PROTOTYPE.md). When in doubt, treat it as copied and leave it out.
- **No proprietary material ever touches the repository**: disc images, executables, `asm/`,
  `assets/`, build output, dumps, the compiler or any SDK binary, SDK headers, links to
  toolchains. Not in a commit, not on a branch, not in a pull request. `tools/proprietary.py`
  (run by `tests/check_repository.py` and CI) checks this; never weaken it to get a file in.
- **Licence.** Everything is AGPL-3.0-or-later. Every new source file starts with
  `SPDX-License-Identifier: AGPL-3.0-or-later` (the check enforces it).
- **English** in everything that lands here.
- **Never delete what you did not create**, and leave other people's uncommitted work alone.
- **The branch is `master`.** Never rewrite its history and never force-push it.

## Commits

As in OpenRAC (CONTRIBUTING.md, "Commits"):

- Conventional Commits with a scope: `feat(us): ...`, `fix(tools): ...`, `docs: ...`,
  `build: ...`, `chore: ...`. The summary says what the change does or what is now true, in
  lower case, without a full stop.
- A prose body wrapped at 72 columns: what changed, why, and what you verified (the commands
  and what they printed).
- One logical change per commit, each leaving the tools and checks working.
- No `Co-authored-by:` trailers or other attribution lines for AI tools.
- Push and open pull requests only when asked.

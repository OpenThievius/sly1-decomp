# Contributing

Thanks for helping. The rules are in [AGENTS.md](AGENTS.md) (written for people and agents
alike) and [LEGAL.md](LEGAL.md). This guide follows
[OpenRAC's](https://github.com/OpenRAC/OpenRAC/blob/master/CONTRIBUTING.md), the sister project
of the same maintainers. The short version:

1. **Set up** your own disc, the Python tools and the compiler ([README](README.md#quick-start),
   [docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)).
2. **Pick something** from [docs/ROADMAP.md](docs/ROADMAP.md). While the project is being set
   up, the build, the file split and compiler qualification matter more than single functions.
3. **Check** with `python3 -m unittest discover -s tests` and `python3 tests/check_repository.py`.
4. **Open a pull request** against `master` from a branch of your fork, saying what you verified.

## Rules

- **Derive everything yourself.** Work from the retail executable of your own disc and public
  hardware documentation. Nothing from other decompilations or ports of this game, no
  third-party code, nothing from the May 2002 prototype ([docs/PROTOTYPE.md](docs/PROTOTYPE.md)),
  and never Sony's SDK source, samples or headers, or leaked or NDA material. The one exception
  is OpenRAC's own work, used openly and credited ([LEGAL.md](LEGAL.md#openrac)).
- **No proprietary material**: no game data, SDK files or toolchain files in the repository, an
  issue, a pull request or a chat, including files a tool generated from your own disc.
  Describe what you see in words. `tests/check_repository.py` must pass.
- **AGPL-3.0-or-later.** By contributing you license your work under it. New source files start
  with `SPDX-License-Identifier: AGPL-3.0-or-later`.
- **Keep docs short and plain.** Plain English, short sentences, lists and tables where they
  help. When you shorten a doc, keep every number, path, command, decision and link.

## Commits

[Conventional Commits](https://www.conventionalcommits.org/), as in OpenRAC:

```
type(scope): short summary

What changed and why, wrapped at 72 columns, and what you verified.
```

- **Types**: `feat`, `fix`, `docs`, `refactor`, `perf`, `test`, `build`, `ci`, `chore`
  (regenerated files, imports), `style` (formatting only), `revert`.
- **Scopes**: a part (`tools`, `config`, `docs`, `policy`, `progress`) or a version (`us`, `eu`).
  Narrower is fine (`us/splat`).
- **The summary** says what the change does or what is now true, in lower case, without a full
  stop.
- **The body** is prose: what changed, why, and what you ran to verify it, with what it printed.
- **One logical change per commit**, each leaving the tools and checks working. Large
  regenerated output goes in its own commit.
- **No attribution lines**: no `Co-authored-by:` or other trailers for AI tools.

```
fix(tools): read the Mode 1 sectors of a raw CD image
feat(us): split SCUS_971.98 by source file
feat(us): func_0012A4C8 exact match
```

## Pull requests

- One topic per pull request, titled like a commit summary.
- Say what you verified and how: the commands and their results.
- Never include generated or disc-derived files.

## Working with other people

Nobody finishes a decompilation alone. Disagree kindly, argue about the code and not the
person, share what you find, and be patient with people's work: a pull request is someone's
evening.

## Working with an AI assistant

Welcome, and the rules above apply the same way. You are responsible for what you contribute,
however it was written: you have to be able to explain it. On top of them, an assistant:

- pushes, opens pull requests or publishes only when asked;
- reports what it checked as it is, failures included;
- follows [AGENTS.md](AGENTS.md).

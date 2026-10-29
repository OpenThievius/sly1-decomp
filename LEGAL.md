# Legal scope of this project

This repository is a **matching decompilation** of *Sly Cooper and the
Thievius Raccoonus* (PS2): the boot executable of the NTSC-U disc
(`SCUS_971.98`), and later the PAL disc's (`SCES_509.17`), rebuilt from source
until every byte equals retail.

## The license

Everything in this repository is licensed under the **GNU Affero General
Public License, version 3 or (at your option) any later version**
([LICENSE](LICENSE)). That covers the tools, tests, build files,
configuration tables, headers, documentation and the decompiled source in
`src/`. Each source file starts with `SPDX-License-Identifier: AGPL-3.0-or-later`.

The license covers what the contributors wrote. It cannot cover the game: the
decompiled source reconstructs the behaviour of a program whose copyright
belongs to Sony Interactive Entertainment. The contributors license their own
work in it under the AGPL; nothing here grants any right to the original
game, its code or its assets.

The tables in `config/` record facts about the retail executables: addresses,
sizes, section layout, checksums, and the names we gave things. They contain
no game code.

## Our own work only

Everything here is written by this project's contributors and derived from
the retail executable of a disc they own:

- **No third-party code.** Nothing is copied from other projects, including
  other decompilations or ports of this game: not their code, symbol maps,
  file splits, names or notes. Library code in the retail executable (Sony's
  libraries, the compiler's runtime) is decompiled from retail like the rest.
- **Nothing from the prototype.** The May 2002 preview disc is recognised by
  the tools and never used as a source: no code, data, names, types or file
  lists come from it ([docs/PROTOTYPE.md](docs/PROTOTYPE.md)).
- The free tools the project runs (splat, spimdisasm, wibo and others) are
  installed by each contributor and are not part of the repository.

## OpenRAC

[OpenRAC](https://github.com/OpenRAC/OpenRAC), the Ratchet & Clank
decompilation and port, is the sister project of the same maintainers, and the
one exception to "our own work only". Its own work (tools, build code,
checks, documentation, policies, research on the PS2 toolchain) may be used
here, openly credited: in the commit that brings it, and in
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).

- What OpenRAC's maintainers wrote is used here under the AGPL-3.0-or-later,
  by their decision.
- What other OpenRAC contributors wrote keeps its GPL-3.0-or-later notice;
  section 13 of both licenses lets it be combined with this AGPL code.
- It does not cover what OpenRAC itself took from other projects (its own
  third-party notices list that), nor any Ratchet & Clank game code.

## No proprietary material, ever

The repository never contains, not even briefly on a branch:

- disc images, the boot executables or any other file from a disc;
- what is generated from them: `asm/`, `assets/`, `build/`, dumps;
- the compiler, assembler, linker or any other SDK binary;
- Sony SDK source, samples or headers, or anything recreated from them;
- leaked or NDA material of any kind.

`tests/check_repository.py` (run by CI on every push and pull request) runs
`tools/proprietary.py`, which rejects binaries, disc images, archives, game
data folders, toolchain files and links, Sony SDK headers and banners, pasted
disassembly and dumps of retail data. Do not post game data anywhere else
either: not in an issue, a pull request or a chat, including files a tool
generated from your own disc. Describe what you see in words.

## What you may use while working

- the retail executables of a disc you own (disassembly, Ghidra, m2c,
  emulators);
- public hardware documentation;
- free tools, used as their licenses allow.

If a function looks like SDK sample code, decode it from the assembly.

## Practical implication

Nothing here builds a game for anyone who does not already own the disc and
supply it locally. Cloning gets you tools and, as the work goes on, source
code: never assets, never the retail executables.

*Sly Cooper* is a trademark of Sony Interactive Entertainment. This is an
unofficial fan project, not affiliated with or endorsed by Sucker Punch
Productions or Sony Interactive Entertainment.

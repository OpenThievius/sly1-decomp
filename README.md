<img align="right" width="108" alt="OpenThievius icon" src="branding/openthievius.png">

# Sly Cooper and the Thievius Raccoonus (PS2) Decompilation

[![OpenThievius](https://img.shields.io/badge/Project-OpenThievius-2a6db5?logo=github&logoColor=white)](https://github.com/OpenThievius/OpenThievius)
[![Discord](https://img.shields.io/badge/Discord-Join%20Community-5865F2?logo=discord&logoColor=white)](https://discord.gg/58HZCCvxHh)
[![Progress report](https://github.com/OpenThievius/sly1-decomp/actions/workflows/progress.yml/badge.svg)](https://github.com/OpenThievius/sly1-decomp/actions/workflows/progress.yml)
[![Code](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Code&measure=matched_code_percent)](https://bytematch.dev/OpenThievius/sly1-decomp)
[![Functions](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Functions&measure=matched_functions)](https://bytematch.dev/OpenThievius/sly1-decomp)

A work-in-progress **matching decompilation** of *Sly Cooper and the Thievius Raccoonus* (Sucker Punch Productions, 2002) for the PlayStation 2 (`SCUS_971.98`, NTSC-U v1.00), part of **[OpenThievius](https://github.com/OpenThievius/OpenThievius)**.

The goal is C++ source that, built with the original compiler, gives back a byte-identical copy of the retail executable. The matched code is then cleaned up into readable code with real types and names, and the matching build stays on as the regression test.

> [!NOTE]
> This repository contains **no game assets, retail executables or disassembly**. To build anything you need your own copy of the game. Please read [`LEGAL.md`](LEGAL.md) before contributing.

---

## Progress

Progress is tracked live on **[bytematch.dev/OpenThievius/sly1-decomp](https://bytematch.dev/OpenThievius/sly1-decomp)**.

<!-- progress:begin (tools/progress.py) -->
| Version | Region | Target | Code | Functions | In the committed report |
|---|---|---|---|---|---|
| v1.00 | NTSC-U (North America) | `SCUS_971.98` | [![Code](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Code&measure=matched_code_percent&version=SCUS_971.98)](https://bytematch.dev/OpenThievius/sly1-decomp/SCUS_971.98) | [![Functions](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Functions&measure=matched_functions&version=SCUS_971.98)](https://bytematch.dev/OpenThievius/sly1-decomp/SCUS_971.98) | 4,236 of 4,770 functions, 76.40% of code (3,354 exact C, 882 original assembly) |
| v1.00 | PAL (Europe; En, Fr, De, Es, It) | `SCES_509.17` | [![Code](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Code&measure=matched_code_percent&version=SCES_509.17)](https://bytematch.dev/OpenThievius/sly1-decomp/SCES_509.17) | [![Functions](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Functions&measure=matched_functions&version=SCES_509.17)](https://bytematch.dev/OpenThievius/sly1-decomp/SCES_509.17) | 4,219 of 4,795 functions, 75.40% of code (3,345 exact C, 874 original assembly) |

A US function counts when the build links its C and still prints `MATCH`; a PAL function when that same C also builds PAL's bytes at its counterpart (`tools/version_check.py`). Original assembly (hand-written code and the linker's leftovers, `docs/ASM_CLASSIFICATION.md`) counts as finished too and is shown apart from the exact C.
<!-- progress:end -->

NTSC-U is the primary version. PAL (*Sly Raccoon*) shares its C and builds byte for byte from its own assembly; [`docs/VERSIONS.md`](docs/VERSIONS.md) compares the two. The May 2002 E3 prototype is recognised by the tools and nothing is taken from it ([`docs/PROTOTYPE.md`](docs/PROTOTYPE.md)).

Every function links at its retail address. Functions not yet decompiled are built from disassembly, so the full executable always links and equals retail. The game is C++ built with SN Systems' GCC 2.95.3 ([`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md)), and its data lives on the disc outside the file system, with no code of its own ([`docs/DISC.md`](docs/DISC.md)).

---

## Quick start

### Prerequisites

- Python 3.9 or newer, and git.
- GNU binutils for mips (`brew install mips-linux-gnu-binutils`, or your distribution's `binutils-mips-linux-gnu`).
- [wibo](https://github.com/decompals/wibo) or Wine, to run the Windows compiler.
- Your own disc image: NTSC-U `SCUS-97198`, and PAL `SCES-50917` if you have it.

### Setup and build

1. **Clone the repository:**
   ```sh
   git clone https://github.com/OpenThievius/sly1-decomp.git
   cd sly1-decomp
   ```

2. **Provide your disc:** put the image(s) in `baserom/` (any name; an `.iso`, or the `.img` of a raw CD dump), or pass their folder. It prints `ok: us baserom/us/SCUS_971.98 ...` for each version it recognises.
   ```sh
   python3 tools/setup.py            # or: python3 tools/setup.py ~/path/to/discs
   ```

3. **Install the Python tools and split the executables:**
   ```sh
   python3 -m venv venv && venv/bin/pip install -r tools/requirements.txt
   venv/bin/python tools/setup_asm.py --version us
   venv/bin/python tools/setup_asm.py --version eu
   ```

4. **Fetch the compiler:** clone the public toolchain mirror outside the repository and link its compiler, and wibo, into the checkout (both links are gitignored):
   ```sh
   git clone https://github.com/AngheloAlf/sce_ps2_sdk_24 ~/toolchains/sn-prodg-24
   ln -s ~/toolchains/sn-prodg-24/local/sce/ee/gcc toolchain
   ln -s /path/to/wibo wibo
   python3 tools/toolchain.py        # finds both and compiles a test unit
   ```

5. **Build and verify:**
   ```sh
   python3 tools/build.py                 # MATCH: build/us/SCUS_971.98 sha1 57dc305d... with N functions from C
   python3 tools/build.py --version eu    # MATCH: build/eu/SCES_509.17 sha1 f23240fc...
   ```

For more detail:
- [`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md): the compiler, assembler and flags, and how each was measured.
- [`docs/AGENT_WORKFLOW.md`](docs/AGENT_WORKFLOW.md): the step-by-step matching guide, for people and AI agents.
- [`docs/ROADMAP.md`](docs/ROADMAP.md): what is done and what comes next.
- [`AGENTS.md`](AGENTS.md): the repository layout and every tool's command.

---

## Contributing

Contributions are warmly welcome, whether you want to match functions, research the game's data formats or improve the tools and documentation.

- Read [`CONTRIBUTING.md`](CONTRIBUTING.md) and [`AGENTS.md`](AGENTS.md) first: they hold the rules, above all that everything is derived from the retail executable and nothing proprietary enters the repository.
- Reserve what you work on in the pinned **[Contributor coordination](https://github.com/OpenThievius/sly1-decomp/issues/1)** issue.
- Before a commit, run `python3 -m unittest discover -s tests` and `python3 tests/check_repository.py`.
- Join our **[Discord community](https://discord.gg/58HZCCvxHh)** to discuss progress, ask questions and collaborate.

---

## Credits

This decompilation is our own work, derived from the retail executable alone: no code, names, maps or splits are taken from other Sly projects or from the prototype. [`CREDITS.md`](CREDITS.md) has the details.

- **[OpenRAC](https://github.com/OpenRAC/OpenRAC)**, the sister project of the same maintainers: the repository layout, rules, commit convention, checks and CI, and its knowledge of Sony's EE compilers ([`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)).
- **Tooling:**
  - [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm) and [rabbitizer](https://github.com/Decompollaborate/rabbitizer): splitting and MIPS disassembly.
  - [wibo](https://github.com/decompals/wibo): running the Windows compiler on Linux and macOS.
  - [objdiff](https://github.com/encounter/objdiff): the report format, validated in CI.
  - [ByteMatch](https://bytematch.dev): progress tracking.
  - [AngheloAlf](https://github.com/AngheloAlf): the public PS2 toolchain mirror.

---

## License

- Everything in this repository is licensed under the [GNU Affero General Public License v3.0 or later](LICENSE), with the scope [`LEGAL.md`](LEGAL.md) explains.
- The repository holds no third-party code beyond what OpenRAC lends ([`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)) and no proprietary material: no game data, no SDK code or headers, no toolchain.
- *Sly Cooper* is a trademark of Sony Interactive Entertainment. The game was developed by Sucker Punch Productions. This is an unofficial fan project, not affiliated with or endorsed by either.

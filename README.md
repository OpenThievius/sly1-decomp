# Sly Cooper and the Thievius Raccoonus (PS2) Decompilation

A work-in-progress **matching decompilation** of *Sly Cooper and the Thievius Raccoonus* (Sucker Punch Productions, 2002) for the PlayStation 2, part of **[OpenThievius](https://github.com/OpenThievius/OpenThievius)**. The goal is C++ source that, built with the original compiler, gives back a byte-identical copy of the retail executable. The matched code is then cleaned up into readable code with real types and names, and the matching build stays on as the regression test.

> [!NOTE]
> This repository contains **no game assets, retail executables or disassembly**. To build anything you need your own copy of the game. Please read [`LEGAL.md`](LEGAL.md) before contributing.

## Status

- Both executables build **byte for byte** from their disassembly (`tools/build.py`), and the US
  build links every matched C function at its retail address and still prints `MATCH`.
- The compiler is identified and qualified: SN Systems' GCC 2.95.3 for the PS2, compiling C++
  ([docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)).
- `tools/check.py` compares one function with retail, on US or PAL; matching follows
  [docs/AGENT_WORKFLOW.md](docs/AGENT_WORKFLOW.md), coordinated in the pinned
  [Contributor coordination](https://github.com/OpenThievius/sly1-decomp/issues/1) issue.

## Progress

Tracked on **[ByteMatch](https://bytematch.dev/OpenThievius/sly1-decomp)**.

[![Code](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Code&measure=matched_code_percent)](https://bytematch.dev/OpenThievius/sly1-decomp)
[![Functions](https://bytematch.dev/OpenThievius/sly1-decomp.svg?mode=shield&label=Functions&measure=matched_functions)](https://bytematch.dev/OpenThievius/sly1-decomp)

<!-- progress:begin (tools/progress.py) -->
| Version | Functions | Code |
| --- | ---: | ---: |
| NTSC-U `SCUS_971.98` | 128 of 4,766 | 6,160 of 1,112,520 bytes (0.55%) |
| PAL `SCES_509.17` | 128 of 4,791 | 6,160 of 1,117,772 bytes (0.55%) |

A US function counts when the build links its C and still prints `MATCH`; a PAL function when that same C also builds PAL's bytes at its counterpart (`tools/version_check.py`).
<!-- progress:end -->

## Versions

| Key | Version | Executable | Size | SHA-1 | Role |
|---|---|---|---:|---|---|
| `us` | NTSC-U v1.00 | `SCUS_971.98` | 1,712,328 | `57dc305db57932ad3f1122966cdb695d2e62a47a` | **primary target** |
| `eu` | PAL v1.00 (*Sly Raccoon*; En, Fr, De, Es, It) | `SCES_509.17` | 1,751,112 | `f23240fc4a3efd463a5b3617b9250da4d5fe842c` | second target |
| `may19` | E3 build 5-19D, 2002-05-19 (prototype) | `SCUS_971.98` | 12,523,740 | `3e5fdf0c479a0f548e90b05d7fc558cd8e94f5c1` | recognised only: nothing is taken from it |

Disc checksums are in [`config/versions.json`](config/versions.json); [docs/VERSIONS.md](docs/VERSIONS.md) compares the two retail executables, and [docs/PROTOTYPE.md](docs/PROTOTYPE.md) says why nothing is taken from the prototype.

## Quick start

You need Python 3.9 or newer, git, GNU binutils for mips, [wibo](https://github.com/decompals/wibo) (or Wine) and the compiler ([docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)).

1. **Clone:**
   ```sh
   git clone https://github.com/OpenThievius/sly1-decomp.git
   cd sly1-decomp
   ```
2. **Your disc:** put your image(s) in `baserom/` (any file name; `.iso`, or the `.img` of a raw CD dump), or pass their folder:
   ```sh
   python3 tools/setup.py            # or: python3 tools/setup.py ~/path/to/discs
   ```
   It prints `ok: us baserom/us/SCUS_971.98 ...` for each version it recognises.
3. **The Python tools:**
   ```sh
   python3 -m venv venv && venv/bin/pip install -r tools/requirements.txt
   ```
4. **The disassembly:**
   ```sh
   venv/bin/python tools/setup_asm.py --version us
   ```
   It writes `asm/us/` (gitignored) and the linker script under `build/us/`.
5. **The compiler and binutils:** link the toolchain mirror's `local/sce/ee/gcc` as `./toolchain`
   and wibo as `./wibo`, and install GNU binutils for mips ([docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)):
   ```sh
   python3 tools/toolchain.py
   ```
6. **Build:**
   ```sh
   python3 tools/build.py                 # MATCH: build/us/SCUS_971.98 sha1 57dc305d... with N functions from C
   python3 tools/build.py --version eu    # MATCH: build/eu/SCES_509.17 sha1 f23240fc...
   ```
   Then `docs/AGENT_WORKFLOW.md` for matching.

## Tools

| Tool | Purpose |
|---|---|
| `tools/setup.py` | Recognises your disc images and puts each version's boot executable in `baserom/<version>/` |
| `tools/setup_asm.py` | Runs splat on `config/splat/<version>.yaml` and writes `asm/<version>/` |
| `tools/build.py` | The full build of a version, with the C of `src/` linked into US: `MATCH` |
| `tools/check.py` | Compiles one file and compares one function with retail, on US or PAL |
| `tools/todo.py` | The functions still to match, with their size, source file and tags |
| `tools/version_check.py` | Every C function at its PAL counterpart (`config/eu/c_status.tsv`) |
| `tools/progress.py` | The ByteMatch reports (`progress/<version>/report.json`) and the table above |
| `tools/inventory.py` | Every function of each version, and PAL's pairing with US |
| `tools/compile.py`, `tools/c_layout.py` | How C is compiled, and placed in the build |
| `tools/toolchain.py` | Finds the compiler and its runner and compiles a test unit |
| `tools/proprietary.py` | Scans what git would commit for game data and proprietary material (shared with OpenThievius) |
| `tests/check_repository.py` | The pre-commit check: `proprietary.py`, licence headers (CI runs it) |

## Contributing

Read [`AGENTS.md`](AGENTS.md) and [`CONTRIBUTING.md`](CONTRIBUTING.md) first; they hold the rules. Before a commit:

```sh
python3 -m unittest discover -s tests
python3 tests/check_repository.py
```

## Credits and license

This decompilation is our own work, derived from the retail executable alone: no code, names, maps or splits are taken from other Sly projects or from the prototype. The repository is built on [OpenRAC](https://github.com/OpenRAC/OpenRAC), the sister project of the same maintainers; [CREDITS.md](CREDITS.md) says what came from it and names the free tools it runs.

- Everything in this repository is licensed under the [GNU Affero General Public License v3.0 or later](LICENSE), with the scope [LEGAL.md](LEGAL.md) explains.
- The repository holds no third-party code beyond what OpenRAC lends ([THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)) and no proprietary material: no game data, no SDK code or headers, no toolchain.
- *Sly Cooper* is a trademark of Sony Interactive Entertainment. The game was developed by Sucker Punch Productions. This is an unofficial fan project, not affiliated with or endorsed by either.

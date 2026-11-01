# Third-party notices

The decompilation holds **no third-party code** and takes none in: everything is written by its
contributors ([LEGAL.md](LEGAL.md#our-own-work-only)). Library code in the retail executable is
decompiled from retail like the rest.

## From OpenRAC

What comes from [OpenRAC](https://github.com/OpenRAC) (LEGAL.md, "OpenRAC"): written by its
maintainers, used here under the AGPL-3.0-or-later.

| Here | Adapted from | What changed |
|---|---|---|
| `AGENTS.md`, `LEGAL.md`, `README.md` | rac3-decomp's files of the same names | rewritten for this game, its versions and its stricter sourcing rules |
| `CONTRIBUTING.md` | OpenRAC's and rac3-decomp's `CONTRIBUTING.md` | the commit and pull request conventions kept; the rules rewritten for this game |
| `tests/check_repository.py` | rac3-decomp's `tests/check_repository.py` (its game data check) | written anew around `tools/proprietary.py`, which adds the SDK, banner and dump checks |
| `.github/workflows/checks.yml` | rac3-decomp's `checks.yml` | this repository's checks |
| `docs/TOOLCHAIN.md` | OpenRAC's `docs/decomp/TOOLCHAINS.md` and `toolchains/README.md` | what is known of Sony's 2.9-ee-991111 builds and where the mirror is, for this game |
| `src/versions/`, `tools/version_src.py`, docs/VERSIONS.md ("PAL's own C") | the layout of rac1-decomp's version-specific C (its `docs/VERSIONS.md`) | the layout and the rule (built in the shared file's unit, with its flags) only; the tools written anew, no code copied |
| `.gitignore`, `baserom/README.md` | OpenRAC's and rac3-decomp's | this repository's paths |

## Tools

The Python packages in `tools/requirements.txt` (splat64, spimdisasm, rabbitizer, PyYAML) are
installed by each contributor and are not distributed with the repository. The compiler is
proprietary and never part of it ([docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)).

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
| `config/cflags.tsv` (a compiler per file), docs/TOOLCHAIN.md ("The libraries") | rac1-decomp's choice of Sony's 2.9-ee-991111 for its SDK objects (its `docs/reference/TOOLCHAIN.md`) | the choice only, measured anew on this game's library; no file, code or list of objects of theirs, and none of the GCC sources they build libgcc from |
| `docs/ASM_CLASSIFICATION.md`, `tools/classify_asm.py`, `config/us/original_asm.tsv` | the policy and evidence described in rac1-decomp's `docs/reference/ASM_CLASSIFICATION.md` (original assembly and linker leftovers counted as finished, apart from the exact C matches; kernel instructions, hand-placed code, and the source names in the SDK's `libc.a` as evidence) | the rules, the tool and the table written anew from this game's bytes; no file or code of rac1-decomp's was copied |
| `tools/nonmatching.py`, `nonmatching/README.md`, the report's `fuzzy_match_percent` | the near-miss staging of rac1-decomp (its `docs/reference/NONMATCHING.md`: a best attempt per function with a verdict, a generated index, the byte share as fuzzy progress) | the scheme only; the tool written anew, with verdicts kept in each file so CI needs no compiler |
| `tools/permute.py` | rac1-decomp's `tools/permute.py` (its `docs/agents/PERMUTER.md`: every order of the lines marked `/*P*/`) | the idea and the marker only; written anew for this build, with `--auto` |
| `.gitignore`, `baserom/README.md` | OpenRAC's and rac3-decomp's | this repository's paths |

## Tools

decomp-permuter (MIT) is fetched by each contributor into `tools/ext/` and is never part of the
repository; `tools/permuter_setup.py` and `tools/permuter_compile.py`, which connect it to this
build, are ours, after OpenRAC's setup (rac1-decomp, `docs/agents/PERMUTER.md`).

The Python packages in `tools/requirements.txt` (splat64, spimdisasm, rabbitizer, PyYAML) are
installed by each contributor and are not distributed with the repository. The compiler is
proprietary and never part of it ([docs/TOOLCHAIN.md](docs/TOOLCHAIN.md)).

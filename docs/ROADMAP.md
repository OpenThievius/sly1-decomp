# Roadmap

What is set up, what comes next, and what is still to decide. Everything is
derived by this project from the retail executable: no code, names, maps or
splits are taken from other projects or from the prototype
([PROTOTYPE.md](PROTOTYPE.md)).

## Done

- [x] Disc recognition and executable extraction (`tools/setup.py`, `tools/disc.py`)
- [x] Both executables split by splat and built byte for byte from assembly (`tools/build.py`)
- [x] Every function of each version, and PAL's pairing with US (`tools/inventory.py`)
- [x] The compiler qualified: SN GCC 2.95.3, C++, `-O2 -G0 -fno-exceptions` ([TOOLCHAIN.md](TOOLCHAIN.md))
- [x] The per-function checker, on US and on PAL (`tools/check.py`)
- [x] C linked into the US build at each function's address (`tools/c_layout.py`)
- [x] The ByteMatch reports and their CI (`tools/progress.py`, `.github/workflows/progress.yml`):
  units for game code, libraries and data sections, each in its category (`config/<version>/layout.tsv`)
- [x] The coordination issue and the matching workflow ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md))
- [x] Repository checks and CI that need no game data, with a scan for proprietary material

## Next

1. **Matching**, function by function ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md)).
2. **Data from C.** A C file's `.rodata` literals (float constants, strings) are linked now: the
   code takes retail's address for them and retail's bytes stay in the image (tools/rodata.py),
   which opens the functions tagged `rodata`. A C `switch` is linked too: its jump table goes with the
   object's `.rodata`, the code takes retail's table address, and `tools/check.py` compares the
   table's case-label addresses with retail's (functions tagged `jtbl`). `.data` still comes from
   the disassembly.
3. **Original assembly.** The game-code functions that were not made from C (VU0 and multimedia
   instructions, the disassembler's own mark) and the linker's leftovers are listed in
   `config/us/original_asm.tsv` and counted as finished, apart from the exact C matches
   (docs/ASM_CLASSIFICATION.md). Sony's libraries are matched in C with Sony's own compiler
   instead (docs/TOOLCHAIN.md). Kernel and cache instructions, `max.s`/`min.s`/`sqrt.s` and the
   fragments that contain a jump are for a person to classify (#18).
4. **File boundaries, found in retail.** Where one source file ends and the next begins, from
   retail's own code: which functions share static data, how `.rodata` and `.data` group, and
   compiler-generated functions (static initialisers) that end a file. The 16 KiB windows of
   `src/main/` then give way to real files, with names that are ours.
5. **PAL's own code.** Its version-specific functions (`config/eu/map.tsv` rows with no
   counterpart, `differs` rows of `config/eu/c_status.tsv`) as version-specific C, in
   `src/versions/eu/` ([VERSIONS.md](VERSIONS.md#pals-own-c)).
6. **Names and types.** Ours, from what the code does, as the C is cleaned up.
7. **The disc's data.** Its loader and index, then each format from the code that reads it
   ([DISC.md](DISC.md)); OpenThievius's extractor is written from that.

## Open decisions

- **The assembly macros.** splat writes its own macro files into `include/`
  (gitignored); the build will need macros written by this project instead.

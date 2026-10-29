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
- [x] The ByteMatch reports and their CI (`tools/progress.py`, `.github/workflows/progress.yml`)
- [x] The coordination issue and the matching workflow ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md))
- [x] Repository checks and CI that need no game data, with a scan for proprietary material

## Next

1. **Matching**, function by function ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md)).
2. **Data from C.** Today a C file may hold only code: `.rodata` (float literals, jump tables,
   strings) and `.data` still come from the disassembly. Placing each file's data where retail
   has it opens the functions tagged `rodata` and `jtbl`.
3. **File boundaries, found in retail.** Where one source file ends and the next begins, from
   retail's own code: which functions share static data, how `.rodata` and `.data` group, and
   compiler-generated functions (static initialisers) that end a file. The 16 KiB windows of
   `src/main/` then give way to real files, with names that are ours.
4. **PAL's own code.** Its version-specific functions (`config/eu/map.tsv` rows with no
   counterpart, `differs` rows of `config/eu/c_status.tsv`) as version-specific C.
5. **Names and types.** Ours, from what the code does, as the C is cleaned up.

## Open decisions

- **The assembly macros.** splat writes its own macro files into `include/`
  (gitignored); the build will need macros written by this project instead.

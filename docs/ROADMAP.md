# Roadmap

What is set up, what comes next, and what is still to decide. Everything is
derived by this project from the retail executable: no code, names, maps or
splits are taken from other projects or from the prototype
([PROTOTYPE.md](PROTOTYPE.md)).

## Done

- [x] Disc recognition and executable extraction for all three versions (`tools/setup.py`, `tools/disc.py`)
- [x] A first splat split of the US executable, one unit per section (`config/splat/us.yaml`)
- [x] The compiler identified (2.9-ee-991111b, C++) and its Windows build running under wibo (`tools/toolchain.py`, [TOOLCHAIN.md](TOOLCHAIN.md))
- [x] Repository checks and CI that need no game data, with a scan for proprietary material (`tools/proprietary.py`, `tests/`)

## Next

1. **A byte-identical build from assembly.** A linker script for the whole
   image (the `.DVP.overlay` sections, `.reginfo`, `.stack` and the overlay
   tables included), assembled and linked to `SCUS_971.98`, checked by SHA-1:
   `MATCH`. Everything after rests on this.
2. **File boundaries, found in retail.** Where one source file ends and the
   next begins, from retail's own code: alignment padding between functions,
   which functions call or share static data with which, how `.rodata` and
   `.data` group, and compiler-generated functions (static initialisers) that
   end a file. Then split by file (`src/<name>.cpp` with `INCLUDE_ASM`
   markers), so each file gets its own flags. File names are ours.
3. **Compiler qualification.** Small retail functions written in C++ and
   compiled with `cc1plus.exe` ([TOOLCHAIN.md](TOOLCHAIN.md#still-to-qualify)),
   then the per-file flags table.
4. **The checker.** `tools/check.py FILE.cpp func`: compiles one function with
   its file's flags and diffs it against retail.
5. **Progress.** A report per version, the README table, and objdiff units.
6. **PAL.** Its own split, with shared source checked against both versions.

## Open decisions

- **The build system.** A Python `tools/build.py` like OpenRAC's rac3-decomp,
  or a `configure.py` that writes a ninja file.
- **The assembly macros.** splat writes its own macro files into `include/`
  (gitignored); the build will need macros written by this project instead.

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
- [x] **Matching** (2026-11-13): every function of both versions. US 4,807 of 4,807 (4,498
  exact C, 311 original assembly), PAL 4,831 of 4,831 (4,520 exact C, 311 original assembly), no
  C with inline assembly left to match. `nonmatching/` holds no near misses.
- [x] **Original assembly**: the 311 functions not made from C, and the linker's leftovers,
  classified in `config/us/original_asm.tsv` and `config/eu/original_asm.tsv`
  ([ASM_CLASSIFICATION.md](ASM_CLASSIFICATION.md)).
- [x] **File boundaries**: every byte of code, 0x100000 to 0x211E0C, in one of 195 proved
  source files named by role (`config/us/files.tsv`); where an edge is not proved by retail, the
  file's head says so and gives the range it could lie in.
- [x] **PAL's own code**: every function only PAL has defined under `src/versions/eu/`, and every
  C function checked at its PAL counterpart (`tools/version_check.py`: 4,520 match, 24 have none).
- [x] **Declarations** (2026-11-14, #148): declarations agree with their functions' C
  definitions in parameters and return type (`tools/params.py`, `tools/decls.py`), so the source
  links with a normal linker; what is left, and the places a 64-bit port must change, are listed
  in #148.

## Next

What is still open, on 2026-11-14 (the README's table and `tools/progress.py` have the counts):

1. **Data from C.** US: 99.97% of data counts (430,919 of 431,059 bytes). PAL: its data is checked at its counterparts
   (`tools/version_check.py`, `tools/data_check.py`, `config/eu/c_data_status.tsv`): 231 of the
   273 globals match (85.8% of PAL's data counts), 25 are absent (`.bss`, no bytes in the file) and 17 differ, each for a cause
   docs/VERSIONS.md lists (a PAL function with no C, a global C++ cannot write, tables PAL grew past
   US's labels, included labels, the hash tables of `global_tables.cpp`).
2. **Names and types.** Ours, from what the code does (docs/NAMING.md). Done: every C function has
   a readable name (the 151 left with their address names are the linker's leftovers of stripped
   functions, which have no role and keep them by rule); 6,243 symbols are named in
   `config/names/`, 1,125 globals among them since 2026-11-14; 1,639 fields named by role that
   day; the libraries' per-function views made into one type per object (the MPEG decoder, the
   IOP clients, the exception runtime, `include/mpeg_decoder.h`, `include/mpeg_bit_reader.h`).
   Left:
   - about 770 globals used in the source still named by address: float constants and vectors
     whose only role is their value, flags and buffers no reader explains, the per-class property
     lists (a name would only restate the class id), and the 108 globals only PAL has
     (`D_eu_XXXXXXXX`), which `tools/names.py` does not take yet;
   - 486 fields of `include/` and 303 of the sources' local types still named by offset, where
     the code shows no role, and PAL's per-function copies of local types (`src/versions/eu/`);
   - local view types named by role with an address suffix (`Bone_166690`), 97 in game code:
     views of a class kept for a stated reason or a type still to share;
   - two class headers by id, `c35.h` and `c52.h`, whose classes only forward their draw slot.
3. **The disc's data**, each format from the code that reads it ([DISC.md](DISC.md)). How the
   game finds its data is described, and a level's textures, objects, geometry, collision,
   animations and events, and PAL's data. Next are the fields not yet named and the sound
   banks' own format; OpenThievius's extractor is then written from these readers. Unchanged
   since 2026-11-04.

## Decided

- **The assembly macros** (2026-11-11). `include/macro.inc` is the project's own: the label
  macros the listings use (`glabel`, `endlabel`, `alabel`, `jlabel`, `dlabel`, `enddlabel`, and
  `nonmatching`, which emits nothing), for GNU as. splat's generated copies are off
  (`generate_asm_macros_files: False` in `config/splat/`). The toolchain's own 1999 assembler
  never reads them: `tools/asm_func.py` writes the macros out for the functions a whole file
  includes.

## Open decisions

None at present.

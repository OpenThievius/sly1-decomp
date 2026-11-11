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

Where each stands is in the README's table (`tools/progress.py`); in short, on 2026-11-11: US at
93.12% of code (4,759 of 4,807 functions) and 94.56% of data, PAL at 92.93% of code and 60.48% of data, 48 US
functions left, every one with a near miss in `nonmatching/`, the original assembly classified,
every byte of code in a proved source file, PAL's own game code all defined, and names and types
well under way. What is still open is the long tail of the matching, the readable names of the
functions left with their address names, and the disc's data.

1. **Matching**, function by function ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md)). On 2026-11-11,
   48 US functions are left (76,480 bytes; 657 were on 2026-11-07), each with a near miss in
   `nonmatching/` that records what still differs. 28 of them (30,676 bytes) are C with inline
   assembly (item 3): compiled C around a few VU0, MMI or system instructions, matched with
   shared helpers in `include/` (AGENTS.md). The other 20 are plain C (45,804 bytes: 16 in game
   code, 4 in the libraries). The largest, func_00109488 (`FillObjectPropertyTable`, 37 KB, 49%
   of what is left), is close but differs in code as well as registers: 9,338 instructions
   against retail's 9,348. Its header and docs/toolchain/long-block-constants.md record why: one
   global-alloc choice, which traces back to the schedule of a few long-lived constants in its
   one very long block; every uniform source form tried so far keeps that choice. Models of
   GCC's register allocation (`tools/globalalloc.py`) and of its first scheduling pass
   (`tools/sched1.py`) replay the compiler's choices from its dumps, to find such levers without
   compiling blind. The toolchain's own runtime (`libgcc`) is C, built by `cc1` in `.c`
   files under `src/lib/`, by Sony's Linux build of 2.9-ee-991111 (docs/TOOLCHAIN.md).
2. **Data from C.** A C file's `.rodata` literals (float constants, strings) are linked now: the
   code takes retail's address for them and retail's bytes stay in the image (tools/rodata.py),
   which opens the functions tagged `rodata`. A C `switch` is linked too: its jump table goes with the
   object's `.rodata`, the code takes retail's table address, and `tools/check.py` compares the
   table's case-label addresses with retail's (functions tagged `jtbl`). A global can be defined
   in C at its address, with its initial value: in `.data`, in `.rodata` as an `extern const`, or
   in `.bss` as a file's `static` (`-fdata-sections`, tools/c_layout.py). A global built at
   startup brings the compiler's static initialiser, which `config/us/generated.tsv` names. The
   reports count the bytes C defines as matched data (`config/us/c_data.tsv`). The rest of the
   data still comes from the disassembly: on 2026-11-11, 94.56% of US data is defined in C
   (23,461 bytes left). PAL links no C, so its data is checked at its counterparts as its
   functions are (`tools/version_check.py`, then `tools/data_check.py`, `config/eu/c_data_status.tsv`):
   a global counts for PAL when its bytes, with every pointer translated to PAL's addresses, equal
   PAL's at its PAL address. On 2026-11-11, 179 of the 240 globals match (280,987 bytes, 60.48% of
   PAL's data), 39 differ (PAL's own bytes, or pointers the translation cannot place) and 22 are
   absent (21 are `.bss`, which has no bytes in the file, and one has no PAL address).
3. **Original assembly.** The functions that were not made from C (system-call stubs, crt0,
   the toolchain's own `.S` routines, the libraries' multimedia routines, frameless VU0 leaves,
   code scheduled by hand) and the linker's leftovers, in game code and in Sony's libraries, are
   listed in `config/us/original_asm.tsv` and counted as finished, apart from the exact C matches
   (docs/ASM_CLASSIFICATION.md; #18): 311 functions on 2026-11-07, and still on 2026-11-11. An audit that day found that
   most of the 890 listed before were compiled C around a few instructions the compiler cannot
   emit, which the original developers wrote as small inline-assembly helpers, as retail's bare
   `sqrt.s` is: GCC's frame and scheduling around them, the same short sequences across hundreds
   of functions. Those are kind `inline` in the table, C still to match with shared helpers
   (include/fpu.h's `Fpu::Sqrt`; a VU0 header in progress), and no longer counted. The functions
   listed for `max.s` or `min.s` alone are plain C: g++'s `>?` and `<?` operators emit them, and
   func_001EAC68 is word for word one. PAL's own functions are
   classified in `config/eu/original_asm.tsv`.
4. **File boundaries, found in retail.** Where one source file ends and the next begins, from
   retail's own code: which functions share static data, how `.rodata` and `.data` group, and
   compiler-generated functions (static initialisers) that end a file. The 16 KiB windows of
   `src/main/` then give way to real files, with names that are ours. A file is proved by
   building it whole, as the original was, and linking each of its sections in one piece
   (`config/us/files.tsv`). The first, `src/main/value.cpp` (0x11AE78 to 0x11C128), is one.
   On 2026-11-07 every byte of code, 0x100000 to 0x211E0C, is in one of 167 proved files (74 of
   game code, 93 of the libraries, the math library and the toolchain's runtime; 168 since
   `src/main/file_14B6A8.cpp` was cut from its neighbour on 2026-11-10), and the data
   the 16 KiB windows defined is in its files too: in the proved files that read it, and in three
   files of data only that open .rodata (`class_descriptors.cpp`, `property_registry.cpp`,
   `global_tables.cpp`; the build proves their place, not where one ends and the next begins).
   The one window file left, `src/lib/001F8000.cpp`, holds the constructor list the linker
   builds. Many proved files are one file between two exact edges that could be several; each
   commit says which. What is left is splitting those when evidence appears.
   A file whose range holds original assembly includes those functions at their place
   (`INCLUDE_ASM`, include/asm_func.h, tools/asm_func.py): `src/main/file_1E5378.cpp`
   (0x1E5378 to 0x1E88D0, five of its 34 functions assembly) is the first. A file is named
   after its first address until what it was is known. A function of its range not matched yet
   is included the same way, so that a file is proved before all of its C is: it still counts
   as unmatched, and its C replaces the line when it matches. Retail's constructor list
   (`D_0027B130`) gives the exact end of every file with a static initialiser.
5. **PAL's own code.** Its version-specific functions (`config/eu/map.tsv` rows with no
   counterpart, `differs` rows of `config/eu/c_status.tsv`) as version-specific C, in
   `src/versions/eu/` ([VERSIONS.md](VERSIONS.md#pals-own-c)). On 2026-11-11, 50 PAL functions
   are left: 49 are the counterparts of functions US has left, and one is a library function
   only PAL has (func_0020A870, 68 bytes). Every game-code function only PAL has is defined.
   `tools/version_check.py` finds 4,469 C functions matching at their PAL counterparts, 24 with
   no counterpart, and one that differs (func_001366A0, its near miss in `nonmatching/eu/`).
   On 2026-11-07, 96 PAL functions
   are left (62 in game code, 34 in the libraries): two C functions differ at their counterparts
   (func_001316E8 and func_0016AB38), 11 game-code functions only PAL has are not defined yet
   (`tools/version_src.py todo`, which lists game code only), and 6 library functions only PAL
   has (964 bytes: 0x1F7738, 0x1F9538, 0x20A730, 0x20A7D0, 0x20A810, 0x20A870) are not defined
   either. The other 77 are the counterparts of the functions US has left (two of US's 79,
   func_001ABE70 and func_001DCEA0, have none). 11 have a near miss in `nonmatching/eu/`.
6. **Names and types.** Ours, from what the code does, as the C is cleaned up. Types come
   first, one per object, so that each name is chosen once: a header per class family of
   retail's class descriptors (`include/cNN.h`, `config/us/classes.tsv`), per kind of the other
   method tables (`config/us/tables.tsv`), per record several files share and per global several
   files read, with the common shapes (`shapes.h`) and the hub globals (`globals.h`); each header
   is named after its role once the code shows it (`box_collider.h`, `font.h`, `anim_curve.h`),
   and keeps its class id until then. Each
   field line ends with its offset, which a compiled assertion checks. They replace the views
   each matched function declared for itself; what is left is the script machine's value and
   its built-ins, and the views kept for a stated reason. The names come after: a family's
   types, fields and header are renamed in place, and its functions and globals get readable
   names as macros over their address names (`config/names/`, `include/names.h`,
   [NAMING.md](NAMING.md)), one table per source file. On 2026-11-11, about 563 functions still
   have only their address name, 6 views are left in game code and 29 in the libraries, and
   `tools/decls.py` flags 73 declarations, each kept because the definition's type breaks a
   caller's match (`TransformByMatrixWithW` is declared with three parameter orders, which may
   be several functions under one name). On 2026-11-07, 4,660 symbols have one;
   266 game functions do not yet (255 of them original assembly, mostly VU0 routines and
   linker leftovers, and 11 in C whose role the code does not show yet). Eight class headers
   keep their ids, and of the views matched functions declared for themselves (`Obj_XXXXXX`,
   `Sub_XXXXXX`, 2,018 of them in game code that morning) 18 are left in game code, each for a
   stated reason (a declaration retail's code needs, data only assembly reads) or a role still
   unclear; the rest are their shared types or local types named by role. The libraries' 176
   views (in 22 files) are not named yet: Sony's library code was outside this pass. The
   sources use the readable names everywhere, in definitions and declarations too
   (`tools/names.py apply`); the markers, comments and the tools' tables keep the address
   names, and `tools/symbols.py` maps one to the other.
7. **The disc's data**, each format from the code that reads it ([DISC.md](DISC.md)). How the
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

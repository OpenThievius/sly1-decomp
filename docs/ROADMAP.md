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

Where each stands is in the README's table (`tools/progress.py`); in short, on 2026-11-07: the
matching is in its long tail, the data mostly from C, the original assembly classified, every byte
of code in a proved source file, PAL close behind US, and names and types well under way.

1. **Matching**, function by function ([AGENT_WORKFLOW.md](AGENT_WORKFLOW.md)). On 2026-11-07,
   79 US functions are left (78,688 bytes: 51 in game code, 28 in the libraries), 36 of them with
   a near miss in `nonmatching/`. The largest, func_00109488 (`FillObjectPropertyTable`, 37 KB,
   47% of what is left), is close but differs in code as well as registers: 9,338 instructions
   against retail's 9,348, 2,990 of them exact. Its header records why: GCC keeps the value 4 in
   one callee-saved register where retail rebuilds it, and every source form found that frees
   that register also moves the CSE windows the rest of the function depends on. The toolchain's own runtime (`libgcc`) is C, built by `cc1` in `.c`
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
   data still comes from the disassembly.
3. **Original assembly.** The functions that were not made from C (VU0 and multimedia
   instructions, kernel and system instructions, code scheduled by hand, the disassembler's own
   mark, the toolchain's own `.S` routines) and the linker's leftovers, in game code and in Sony's
   libraries, are listed in `config/us/original_asm.tsv` and counted as finished, apart from the
   exact C matches (docs/ASM_CLASSIFICATION.md; #18). PAL's own functions are classified in
   `config/eu/original_asm.tsv`.
4. **File boundaries, found in retail.** Where one source file ends and the next begins, from
   retail's own code: which functions share static data, how `.rodata` and `.data` group, and
   compiler-generated functions (static initialisers) that end a file. The 16 KiB windows of
   `src/main/` then give way to real files, with names that are ours. A file is proved by
   building it whole, as the original was, and linking each of its sections in one piece
   (`config/us/files.tsv`). The first, `src/main/value.cpp` (0x11AE78 to 0x11C128), is one.
   On 2026-11-07 every byte of code, 0x100000 to 0x211E0C, is in one of 167 proved files (74 of
   game code, 93 of the libraries, the math library and the toolchain's runtime). Many are one
   file between two exact edges that could be several; each commit says which. What is left is
   splitting those when evidence appears, and placing the data the 16 KiB windows still define
   in their files: the 21 window files left (19 of game code, 2 of the libraries) hold no code,
   but 538 of the 767 globals defined in C (205,348 bytes of 422,765) are still in them.
   A file whose range holds original assembly includes those functions at their place
   (`INCLUDE_ASM`, include/asm_func.h, tools/asm_func.py): `src/main/file_1E5378.cpp`
   (0x1E5378 to 0x1E88D0, five of its 34 functions assembly) is the first. A file is named
   after its first address until what it was is known. A function of its range not matched yet
   is included the same way, so that a file is proved before all of its C is: it still counts
   as unmatched, and its C replaces the line when it matches. Retail's constructor list
   (`D_0027B130`) gives the exact end of every file with a static initialiser.
5. **PAL's own code.** Its version-specific functions (`config/eu/map.tsv` rows with no
   counterpart, `differs` rows of `config/eu/c_status.tsv`) as version-specific C, in
   `src/versions/eu/` ([VERSIONS.md](VERSIONS.md#pals-own-c)). On 2026-11-07, 96 PAL functions
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
   [NAMING.md](NAMING.md)), one table per source file. On 2026-11-07, 4,559 symbols have one;
   367 game functions do not yet (255 of them original assembly, mostly VU0 routines and
   linker leftovers, and 112 in C whose role the code does not show yet). Eight class headers
   keep their ids, and of the views matched functions declared for themselves (`Obj_XXXXXX`,
   `Sub_XXXXXX`, 2,018 of them in game code that morning) 18 are left in game code, each for a
   stated reason (a declaration retail's code needs, data only assembly reads) or a role still
   unclear; the rest are their shared types or local types named by role. The libraries' 221
   views (in 23 files) are not named yet: Sony's library code was outside this pass. Function
   bodies use the readable names; declarations and definitions still use the address names.
7. **The disc's data**, each format from the code that reads it ([DISC.md](DISC.md)). How the
   game finds its data is described, and a level's textures, objects, geometry, collision,
   animations and events, and PAL's data. Next are the fields not yet named and the sound
   banks' own format; OpenThievius's extractor is then written from these readers.

## Open decisions

- **The assembly macros.** splat writes its own macro files into `include/`
  (gitignored); the build will need macros written by this project instead.

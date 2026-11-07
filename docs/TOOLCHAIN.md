# The toolchain

The compiler, assembler and linker are proprietary. They are never committed,
and nothing in the repository is copied from them: you supply them, and the
tools find them outside the tree.

## What built the game

**SN Systems' GCC 2.95.3 for the PlayStation 2, compiling C++**, with
`-O2 -G0 -fno-exceptions -fno-rtti`, assembled by the EE GNU assembler of the same era.
Measured on 2026-10-28 against seven retail functions of `SCUS_971.98` (a push
onto a list, an add-if-absent loop, a pop, two calls passing a data address, a
float update, and a function with saved registers and a local object): every
one is EXACT with this compiler, on US and on PAL.

| Compiler (folder under `lib/gcc-lib/ee/`) | Banner | The seven functions |
|---|---|---|
| `2.95.3` (sce_ps2_sdk_24) | GCC 2.95.3 SN BUILD 1.14 | 7 EXACT: **the one config/cflags.tsv names** |
| `2.96-ee-001003-1` (sce_ps2_sdk_24) | GCC 2.95.3 SN BUILD v1.07 | 7 EXACT |
| `2.95.2` (sce_ps2_sdk_24) | GCC 2.95.2 SN BUILD v2.74 | 7 EXACT |
| `2.9-ee-991111` (sce_ps2_sdk_24) | GNU 2.9-ee-991111b/r4 (Sony's) | 2 EXACT: it makes tail calls (`j` in place of `jal`) and saves registers in 8 bytes, where retail saves 16 (`sq`) |

The three SN builds agree on everything measured so far; SN BUILD 1.14 is the
working choice because it is the one other 2002 games of the period were built
with. A function that tells the SN builds apart is worth recording here.

What else was measured:

- **The assembler matters.** cc1plus leaves macros and hazards to the
  assembler. Compiled C goes through `ee/bin/as.exe`, the assembler the
  compiler driver runs, with the options the driver gives it (`-G0 -O2`):
  - `move` becomes `daddu`, as in retail; a modern GNU as writes `or`;
  - no `nop` after `mtc1` before the register is used (`li.s`, `cvt.s.w`), as
    in retail. `bin/ee-as.exe`, the same release (`2.9-ee-991111b`) in
    another build, puts one there: measured on `func_00158108` and
    `func_001A7290`, EXACT with `ee/bin/as.exe` only;
  - a short loop gets nops before its backward branch, for the R5900's
    short-loop erratum, until five instructions precede the branch, even
    under `.set noreorder` (`bin/ee-as.exe` adds none). cc1 of both
    compilers already writes the four nops of a one-instruction delay loop
    (`for (i = 0x100000; i != -1; i--) {}`) itself. Retail's short loops,
    in Sony's libraries and in the game, show the same padding: the CD
    library's waits (func_002030C0, func_002033D8) match with nothing
    added. tools/check.py prints every zero word (`objdump
    -z`): without it a run of nops collapsed into `...` and the padding
    seemed missing from both columns.

  Then GNU objcopy rewrites the object's symbol table in the order modern ld
  wants, without touching code.
- **Sony's libraries had another assembler.** Sony's 2.9-ee-991111 never puts a
  volatile store in a delay slot: it marks it with `.set volatile` (kept as a
  comment) and leaves the `jal` after it to the assembler, in reorder mode.
  Ours fills that slot with a `nop`; retail's assembler moved the store into it,
  keeping a store macro's `lui $at` before the `jal` (func_0020FAF0,
  func_00210E00, func_00211348). tools/volatile_slots.py writes out what that
  assembler did for every file built with 2.9-ee-991111, after OpenRAC's
  rac1-decomp: every library function matched before stays EXACT with it.
- **`-fno-exceptions`.** Without it every file gets C++ exception frame records
  in `.data`; retail has only four such records, all in library code.
- **`-fno-rtti`.** Retail's game vtables (the method tables of its C++ classes)
  start with a zero entry, the slot RTTI would fill with the type's descriptor;
  with RTTI on, GCC 2.95 fills it and emits the descriptors, and a whole file
  with classes then differs. Every matched game file builds the same with or
  without it. The libraries' own vtables (the runtime's `bad_alloc` and its
  exception classes) do fill the slot; they have their own compiler and rows.
- **`-ffunction-sections`** is added to every file so that the build can put
  each function at its retail address (tools/c_layout.py). It changes no code.
- **`-mvu0-use-vf0-vf15`** gives the compiler the VU0 registers: the constraint
  `j` (class `VU_REGS`) then allocates $vf1..$vf15 to 128-bit values, and the
  compiler loads, stores and moves them itself (lqc2, sqc2, qmtc2, qmfc2).
  Without it the class is empty and an asm that names it does not compile. It
  also shifts the register choice of a few functions with no VU0 code, which is
  how it is pinned to every file: with it, the only two game functions that
  differed (ChooseBlinkObjectState, DrawAlignedText) each held a local standing
  in for a constant, and written plainly they match with the option and not
  without it. Retail's compiled C uses up to $vf13; vf13 to vf29 build the
  same, vf30 and vf31 change func_00138C00. See "The VU0 helpers".
- **The preprocessor** is the toolchain's `cpp.exe`, given the macros the
  compiler driver defines (tools/compile.py).

## The VU0 helpers

include/vu0.h holds the VU0 macro-mode sequences of the game's C (2026-11-07,
found on the pilot list of docs/ASM_CLASSIFICATION.md's `inline` functions).
What retail shows, and what the compiler does:

- **The compiler allocates the vector registers.** Retail's $vf numbers change
  from function to function and its lqc2/sqc2 are scheduled among the other
  loads and stores: they are the compiler's, for `j` operands
  (`-mvu0-use-vf0-vf15`, above). So a helper is one `__asm__` with `j`
  operands holding only the arithmetic; the loads and stores are C.
- **Operands are 128-bit scalars.** A struct or union as a `j` input stops the
  compiler (internal errors in expr.c and function.c), and a float is not
  allowed in the class at all. The helpers take and return `u128`
  (`mode(TI)`); a vector in memory is read and written through `Vu0::Q`. A
  float goes in with qmtc2 from a GPR ("r", the compiler adds the mfc1) and
  comes out with qmfc2 to a GPR ("=r", the compiler adds the mtc1).
- **Stack stores nothing reads are vector locals.** A local of a vector type
  (Vec02, Mat02) lives on the stack, so a result assigned to it is stored
  there even when every use takes the register. Retail stores every float it
  turns into a vector that way: the C put it in a local first. A helper's
  result that is used directly is never stored.
- **Not volatile.** Retail moves loads, stores and other asm across the
  sequences; a volatile helper is a barrier and changes the order.
- **Register sharing.** A result may take an input's register ("=j", not
  "=&j"). Which input it takes follows the order of the inputs: the
  allocator ties the result to the first input that dies there. MulX lists
  the scale first (retail's result takes the scale's register when the scale
  dies there and the vector's otherwise), and Rotate's result is tied to its
  vector ("0"), which is what retail's registers show in all six matched uses.
  A register a sequence only writes (Dot's 1.0 in vaddw.x) is a second output.
- **Matrices by reference.** Rotate reads its rows where they are: retail
  forms the matrix's address once (`addiu v0, s0, 0xD0`) and loads the rows
  through it, which a helper taking three row values does not give.

- **Two forms of the rotation.** Rotate ties its result to v; RotateUntied
  leaves it free, and the result then takes the register of the first input
  that dies, the rows before v. Retail has both: the rows of a product of two
  rotations (placed_object.cpp's MulRotation) and func_00125750's rotated
  position take a register Rotate's tie would not give, and Rotate untied
  breaks its other uses.
- **The cross product's operands.** Cross lists a before b; its result takes
  a's register when a dies there and b's when a lives on. A value loaded in
  another basic block cannot be tied (func_00157B88's spin, read before the
  branch that picks the arm, leaves the result to the arm).
- **vmove is the compiler's.** A vmove.xyzw is a copy the allocator makes
  (a value kept across a loop, func_001CAB10), not a helper.
- **Address registers of Q.** Q returns a reference, so `Q(v) = x` stores
  through an address register; when the local is also passed by address
  after a call, CSE keeps that address in a callee-saved register, where
  retail forms it again for the call. Vu0::Set stores from the frame instead
  (func_001BC828).
- **Floats in memory.** Retail loads a float in memory straight into the GPR
  for qmtc2 (`lw`, func_001CAB10, func_001A31A0, func_001D9AC8), where FromFloat
  on a float gives lwc1 and mfc1. A FromFloat that passes the float's bits (a
  union) gives the lw but moves func_001BC828's computed float from v0 to v1,
  so the header keeps the float form; those three are near misses.
- **A loop's alignment reaches later functions.** func_001579B0's C is
  retail's bytes, but in the whole file's build the assembler then adds its
  short-loop nops to func_00158F80's copy loop, 12 bytes on. The cause is the
  `.p2align 3` cc1plus emits before the first function's loop label (no
  padding there): without it, or without the function's `.align 3`, the later
  loop assembles as retail's. tools/check.py, which builds each function in
  its own section, does not see it; only the full build does.
- **The time argument.** In EABI a float argument goes in $f12 wherever it
  is in the list, but its place sets the order of evaluation: retail's mov.s
  before the pointer arguments of func_00125750's calls of the position and
  rotation methods (slots 34 and 35 of class 0x02) puts the time right after
  the object.

The sequences still without a helper, by how often retail has them (runs of
VU0 instructions in the `inline` functions): vsqrt/vwaitq/vaddq.x (208),
vdiv/vwaitq/vmulq.xyzw (140), vmulax.xyzw/vmaddx.xyzw (75), vmul.xy/vaddy.x
(31), the 4x4 forms with vmaddw. The two-term dot vmul.xy/vaddy.x has no
helper yet: group c's functions never use it alone (func_001A9868 joins it
to the square root). The assembler takes `vsqrt` (the disassembler prints it
as a `.word`).

## Getting the compiler

Its Windows build is in the public mirror of Sony's SDK 2.4 tools. Clone it
outside the repository:

```sh
git clone https://github.com/AngheloAlf/sce_ps2_sdk_24 ~/toolchains/sn-prodg-24
ln -s ~/toolchains/sn-prodg-24/local/sce/ee/gcc toolchain     # or export SLY1_TOOLCHAIN=...
```

OpenThievius's `tools/openthievius.py setup` makes the `toolchain` link for you.
If you have an OpenRAC checkout, its `toolchains/sn-prodg-24` is the same mirror.

The Windows tools run on macOS and Linux through
[wibo](https://github.com/decompals/wibo) (or Wine): a `wibo` link in the
repository root, `SLY1_RUNNER`, or `wibo` on `PATH`. Both links are gitignored,
and `tests/check_repository.py` rejects them if they are ever staged.

```sh
python3 tools/toolchain.py      # finds the tools and compiles a test unit
```

The disassembly is assembled and linked by GNU binutils for mips
(`mips-linux-gnu-as`, `-ld`, `-objcopy`, `-objdump`; `brew install
mips-linux-gnu-binutils`, or your distribution's `binutils-mips-linux-gnu`),
with `-march=r5900 -mabi=eabi`. splat writes n32 register names for it.

## Still to qualify

1. **SN build.** A function that compiles differently under the three SN
   builds would settle which one retail used.
2. **Per-file flags.** `-O2 -G0 -fno-exceptions -fno-rtti` is every file's default so
   far (config/cflags.tsv); a file that needs other options gets its own row,
   never a function.
3. **The libraries.** Sony's libraries and the compiler's runtime were linked
   from prebuilt archives and need other compilers or options. Their code is
   decompiled from retail like the rest: never from SDK source, headers or
   samples. Measured on 2026-10-29: the double-precision float support at
   0x1FB618–0x1FD6E0 makes tail calls and saves registers in 8 bytes, and
   five of its functions (`func_001FBDF8`, `func_001FCD20`, `func_001FCD78`,
   `func_001FD308`, `func_001FD548`) are EXACT with Sony's `2.9-ee-991111`,
   none with the SN builds.

   **The whole library is Sony's 2.9-ee-991111** (measured on 2026-11-01).
   Every one of the 340 library functions that saves a register saves it
   with `sd`, none with `sq`; 52 of the 619 library functions end in a tail
   jump to a function, against 2 of the 4,151 in game code; and 49 of the 51
   library functions matched with 2.95.3 are EXACT with 2.9-ee-991111 as
   well (the other two sit among `sd`-saving functions and were rewritten).
   config/cflags.tsv names 2.9-ee-991111 in the third column of every
   `src/lib` file's row, and tools/compile.py runs that release's
   `cc1plus.exe`. This is how OpenRAC builds its SDK objects (rac1-decomp,
   `docs/reference/TOOLCHAIN.md`: Sony's 2.9-ee for the `ee29` objects).
   Unlike OpenRAC, which builds libgcc from GCC's own sources, nothing here
   comes from GCC's sources: the runtime's functions (the double-precision
   float support among them) are decompiled from retail like the rest
   (LEGAL.md).

   **The C++ runtime (once src/lib/001FC000.cpp, now its whole files) was built with exceptions on**
   (measured on 2026-11-02), 2.9-ee-991111's default. Its throw and
   exception-specification functions (func_001FEC10, func_001FEE48, and
   func_001FEDC8, which splat joins to func_001FEC10) match only so, and so
   does func_001FD920: with exceptions on the compiler makes no tail calls,
   and a call to a function that never returns keeps retail's frame and
   `jal`. All 53 functions matched in that file stay EXACT without
   `-fno-exceptions`, which config/cflags.tsv no longer gives it. The object
   then carries frame (unwind) tables in `.data` (1,668 bytes) that no code
   refers to; retail's are in the disassembly's `.data`, and
   tools/c_layout.py takes them out of the object (drop_frame_tables). The
   throw functions name the runtime's helpers the compiler calls
   (`__eh_alloc`, `__cp_push_exception`, `__throw`, `__start_cp_handler`,
   `__uncatch_exception`, `__cp_pop_exception`, `terminate__Fv`) and their
   classes' vtables and destructors in config/us/libcalls.tsv; the file
   starts with `#pragma interface`, so the compiler refers to those vtables
   by name rather than writing its own. All four match.

   **The math library is another build** (measured on 2026-11-01). Its range,
   0x204F68-0x208F90 (26 functions unmatched), puts two `nop`s before every
   `div.s` that uses a value computed just before, and sets up its frame
   before the body. None of the toolchain's compilers (2.95.3, 2.96-ee-001003-1,
   2.95.2, 2.9-ee-991111) with any of its assemblers (`ee/bin/as.exe`,
   `bin/ee-as.exe`, `ee/bin/ps2eeas.exe`) gives that, whatever the scheduling
   flags. Sony's own build `2.9-ee-991111-01` does: its compiler writes
   `nop; nop; div.s` itself. It comes in the archive OpenRAC uses for its
   DTL-S13010 assembler (decompme/compilers `ee-gcc2.9-991111-01-dtls13010.tar.gz`,
   SHA-256 `3ab52a7ea962100f2a7df3e04d3e7a758aad669eb365251682e769b755d9d586`;
   kept in the toolchain folder, never committed), as 32-bit Linux programs
   with their own loader: on macOS they run in a Linux container. Built with
   it, a near miss of func_00206298 (written for 2.9-ee-991111) comes out at
   1,064 bytes against retail's 1,072, with 89% of its instructions in line,
   against 1,016 bytes with 2.9-ee-991111; `-O2` is the right level
   (`-O1` or no scheduling is far worse).

   **The math library builds with it** (2026-11-02), as OpenRAC's
   rac1-decomp builds the objects Sony built with 2.9-ee-991111-01 (its
   `Makefile.sn` and `config/core_text.objects`). The library is
   0x204F68–0x2093F0 (PAL 0x2062A8–0x20A8B8): from the first function that
   pads `div.s` to the last one only the library calls, func_002093C0;
   func_002093F0 after it is called from game code. config/us/layout.tsv
   gives it its own folder, `src/libm/`, and config/cflags.tsv names
   `2.9-ee-991111-01` for its files. tools/compile.py runs that release's
   Linux `cc1plus` through its own loader (`lib/ld-2.3.6.so`), from
   `ee-gcc-2.9-991111-01/` or `ee-gcc-2.9-dtls13010/` in the toolchain
   directory or from `SLY1_LINUX_TOOLCHAIN`; the preprocessor and the
   assembler stay the Windows 2.9-ee-991111 ones. On x86 Linux the program
   runs as it is; elsewhere it runs in an `i386/busybox:1.36` container
   (`docker run --platform linux/386`, OrbStack or Docker Desktop on macOS),
   or under `SLY1_LINUX_RUNNER`. Without the Linux build, tools/build.py
   leaves `src/libm/` out and takes the library from the disassembly: the
   image still matches, with fewer functions from C, and it says so.
   `tools/check.py` falls back to the Windows 2.9-ee-991111 for these files,
   as rac1-decomp does, which cannot match a `div.s` function.
   `python3 tools/toolchain.py` reports which is found. The three math functions matched before this
   (func_00205318, func_00205578, func_00208FE8) are EXACT with both builds,
   in US and PAL. The first pass with it (2026-11-02) matched six more,
   func_002082F8 (2,380 bytes) among them.

   **Its bit-access macros** (2026-11-02). Two forms recur in its near
   misses:
   - a `nop` after a `b` or `jr` and its delay slot, putting the next label
     on an 8-byte boundary (0x204FB4, 0x2062EC, 0x20730C, 0x208DC4 and
     others), where this compiler aligns jump targets to 4;
   - a float argument's bits copied out (`mfc1`, `move`) and the frame set
     up before any constant is loaded, where ours loads the constants first.
   No flag or tool gives them (`-O1`, `-O3`, `-G2`, `-fno-schedule-insns`,
   `-fno-schedule-insns2`, `-fno-delayed-branch`, `-mips3`, `-mcpu=r4000` and
   `r5000`, C with the Linux `cc1`, the Linux `ee/bin/as.bin`), and
   `-malign-jumps=3` pads every jump target, not some. The compiler aligns
   the first label after the start of a loop to 8 (`-malign-loops=3`, its
   default), and a `do { } while (0)` is a loop to it: reading the float's
   bits inside one gives both forms. func_00204F68, func_00205210 and
   func_00209210 are EXACT that way and with nothing else. Retail's library
   was written with such macros, so include/float_bits.h defines a pair,
   `FLOAT_TO_BITS` and `BITS_TO_FLOAT` (our names), which src/libm uses for
   a float's bits, and the same for a double's words (`DOUBLE_TO_WORDS`,
   `WORDS_TO_DOUBLE`, `DOUBLE_HIGH`, `SET_DOUBLE_HIGH`), which func_00209010
   needs; AGENTS.md allows `do { } while (0)` there and nowhere else. With
   them all 33 functions of the library match.

   **Its files** (2026-11-06). The library is 35 objects, proved whole in
   config/us/files.tsv as src/libm/file_*.c: one function each, and two
   with no code, only a constant in .rodata (the double infinity at
   0x24FF70 and the error mode at 0x24FF78). They are C, built by the
   Linux `cc1` with `-O2 -G0`. Each file's .rodata is its own in one
   piece, 0x24F890-0x24FFA0 in the order of the code: the file's
   `static const` floats and tables in definition order, then the
   literals its code needs (a checked function's name, a folded
   `0.0 / 0.0` or `-two25 / zero`). GCC folds a `static const` into the code
   as an immediate and still writes it out, unused or not, which is why
   retail has a 1.0 after the cosine's code and a 1.0 and 1e-30 after the
   square root's. Double arithmetic in plain C (`(double)x`, `-inf`,
   `y *= 0.5`, `x < 0.0`) gives the software routine calls retail makes.
   The word-for-word comparison with the toolchain's `libm.a` confirmed
   each object's range and that every one was compiled from C; nothing
   else was taken from it.

Record every result here: the function, the compiler, the flags, and whether
it matched.

Additional US checks on 2026-10-29: 80 small functions across
`src/main/00104000.cpp`, `0011C000.cpp`, `00128000.cpp`, `00134000.cpp`, and
`00140000.cpp` matched with SN GCC 2.95.3 and `-O2 -G0 -fno-exceptions`.
The full US build, linked with GNU binutils using `-march=r5900 -mabi=eabi`,
printed `MATCH: build/us/SCUS_971.98 sha1
57dc305db57932ad3f1122966cdb695d2e62a47a with 1785 functions from C`.

Twenty-two near misses from this wave are retained under `nonmatching/` with
the remaining differences recorded in each file. PAL version check reported
27 absent, 42 differs, 7 error, 1709 match; 79 of the 80 functions in this
wave match at their PAL counterparts, while `func_001365A0` differs there.
Progress reported US 1785/4766 functions (13.38%) and PAL 1709/4791 (12.62%).
Unit tests printed `OK` (11 tests), and
`python3 tests/check_repository.py` printed `ok: 0 problem(s)`.

**The square root (2026-11-03).** Nine game functions hold a bare `sqrt.s`. `__builtin_sqrtf`
adds a NaN check and a call to `sqrtf` that retail never has. `-ffast-math` gives a bare
`sqrt.s`, but its result lands in its input's register and the compiler schedules code around
it, where retail never does either: retail's `sqrt.s` behaves as an inline-assembly helper,
fixed in place, with an early-clobbered result. include/fpu.h is that helper, `Fpu::Sqrt`, the
one inline assembly AGENTS.md allows; with it, under the files' own flags, the functions match
(func_001EDDB0 first). OpenRAC's RAC3 keeps a `sqrt.s` helper for the same reason.

**The toolchain's runtime is C (2026-11-06).** Retail's 64-bit divide and remainder helpers
(func_001FAE38, func_001FB790, func_001FBE00, func_001FC3D0) are word for word the members of
the toolchain's `libgcc.a` (2.95.x and 2.9-ee-991111 alike), whose debug sections name a `.c`
source; the C++ runtime's throw and rethrow (func_001FE6A8, func_001FE4C8) need
`__builtin_unwind_init` and `__builtin_eh_return`, which `cc1.exe` has and `cc1plus.exe` lacks.
So that code is C: tools/compile.py builds a `.c` file with the release's `cc1` and the
driver's C predefines. Like the math library, the runtime was built by Sony's Linux build,
2.9-ee-991111-01: with the Windows `cc1.exe` of the same release the remainders and the unsigned
quotient keep their code but lose the unused stack slots retail's frames have (48 bytes for
func_001FC3D0, where cc1.exe gives 16), and with the Linux `cc1` all four divisions match. Each
division is its own file, as each is its own object in retail with its own copy of the table of
significant bits (src/lib/divide.c, remainder.c, divide_unsigned.c, remainder_unsigned.c, on
include/divide.h). src/lib/throw.c matches with `-O2 -G0 -fexceptions`; without `-fexceptions`
the stub of func_001FE4C8 moves and cc1 fails on func_001FE6A8. Without the Linux build these
files stay assembly in the build, as the math library's do. The
divide helpers multiply with one `multu`, read from lo and hi, which no C product gives (GCC
multiplies twice or splits a 64-bit product): include/mul_wide.h is that helper, the second
inline assembly AGENTS.md allows. As with libc and libm, nothing is taken from the archive but
the kind of its source; the C is written from retail's code.

**The runtime's files (2026-11-06).** From 0x1FAE38 to 0x1FFFD0 the runtime is proved file by file
(config/us/files.tsv), every file C built by the Linux cc1: the four division files, three
conversions (src/lib/double_to_u64.c, s64_to_double.c, s64_to_float.c), abstract_call.c, the double
and single software floating point (soft_float.c, soft_float_single.c), the exception runtime
(throw.c, with its frame tables in .data from -fexceptions), the 64-bit product (multiply.c) and
the unwinder (unwind.c, no frame tables, so no -fexceptions). Each boundary is where one object's
code and data end: its own tables and literals in .rodata, its frame tables in .data, its statics
in .bss; most are also one member of the toolchain's `libgcc.a`, equal word for word with
relocations masked (only that equality is used). Padding is no evidence here: the runtime's
functions are all 8-byte aligned, inside an object as between objects. The C++ runtime's
objects are proved too, each C++ built by the Linux cc1plus with exceptions on: allocate.cpp
(0x1FD8A8), exception.cpp (0x1FE8F0), new_handler.cpp (0x1FFFD0), type_info.cpp (0x200080) and
type_info_kinds.cpp (0x200750). Their classes take the names their type-name strings spell
(docs/NAMING.md); `#pragma implementation` writes the inline members, vtables and
type-information functions of include/exception.h, new.h and typeinfo.h where retail has them,
config/us/generated.tsv gives those functions retail's names, the common type-information
objects take their addresses from config/us/libcalls.tsv, and two of the files place their
`.gcc_except_table` (config/us/files.tsv's `except` column). cc1plus of 2.9-ee-991111 refuses
`#pragma implementation` after the preprocessor's line marker for the source, so tools/compile.py
names the unit itself in those markers.

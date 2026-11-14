# How matching work runs

The whole procedure, for people and AI agents alike. AGENTS.md has the rules; this page has the
steps. It follows rac2-decomp's (OpenRAC), the sister project of the same maintainers.

## The parts

| Tool | What it does |
| --- | --- |
| `python3 tools/todo.py` | the functions still to match, with their size, source file and tags (`leaf`, `calls`, `data`, `rodata`, `float`, `vu`, `jtbl`, `mmi`, `system`, `handwritten`, and the blocker `asm` for original assembly, docs/ASM_CLASSIFICATION.md) |
| `python3 tools/check.py FILE.cpp FUNC` | compiles one file with its flags and compares one function with retail: `EXACT`, or `DIFFER` with both disassemblies side by side |
| `python3 tools/check.py FILE.cpp FUNC --version eu` | the same function at its PAL counterpart, every address translated |
| `python3 tools/build.py` | the full US build with every C function of `src/` linked in: `MATCH` or `DIFFER` |
| `python3 tools/build.py --version eu` | PAL's build from its assembly: `MATCH` |
| `python3 tools/version_check.py` | every C function of `src/` checked at its PAL counterpart; writes `config/eu/c_status.tsv`, then the globals' `config/eu/c_data_status.tsv` (`tools/data_check.py`) |
| `python3 tools/progress.py` | the reports ByteMatch shows (`progress/<version>/report.json`) and the README table |

A function's disassembly is in `asm/us/text.s`, at its `nonmatching func_XXXXXXXX` line (`grep -n -A80 'nonmatching func_0011A338' asm/us/text.s`).

## 1. Coordinate

Before you start, and before you hand work to agents: read the pinned
[Contributor coordination](https://github.com/OpenThievius/sly1-decomp/issues/1) issue, make sure
you have exactly one comment there, and reserve what you will work on in it (AGENTS.md,
"Coordinating work"). At most 500 unfinished functions per contributor, all agents included.

## 2. Pick

Sort by size with `tools/todo.py`, and match by tier:

- **Haiku**: up to 400 bytes, many workers at once.
- **Sonnet**: 401 to 1,000 bytes, and what Haiku gave up on. A function Haiku left within a few
  instructions of retail goes to a Sonnet worker, one function each, with the earlier attempt and
  `tools/check.py --diff` as its start: that matched 40 of the 92 closest near misses (43%; the
  closest dozen, 7 of 12), against 28 of 420 (7%) when Haiku retried the same kind of function.
- **Opus**: over 1,000 bytes, complex ones, near misses in `nonmatching/`, and leading (the full
  build, landing, the reports).

Start with `--untried --exclude vu,system,handwritten`. `vu`, `system` and `handwritten` are
permanent for C (no inline asm: AGENTS.md). A `jtbl` function is a C `switch`; tools/check.py
compares its table with retail's. `tools/todo.py --untried --summary` counts each blocker. A `rodata` function is
fine, and its constant can be written two ways: read through an extern at the address retail loads
(`extern f32 D_00219718[];`, the object then keeps no `.rodata` and the relocation reaches retail's
address by name), or as a plain literal in C (a float, or a string), which the build links with
retail's own address (tools/rodata.py); `check.py` compares the whole literal with retail's and
prints `EXACT: ... (rodata)`. A table of data read by address is an `extern`, as ever. A worker stops
at its bound and hands its attempt up a tier.

## 3. Write C++ until it is EXACT

The game is C++ built by SN Systems' GCC 2.95.3 for the PS2 (docs/TOOLCHAIN.md). For each
function:

1. Read its disassembly. Work out the arguments (`$a0`–`$a3`, then `$a4`–`$a7`; floats in `$f12`,
   `$f13`, ...), the return value (`$v0`, `$f0`), the fields it reads (`lw $v0, 0x708($a0)` is a
   32-bit field at offset 0x708 of the first argument), the calls it makes and the data it uses.
2. Write a C++ file with the declarations it needs and the function, named as in the disassembly:

   ```cpp
   // SPDX-License-Identifier: AGPL-3.0-or-later
   #include "common.h"

   struct IntList { s32 count; s32 items[1]; };

   void func_0011A338(IntList* list, int value)
   {
       list->items[list->count++] = value;
   }
   ```

   - Types are `s8`/`u8` ... `s64`/`u64` and `f32` from `include/common.h`.
   - A field is a member of a struct with padding before it (`u8 pad[0x708];`).
   - A function it calls is declared with the arguments it is given:
     `void func_001B5F28(void* list, void* item);`.
   - Data it refers to is `extern` with its address name: `extern u8 D_0062C568[];`. A worker
     never defines a variable; defining a global is the lead's step (below, "A global defined in C").
3. `python3 tools/check.py your.cpp func_0011A338` until it prints `EXACT`. Read the `*` lines:
   they are the instructions that differ.
4. Then `python3 tools/check.py your.cpp func_0011A338 --version eu`. PAL usually has the same
   code; `DIFFER` there is worth a note, not a reason to change working US C.

### What usually moves the bytes

Measured on this compiler; add to this list when you learn something.

- **Branch order follows the `if`.** For `if (c) A; B;` the compiler makes `A` the branch and `B`
  the fall-through: when retail falls through into `return 0`, write
  `if (x > 0) return ...; return 0;`, not `if (x <= 0) return 0; return ...;`.
- **One load or two.** `p->n++` used as an index loads `p->n` once; writing `p->items[p->n] = v;
  p->n++;` loads it twice, because the store might change it.
- **Locals that live across calls** go into `$s0`, `$s1`, ...; a value that is only passed on stays
  in an argument register.
- **Returning the first argument** (`daddu $v0, $a0, $zero` at the end) is a function that
  returns its argument, often a C++ object returned by value through a hidden pointer.
- **`move` is `daddu`**, and saves are `sq`/`lq` of 16 bytes: both are what the compiler does,
  nothing to fix.
- **Type size and sign**: `lb`/`lbu`, `lh`/`lhu` and `lw` tell `s8`/`u8`, `s16`/`u16` and 32 bits
  apart; `slt` against `sltu` tells signed from unsigned compares.
- **Floats**: `$f12`, `$f13` ... `$f19` are the float arguments, in order, apart from the integer
  ones; declare as many as retail passes. `mul.s`, `add.s` and `c.lt.s` are the usual arithmetic
  and compares. A float literal built with `lui`/`ori`/`mtc1` is a plain constant in C
  (`0x3F19999A` is `0.6f`).
- **Compare operand order** decides the branch's registers: `if (v != p->f)` and `if (p->f != v)`
  give `beq a1,v0` and `beq v0,a1`. Flip the operands before rewriting anything else.
- **Signed or unsigned**: retail's `sltiu` against a constant means an unsigned compare
  (`for (u32 i = 0; i < 4; i++)`); `slti` means signed.
- **Statement order**: two stores often come out in the reverse of the source order; when only a
  pair of stores is swapped, swap the statements.
- **`if` against `?:`**: a ternary often becomes `movz`/`movn` and an `if` a branch. Write the form
  retail has; `if (x >= 16) m = 0; else m = 1 << x;` gives a branch-likely with its delay slot.
- **`base + (n * k + c)`**: retail adds the constant before the base when the sum is grouped so.
- **Virtual calls**: a pointer is 32 bits, so slot `N` of a vtable is at `N * 4`:
  `typedef void (*VFn)(void* self); struct Obj { VFn* vtbl; };` and `obj->vtbl[7](obj)` for
  `lw 0x1C`.
- **128-bit and unaligned copies**: a 16-byte copy is `lq`/`sq` only when the type is 16-byte
  aligned (`struct __attribute__((aligned(16))) Quad { s32 a, b, c, d; };`); an 8-byte copy is
  `ldl`/`ldr`/`sdl`/`sdr` when the type is packed (`__attribute__((packed))`). These attributes
  describe real types and are allowed; they are not compiler tricks.
- **The frame size** shows the locals: `addiu $sp, $sp, -0x60` with `$ra` saved at 0x50 means
  0x50 bytes of locals; size the local struct so.
- **A wrapper that passes a float through untouched** (retail never moves `$f12`) declares the
  callee with fewer parameters in that file; do not add a dummy float.
- **Dead loads** in retail are not reproduced by unused locals: the compiler removes them. Note it
  and move on.
- **A `u8` return** adds `andi $v0, $v0, 0xff` before `jr $ra`; when retail has no mask, the
  function and the local hold an `s32`.
- **The frame is set by the locals that are used**, laid out in declaration order: a frame that
  is off while the body matches usually means a missing local (a 12-float array, a 0x50-byte
  struct). An unused `s32 scratch[4]; (void)scratch;` reproduces 16 extra bytes of frame, as long
  as nothing is stored to it.
- **Callees take what they read.** Count a callee's parameters from its own disassembly: an extra
  argument changes the caller's prologue and delay slots. When retail leaves `$a0` untouched and
  sets only `$a1`, the callee has a first parameter that is passed on unchanged.
- **Branch shape.** `if (x != 0) { ...; return 1; } return 0;` gives retail's branch-likely form;
  `if (c) A; else B;` makes `A` the fall-through, so flip the arms when retail branches to it; a
  `switch` on 0, 1, 2 gives a compare tree where an `if` chain does not; `if (p) do { ... } while
  (p);` gives a bottom-tested loop. A single exit (`if (r != 0 && c) { ... } return r;`) avoids
  the `move $v0, $zero` of a second return.
- **Expression shape.** Loads retail hoists above a branch are named locals before it; `i * a`
  and `a * i` give `mult` its operands in different orders; the compiler reassociates
  `(head - 1) + n`, so split it (`t = head - 1; t += n;`). Runs of stores to one base are
  rescheduled whatever the source order: try the permutations of a few stores before anything
  else.
- **Struct initialisers** (`Pair p = { a, b };`) call `memset`; assign the fields one by one.
  Packing only an 8-byte member gives `ldl`/`ldr`/`sdl`/`sdr` while the rest stays aligned.
- **A store after a call** can land in the call's delay slot; write it before the call when retail
  has it there. A local whose address is passed to a callee lives in the frame: put such locals
  in one struct sized to retail's frame. Reloading `self->field` after a call, rather than keeping
  it in a local, saves a callee-saved register.
- **Float details.** `__builtin_fabsf(x)` gives `abs.s` (`x < 0 ? -x : x` does not); float
  compares keep the source's operand order.
- **Casts decide extension.** Packing 32-bit values into 64 bits matched with `s32` parameters,
  not `u32` or `u64`; a 64-bit bit test needs an `(s32)` cast on each side.
- **Read the diff before rewriting.** A near miss (a few instructions off) is almost always a
  fact about a callee or about order, and `tools/check.py FILE FUNC --diff` shows which:
  - a register retail loads and ours leaves unused: the callee takes one more argument (pass the
    local on); a float moved before `sq $ra`: the callee takes that float; `$v0` kept busy across a
    call: the callee returns a value, so declare it non-void and cast the call to `(void)`;
  - the same callee declared with its integer and float parameters in a different order moves the
    argument moves, even though the registers are the same: copy the prototype from a caller that
    already matches;
  - a callee's declared return type can change the register an unrelated test uses; and a
    memset-like callee returns its pointer, so declare it so;
  - two independent stores swapped, or one store written as `*(s32*)((u8*)self + 0xNNN) = v`,
    which the scheduler orders differently from member access (for five stores, try all 120
    orders);
  - `while (*p)` with `(u8)*p++` passed straight to an `s8` parameter keeps the separate `lb` test
    and `lbu` load that a `u8 c` local folds into one;
  - `extern s32 T[][2]` indexed `[i][1]` fixes the operand order of an address add for a stride-8
    table; a loop counter copied into its own local when retail tests the call's `$v0` directly.
- **What does not move.** A `lui`, `li` or `move` scheduled against a store or another `move`
  before a `jal`; a pair of `$s` registers swapped; two `$v0`/`$v1` temporaries swapped; an
  epilogue shared where retail duplicates it. Ten to thirty source variants each left these put.
  After about 25 compiles, record it as NEAR and move on.
- **Absolute addresses.** Data splat pins to an address outside the executable (`D_FA0` at 0xFA0)
  is spelled with eight digits in C (`D_00000FA0`); the link maps it.
- **Which `D_` load is a literal.** A `lui`/`lwc1` pair aimed at `.rodata` (0x217380 to 0x250580)
  is a constant: write it as a literal (`3.4028234663852886e+38f` for 0x7F7FFFFF; a string as
  `"text"`), and `check.py` compares it with retail's whole. The same pair aimed at `.data` (above
  0x250580) is a variable: declare it `extern f32 D_0026185C;` with its eight digits. A block that is
  only copied (`lq`/`sq` from a table) is an `extern u8 D_...[]` and an aligned struct assignment.
  A constant retail builds with `lui`/`mtc1` (0.25f, 0.5f) is pooled in `.rodata` when written as a
  literal, and does not match that way; so far no source form of it has.
- **A function that cannot match for its size.** If a function's code is byte-identical and the
  checker still says retail has more bytes after it, the function table gives it the size of the
  function entered through a pointer after it. `config/<version>/symbol_addrs.txt` names those
  starts; re-run `tools/setup_asm.py` and `tools/inventory.py`. The same holds for a function
  behind the linker's leftovers (8-byte runs of an `addiu $sp` or a store, then a nop): code
  takes its address as `func_X + N`, and without a name splat joins it to them.
- **A global defined in C.** A `.data` global (from 0x250580 in US) may be defined in the
  one file that owns it, with its initial value: `s32* D_0025C360[2] = { D_0025C540, D_0025D540 };`.
  A `.rodata` one (0x217380 to 0x250580) is a `const`, written `extern const` so that it keeps
  its name (`extern const Fn D_00219668[4] = { func_0011F0C8, ... };`): a namespace-scope
  `const` is file-local in C++, and dropped when nothing uses it.
  Every other file keeps it `extern`. Each global gets its own section (`-fdata-sections`), and
  `tools/c_layout.py` puts it at the address its name gives, in place of the disassembly's labels it
  covers, which stay defined at their addresses. It must start at a label of
  `asm/us/data/<section>.<section>.s` and end where a later label (or jump table) starts, or one
  word before an 8-aligned label: the padding GCC leaves before an aggregate of 8 bytes or more
  (a scalar `f32 D_X = 150.0f;` followed by four zero bytes, not an `f32[2]`). The full build is the check: a
  wrong value makes it `DIFFER` at that global's offset. With GCC 2.95, a C++ global goes to
  `.data` even with no initialiser (`= 0` too); only a file's `static` variables go to `.bss`.
  So a `.bss` label (from 0x27B300) is a `static` of the one file that uses it, named
  `D_XXXXXXXX` and defined before its first use: all of a file's statics share its `.bss`, and
  each must sit at its address's offset from the first. `.bss` is not in the image, but every
  instruction that addresses it is.
- **A global built at startup.** A global whose initialiser is not constant (it copies another
  global, or calls a function) makes the compiler write a static initialiser
  (`__static_initialization_and_destruction_0`) and a constructor that calls it
  (`_GLOBAL_$I$`, named after the file's first public definition), which retail's constructor
  list in `.data` calls. `config/us/generated.tsv` gives them retail's names
  (`_GLOBAL_$I$*` for whichever the constructor is); `tools/compile.py` renames them, and they
  are checked and counted like any function of the file. The object's own `.ctors` entry is
  discarded: retail's list comes from the disassembly.
- **A function-local static.** `static T x;` inside a function, where `T` has a constructor, is
  built on first use: GCC 2.95 tests a guard word, runs the constructor and sets the guard.
  Retail shows it as a `.data` word (the guard, tested and set to 1) and a `.bss` record that
  the function alone uses, filled in that branch. The compiler names them itself, the variable
  `x.N` and the guard `_$tmp_K.N` (in its own section `.data._$tmp_K` with
  `-fdata-sections`), and writes both out just ahead of the function's code;
  `config/us/statics.tsv` (file, function, variable, object, guard; `-` for no guard) gives
  them retail's labels, read from the function's `%hi`/`%lo` pairs, and `tools/compile.py`
  renames them as it does `config/us/generated.tsv`'s functions, so that `tools/check.py`
  resolves them and a split file places them like any `D_XXXXXXXX` global or static. A row is
  written once the labels are known, matched or not: a function still in assembly is skipped,
  and in `src/` one defined without the static is an error. In a whole file the guard is
  emitted with its function, after every global defined above it, so retail's `.data` order
  shows where the function sits among the file's data; and the file's `.bss` column in
  `config/us/files.tsv` gives the records' start. The parameter blocks of
  `DrawPlayerMarkerRing1` and its kin (func_001D5FA8, func_001D60B0, func_001D61C8, whose
  three guards end player_request.cpp's `.data`, and func_0018A510, whose guard sits before
  world2_boss.cpp's later globals, so those are defined after the function) are the known
  cases: each is a brace initialiser that runs once (include/ring_params.h; a record cleared
  by the compiler's memset call and filled with constants in one block is that form,
  docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER").
- **A real source file.** A 16 KiB window is our cut, not the original's. Where retail shows one
  of the original files (a static initialiser ends a file; data used together sits together, in
  code order), its functions move to a file of their own, `src/main/<name>.cpp`, in retail's
  order, and `config/us/files.tsv` gives its code range and the addresses of its `.rodata`,
  `.data` and `.bss`. Such a file is compiled whole, as the original was (no
  `-ffunction-sections` or `-fdata-sections`, no literal baking), and each of its sections is
  linked in one piece: the full build's `MATCH` proves the boundary. Its globals with
  constructors bring the compiler's initialiser functions, named in `config/us/generated.tsv`.
  Its original assembly functions, and those of its functions not matched yet, are included at
  their place with `INCLUDE_ASM(func_X);` (include/asm_func.h); an unmatched one still counts as
  unmatched, and its C replaces the line once it is EXACT. Retail's constructor list
  (`D_0027B130`) names each file's `_GLOBAL_$I$` function, so it gives that file's exact end.
- **Finding and proving a file.** Retail's constructor list (`D_0027B130`) names each file's
  `_GLOBAL_$I$` function, so it gives the exact end of every file with a static initialiser. A
  file's start comes from its data: `.rodata`, `.data` and `.bss` are laid out in file order, in
  several stretches of their own (method tables, literals and strings, initialised data), so the
  last label the previous file's functions read bounds it. Inside one file the data follows the
  definitions' order, not the code's. What the full build showed while proving files:
  - GCC aligns a jump table to 16, so a file's `.rodata` must start where its tables land on 16.
  - A string or float the code reads once is a literal in the code, placed before its
    function's jump table; a named `extern const` would be emitted elsewhere, or folded.
  - A global with no initialiser goes to the end of the file's `.data`; one in the middle of
    retail's carries `= { 0 }`. A global built by a constructor stays at its definition.
  - The linker pads before a file's `.data` or `.rodata` to that file's own alignment, up to 16.
    One file's literals and jump tables leave no gap of their own (a float literal is aligned
    to 4), so a 4-byte literal on 16 after a gap of zeros starts the next file's `.rodata`:
    func_0014B6A8's FLT_MAX at 0x249EF0, 12 bytes after func_00149760's last jump table, ends
    file_149398.cpp (now camera_controller.cpp) between the two (one file built whole came out
    12 bytes short).
  - A cut the data bounds only to a range is a choice, said so in both files' heads. The
    functions from 0x14A7B8 to 0x14B6A8 read no `.rodata` or `.data` of either side, code is
    on 8 in every file, and a file that holds only words aligns its `.bss` to 4 (`objdump -h`
    of file_149398.o: `.bss 2**2`), so the two statics D_0027C008 and D_0027C00C can be two
    files' `.bss`. Built whole, the cuts at 0x14A7B8, 0x14A888, 0x14ABD0, 0x14B608 and
    0x14B6A8 all printed `MATCH`. The cut is at 0x14B6A8 (gauge_manager.cpp), where the second
    file's data provably begins; the functions before it could belong to either file or a third.
    They are now three files cut by role only (item_column.cpp, symmetric_solve.cpp,
    agent_registration.cpp), and file_149398.cpp is camera_controller.cpp, ending at 0x14ABD0.
  - A cut no signal shows, made because one unit at one set of flags cannot build its
    functions, is a choice too, decided by the maintainer: on 2026-11-12, on loop.c's threshold
    (docs/toolchain/loops.md, "A threshold of 94" and "The splits on the threshold"),
    path_follower_helpers.cpp (0x1D8E40 to 0x1D9AC8, `-mvu0-use-vf0-vf30`) was cut out of path_follower.cpp
    for func_001D9488, leaving path_follower.cpp (to 0x1D8E40) and world.cpp (from 0x1D9AC8),
    and curve_segment.cpp (0x130168 to 0x130F48, the same flags) out of placed_object.cpp for
    func_00130C58, where the role changes inside the range the data allows.
    Its edges are where each data section separates with the fewest globals defined in one unit
    and read only in another, every section contiguous and on its unit's alignment (a unit with
    a 16-aligned object starts its `.data` on 16); what crosses is declared `extern`, and the
    heads say what is evidence and what is choice.
  - GCC 2.95 writes a file's vtables after everything else in its `.rodata`: a test unit built
    whole, a class with two virtuals and then a function with a jump table, puts the jump table
    first and the vtable (`.align 3`, 8 bytes per entry and 8 for the end) after it. So a GCC
    vtable followed by another function's literal or jump table ends a file's `.rodata`:
    D_0024A0E0 (PacketWriter's base, pooled_object.cpp) before PivotActiveSet's jump table at
    0x24A100 (active_set_solver.cpp), and D_0024A6F8 (the GIF writer's, game_progress.cpp) before
    ReadPlacedObjectModel's FLT_MAX at 0x24A710 (placed_object_model.cpp).
  - Functions GCC emits after the static initialiser and before `_GLOBAL_$I$` (the setters at
    0x137248 to 0x137268) look like inline functions it emitted out of line at the end of the file.
  - The colour objects (`Clr_180E38`, four bytes set in the constructor; `ColorWord` (placed_object_model.cpp), one word)
    and the 0x1C-byte style object (zeroed, then 0x2D, 0xFF7D4B00, two sizes given as integers,
    0.3 twice) recur in many files' static initialisers.
  - The compiler has one read-only section. A test unit with a `const` table of function
    pointers, a `const` aggregate with relocations, a `static const`, a vtable, a string literal,
    a float and a jump table, built whole, gives one `.rodata` (cc1plus writes `.rdata` for all
    of them); only `-fdata-sections` splits it. So read-only data that lies apart from the
    `.rodata` of the files whose code reads it, in no order of those files, is the `.rodata` of
    a file with no code. Such a file gets an empty code range at its place in the link
    (`text` = `end` in config/us/files.tsv, as src/libm/infinity.c), and is linked whole like
    any other.
  - The first stretch of `.rodata` (0x217380 to 0x248D80) is three such files, linked between
    entry.cpp and object_host_functions.cpp (an empty range at 0x1000C8): class_descriptors.cpp
    (the class descriptors and method tables, grouped by the file of their methods but in no
    order of those files: oscillator's classes at 0x2178C0, zone_collider's at 0x218970,
    oscillator's again at 0x21C038), property_registry.cpp (the property lists by class id),
    and global_tables.cpp (tables read all over: the sound table, the classes by id, the disc
    check's checksum table, keys, the level table whose names are in commentary_best_time.cpp's
    own `.rodata`). The last also holds the first 0x58 bytes of `.data`, just before
    object_host_functions.cpp's: a file with no code comes first in both. The game's GCC
    vtables, by contrast, are in their files' `.rodata`. Where one of these files ends and the
    next starts the build cannot tell (each cut is on 16, the most any of them aligns to); the
    cuts follow what the data is, and keep each file under the repository's size limit.
  - An aggregate is aligned to 8 by itself (16 for a type that asks for it), so a word-aligned
    array is the tail of the object before it: D_00244DFC is the last member of the property
    registry D_00244950.
- **Spell data names with eight digits** (`D_00000FA0`, not `D_FA0`): `check.py` resolves only those.
  Keep each prototype, and each struct with an `__attribute__` in front of it, on one line:
  `tools/todo.py` reads source files line by line.

## 4. When to stop

Stop when it is not a function (it reads registers it never sets, or has no `jr $ra`; it starts
with a stray `addiu $sp, $sp, +N`), when it is hand-written (a bare busy-wait of `nop`s, a loop in
a delay slot, a jump into another function), when it needs an instruction C cannot ask for
(`sqrt.s`: `__builtin_sqrtf` becomes a call to `sqrtf`), when it reads `$t0`–`$t3` as inputs
(arguments past the eighth are on the stack, so plain C cannot pass them there), when three different
wordings give the same wrong bytes, or after about ten compiles without getting closer. Variadic
functions wait for a `stdarg.h` written for this project. If `check.py` says "the C is N bytes,
retail's function M", fix the size first: something is extra or missing. Put the attempt in `nonmatching/func_XXXXXXXX.cpp` with a comment at the
top saying what still differs, and move on.

When only the order of some statements is left (a run of stores, the arguments set up before a
call), do not try orders by hand: mark the lines with `/*P*/` and run
`python3 tools/permute.py FILE FUNC`, which compiles every order and stops at an EXACT one
(`--auto` marks each run of simple statements itself; `--write OUT` keeps the best). Its result
counts like any other once `tools/check.py` prints `EXACT`.

Before calling a difference a register-allocation tie, check the declarations of the functions
it calls: `python3 tools/decls.py` lists those whose return type contradicts the function's C
definition or retail's callers. A call to a function that returns a value sets `$v0`, so a `void`
declaration moves the caller's registers around the call even where the value is ignored
(func_0018F448 and func_00211348 matched once func_0020A538 and func_0020B190 were declared `s32`).

Before guessing at a register difference, ask the compiler why: `python3 tools/regalloc.py FILE
FUNC` compiles the attempt with the allocators' dumps (`-dl -dg`, `-dp` and `-g` for the line
notes, kept in `build/regalloc/FUNC/`), aligns our instructions with retail's as regdiff.py does,
and for each register that differs prints the value behind it:

```
value r139: ours $t1 -> retail $t2 (2)  [at 211644 21169C]
  r139 (4 refs over 24 insns, set 2 times, temporary, several blocks)
  born insn 153, line 16 `do {`
  dies insn 123, line 31 `self->w18 = n + self->w18;`
  got $t1 from global-alloc: 5 of 6 in its order
  $t2 was free when r139 was placed: it took $t1 first
  in retail, $t1 holds r141 over 23 insns of this life (...); r141 is $t2 in ours, ...
```

- **A value** is a pseudo register of the `.lreg` dump (`r139`), found through the insn each of
  our instructions comes from. "born" and "dies" are its first set and last use, with the source
  line (`vu0.h:859` for a line of a header's inline function).
- **Who placed it**: local-alloc (a value used in one basic block; it goes first, by priority
  `floor_log2(refs) * refs / span`, its span counted in its block's insns in sched1's order, ties
  to the one born first), global-alloc (in the order `.greg` prints; ties to the lower pseudo
  number, the value the RTL made first), or none (reload gives it a register insn by insn).
- **What took retail's register**: a value placed before it and live over part of its life
  ("taken by"), a hard register in use (an argument, a return value, a call's), or nothing
  ("free"): then it took ours first, and the tool looks for what retail keeps in our register
  ("in retail, $t1 holds r141"). That value is the one to fix first: `Likely levers` names where
  each chain starts.
- **Swaps** (two values whose registers retail exchanges) end with what flips the allocator's
  order: a shorter life or more refs for one, a longer life for the other, or the other born
  first. For local values it prints the block's order of their sets and uses: sched1's order,
  which can differ from the final code's.
- **A call crossed**: a value crossing a call takes a saved register unless caller-saves keeps
  it in a caller-saved one; a value with no register lists who holds each register it could take.

The dump does not always say why: a register free over the whole life but not chosen is the
allocator's order or its own lifetimes (local-alloc's are one insn longer at each end with
scheduling), and the tool says so rather than guess. Its priorities are the dump's measure, a
guide to which edit could flip an order, not the compiler's numbers (docs/TOOLCHAIN.md,
"Constants in one very long block"). Use it after `tools/decls.py` and before the permuter: a
lever it names (a value kept too long, set too early, tied by a copy) is an edit to try by hand.

For a register-allocation or scheduling tie that no reordering moves, use decomp-permuter
(https://github.com/simonlindholm/decomp-permuter, MIT). It is never committed: fetch it once into
`tools/ext/`, which is gitignored, with its own Python environment:

    git clone https://github.com/simonlindholm/decomp-permuter tools/ext/decomp-permuter
    python3 -m venv tools/ext/venv && tools/ext/venv/bin/pip install toml Levenshtein

Then `python3 tools/permuter_setup.py FILE FUNC` writes `build/permuter/FUNC/` (retail's function
assembled as `target.o`, the C as `base.c`, a `compile.sh` through `tools/compile.py` with the
function's own compiler) and prints the command that runs the permuter on it. A score of 0 is a
lead: copy the candidate back and check it with `tools/check.py`. Its C must still follow every
rule here (plain C++, no barriers).

Unattended, `python3 tools/permute_night.py FUNC ...` runs near misses one after another and keeps
each zero, spliced back into its near miss and checked, in `build/permute_night/FUNC/`
(`EXACT_*.cpp` when check.py agrees); `--recheck FUNC` splices and checks again what a run kept.
Pick its targets with `python3 tools/regdiff.py --all`: those that differ only in `registers` or
`order` are the permuter's. What the first VU0 night (2026-11-07) showed:

- **Most zeros are tricks.** Of 77 zeros on one near miss, 75 were EXACT, every one by taking a
  parameter's address (`p = &self`) or reusing one variable for two values. Read each diff; when a
  zero points at a real change, write that change plainly and check it: func_001D6608 matched as
  the store common to both branches written once after them, where the permuter's zero wrote it
  twice.
- **What the setup must carry through the permuter's C parser:** u128's `mode(TI)` (else every VU0
  helper's `j` operand is impossible) and g++'s `<?` and `>?` (rewritten as permuter_max and
  permuter_min calls and back); both are done by permuter_setup.py and permuter_compile.py. A near
  miss must be one function with its declarations: a whole-file copy, or a member function
  defined outside its class, stops the setup.
- **Probe before a long run.** A target whose base.c does not parse fails in seconds with no base
  score and wastes nothing, but a run of 20-minute slots needs every target to reach a base score
  first: start each for a few seconds and read `base score =` in its run.log.

Before (or instead of) the permuter, `python3 tools/tsearch.py FUNC` searches the rewrites a
programmer plausibly wrote, not random ones: a library of meaning-keeping transforms (for against
while and a guarded do-while, if/else against a ternary or an early return, a result variable
against returns, switch against an if chain, x = x + y against x += y, statement order within the
dependences, a declaration hoisted or sunk, s32 against u32, const, a pointer local against a
reference, an argument named before its call or a temporary written in place, an index walk
against a pointer, an element named by a pointer, a helper of the file or its headers written in
place or called, VU0 helper alternatives, commuted operands, zero tests; `--transforms` lists
them). It also knows the source forms that matched in November 2026, each proved by finding a real
match again (docs/toolchain/*.md has the mechanisms): a constant named by a local of a loop body or
of the function, and back (`named-constant`, func_00131F60); a local that only carries an
expression written as the expression at each use, and back (`repeat-expression`, func_001D5678); a
struct's single-expression method on a cast of a global array written as the array's elements in
place, and back (`helpers`, func_001D7778); a float parameter moved among integer ones, or the
reverse, with the file's declarations and calls following (`param-order`, func_00185150); a
callee's prototype between `void` and `s32` where its result is unused (`callee-return`,
func_001FA6B0); two locals with separate lives merged and one split, one index for two loops
(`reuse-variable`, func_001B7280, func_001FA6B0); a test of a variable both arms set written in
each arm, and back (`test-in-each-arm`, func_00187F40); a switch's arms reordered and a variable
set in every arm instead of before the switch, and back (`case-order`, func_001B7280); `a = v;
b = v;` against `a = b = v;` (`chained-assignment`, func_00109488's form); a vector stored through
`Vu0::Q` against a `Vu0::Vec` structure cast (`struct-store`, func_0019ED58). A candidate that
changes a parameter's order or a callee's return type lists in its header the declarations and
callers in other files that must follow before it can land. It applies each at every place it
fits, compiles every result the way the function lands,
scores it as regdiff.py does (instructions out of line, registers aside, then words that differ),
and keeps the best `--beam` for the next step, to `--depth` steps or `--minutes`; `--beam 0` keeps
every code reached, the closure to `--depth`, for a small function. Every improvement is written to
`build/tsearch/FUNC/best_NN.cpp` with the chain of rewrites that made it, an EXACT as
`EXACT.cpp`, and `log.tsv` scores every candidate. A candidate never holds more inline assembly,
`register`, `volatile`, `do { } while (0)`, goto or empty statements than its start, nor a local
never read or a new array (tests/test_tsearch.py runs the library over every near miss to check
it). Its dependences are judged on the text (memory by field name), so read an EXACT before
landing it, as any other, through `tools/check.py` and the full build.

The lead keeps the closest attempt per function in `nonmatching/` (PAL's own definitions in
`nonmatching/eu/`): `python3 tools/nonmatching.py stage 'build/swarm/*/func_*.cpp'` adds every
attempt within 15% of retail's bytes, and `python3 tools/nonmatching.py check` re-scores them all,
writes each file's verdict line (`// BYTES n/size (p%), checked DATE`) and the index
`nonmatching/README.md`. The progress report credits a near miss with its share of retail's bytes
as `fuzzy_match_percent`; matched functions and code still count EXACT functions only. Landing a
function removes its staged file.

## 5. Land

A worker's `EXACT` is not a match: the full build is. The lead (or you, alone):

1. puts each EXACT function into its source file, the 16 KiB window of `src/main/` (game code) or
   `src/lib/` (libraries) or `src/libm/` (the math library; config/us/layout.tsv) its address falls in (`tools/todo.py` names it), in address order, with the declarations it needs;
2. runs `python3 tools/build.py`: it must print `MATCH ... with N functions from C`. A function
   that broke it goes back to `nonmatching/`;
3. runs `python3 tools/version_check.py`, `python3 tools/progress.py`, the tests and
   `python3 tests/check_repository.py`;
4. commits: the matches with what was verified in the body, the regenerated reports in their own
   commit (CONTRIBUTING.md, "Commits"), and opens the pull request;
5. updates its coordination comment: finished functions come off it once they are on `master`.

## Running a team of agents

- The lead reserves the wave's functions in its coordination comment first, then splits them
  between workers: no two workers share a function, and contiguous functions go to one worker,
  since they often belong to one class.
- Workers write in their own folder (`build/swarm/<worker>/`, one `.cpp` per function) and never
  edit `src/`; only the lead lands. Each reports one line per function: `EXACT`, `NEAR` (what
  still differs) or `SKIP` (why).
- Each type a worker defines carries the function's address as a suffix (`List_11A338`), so that
  files merge without clashes; the lead renames them when it lands related functions together.
- Every brief says: the rules of AGENTS.md (plain C++, no per-function flags, nothing from the
  prototype or other projects), the bound (about ten compiles a function), where results go, and
  to leave `src/` alone.

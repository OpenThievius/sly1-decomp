# How matching work runs

The whole procedure, for people and AI agents alike. AGENTS.md has the rules; this page has the
steps. It follows rac2-decomp's (OpenRAC), the sister project of the same maintainers.

## The parts

| Tool | What it does |
| --- | --- |
| `python3 tools/todo.py` | the functions still to match, with their size, source file and tags (`leaf`, `calls`, `data`, `rodata`, `float`, `vu`, `jtbl`, `mmi`, `system`, `handwritten`) |
| `python3 tools/check.py FILE.cpp FUNC` | compiles one file with its flags and compares one function with retail: `EXACT`, or `DIFFER` with both disassemblies side by side |
| `python3 tools/check.py FILE.cpp FUNC --version eu` | the same function at its PAL counterpart, every address translated |
| `python3 tools/build.py` | the full US build with every C function of `src/` linked in: `MATCH` or `DIFFER` |
| `python3 tools/build.py --version eu` | PAL's build from its assembly: `MATCH` |
| `python3 tools/version_check.py` | every C function of `src/` checked at its PAL counterpart; writes `config/eu/c_status.tsv` |
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
- **Sonnet**: 401 to 1,000 bytes, and what Haiku gave up on.
- **Opus**: over 1,000 bytes, complex ones, near misses in `nonmatching/`, and leading (the full
  build, landing, the reports).

Start with `--exclude vu,jtbl,rodata,system,handwritten`: those need things the build does not
model yet (docs/ROADMAP.md). A worker stops at its bound and hands its attempt up a tier.

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
   - Data it refers to is `extern` with its address name: `extern u8 D_0062C568[];`. Never define
     a variable.
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

## 4. When to stop

Stop when it is not a function (it reads registers it never sets, or has no `jr $ra`), when it is
hand-written (a bare busy-wait of `nop`s, a jump into another function), when three different
wordings give the same wrong bytes, or after about ten compiles without getting closer. Variadic
functions wait for a `stdarg.h` written for this project. If `check.py` says "the C is N bytes,
retail's function M", fix the size first: something is extra or missing. Put the attempt in `nonmatching/func_XXXXXXXX.cpp` with a comment at the
top saying what still differs, and move on.

## 5. Land

A worker's `EXACT` is not a match: the full build is. The lead (or you, alone):

1. puts each EXACT function into its source file, the 16 KiB window of `src/main/` its address
   falls in (`tools/todo.py` names it), in address order, with the declarations it needs;
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

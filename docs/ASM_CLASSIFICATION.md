# Original assembly

Some retail code was not made from C, and some words are what the linker left of a function it
stripped. Compiling C to match those bytes would misrepresent where they come from, and the
build already keeps them from the disassembly. `config/us/original_asm.tsv` lists them, and
`tools/progress.py` counts them as finished, apart from the exact C matches.

This follows [OpenRAC's classification](https://github.com/OpenRAC/rac1-decomp) (rac1-decomp,
`docs/ASM_CLASSIFICATION.md`; credited in THIRD_PARTY_NOTICES.md). The rules below are ours,
from the evidence in this game's bytes.

## What is counted

The progress report's `matched_functions` and `matched_code` now include the listed functions.
The README table and `tools/progress.py` show the two apart:

    3,183 exact C, 670 original assembly, of 4,770 functions

A function is exact C when `src/` defines it and the build links it and still prints `MATCH`
(`tools/version_check.py` for PAL). A function cannot be both: `tools/progress.py` stops if
`src/` defines a listed function, and `tests/test_tools.py` checks the table.

A PAL function is original assembly when its US counterpart (`config/eu/map.tsv`) is: the
same source, built for the other region.

**Changing what the report counts is a policy change and needs the maintainers' review**
(OpenRAC's docs say the same of theirs). The exact C count is kept visible so that nothing is
hidden by it.

## The table

`config/us/original_asm.tsv`, written by `python3 tools/classify_asm.py` and checked with
`--check` (both need `asm/us/`; CI only reads the committed table). Columns: name, address,
size, kind, why.

Game code and Sony's libraries are both classified; a function matched in C is C and is left
out. Counts are of `config/us/original_asm.tsv` as written on 2026-11-01.

### handwritten

The function holds an instruction the compiler cannot emit, or other evidence says it was
written as assembly:

- a VU0 macro-mode instruction (COP2: `vaddx`, `lqc2`, `ctc2`, ...): 563 functions;
- a 128-bit multimedia (MMI) instruction that no function matched in C contains: 57;
- the disassembler's own "handwritten" mark: 103, among them the crt0 entry (func_00100008),
  func_001000C0 at the start of game code and the library's kernel call stubs;
- a kernel, cache or system-control instruction (`syscall`, `ei`, `di`, `eret`, `mfc0`, `mtc0`,
  `cache`, `sync`), a paired-pipeline instruction (`mult1`, `mtsa`, ...) or `max.s`/`min.s`:
  35. No function matched in C holds one, and neither compiler emits them from plain C;
- stores and `nop`s before the stack frame is set up (`swc1`, `nop`, then `addiu $sp`): 5.
  Neither compiler ever schedules a store before its prologue, and no function matched in C
  does;
- a function whose code is, word for word apart from its relocations, a member of the
  toolchain's `libc.a` that was assembled from a `.S` source: 6 (the library's block copy and
  fill routines). The member's `.mdebug` section names its source file; only whether it ends
  in `.S` or `.c` is read, never its code, names or anything else (`sdk_assembly()`).

These rules follow OpenRAC's (rac1-decomp, `docs/reference/ASM_CLASSIFICATION.md`: kernel
instructions such as `ei`, hand-placed nops, `max.s`/`min.s` in delay slots, and the source
names in the SDK's `libc.a`), as the maintainers decided on #18. Two things OpenRAC also
weighs are measured here and do not count: `sqrt.s` (both compilers emit it for
`__builtin_sqrtf`, followed by a NaN check that calls `sqrtf`; a bare `sqrt.s` stays blocked as
`nonc` in `tools/todo.py`) and a `nop` outside a delay slot (462 functions matched in C have one).
`break 0, 7`, the compiler's divide-by-zero trap after a division, is plain C as well.

The MMI rule is evidence-based. Six functions that are matched in C contain `por`, the
compiler's 128-bit `|`, so `por` proves nothing and is in `COMPILER_EMITS`. An instruction is
added there only together with a function that is matched in C and contains it.

### remnant

A run of words the linker left of a function it stripped. It counts when:

1. it starts on an 8-byte boundary, where a stripped function began;
2. it holds no jump or branch;
3. nothing refers to it: no instruction or data in `asm/us/` names it;
4. the code before it is finished: going back over earlier remnants, there is a `jr` and its
   delay slot, a tail `j`, or the start of game code.

Fragments that fail a test stay unmatched, with the `fragment` blocker in `tools/todo.py`, as
a boundary for a person to look at. 113 remnants pass.

## What is not classified

- **Multimedia instructions the compiler emits** (`por`, `pref`): 9 functions hold only those;
  they are C.
- **`break 1023, 1023`**: one function; not the divide trap, left for a person to look at.

## Keeping it right

- `python3 tools/classify_asm.py --check` after `tools/setup_asm.py`: fails if a rule or the
  disassembly changed what the table should hold.
- A function in the table is not work for `tools/todo.py` (blocker `asm`).
- If a function in the table is ever matched in C, remove it from the rules (an instruction
  that is `COMPILER_EMITS`), not from the check.

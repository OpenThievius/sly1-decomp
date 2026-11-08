# Original assembly

Some retail code was not made from C, and some words are what the linker left of a function it
stripped. Compiling C to match those bytes would misrepresent where they come from, and the
build already keeps them from the disassembly. `config/us/original_asm.tsv` lists them, and
`tools/progress.py` counts them as finished, apart from the exact C matches.

This follows [OpenRAC's classification](https://github.com/OpenRAC/rac1-decomp) (rac1-decomp,
`docs/ASM_CLASSIFICATION.md`; credited in THIRD_PARTY_NOTICES.md). The rules below are ours,
from the evidence in this game's bytes.

## What is counted

The progress report's `matched_functions` and `matched_code` include the listed functions of
kinds `handwritten` and `remnant`; the kind `inline` is C still to match (below).
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
out.

PAL's functions that US has count through their US counterpart. The game-code functions only PAL
has (docs/VERSIONS.md) have no counterpart, so the same rules run over PAL's own code
(`asm/eu/`) and write `config/eu/original_asm.tsv` for them: on 2026-11-05, 7 remnants (stray
stack increments and lone words, like US's) and 2 handwritten (`max.s`, `min.s`).
`tools/version_src.py todo` leaves them out. Counts are of `config/us/original_asm.tsv` as written on 2026-11-01.

### handwritten

The function holds an instruction the compiler cannot emit, or other evidence says it was
written as assembly:

- a VU0 macro-mode instruction (COP2: `vaddx`, `lqc2`, `ctc2`, ...): 563 functions;
- a 128-bit multimedia (MMI) instruction that no function matched in C contains: 40. `mult1`
  is not one: the compiler issues the second of two multiplies to the EE's second pipeline as
  `mult1` (the 64-bit product, func_001FE890 in src/lib/multiply.c, and the pad library's slot
  readers in src/lib/00204000.cpp matched with it), so tools/todo.py counts it among the
  instructions the compiler emits, and the functions that held only it are code to match;
- the disassembler's own "handwritten" mark: 103, among them the crt0 entry (func_00100008),
  func_001000C0 at the start of game code and the library's kernel call stubs;
- a kernel, cache or system-control instruction (`syscall`, `ei`, `di`, `eret`, `mfc0`, `mtc0`,
  `cache`, `sync`), a paired-pipeline instruction (`multu1`, `mtsa`, ...) or `max.s`/`min.s`:
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
`__builtin_sqrtf`, so it is no proof of assembly; but always followed by a NaN check that calls
`sqrtf`, which no retail function has, so `tools/todo.py` keeps it blocked as `nonc`) and a `nop`
outside a delay slot (462 functions matched in C have one).
`break 0, 7`, the compiler's divide-by-zero trap after a division, is plain C as well.

The MMI rule is evidence-based. Six functions that are matched in C contain `por`, the
compiler's 128-bit `|`, so `por` proves nothing and is in `COMPILER_EMITS`. An instruction is
added there only together with a function that is matched in C and contains it.

### inline

C with inline assembly (2026-11-07). An instruction the compiler cannot emit does not by itself
make a function hand-written: in most of these functions it sits in code GCC shaped. The function
has the compiler's own stack frame (`addiu $sp, $sp, -N` among its first four instructions, the
same N freed at its return), saves and restores registers, calls with filled delay slots, and
schedules the special instruction among its loads and stores; the special instructions are 1 to
5% of it. The same short sequences recur across hundreds of functions (`lqc2`/`sqc2` around a
vector, the three-term dot product `vmul.xyz vaddw.x vadday.x vmaddz.x`, `vwaitq vaddq.x
qmfc2.ni`): a library of small inline-assembly helpers, called from C. So these functions were
written in C, as retail's bare `sqrt.s` is (include/fpu.h's `Fpu::Sqrt`, AGENTS.md).

- A function the rules above would call hand-written for a VU0, MMI or system instruction, or the
  disassembler's mark, is `inline` when it has the compiler's frame. A frameless leaf stays
  hand-written: its shape does not tell.
- `max.s` and `min.s` are not evidence at all. g++ 2.95's GNU minimum and maximum operators
  (`a <? b`, `a >? b`) emit them as ordinary instructions under the files' own flags, which the
  scheduler moves and puts in branch delay slots as retail's are; func_001EAC68 is word for word
  `scale = scale >? __builtin_fabsf(a)`. (`-ffast-math` also emits them from `?:`, but it changes
  the bytes of functions already matched in 11 of the 18 files that hold them, so retail was not
  built with it.) A function whose only special instructions are these is plain C.
- The toolchain's `.S` members, a game-code tail jump and stores scheduled before the frame stay
  hand-written.

On 2026-11-07: 547 functions in US (533 of game code, 14 of the libraries), and one of PAL's
own. They are C to match, not finished: `tools/progress.py` leaves them out of the count, their
files include them with `INCLUDE_ASM` (not `ASM_FUNC`), and `tools/todo.py` lists them with the
tag `inline` and the blocker `helper` until the shared helper headers for their VU0, MMI and
system sequences exist (AGENTS.md). `tools/version_src.py todo` lists PAL's own one. The 31
functions whose only special instructions were `max.s` and `min.s` are plain C.

### remnant

A run of words the linker left of a function it stripped. It counts when:

1. it starts on an 8-byte boundary, where a stripped function began;
2. it holds no jump or branch;
3. nothing refers to it: no instruction or data in `asm/us/` names it;
4. the code before it is finished: going back over earlier remnants, there is a `jr` and its
   delay slot, a tail `j`, or the start of game code.

Fragments that fail a test stay unmatched, with the `fragment` blocker in `tools/todo.py`, as
a boundary for a person to look at. 113 remnants pass.

### Two kernel-library functions examined (2026-11-08)

func_001FAA00 (src/lib/tlb.cpp) and func_001F71D0 (src/lib/request_thread.cpp) are `inline`
only through the disassembler's mark, and each has a feature no other function has, so they were
examined for whether they are assembly or C. Neither classification was changed; the maintainers
decide. The experiments are in `build/swarm/handwritten-research/` (not committed), each a copy
of the whole file with the function written in C, checked with
`SLY1_COMPILER=2.9-ee-991111 python3 tools/check.py FILE FUNC --flags "-O2 -G0 -fno-exceptions"`,
the files' own row in config/cflags.tsv.

What the disassembler's mark means: spimdisasm marks a function "Handwritten" when any one of
its instructions is one rabbitizer's `isLikelyHandwritten()` accepts (COP0 moves, `syscall`,
`cache`, `eret`, ...). Checked with the project's rabbitizer 1.16.2: `mtc0 $zero, $6` and
`syscall` are flagged, `sync.p` and `daddu $t9, $zero, $zero` are not. The mark is about one
instruction, says nothing of the code around it, and an inline `__asm__` gives the same
instruction and the same mark. The kernel library has no archive in the toolchain (only libc.a
and libm.a, `ARCHIVES` in tools/classify_asm.py), so the `.S`/`.c` test does not apply to
either function.

**func_001FAA00, 500 bytes: compiled C with a local register variable for its counter and two
inline `mtc0 $6; sync.p` (the TLB's Wired register), high confidence.**

For assembly:

- the counter lives in `$t9`, caller-saved, across all four loops' `jal func_001FA9B0` and, on
  the overflow paths, across `PrintToOutputHook` and `TerminateProgram` (`daddu $t9, $zero,
  $zero` in the delay slot at 0x1FAA64, read at 0x1FAA7C after those calls). GCC never
  allocates a caller-saved register to a value live across a call;
- `mtc0 $x, $6` and `sync.p` occur nowhere else in retail;
- the same library's assembly uses `$t9` freely (func_001FA7D8, the cache routine, keeps its
  mask in it), so the register is in its authors' style. Weak: that routine is a leaf.

For C:

- the C below, compiled with the file's flags, is **EXACT** (all 125 words), and its
  neighbour func_001FA9C0 stays EXACT in the same unit. Its only unusual line is
  `register s32 i __asm__("$25");`. The same C with a plain `s32 i;` gives the compiler's own
  choice: the counter in `$s2`, a fourth saved register (`$s3`), a 0x50 frame and 504 bytes. So
  `$t9` is exactly what a register variable gives, and nothing else the compiler does differs;
- every shape is GCC 2.95's: the frame (0x40, `$s0`/`$s1`/`$s2` at 0/0x10/0x20, `$ra` at 0x30,
  the saves interleaved with the first `lui`/`addiu`), the record's high half kept in `$s2` and
  `addiu $s0, $s2, %lo(D_00277FE0)` rematerialised before each block (-G0), each loop rotated to
  `bnezl` with its first load duplicated in the likely slot, `slt $v0, $t9, $s1` recomputed after
  the overflow calls, the last loop's `0xE0000000 + (j << 13)` strength-reduced to `addiu $s1,
  $s1, 0x2000`, and a `nop` before a loop label only where the label would not otherwise be
  8-byte aligned (0x1FAA8C and 0x1FAAF4, not before 0x1FAB70): the compiler's loop alignment,
  which the C reproduces;
- a compiler artefact, not a choice anyone writes: retail returns `$t9` after `sll $t9, $t9, 13`
  in the last loop's guard (0x1FABA4), i.e. the count shifted by 13. The C that matches says
  `return i;` (`return i << 13;` adds a second `sll`): GCC does not reserve a local register
  variable's register, and its loop optimiser computed the address's starting value into `$25`
  itself. An author of assembly who wanted the shifted value would not get it this way;
- a single helper, `mtc0 %z0, $6; sync.p` with the operand constraint `"dJ"`, gives both writes
  (`$zero` for 0, `$t9` for the count), also EXACT;
- the file is one object (config/us/files.tsv) whose other function, func_001FA9C0, is matched C,
  with a file-local copy of the 0x56 system call stub (func_001FA9B0) that only this function
  calls; the kernel library's C also uses inline COP0 helpers (system_calls.cpp's four wrappers,
  `ReadCop0Status`, matched in C).

The remaining doubt is compiler output edited by hand, which the bytes cannot tell from C; the
register variable is the simpler account of every instruction. Matching it in `src/` needs that
register variable, which AGENTS.md does not allow ("no register pins"): the choice is between
allowing it here as the original's own declaration, or leaving the function as it is.

```c++
s32 func_001FAA00(void)
{
    register s32 i __asm__("$25");
    TlbEntry* e;
    s32 n, j;
    PrintToOutputHook(D_0024EC30, t.n0 - 1, t.n0, t.n0 + t.n1 - 1, t.n0 + t.n1,
                      t.n0 + t.n1 + t.n2 - 1);              // t is D_00277FE0's record
    SetWired(0);                                            // mtc0 $zero, $6; sync.p
    i = 0;
    n = t.n0;
    if (n > 0x30) { PrintToOutputHook(D_0024EC68); TerminateProgram(1); }
    for (e = t.t0; i < n; i++, e++) func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
    n = i + t.n1;
    if (n > 0x30) { PrintToOutputHook(D_0024EC80); TerminateProgram(1); }
    for (e = t.t1; i < n; i++, e++) func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
    t.wired = i;
    SetWired(i);
    if (t.n2 > 0) {
        n = i + t.n2;
        if (n > 0x30) { PrintToOutputHook(D_0024EC98); TerminateProgram(1); }
        for (e = t.t2; i < n; i++, e++) func_001FA9B0(i, e->mask, e->hi, e->lo0, e->lo1);
    }
    for (j = i; j < 0x30; j++) func_001FA9B0(j, 0, 0xE0000000 + (j << 13), 0, 0);
    return i;
}
```

**func_001F71D0, 148 bytes: compiled C with an inline system call, very high confidence.**

For assembly:

- it is retail's only `syscall` outside the 16-byte stubs and the program's entry; every other
  system call goes through a stub (`addiu $v1, $zero, N; syscall; jr $ra; nop`);
- no stub for -0x2F exists in retail (0x2F's is func_001F6A90). Weak: the linker strips unused
  functions (the remnants above), so the library may have had one.

For C:

- the C below is **EXACT** (all 37 words), with func_001F7020 and func_001F70F8 still EXACT in
  the same unit. The system call is one inline `__asm__("li $3, -0x2F\n\tsyscall")` whose output
  is a `register s32 r __asm__("$2")` (or, equally EXACT, a `move %0, $2` inside the asm). With
  an unbound `"=r"` output the compiler drops `daddu $s0, $v0, $zero` and differs, so that move
  is the compiler copying a `$v0`-bound result into the register that keeps it across the call;
- the frame is the compiler's (0x20, `$s0` at 0, `$ra` at 0x10), the `(u32)self < 0x100` test
  is hoisted into the `beq`'s delay slot (0x1F71EC), the early return is `b 0x1F7258` with
  `ld $ra` taken from its target into the slot and the branch moved past it (reorg's delay-slot
  filling from the target), `-1` is set in a `b`'s slot, and the ring's address is copied for no
  reason (`daddu $v1, $a1, $zero` at 0x1F7240, then `sb` through both): artefacts of GCC's CSE
  and scheduling that nobody writes by hand;
- `beq $s0, $a0` reads the argument after the `syscall`: C that tells the compiler only `$3`
  is clobbered gives exactly that;
- it sits inside a C object between func_001F70F8 and the linker's leftover word at 0x1F7268, and
  uses that object's static ring, semaphore and thread id.

```c++
s32 func_001F71D0(s32 tid)
{
    s32 self = CurrentThreadIdFromInterrupt();   // li $3, -0x2F; syscall, result in $2
    if (self != tid) {
        return WakeThreadFromInterrupt(tid);
    }
    if ((u32)self >= 0x100 || g_requestThreadId == 0) {
        return -1;
    }
    u32 t = g_requestRing.tail & 0x1FF;
    g_requestRing.tail = t + 1;
    g_requestRing.e[t].kind = 0;
    g_requestRing.e[t].arg = self;
    PostSemaphoreFromInterrupt(g_requestSemaphore);
    return self;
}
```

Both are against what the classes above say of the disassembler's mark: here it was raised by
one system instruction in code the compiler shaped, which is the `inline` rule's case. The 169
functions classified `handwritten` look different: 87 are marked by the disassembler (80 of them
16-byte system call stubs, the others frameless routines of 8 to 172 bytes such as the program's
entry and func_001FA7D8's unscheduled `sync; cache; sync` with a hand-placed `nop`), the rest
are VU0/MMI leaves, `.S` members of libc.a, a tail jump and one `sync` routine. None of the 169
sets up a stack frame in its first four instructions, as these two do.

Decision (2026-11-08, the maintainer): both are matched as the C they were, with the original's
own forms allowed for these two functions only (AGENTS.md, "Plain C++"): func_001FAA00's
register variable in $t9, and the two system sequences as helpers in include/system.h
(`SetTlbWired`, `CurrentThreadIdFromInterrupt`). They are out of the table.

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

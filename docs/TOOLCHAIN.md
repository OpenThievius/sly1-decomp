# The toolchain

The compiler, assembler and linker are proprietary. They are never committed,
and nothing in the repository is copied from them: you supply them, and the
tools find them outside the tree.

The research notes are split by compiler pass into one file per chapter under
[docs/toolchain/](toolchain/), because a single file grew past the repository's
512 KiB limit. A reference to a section of docs/TOOLCHAIN.md names a
subsection in one of those files: search docs/toolchain/ for its title.

## The chapters

- [The VU0 helpers](toolchain/vu0-helpers.md)
- [The MMI and system helpers](toolchain/mmi-system-helpers.md)
- [Reloads and stores](toolchain/reloads-and-stores.md)
- [Loops](toolchain/loops.md)
- [CSE](toolchain/cse.md)
- [GCSE](toolchain/gcse.md)
- [sched1](toolchain/sched1.md)
- [Conditional moves (jump.c)](toolchain/conditional-moves.md)
- [Alias classes in the schedule](toolchain/alias-classes.md)
- [Stack slots](toolchain/stack-slots.md)
- [Shapes of large functions](toolchain/large-functions.md)
- [Constants in one very long block](toolchain/long-block-constants.md)
- [Still to qualify](toolchain/still-to-qualify.md)

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
  - **but it miscounts where its fragment list breaks**, and the original did not
    (2026-11-08). Its code fragments sit on an obstack whose chunks hold about 3992 bytes of
    straight code; when the chunk runs out within the five instructions after a loop's label,
    it counts only the instructions in the label's own fragment and pads any loop there,
    five instructions or ten, with up to five nops (a sweep of a 5-instruction `bne` loop behind
    0 to 3000 filler instructions: nops at 994 to 998, 1992 to 1996, 2990 to 2994 only). Any
    directive before it that ends a fragment (`.p2align`, even with nothing to pad) moves the
    breaks, so a function's C can be EXACT alone and still move its file: func_001BC0E0
    (StartSoundEffect's 16-byte copy loop got five nops, func_001BFFC8 landed 0x18 late) and
    func_001579B0 (three in func_00158F80's). Retail has none of this: in its .text no
    backward branch with no other branch or jump in its loop has two nops or more before it
    unless its loop is short, and no short loop has more than its count needs. A loop holding
    an FPU operation (`neg.s`) is not padded at all (func_00153A50's 4-instruction list walk at
    0x153B18), and a call or another branch in the loop also stops it, so the rule is the
    assembler's own and not ours to restate. tools/short_loops.py keeps the assembler as the
    judge without its miscount: each loop of compiled code is first assembled alone, in a
    section of its own (a fresh fragment list), and the nops it gets there go into the text
    before its branch; the branch itself aims at a forward alias of its label (`$LSLk = $Ln`
    after it), which the assembler cannot measure, so it adds none of its own. Applied to
    every compiled file in tools/compile.py; both builds match with it, and with it
    func_001BC0E0 is linked.

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
  The same assembler filled a return's slot (`j $31` in reorder mode) with the one real
  instruction before it, where ours leaves a nop (2026-11-08): a volatile store
  (func_001F7270's write to the serial port) or the `dsra $r,$r,32` that ends the
  compiler's two-instruction 64-to-32-bit truncation, which the compiler never puts in a slot
  itself (func_002115F8, func_001F7390). A load or a macro (`li`) stays, as retail leaves a
  volatile load and a `li` before a call (func_00202DA0, func_001F9AD8); tools/volatile_slots.py
  does this too. A volatile load right before a reorder-mode `jal` went into its slot as well
  (func_00203B18's semaphore, 2026-11-08), except where the load follows a label or the slot of a
  branch (an instruction emitted under noreorder): both of func_00202DA0's stay before their
  calls, as GNU as never swaps a branch with an instruction after a label or after a noreorder
  one.
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

## Index of the techniques that matched

What matched functions overnight on 2026-11-08/09 (about 80 of them), grouped by the compiler pass each
technique targets. The rule of the method: find the pass in the dumps and GCC's source first, then write the
plain C++ that has retail's property. Each entry names a function where it matched and the section that
explains it; search the section's title or the function. Walls that stay open are listed at the end.

### Signatures and declarations
- **A missing parameter is the commonest hidden difference.** A parameter passed on to a base method or a
  virtual slot is one more pseudo before the call; reload deletes its moves, but sched1 and global-alloc count
  it. Look at the callers' argument registers and the sibling methods' signatures (func_001EBF40 "A Load
  method's reader", func_00143418 "A time step passed on", func_0018AD88, func_00161B10, func_001719E8).
- **An extra parameter is the same mistake the other way** (func_001F5268). A near miss passed a seventh
  argument to CollectTreeNodeSpans, the base pointer its two vertex addresses are built from, because retail
  holds that pointer in $t2. The copy `$t2 = verts` kills `verts`, so its INSN_REG_WEIGHT is 0 and sched1 picks
  it before the two `verts + index` sums; `verts` then dies at the second sum, ties to $a1 there, and a move
  to $t2 is left over (4 bytes). Without the argument, local-alloc simply finds $t2 free for `verts`. The other
  callers (collider_contact.cpp, camera.cpp) pass six arguments: a register retail sets is not an argument
  until the callers agree.
- **A prototype's parameter order** sets the order of argument moves, since ints and floats use separate
  registers; the callee's code cannot show it, the callers do (func_0013A128, func_0012C9E8, func_001E4888,
  func_00131198).
- **A callee declared `void` that really sets v0** changes sched2's dependents (func_00131198 "A call's result
  register ends a use's dependences"). A function returning a value nobody reads can be the original
  (func_00211618).
- **A matrix returned by value** is g++'s named return value: each row to a local, then to the result
  (func_0018A040, func_00188B48, func_001BA5B0, func_001C6028).
- **The file's real struct and pointer types.** A record's member load has an alias flag a cast array's does not
  (func_00191C78 "Corner pointers read as a record's members"); Sony's compiler separates stores by type
  (func_001F7BE8 "A run of stores in two alias classes").

### Alias classes and memory (sched1, sched2)
- **The weight slot is a cast's copy.** `Vu0::Scalar`, `ScalarAt`, `FromFloats` and `ScalarInGpr` end in
  `return Q((s128)r)`: g++ 2.95 copies the register into a scalar-flagged temporary that member loads never wait
  for (func_001D87C8, func_001C75B0, func_0017ABE8, func_001A00A0, func_0015BC78 "The weight slot is a cast's
  copy"). Where a near miss stores its own `Vec02 k` or `Slot`, pass `Vu0::Scalar(...)` directly.
- **Call through the descriptor member** (`self->desc02()->m20(...)`), not a cast array of function pointers,
  so both sides of the alias test carry a flag (func_001EB698). `RotateMembers` and `Vec::ScalarAtValue` read
  rows and members as members (func_001980B0, func_001C75B0, func_001719E8).
- **A global read as `D[0]`** is an aggregate's word and waits behind pointer stores (func_001CDB70, PAL
  func_eu_001AEC90 "A pointer global read as an aggregate's word").
- **Read a pointer or vector where it is used**, or before the frame stores, so no register holds an address
  across a test and no store holds the load back (func_00199698, func_001A2D88 "A pointer read before the frame
  stores").
- **An extern const float or FLT_MAX is folded into a second .rodata word:** write the literal (func_00186BA8,
  func_001C57C8, func_0013BF68). check.py misses it; the full build catches it.

### Scheduling order (sched1, sched2)
- **The birthing rule:** adjust_priority raises a pseudo set once and live at the block's end (func_00179A68).
  Ties fall to INSN_REG_WEIGHT, then dependents, then INSN_LUID, which is where the insn is expanded.
- **Operands in insn order:** name each weight beside its vector, or pass the vectors as `Vec::Of`, so loads
  come before slot stores (func_001A15D8 "Operands in insn order", func_00191570). Name a weight just before its
  use, not at the top, where retail stores it late (func_001C3EB0, func_0018DDD8, func_0014A8F8).
- **Weight-first helpers:** a sum helper's parameter order sets when slot stores are emitted (`MulAddX3`,
  `MulAddX2WeightFirst`; func_001DDE90, func_001218C0).
- **A store after a call at a block's end** makes the jump every insn's dependent: write it once after the join
  so the call ends the block (func_0017B8C0). The same shape lets a call end its arm and flow's nop take an
  issue slot (func_0013BF68 "A call that ends an arm leaves flow's nop").
- **Conversion helpers** (`ToFloat`, `ToFloatMoved`, `ToFloatViaBits`, `ToFloatNow`) differ in latency, unit
  and where the GPR comes from; try the other one (func_001D4348, func_00186230, func_00141D88).
- **Store then scale in place** (`Q(*o) = Sum(..); Q(*o) = MulX(Q(*o), w)`): the dead store lives until flow2
  and keeps the product out of the sum's register (func_00130540, func_001C6028).
- **sched1's weight puts a dying value's store first** (Sony's compiler, func_001F8290).

### Register allocation (local-alloc, global-alloc, reload)
- **Global ranking is log2(refs) x refs / live length.** Split an expression into two statements, or name an
  intermediate, to change the counts (func_001F7390, func_0012C9E8 "A named operand of `>?`", func_00144BE8).
- **A variable reused for two values or two loops** joins their conflicts and preferences (func_0016E738,
  func_00186568, func_001BBC38, func_0018AE38).
- **A block-local variable that crosses a call** takes s0 first and pushes a long-lived value out of it
  (func_001C9DE0 "A load hoisted over a conditional move takes a register from it").
- **A literal initial value, or leading equal constants,** double a life through REG_EQUAL (func_001BB290,
  func_0017C428 "a switch's default first", PAL func_eu_0015DF58).
- **A named local versus a literal** moves a life by one insn: a float constant in a named local is a
  user-variable pseudo scheduled early; write the literal where the matched twin does (PAL func_eu_0015C5C0,
  func_eu_001AB2B0).
- **Two variables sharing one register:** read the near key before the call in its arm (func_00185498).
- **A Vec named from a Vec result** adds a movti copy and a reference (func_0016C528).
- **Reload's round robin is one step off with no visible extra reload:** the original repeated code that
  cross-jumping merged after reload; write the repeated tail instead of a fall-through (func_001F2840).
- **A dot product kept in a saved GPR across calls is a float, not a vector** (func_00171238): retail's
  `qmfc2 s0, vfN` after a Dot, then `mtc1 s0` for an FPR use and `qmtc2 s0` for each weight, is
  `f32 x = ToFloat(Dot(..))` used as `FromFloat(x)`: ToFloat's "=r" output and FromFloat's "r" inputs
  outnumber the one FPR use, so regclass prefers GR_REGS. A u128 Dot result across calls is
  "VU_REGS or none" in the .lreg dump (set once or twice, with ToFloatMoved too) and is spilled.
- **A frame address passed to an inline function is no GCSE expression,** so PRE does not keep it in a
  saved register across a guarded call (func_00171238, "A frame address passed by an inline call").
- **A ToBits store just before a load costs the load its register**: local-alloc's widened lifetimes keep
  the next value out of the qmfc2's GPR; `Vu0::StoreX` makes the qmfc2 a reload. Two loops over the same
  three corners sharing one counter variable give their reversed counters one register (func_00191290
  "A frame address PRE copies, StoreX's reload and one counter for two loops").

### Loops (loop.c, jump.c)
- **loop.c moves an invariant when 80 x savings x lifetime >= insns** (the threshold is 79 for a loop with a
  call and falls by 3 per move). A `const f32&` local at the top of the body, a named constant, or Vec versus
  u128 operands change what moves and in which pass (func_001CF158, func_001389D0, func_001D8E40).
- **Pass a weight by value** (`ScalarAtCall`) so loop.c does not hoist its address (func_0017E3C8).
- **`for (i = n; --i >= 0; )`** keeps PRE off `n - 1` and reloads `n` before each of several loops
  (func_00186568). `&recs[n++]` versus `q[-1]` reduces differently (func_00148938).
- **A `continue` leaves a label among the rolled tests** and stops jump.c copying a loop's exit test
  (func_001388A0).
- **Vec values in the loop body** keep cse_around_loop from folding the loop bound into a second register
  (func_001C4D60, func_00191C78).
- **A loop variable declared before its loop** puts its set in the preheader (func_001E4888).

### CSE, GCSE, jump and reorg
- **GCSE's table has (n+3)/2|1 buckets** from the insn count; PRE's pseudos follow bucket order, which sets
  spill slots and callee-saved registers. Read T from the -dG dump's second "hash table (N buckets" line and
  tune the count with Vec/u128 forms or extra statements (func_001841D0, PAL func_0016AB38, func_00211618).
- **A loop test reading a point through `Q`** leaves a pseudo for its address that CSE reuses for the body's
  `&c` and PRE hoists into a saved register; `Vu0::Vec::Of` in the test avoids it (func_001C8590).
- **A store in each arm** avoids a pointer copy and keeps a value read after the join; cross-jumping merges the
  stores after reload (func_00126CB8, func_001D8E40).
- **A set written in the target's arm** lets reorg copy it into the delay slot (func_001CD870). jump.c hoists
  `x = 1` above a test when the else arm's first insn sets x: write the set later (func_001C4D60).
- **A return in each branch** lets the tails merge before the epilogue (func_0014DA98).
- **Assignments written once after an if/else** keep PRE from copying them into the arms (func_0013BF68,
  PAL func_eu_0015DF58).
- **A `b` over one load whose copy is in the delay slot** (`b join; lw a0, N(s2)` then `lw a0, N(s2)` at the
  else label) is an else arm whose own set reorg took into the first test's slot: `if (..) { mode = 2; .. }
  else { mode = -1; }`, not `mode = -1;` before the if (func_00171238).
- **A chained struct assignment re-reads its middle operand** in C++ (`b->v = a->v = zero;` is an lvalue):
  the left pointer is loaded first (expand_assignment expands the target before the value), then `a`'s
  pointer again for the copy, which retail's early `lw a1` then `lw v1` show (func_00171238).

### Inlining
- **An inline setter's constants** are substituted per insn, giving retail's mix of frame-relative and
  register-relative stores (func_001A7800 "A stack record filled by an inline").
- **An inline layout helper's frame-address parameters** give a fresh `addiu` at each call and the buffer from a
  spill slot (PAL func_001316E8 "Integration: an inline function's parameters and results"; func_00134B48).
- **A non-immediate constant argument** (a colour literal) makes try_constants keep the inline frame's base
  pseudo, which CSE then keeps in a saved register; pass a variable (func_001366A0 "One layout helper for three
  layouts"). A pointer argument to an inline (`StyleDrawer::Draw(.., &g_gsPacketWriter)`) has its %hi live
  across the code before the call, which changes reload's spill registers (same section).
- **An inline's whole frame** is one BLKmode temporary per call; locals declared in an inner block free their
  slots at its end (func_00125138, func_001E4888); a Scalar's copy reuses an inner block's slot of its mode
  (func_00158480 "A block's local slot taken by a Scalar's copy").

### Library code (Sony's 2.9-ee-991111)
- **Stores of different types do not conflict;** use the file's real pointer types (func_001F7BE8).
- **The frame is the size of the locals,** so a 256-byte frame means a 256-byte local (func_00203FD0, held back
  for the maintainer's decision; its section is on branch w9-203FD0).
- **`volatile` only for words an interrupt or another thread shares,** as retail reloads them (func_00203548).
- The GCSE bucket order is the same as SN's (func_00211618 "Sony's compiler: the same bucket order").
- **A flag tested twice and recomputed at the second test** came from a variable copied from a loaded temporary:
  GCSE's copy propagation splits the two tests into two expressions (func_001F8DB8, func_001F9028).
- **A local reused by two loops is one register;** retail's loops in different registers had their own variables.

### Process
- Find the mechanism first: the pass in the dumps (-dS, -dl, -dg, -dL, -dG, -fsched-verbose-6) and in GCC
  2.95.3's source, then write variants.
- Re-score before starting: notes go stale (constants, prototypes, a fix lost in a merge).
- Predict before compiling: the local-alloc and sched1 emulators and the GCSE table-size formula.
- Diagnostic probes that print EXACT but are not plain C++ (an empty `asm volatile`, a dead `else`, a volatile
  slot) prove a mechanism; they are never landed.

### Still open
func_00186230, func_00186320, func_00130748 and func_001D4348 (a compiler-made `qmfc2` that an asm one does not
reproduce); the static-record constructor wall (func_0018A510, func_001D61C8, func_001D5FA8, func_001D60B0);
func_0013BE18 and func_0014F168 (a store in each arm merged only after sched2); func_001F3140, func_0020A190,
func_00183668 (a pass-ordering effect no plain form gives); func_0014B6A8, func_001DC4D0, func_001DC238 and
func_0015A198 (an unread small object that only an empty destructor reproduces).

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

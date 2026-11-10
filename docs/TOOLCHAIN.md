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
- **The Q register.** Sqrt (vsqrt Q, a.x; vwaitq; vaddq.x) and DivX (vdiv
  Q, vf0w, s.x; vwaitq; vmulq.xyzw) are one asm each: nothing in retail is
  scheduled inside them. Dot and Sqrt stay two (Length calls both): retail
  puts loads between them (func_001EF768). DivX lists the scale first, as
  MulX does: the result takes the length's register when the length dies
  there (func_001C3B40, func_0018DE70 take the vector's).
- **A float from memory.** FromFloat's f32 operand is a pseudo the compiler
  loads into an FPR and moves with mfc1, even when its only use is the
  qmtc2, and so does a raw asm with the field as its operand. Retail loads
  such a float with lw (97 qmtc2 in retail take a register lw just loaded,
  against 35 lwc1 and mfc1, those with other uses of the float):
  FromFloatAt passes the float's bits, which the compiler loads with lw:
  as the qmtc2's own operand ("rV"), which reload loads into the register of
  an address that dies there, as retail does ("Reloads and stores").
- **A normalisation with a fallback.** Retail's "the unit vector, or this
  one when shorter than 1e-4" loads the fallback before the test (lq, then
  qmtc2 on the fallback's path), and the result's address, when it is a
  store's, is formed before the test too: the fallback is an argument of a
  function (NormalizeOr) and the store's pointer an argument of Q, both
  copied into registers when inlined.
- **Not yet reproduced.** In func_0018DDD8, func_001C3C98 and func_001C3EB0
  retail moves a float into the VU (lw or div.s, mfc1, qmtc2, and the store
  to its local) early, before the length's square root or the loads after
  it, and keeps it in a register across a branch; here sched1 moves it after
  the VU work, which changes the allocation (nonmatching/). A volatile
  FromFloat or one through a union changes matched functions. A boolean of a
  float comparison that retail sets with `li 1; bc1fl ...; move 0` is a
  variable assigned the comparison (func_001BC670, func_0013B778).

- **Weights are Scalars.** A float that scales a vector (a blend's 1 - t and t, a
  spring's k, damping and dt, Transform's w) is stored to a stack slot nothing reads,
  but not to a local of the function: two weights of one MulXSum share one slot (a
  third, of a MulAddX after it, too), the first stored first, and later locals reuse
  the slot. They are locals of calls that have ended: `Vu0::Scalar(f)` holds the
  store in a 16-byte local of its own. The same float twice is one qmtc2 and two
  stores (func_00143180). Transform takes w as a float and makes it a Scalar inside:
  retail allocates w's register after v's. FromFloat stays `"r"(f)`: reading the
  float's bits instead gives the `lw` retail has for a global but breaks
  func_001A35F0, whose weights are computed.
- **Rows as values when a product stores between rows.** MultiplyMatrices
  (func_00188668) and the three-row product store each result row between the
  sequences; rows read in place would be read again after each store, so retail's
  C had them in values first (Transform4, RotateRows, and MulTransposed loads b's
  rows, then a's, before its three sequences). Rotate and RotateTransposed read the
  matrix where it is (one address formed, rows loaded by the compiler).
- **Rotate or RotateRows.** Rotate's result is tied to the vector ("0"), as its six
  users show; RotateRows takes the rows as values and does not tie, so the result
  takes the first of r0, r1, r2, v that dies there (v's while the rows live on, row
  0's at the last row of a product: func_00116840 and the others the wave-2 workers
  found, func_001EBDD0, func_00128150, func_00128E88, func_00125138, func_001CCF98,
  func_001CDD98, func_001EA918, func_00144AA0).
- **The three-row product is three sequences.** `vmulaz/vmaddaz/vmaddz`, then x,
  then y (func_00189150, func_00128FD0) is one sequence per row of a's transpose
  times b; retail's z, x, y is the scheduler's order, and only y (the last) shares a
  register with an input, which three separate `__asm__` give and one does not.
- **The ten-instruction form is the inverse rotation.** `vmul.xyzw` of each row by
  v, `vmaxw.xyzw` of vf0 by its w (1.0 everywhere), then `vadday.x/vmaddz.x`,
  `vaddax.y/vmaddz.y`, `vaddax.z/vmaddy.z`: the dot of v with each row, that is v
  through the transpose (RotateTransposed). Its result is never tied ("=&j").
- **Return by value shows.** A function whose code returns its first argument in v0
  (`daddu v0, a0`) returns a struct by value: func_00188520
  (MultiplyByTransposedMatrix3x3) returns a 3x3 matrix, and its callers copy the
  returned temporary.

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
- **vmove.xyzw is a copy, sometimes the C's.** A plain `u128 b = a;` survives
  only when the copy is made in one basic block and read in a later one
  (func_0014BB08's two vmoves match that way); within one block CSE folds it
  away, and retail's vmove there (func_00141D88, func_00141F48) is reproduced
  only by an asm copy helper, which is still to add (Vu0::Copy). The allocator
  also makes vmoves of its own for a value kept across a loop (func_001CAB10).
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
- **A loop's alignment reaches later functions.** func_001579B0's C first broke its file's
  build: the assembler padded func_00158F80's copy loop with three nops, 12 bytes on. It was
  the assembler's fragment breaks, which a `.p2align` anywhere before moves (the short-loop
  padding of "The assembler matters"); tools/short_loops.py removes the effect.

- **The time argument.** In EABI a float argument goes in $f12 wherever it
  is in the list, but its place sets the order of evaluation: retail's mov.s
  before the pointer arguments of func_00125750's calls of the position and
  rotation methods (slots 34 and 35 of class 0x02) puts the time right after
  the object.

- **The two-term dot.** `vmul.xy` then `vaddy.x` (DotXY) is a dot of x and y; with
  a vector and itself and then Sqrt it is a length on the ground plane, retail's most
  common use (func_001A9868, the pair controller's nearest-object searches, the gauge
  agent's goals).
- **A word stored from qmfc2.** Retail's `qmfc2` followed by `sw` of the word (a
  float stored as bits: func_00160EA0's plane distances, the camera's ground length)
  is ToBits, qmfc2 into a u32; ToFloat's f32 goes through mtc1 and swc1.
- **The compiler's own qmfc2.** A u128 converted to an integer in C (`(u32)v`, a
  u64, a u16) makes the compiler move the VU0 register itself with qmfc2, the same
  encoding as retail's `qmfc2.ni`, but the truncation always follows as code
  (`dsll32`/`dsra32`, or `andi`), never folded into the store; a union reads it back
  through memory (sqc2, then lw or lwc1). No plain C form gives qmfc2 then sw or mtc1.
  A u128 given to an asm as an `"r"` operand is moved the same way, with nothing
  after it: ToFloatMoved holds only the `mtc1`, the qmfc2 being the compiler's,
  which reorg puts in a branch's delay slot (an asm statement never goes there) and
  the compiler makes in each arm that meets at the conversion. It finished
  func_0014EB10 (the delay-slot near miss), func_0019BC40, func_0019CF68 and
  func_001D12F0, and matches func_0016D828. Every user of ToFloat but one matches
  with this form too; func_00187B60 takes other VU0 registers with it, so the two
  stay: ToFloat where retail keeps the value in its VU0 register up to the qmfc2.
- **A length's test reads it through ToFloatMoved.** Where retail's mtc1 follows the length's
  qmfc2 at once, or a load (a constant, a divisor, a fallback's address) comes before the qmfc2,
  the qmfc2 is the compiler's reload of an "r" operand, scheduled after the other insns of the
  block: ToFloatMoved, not ToFloat (2026-11-08: func_00189B18, func_00189C28 through
  NormalizeOr, func_001162D0, func_001268B8's second test, func_001A3008, func_001C9AF8). It
  changes nothing already matched: NormalizeOr reads its length so, and the full build still
  matches.
- **A callee's return type reaches the FPRs after the call.** A callee declared to return a
  float that retail ignores marks $f0 set at the call, so the first float constant after it
  takes $f1; declared void (as its other callers have it), the constant takes $f0
  (func_001D66A8, ComputeOscillatorDisplacement).
- **A u128 across a call is spilled by the compiler.** VU0 registers do not survive
  a call, so a u128 local live across one is stored with sqc2 and reloaded with
  lqc2 (func_00198570's position); a plain copy of a vector to a local instead
  compiles to lq and sq.
- **The view test.** `vmulax/vmadday/vmaddaz/vmsubax.xyzw` into ACC, four `vnop`
  and `cfc2 v0, $vi17` (PlaneSigns) are the distances of a point from the camera's
  four side planes (their normals the columns of the 3x4 matrix at Camera+0x50) less
  a radius, read as the MAC flags; `(flags ^ 0xF0) == 0` (xori, bnez: all four
  negative) is retail's test, where `== 0xF0` gives li, bne and a nop. The radius's
  `(1, 1, 1, 1)` is Ones (`vmaxw.xyzw r, vf0, vf0w`), a separate asm because retail
  schedules it apart. The test is IsSphereInCameraView (func_00146038), inlined in
  ten more functions: func_001A0758 is matched; func_00125C90, func_00126270,
  func_00134B48, func_001358D0, func_0013AD80, func_0018F9D8, func_0019F620,
  func_001A3250, func_001AFBB0 and func_001F4AE0 have it. The assembler wants
  `$vi17`, written so, not an operand.
- **Weighted sums.** MulXSum3 and MulXSum4 (`vmulax`, `vmaddax` once or twice,
  `vmaddx`) weight three or four vectors by Scalars and list the first weight first,
  as MulXSum: retail's result takes its register (func_00130540, func_001D4698).
  MulAddX2 (`vadda` with vf0, `vmaddax`, `vmaddx`) adds two weighted vectors to a,
  its inputs in their own order (a, b, s, c, t). A weight read from memory is
  ScalarAt: FromFloatAt into Scalar's slot, the lw retail has (func_00198BD8's two,
  func_001D4698's speed).
- **MulAddX2's result takes a's register.** Retail gives the sum a's register
  wherever a is loaded in the block for it (func_001BBEB8, func_0017E3C8,
  func_001C54D0, func_001CEB18) and c's in func_00198BD8, whose a and b come from
  earlier blocks: the local allocator ties the result to the first input that is
  local to the block and dies there, so one order, a first, gives both (the header
  had c first, for func_00198BD8 alone). Where a's register still differs, the
  cause was around it, not in the helper: in func_001BBEB8 the next statement's
  `vel[i]` reload, right after the store, is allocated before the sum (shorter
  life) and takes vf2; the allocator's widened lifetimes (`fake_birth`) then keep
  the sum, whose life ends just before, out of vf2, and b takes it instead. Retail's
  order there is the reload, then the weight's store, then `acc[i]`: the operands
  of `MulAddX(vel[i], acc[i], Scalar(dt))` named in that order. In func_0017E3C8
  the registers came from the second weight's load instead (ScalarAtCall, see "A
  weight's address hoisted out of the loop"), with every argument inline. A tie ("+j" or "0") on a instead raises
  a's priority (its references doubled) above b's and swaps their registers.
- **A word stored from a reload.** StoreX(dst, a) is `sw` of a vector's low word
  with the vector as an `"r"` operand: the qmfc2 to the GPR is the compiler's, a
  reload, whose GPR is chosen after every pseudo has its register. ToBits' result is
  a pseudo of its own, which the local allocator gives the first free GPR (v0) before
  the loop's pointers have theirs. Retail's func_001DAA18 (qmfc2 a1 after its loop
  pointers in v0, v1, a0), func_0013B828 and func_00137FB0 store this way; ToFloat
  there gives retail's registers through the same reload (its f32 pseudo prefers an
  FPR), but then mtc1 and swc1. ToBits stays where retail's qmfc2 takes a register
  the local allocator gives (func_00160EA0's plane distances, the camera's ground
  lengths, func_001BBEB8's face distances: five matched uses).

- **Through the GPRs, "r" operands.** Where retail handles a vector or floats in
  GPRs (qmfc2 or lq, mfc1, the MMI pextlw/pextuw/pcpyld/pcpyud/prot3w, sq or qmtc2),
  the helper holds only the MMI instructions and takes and gives "r" operands: the
  compiler makes the moves, keeps one GPR copy for several reads, stores with sq
  where the value goes straight to memory and moves it to VU0 with qmtc2 where it is
  used there (wave 4, func_00141690 and func_00174E20 against func_00144AA0).
- **A float out of a GPR is a reload.** ToFloatY (prot3w) and ToFloatZ (pextuw
  r, $zero, a) give their float as "=r", so the mtc1 to an FPR is a reload, put in a
  GPR the values live there leave free: func_001B9940's a0, where an f32 or u128
  result of the caller's (local-alloc'd before the values across the branches) takes
  v0. x is ToFloatMoved of the same GPR copy. The lane tests of retail's zero checks
  (SetColliderVelocity, SetColliderSpin, MoveDriftingEffect,
  ApplyColliderPendingImpulse) are a boolean set with `li 1; bc1tl`, as before.
- **Three floats are one sequence.** FromFloats is mfc1 x3 with pextlw and pcpyld in
  one asm, the floats as "f" operands: separate mfc1s are hoisted by sched1 and change
  the FPRs the floats take (func_00144AA0). Its result has a slot of its own (two
  stores in retail: the caller's local and the slot; func_00184B58, func_001C41A0).
  Its w is z's sign extension.
- **The splat turns its input in place.** All ten of retail's splats are `pextlw t,
  t, t; pextlw r, t, t` right after the compiler's mfc1 into t, r being t or another
  GPR: Splat's first pextlw writes its "r" input's register (the float's GPR copy,
  which dies there). It has no slot: retail stores it once, where the C put it.
- **The 3x3 transpose is two sequences.** func_00188B48 (near miss) does
  pextlw/pextuw of rows 0, 1 and of row 2 with $zero, then pcpyld/pcpyud/pcpyld; retail
  schedules the -1.0's lui/mtc1 between the two, and one asm per instruction is
  scheduled otherwise. Vu0::Transpose holds the two.
- **A constant moves to the second operand of min.s and max.s.** fold puts the
  constant of `c >? x` second, so retail's `max.s f1, f21, f1` (the constant first,
  the result in x's register) comes from a float variable holding it, and the value
  assigned before (`score = x - r; score = eps >? score`, func_00181ED0).
  Between two values, retail's operand order and result register come from an inline
  function: func_001A6788's `min.s f1, f0, f1` (the speed, then the maximum, into the
  maximum's register) is `MinF(speed, max)` returning `a <? b`, and func_001A48C0's pose counts
  (poseA loaded first, `max.s` with poseB first, into poseB's register) are `MaxF(a, b)`
  returning `b >? a`; neither order of a bare `<?` or `>?` gives them (night-close6, 2026-11-08).
- **A literal is the function's own.** A float a function reads from .rodata (FLT_MAX)
  is the literal its C writes, emitted after the function's earlier literals: a
  defined `extern const` there is folded into a second copy, which in a whole file
  grows its .rodata past the next file's (the link failed on func_00141690). The
  definition or INCLUDE_RODATA line goes when the function becomes C (func_00141690,
  func_0019E220, func_001C41A0, func_00181ED0).
- **Inline locals and later locals share slots.** A local declared after a block or an
  inline function call ended reuses its slot (func_0019F620's scale over the view
  test's Scalar, func_001DF700's message over its direction), where locals declared
  first come first in the frame.
- **The copy within a block.** Vu0::Copy (vmove.xyzw) gives retail's vmove in
  func_00141D88's loop (the length taken of the copy, the division of the original),
  but in func_00141D88 retail's store and length use the copy where NormalizeOr's one
  vector is used for both. func_001CB3D0 matches with it: the difference kept, its Copy
  stored and dotted in case 0, the original dotted in case 1 (retail's vmove vf3, vf2).
- **A constant hoisted out of a loop in retail's order.** loop.c moves a loop's constants in
  the order it finds them; where retail's order differs (func_001821B0: 1728.0 before 16.0),
  the one that comes first is a named local inside the loop body.

- **A length compared is ToFloatMoved.** Where retail's `mtc1` of a length (or a squared
  distance) comes straight after its `qmfc2`, before an unrelated store or load that ours puts
  between them, the qmfc2 is the compiler's: ToFloatMoved, and NormalizeOrMoved for the
  normalisation with a fallback (func_001C96D8, func_00189C28, func_001ED908, func_0012FB68,
  func_001A9AE8, 2026-11-08). In func_00187A88 it gives the order but moves the VU0 registers;
  there both moves are one sequence, Vu0::ToFloatNow (qmfc2 and mtc1 through a GPR the
  compiler picks), which keeps the stack store sched2 would otherwise put between them out.
- **A float's place in a prototype.** The curves' slot 0 takes its floats before the out
  pointers (PositionCurveEval after the mode, WeightCurveEval right after the owner): their
  callers set $f12 and $f13 before those argument registers (func_0011FC90, func_0011F6B0,
  func_001A95D0's time third), and every matched caller keeps its bytes.

- **Wave 6 findings (night-vumid2, 2026-11-08).** (1) A float read from a vector's lane for a
  compare and then again after the arms (func_0017D248's `b.x`) is `x = b.x` written *after* the
  arm's other statements in each arm: assigned first, the allocator gives it f1 where retail has
  f0. (2) The idiom `lq v0,0(sp); qmtc2 v0,vf3` of a vector stored by pieces and then normalised
  (func_0017D248, func_001E31F0) is the vector as a `Vu0::Vec` value (`Vec::Of(a)`, Length, DivX,
  ToFloat); a plain u128 or Q(a) read gives lqc2. The normalisation's length survives the if in
  a VU0 register only with ToFloat (the compiler's own qmfc2 of ToFloatMoved is shared and the
  length is moved back with qmtc2). (3) A loop of `Vec` values (func_001BC978, func_001CC490) is big
  enough for loop.c to leave its row address and list index alone; the same loop of u128 values
  gets them reduced to induction variables. (4) A walk's `GliderListFrame`-style
  frame shares the slot of a vector declared in the first arm of the function (declare that
  vector inside the arm), and the outputs of a call declared after the weights' statement share
  the weights' slot. (5) A callee that takes a float and a flag is declared float first when
  retail sets $f12 before the flag. (6) The rotation curves' slot 1 is the angles of the same
  evaluation (the kind 2 blend calls it), not a second evaluation: RotationCurveGet.
  Still open: the `lw X,0(X)` (the weight's bits loaded into the dying pointer's register)
  before a qmtc2, which eleven unmatched functions have and no C form here gives
  (func_00120700, func_00120470, func_00122DE0 and eight more).

- **Untouched pass (night-untouched, 2026-11-08).** (1) A failure path that two tests share,
  written once with a goto, lets CSE follow the first test's skip into the code after it and keep
  an index product there; written twice (cross-jumping merges the copies after allocation), the
  index is computed afresh as retail does (func_00203FD0's slot offset). (2) One variable for a
  list node and for an attachment read elsewhere in the function gives retail's single saved
  register for both (func_0012EBD8); one record pointer shared by three loops likewise
  (func_00177990). (3) `n < sizeof(recs) / sizeof(recs[0])` is retail's sltiu bound of a signed
  count. (4) Both stores to a vector local through Vu0::Set keep its address out of loop.c's
  invariants, so a call forms it afresh (addiu) instead of taking a matrix local's hoisted copy
  at the same offset (func_0013D278). (5) A helper that reads its vector through a pointer twice
  gives retail's reload after a Scalar store for a buffer entry and its vmove copy for a stack
  local (func_00154370's AddLimited). (6) The runtime's swap macro (do-while) is what its heap
  sort's loops need; a plain block of the same statements is not (func_001FF1E0).

- **Size pass (night-size2, 2026-11-08).** (1) A product's second matrix read by index through a
  pointer to its rows (`const u128* q = (const u128*)&b; ... q[1]`) keeps that pointer a register of
  its own: retail's `lqc2 0xD0(s0); addiu v0, s0, 0xD0; lqc2 0x10(v0); lqc2 0x20(v0)`, each row
  after the stores of the row before. Through `Vu0::Q(b.r[i])` the row's address is the
  reference parameter of an inline function, a pseudo whose `(plus p 16)` CSE folds into the
  object's offset (`fold_rtx`); an address written in the load itself stays as it is
  (`find_best_addr` keeps an equal-cost address), and only the first row, `(mem p)`, takes the
  object's offset. mul_rotation.h's MulRotationRowsIndexed, MulRotationRowsXIndexed and
  MulRotationIntoRot (the result written through the object, `o->rot = r`, where a `Mat02*` to
  the matrix stores through a register of its own) matched func_001225D0, func_001EBDD0,
  func_001A11C0, func_00125440 and func_001B8148; seventeen retail functions have the pattern.
  (2) A vector added in place and then scaled (func_001B8148's spin) is read again from memory
  for the scale when the sum is a struct store (`*(Vu0::Vec*)&v = Vu0::Add(...)`); a `Q()` store
  keeps the first read. (3) A struct whose inline member clears it (`Clear()` calling FillMemory
  on `this`) gives retail's address formed again at each use, where `= {}` or a plain array keeps
  it in a saved register (func_001E2438). (4) A field read as ld then `dsll 8; dsra32; andi 3` is
  an int bit-field read into a local (placed_object.h's bits24, func_00125138); `== 2` on the
  field itself folds into a mask compare. (5) A float constant used across calls that retail
  holds in a saved FPR from a join block on is a local assigned in that block (func_001BC0E0);
  assigned at the top, the constant is propagated into each use. (6) With func_001BC0E0's C
  (EXACT alone), our assembler padded StartSoundEffect's copy loop with five nops in the whole
  file's build; the cause was its fragment breaks, not the code, and tools/short_loops.py now
  pads short loops as the original did (see "The assembler matters"): file_1B7968.cpp places.

The sequences still without a helper: a float stored as a quadword (func_00191AC8,
func_00118CF0: mfc1 once into a saved GPR, then per use a copy (`daddu`) and sq,
read back with lqc2; an asm `sq` of an "r" float gives the sq straight from the saved
GPR, without the copy). The rest have helpers: the Q-register forms (Sqrt, DivX,
Length, NormalizeOr), the matrix forms (Transform, Transform4, RotateRows and
RotateUntied, RotateTransposed, MulTransposed, Transpose), the weighted sums (MulXSum,
MulXSum3, MulXSum4, MulAddX, MulAddX2), the dots (Dot, DotXY), the view test
(PlaneSigns, Ones), the cross product, Min and Max, the copy (Copy), and the GPR forms
(ToFloatMoved, ToFloatViaBits, ToFloatY, ToFloatZ, FromFloats, Splat, ToBits, StoreX). The assembler takes
`vsqrt` (the disassembler prints it as a `.word`).

### A microprogram's interface (vcallms)

func_0013A498 and func_00185150 start VU0 microprograms with `vcallms`, which reads fixed
registers ($vf21..$vf31, $vi2..$vi4) that the compiler, allocating only $vf1..$vf15, cannot
pick. include/vu0.h has one-instruction helpers on named registers, as templates on the
register number (the assembler takes `$vf%1` from an "i" operand): LoadVf<N> (lqc2),
StoreVf<N> (sqc2), MoveToVf<N> (qmtc2.ni), MoveToVi<N>/MoveToViWait<N> (ctc2.ni/.i),
ReadVi<N>/ReadViWait<N> (cfc2.ni/.i; ReadViWait<0> is the game's wait), CallMs<addr> (vcallms)
and VuNop (vnop). All are volatile with a "memory" clobber, so they keep their order with each
other and with the loads and stores around them. The C around them sets and reads the registers in
retail's order. A float the caller passes in a GPR with a 128-bit `por` is a u128 parameter
(MoveToVf takes it, ToFloatMoved reads it). Neither function matches yet (nonmatching/): the
bodies are retail's apart from register allocation.

### func_00185150's vi block was one non-volatile asm (2026-11-10)

Two of func_00185150's last differences come from the volatility of its four one-instruction
helpers (ctc2.i $vi3, ctc2.ni $vi4, cfc2.ni $vi2, vnop), and both point to one asm statement with
an output, which GCC does not make volatile (stmt.c makes an asm volatile only when it is declared
so or has no outputs):

- **sched1's dependents.** A volatile asm is a full barrier (haifa-sched.c, ASM_OPERANDS with
  MEM_VOLATILE_P), so the three field loads retail has before ctc2.i must be read before it. With
  separate asms the count's load has three forward dependents (its own ctc2.ni through flow's
  LOG_LINK, the ctc2.i barrier, the block's jump) against two for fE's and kind's, and
  rank_for_schedule, after equal priority and weight, prefers more dependents: count comes first
  in every source order (tools/permute.py tried all six). Only an asm that consumes fE and count
  together ties them, and INSN_LUID then gives retail's fE, count, kind.
- **reorg's redundant insn.** resource_conflicts_p counts any insn with `volatil` set as a
  conflict, so redundant_insn never looks back across a volatile asm. The join's `t7 = i + 1`
  (PRE's copy at the switch's end) is then not redundant with the identical insn in the earlier
  bnez's delay slot: the default arm's `b` takes a copy, and fill_eager_delay_slots lets the case-0
  `beqz` steal it (steal_delay_list_from_fallthrough). Retail's two empty slots need no volatile
  insn between that bnez and the b.

With `__asm__("ctc2.i %1,$vi3; ctc2.ni %2,$vi4; cfc2.ni %0,$vi2; vnop" : "=r"(mask) : "r"(fE),
"r"(count))` and a plain `switch (grp->kind)` (the kind's load is then free to move up), both match
(build/swarm/w11-185150/h4.cpp, scratch only). What is left is a global-alloc tie: three fewer loop
insns than the separate asms move the light table's address (3 refs over a 134-insn life, doubled by
its REG_EQUAL constant) ahead of the out-count pointer (2 refs over 90). A four-instruction asm used
by one function is not a project helper (AGENTS.md), so the near miss keeps the separate helpers
until that is decided.

## The MMI and system helpers

The 37 `inline` functions whose special instructions are MMI or system ones, not VU0
(2026-11-08, build/swarm/lead/night/mmi.tsv), were matched as the VU0 ones were: plain C around
shared helpers.

- **The game's MMI needs no header of its own.** Its 19 functions use pextlw, pcpyld, pextuw
  and prot3w only in the GPR forms include/vu0.h already has: FromFloats (mfc1 x3, pextlw,
  pcpyld) for a vector built of three floats, Splat (pextlw twice) for one float in all four
  fields, and ToFloatMoved, ToFloatY (prot3w), ToFloatZ (pextuw with $zero) for a vector's lanes
  in a GPR. No include/mmi.h: none of pmaxw, pminw, por, qfsrv, mfsa, plzcw or a multu read
  through hi is in game code's C. Matched with them: SetWorldGravityZ, BuildUniformScaleAboutPoint,
  ResetFlagTable, HandleModeColliderActivation, ResetTintBlendColliderOrientation,
  HandleModeWalkerActivation, func_00125BF0, SetRandomEffectSpin, InitIdLinkedObject,
  LaunchContactListObject, SetRangeRecordPosition and SetRangeRecordDirection, InitPlayer,
  MatrixToAxisAngle.
- **include/system.h** holds the system instructions, as static inline functions (C and C++
  include it: the libraries have .c files), each one volatile asm, as AGENTS.md allows hardware
  access to be: retail never schedules anything across them.

  | Helper | Sequence | Form | Users |
  | --- | --- | --- | --- |
  | `Sync()` | `sync` | no operands | DisableInterruptCause, EnableInterruptCause, DisableDmaInterrupt, EnableDmaInterrupt (after the system call), DefineDrawEnvironment (at the end), func_00210C38 (before starting the DMA) |
  | `SyncAndEnableInterrupts()` | `sync; ei` | no operands | the ends of the interrupt handlers WakeDiscWaiter, WakeCardWaiter, func_001F89F8, HandleGsFinish, HandleVblankStart, func_0015E6A8 (and the near misses HandleCommandInterrupt, func_00210F18) |
  | `ReadCop0Status()` | `mfc0 r, $12` | `"=r"` u32 | the four interrupt wrappers of system_calls.cpp, RefreshPadFrames |
  | `ReadCop0Count()` | `mfc0 r, $9` | `"=r"` u64 | ResetGameClockTick |

- **The status bit in its own register.** Retail's `mfc0 s0, $12; and s0, s0, v0` is a variable
  given the register and then masked in place: `u32 enabled = ReadCop0Status(); enabled &=
  0x10000;`; the mask written in the initialiser gives `mfc0 v1` and `and s0, v1, v0`.
- **Count is a doubleword.** Retail stores `mfc0`'s result with `sd` at once; mfc0
  sign-extends, so the helper's result is u64 (a u32 assigned to the u64 global adds the
  zero-extension).
- **Sibling calls.** The libraries' compiler (2.9-ee-991111, above) turns a call at the end into
  `j` after the epilogue: RefreshPadFrames and func_00210C38 end with `j EnableInterrupts`,
  plain C.
- **A constant set again before each call is an inline function's.** Retail sets the 1e-4
  tolerance of AreFloatsNearlyEqual (lui, ori, mtc1 $f14) again before each of a vector's three
  tests; the constant written at each call is shared by CSE in a saved FPR. An inline function
  that passes it (range_record.cpp's IsNearlyEqual) gives retail's code: each inlined body is a
  block of its own to CSE.
- **Tails merged by cross-jumping.** Code that two arms share after the registers are allocated
  is merged by jump.c's cross-jumping, leaving in each arm only what differs: MatrixToAxisAngle's
  sign fix of the largest axis z is written in both arms of the x test (retail negates x from the
  register both arms hold), and func_001478F0 (near miss) evaluates its curve in each arm, which
  leaves the arms' own `c[0]` loads in them, as retail's.
- **Data a DMA fills is volatile.** The command channel's receive buffer (HandleCommandInterrupt,
  near miss) is read with `lbu` then `andi 0xff`: a volatile byte, whose zero-extension combine
  leaves.
- **Statement order is store order.** In InitPlayer, InitIdLinkedObject and ResetFlagTable the
  stores of constants come out in the C's order (tools/permute.py found InitPlayer's last seven);
  DefineDrawEnvironment writes each register's address before its value, as retail stores them.
- **The assembler and a macro in a delay slot.** A store to a constant address whose low half is
  negative (`sw $3,0x1000b000`, a macro of lui and sw) that the assembler moves into a `jal`'s
  delay slot came out with the lui's carry lost (`lui at, 0x1000`, where retail has 0x1001; the
  same store outside a delay slot was right). The build corrects it: tools/volatile_slots.py, which
  already writes the `lui $at` / `jal` / `sw` of a volatile store into the call's slot, writes a
  constant address's high half itself, with the carry (`lui $1,4097`, `sw $3,-20480($1)`), instead
  of `%hi`/`%lo` of the bare constant, which this assembler takes without the carry. A symbol
  keeps `%hi`/`%lo`. Only the stores that tool moves into a slot are affected (func_00210F18, now
  matched).
- **Left as they are.** func_001F71D0 is the only function with an inline `syscall` (`li $3,
  -0x2F; syscall`, its result moved from $v0), so it has no helper (a sequence one function
  alone has). func_001FAA00 keeps its loop counter in $t9 across calls, which the compiler never
  does with a caller-saved register: it was written with a register variable or by hand, and is
  not C to match as it stands; its `mtc0 $6` and `sync.p` (the TLB's wired count) occur nowhere
  else.

## Reloads and stores

When retail reads a word again that the compiler could have kept, or keeps one
the compiler reads again, the cause is in how each memory reference is written
(2026-11-07, func_001590A0):

- **A store to a stack struct's member makes the compiler reload.** GCC 2.95
  (without `-fstrict-aliasing`) marks each memory reference as a structure's
  (`a.f`, `p->f`, an aggregate) or a scalar's (`*(T*)((u8*)&a + o)` of a
  scalar T, which is not a member access), and assumes that a scalar reference
  at a fixed address (the frame plus a constant) never overlaps a structure's
  through a varying pointer (alias.c, `fixed_scalar_and_varying_struct_p`). So a
  store into a stack record through a byte offset leaves CSE free to keep
  `m->flags` in a register, and a store to `rec.field` does not: the compiler
  reads `m->flags` again after it. func_001590A0 reloads the message's flags
  (`lw v0, 0(s2)`) before every test after a store into its copy of the
  0x200-byte record: one store rewritten as a member access brought that
  reload back, and the record as a struct written member by member gave every
  one. The same rule reloads a field read twice around a member store
  (`rec.f1D4 = m->scale; rec.f1D0 = m->scale;` reads it twice, retail's
  `rec.f1D4 = rec.f1D0 = m->scale` once). It is not a call or a pointer: the
  offset store was through a pointer as well. It does not reach a value stored
  and loaded back with nothing between (func_001C8920's `sqc2`/`lqc2`): with no
  store between them, CSE forwards the stored value whatever the type.
- **An inline function's argument goes straight into the call's register.**
  `FillMemory(&frame, 0, 0x60)` puts `&frame` in a pseudo the later uses share
  (`move a0, s0`, s0 set before the call); called from an inline member
  (`frame.Clear()`, `FillMemory(this, 0, sizeof(*this))`) the address is
  computed into a0 and again into s0 after the call, as retail's func_001590A0.
- **A word loaded for a qmtc2 is the qmtc2's own operand, loaded by reload.**
  Retail loads a word into the register that held its address (`lw s0, 0(s0)`,
  `lui v1; lw v1, %lo(D)(v1)`) before a qmtc2 in about 25 functions, and where the
  address lives on, into a register no allocation explains (`lw a0, 0(s0)` with
  v0 free) (2026-11-08, func_00120700, func_001D4698, func_001DF600). Both are
  reload's: push_reload (reload.c) gives an input reload the register of a REG
  that dies in the insn and is mentioned only in that operand, and otherwise
  allocate_reload_reg (reload1.c) takes the spill registers round-robin from the
  last one used. So the qmtc2's operand was the memory reference itself when
  reload ran. Nothing else gives either register: local allocation tries each
  quantity first with a lifetime one insn longer at each end (INSN_SCHEDULING,
  block_alloc), so a load's result never takes the register of the address
  that dies at the load, and ties a result only to a REG operand (a MEM's
  address only under 'p'); global allocation frees a dying input before the
  output is set (a word loaded before an if and used after it takes its
  address's register), but func_001EB698 is one basic block; and no pseudo is
  spilled where nothing else wants the registers. A plain "r" never leaves the
  memory reference there: expand_asm_operands copies an operand that fails its
  constraint into a pseudo, combine and update_equiv_regs put one back only if
  check_asm_operands accepts it ("r" takes no MEM), an inline function's
  argument is copied into a register (process_reg_param), and combine turns
  `(subreg (mem))` into a narrower MEM. A constraint that admits memory before
  reload and not in it does: "rV" ('V', non-offsettable memory, takes any MEM in
  asm_operand_ok; reload finds the reference offsettable and loads it into a GPR
  for 'r'), as "<r" and ">r" do (but those form a global's address with addiu
  and load at 0, where "rV" keeps retail's `lw X, %lo(D)(X)`). Every plain
  letter tried (r d y b e t; m o g X R) and "r,m" with `!` or `?` gives v0 or
  prints the MEM. Vu0::FromFloatAt passes the float's bits as "rV": the five
  functions that matched with "r" still do, and func_00120700, func_00120470,
  func_0013D0B0, func_0014F270, func_00150008, func_00172EE0, func_0018E040,
  func_001A31A0, func_001D8BD0, func_001D4698 and func_001DF600 match with it
  (and func_001DF520, whose callee takes the caller's own a1). What the
  original wrote is not known; this reproduces what it compiled to.

### The reload register's round robin (func_001E31F0)

Which GPR reloads a spilled pseudo is not decided at that insn alone
(reload1.c, read 2026-11-08 for UpdateOnOffCameraController):

- **The spill registers are the function's, in register order.** Each insn
  that needs reloads picks spill registers from `order_regs_for_reload` (the
  hard registers no live pseudo holds there); finish_spills then gathers every
  register spilled anywhere into `spill_regs`, sorted by number (v0, v1, a0,
  ..., then FPRs and VU0 registers), and gives each insn all of them that no
  pseudo live there occupies.
- **allocate_reload_reg rotates.** It starts the search one past
  `last_spill_reg`, the index of the register the previous reload took, so
  consecutive reloads walk v0, v1, a0, ... and wrap. A spill register that one
  insn anywhere in the function needs shifts the choice of every reload after
  it in the rotation: with a0 in the set, the reload after one in v1 takes a0;
  without it, it wraps to v0.
- **func_001E31F0.** The spilled `limit = object->f41C` was reloaded into a0
  where retail uses v0, and every reload after it was shifted (lw a0/v1,
  260(sp) for the spilled camera, the qmfc2 temporaries). The cause was 400
  instructions later: the stick from FromFloats (an asm with an "=&r" output)
  went to a VU0 register, because its three "j" uses (Length's two operands,
  DivX's) outweigh the one "=&r" in regclass, so the asm's output needed a GPR
  reload and a0 became a spill register. Retail keeps the stick in a0 (qmtc2
  a0 to vf1 and vf3 before each use). Copying the value through a Vu0::Vec
  local and normalizing the Vec values, `n.q = FromFloats(...); *(Vec*)&stick
  = n; *(Vec*)&stick = NormalizeOr(Vec::Of(stick), Vec::Of(g_unitXVector))`
  (file_1793C0.cpp's form), gives the pseudo equal costs (`TI_REGS` in the
  .lreg dump), global-alloc puts it in a0, and no reload needs a0. The .greg
  dump's `Spilling for insn N. / Spilling reg R.` lines list every insn's
  spill registers: one `Spilling reg 4` in a function shows where a0 came
  from.
- **Fields against fixed stack slots.** The same function read its camera
  parameters (the 0x90 bytes at object+0x2F0) through an `f32*` as `block[n]`.
  Such a MEM is not marked as a structure's (no `/s` in the dumps), so sched2
  could not move the reads above the stores to the address-taken
  `placeDist`/`placeHeight` (scalars at fixed frame addresses), and jump2
  cross-jumped the identical tails of two switch cases. Read as fields of a
  struct (`block->f58`), the MEMs are `mem/s` and
  `fixed_scalar_and_varying_struct_p` separates them from the scalar slots:
  sched2 then hoists the reads as retail does, and every case, written in
  source order, matches.
- **func_001F2840: the order of the insns decides the rotation (2026-11-08).** In the else
  branch, retail reloads the spilled mesh into v0 for `mesh->f68` and the Transform's 1.0 into
  v1 (mfc1), ours the other way. Ours reaches the qmtc2's reload first, after the case blocks'
  VU0 reloads (vf3) left the rotation past the GPRs, so it wraps to v0 and the mesh takes v1.
  The mesh's load came after the qmtc2 because sched1 kept it behind the Scalar slot's store
  (`[sp+96]`, neither MEM flag) that it may alias. Reading the pointer before the Transform
  (`void* skin = mesh->f68;` then `if (skin != 0)`) puts the load first in the insn order, so
  it no longer depends on the store, takes v0 in the wrap, and the qmtc2 takes v1: retail's
  registers and its order (the slot store in the branch's delay slot).
- **What the rotation shows when the final code is the same.** In the same function's vertex
  loop the three Length cases' qmfc2 reloads are v0, v1, a0 in ours and v1, a0, v0 in retail
  (a1, holding `&obj->v140` across the loop, is skipped), and every reload after the loop is
  one step behind too (mesh in a1 for v1, obj in v0 for a1). Before them ours and retail agree
  (the loop head's mfc1 a0). An offset of exactly one with v0 free means retail allocated one
  more GPR reload, landing on v0, between the loop head and case 1, and no instruction of the
  final code shows it: the dispatch (`lw v0, 32(s4)` for the mode) and the case -1 block are
  the same bytes in both. A candidate is a reload whose value an insn already had, such as a
  pseudo with a REG_EQUIV memory left without a hard register, whose load reload then makes
  in its use's reload register (the same `lw v0`). Ruled out: the conversion helper of each
  case (ToFloat, ToFloatMoved, ToFloatNow, ToFloatViaBits: one helper for all three changes
  nothing, mixing them is not plausible), the weight stored once after the switch, default
  apart from case -1, the matrix read as rows, `Vec::Of(p)`, `d` declared outside the loop, and
  the mode read into a local before the loop (it takes a1 and moves &obj->v140).
- **The hidden reload was a case that cross-jumping deleted (func_001F2840, matched
  2026-11-09).** Reload allocates every block that exists when it runs, and jump2's
  cross-jumping (jump.c, after reload) deletes a block whose insns, registers included, equal
  the tail of another block that jumps to the same place. Retail's switch had case 0 as a
  block of its own, written before case 1 (`case 0: d = Length(p); goto curve;`), and case 3
  its own copy (`p.x = 0; d = Length(p); goto curve;`) instead of falling into case 0. Reload
  gave case 0's qmfc2 v0 (the extra reload), cases 1, 2 and 3 v1, a0 and v0; case 3's tail
  then equals case 0's block, cross-jumping keeps one copy, and the jump table's case 0 points
  into case 3 after its `sw zero`. The final code is the same as the fall-through form's, but
  the rotation is retail's from there on: every difference after the loop head goes. When
  reload's rotation is one step off with no visible extra reload, look for code the original
  repeated that jump2 merged. The skin pointer's early read (above) is no longer needed since
  Vu0::Scalar's slot became MEM_SCALAR_P: `if (mesh->f68 != 0)` read at its use matches too.

## Loops

When retail's loop keeps its constants and multiplies its index each time round (`li 0xD0;
mult` for an array of 0xD0-byte entries, the constants 0, 1.0 and 2pi loaded inside), yet its
top is still aligned, the loop optimiser ran and chose to move nothing (2026-11-07,
func_00140258, func_001F2EF0, func_001F3408):

- **A big loop is left alone.** GCC 2.95's loop.c moves an invariant out of a loop only when
  `threshold * savings * lifetime >= insns`, where `insns` counts the loop's real insns at the
  loop pass and `threshold` is `(1 + n_non_fixed_regs)`, doubled when the loop makes no call
  (scan_loop, move_movables; strength_reduce has the same test with `3 +`). With the files' flags
  that is 80 for a loop with a call and 160 for one without (measured: a loop with a call moves
  its constants at 79 insns and not at 81; without `-mvu0-use-vf0-vf15` the limit is 65, the
  other SN builds give 80 too). A constant used once (lifetime 1) stays in a loop of more than 80
  insns, and the index's `li 0xD0` with it; then `i * 0xD0` is not a multiple of an invariant, so
  it is not a giv either and nothing is strength-reduced. A value used farther apart (1.0 in
  three subtractions, an address used twice) is still moved, as retail moves it. The loop notes
  stay, so the top is aligned. The pass runs twice (`-frerun-loop-opt`): both counts must be over
  the limit. cc1plus given `-dL` writes the loop pass's dump next to its input (`unit.ii.loop`):
  each loop's count and each decision ("not desirable", "moved to", "reduced to").
- **What the count includes.** The insns of the loop when loop.c sees it, before combine and the
  register allocator, so things that never reach the output count: flow's `(use (const_int 0))`
  after a call that ends a basic block (gcse puts them there), copies into argument registers,
  and copies of 128-bit values. Retail's loops are bigger at this point than the same code
  written with u128 values: ours had 53 and 78 where retail needed more than 80.
- **The vectors were values of a struct type.** A vector held in a struct of one u128
  (`Vu0::Vec`, include/vu0.h) and passed and returned by value through inline functions compiles
  to the same code, but GCC copies it from pseudo to pseudo at each inline call (four to six
  movti a call), copies CSE leaves for the allocator: func_001F2EF0's loop goes from 53 to 94
  insns and keeps its constants and multiplication, func_00140258's from 78 to 86 and is EXACT,
  func_001F3408's is 194. A Vec temporary in a condition makes the front end compute the
  condition as a value (its cleanup point) where retail branches: func_00140258's distance test
  is Vu0::Distance, an inline function that keeps the Vecs inside it.
- **Vu0::Vec is the convention for new VU0 code** (decided 2026-11-08). The
  original held its vectors as values of a struct type passed through inline
  functions, as the loops show: a function matched from now on writes its
  vector values
  as Vu0::Vec, and uses the u128 helpers only where retail's code shows the
  difference (a loop under loop.c's limit, a register a Vec copy moves). The
  functions already matched with u128 values are rewritten to Vec only where
  each still matches, function by function, never as a sweep that changes
  bytes.
- **A loop entered in the middle is not a loop to loop.c.** func_00140258's comparison of its
  found objects with the old list (`for` with a `break`, whose first test jump.c duplicates
  ahead of the loop) is "ignored due to multiple entry points": nothing in it is moved or
  reduced, in retail as here.
- **Locals whose address is taken later go last.** A float whose address is first taken after
  its declaration (`f32 sn, cs; ComputeSinCos(x, &sn, &cs);`) is kept as an ADDRESSOF and given
  its stack slot only when purge_addressof runs, after every temporary of the function: retail's
  sine and cosine sit above the weight slot (func_001F2EF0 at 0x10, func_001F3408 at 0x70), which
  an `f32 sc[2]` (placed at its declaration) does not give.
- **Not yet reproduced.** After ComputeSinCos both oscillator functions move the cosine into its
  VU0 register before the sine's `mfc1`, which then takes v0; ours does the sine's `mfc1` (a
  reload) first, into v1 (nonmatching/func_001F2EF0.cpp, func_001F3408.cpp).

### A `for` over a call's count, and a zero named in the body (func_00149190)

Measured with `-dL` dumps (2026-11-10, the armed notifier's push loop, src/main/state_notifier.cpp):

- **The pretest on the call's result.** Retail's `blez v0` tests GatherObjectsById's result
  before `move s2,v0`. A `do { } while (p++, --n != 0)` under `if (n > 0)` tests n's own
  pseudo (`move s2,v0; blez s2`); `for (s32 i = 0; i < n; i++)` with `found[i]` tests the
  value and lets loop.c's second pass reduce `found[i]` to a pointer and count the copy of n
  down (retail's `addiu s2,s2,-1; bnez s2`).
- **The zero.** Retail's `mtc1 zero,$f20` sits after the pretest, so it was moved out of the
  loop: `f32 zero = 0.0f;` at the top of the body (life 150 in pass 1, moved first). Before the
  `for` it is set before the call; a literal `0.0f >? push.z` stays in the loop (life 1).
- **The loop's size.** The body's vectors as Vu0::Vec values make pass 1 109 insns and pass 2
  97, so 250000.0f and 99 (life 1) stay in the loop as retail's; with u128 values (87 and 76)
  pass 2 moved both into saved registers, and the weight's ScalarAt (a reference, life 7) moved
  D_00261BE0's `%hi`. The weight is `Vec k = Vec::ScalarAtValue(D_00261BE0);` named before the
  product: its slot is stored before `lqc2` of the velocity and the product takes its register.
- **Slot order.** The message is declared in the listener's `if`, as the file's other senders
  do: the weight's temporary then gets the slot before it (112, the message 128).

### An index loop.c leaves alone: a giv's benefit against a big loop (func_00154370)

Matched 2026-11-10 from the `-dL -dl -dg` dumps. The impulse distribution's last loop (each
group's parts, `list[i]` with `list` from its spill slot at 96(sp), `i` counted up in s4 against
the count in s8) is retail's only when loop.c reduces nothing in it:

- **The test.** strength_reduce leaves a giv when `lifetime * threshold * benefit < insns`
  (loop.c, the "not worth while" line of the `.loop` dump), with threshold 81 for a loop with a
  call and the benefit less the add it would cost (4 per biv increment). `list[i]`'s address is a
  DEST_ADDR giv of lifetime 1 and benefit 7 - 4 = 3: it stays only in a loop of more than 243
  insns at the loop pass, in both passes. Once it stays, the biv is used in it, so the loop is not
  reversed either (retail's `addiu s4,1; slt; bnez`, not a countdown).
- **The size.** Written with u128 helpers the loop is 122 insns (`list[i]` becomes a walking
  pointer and `i` a countdown); with the parent arm's vectors as Vu0::Vec values 237; with
  AddLimited (the inline that adds a vector cut to a limit) over Vec values as well, 245 and 243+
  in pass 2. Every part of the inline as Vec is needed: any of its three statements left as u128
  stays under 243.
- **The weight named before the vector.** In the Vec form, `MulAddX(a, Vec::Of(*v),
  Vec::Scalar(..))` expands the nested Of first (inline arguments, two passes), so the load of
  `*v` precedes the weight's slot store and CSE reuses the dot's load; retail reloads `*v` after
  the slot store where `v` points into a part's buffer (no known base) and keeps it (vmove) where
  it is a stack local. `Vec s = Vec::Scalar(..);` named before the MulAddX gives both.
- **One counter for the two loops over the groups.** The first loop (`bufs[j] =
  AllocateZeroedBackMemory(counts[j] << 5)`) and the outer last loop share `s32 j`, declared at
  the top: j's pseudo then crosses the first loop's calls, so global-alloc gives it a saved
  register (s0, free once the first loop's countdown is dead) instead of v1, as retail. Then the
  group's count, buffer and list read in that order (count first, list last) for sched1's order
  of the three loads.

The two functions before it in the file (2026-11-10):

- **func_00153780 (matched).** Three source forms, each read from retail: the item's axes
  stored through the array pointer walked in the `for` header (`for (s32 i = 0; i < a3; i++,
  axes++)`, `Q(*axes) = ...`: retail's `addiu a0,s7,16` spilled at the top and `lw s7` at the
  bottom is PRE's copy of `axes + 1`, as for a counter, where `axes[i]` gives an indexed
  store); the zero written at each use (`Q(out[j]) = Vu0::Zero();`), which loop.c moves to the
  preheader after the entry test as retail (a `zero` local before the loop is scheduled into the
  prologue); and the early-out first (`if (body == 0 || body->f4BC < 0) zero; else if (end 0)
  ...; else if (end 1) ...; else zero;`), whose two zero stores reload into the same register
  and cross-jump into one tail. The first loop reads `contact->end[i].body` by index, not
  through a walked `end` pointer, for retail's s4/s5. With the axes walk, a1 keeps s7 and the
  contact is spilled, as retail.
- **func_001536C8 (near miss).** The dot over Vec values gives retail's size (the count reloaded
  for the row's index, cse_around_loop as in func_001C4D60); only local-alloc's order of the
  owner pointer and the count chain differs (a0/v1 swapped).

### Which pass moves an invariant: the preheader's order (func_001971B8)

The preheader holds what loop.c put before the loop's start, in the order it put it there, and
sched1 keeps that order when the insns tie (all alu, priority 1, one set each: INSN_LUID decides).
Each pass emits its moved invariants (in their order in the loop) and then the start values of
the givs strength_reduce reduced, all before the loop's start; so what the second pass
(`-frerun-loop-opt`) moves comes after the first pass's givs.

- **The gauge collider's best-target search.** Retail's preheader is `addiu s4,sp,432` (the
  address of a local, moved by pass 1), `move s2,sp` (the reduced `&list[i]`, started by pass
  1), then `lui s6` (the high part of the angle limit D_0026A82C). Ours moved the `lui` in pass
  1 too, so it came before `move s2,sp`. The dump (`-dL`) showed two causes: the high part's
  lifetime was 11 luids, because `D_0026A82C < fabsf(WrapAngle(...))` expands the global's
  address before the calls; and the loop had 70 insns in pass 1, 60 in pass 2.
- **Retail's form: lifetime 1, and a loop of 81 to 90 insns in pass 1.** Written
  `fabsf(WrapAngle(...)) > D_0026A82C` (the same `c.lt.s` with the constant first) the `lui` is
  expanded right before its load (lifetime 1), so moving it needs `80 * 1 * 1 >= insns`. With
  the loop's vector statements as Vu0::Vec values (the project's convention, whose movti copies
  loop.c counts) pass 1 sees 84 insns and leaves the `lui`; strength reduction takes pass 2 down
  to 75, which moves it, after the giv's start: retail's order. With all three of the loop's
  vector statements as Vec the counts are 90 and 81 and neither pass moves it (one Vec statement,
  the angle's difference, stays a u128 expression). With the u128 forms (70 insns) the `lui` and
  its `lw` stay apart in the order of the first pass.
- **Reading it.** A preheader `lui` (or any moved constant) placed after a giv's start value was
  moved by the second pass: its first-pass count was over `80 * lifetime` (160 without a call)
  and its second-pass count under it.

### A count-up loop over arrays reversed only when pass 1 finds every giv (func_00118988, near miss)

- **Retail.** SampleScriptAnimation's inner loop `for (i = 0; i < n; i++)` indexes four arrays
  by i and calls functions. Retail counts it down (`move s3,v0` after the entry test,
  `addiu s3,s3,-1; bnez s3`), with the four array pointers in s4..s7 initialised after the
  entry test, in the preheader.
- **check_dbra_loop.** In a loop with calls it reverses a counter only when it is used for
  nothing but counting: `bl->giv_count == 0`. Loop.c runs twice (-frerun-loop-opt): givs pass 1
  reduces are gone when pass 2 looks at i. `&rotations[i]` multiplies by 48 through a register
  loaded in the loop (`li 48; mult`); pass 1 finds that giv only if it first moves the `li`.
  It is "not desirable" there: the threshold `(has_call ? 1 : 2) * (1 + n_non_fixed_regs)`
  (between 69 and 77 here, measured) falls by 3 for each register moved, and the switch's
  compare tree, at the top of the body, gives five constants that move first (67 insns against
  at most 62). Pass 2 moves it, reduces the giv, and i then has a giv: not reversed.
- **Pointer walks** (`pp++` for each array) reverse the counter, but their inits are the
  source's, before the entry test, where retail's are after it (loop.c's own inits).
- **Hoisting `r = &rotations[i]` above the switch** moves the 48 first and the loop reverses,
  everything else retail's but one swap: rotations' reduced register is reduced last (givs are
  reduced in reverse insn order, and the last one's init sits nearest the loop, the shortest
  life and so global-alloc's first choice), so it takes s4 where retail has positions there.
  In retail's order (positions, rotations, q4, q8 in the cases) the registers come out right;
  what keeps the 48 movable in pass 1 there is still to find.

### The threshold falls as loop.c moves: which invariant wins a saved register (func_001CF158)

Read from loop.c (move_movables) and global.c with `-dL -dG` dumps (2026-11-08,
ChoosePlayerTargetByCost's curve loop, nonmatching/func_001CF158.cpp):

- **Each move costs 3.** move_movables lowers `threshold` by 3 after every invariant it moves,
  in the loop's order, so an invariant late in a big loop faces a smaller limit: the curve loop
  (137 insns in pass 1, with a call) moves `&at`, `&ctx`, D_00274E44's `%hi` and 30.0 first,
  and then D_00274E10's `%hi` (lifetime 2) needs `2 * 68 >= insns` and D_00274E20's `2 * 65`.
  Both stay for pass 2 at 137 insns, and move there (126 insns) after the scorer's `%hi`.
- **The last one moved wins.** The hoisted `%hi` parts all cross the loop's calls, have three
  refs each and are live over the whole loop, so global-alloc's priority (refs over live length)
  differs only by where each sits in the preheader: the one put last (last of the second pass)
  is the shortest and takes the one saved register left, the others are spilled and reloaded
  (rematerialized) in the loop. sched1 keeps the preheader's order (all alu, priority 1).
- **Telling hoisted from never moved.** A `%hi` reloaded in the loop takes reload's round-robin
  register (v0, v1, a0 in turn across the loop's reloads); one never moved is local-alloc's and
  takes v0. Retail's curve loop reloads D_00274E10 into v1 and D_00274E20 into a0, so retail
  hoisted them and they lost to the scorer's `%hi` (s8): they were moved before it, in pass 1,
  which a loop of 130 insns or fewer would do. Not reproduced: no source form found shrinks the
  loop (statement order, named locals and the loop variable leave the count at 137).
- **A function's parameter order shows in its callers' moves.** The same function's vector loop
  sets `$f14` (the low end, 50.0) after a0 and a1: FindLocalMinimum's prototype is (fn, ctx,
  start, step, lo, hi, outX, outY), which its definition (file_1E88D0) and its other callers
  match as well as the old order (the moves follow it, docs above, func_0013A128).

### Solved: the weight and the limit named at the top of the loop (func_001CF158)

ChoosePlayerTargetByCost matched on 2026-11-09 (src/main/player_target.cpp). The count was
never the lever; the lifetime was:

- **A movable's lifetime is in luids, not insns.** `threshold * savings * lifetime` uses the
  luid distance from the `%hi` set to its last use. `cost * D_00274E10` expands the `%hi`, then
  the load of cost, then the load of the weight: lifetime 2. At threshold 68 (65 for the
  limit) a 137-insn loop needs 3. A `const f32& weight = D_00274E10;` at the top of the loop
  body forms the `%hi` there (g++ folds the reference into the global's own address, so the
  load stays at the use, and the final code is unchanged), which gives it a lifetime of 85
  and the limit's 92: both move in pass 1, ahead of `&at`, `&ctx` and D_00274E44's `%hi`. The
  scorer's `%hi` (lifetime 1 in pass 1, 11 in pass 2 after loop.c folds its `lo_sum` into the
  a0 move) is then the only `%hi` moved in pass 2, last in the preheader, and takes s8; the
  weight and the limit are spilled and reloaded into v1 and a0 as retail's.
- **D_00274E44 had to stay a pass-1 move.** Naming the step (`f32 step = D_00274E44;` after the
  upper end) makes its `%hi` lifetime 1, so it leaves pass 1 and D_00274E10 moves (threshold
  71); but D_00274E44 is then never hoisted (a variable load is never loop-invariant in a loop
  with calls, so no pass-1 substitution lengthens it), local-alloc gives its `%hi` v0, one
  reload fewer shifts reload's round robin, and the switch after the loops takes other
  registers. Retail's reload sequence (v0, v1, a0 for the step, the weight and the limit)
  proves all three were hoisted and spilled.
- **Where the references go.** Declared just before FindLocalMinimum, or after `c = &ctx`, the
  limit's `%hi` combines with the weight's move and the code differs (58 lines); at the top of
  the body, after the loop's own declarations, it is retail's. The point loop, which weighs
  and tests its cost the same way, takes the same two references with no change to its code
  (its loop is small enough to move both in pass 1 either way); the four other loops compare
  with D_00274E20 directly, and a reference there moves their `%hi` parts into saved
  registers (119 lines), so they had none.
- **Also EXACT, not landed:** small inline helpers taking the global as `const f32&`
  (`WeightRef(cost, D_00274E10)`, `ValueRef(D_00274E20)`) do the same through the inline
  body's block notes (func_0017E3C8's lever above), and a block `{ const f32* w =
  &D_00274E10; ... }` lengthens the weight's lifetime to 3. A struct type with an `operator
  f32()` for these globals reaches the curve loop too but loads the limit before cost in the
  other loops (10 lines).
- **Rule.** A `%hi` that retail hoists in a big loop while ours waits for pass 2 (a spilled
  `%hi` reloaded in round-robin registers, against a later hoisted one that took the saved
  register) points to a name bound to the global earlier in the body: a reference or pointer
  local, or a `const T&` parameter of an inline function.
- **PAL fixes the declaration order (2026-11-09).** The results bestPointT, bestCurveT and
  bestVectorT are each used 3 times over about 730 insns, so global-alloc's integer priority
  (`floor_log2(refs) * refs / live length * 10000`) is 41 or 40 and ties fall to the pseudo
  number, that is the declaration order. In US the point's life is 732 insns (priority 40),
  so only curve before vector showed. PAL's shorter checksum tail (RandomIntInRange instead of
  the clock and RandomFloatInRange) makes all three 41, and retail's f26, f27, f28 for point,
  curve and vector prove they were declared in that order; the shared source now declares them
  so, and US is unchanged.

### A negative index splits its offset; `&recs[n++]` is retail's record (func_00148938)

Read from `-dr -dL` dumps (2026-11-08, func_00148938's candidate records, 8 bytes each):

- **`q[-1]` is a large offset.** g++ expands `q[-1]` (and `q++` followed by `q[-1].field`) with
  the index as a product in an unsigned sizetype (inferred: the .rtl dump shows the split at
  expand), so the address is `q + 0xFFFFFFF8`, which the MIPS
  address legitimizer splits into `q + -32768` and an offset of 32760 or 32764. loop.c then sees
  `q - 32768` as a giv (lifetime 46), combines the record's stores into it and eliminates the
  biv: the pointer starts at `addiu a1,s2,-32768` and every store is biased by 0x8000. Retail
  never shows such a bias, so a record written through `p[-1]` was not the original.
- **A record taken by index.** `Candidate* r = &recs[n++];` makes r a giv of the count biv
  (mult 8, add recs). loop.c reduces it to a register started at recs (`move a1,s2`), kept as a
  copy for r (`move v1,a1`), and puts the reduced register's `+8` right after the count's
  increment, so the stores after `n++` read `-4(a1)` and `-8(a1)` while the store across the
  VU0 asm keeps r (`0(v1)`). Writing `n++` after `r->obj = p` (r taken as `&recs[n]`) leaves the
  first store on r (`4(v1)`) and moves both increments. A pointer advanced by `q++` with
  `r = q++` gives neither. Retail's `&recs[n++]` is the plain way to append to an array.

### Where a loop's exit store sits: loop depth in global-alloc's ranking (func_00203828)

flow counts each reference to a pseudo with the loop depth of its block (`REG_N_REFS +=
loop_depth`, depth 1 outside any loop, from the LOOP_BEG and LOOP_END notes at flow time), and
global-alloc ranks by floor_log2(refs) * refs / live length. So a statement's place relative to
the loop notes moves a global's high part in the ranking without changing a single instruction.
WaitDiscReady binds a client once, `if (flag < 0) { retry loop } `, and retail's saved registers
need the flag's high part first (4 refs over 66 insns, 0.121, above the mode's 0.104) while
everything in the retry loop is at depth 2 (the client's high part 6 refs over 160, below the
send buffer's 5 over 132). The forms, with Sony's 2.9-ee-991111:

- `while (flag < 0) { while (1) { ... if (server) break; wait; } flag = 0; }`: the store is in
  the outer loop (depth 2, the flag first) but the retry loop is at depth 3, so the client's
  high part (8 refs) rises to the top. Order off.
- `if (flag < 0) { while (1) { ... if (server) break; wait; } flag = 0; }` (BeginDiscSCommand's
  form): everything right except the flag, whose store is at depth 1 (3 refs, last).
- `if (flag < 0) { while (1) { ... if (server) { flag = 0; break; } wait; } }`: expand_end_loop
  does not rotate the loop (its exit is an unconditional jump after the store), and loop.c's
  find_and_verify_loops moves the block `flag = 0; goto exit` out of the loop (a block ending in
  a jump out, behind a conditional jump around it, goes to a barrier at the target's depth): the
  store is back at depth 1.
- The same body as `do { ... } while (1);`: expand_end_loop rotates it (the wait first, entered
  by a jump to the bind, retail's layout), the store and its break end the rotated region and
  fall into LOOP_END, so there is no jump out for loop.c to move and the store stays at depth 2.
  EXACT.

The tell: a flag's or pointer's high part ranked as if it had one more reference than its
loads and stores, with every other value ranked as at the inner loop's depth, is a store inside
the loop that loop.c did not move out. A `while (1)` with `{ store; break; }` loses it; a
`do { } while (1)` keeps it.

## CSE

### The same walk twice: Vec values keep the second bound's copy (func_00191C78)

Read from cse.c (cse_around_loop, cse_set_around_loop) and the -ds/-dG/-dL dumps (2026-11-09).
func_00191C78 walks the graph's triangles twice (the total area, then the pick), each walk
`for (i = 0; i < self->graph.triCount; i++)`. Retail's second walk loads the count into v0 for
the entry test and copies it into a2 in the preheader after the moved invariants; ours loaded
it straight into a2. With the edges written `Vu0::Sub(Vu0::Q(..), Vu0::Q(..))` the body has no
store CSE cannot see through, so cse_around_loop replaced the bottom test's load with the
REG_LOOP_TEST_P register and put the copy before the entry branch, where GCSE's copy
propagation folded it. With the edges as `Vu0::Sub(Vu0::Vec::Of(..), Vu0::Vec::Of(..)).q` the
helpers' Vec temporaries are stores through ADDRESSOF at CSE time, the load's entry is
invalidated before the scan reaches it, loop.c moves the load to the preheader and cse2 makes
it `move a2,v0`: EXACT. (cse_jumps_altered, the other way to skip cse_around_loop, is reset for
each basic block that is not extended along a jump path, so a jump CSE folds earlier in the
function does not stop it: tested.) A label in the body also stops the scan (a `continue` to a
real test gave retail's preheader as an experiment), but nothing in retail's body needs one.

### A skipped block's struct store forgets memory (func_001B2140)

At -O2 CSE follows a conditional jump that skips a block (`-fcse-skip-blocks`): the path goes
from before an `if` straight to the label after it, and what the skipped body stores is
forgotten by `invalidate_skipped_block`. Its `invalidate_skipped_set` forgets one location for a
plain scalar store with a fixed address, but *all* memory for a store that is
`MEM_IN_STRUCT_P`, BLKmode or through a varying address. So a local whose address escaped (an
out-parameter, a stack slot after purge_addressof) and that is read before the `if` and again
after it is read twice when the `if`'s body stores a struct, once when it stores only through
`u128*` casts or scalars. The second load starts the block after the join label, so it comes
after every store of the body in the schedule, and the register the first load held is free in
the body.

func_001B2140 tests the count of colliders a call wrote (`lw v0, 160(sp); beqz`), computes a
segment's two ends only `if (count != 0)`, then runs `for (i = 0; i < count; i++)`, whose copied
entry test retail reads again (`lw v0, 160(sp); blez`) after the segment's stores, and whose
weights it loads with `lw v0`. Written with `Vu0::Q(a) = ...` (a u128 store, no struct) inside
an `if` holding the loop, or around the two stores only, CSE kept the count in v0 across the
segment and the weights took v1 (97.0%). The ends written as Vu0::Vec values
(`*(Vu0::Vec*)&a = Vu0::MulAddX(...)`, a struct store) in an `if` of their own before the loop
give retail's reload and registers. The join label survives sched1 (the -dS dump still branches
to it); the branch reaches the function's end in a later pass. With the loop inside the `if`, no block is
skipped and Vec stores change nothing; with the `if` around the stores and u128 stores, the
skip path keeps the count. Both are needed.

### A constant the loop does not own: an untied product (func_001389D0)

Read from local-alloc.c (block_alloc, combine_regs), loop.c, jump.c and stmt.c with `-dL -dl
-dg -dr` dumps (2026-11-08, SortSweepAxes, src/main/file_137290.cpp):

- **Retail's sign.** `li v0,0x1800; mult a0,a1,v0`: the constant and the product in different
  registers. In ours the constant's pseudo died in the multiply and block_alloc tied the product
  to it (combine_regs ties operand 0 of a two-operand insn to the first input that dies there,
  if that input is a local pseudo), so both took one register (`mult v1,a1,v1`), and every
  register of the block after it moved (the base, the count and the counter).
- **No tie when the constant is not local.** A pseudo live in more than one block has
  `reg_qty` -1, and combine_regs refuses it. With the multiplier a pseudo live over the whole
  loop that gets no hard register (all nine saved registers already taken, like the constant
  loop.c hoists in func_001CF158), reload rematerialises its REG_EQUIV constant into a reload
  register just before the multiply, and the product is a quantity of its own: retail's
  `li v0; mult a0` and, after it, retail's base in v1, count in v0 and counter in a1.
- **Why loop.c did not hoist ours.** The outer loop had 85 insns at the loop pass, over the
  80 of a lifetime-1 constant in a loop with calls. Six of them and four of gcse's copies are
  the inner `while` loop's exit test that jump.c duplicates ahead of the loop
  (duplicate_loop_exit_test, after regscan) and that cross-jumping removes again after reload:
  the final code shows nothing of it, retail's shape included. Blocking the duplication (a test
  only) drops the count to 78 and the constant moves, with retail's registers; no plain source
  shape of the inner loop avoids it (`while`, `for` with or without the decrement, `for (;;)`
  with breaks, the break folded into the condition: stmt.c's expand_end_loop rotates them all
  the same way, and jump.c's first pass deletes the label between the two tests).
- **Retail's form: a named size.** `s32 axisSize = 0x1800;` before the loop, multiplied by the
  axis (`buf1AD8 + axis * axisSize`), as the same file's AddColliderToSweepAxes keeps its
  stride in a named local. The middle loop counts down with `for (k = count * 2; --k > 0; p++)`:
  its `sll a1,v0,1; addiu a1,a1,-1` sets the counter itself, where `k = count * 2 - 1` puts the
  doubled count in a temporary that local-alloc ties to the loaded count.

### A copy into a longer-lived variable becomes the canonical register (func_001C57C8)

- After `best = c`, CSE puts the two in one equivalence class and replaces later reads of c in
  the block with the class's first register. make_regs_eqv makes the copy's destination first
  when it lives past the block and its last use is later than the source's, as a running
  "best so far" pointer does (c dies in the loop, best is read in a later loop). Every
  member read through c after the copy is then a read of best: one more weighted reference
  each (flow weights references with the loop depth, 3 in a nested loop), which raises the
  variable's global-alloc priority (floor_log2(refs) * refs / live length).
- func_001C57C8's first walk saved the contact (`best = c`) before storing the pivot's
  fields from `c->end[1 - j]` and `c->v80`. Both reads went through best: 13 refs over 382
  insns, priority 0.102, allocated before freed (0.061) and the second walk's
  &D_00274AD0 (0.042), so best took $s6 where retail has $s8. Written as the body's last
  statement, best has only its sets and the later compare (7 refs, 0.037): freed takes $s6,
  the address and the first walk's high half $s7, best $s8, as retail's. The reads keep c's
  register in the output, so only the allocation shows the order.
- So where retail's code reads a member through the loop's pointer after a save into a
  longer-lived variable and the variable ranks low, the save came after the reads.
- Still open there: in the level contact, sched1 issues the start's lqc2 before the depth's
  qmtc2 (both ready at the same cycle with priority 8: the vsub feeds the d store, whose
  two-cycle store-to-load latency holds the lqc2, and the Dot, qmfc2 and qmtc2 chain alike).
  rank_for_schedule's INSN_REG_WEIGHT prefers the lqc2 (it kills its address, 0) to the
  qmtc2 (depth lives on to the call's $f12, 1), and the lqc2 also has more dependents. In
  that order local-alloc ranks the Scalar first (vf1); retail's vf2 for it needs the qmtc2
  first (emulated with lalloc.py on the `.lreg`).

### A hoisted address after NOTE_INSN_LOOP_BEG is a scheduling barrier (func_0014D680)

func_0014D680 (src/main/path_curve.cpp) differed only in its prologue: retail's `addiu
s2,sp,16` (the address of the loop's local d, passed to two calls) sits among the
callee-saved saves; ours came after all of them, in the entry jump's delay slot (2026-11-09).

- **The barrier.** A `for (;;)` loop whose top is an exit test is rotated by
  expand_end_loop (stmt.c): the entry `goto` is emitted after NOTE_INSN_LOOP_BEG. With
  `Vu0::Q(d) = ...` at the loop top, `&d` is a pseudo set unconditionally there, so PRE
  hoists it to the end of the block before the loop, after the note and before the jump.
  haifa-sched turns a LOOP_BEG note into a REG_SAVE_NOTE on the next insn and makes that
  insn depend on every earlier insn (`schedule_barrier_found`): the addiu waits for every
  save. The insertion also makes loop.c call the loop phony (its first insn after the note
  is neither the entry jump nor a label), so nothing else is moved.
- **Retail's form: loop.c moves it instead.** Written with Vu0::Vec values (`*(Vu0::Vec*)&d =
  Vu0::Sub(Vu0::Vec::Of(*pos), ...)`, `Vu0::Vec ev = Vu0::Vec::Of(e)`, as func_0014D3A8 is),
  the address is formed only at the calls, PRE leaves it, and loop.c moves it before the
  note, where sched2 is free to interleave it with the saves. The Vec copies make the loop 91
  real insns at the loop pass (56 written with u128 and frame-addressed stores): `&d` (life 3,
  80*3 >= 91) moves, `n - 2` and `0.0f` (life 1, 80 < 91) are "not desirable" and stay, as in
  retail. With u128 values and frame-addressed stores loop.c moves all three (a 240-byte
  frame, n - 2 spilled).
- **Diagnosis.** A prologue insn that ours puts last (or in the entry jump's delay slot) and
  that the sched2 dump shows depending on every earlier insn is this barrier: look for the
  LOOP_BEG note right before it in the `.sched2` dump and for "is phony" in the `.loop` dump.

### A loop bound from the copy, a call's result stored first (func_00142B78)

Three statement shapes closed func_00142B78 (src/main/collider_span.cpp) from 93.7% to EXACT,
each read off the diff's registers (2026-11-09):

- **The bound computed from the loop's copy.** Retail's `move t1,s1; mult a1,v0,s2; addu
  v1,a1,t1` builds the end pointer from the loop variable's register (t1), not from the
  segment pointer that lived across the call (s1). Written `ColliderSpan* sp = seg;
  ColliderSpan* segEnd = sp + got; for (; sp < segEnd; sp++)`, the segment pointer dies at the
  copy; written `for (sp = seg; sp < seg + got; sp++)` it lives to the bound, which raised its
  global-alloc priority above the inner loop's link pointer: the two swapped s0 and s1 (and
  every reference to them in the inner loop differed). An index loop (`seg[j]`, j < got) is
  not it: loop.c turns it into a counted loop with no top compare.
- **A pointer initialised with a sum keeps the source order** (see "The operand order of an
  address sum"): retail's `addu a0,a0,v0` (base first, into the base's register) is
  `SpanOther* other = &set->others[l->other]; if (other->flags & 0x100)`; the member read
  straight off the element (`set->others[l->other].flags`) puts the index first.
- **A call's result stored to an address-taken local, then copied.** Retail stores the
  allocation into the record end whose address the next call takes (`sw v0,32(sp)`) and copies
  it into the callee-saved base after the next load (`lw a0,8(s0); move s7,v0`). `recs =
  Alloc(); end = recs;` stores the base's register (`move s7,v0; ...; sw s7`), which the
  store then waits for; `end = Alloc(); recs = end;` stores the call's value and CSE replaces
  the read of `end` with that same value, so the copy to recs is free to move.

### A weight's address hoisted out of the loop: a reference's block notes (func_0017E3C8)

func_0017E3C8 (src/main/file_17D248.cpp) went from 92.5% to EXACT on one change, a float
weight passed to its helper by value instead of by reference (2026-11-09). Its loop body
ends `p = from + tmp * -D_00264020 + unitZ * D_00264024` (MulAddX2); retail loads the second
weight `lui v1; lw v1, %lo(D_00264024)(v1); qmtc2 v1, vf5`, and gives `from` and the result
vf2 and the first weight vf3. With `Vu0::ScalarAt(D_00264024)` ours swapped vf2 and vf3 and
built the address in a0, and the a0 carried on to `*outEnd`'s reload after the call.

- **loop.c counts notes in a lifetime.** A movable's lifetime is the luid distance from its
  set to its last use, and loop.c gives every insn a luid, notes included. ScalarAt takes
  `const f32&`: the inliner computes the argument, the address (`high` and `lo_sum` into a
  pseudo), at the call, and the inline bodies' NOTE_INSN_BLOCK_BEG/END notes (ScalarAt's,
  its Slot's scope, FromFloatAt's) follow before the asm that uses it: `regno 227 (life 9),
  move-insn savings 1 moved` (80 x 1 x 9 >= the loop's 135 insns). The hoisted `high` lives
  through the loop and calls, global-alloc spills it, and reload rebuilds it at the asm. Its
  memory operand then needs two reload registers ("Spilling for insn 528: reg 3, reg 4"),
  which puts a0 in the function's spill registers; the round robin (see "The reload
  register's round robin") then gives the asm a0, and `*outEnd`'s reload after the call a0
  where retail's set {v0, v1} gives v1 (v0 holds the copy of tmp there).
- **By value the load sits next to its address.** A by-value `f32` argument is loaded at the
  call, right after its `high` (`life 1, not desirable`, like the first weight's), and the
  load folds into the asm's `"rV"` memory operand. local-alloc gives the `high` v1, and
  push_reload loads the operand into that dying register (`lui v1; lw v1,(v1)`): no spill
  register, and the round robin goes on as retail's. The load in the block also moves
  sched1's order, so the combined `from` and result quantity outranks the first weight in
  local-alloc (vf2 to `from` and the result, vf3 to the weight), as retail has it.
- **The helpers.** include/vu0.h's `FromFloatAtCall`, `ScalarAtCall` and
  `Vec::ScalarAtCall` take the float by value with FromFloatAt's `"rV"`. Changing ScalarAt
  itself to by value breaks other matched functions (func_001DDE90's spill slots move), so
  both forms stay: the reference where retail's address was formed before the helper's body
  (outside a loop, or hoisted as retail's are), the value where retail's `lui` sits just
  before the `lw` inside a loop.

### A count-up loop reversed: the counter after PRE's insertions (func_001D4348)

Retail's `li v1,7; addiu v0,a1,224; sw zero,0(v0); addiu v1,v1,-1; bgez v1` with the
pointer stepping down by 32 is `for (i = 0; i < 8; i++) slots[i].weight = 0.0f;`, not a
loop written downwards (2026-11-09, read from the `-dG` and `-dL` dumps):

- **loop.c reverses it.** check_dbra_loop finds the counter used only to index stores through
  a giv that do not overlap, and turns the loop round: the counter counts 7 to 0 against zero
  (bgez) and the address starts at the last element. Retail's final weighted sum
  (`move v0,a1; li v1,7; ... addiu v0,v0,32; bgez v1`) is the same loop over the slots,
  reversed only in its counter.
- **The new counter's init comes after what PRE hoisted.** PRE put the two asms that the end of the
  function computes (Zero, and the qmtc2 of Scalar(scale)) at the end of the block before the
  loop, after the source's `i = ...`. Written `for (i = 7; i >= 0; i--)`, that init keeps the
  smallest luid of four equal insns (priority 1, weight 1), and sched1 and sched2 issue the
  `li` first. Reversed, loop.c deletes the source's init and emits its own at the loop start,
  after the hoisted insns: retail's `mfc1, vsub, qmtc2, li, addiu`.
- **Spotting it.** A counter loaded with N-1 that counts to zero with bgez, while the loop's
  invariants and hoisted values come before its `li`, is a count-up `for` loop.

### An exit test jump.c does not copy: a label among the rolled tests (func_001388A0)

expand_end_loop (stmt.c) rolls a loop that begins with an exit test: everything from the top to
the last jump to the loop's end within 30 insns goes to the bottom, and the loop is entered by a
jump to it. In the first jump pass (after regscan), jump.c's duplicate_loop_exit_test then
copies those tests in front of the loop when a LOOP_BEG is followed by that jump, unless the
copied code holds a CODE_LABEL, a call, a LOOP_BEG or LOOP_CONT note, or more than 20 insns. A
label counts only while something jumps to it: a label jump threading empties is deleted, and
the pass runs again until nothing changes, so the copy is made on the next round. A copied test
adds its references at the outer depth (flow's `REG_N_REFS += loop_depth`), and the first
block after LOOP_BEG holds what sched1 put before the entry jump, at the loop's depth. The
final code can be the same either way: cross-jumping after reload merges the copy into the
bottom test.

RemoveColliderFromSweepAxes scans each axis for a collider's start entry and stops at its end
entry. Retail's owner (a parameter compared once) ranks after self in global-alloc, and the
axis counter's `i + 1` before the 0xAAAAAAAB constant: the owner has 4 references (its copy
from a1, one compare at depth 3) and `i + 1` has 5 (set after the outer loop's LOOP_BEG, at
depth 3). The forms:

- `for (;;) { while (cur->owner != owner) cur++; if (cur->flag != 0) break; start = cur;
  cur++; }`: retail's code, but the inner while's test is copied in front of it (8 refs for the
  owner, 1 + 3 + 4) and `i + 1` sits before the outer loop (4 refs): the owner ranks fourth.
  90.8%.
- `if (cur->owner == owner) { if (cur->flag != 0) break; start = cur; } cur++;` and
  `... { if (cur->flag == 0) start = cur; else break; } cur++;`: rolled, but no label survives
  in the rolled tests (the second's else label is threaded away), so jump.c copies them and the
  copy stays before the loop.
- `if (cur->owner != owner) { cur++; continue; } if (cur->flag != 0) break; start = cur; cur++;`:
  the label of the skip's else is in the rolled code, so nothing is copied and every register is
  retail's, but the rolled region ends at the `break`, so `start = cur` is left at the top of
  the loop (`beqz` back to it) where retail has it after the test (`bnez` out, then `b`).
- `if (cur->owner != owner) { cur++; continue; } if (cur->flag == 0) start = cur; else break;
  cur++;`: the region ends at the else's unconditional `break`, so `start = cur` rolls with the
  tests, the skip's label keeps jump.c from copying them, and only `cur++` stays at the top.
  EXACT. With SweepAxisSlot pointers, the first count `(cur - start) * 12 - 12` written in one
  expression is folded to the byte difference; counted into a local first (`s32 n = cur -
  start;`) it keeps retail's exact division.

The tell: retail enters a loop with a `b` to its tests, a parameter compared once in it ranks
as if referenced once at the loop's depth, and the near miss's dump shows the test copied in
front of the loop: a `continue` that skips to the next element leaves a label in the tests.

### The opposite: a minimum of two members in the exit test, through an inline (func_001CC120)

The other way round from func_001388A0: retail copied the exit test, ours did not. The loop is
`while (i < min(self->owned.count, self->listed.count))`. Retail enters with the test and its
loop.c invariants (`&rot`, `self + 92`, `self + 228`) sit after the `blez`; ours entered by a
jump to the bottom test, the invariants went before it, and every register of the outer loop
differed (37.4%).

- **Mechanism.** COND_EXPR's expansion of `a < b ? a : b` with both arms members leaves
  `t = listed; if (owned < listed) t = mem[self + 88]`: the arm is a memory load, `may_trap_p`,
  so jump.c's conditional move (jump.c, "x = a; if (...) x = b;") refuses it. Its label survives
  the first jump pass, and duplicate_loop_exit_test refuses any test with a CODE_LABEL. `a <? b`
  (MIN_EXPR) does no better: its `target = op1` is still the member's MEM.
- **Lever.** An inline `MinOfCounts(s32 a, s32 b) { return a < b ? a : b; }` (as player.cpp has):
  the parameters are pseudos, so the arm is a register move, jump.c turns it into `movz` in its
  first round, the label is deleted, and the next round copies the test in front of the loop
  (the copy is the `movn` form, the bottom the `movz` one: retail's two shapes are the tell).
- **Then loop.c's order.** With the loop rotated, retail moves `sp + 16` before `self + 92`
  (the order of their spill stores). The outer loop needs more than 80 insns at the first loop
  pass so that the life-1 invariants (`self + 92`, a `%hi`) wait for the second pass, while
  PRE's long-lived copies (`self + 228`, `&rot`) move in the first. `Vu0::Distance` (Vec values)
  for the inner loop's distance brings the outer loop from 72 to 80 insns, which does it;
  the u128 `ToFloatMoved(Length(Sub(..)))` does not.
- Two other differences: the second loop written `for (; i < n; i++) { m = found[i]; ... }`
  (loop.c's reduced giv: `addu s2,v0,s3`, index first) rather than a walking pointer, and
  `radius` declared before `step` (retail loads 1/(2pi) before 2pi).

### A search loop that leaves by `goto`: breaks roll the body into the exit test (func_0015FD78)

expand_end_loop's scan takes the *last* jump to the loop's end label within 30 insns of the first,
and a `break` is such a jump, conditional or not. A search loop whose body begins with early
exits (`if (mode == 1) break; if (mode == 2) { m = 0; break; }`) therefore has its whole head,
the mode tests included, rolled to the bottom with the `m != 0` test; duplicate_loop_exit_test
then copies all of it in front of the loop, and the copy enters the loop by a conditional jump
to the label after the tests. loop.c reports "Loop at N ignored due to multiple entry points",
moves nothing out of the inner loop, and the outer loop takes its constants (`li 1`, `li 2`)
into saved registers for its whole body (ours: frame 160 with s6 to s8, 44 bytes longer).
Retail's code has only the `m != 0` test rolled (`bnezl s0` at the bottom, the mode tests at the
loop's head, the constants in a2 and a3 in the inner preheader): its exits did not jump to the
loop's end label. A `goto done;` to a label after the loop (the same place) gives exactly that,
and so would any exit that is not the loop's own `break` (an inline function's `return` also
avoids the roll, but its own pseudos for the pointer and the result do not match here). Spot it:
"ignored due to multiple entry points" in the .loop dump, or retail's inner loop with its
early exits at the head and only the continuation test at the bottom.

### A reference's address reused across a test: read the vector at its use (func_00199698)

- **What retail shows.** `UpdateNumberedItem` tests the squared distance between `target->v140`
  and `self->v140`, and after the test passes `&target->v140` and `&self->v140` to calls.
  Retail forms `self + 320` before the test (`addiu s2,s0,320`, kept for the second call), but
  `target + 320` only after it (`addiu a2,a0,320` beside the call's other argument moves). Ours
  formed both before the test, which also moved the `mul.s` and the `vsub` out of the
  `c.lt.s` nop and the branch's fall-through (89.1%).
- **Mechanism.** `Vu0::Q(x)` (like `Vec::Of`, `Set`) takes `x` by reference: after inlining,
  the parameter is a pseudo set to `(plus target 320)` in the test's block. CSE, following the
  branch into the next block, finds the call's `&target->v140` equal to that pseudo and reuses
  it, so the address is computed once, before the test, and sched1 orders the block around it.
  A read written `*(const u128*)&target->v140` at the use is a plain `mem` with the sum inside
  it: no register holds the sum, so the call's address is expanded afresh where it is used.
- **The form.** The read side of the rule `Set`'s comment in include/vu0.h gives for stores
  (`*(u128*)&v = x` at the use): where retail forms an address afresh for a call after the
  vector was read, read it with the cast at the use; where retail keeps the address (self's
  `s2` here), read it through `Q`. Different statement orders, a pointer local and a
  re-read of `data->f18` keep the CSE'd pseudo and do not help.

### A vector stored in each arm is read back after the join (func_001D8E40)

Retail's wheel-spawn loop stores FromFloats' GPR result with `sq v0` to its offset local and to
the helper's slot and then reads the offset back with `lqc2`, where ours moved it to VU0 with
`qmtc2` and stored it with `sqc2` (2026-11-09, read from the `-ds -dt -dl -dL` dumps and
local-alloc.c's update_equiv_regs):

- **CSE2 forwards a store in its block.** CSE1 does not forward `Q(off) = ..` into the reads
  (the Vec values' addressof copies between them forget the memory), but CSE2, after
  purge_addressof, replaces both reads with the asm's output. That pseudo then has two VU0
  uses besides its two stores and takes a VU0 register (`qmtc2` from the asm's GPR).
- **A label between store and read stops it.** Written `if (front) Q(off) = FromFloats(0, 0,
  f610); else Q(off) = FromFloats(0, 0, f614);` instead of a `len` chosen by `?:`, the store
  is in each arm and the read follows the join, where CSE starts a new table: the reads stay
  loads, the asm's pseudo is only stored (GPR, `sq`), and jump2's cross-jumping merges the two
  arms' identical tails after reload, leaving only the loads of f610 and f614 in the arms.
- **An untied rotate where the result takes row 0's register.** The velocity's `vmaddz` writes
  vf2 (row 0, last used there) from an input in vf4: RotateUntied. The tied Rotate made combine
  merge the result into the input's pseudo (".lreg: set 2 times"), which also keeps the input
  out of update_equiv_regs.
- **loop.c's count picks the hoisted `%hi`.** With a nested `RandomFloatInRange` argument, `&m`
  is computed before the call (lifetime 6) and moves into s8; written as a statement of its own,
  `&m` is formed at the call. The tilt range read through a pointer (`f32* tilt = D_00275510;`,
  as the turn's `range`) gives its `%hi` and address lifetime 3; the `%hi` takes s8 and the
  spilled address is rematerialized (`lui v1; addiu v1`) at the call. With Vec values in the
  offset's sum (Vec::Of) the loop is 231 and 216 insns: those two move only in pass 2, after
  g_unitYVector's `%hi`, and g_unitZVector's (lifetime 3, threshold minus 9) stays, local-alloc's
  a0. u128 helpers (Q) there make it 218 and 201: the tilt's two move in pass 1, and pass 2 moves
  both unit vectors' `%hi`, spilled and rematerialized (`lui v0`) at each use, as retail's are.

### One address, two adds: which forms CSE merges (func_001C3C98, unsolved)

Observed in the `.rtl`, `.cse` and `.lreg` dumps of func_001C3C98 (three accesses to
`c->end[end]`: two loads and a store), 2026-11-10:

- **Index first means no pointer local.** An address expanded as an inline's reference argument
  or inside a memory reference (`Vu0::Q(c->end[end].v10)`, `Vec::Of`, `*(Vu0::Vec*)&...`) is
  `(plus index c)`, retail's `addu v0, v1, a1`. A reference or pointer local
  (`ContactEnd03& e = c->end[end]`) folds `&c->end[end]` into pointer arithmetic: `(plus c index)`.
- **CSE never reuses a user variable's address for a later one.** Q's and Of's reference
  parameter is a user variable; a later equal sum (a cast's temporary, or another Q) stays an add
  of its own (three Qs: three adds). reload_cse then turns each later add into `move`, the copy
  retail shows. The other way round, a temporary's address first and a Q later, CSE replaces the
  Q's parameter with the temporary and deletes it: one register for everything.
- **So retail's `addu v0; move v1, v0`, both loads on v0 and the store on v1** is the store's
  user-variable address expanded first (`Q(...v30) = MulAddX(...)` in one statement, the left
  side expanded before the arguments) and both loads as temporaries (a cast and `*(Vec*)&`)
  after it. Spot it: an address copied with `move` right after its add, the copy used only by
  the store.
- What was left in func_001C3C98 is local-alloc's ranking (the address, 3 refs over 9 insns,
  against p->anim, 2 over 4): see the near miss's notes.

### A member array searched and moved up: where the constant is added (func_00145088)

Read in expr.c and the `-dG`, `.loop`, `.flow` and `.combine` dumps of func_00145088
(PushCameraController: a search through `self->stack[i].key`, then MoveMemory of the entries up
by one), 2026-11-10:

- **`self->stack[i].key` adds the member's offset first.** expand_expr's COMPONENT_REF case (via
  get_inner_reference) adds the constant to the base before the index whenever the base is a
  BLKmode object and the reference's alignment equals the field mode's (any `s32` member of a
  struct array): `t = self + 980; a = t + i*16`. `t` is a loop invariant expression, and PRE
  inserts it, with the count's load, at the end of the block before the loop, before its
  branch; the count's pseudo then shares a register with the loop's copy of the count (ours:
  `lw a0; blez a0` and no `move`).
- **`(self->stack + i)->key` adds the index first.** The reference is an INDIRECT_REF, whose
  address is expanded with EXPAND_SUM, which puts the constant outside:
  `(plus (plus (mult i 16) self) 980)`. Nothing is invariant, loop.c reduces the address to a
  giv initialised in the preheader after the entry test, and the entry test's count dies in
  the copy for the loop (`lw v1; blez v1; ... move a0,v1; addiu v1,s1,980`), retail's code.
  The rotated first test still reads `980(s1)`: CSE folds i = 0.
- **Two pointers from one base, copied: an inline's parameters.** Retail's `addu a0,s0,s1;
  move a1,a0; addiu a0,a0,996; addiu a1,a1,980` is two equal sums that CSE kept apart, the
  second made a `move` by reload_cse, as in RemoveFromSmallList (file_1E88D0.cpp, its
  MoveItemsDown helper) and the section above: MoveMemory called through a small inline whose
  parameters are the two entry pointers (`MoveEntriesUp::Of(&self->stack[i + 1],
  &self->stack[i], n)`). Called directly, CSE shares one `i*16 + self` and combine folds the adds
  into the argument moves (`addiu a1,a0,980`, one insn short).
- Spot it: a search loop whose count is loaded into one register and copied to another after
  the first test, and the loop pointer set after that copy; and a pointer argument made by
  `move` and then `addiu` of its own register.

### A vector copied before a call with global float arguments (func_00145718, unsolved)

`self->pos = *a2;` then a call whose float arguments are three `.data` globals: copied as a
Vec02 assignment the store is MEM_IN_STRUCT_P, the scalar globals' loads pass it
(fixed_scalar_and_varying_struct_p), and local-alloc gives the copy a2 and a %hi t0 (four bytes
short: a0 keeps self, no `move a0,s0`). Copied as `Vu0::Q(self->pos) = Vu0::Q(*a2)` the store has
no class, every float load waits for it, and the registers are retail's (copy in v0, %hi in a0,
`move a0,s0` in the delay slot), but retail loads `$f13` before the store and ours after it.
Neither form gives both; a Vec member store (`((Vu0::Vec*)&p)->q`) behaves as the assignment.

### An address taken after a clamp's join reaches a later arm: a fifth saved register (func_001DEBE8)

From cse.c and gcse.c of GCC 2.95.3 and the `.cse` and `.gcse` dumps (2026-11-10):

- **Each inline method call on a global makes its own address.** `g_unitRange.Clamp(x)` in
  three places gives three `(high sym)` and `(lo_sum (high) sym)` pairs. The lo end is read as
  `(mem (lo_sum H sym))` (CSE folds `this`), the hi end as `(mem (plus this 4))`, so `this`
  (the lo_sum) stays a register.
- **GCSE runs one pass (MAX_PASSES 1).** PRE makes the later highs copies of the first (retail's
  `daddu s1, v1` after the lean clamp's `lui`), but the lo_sums still have different operands
  in the same pass's hash table, so none of them is redundant: every clamp recomputes `addiu
  v0, sN, %lo`.
- **Retail's `addiu s5, s1, %lo(g_unitRange)` before the first BuildAxisAngleMatrix, used as
  `lwc1 4(s5)` in the speed clamp only, is CSE.** A clamp's join label (two uses) ends a CSE
  path, but the block after it runs through the calls to the speed test, and the test's then-arm
  falls through: an address computed there is the speed arm's `this`. The lean clamp (before
  the join) and the w clamp (after the speed arms' join) compute their own, as retail does.
  So the original took the range's address after the lean clamp and used it for the speed
  clamp; written before the lean clamp or used by the w clamp it lands in the wrong place.

### A reload after an if whose body returns: follow-jumps (func_00183668, unsolved)

`cse_end_of_basic_block` follows a conditional jump (`-fcse-follow-jumps`, on at -O2) when its
label has exactly one use and, walking back from the label over notes and unused labels, the
first thing met is a BARRIER. `if (x->f == a) { ...; return ...; } if (x->f == b) ...` is
exactly that: every path of the first body returns, so its last jump leaves a barrier before the
label after it, CSE takes the branch, and the second test reuses the first load's register.
Retail's func_00183668 instead loads `n->key` once and copies it (`bne v0,t1; move v1,v0`), then
tests the copy against the other key: that copy is GCSE's (the -dG dump makes a new pseudo for
the load and copies it to both users), so in retail CSE did not reach the second test from the
first. The path stops only at (1) a label with more than one use, (2) a used label or a
NOTE_INSN_LOOP_END between the barrier and the label, or (3) any CODE_LABEL or (before loop.c) a
NOTE_INSN_LOOP_END in the forward scan before the second load. An empty `do { } while (0)` as
the last statement of the returning body (case 2) gives retail's copy and every register
(EXACT); one between the two tests (case 3) gives the registers but aligns a later label
(`.p2align 3`, one nop). Both are barriers. Ruled out as the original: the second test written
as an `else if`, the three conditions repeated in each test (jump threading does not merge
them), the inner range tests as a `switch (key)` with or without `default`, the body as an
inline function returning the comparison, and the search as a loop that `break`s on the second
key with the unlink after it. Every natural body that returns on all paths ends in a barrier;
the original must have had a used label or a loop end there.

### A default set in the else arm, not in the walk's test: reorg's stolen slot (func_001CD870)

AddPlayerObjectContacts walks a node's parents (`while (n != 0 && !(flags & 2)) n = n->parent;`)
and then takes a contact row's lists, or the player's own list when no parent has the flag.
Retail's loop top is `beqz s0,else; addiu s5,s1,1204` with the back edge (`beqzl`) aiming at
it, the else block is a lone `move s2,s5`, and the branch after the loop carries that move in
its slot (2026-11-09, read from reorg.c, loop.c and the `-da` dumps):

- **Not loop.c's.** The near miss set the default inside the loop's test (`while ((last =
  &self->list, n != 0) && ...)`) to put the `addiu` there, but loop.c moves it out (the loop
  dump's `Insn 69: regno 127 (life 250), global savings 1 moved`): a set of an invariant used
  outside the loop is moved whenever threshold * savings * lifetime reaches the loop's insn
  count, and a variable living to the function's end always does. Set before the loop, it is
  the same. Either way `last` is born before the walk, and its longer life puts it after the
  axis pointer in global-alloc's order (0.073 against 0.077): the three saved registers
  rotate (s7, s5, s6 for retail's s5, s6, s7), and the label gets an alignment nop.
- **reorg's.** Written in the else arm (`else { last = &self->list; head = last; }`), the
  `addiu` is the first insn of a block both of the walk's exits branch to. The loop-top
  branch's fall-through never reads s5 before setting it, so fill_slots_from_thread copies the
  `addiu` from the else thread into its slot and aims the branch past it; for the branch after
  the loop, redundant_insn finds the same `addiu` in the loop top's slot with s5 unchanged
  since, skips it, and steals the `move` instead. The else arm's life is a few insns, and the
  registers fall into retail's order. EXACT.
- **Spot it**: a delay slot holding a value's only set, executed on a path where the source
  sets it later anyway, is reorg's copy from the branch target: write the set in the target's
  arm.

### A loop bound copied into its own register: cse_around_loop and Vec temporaries (func_001C4D60)

Read from cse.c and jump.c of GCC 2.95.3 and the -ds/-dG/-dL dumps (2026-11-09). Retail's plane
loop loads the face count for the entry test into v0 (`lw v0,908(s0); blez v0`) and copies it
for the loop's compare after the moved invariants (`lw a0,912(s1); move a3,v0`); ours loaded
it straight into a3.

- **Where the copy comes from.** jump.c's duplicate_loop_exit_test copies the bottom test
  (`147 = mem; 148 = j < 147`) before the loop with new pseudos and marks 147
  REG_LOOP_TEST_P. At the loop's end cse_basic_block calls cse_around_loop, which walks the
  loop body from its top label and, through cse_set_around_loop, replaces the in-loop load with
  the register and emits `147 = 182` right after the entry copy's load, before the entry
  branch. GCSE's copy propagation then folds 147 into 182: one register, no copy.
- **What stops it.** cse_around_loop invalidates whatever each body insn writes before it
  reaches the load (and stops at a CALL_INSN or CODE_LABEL). With the point as a `Vu0::Vec`
  value, the inline helpers' Vec temporaries are still stores to `(mem/s:TI (addressof ...))`
  at CSE time (purge_addressof runs later), so the load's table entry is gone and the load
  stays in the loop. GCSE makes it a copy of the entry load, and loop.c moves that copy
  (`move-insn savings`) into the preheader after the entry test, as retail's is. Written with
  u128 helpers (Q, Copy) the body has no stores and the copy goes.
- **Also cse_jumps_altered.** cse_around_loop is skipped entirely once CSE has folded any
  conditional jump earlier in the function (follow-jumps on), which is another way a loop's
  bound keeps its own register.
- **The other difference: jump.c's hoist.** `if (other == 0) changed = 1; else { changed = 0;
  ... }` is hoisted to `changed = 1; if (other == 0) goto tail; changed = 0;` (the then arm is
  one set and the else arm's first insn sets the same variable, "An if/else of a constant"
  below), and reorg turns it into `beqz s0,tail` with `li t2,1` in the slot. Retail's `bnezl
  s0` (the else arm's first load in the slot) then `b tail; li t2,1` means the else arm's first
  statement was not the flag's: `changed = 0` written after the arm's pointer locals.

### A switch case that repeats the variable's value: three passes delete it (func_0020A190)

Measured 2026-11-09 on the MPEG demultiplexer's stream-id lookup (src/lib/mpeg_demultiplexer.cpp,
Sony's 2.9-ee-991111; nonmatching/func_0020A190.cpp). `s32 sh = 0;` then a switch on a 64-bit
mask with cases 0xFFFF000000 (24), 0xFF00000000 (32) and 0xFFFFFFFFFF (`sh = 0`). Retail tests
`== 0xFFFF000000`, then `> 0xFFFF000000` with a `bnezl` whose annulled slot is `move a1,zero`,
then `== 0xFF00000000`, and never compares with 0xFFFFFFFFFF; the default path reads the top
`sh = 0`. Ours has the same tree but branches past the case's `sh = 0`. What deletes it:

- **The tree.** `balance_case_nodes` splits three cases at the middle one, and
  `emit_case_nodes` emits `GT -> test_label; == B; jump default; test_label: == R`. A greater-than
  branch goes straight to the right child's label only when `node_is_bounded` holds: its high is
  the index type's maximum or one below a parent's low, *and* its low is the minimum or one above
  a parent's high. A lone 0xFFFFFFFFFF never is; a GNU range `0xFFFF000001 ... ~0ULL` is (tested:
  no third compare).
- **CSE (follow-jumps).** The `== R` label has one use and a barrier before it, so the first CSE
  follows `GT` then `== R` from the function's top, knows `sh` is 0, rewrites the case's set as
  `sh = sh` (`src_related = dest`, cost -1) and `delete_trivially_dead_insns` removes it; the
  jump pass after CSE then deletes the now useless `== R`. That is our code. With a 64-bit `sh`
  CSE keeps the set (and the compare), but the shift then needs the `dsll32`/`dsra32` truncation
  retail lacks. Any case order, a `default` sharing the case (first or last), `default: break`,
  an inline function returning the shift (by value, by pointer or by reference) all end the same
  or worse (12 to 43 differences).
- **reorg.** Even where the set reaches reorg (the range form compiled with
  `-fno-cse-follow-jumps`, to explore only), `fill_slots_from_thread` calls `redundant_insn`,
  which scans back from the `bnez` to the top `move a1,zero` in the `beqz` slot (same pattern, no
  label between, nothing setting a1) and drops the copy: still our code. Retail's `bnezl` with
  the set means `redundant_insn` failed there: a different pattern (another mode), a label
  between the top and the `> 0xFFFF000000` test, or an insn setting a1 between them, none of which
  the visible code shows.
- **Registers.** Separately, the key's copy takes $t1 where retail has $a3: global-alloc ranks it
  2 refs over 22 insns (0.091) after `idx * 16` (3 over 17, 0.176). Retail's order needs the key
  at 4 or more references (or 3 within 17 insns), which suggests retail's RTL used the key in
  more than one shift, merged after reload by cross-jumping.

Not matched; the plausible plain forms are exhausted. The remaining lead is a source in which
the key's shift is written on more than one path (the tails merged by jump2), which could also
change what precedes the greater-than test at reorg.

### An end pointer, a switch and a reread argument: a kind loop's size (func_00185F48)

Matched 2026-11-10. The function walks each contact's two ends and carries each end's point into
the world, with a part's frame or, for some kinds, from the part's centre along the normal.
The near miss (indexing `c->end[e]` in every statement, nested ifs for kinds 4 to 6) was 376
bytes against 348. Three source properties gave retail's code:

- **A pointer to the end, `ContactEnd03* end = &c->end[e];`.** Under `if (e == 0)` CSE records
  e = 0 (record_jump_equiv) and folds `&c->end[e].v20` to c + 32, so our end-0 calls used fixed
  addresses from c. CSE does not refold the value of a register already set from e, so through
  `end` the end-0 arm keeps `end + 32` and `end + 16`, and loop.c gives each call site its own
  pair of reduced registers (retail's s4/s5, initialised as copies of s2/s3). With this the
  constants 7 and 9 also stayed in their arm (loaded with `li v1` before each compare) instead
  of being hoisted into s7/s8.
- **A switch for end 0: `case 4: case 5: case 6:` and a default.** The compare tree tests the
  case range's high bound then its low bound (`slti 7; beqz default; slti 4; beqzl case`), the
  two signed compares retail has; `kind >= 4 && kind < 7` or a range test is merged into one
  `sltiu` and the two nested ifs give two call sites, three induction pairs and 392 bytes.
- **The default reads `end->part` again.** Retail's `lw a0,4(s0)` sits between the kind < 4
  test and the call, and the kind >= 7 branch jumps past it: the default's first insn is the
  reload, and reorg retargets the branch whose path already holds the value in a0 past the
  redundant load (inferred from the code; not checked in the reorg dump). With `part` passed
  the load is gone (344 bytes), and its reference also gives the end pointer s0 and the contact
  s1, as retail has them.

The last difference was the MulAddX's operand order: retail loads the centre (`lqc2 $vf3`)
before the weight's slot store and the normal after it. An inline call's plain memory operands
are copied after its nested inline calls, so `Vu0::Q(part->v140)` came after the Scalar; naming
the centre as a local just before the statement (`u128 centre = Vu0::Q(part->v140);`) loads it
first and gives retail's VU registers. The Vu0::Vec form (Vec::Of, Vec::Scalar) loads both
vectors before the slot and does not match.

### A flags word PRE shares that retail reloads (func_00187F40, unsolved)

Read from the -dG dump (2026-11-10). The contact dispatcher reads `p->flags538` into a local at
the top of its loop body and tests its bits, then reads `p->flags538` again in the sweep tests
and for the `|=` after a swept call. PRE (gcse.c) finds those reads redundant with the first
load ("PRE: redundant insn 130 (expression 1)", a copy of the load's register at the end of bb 1
and loads inserted after each call), so ours keeps the word in a register and is 12 bytes
short. Retail reloads it at each of those reads, but reuses `other->flags538`, loaded before
the bit-47/56 test, at the first sweep's bit-40 test. GCSE does not hash a MEM's alias set
here (`-fstrict-aliasing` is off), so only a memory set in a block between the two loads
(mem_set_in_block: a store or a call) or another address expression for the later reads would
keep p's word unavailable while other's stays available. `-fno-gcse`, as a diagnostic only,
gives retail's reloads everywhere but that reuse (816 bytes against 812). Retail's sweep flag
is spilled at 4(sp) with 0(sp) unused, a sign of another frame object in the original.

### Loop variables declared once at the top: shared counters and an indexed record (func_00139740)

Matched 2026-11-10 from the -dG dumps. ComputeBlendedDuration has four loops over two counts
(three over the items, two over the keys). Retail shows three signs of C-style declarations,
`s32 j; s32 k; BlendEntry* item;` at the top, each reused by every loop:

- **A count-down counter in its own register.** loop.c reverses each `for (j = 0; j < count;
  j++)` whose j is only counted (check_dbra_opportunities). The reversed biv is j's own pseudo,
  set to the count before the loop. With one j per loop, the copy ties to the count's register
  where the count dies (ours counted down in a1). With one j for every loop, the pseudo is live
  where the count is live too, so it conflicts with a1, and retail's `move t2,a1` comes before
  each of the three loops. A shared k is the same: the last loop's k is in t0, like the key
  loop's.
- **The record taken by index, not advanced by pointer.** With `item = (BlendEntry*)((u8*)items
  + j * stride)` at the top of the body, PRE leaves the weight's second load after the
  if/else's join (retail's `lwc1 $f0,0(a2)` before the multiply). With the pointer advanced at
  the end of the body (`item = item + stride`), PRE finds the join's load redundant and keeps
  the value in a copy (`mov.s $f2,$f0` in the test's delay slot). In the dump, only the pointer
  form gives a "PRE: redundant insn" for the load. loop.c then reduces the index to the same
  pointer registers, so the rest of the loop does not change.
- **A user variable live past the loop keeps loop.c's copy.** When one `item` serves every
  loop, the key loop's giv `item` is still live after that loop, since the next loop reads it.
  loop.c then keeps `item = reduced` at the top of the body and advances the reduced register
  early. That gives retail's `move t0,v0` with `addu v0,t0,a0` in the branch's delay slot. With
  a local `item` per loop, the giv is replaced and the pointer advances at the end.

### A weight slot's address must not outlive the statement (func_0017BCD0)

Read from cse.c (cse_end_of_basic_block, cse_basic_block) and the `.cse`/`.greg` dumps of
StartNextQueueEntry (2026-11-10):

- **What differed.** Kind 5 builds a goal (`goal += drift * rise`, a MulAddX whose weight slot
  is 64(sp)), skips a lift for kind 0x76 (`if (IsObjectOfKind(obj, 0x76)) goal.z += D;`), calls
  SolveArrivalTimeAtHeight and, in its body, passes a block-scope `Vec02 v` (the freed slot,
  64(sp) again) to slot 32. Retail forms `addiu a1,sp,64` at the call; ours kept the address in
  a saved register from the first weight on, one saved register more (s8), 0x10 more frame and
  every register after it shifted (17.9%).
- **The mechanism.** Vu0::Scalar returned `Q((s128)r)`: Q returns a reference, so the inlined
  return value is the slot's address in a pseudo of its own (`(set (reg 270) (plus fp 64))`),
  dead once CSE folds the load back to the frame address. CSE keeps that pseudo in the class of
  `(plus fp 64)` for the rest of the extended block: with `-fcse-skip-blocks` the path skips
  the kind test's body (`invalidate_skipped_block` forgets only what the body sets) and falls
  into SolveArrivalTimeAtHeight's body, where `&v` is the same frame address and CSE replaces it
  with the oldest register of the class. The pseudo then lives across four calls. Breaking the
  path at the kind test's label (a second use of it) gives retail's frame, confirming it, but
  also splits `&goal` and `&drift` into PRE copies retail does not have: retail's path does go
  through, so the weight's address simply never was a register.
- **The change.** Vu0::Scalar takes the cast's address itself, `return *(u128*)&(s128)r;`:
  the same cast-lvalue temporary (MEM_SCALAR_P, the same slot and store) with no reference
  return, so no address pseudo is left for CSE. All matched functions build the same (full
  build MATCH).
- **Spot it:** a saved register holding `sp+N` (`addiu sN,sp,N` with no other use) where N is a
  weight slot that a later block-scope vector reuses, and retail forms the address at the call.
- Also in this function: `&vel`, `&goal`, `&drift` written plainly at each call (no pointer
  locals): CSE and PRE make retail's address registers, PRE inserting `&vel` into the arms that
  lack it (`addiu s5,sp,16` in delay slots). `s32 sub = e->value != 0 ? 0 : 2;` shares the 2 with
  the state argument and a store (`li a1,2; move s7,a1`), where `sub = 2; if (..) sub = 0;` does
  not. The drift update written with Vu0::Vec values (`MulAddX(Vec::Of(goal), Vec::Of(drift),
  Vec::Scalar(rise))`) puts the goal's load first in the luid order, which sched1's tie-break
  needs for retail's vector registers. CreateAnimationPlayerWithoutPresetTargets declared void
  (as five other files do) lets local-alloc give the next load v0.

### A constant passed through an inline is no pseudo for cse2 to copy (func_0016BEA0)

Read from calls.c, integrate.c and cse.c with `-dt -dL -dS -dl` dumps (2026-11-10,
DrawGridSelector, src/main/file_16AA18.cpp):

- **Retail's sign.** `lui/ori/mtc1 $f12` for the push's 1.3 after GetFontById, a second
  `lui/ori/mtc1 $f27` for the loop's 1.3, and `mov.s $f13,$f12` in the call's delay slot. Ours
  (`PushFontScale(f, 1.3f, 1.3f)` and `k * 1.3f` in the loop) loaded 1.3 once, before the
  title's DrawFontString, into a saved register, and copied it for the call and the loop.
- **Why.** A call's constant argument costs more than 2, so precompute_register_parameters
  copies it into a pseudo before the hard register (calls.c, preserve_subexpressions_p is
  always true at -O2). loop.c hoists the loop's 1.3 to the end of the block that holds the
  push, and cse2 (after loop) finds that pseudo still holding 1.3 there: the hoist becomes a
  copy of it, the pseudo crosses the calls, and sched1 (a call-crossing pseudo has no anti
  dependence on the last call) moves its set above DrawFontString. The 0.5 and `&out` copies
  retail does show (`mov.s $f25,$f20`, `move s8,s0`) are this same mechanism on user variables.
- **Retail's form: an inline with one scale.** `inline void PushUniformFontScale(Font* f, f32 s)
  { PushFontScale(f, s, s); }` called with 1.3f: integrate.c substitutes an unmodified
  parameter's constant into the saved body, whose call already reads a register, so the body
  sets `$f12` and `$f13` from the constant directly, no pseudo holds it after the call (the call
  clobbers the hard registers), and the hoisted 1.3 keeps its own load. The `$f12` load stays
  after GetFontById (a call-used hard register depends on the last call).
- **Spot it.** Two loads of one float constant in a block, one into an argument register:
  the argument came through an inline's parameter (or was otherwise never a pseudo).

### A stored product's two-operand mult: what combine needs (PAL func_eu_001ACC68, unsolved)

Retail's `mult $zero,v0,v1` with a later `mflo a0` (the two-operand form, the product in LO)
against our three-operand `mult a0,v0,v1`, where the product (two member loads, each also
stored elsewhere) is only stored (US func_001ABE70, PAL func_eu_001ACC68). Read from
combine.c (try_combine, find_split_point) and cse.c (make_regs_eqv) with `-dc -dr -dl` dumps:

- The mulsi3 expander always emits mulsi3_mult3_r5900, a PARALLEL with three clobber pseudos,
  which regclass gives GR for the product ("GR_REGS or none" in the `.lreg`): three-operand.
  Only an insn that combine *re-recognises from the bare SET* (the mult's SET without its
  clobbers) matches mulsi3_internal first ("=l" only, `mult\t%1,%2`), and reload's output
  copy is the mflo that sched2 delays. combine builds that bare SET when the mult (i2) is
  substituted into a later insn (i3) by the normal path. It keeps the PARALLEL, clobbers and
  all, in the i3_subst_into_i2 path, taken when i3 is a register copy of the product that is
  the very next real insn and in which the product dies (`next_real_insn (i2) == i3`).
- A store can never be i3 (`(set (mem) (mult ..))` matches nothing, and the split needs an
  i1 that dies, which two loads used again by the cols/rows stores are not). So the product
  needs a register copy that survives CSE, not right after the mult. CSE keeps a copy only
  when its destination is the class's canonical register: make_regs_eqv makes it first only
  if it lives outside CSE's block (first use before the block, last use after it) and longer
  than the source. The tail after a switch's join is one CSE block, so an inline getter's
  return copy, a local or a chained assignment all have their copies replaced and deleted.
- Shown: a variable first set before the switch, assigned the product from a local after the
  cols2/rows2 stores (`s32 m = cols * rows; ...stores...; n = m; self->cells = n;`), gives
  retail's whole tail (mult, mflo a0, the store order). The same with the copy right after the
  mult (an inline getter into the reused variable) keeps mult3. Neither is plausible source,
  and the reused variable moves the switch's registers. Ruled out as well: `s64` locals and casts
  (`(s32)((s64)a * b)` folds back to SImode; an `s64` local keeps a truncdisi2 of
  `(truncate (sign_extend p))` that SN's combine does not reduce; u64 forms widen and shift).
- The other nine `mult $zero` sites in US are products by a constant or with an operand that
  dies (MoveAnimationTrackToEnd's `(count - idx) * 0x1C`, EnterTimedGroupState's `* 1000`) copied
  to an argument register: a three-insn combine whose split leaves the bare SET.

## GCSE

What GCC 2.95's gcse.c does with a load, read from its source and `-dG` dumps (2026-11-08,
func_001F0AE0):

- **PRE is lazy code motion on blocks, with no cost test.** Every pseudo set whose source is
  not a register or constant is an expression, a load included (hash_scan_set). An occurrence
  is deleted when it comes before any kill in its block (ANTLOC) and is neither "latest" nor
  "isolated" there (lcm.c); the value then comes from a copy made where the expression was
  last computed, and that pseudo lives across the blocks between. A store or a call that is
  not `const` kills every memory expression: there is no alias analysis, and the alias set,
  which expr_equiv_p does compare, is 0 for every MEM, since the files' flags do not include
  `-fstrict-aliasing`. In this release `latein` is `delayin` for every block but the last
  (compute_latein only computes the intersection over successors for the last block).
- **One read as 64 bits is another expression.** A field read into an `s64` (`s64 cursor =
  self->cursor;`) is `(sign_extend:DI (mem:SI ...))`, which gcse hashes as a different
  expression from `(mem:SI ...)`. Its `lw` is the same instruction, and the comparison of the
  64-bit register the same `bne`, but that read no longer makes a later `self->cursor` in
  another block redundant: the kill before it (a call on one path) makes the later load the
  earliest place, and it stays a load. func_001F0AE0 reads its cursor once for a test and
  again for the selected entry; retail loads it twice (`lw v1` in a `bnezl` delay slot, then
  `b; lw s3`), which only the `s64` read gives (with `s32`, PRE substitutes the second load
  with the first, which keeps the value in a1). `(s64)self->cursor != 1` is not enough: the
  front end shortens the comparison back to 32 bits.
- **Diagnosing it.** cc1plus given `-dG` writes `unit.ii.gcse`: the blocks with their
  predecessors and successors, the expression table (`Index N`), and one line per PRE deletion
  (`PRE: redundant insn I (expression N) in bb B, reaching reg is R`) and per copy it inserts.
  A load that retail repeats and ours takes from a register is one of these lines.
- **Ruled out for that load** (func_001F0AE0): about 25 statement shapes of the test and the
  selection, byte-offset reads, a local copy, a reference-returning inline accessor (cse
  folds the address back to `self + 732`), and a `long` cast in the comparison.
- **The table's size is the function's insn count, and it orders the pseudos PRE makes.**
  alloc_expr_hash_table sizes the expression table `n_insns / 2`, made odd, with `n_insns` the
  number of insns when gcse starts (the `.addressof` dump: count the `(insn`, `(jump_insn` and
  `(call_insn` lines; this compiler's table is the public formula's for that count plus 3, so
  824 gives 413 buckets and 825 gives 415). The table is walked bucket by bucket, so its size
  sets the order of the reaching registers PRE creates, and reload gives spilled pseudos their
  stack slots in pseudo order. One insn more or less anywhere in a big function can reorder
  its spill slots (func_00179A68: a statement that adds one insn put one slot at the end of
  eight). Each Vu0::Vec value passed to or returned from an inline is a `movti` copy at that
  point (vu0.h), so the Vec and u128 forms of one expression are the knob: write the form whose
  count keeps the table retail's. `-dG` prints the size: `Expression hash table (N buckets`.
- **The bucket is the hash of the expression's registers too, so pseudo numbers move slots**
  (2026-11-08, func_00162890). hash_expr_1 adds a register's number and a constant's value, so
  in this build `(plus (reg R) (const_int C))` falls in bucket (13258 + R + C) mod T and
  `(and (reg R) (const_int C))` in (13266 + R + C) mod T; a frame address is R = 1 (the soft
  frame pointer). pre_delete walks the buckets in order and gives each redundant expression
  its reaching register with gen_reg_rtx as it meets it, so the PRE pseudos, and through
  reload the spill slots of those that spill, come in bucket order. Both T and the pseudo
  numbers of the loop counters and pointers in those expressions decide it. Sorting the 13
  slots retail's ReadPlacedObjectModel spills by these formulas, over T and the pseudo
  numbers, needed T = 483 (ours 481: one insn more) and its morph-loop pointer 53 to 56
  pseudos later. Unused locals and an extra call proved the model (retail's slot order
  exactly) before any real source was found; then each candidate form was scored by its
  insn count and pseudo numbers from the `-dF` and `-dG` dumps before its bytes.
- **What costs pseudos and not insns.** Pseudos are numbered as the front end expands, and
  cse deletes the copies that leave no use, so a source form can add pseudos and leave the
  insn count alone: a count read into its own named local and its byte size written at each
  use (`s32 nverts = ReadBufferedU16(stream);` and `nverts * 12` twice, +6 each against one
  reused `size`), a multiplication by an element size where we had a shift (`n * 16` against
  `n << 4`: +1 each), and an inline's body (each call copies its arguments into new pseudos
  and every pseudo of the body: `u32& v = *(u32*)p; ... v += d;` costs 4 more per call than
  `u32 v = *p; ... *p = v + d;`). A value read twice where we had a local for it
  (`if (strip->extra != 0) { StripExtra* e = strip->extra;`) adds the one insn the table
  needed: cse leaves the second load, and later passes delete it.
- **Two spill slots swapped, read off the formula before any compile** (2026-11-08,
  func_001841D0). RefreshConeVolumeShape's last FitUnitRampBetweenPair call spills two
  addresses PRE hoists above an earlier call: `&self->rangeMin`, (plus (reg 116) 816), and
  `&ramp[1][3]`, (plus (reg 1) 300). Ours had 319 insns at gcse, T = 161, buckets 22 and 35,
  so rangeMin's pseudo came first and took the lower slot (0x140); retail has it at 0x144.
  The formula, (13258 + R + C) mod T, puts the frame address first for T in 145..157 and
  167..171 (and 183..187), so retail had 5 or more insns fewer or 10 to 21 more. Each
  expression written with Vu0::Vec values instead of u128 adds 6 or 7 movti copies and leaves
  the code alone; the six plane distances in Vec form (the loop's four, far, near: +20, T =
  171) give retail's slots, as do the three MulX scalings (+18, T = 169); converting all seven
  (T = 181) or four (T = 173) does not, as predicted. The six distances as Vec values landed.
- **The order of an inline's parameters orders loop.c's invariants.** In that function the
  three Fix calls in the inner loop hoist `&strip->qwc[n]` and `&starts[n]` out of the loop;
  global-alloc then takes the one of higher priority first, and their priorities differ only
  by one insn of life: the one born first lives longer and is placed second. With the size before the start in
  the helper's parameters (RemapMeshQueueValues's own order), the qwc address is computed
  first and the two take retail's registers.
- **Bucket order also picks callee-saved registers, not only spill slots** (2026-11-08,
  func_001E4578). A call between two loops takes `&lo`, `&hi`, `&count` and `&list`; PRE finds
  each frame address partially redundant and hoists it, with a reaching register of its own,
  before the first loop, so each lives across a call and gets a saved register. Those
  pseudos tie in global-alloc's priority (2 refs over the same life, 0.067 each), and a tie
  falls to the allocno number, which is the pseudo number: bucket order. With T = 75 (149
  insns, the u128 form) `&hi` (offset 16) is in bucket 0 and takes s0 before `&count` (176)
  and `&list` (180); retail has them in s0, s1 and s5 the other way round, which needs a T
  where (13258 + 1 + 16) mod T is after the other two (71, 73, 83, 85, 91 to 97, 101; not 75,
  77, 79, 89, 99). Shortening our function by three insns (deleting a statement) gave
  retail's three registers at once, which proved the model; the source that has it is the
  project's Vec form throughout (each inline's argument and result a `movti`): 200 insns,
  T = 101. The intermediate mixes (199 insns, T = 99) and a pointer walk for the second loop
  (T = 97, retail's Gather registers but a tie lost in that loop) told the forms apart before
  their bytes. A `Vu0::Set(x, v.q)` store against `*(Vu0::Vec*)&x = v` is one insn, so a
  function that mixes the two can land on any of several sizes; the uniform Vec form is the
  plausible one, and it is retail's here.

- **A tie of two hoisted frame addresses, read off the hash values** (2026-11-08,
  func_001BA5B0). PRE hoists seven frame addresses (`&target2`, `&spin`, `&spinAlong`, ...)
  before the first of four gain loops; `&spin` (sp+48) and `&spinAlong` (sp+176) live over the
  same 54 insns with 2 refs each, so global-alloc takes the lower pseudo first. The gcse dump
  prints each expression's hash value: (plus at N) hashes to 13259 + N, so with T = 191 (377
  insns) &spinAlong is bucket 65 and &spin bucket 128, and &spinAlong takes s4. Retail has
  &spin in s4, which needs no multiple of T between 13307 and 13435: T = 187, 195, 201, 207, ...
  not 189, 191, 193. Over these sizes T came out as (insns + 4) / 2 | 1. The dot product of
  the last block written with Vec operands (`Dot(Vec::Of(a), Vec::Of(b))`, the project's form)
  is seven insns more: 384, T = 195, retail's two registers and nothing else changed.

- **Two hoisted symbol halves, placed in index order and numbered in bucket order** (2026-11-09,
  PAL's func_0016AB38). PRE hoists the `lui` of both arguments of the last call,
  `PushStackElement(g_elementStack, &D_0026FA90)`, to the entry. pre_edge_insert places the
  copies in expression-index order (the order the expressions first appear: the first
  argument's first), pre_delete numbers their reaching registers in bucket order, and both
  live to the call's argument moves, made in argument order, so the two lives tie and the
  lower pseudo takes s7. A `(high (symbol_ref "NAME"))` hashes to 7933 + h (HIGH 119, SImode
  6, SYMBOL_REF 61 << 7), h the name's characters folded as `h += (h << 7) + c` in 32 bits:
  D_00275BC0 comes before D_0026FA90 only for T = 77, 81, 85, 91, 99, 103, 113, 115, ... and
  ours had T = 95, so D_0026FA90's half took s7. Retail has D_00275BC0's first and in s7; the
  old near miss read FA90's address into a local first, which put that half first and gave
  the right registers in the wrong order. Three extra stores proved T = 99 before any real
  source; the form that lands is the switch with each case's own `v &= 1` (no shared tail),
  the previous level's index read in the condition, and each TeleportStateWalker's key read
  into its own local (T = 99). Read the size from `-dG` ("hash table (N buckets", the
  expression table is the second): the `.addressof` count was up to 5 short of it here.

### Sony's compiler: the same bucket order, and what it hashes (func_00211618)

The libraries' compiler (2.9-ee-991111) has the same PRE and the same tie. In the MPEG bit
reader's advance (src/lib/mpeg_bit_reader.cpp, 2026-11-08), the update after the refill loop,
`self->consumed += n`, joins the loop's exit and the branch around it; PRE copies the load of
`consumed` and `(s64)n` (a `sign_extend:DI` of n's pseudo) into both arms, and their reaching
registers tie in global-alloc (4 refs over 24 insns each: sched1 puts the load first in one arm
and the extension first in the other, so the lives are equal). The tie falls to bucket order:
with 34 to 35 insns at gcse, T = 17, the load is in bucket 2 and the extension in bucket 15,
so the load takes $t1 and n $t2; retail has them the other way round. What was measured:

- **T is `max_cuid / 2`, made odd, at least 11** (gcse.c's `alloc_expr_hash_table`; the cuid
  count is every insn of the `.addressof` dump): 34 and 35 insns give 17, 36 to 39 give 19.
  For this function the `(n+3)/2|1` of the section above does not hold; read T from `-dG`.
- **This compiler does not hash a MEM's alias set.** A unit that gave `unsigned long` alias set
  24 instead of 6 left the load's bucket unchanged. Alias sets here are numbered as types are
  first used (1 to 5 are taken before the first function: `int` is 5), but they do not move
  buckets.
- **The two buckets, measured for T from 11 to 77** (one test function per size): the
  extension comes first for T = 11, 13, 21, 23, 25, 29, 33, 35, 37, 39, 43, 47, ... and the load
  for T = 15, 17, 19, 27, 31, 41, 45, 49, ... So retail's function had at least 40 insns at gcse
  (6 more than the plain form, all gone by the end) or a different pseudo in the extension.
- **The pseudo in the extension moves its bucket by one per number.** `s32 count = n;` used for
  the update, declared as the function's third to fifth pseudo (119 to 121), gives retail's
  bytes exactly; declared first (118) it is bucket 16, still after; copied later, cse
  substitutes n back. The only way found to put it there was unused locals before it, which the
  rules forbid, so it is not landed.
- **What adds insns that vanish:** a `u32` byte widened to `u64` (`dsll32`/`dsrl32` that combine
  folds into the `lbu`, +2), `self->loaded += 8` re-reading the field after the join (+1, PRE
  deletes it), returning the new count (`return self->consumed += n;`, +2: the copy to $v0 and
  its use). Together they reach 39, still T = 19; the loop's shape (`while`, `if` and
  `do`/`while`, `for`, `<= 56`) and locals for the first statements add nothing more, because
  cse1 removes every other copy. Inline helpers for the refill or the update keep n's pseudo.
- **The copy cse keeps: a local the loop tests, set from the field** (2026-11-09, matched). cse1
  substitutes a copy's source within its path and deletes the copy only when no use is left; a
  variable the loop's test reads across the back edge keeps a use outside the path, so `loaded = self->loaded += 8;` at the end of the body (the
  chained assignment's copy into the local) survives to gcse, and cprop and flow delete it
  afterwards. With the byte read into a `u8` local (a QImode load and its widening, which combine
  folds into the `lbu`, +1) and the new count returned (+2), the advance has 40 insns at gcse,
  T = 21, the extension's bucket comes first and n takes $t1: retail's bytes. The body still reads
  `self->loaded` for the shift, as retail reloads it each pass; the local only carries the test.
  Count `(insn/i` lines too when measuring: an inline's insns are marked `insn/i`.

### Three spilled array addresses and a dot helper's copies (func_00186BA8)

The contacts between two colliders' edge hits (2026-11-09) spill three frame addresses PRE
hoists out of the GroupEdgesByKey loop, `&groupCounts` (sp+28688), `&keys` (sp+28704) and
`&groups` (sp+29216); retail's slots hold them in the order groupCounts, groups, keys. By
(13259 + C) mod T that order needs T = 103, 105, 129, 131, 171 to 175, 257, 261 or 263 (none
from 201 to 255), and the near miss had 463 insns (T = 233), the path loop's operands named
479 (T = 241). Three extra calls at the end (511 insns, T = 257) gave retail's slots before
any source did. What landed is the uniform Vec form of every dot product: a file-local
`DotFloat(Vu0::Vec a, Vu0::Vec b)` (and its ToFloatMoved twin for the last contact, whose
conversion retail schedules as the compiler's own) costs 4 insns a call over
`ToFloat(Dot(Vec::Of(x), Vec::Of(y)))` (two movti parameter copies), and the edge test's
differences named as Vec locals 2 each: 511 insns, T = 257, and the build matches. A float dot
of two vectors is the ordinary helper of such code; the per-call cost is the knob. Measured
deltas on the way, each with the same final code: a Vec param for the point only (+2 a call),
a named Vec operand (+2), `*(Vu0::Vec*)&x = v` against `Vu0::Set(x, v.q)` (+2), a pointer
local read twice instead (+0 to +1).

- **The path loop's blends** (`pts[k] = seg[2k] * (1 - t) + seg[2k+1] * t`) are func_00191570's
  shape: retail stores the 1 - t weight, loads the first end, stores t, loads the second, so
  the operands are named in that order (`Vec s0 = Scalar(1 - params[0]); Vec a0 = Of(*seg[0]);
  Vec t0 = Scalar(params[0]); Vec b0 = Of(*seg[1]);`). Written as MulXSum's arguments, the
  first pair's weights were computed before the second pair's loads and every VU register of
  the block differed.
- **The lowest float was the compiler's literal.** With `extern const f32 D = -FLT_MAX` defined
  in the file, g++ folds the read into a literal of its own and emits a second word, which
  moved the next data by 4 in the full build (check.py's literal check passes it). Written as
  the literal `-3.40282347e+38f`, the constant is retail's word at 0x24B258.

### A store after the join copies its pointer into a pseudo (func_00126CB8)

`if (c) rate = a; else rate = b; p->node->rate = rate;` and the same store written in each arm
give the same final code (cross-jumping merges the two stores after reload, and reorg fills the
branch's delay slot with the load both arms share), but not the same registers. With one store
after the join, GCSE's copy propagation leaves each arm's load of `p->node` in its own pseudo and a
copy into the pseudo the join's store reads (`r133 = r125`). sched1 places that copy in the arm's
block, here between the float load of `node->level` and its use: the level's span in local-alloc
grows from 2 insns to 3, the constant's (2) is now shorter, local-alloc places the constant first
and gives it `$f1`. With a store in each arm there is no copy; the two spans tie and the value born
first, the level, takes `$f1`, as retail has it. A swap of two short-lived temporaries in one arm of
an if/else whose result is stored after the join points at retail storing in each arm. (The
sibling func_00126D60, the same shape, has its store after the join: the original wrote both.)

### A call that ends an arm leaves flow's nop, which takes an issue slot (func_0013BF68)

`if (m) { Collect(&n, &list); ... } else { Gather(r, w, 0, &self->v610, ..., &n, &list); }`
followed by `pos = &self->v610; rot = &self->m620; ...` once after the join gives retail's code;
the same four assignments written at the end of each arm put the else arm's `move s5, s0` (pos,
copied from the call's argument address) in the call's delay slot where retail has the last
argument (`addiu t2, sp, 116`) and the copy after the call. Everything else is the same, registers
included.

- **The nop.** With the assignments after the join, the else arm ends with the call when gcse
  builds its flow graph, so find_basic_blocks (flow.c) emits `(use (const_int 0))` after the
  call ("so that the CALL_INSN itself is not at basic_block_end"). PRE then copies the four
  addresses into each arm's end (the else arm's `self + 0x610` is its argument's pseudo, so
  pos becomes a copy of it), after the nop.
- **The issue slot.** The nop stays in the block through reload and sched2. It has no unit
  (`none` in the dependence table) but counts against the issue rate (2) like any insn
  (schedule_block's `can_issue_more--`). Before the call there are 11 insns that the call
  depends on and pos's copy (priority 1, ready from cycle 2): without the nop the copy takes the
  one free slot, in cycle 6 beside the last argument, and reorg's backward fill puts the copy
  in the delay slot. With the nop, the nop (priority 1, earlier insn order) takes that slot, the
  copy issues with the call in cycle 7 (the call first, priority 4), and reorg fills the slot
  with the last argument, as retail.
- **Reading it.** A call whose delay slot holds the last argument move, with a copy that does
  not depend on the call just after it, where ours puts the copy in the slot: count the insns
  before the call in sched2's table. One short means retail had flow's nop, so the call ended
  its block when gcse ran; the statements after it were after a join in the source.

### Three loops over one count: `--i >= 0` keeps PRE off `n - 1` (func_00186568)

- **What differed.** Three loops run down the same list of n records. Retail spills n itself
  (`sw a2,0(sp)` in the prologue) and each loop starts from a reload, `lw v1,0(sp); addiu
  a2,v1,-1`. Written `for (i = n - 1; i >= 0; i--)` three times, the gcse dump shows PRE taking
  the third loop's `(plus n -1)` as redundant with the second's ("PRE: redundant insn ...
  reaching reg is 237", a copy inserted after the second loop's init): the pseudo holding
  `n - 1` lives across the second loop's call and is the spilled one, n dies early, and the
  counters and stack slots all move (50 lines differ).
- **The form.** `for (i = n; --i >= 0; )`: the init is `i = n` and the decrement is a
  computation of i, which every loop kills, so no expression of n alone is left for PRE to
  share; n stays live to the last loop and is spilled as retail's. 50 lines to 14.
- **The rest: one variable reused.** Retail keeps the record's face in t0 in all three loops,
  where three loop-local pointers took three registers: one `MeshFace* f;` declared with i at
  the top and assigned in each loop (a user variable set more than once is global-alloc's,
  docs above: func_0018AE38). And `addu v0,t3,v0` (base first) is a pointer set from the sum,
  `MeshFace* far = &faces[e->face[1]]; if (!(far->flags & 1))`, not the index inside the
  memory reference (expr.c puts the index first there; a pointer set from a sum keeps the
  source order). EXACT.
- **Reading it.** A loop bound retail reloads from the stack before each of several loops,
  where ours reloads `n - 1` (or keeps it in a register): the original counted with
  `--i >= 0` (or another form whose init is not an expression of the bound).

### Pointer copies for an inner loop: CSE2 makes them canonical for PRE's increments (func_001C4C20)

- **What differed.** An outer loop over three vertex arrays (`src++, cur++, dst++` at its end)
  holds an inner loop over a vertex's three floats. Written with walking pointer copies
  (`f32* c = (f32*)cur; ... c++`), the near miss stood at 56.9%: retail's `addiu s6,a0,16`
  (cur's next value, which PRE hoists from the outer loop's end into the block before the inner
  loop) became `addiu s8,s0,16`, read from the copy c. The gcse and loop dumps still show
  `(plus (reg cur) 16)`; the sched dump shows `(plus (reg c) 16)`: CSE after loop
  (-frerun-cse-after-loop) put c, the copy made just before and live longer, first in the
  equivalence class (make_regs_eqv), so the hoisted increments depend on the copies. That
  raised the copies' sched1 priority (2 against 1), moved every hoisted increment and the
  counter's `i - 1` later in the block, shortened the `i - 1` pseudo's life and ranked it above
  the rotation's address in global-alloc: retail spills the counter's slot and keeps the address
  in s8; ours spilled the address.
- **The form.** The inner loop indexes the floats, `(&cur->x)[k]`, `(&world.x)[k]`,
  `(&dst->x)[k]` with `for (k = 0; k < 3; k++)`: loop.c reduces the indexes to walking pointers
  and reverses k (retail's `li s3,2 ... bgez s3`), its pointer inits coming after PRE's copies,
  so no copy precedes the increments when CSE2 runs. 11 lines left; the outer count written
  `for (i = n; --i >= 0; )` (above) instead of `i = n - 1; i >= 0; i--` gave the rest. EXACT.
- **Reading it.** Retail's hoisted pointer increments reading the outer pointers while the inner
  loop walks registers of its own: the inner loop was written with an index, not with copies.

### Where PRE puts a loop's `i + 1`: the skip edge's block (func_001F3140, unsolved)

`for (i = 0; i < n; i++) { e = &entries[i]; if (e->used == 0) { inner loop; sum += span; } }`.
Retail's `addiu v0,a3,1` in the `bnez` delay slot and `move a3,v0` at the latch are PRE's: the
latch's `i + 1` is deleted (`i = r181`) and r181 is computed before the skipped body. The
difference is only where r181 is born, and it decides every GPR of the loop (2026-11-09):

- **The insertion points.** With lcm.c's `latein = delayin` (above), PRE inserts the
  expression at the end of every block on the delayed chain from the loop top whose
  successors are not all isolated. The skip from the loop top to the latch is a critical edge,
  so the loop-top block itself gets `r181 = i + 1` before its `bnez` (and the inner loop's
  preheader a second copy, which cse2 turns into `r181 = r181`).
- **sched1 hoists it.** In the loop-top block the add depends on nothing but `i`, so it issues
  in cycle 1 beside the `mult` of `i * 0xD0`. r181 is then live across the `mult`/`addiu`
  temporaries that local-alloc put in v0, so it conflicts with v0, loses its v0 preference
  (the latch's `slt` into v0, carried through `i = r181` by expand_preferences) to
  prune_preferences, and the entry pointer, first in global-alloc's order, takes v0. Every
  other register follows (21 lines differ).
- **What retail had.** Retail's r181 is born after the entry pointer's add: with the add held
  after the load (a diagnostic `asm volatile("")` between the load and the test), or with a
  transparent block on the skip edge (a diagnostic `else { k = 0; }`, a dead set that flow
  deletes after gcse), the function is EXACT. In the second, ISOOUT of the loop-top block
  becomes true (the skip block is "isolated"), so PRE inserts at the end of the skip block and
  the preheader, never in the loop-top block; reorg then steals the skip block's add into the
  `bnez` slot and retargets the branch to the latch, which is retail's code.
- **Ruled out** (all give the same 21 lines or worse): `continue`, `else continue`, a one-case
  `switch`, `goto next`, a `while` loop, the cast address, no entry pointer, a post-increment
  index (loop.c then strength-reduces the `mult` away), an inline helper returning a flag or
  adding the span, a flag variable (not threaded), and the increment written in both arms
  (12 lines: the else arm's `i++` is in place and the latch's `move` falls into the vadd
  block).
- **Spotting it.** A loop index's `i + 1` in a branch delay slot, held in a register whose
  number the body's temporaries also use: retail's add was born late, so the skip edge of the
  original had a block of its own when gcse ran. A plain-C form that gives that block without
  a dead statement is still to be found.

### A copy in each arm is propagated into the join (func_00114BB0, matched 2026-11-10)

- **What differed.** AppendScriptLists links each list it appends after the last node and
  walks to the new end: `while (last->next) last = last->next;`. Written with `last = c;` in
  both arms of `if (head == 0)`, gcse's copy propagation (the -dG dump: "1 copy props") finds
  the copy `(set last c)` available at the join on both paths and rewrites the walk's first
  test (jump.c's copy of the exit test) to read `c->next`. Retail tests `last->next` (`lw
  v0,8(s2)`), and the PRE'd `n->next` load and the exit's `move` land differently (8 bytes
  short).
- **The form.** One `last = c;` after the if/else (each arm keeps only what differs: the new
  head's chain, or the store into the old end). The join's block then sets `last` itself and
  the copy is not "available" from the predecessors, so the walk reads `last`; reorg still
  copies the join's first load into the head arm's `b` delay slot.
- **Also needed:** the function gives its value back as a class (RetValue, as func_00118198
  and func_00119218): its `args->tag == 0` return keeps its own copy, destruction and return
  only so; with explicit calls jump2 cross-jumps that return into the last one. With the class
  alone the code was 8 bytes short and n took s1 instead of args' s0; the single copy after the
  join gave both (retail's registers follow from the walk's lives).
- **Spotting it.** A walk or test after a join that reads, in ours, the variable each arm
  copied from, and in retail the variable the arms copied to: write the copy once after the
  join.

### A frame address passed by an inline call is not GCSE's (func_00171238)

- **What differed.** After a guarded curve sample (`if (c->vt->m02) m02(c, t, 0, &vel);`)
  and `TransformDirectionBetweenFrames(frame, 0, &vel, &vel)`, ours kept `sp + 32` in a saved
  register across the sample's call; retail forms it again in the call's delay slot and at the
  join (`addiu a2, sp, 0x20` twice). The saved register pushed a value retail keeps in s0
  into a spill slot: 16 more bytes of frame and every register after it renumbered.
- **Why.** An argument written in the call expands to `(set (reg P) (plus fp 32))` and then
  a move into the argument register: P's set is in gcse's expression table. The expression
  is anticipated at the end of the test block (both successors compute it before any call),
  so PRE inserts it there (`-dG`: "PRE/HOIST: end of bb 30 ... expression 66") and after
  the arm's call, and cse2 then folds the arm's own computation into the hoisted pseudo,
  which now lives across the call. Passed to an inline function instead, the address is the
  inline's unmodified parameter: integrate.c substitutes it as a constant at each use, so
  each argument move is `(set (reg a2) (plus fp 32))` straight into the hard register,
  which gcse never records (hash_scan_set takes only sets of pseudos). No expression, no
  PRE.
- **The form.** The sample and its transform as one inline helper (`SampleCurveDirection(c,
  frame, t, &vel)`): the direction of a path curve at t in the world, a step the original
  plausibly had as a function of its own. The same function's first sample (`m01` with
  `&pos`) is PRE'd in retail (its address in s0), so that one stays written out.
- **Spotting it.** A frame address in a saved register (`addiu sN, sp, n` in a branch's delay
  slot before a guarded call) where retail forms it at each call: try the calls through an
  inline function taking the pointer.
- **Both uses in one block need the inline (func_001701B0, StepPlayer).** `StoreQuadword(&m.r[1],
  v)` followed by `SteerColliderTowardRotation(self, 0, 0, &m.r[0], &m.r[1], t)` kept `sp + 16`
  in s0 across the store's call; retail forms it in each call's delay slot. With only the steer
  call through an inline the address is still shared (cse1 replaces the hard register's
  constant source with the store's pseudo in the same block); with both calls in one inline
  taking `dir` (`SteerAlongDirection(self, &m.r[0], &m.r[1], v, t)`) neither use makes a
  pseudo: EXACT. The same function's prologue order (`mov.s $f20, $f12` before `sq ra`) came
  from a missing argument: StepCollider reads $f12 (`mov.s $f20, $f12` in its first insns), so
  the call is `StepCollider(self, t)`, as its other callers declare it.

### A rotation product's rows read after the stores (func_0016FD70)

func_0016FD70 (the player's upright torque) was 24 bytes short with every register after the
product renumbered. Four separate causes, found from `-dl -dS -dF -dG` dumps (2026-11-10):

- **The rows of b must have no alias base.** Retail loads row 0 of the player's matrix at
  `0xD0(s2)` and rows 1 and 2 at `0x10(s1)`, `0x20(s1)` (s1 = s2 + 0xD0), each after the two
  stores of the row before. find_base_term of `(plus R 16)` gives R's base only when R has
  REGNO_POINTER_FLAG; without it (and with an argument's VOIDmode base) the address has no base
  and base_alias_check lets it conflict with the frame stores. A pointer variable of the
  function (`Mat02* cur`), a reference variable, a pointer parameter's copy (integrate.c marks
  it) and a pointer an inline returns into a variable are all flagged, and their loads move to
  the top; MulRotationRowsIndexed's own `q = (const u128*)&b` comes out unflagged in the
  caller's RTL (`.lreg`: `user var`, no `pointer`) and its loads wait. But that q is set after
  the two calls that build the turn, where retail sets s1 in the first call's delay slot (it
  lives across both). Only a pointer variable of an inline, set at the inline's top before
  those calls, has both properties: `TiltRotation(&rot, &turn, self->rot, goal->r[2], &axis)`,
  an inline that reads m's rows through q from its first line (the angle from row 2, then the
  product), matched.
- **Q's reference return leaves an address pseudo per row local.** `Vu0::Q(x) = ...` inlines a
  function returning `u128&`; its result is a pseudo set to `(plus fp n)`, dead after cse but
  still in gcse's table, and GCSE then replaces a later `&v` of a block-scope local reusing the
  same frame offset by a copy of it: `sp + 224` (or 208, 240) in a saved register across the
  pivot's calls. Writing each row with `Vu0::Set` (which returns nothing) leaves no pseudo.
- **Two speeds whose addresses are passed are two scalars, not an array.** Retail's speeds
  are at 0x130 and 0x134, above the product's inline frame (0xD0 to 0x130), and the Scalar
  slots and the pivot's locals reuse 0xD0 after it. An `f32 speeds[2]` is an assign_temp local
  at its declaration (below the product, or reusing its freed BLKmode slot when declared after
  it); two `f32` locals whose addresses are taken go through ADDRESSOF and get their slots from
  purge_addressof, after every local: retail's offsets.
- **The clamp's result in its own register.** Retail clamps into $f2 and copies to $f11 after
  the join (`mov.s $f11, $f2`), for both clamps. A clamp whose returns set the result (or whose
  argument variable is reassigned) is expanded straight into the target variable. ValueRange's
  `Limit` (a local result `r` set in each arm, then `return r`) gives the copy when the target
  is a variable that lives past the block: the blend weight reused for the speed scale (`t =
  g_unitRange.Limit(EvalCurve3(D_00263770, k))`), which makes cse keep t as the class's head.
  The last five instructions then fell to `ToFloatMoved` for the ground speed (the other
  conversion first, as the brief's sched2 lever says).

### A named frame address is an expression; an argument register's is not (func_0016BEA0)

Read from gcse.c (hash_scan_set) and global.c with `-dG -dl -dg` dumps (2026-11-10,
DrawGridSelector):

- **Retail's sign.** `addiu a1,sp,48` before `addiu a0,sp,16` for SetTextLayoutColor, and in
  the loop and the tail `addiu a1,sp,48` / `addiu t2,sp,48` (rematerialized) while `&out`'s
  loop copy has s8. Ours set a0 first, and PRE's reaching register for `sp+48` (inserted at the
  end of the block before the loop) took the last saved register from `&out`'s copy.
- **Why.** gcse records only sets of pseudos. Through the inline methods (`out.Color(&slot.v)`)
  the frame address is substituted as a constant and set straight into `$a1`: no expression.
  PRE then inserts its own computation late (lazy code motion), so the reaching register lives
  from there to the tail: 5 refs over 72 insns beat `&out`'s copy (4 over 236) in
  global-alloc. Named
  (`s32* color = &slot.v; out.Color(color);`) the address is a pseudo set in the first block,
  the loop's and the tail's `sp+48` are redundant with it, the reaching register lives over the
  whole function and is spilled (its REG_EQUIV address is rematerialized at each use), and the
  set's extra dependent (PRE's copy) ranks it, and so `$a1`, before `$a0` in sched1.
- **Spot it.** An argument's frame address set before an earlier argument's, and the same
  offset rematerialized later in the function: the original named that address.

### MoveMemory's frame arguments: an inline's parameters set the argument registers directly (func_001B55C0)

Read from gcse.c (hash_scan_set, compute_transp, pre_insert), lcm.c (pre_lcm), calls.c
(precompute_register_parameters) and integrate.c, with the `-dF -dG -dL` dumps of the triangle
animator's strip walk (2026-11-10). Retail shifts two three-entry windows on the stack each time
round the strip loop, `MoveMemory(sp+32, sp+48, 32)` and `MoveMemory(sp+80, sp+88, 16)`, and an
inner loop reads `uv[next[j]].x` and `.y` (bases sp+80 and sp+84, which loop.c moves into the
inner loop's preheader). Written as plain calls, ours was 8 bytes short and its saved registers
rotated:

- **Calls never kill a frame address.** compute_hash_table records the call-clobbered registers
  as set by a call but leaves out FRAME_POINTER_REGNUM (MIPS's `$1` before elimination), so
  `(plus fp 80)` is transparent everywhere. A plain call's argument goes through a pseudo
  (calls.c copies any argument whose rtx_cost exceeds 2 to a register, and expand_expr's
  ADDR_EXPR has already forced the address into one), so the shift's `&uv[0]` is an
  anticipatable occurrence of the same expression the inner loop computes.
- **PRE then takes the inner loop's copy.** With `(plus fp 80)` ANTLOC in the shift's block,
  that block is LATEIN, the inner loop's occurrence is redundant, and pre_insert puts a fresh
  computation at the end of the shift's block (before the flags test's branch, whose delay slot
  it then fills): one word more than retail, and retail's `bnezl` with the latch's load is
  lost. The 8 bytes are that word and the inner loop label's alignment nop. The same goes for
  `&uv[1]` and `&tri[1]`: their PRE pseudos live across the whole loop and compete for the
  saved registers, so `&uv[1]` took retail's `&tri[2]` register.
- **Retail's arguments were not in the table.** hash_scan_set records only sets of pseudos; a
  set of `$a0` itself is never an expression. integrate.c gives a pointer parameter whose
  argument is a frame address a constant equivalent and substitutes it into every copied insn,
  so an inline function that passes its parameters on to the call (`template <class T> void
  DropFirst(T* w) { MoveMemory(w, w + 1, 2 * sizeof(T)); }`) leaves `(set (reg a0) (plus fp
  80))` and `(set (reg a1) (plus fp 88))`: no PRE, the inner loop's address moved by loop.c,
  retail's size and its saved registers (199 differing lines to 22).
- **Spotting it.** A call's frame-address arguments formed afresh at the call every time round a
  loop (`addiu a0,sp,K` in the loop, nothing kept in a saved register) while the same addresses
  passed to another function in the same loop are kept in saved registers: the first call went
  through an inline. An extra address computation before a branch, where retail forms it in a
  later loop's preheader, is PRE's insertion after a computation that should not have been in
  the table.

### A frame address PRE copies, StoreX's reload and one counter for two loops (func_00191290)

Three independent causes, each fixed at its own pass; the function matched once all three were.

- **PRE's copy of a frame address.** Retail keeps `&node1` in s0 for the first loop and passes
  `t3`, a copy made right after the block that set s0, to the search call after both loops. That
  is gcse.c's PRE: `&node1` computed again at the call (`SearchPointGraph(graph, &node1, ...)`)
  is redundant with the earlier `n1 = &node1`, so PRE gives the expression a reaching register
  and copies into it after the first computation. Passing `n1` itself has no copy (one insn
  short, and the loop labels' alignment nops move with it).
- **The minimum by an inline.** `n = maxOut < count ? maxOut : count` written in place, or as
  an if, gives `movn` into count's register or a `slt` that reads n's register: CSE makes the
  longer-lived n the copy's canonical register. Retail's `move s0,s7; slt v0,s7,v1; movz
  s0,v1,v0` is `static inline s32 MinOfCounts(s32 a, s32 b) { return a < b ? a : b; }` called
  as `MinOfCounts(maxOut, count)` (the helper player.cpp and agent.cpp already have).
- **StoreX instead of ToBits for a float member.** With `*(u32*)&l->length =
  Vu0::ToBits(...)` the qmfc2's GPR is a local-alloc quantity that dies at the store, right
  before the reload of `node1.links` from its frame slot. local-alloc first tries each quantity
  over its life widened by one insn at each end (`fake_birth`/`fake_death`, INSN_SCHEDULING),
  so the load that follows cannot take the qmfc2's v0 and takes v1, which pushes the index and
  the exit test one register up and the loop's pointer from a1 to a3. `Vu0::StoreX(l->length,
  ...)` makes the qmfc2 a reload (no quantity): the load takes v0 and every register falls into
  retail's place. Spot it: a value born just after a ToBits store in a register one above the
  one retail gives it.
- **One counter for both walks of a triangle's corners.** The links to the goal's corners and the
  loop that lowers their counts again both run `k` from 0 to 3; loop.c reverses each into a down
  counter in the biv's own pseudo. Declared once (`s32 k;` before the first of the two), the one
  pseudo conflicts with both loops' values and global-alloc gives it t0 in each, retail's
  registers; a counter per loop ranks below the corner pointer (42 insns of life against
  its 23) and takes t1 and a1. Sharing the first loop's or the copy loop's counter as
  well is worse: retail's registers show which loops share a variable.
- Taking the records by index (`PathLink* l = &links1[i]; PathNode* c = tri0[i];`, loop.c
  reducing both) instead of walking pointers kept the order and the size; the near miss's
  pointer walks reused one `l` and one `tp` for both loops, which ties their registers.

### A `%hi` copied into a second register: the store's block began with a label when cse ran (func_00140968, unsolved)

RefreshDiscStatus (`if (g_discStatus != status) g_discStatus = status; return g_discStatus ==
0x14;`), read from cse.c (cse_end_of_basic_block, cse_main), gcse.c (pre_insert,
pre_insert_copy_insn, pre_delete) and lcm.c with `-ds -dG -dt -dl -dg` dumps (2026-11-10):

- **Retail's sign.** `lui v1` before `move a0,v0`, `beq v0,a0` with `move a1,v1` in its delay
  slot, the store through a1 and the return's load through v1; the equal path skips the reload
  (reorg finds the target's `lw v0` redundant with the compare's and retargets past it). Ours
  has one address register: `bnel` with the store in the likely slot, 4 bytes short.
- **Why ours has one.** cse's blocks end only at a CODE_LABEL (cse_end_of_basic_block), so the
  then-arm of a plain `if` is in the compare's block and its `%hi` becomes the compare's
  pseudo before gcse runs: the expression has one occurrence, and PRE does nothing.
- **What gives retail's code.** When the arm begins with a label at cse time, its `%hi` stays a
  pseudo of its own. lcm.c then finds the `%hi` anticipated at the end of the compare's block
  and, lazy, inserts a new computation there (insert_insn_end_bb) rather than reuse the
  compare's; the arm's and the join's become copies of it, cse2 turns the insertion into a copy
  of the compare's pseudo, which lives on to the join, so the copy keeps a register of its own
  (a1) and sched1 raises the `lui` (it now has a dependent) above `move a0,v0`. Diagnostics
  that show it: `if (g_discStatus != status || status == 0x7fffffff)` (a real second test) gives
  retail's first seven instructions; `while (g_discStatus != status) g_discStatus = status;`
  (cse folds the loop's second test, after its top label made the store a block of its own)
  gives the whole shape, with status and the address in v1/a0 swapped and an extra `nop`.
- **Ruled out** (all the same 60 bytes): the comparison's operands swapped, an empty then-arm
  with an `else`, a pointer local, a reference- or pointer-returning inline accessor, an inline
  setter (`SetIfChanged(&g_discStatus, s)`), inline predicates (`bool`, `if/return`), a flag
  (`s32 changed`, `bool changed`), a named old value, an unused named label, a returned copy
  in each arm, and an early return: jump.c's first pass removes every jump into the arm that
  plain forms make before cse sees it.
- **Spotting it.** `move aN,vM` of a `%hi` register in a branch's delay slot, the store through
  the copy and later loads through the original: the store's block was entered by a jump that
  cse folded away (a loop's back edge or a redundant second test), not by the `if` alone.

## sched1

GCC 2.95's first scheduling pass (haifa-sched.c, run before register allocation) decides
which pseudos are live together, so it decides registers. How it chooses, read from its
source and `-dS -fsched-verbose-6` dumps (2026-11-08, func_00179A68):

- **A list scheduler, top-down, by cycle.** Each cycle the ready insns are sorted by
  `rank_for_schedule` (priority, then `INSN_REG_WEIGHT`, then the class of dependence on the
  last insn scheduled, then the number of dependents, then insn order) and issued from the best
  while their function unit is free (the machine description's units: memory, two alus,
  fmac, fdiv, flop). Insns of different units issue in the same cycle in rank order, and that
  order is the insn order register allocation sees. An insn's static priority (the `prio`
  column of the dump's dependence table) is the length of its longest path to the block's end
  in latency (a load 2, mul.s and add.s 3).
- **adjust_priority raises an insn that births a pseudo.** When an insn's last dependence is
  resolved, adjust_priority runs on it. Its REG_DEAD test never fires (the notes are gone by
  then), so the only case that acts is the "birthing" one: an insn whose single SET is a pseudo
  that is set once in the whole function (`REG_N_SETS == 1`) and live at the block's end
  (birthing_insn_p) gets its priority raised to `max_priority`, the higher of the insn just
  scheduled and the lowest-ranked ready insn. So a load into a variable or parameter set once
  outranks the arithmetic around it, and an add whose result is assigned again later (a
  clamp written in place, `v = lo` / `v = hi`) keeps its static priority.
- **Diagnosing it.** The dump's `Ready list (t = N):` lines list the sorted ready insns, best
  last; a priority that is not the table's `prio` is adjust_priority's.
- **ControlModeCollider (func_00179A68).** `f700 = Clamp(f700 + dt * f708, b[0], b[1])`
  written in place left the add at priority 7 while the load of `b[1]`, born once, went from 2
  to 8 when the store before it was scheduled. Both were ready in cycle 6; the load went first
  and was live across the product in $f0, so it got $f3 where retail has $f0. Written as a clamp
  that returns its result (`if (v < lo) return lo; if (hi < v) return hi; return v;`) the sum
  is a pseudo set once, the add is raised to 10 when the multiply is scheduled, and it is
  issued before the load: retail's registers. That form costs one insn more (the copy of v to
  the result), which moved one spill slot through gcse's table size (GCSE above); one Vec
  difference stored through `Vu0::Q(...) = ... .q` gives the insn back.
- **Which of two equal subtractions goes first decides a copy preference (func_001E31F0).**
  `t1 = clock - a; t2 = clock - b;` were ready in the same cycle at the same priority: both are
  set once and both were raised by adjust_priority by the same clock load, so INSN_REG_WEIGHT
  decided, and t2's ranks first (the shared clock dies in the later statement). Issued first, it
  leaves the clock to die in t1's, and global-alloc (`set_preference`: a source that dies in the
  insn) gives t1 a copy preference for the clock's $f1 ahead of $f12, the register of the
  division t1 feeds. What retail had was a different cycle, not a different rank: the next
  statement, `s = 0.0f; if (0.0f < object->f428)`, puts the zero (on the memory and flop units)
  before the load of f428 in insn order. Read into a local first (`f32 ramp = object->f428; f32
  s = 0.0f; if (0.0f < ramp)`, the second division reading the field again as retail does), the
  load issues first and the zero's flop slot delays t2's add by a cycle. t1's subtraction is
  then ready alone, issues first, and t1 takes $f12. The cost was one insn of t2's life, which
  put t2 (3 refs over 13 insns, priority 0.231) ahead of `goal` (9 refs over 125, 0.216) in
  global-alloc's order, so the two swapped $f22 and $f23. Retail's `goal` has one assignment more:
  `if (!(flags & 2)) goal = angle1; else if (0.0f < d) goal = angle1; else goal = angle2;`
  instead of `||` gives 10 refs (priority 0.24), and the function matches. global.c's priority is
  `floor_log2(refs) * refs / live_length`, so one ref can reorder two pseudos whose code is
  identical.

### Two loads tied at one priority: name the term retail loads first (func_0016BEA0)

DrawGridSelector's first cell's y (`self->y + fontH * fontSy + gap + cellH * half`) and x:
retail loads the cell font's height and scale before the title font's and both before
`self->y` and `self->x`. The title font's loads wait two cycles for `self->font`, and among
the ready loads of equal priority INSN_LUID decides, so the cell's height named first (`f32
cellW = f->Width('_'); f32 cellH = (f32)f->height * f->sy;`, then y0, then x0) gives retail's
order and registers; the step (`dy`) still reads the font again after the second Width call,
as retail does.

- **PAL's frame (func_0016C4C8).** PAL draws the title through a 0xC0-byte text buffer at 0x40
  while the colour slot, the cell string and the line's colour share 0x30 and the string's
  initializer temporary is at 0x100. The colour slot in a block, freed as a 16-byte slot that
  the buffer does not fit, and the buffer declared at function level after the block give that
  layout; the buffer in a block of its own is freed and the temporary moves into it.

### Argument moves held back to a call's own block: what is and is not a barrier (func_001DEBE8, unsolved)

From haifa-sched.c of GCC 2.95.3 (sched_analyze, sched_analyze_insn) and the `-dS -dR
-fsched-verbose-6` dumps (2026-11-10):

- **Retail:** the third BuildAxisAngleMatrix's `lui v0, %hi(K); addiu a1, sp, 0x80; lwc1 $f12;
  move a0, s4` come after every store of the matrix block before it. Ours issues the lui and
  the two argument moves in idle alu slots among the block's loads (they depend only on the
  previous call), in sched1 and again in sched2, and the lui then takes v1 (v0 holds
  `self + 0x660` there).
- **Only a barrier gives retail's order.** An insn depends on everything before it and
  everything after depends on it when it is a volatile asm, an ASM_INPUT (an asm without
  operands, even non-volatile), an UNSPEC_VOLATILE, or the first insn after a
  NOTE_INSN_LOOP_BEG/END, EH-region or setjmp note. An empty `__asm__ volatile("")` before the
  call (diagnostic only) gives retail's four insns and their registers. A `do { } while (0)` (or
  `for (;;) break;`) there does too, but its loop notes also add an aligned label's `nop` in a
  later clamp (1704 bytes): retail has no loop there.
- Not yet found: which plain C++ the original had there. A REG_EQUIV pseudo used once in another
  block is moved before its use by update_equiv_regs (after sched1), which would explain the
  lui but not the two argument moves.

### sched2 keeps sched1's dependences (func_001358D0)

- **LOG_LINKS are never cleared.** haifa-sched.c's sched_analyze only adds to an insn's
  LOG_LINKS (add_dependence skips a link it already has); nothing frees them between sched1 and
  sched2. So sched2 also sees every dependence sched1 had, on pseudos and hard registers that
  reload has since changed: a stale link still counts as a dependent in rank_for_schedule.
- **What that decides: two argument loads of one call.** After reload, rank_for_schedule has no
  register weight; at equal priority the class of dependence on the last insn, then the number
  of dependents, then insn order decide. In CollectPanelEntriesOfClass the first
  `ArctangentOfRatio(d.y, d.x)` loads $f12 and $f13 at the same priority, and the next call's
  arguments (`d.z`, `ToFloat(Sqrt(DotXY(v, v)))`) set the same two registers again. With
  ToFloat, combine had put the asm's output straight into $f13 (`(set $f13 (asm_operands
  "qmfc2"))`, invalid for "=r", so reload added v0 and an mtc1): the qmfc2 kept sched1's output
  dependence on the $f13 load and the mtc1 got its own, so that load had one dependent more than
  the $f12 load (7 to 6), issued first, and the $f12 load went to the call's delay slot, the
  reverse of retail's. With ToFloatMoved (`mtc1` alone, the qmfc2 the compiler's into a pseudo),
  only the mtc1 depends on the $f13 load, the two loads tie at 6, and sched1's order ($f12
  first) stands: retail's (PAL's too, with the caption box's fields at PAL's offsets). ToFloatMoved
  is the helper already used wherever retail's qmfc2 is the compiler's own copy (agent.cpp's
  distances, the length tests above); nothing else changes. The forward-dependence table of `-dS -fsched-verbose-6`'s `.sched2`
  dump lists each insn's dependents; a link in the RTL whose register no longer matches is a
  stale one.

### A block whose first cycle holds one insn: reorg's two copies (func_0020BB18, unsolved)

Read from haifa-sched.c (schedule_block, rank_for_schedule, sched_analyze_insn), reorg.c
(fill_eager_delay_slots, fill_slots_from_thread, own_thread_p) and the `-dS -dR -fsched-verbose-6`
dumps of func_0020BB18 (src/lib/mpeg_decoder.cpp, Sony's 2.9-ee-991111, 2026-11-10):

- **What retail shows.** After `if (w == pic->width && h == pic->height) return;` retail has
  `bne s7,v1,L` and `beq s6,v0,RET` with the same `addiu v0,s8,1320` (the last plane's address,
  a spilled pseudo) in both delay slots, and L is the height store. Ours has `bnel` with the
  height store and `beq` with the epilogue's `ld ra`, and from there the body one insn off.
- **Read backwards through reorg.** The bne's target label is also reached by the beq's
  fallthrough, so own_thread_p is false and fill_slots_from_thread can take only the thread's
  first insn (`(! lose || own_thread)` stops the scan at the first skipped insn). Retail's copy
  in the bne slot means the address was the body's first insn after sched2; the copy retargets
  the bne past it, the old label loses its last use, the beq's fallthrough becomes its own thread
  and the beq takes the insn itself. With the height store first (ours), the likely bne (an `NE`
  test) takes the store into an annulled slot instead.
- **Read backwards through sched2.** Retail's body is exactly ours with that address issued
  alone in cycle 1 and every later insn one cycle later (each of our cycles' pairs then reads
  reversed against retail's). In ours the address and the height store tie at priority 65 in
  cycle 1 and the store wins on dependents (9 to 6: the spill-slot stores conflict with it), so
  they share the cycle. No order of the stores, the size, the tests or the planes' arguments
  changes that: a pair in one cycle is always sorted by rank, and for the address to be first
  and still alone the two picture stores must depend on it.
- **What reproduces it.** A scheduling barrier at the address: an insn that carries a loop note
  (sched_analyze_insn's schedule_barrier_found) depends on every earlier insn and every later one
  on it. `for (p8 = &st->planes[8].addr; 0; ) { }` at the top of the body gives retail's two
  delay slots and the whole test exactly (680 bytes, 35 lines left, all in the body: the extra
  notes are a second barrier, and the early-created pseudo takes the first spill slot, 48(sp),
  where retail's last plane has 68(sp), the slot of the last pseudo). That form is not plausible
  original code; it shows only what retail's sched2 saw: the last plane's address set alone at
  the head of the block, its pseudo created after the other five spilled addresses.
- **Ruled out** (all 102 lines, the near miss's score): the body inside `if (w != pic->width ||
  h != pic->height)`, the operands swapped, the picture's fields unsigned, w and h computed in
  the other order or as `* 16`, rows stored in both arms and read back, the size before the
  test, the stores after the size, an inline helper for the body (Sony's compiler calls it, not
  inlined), `do { } while (0)` around the body (128) or before it (123),
  `-fno-strict-aliasing`, `-O3`, `-fno-gcse` (146), the Linux 2.9-ee-991111-01 build (102).
- **Spot it.** Two branches into one block whose delay slots hold the same insn and whose
  target is the block's second insn: the copied insn was alone in sched2's first cycle.

### A value negated into itself crosses the call (func_001A2380)

- **sched1's call rule.** sched_analyze makes an insn that sets a pseudo depend (anti) on the
  last call only when the pseudo crosses no call (`REG_N_CALLS_CROSSED == 0`): such a pseudo
  must not be moved over a call. A pseudo that already lives across calls gets no such link.
- **What that decides.** AttachHitMarkEffect passes `size` to a virtual call and then stores its
  negation. Written `size = -size; ... e->m30[2] = size;`, the neg sets `size`'s own pseudo,
  which crosses calls: the neg has no link to the call, is ready with it, and sched2 issues the
  two in one cycle, so the 5.0 load and the high part of `&g_unitZVector` share the next cycle,
  one slot before retail's. Written `e->m30[2] = -size;`, the neg sets a fresh pseudo that
  crosses no call (local-alloc still ties it to `size`'s $f20, which dies there): it gets the
  anti link to the call, sched2 keeps that stale link (above), and the neg issues in the cycle
  after the call with the 5.0 load, which pushes every ALU insn of the next call's setup one
  cycle later: retail's interleaving of the four stores with the lui/addiu pairs, exact.
- **Reading it.** In the `.sched2` dump an insn that issues in the call's cycle and has no
  REG_DEP_ANTI to the call, where retail puts it one cycle later, is the sign: look for a
  reassigned variable that could be an expression instead.

### A compiler's qmfc2 of a VU0 product (func_00186230)

MeasurePointToLine (2026-11-09) tests `Dot(e, e) < 0.0001f`. Retail's head is: the product
in vf1, the dot's 1.0 in vf4, `a` in vf3, `p` loaded into vf2 before the qmfc2, then `qmfc2
v0,vf1; mtc1 v0,$f2; vsub vf1 = p - a; c.lt.s; sqc2 e; bc1f; (sqc2 w)`. Read from the
dumps, it needs two things at once:

- **local-alloc: the product a VU0 pseudo.** With ToFloat or ToFloatNow the product is
  VU_REGS, ranks first (ToFloatNow's two-output asm repeats its input: three refs) and takes
  vf1 over the dot's insn and the load of p, so p takes vf2, a vf3 and the 1.0 vf4, retail's
  registers. With ToFloatMoved the product has one `"=j"` def and one `"r"` use: both costs
  are a VU0-to-GPR move, regclass ties and picks the union TI_REGS, local-alloc gives it v0
  and the asm's output reload uses vf1 after every VU0 pseudo has its register: p takes vf1,
  a vf2 and the 1.0 vf3. No sched1 order fixes that (emulated with la.py over the .lreg: the
  1.0 can only reach vf4 if vf1 to vf3 are all taken around the dot, and without the product
  only b could hold vf1 there, which needs the load of p before the subtraction of b, ranked
  4 against the constant's 6 and the subtraction's 7).
- **sched2: the qmfc2 the compiler's.** At cycle 5 the dot is done and the ready list holds
  the conversion and the sqc2 of e (priority 2). An asm's qmfc2 (ToFloat, ToFloatNow,
  ToFloatViaBits) has no function unit, so both issue and the store lands before the
  subtraction of w, which waits on the conversion's read of vf1 (an anti dependence, and
  insns made ready in a cycle never issue in it: schedule_block moves the last ready insn
  into the issued one's slot and counts down past it). The compiler's qmfc2 (a movti
  reload, unit vu0) takes the vu0 unit the sqc2 also needs: the store waits, the mtc1 and the
  subtraction issue at cycle 6, the c.lt.s and the store at 7, and reorg puts the sqc2 of w
  in the branch's delay slot: retail's order. Probed with a ToFloatMoved whose asm also takes
  the product as a dummy `"j"` operand: the product becomes VU_REGS and the qmfc2 the
  compiler's, but the subtraction then waits on the mtc1 that names vf1, and the store still
  comes first.

What retail had is a product in VU_REGS whose only reader takes it as `"r"`: some second
VU0 reference that leaves no code (a loop's weight, a copy CSE keeps), and none of the
plain forms found has one. Ruled out: a user variable for the product (CSE folds the copy:
the variable is canonical only if it lives beyond the block), the same variable reused for
the arms' squared distances (global, vf4), a truncating cast (sign extension), a union or
`*(f32*)&` (memory), the product converted again in the else arm (CSE shares the float).
The near miss keeps ToFloatNow (every register retail's, the sqc2 one slot early); ToFloatNow
for the else arm's dot also puts the division before the mfc1 of 1.0, as retail has it, and
the distance stored as `*(u32*)dist = ToBits(Sqrt(d))` gives the square root vf1 (StoreX's
"r" operand put it in vf2).

MeasurePointToSegment (func_00186320, 2026-11-09) has the same head and the same wall: with
ToFloatNow for the length, ToBits for the distance and the reused float variable above
("A reused float variable joins two lives' conflicts and preferences") every register is
retail's and only the sqc2 of e is one slot early (73 of 75 lines). Re-probed there: the
dummy `"j"` operand on ToFloatMoved gives the registers but makes the subtraction of p wait
on the asm's mtc1 (an anti dependence on vf1: ready at cycle 7, after the store issued at 6);
ToFloatMoved through Vec values (`Dot(Vec::Of(e), Vec::Of(e))`) still ties the product to
TI_REGS (the movti copies are tied away by local-alloc); storing e after the subtraction of p
in the source changes nothing (the store is ready from the subtraction of b on, whatever its
insn position). Retail's form needs the mtc1 to read only the GPR, with the product in
VU_REGS: two references for the product's class, one leaving no code.

### A block-scoped struct local frees its slot for a later Scalar (func_00154088)

Matched 2026-11-10 from the -dS dumps. LimitContactTangents (func_00154088) sums each contact's
vector over the active items into a Vec02 `acc` on the stack, then, after the search loop,
scales the best tangent by `Vu0::Scalar(1.0f / mag)`. Three separate differences, in cascade
order:

- **A counted inner loop, not a pointer walk.** Retail's `addiu a0,-1; bnez a0` with a `blez`
  entry test is loop.c's reversal (check_dbra_loop) of `for (k = 0; k < self->count; k++)`
  with the record taken by index (`items + k * 0x60`); the count is read before the items
  pointer, which is reloaded rather than copied. A walk `for (k = count; k > 0; k--)
  other++` gives `bgtz` and CSE's copy of the outer loop's items register, and moves the
  outer loop's registers (37 of 77 differing lines went with this alone).
- **A value set after a call, declared after it.** `s32 bestIndex = -1;` written before the
  solver call crosses it and takes s0; after it, t2 as retail.
- **The weight's slot is acc's, because acc is declared in the loop body.** stmt.c's
  expand_decl gives a block's memory variable a kept temporary slot (assign_temp with keep),
  freed when the block ends; the tail's Scalar temporary then reuses it (both TImode), at
  16(sp) as retail. Declared at the top of the function, acc keeps 16(sp) and the Scalar takes
  the next slot, 32(sp). The tail also needed the Scalar directly (the scalar-slot lever): with
  `Q(acc) = FromFloat(1.0f / mag)` and `MulX(best, Q(acc))`, the store to acc has no alias
  class, so sched1 keeps the load of `it->twin` behind it, and MulX's result ties to the
  dying scale instead of `best` (retail's `vmulx vf1, vf1, vf2x`).

The handler at slot 0x108 takes `(self, flags, item, end, dt)`: retail's `mov.s $f12` fills the
call's delay slot after the a1-a3 moves, as in func_001BCD00; with dt second it goes first.

### An argument's frame address that sched2 holds back (func_0014F168, unsolved)

Read from haifa-sched.c, flow.c, reload1.c and toplev.c of GCC 2.95.3 and the `-dS -dR -dl
-dg -df -fsched-verbose-6` dumps (2026-11-09):

- **What retail shows.** func_0014F168's last block (after NormalizeOr's join) is retail's but
  for the call's `addiu a1, sp, 16` (the address of the sum `r` passed to the method at 0x90):
  ours issues it in cycle 3 beside `addiu v0` (it has no dependence and a free ALU slot), retail
  between the weight's `sqc2 vf3` and r's `sqc2 vf1`, i.e. in cycle 9 of the same schedule.
  Replaying sched2's cycles (two issues, one memory unit, the slot-swap quirk above) puts it
  there exactly if the insn becomes ready in cycles 5 to 9: a dependence on one of 316, 171,
  319, 214, 246 (the weights' loads and qmtc2s, unit Z's load), 269 (`move a0, s0`), 251 (the
  MulXSum asm), or an anti dependence on 242 or 131. Or if it is in a SCHED_GROUP with r's store
  261 or the weight's store 181 (adjacent to both in retail).
- **No plain form gives it one.** In sched2 `(set a1 (plus sp 16))` can only depend on an insn
  that touches a1 or sets sp (none in the block: reload_cse deletes no-op moves before sched2,
  reload deletes CLOBBERs and equivalence inits), on a barrier (a volatile asm, a loop or EH
  note: each would also hold 181, 224 or 269 where retail does not have them), or on a stale
  sched1 link. In sched1 the insn is combine's merge of Q's address pseudo into `$5 = $1+16`;
  had it stayed `$5 = P`, P's init is either deleted by reload (no hard reg: reload1.c makes a
  frame-plus-constant REG_EQUIV a reg_equiv_constant via function_invariant_p) or becomes the
  addiu itself (P in a1), with no link to any of the insns above either way. flow2's LOG_LINKS
  (life_analysis after reload) follow the post-reload registers and add nothing. SCHED_GROUP_P
  is set only for cc0 users and USE insns before a call.
- **Tried, unchanged (the addiu first):** a pointer to r for the store, the call or both; the
  `p` of d reused for r; Q's address through an inline returning it (`Put(&r, v)`); the call
  through an inline wrapper or a local function pointer; r as a Vu0::Vec copy; ScalarAtValue
  weights; earlier `*(u128*)&r`, Vu0::Set and the descriptor read after the sum or inside the
  call. ScalarAtCall weights and d read through p move other code (264 and 268 bytes); d and r
  as a two-element array breaks block 0. What retail had is outside this model: look for a
  construct that leaves an insn naming a1 (or a group) that the final code does not show.

### A store in each arm leaves the join block to sched2 (func_0013BE18, unsolved)

func_0013BE18 (src/main/child_group_object.cpp) has func_0014F168's tail (2026-11-09): d
normalized through NormalizeOr into `*p`, then `r = d * w1 + Z * w2` (MulXSum of two ScalarAt
weights) passed to ConstrainVectorByParentAnchor and the method at 0x90. With Vu0::ScalarAt for
the weights every register is retail's; what is left is the section above's: `addiu s0,sp,16`
(&r) and the argument moves issue early in ours, after the reload of d in retail. Here the
moves that hold back include `addiu a1,s1,1088` and `move t0,zero`, which name nothing any
earlier insn touches, so no dependence on &r explains it; the issue slots do.

- **The store at the join takes the slots.** In ours NormalizeOr's result is stored once, at
  the join (`sqc2 vf1,0(v1)`), and that store heads the join block that sched2 schedules with
  the weights, the sum and the call: a memory and vu0 insn of the highest priority whose unit
  is busy for three cycles, so the loads behind it queue and the ALU insns (&r, the moves) fill
  the free issue slots from cycle 3. Written with the store in each arm (`if (len < eps)
  *p = x; else *p = DivX(d, len);`, probes e1, e4, e5), the join block starts at the weights'
  lui, the slots are full of priority 12-14 insns, and &r and the moves come out where retail
  has them: `lqc2 vf1,0(sp); addiu s0,sp,16; vmulax; vmaddx; sqc2 vf3; move a3,s0; sqc2 vf1`
  (with Vec values for d, e5, the whole tail is retail's but for the two weights' lw order).
- **Retail stored in each arm.** toplev.c runs jump2's cross-jumping after sched2 (reload,
  flow2, sched2, then `jump_optimize (insns, JUMP_CROSS_JUMP, ...)`), so two identical stores
  at the ends of the arms are merged into one at the join after sched2 has scheduled the join
  block without them. Retail's fallback arm (`b join` with `qmtc2 v0,vf1` in the delay slot,
  the join `sqc2 vf1,0(v1)`) is what that merge leaves.
- **Not found: the arms' identical stores.** For the merge both arms must store the same
  register through the same register: retail's fallback arm copies the GPR-loaded fallback
  into vf1 and stores vf1 through p (v1). Written plainly, CSE replaces the arm's copy by the
  fallback itself and p by sp (`sq v0,0(sp)` against `sqc2 vf1,0(sp)`), the stores differ and
  stay in the arms. A store in each arm of one VU-class variable through a pointer CSE cannot
  resolve is what is needed; func_0014F168 has the same head and should share the answer.
  Spot it: a join block whose first insn is a store common to both arms, and an ALU insn that
  retail issues later than ours although nothing it reads or writes is touched before.

### The compiler's qmfc2 again, and a rescale's divide order (func_001D4348)

The player's blend weights (2026-11-09) compute three slot weights, each a dot product over
a length (`scale * Dot(v, v)`), and rescale them by their sum:

- **The rescale's divides go in source order only if the last one is where the sum dies.**
  `slots[0] = w0 / sum; slots[2] = w2 / sum; slots[4] = w4 / sum;` all have priority 8; the
  last divide kills both its inputs (INSN_REG_WEIGHT -1, the others 0), so sched1 issues it
  first and the others in insn order: w4, w0, w2, retail's order. local-alloc's equal spans then
  give the three quotients f0, f1, f2 in that order, and global-alloc's preferences
  (set_preference: a pseudo that dies into a local's hard register) put w4 in f0 and the sum in
  f2, retail's registers. Written in the order w4, w0, w2 the divides came out w2, w4, w0.
- **One sum, not one accumulated.** `sum = w0 + w2; sum = sum + w4;` is one pseudo with two
  sets (f2 throughout); retail's `add.s f1 = w0 + w2; add.s f2 = f1 + w4` is `sum = w0 + w2 +
  w4`, the partial sum a block-local temporary.
- **A conversion's mtc1 as an asm has a latency of 1.** ToFloat's mtc1 is reload's (cost 2):
  the mul.s of the length waits a cycle and the next conversion's mtc1 goes first. Retail's
  `mtc1 v0,f0; qmfc2 a0; mul.s f0` is ToFloatViaBits for the first length.
- **The same wall as func_00186230.** Retail issues the 1.0 constant's lui/mtc1 between the
  second length's qmfc2 and the next lqc2, and that order comes only from a compiler qmfc2
  (ToFloatMoved: unit vu0, which holds the lqc2). With ToFloatMoved every instruction is in
  retail's order, but the product becomes a TI_REGS pseudo in v0 and its output reload takes a
  VU0 register after the dot's scratch 1.0 took vf1 (ours vf3 and vf4 for the products, retail
  vf1). All six conversions as ToFloat give every one of retail's registers (reload's round
  robin alternates v0 and a0 over the six qmfc2) and lose the order. The near miss keeps the
  order; what is missing is still a product in VU_REGS whose qmfc2 is the compiler's.

### The same wall in a reach test, and what led up to it (func_001CEB18)

The player's reach test against a point carried to time t (2026-11-10) went from 30.7% to
97.8% (four lines) by reading the code again, not by variants:

- **Retail's operand, not the notes'.** The inside arm's `c1 0x20004` is sqrt.s with ft = $f2,
  the squared distance: `*out1 = Sqrt(dist2) - r`, where the near miss had `Sqrt(r * r)`.
- **Two early outcomes, each with its own tail and return.** Retail places the solve block
  last, falling into the epilogue, and shares one `swc1 $f0,0(s1)` between the two out1
  values: the source returns from both early cases, each repeating `out2 = pos0; out3 = v +
  t g`, and cross-jumping merges the tails after reload. Written as an if/else whose join
  holds the tail, the solve block comes first. With the tails in their arms the first block's
  `Scalar(t)` (one qmtc2) also serves both tails' weights: the frame grows to 208 with retail's
  spill at 0x60, and the tails keep their own slot stores. A named `u128 tv = Scalar(t)`
  instead copies the slot through a GPR.
- **The callee's parameter order.** TransformPointAtTime's `$f12` copy ranked last among the
  argument moves (INSN_LUID) and sched2 then issued `move a3,zero` before the sum; declared
  `(self, top, t, pos, rot, vel, spin)`, as player.cpp's matched caller has it, the float's copy
  ties ahead of a3's and the head is retail's. func_001259D8 stays EXACT defined that way.
- **The normalisation as an inline with the fallback by reference** (player_path.cpp's
  NormalizeVector): the fallback's address is formed before the length test, as retail has it.
- **What is left is func_00186230's wall.** After the call, retail issues the radius's lwc1
  before the vsub and the `r * r` before the distance's qmfc2. With ToFloat every register is
  retail's (product vf2, 1.0 vf3, the qmfc2 into reload's a0), but reload's mtc1 costs 2, so
  the subtraction's chain (1 + 1 + 1 + 2 + 4) ties the radius's (2 + 3 + 4) at 9 and wins on
  dependents (3 against 2), and the same tie puts the qmfc2 before the mul.s. A chain of 8
  (ToFloatMoved, ToFloatViaBits) gives retail's order in the dumps, but ToFloatViaBits' bits are
  a local pseudo in v0 (an anti dependence on the lwc1's base that pulls the load before the
  second lqc2), and ToFloatMoved makes the product TI_REGS in v0 with the 1.0 in vf2. Retail's
  a0 is a reload register: the compiler's qmfc2 of a product in VU_REGS, as in func_00186230.

### The rest of rank_for_schedule (func_001782C0)

Read from haifa-sched.c and the `-dS -fsched-verbose-6` dumps (2026-11-08):

- **INSN_REG_WEIGHT counts every SET, a store included.** find_pre_sched_live adds one per
  SET or CLOBBER in the pattern, whatever its destination, and takes one off per REG_DEAD or
  REG_UNUSED note, in the insn order before scheduling. A store whose value dies there weighs
  0, a load +1 (0 if it is the last use of its base pointer), an asm that kills two inputs -1.
  A Scalar's slot store comes before the asm that uses the weight (the helper's body), so the
  asm, not the store, is the weight's death.
- **Asms cost one cycle both ways.** insn_cost gives an unrecognised insn (an asm) a cost of 1
  as a producer, and a link into an asm is LINK_COST_FREE (1), so the "last scheduled insn"
  class is 3 for every candidate that follows an asm or feeds one. Ties then fall to the number
  of dependents and last to INSN_LUID, the insn order before scheduling. asms count against
  the issue rate (2) like any insn.
- **ComputeTargetArc (func_001782C0).** The tail's weights dt and -0.5 dt share one stack
  slot with three stores. Local allocation ranks the -0.5 dt weight (3 references) between
  the end point (5 over 30) and dt (5 over 34) only if its life is exactly 5 insns: retail's
  vf4, under the end point's vf3 and above dt's vf5. With gravity read once into a local before
  the division, its load (then self's last use, weight 0) ties with the weight's qmtc2 in one
  cycle on priority, weight and dependents, and its lower LUID puts it first, outside the
  weight's life (4 insns: the weight outranks the end point and takes vf3); read before the end
  point, the load lost on weight (+1), the weight's qmtc2 went before the division on its
  dependents, and the weight lived 6 (dt took vf4). Read in each expression
  (`MulAddX(v, Vu0::Q(self->gravity), Scalar(dt * -0.5f))`, the same for the last weight), the
  load is expanded after the weight's qmtc2, loses the LUID tie and lands inside its life:
  retail's registers. CSE makes the two reads one load. Written as Vu0::Vec values
  (`Vec::Of(self->gravity)`) the order is the 4-insn one again.

### Three differences of four loads: which statement comes first (func_00142278)

Found from the `-dS -fsched-verbose-6` and `.lreg` dumps (2026-11-09):

- **The load whose pointer dies there goes first.** `ab = b - a; cd = d - c; ca = a - c;`
  loads four vectors at priority 9. b is never used again, so its load carries b's REG_DEAD
  note and weighs 0 against the others' +1 (INSN_REG_WEIGHT): sched1 issues it first whatever
  the statement order. a and c tie on priority, weight and dependents (three each), so the
  first one in insn order (INSN_LUID) goes second.
- **The subtraction that becomes ready first goes first.** All three differences are set once
  and live at the block's end, so adjust_priority raises each to max_priority when its last
  load is scheduled; the loads' latency then decides which is ready first. With a loaded before
  c (b, a, then ab ready a cycle before c's load), ab was issued at once and b died early: b
  took vf1, where retail has vf4. Written `cd = d - c; ab = b - a; ca = a - c;`, c is loaded
  before a, ca and ab become ready together, and INSN_REG_WEIGHT puts ca first (it kills a and
  c, -1; ab kills only b, 0): sched1's order b, c, a, ca, ab, d, cd, and local-alloc gives
  retail's d vf1, a vf2, c vf3, b vf4, which global-alloc follows (cd vf3, ab vf4, ca vf5).
  Each of the three earlier orders tried (ab/cd/ca, ca/cd/ab, cd/ca/ab) compiled to the same
  code, so the statement order looked irrelevant until the dumps showed why.
- **A dot's result that a later ToFloatMoved reads is not a VU0 pseudo.** `nn =
  ToFloatMoved(Dot(n, n))` makes the dot's result a TI_REGS pseudo (local-alloc puts it in
  $v0) and reload picks its VU0 register (vf3); ToFloatNow (or ToFloat) keeps it in VU_REGS,
  local-alloc gives it vf1 and the dot's scratch vf2, retail's. ToFloatNow also keeps the mtc1
  next to the qmfc2 where retail has it. ToFloatNow's two outputs repeat its input in each SET,
  so the dot's result counts three references, not two, in local-alloc's priority.
- **Still open: the side test's block.** An emulation of local-alloc (build/swarm/w7-142278,
  la3.py and enumg.py in the g11 worktree) over every order of that block's VU0 insns finds
  one that gives retail's registers with side = ToFloatNow, s and u = ToFloat: the s dot and
  its conversion before side's conversion and the u dot. sched1 issues side's conversion first
  (static priority 5 against the s dot's 4: the compare's 3 cycles count, the division's 6 do
  not, as only the branch follows it), and neither a dot (a PARALLEL) nor an asm conversion is
  raised by adjust_priority. None of the 64 combinations of ToFloat, ToFloatMoved, ToFloatNow
  and ToFloatViaBits for side, s and u scores better than the near miss.

### A burst's two records (func_00156288)

Read from haifa-sched.c, local-alloc.c and the `-dS -dl -fsched-verbose-6` dumps of the effect
spawner's splash (2026-11-09, still a near miss). Two frame records are cleared by FillMemory
and filled member by member, one block holding both calls:

- **Equal spans fall to birth order, so the store order picks the constants' registers.** The
  tail's 8.0 and 12.0 loads issue in consecutive cycles (priority 15, the memory unit), and
  their stores two cycles apart with one ALU insn between: equal spans, and local-alloc gives
  the one born first $f0. Retail's 12.0 has $f0, so its span was shorter: stores of f20 and f24
  issued back to back. Writing those two stores first gives retail's registers (the earlier
  stores' LUIDs win the memory cycle as soon as the loads' latency allows), but sched2 then
  keeps that LUID order for the tail's other stores, which retail's code does not show.
- **A store weighs +1, less one if its value dies.** The store of a parameter on its last use
  weighs 0 and goes before a store of a value that lives on (+1) at equal priority, whatever
  the source order; sched2 has no weights but keeps the order by LUID, and reorg fills the
  call's delay slot with the last one. Retail's delay slot holds the parameter's store, so in
  its sched1 the parameter was not dying there; keeping it live in an experiment gives that
  order. No plain form was found.
- **Constants and stores at the end of a block.** A float constant's load (movsf, two
  instructions) has priority 4 and its store 2; stores that anti-depend on a load through a
  pointer loaded from memory (no base, so it conflicts with every frame store) wait for it, and
  then every constant still to be loaded is loaded before any of them is stored. Two constants
  can share a register only if one's store comes before the other's load in sched1's order,
  which nothing in that block's shape allows: retail's shared $f0 for 5.0 and -1.0 means some
  other shape (a store with a dependent in the block, or a block boundary).
- **The copy loop's registers follow the same order.** The struct copy's destination pointer
  (sp+64) is set on a free ALU slot before the gravity load, so it is live while the world
  pointer (local-alloc's $a0) is and global-alloc gives it $a1; retail's $a0 means it was set
  after that load.

### Emulating sched1 to read local-alloc's registers backwards (func_001CC818)

Worked out on the link swing's last block (2026-11-09):

- **Two emulators reproduce the compiler exactly.** A list scheduler over the `-dS
  -fsched-verbose-6` dependence table (the table's `prio`, `cost` and units; LOG_LINKS kinds from
  the RTL; a link into an asm or an anti/output link costing 1, any other the producer's cost;
  issue rate 2 with one memory insn a cycle; the birthing raise for pseudos set once and live at
  the block's end; rank_for_schedule's keys) gave sched1's order of the block, and the
  local-alloc emulator (g11's lalloc2.py, corrected to tie an asm's output only to a pseudo that
  is local to the block: a value used in a later block belongs to global-alloc and never joins
  a dying input's quantity) gave every VU register of ours. Searching orders and single-insn
  priorities with both says which change to sched1's input retail's registers need, before any
  variant is compiled (build/swarm/w7-1CC818/sim.py, la3.py in the g10 worktree).
- **What it showed here.** Retail's registers need two things: the load of `self->v150` issued
  before v2's (its priority 8 where the vsub, division, subtraction and store after it give 6,
  or the nd * rate product's lowered from 7 to 5), and the Scalar(r) qmtc2 out of the second
  issue slot after the call (another insn ranked above it there). No single priority or move
  does it, and no reordering of the statements (permute.py), Vec values, RotateUntied, Scalar(r)
  named first or a local for the f22AC pointer changes sched1's priorities: priorities come
  from the dependence graph, which only a different expression tree or helper split would change.
- **The address CSE keeps for `&local`.** `Vu0::Q(g) = x` inlines Q's reference parameter into a
  pseudo holding g's address; CSE then gives the call's later `&g` that pseudo, computed before
  the branch (`addiu a3, sp, 192` hoisted out of the call block). `*(u128*)&g = x` addresses the
  frame directly, as Set's note in vu0.h says, and the call forms the address again: retail's.

### Twenty-four weight products: the statement order and local-alloc's first tie (func_0019CC10)

ComputeGridBlendWeights writes out[i*8 + j*4 + k] = zk * yj * xi for three x weights, two y
weights and four z weights (2026-11-10, still a near miss):

- **The statement order decides the x weights' registers.** CSE makes the eight zk * yj
  products once each; sched1 puts all eight first (priority 8 against 5 for the second
  products and 2 for the stores), ordered by INSN_REG_WEIGHT (an insn that is a pseudo's
  last use in LUID order goes first) and then LUID. The 24 statements written z weight by z
  weight (for each k: xa, xb, x, each with ny then y) give retail's x, xa and xb in $f15 to
  $f17, the entry copy of x and y left in $f13; written in out-index order (x weight
  outermost) x keeps $f12 and y is copied. Of all 1728 regular orders (nest order and each
  index's direction) this one is the closest; naming the eight products first changes nothing
  (the weights and LUIDs of the product insns are the same).
- **What is left is one local-alloc tie.** local-alloc ranks a quantity by floor_log2(refs) *
  refs / life; z2*y (tied with its last product, 6 refs over 56 half-insns, 2142) loses to
  z2*y*x (2 refs over 8, 2500), which takes $f0, so z2*y gets $f1 and the globals that prefer
  $f0 (z1, from `3.0f - z`) and $f10 (ny, from z1*ny) follow differently from retail (z1 $f10,
  ny $f2). An emulator of local-alloc on the .lreg block (build/swarm/w11-19CC10/la_sf.py and
  la2.py in the g5 worktree: births and deaths at twice the insn number, a product tied to a
  dying local input, the one-insn widened range tried first) reproduces every register of
  ours, and shows that out[23]'s store one insn later in sched1 gives retail's z2*y and z2*y*x;
  but the store is issued on the memory unit the cycle its product is ready, and no statement
  order, named product, extra weight variable or re-association tried moves it.

### A Scalar's slot store after the load it would block (func_0014A8F8)

Read from the `-dS -fsched-verbose-6` dumps of UpdateFrameCameraController (2026-11-08):

- **The slot store waits for nothing once it follows the load.** `MulAddX(Vu0::Q(frame->v140),
  ..., Scalar(10.0f))` (or a named `Vec02 k` stored first) expands the Scalar's slot store
  before the v140 load: the load, through a pointer loaded from memory, may alias the frame
  slot, so it depends on the store, which inherits its priority and issues first. Written with
  Vec values, `MulAddX(Vec::Of(frame->v140), Vec::Of(basis.r[0]), Vec::Scalar(10.0f))`, both
  arguments are nested inline calls, expanded in argument order: the load comes first, the
  store only anti-depends on it, and sched1 puts it after the vmaddx, where retail has it.
- **Ruled out for the rotation's copy order.** The five stores after a three-row product's
  last row (out's rows 1 and 2, the row-2 stores of the matrix and vector locals, out's row 0)
  all feed the v140 load (priority 23); out's rows 1 and 2 are their rows' deaths (weight -1)
  and go first, and the other three tie on class (frame stores at distinct offsets have no
  dependence) and dependents (seven each) and fall to INSN_LUID. Any form whose `*out = r`
  follows both row-2 stores gives matrix row 2, vector row 2, out row 0; retail's out row 0
  before vector row 2 needs out's row 0 copied between the two row-2 stores, which tools/
  permute.py confirms (EXACT) but no plausible source has. The vector locals are aggregates,
  never MEM_SCALAR_P, so fixed_scalar_and_varying_struct_p cannot separate them from the load.
- **The same with a named scale (func_001C3EB0, 2026-11-09).** `u128 s = Vu0::ScalarAt(k);`
  written before `Q(d) = Sub(Q(to->v140), Q(from->v140)); d.z = 0.0f;` expands the slot store
  first; the two loads, through argument registers with no pointer flag, may alias the frame
  slot and wait for it, so the store and its qmtc2 inherit their priority and the loads come
  out in the wrong order and registers (73% as a near miss). Named after `d.z = 0.0f`, right
  before the MulX that uses it, the slot store follows the loads and the z store and issues
  where retail has it (after `sw zero,8(sp)`): EXACT. Where a weight slot's store sits late in
  retail, name the weight just before its use.

### A run of global stores: the constant's death and the high parts' lives (func_00203548)

Found on InitDiscLibrary (Sony's CD/DVD library, cc1 of 2.9-ee-991111) from the `-dG`, `-dS`,
`-dR`, `-dl` and `-dg` dumps (2026-11-08); it was 723/736 bytes as a near miss.

- **PRE shares a global's high part, and global-alloc decides whether it stays.** The init
  block's `%hi(D_00279424)` is the reaching value PRE gives the same high part in the loop's
  error path and after the loop (`PRE: redundant insn ... reaching reg`), so one pseudo lives
  over the whole function and competes for the nine saved registers. Written plain, it has 5
  references over 216 insns (floor_log2(5) * 5 / 216 = 0.046) and outranks the receive buffer's
  high part (3 over 78, 0.038), taking `$fp`: 95 bytes differ. With the flag's three stores
  volatile (the interrupt's callback reads it, and retail writes it as volatile) it has 4 over
  218 (0.037), loses, and reload rematerialises a `lui` before each store from its REG_EQUIV:
  retail's code. Each of the three stores is needed.
- **A `return` inside a case adds a dependent.** Case 5's own `return result;` puts `move v0,
  s0` in the case's block; sched2 then ranks the last semaphore id's `lui v0` (an output
  dependence on the move) above the store before it on dependents, and swaps them. With
  `break` to the function's one `return result;`, the move is in the next block (reorg still
  fills the branch's slot with it) and the stores keep retail's order. The switch keeps `case 0:
  case 1:` beside `default:` for retail's compare tree.
- **The shared constant's last store goes first.** In a run of `x = -1;` stores the constant's
  pseudo dies at the last one in source order; that store's INSN_REG_WEIGHT is then -2 (two
  deaths, no set) against -1 for the others, and sched1 issues it first (retail's `sw` to
  D_0027943C before the other five). The high parts tie on everything else and go in source
  (LUID) order, and local-alloc ranks each by 2 refs over its life: a `lui` issued later lives
  shorter and takes the lower register. Retail's order of the run (D_00279440, 438, 448, 444,
  44C, 43C, then the volatile D_00279434 = 0 and the increment) is the one of the 24 orders of
  its last four statements that gives every register; the others leave 5 to 20 lines.
- **What does not matter.** The thread id's word is stored plain (the interrupt does not read
  it); written volatile too, the function is the same. `D_0062A7D0 = GetCurrentThreadId();`
  before the flag's store gives retail's order: the flag's volatile store and the id's store
  have no dependence, and the scheduler issues the flag's first.

### Dead stores keep their insn order (func_00188B48)

Read from haifa-sched.c and the `-dS -fsched-verbose-6` dumps (2026-11-08):

- **A dead store ranks on insn order alone.** A store to a stack object nothing reads again has
  no dependents in sched1 (its frame address conflicts with nothing later) and no REG_DEAD note
  (the value's last use is a later store), so every such store has priority 2, weight 0, class 3
  and no dependents: they issue last, in INSN_LUID order. In sched2 they all gain the same
  dependents (the later stores through a pointer, which may now alias the frame) and tie again,
  and sched2's LUIDs are sched1's output order. A dead store that some later frame access
  depends on (a helper's slot sharing its address) goes earlier on priority.
- **What that decides: a returned local's copy.** `*(Rows*)out = Vu0::Transpose(m)` writes
  Transpose's local `t` (three rows), then the inlined `return t` copies it to the call's
  result temporary by pieces (CSE turns each load into the asm's output), then to out. The
  rows of `t` all come before the copy's, so the dead tail is t0, t1, t2, r1, r2 (r0 goes
  early: the Scalar's slot reuses the temporary's first row). InvertRigidTransform's retail
  tail is t0, t1, r1, t2, r2: its RTL wrote each row to both objects in turn. A scratch copy of
  the helper that writes the return slot (`Rows TransposeProbe(const M& m) return y`, g++'s
  named return value) right after each row of its local matches retail exactly, frame slots
  included. No form of the caller reaches it with the current helper (the copy always follows
  the last row). Matched since with Vu0::Transpose itself written that way (below, "A matrix
  returned by value").

### A matrix returned by value: the call sets no v0 (func_0018A040, func_00188668)

Read from haifa-sched.c's sched_analyze and rank_for_schedule and the `-dS -dR
-fsched-verbose-6` dumps (2026-11-08):

- **What decided the order.** BuildScaleAboutFrame copies a 64-byte product (four `lq`, four
  `sq`) just before a call. sched1 issues the four loads in insn order (equal priority, weight,
  class and dependents), so sched2's LUIDs are rows 0, 1, 2, 3. In sched2 the row whose
  register a later load reuses after the call has one more dependent and goes first: a call's
  implicit clobbers of call-used registers are added to `reg_last_sets` (the later set depends
  on both the call and the earlier set), but an explicit SET in the call (`call_value`'s v0)
  replaces the list. With `Quad16* MultiplyMatrices(Quad16* out, ...)` the call sets v0, so
  only v1's row (row 2) gains the dependent: 2, 0, 1, 3. Retail's 2, 3, 0, 1 is v0's row
  gaining one too: the call sets no v0.
- **What the callee is.** func_00188668 starts with `move v0,a0` and its callers copy its
  result out of a temporary: a function returning the matrix by value (g++ passes the
  result's address in a0, returns it in v0, and the call is a `call_internal` with no SET),
  `step = MultiplyMatrices(&scaling, &inverse); *out = MultiplyMatrices(&frame, &step);`,
  the two calls sharing one temporary slot. A void declaration matches the caller too, but not
  the callee's v0.
- **The callee's rows.** Retail writes each row to its local and then to the result before
  loading the next row of `in` (the result's address and `in` are both arguments, so they may
  alias). `return r;` copies only after the last row (the copy is a block move at the return).
  g++'s named return value, `Mat4A MultiplyMatrices(Quad16* m, Quad16* in) return out`, makes
  `out` the return slot itself, so each row's store sits where it is written: func_00188668,
  TransformMatrixByObject (`*(Mat4A*)out = MultiplyMatrices(arg, tmp)`) and func_0018A040
  all match with it. This is the second function of the matrix file whose retail writes each
  row to a local and to its result in turn (InvertRigidTransform's Transpose above is the
  first); taken together they say the original's matrix code returned matrices by value with
  named return values, a documented g++ 2.x extension.
- **InvertRigidTransform's transpose (func_00188B48).** Retail has no separate transpose
  function: the MMI transpose (pextlw/pextuw, then pcpyld/pcpyud) occurs once in all of `.text`,
  inlined there. Written as MultiplyMatrices is, a local made row by row and each row copied to
  the named return value (`inline Vu0::Rows Vu0::Transpose(const Rows& m) return y`), the dead
  stores fall in retail's order (local, result, row by row) and the function matches. Two
  limits of g++ 2.95 decide where it is written: a named return value in a class body is a
  parse error, and on a member template the compiler never finishes (cc1 still running after
  120 seconds), so Vu0::Transpose is declared in the class, takes `const Rows&` and is defined
  inline at namespace scope after it. A wrapper in matrix.cpp around the shared asm does not
  work: helpers whose several outputs are reference parameters give each output a stack slot
  (frame 112, not 96), and one-instruction helpers are scheduled apart; the two sequences must
  sit in the function that writes the rows. InvertRigidTransform is Transpose's only caller.
- Lever: a function whose callers copy its result from a temporary and whose own code begins
  with `move v0,a0` returns a struct; a call that should not set v0 (a later reuse of v0
  depending on an earlier set across the call) is a call to such a function.
- **The argument moves of such a call (func_001A1F40).** Declared
  `void MultiplyMatrices(void* out, void* b, void* in)`, ComputeHullSeenFromCamera's call had
  every instruction of retail's but its three argument moves in a1, a0, a2 order (and, through
  sched1, `move s3,a2` before `move a0,sp` in the prologue); retail sets a0, a2, a1. With
  `Mat4A MultiplyMatrices(void* m, void* in)` the result's address is the hidden first
  argument, expanded apart from the two declared ones, and `t = MultiplyMatrices(&m1, &m0);`
  into a `Mat4A t` gives retail's order, its copy of the temporary into `t` (four `lq`/`sq`
  before the next call) and the prologue, all at once. Lever: a three-pointer void declaration
  of a by-value function shows as argument moves in the wrong order; the copy from a stack
  temporary to another local is the result's assignment.

### Weights stored, then scaled in place: local-alloc's tie and sched1's tie (func_0017AF38)

Retail's `mul.s $f1,$f2,$f1` writes a product into its second operand's register although the first
operand (`$f2`) dies there too. local-alloc's block_alloc tries the operands in order (mulsf3 has no
`%`), and combine_regs ties the output only to an operand with a REG_DEAD note at that insn, counted
on sched1's order. When the original stored the factor unscaled first and then scaled the member in
place (`w[1].w = 1 - a - b; ... w[1].w *= k;`), CSE replaces the reload with the register, the store
stays until flow2, and sched1 puts it after the product: the factor's last use is the dead store, the
tie to it fails and the product ties to `k`. Writing `k * rest` instead gives the tie but the operands
in the other order.

The same form decides a store against an argument move in one cycle. rank_for_schedule compares
INSN_REG_WEIGHT before anything else, and find_insn_reg_weight counts every SET, a store's included,
less its REG_DEAD notes: a store whose value dies there weighs 0 and goes before `li a1,12` (weight
1), and sched2 keeps sched1's order on the remaining tie (LUID). Retail's `li a1` first means the
weight store was not the value's last use. All three weights stored unscaled (`w[0] = a; w[1] = 1 -
a - b; w[2] = b; w[3] = D;`) and then scaled (`w[0] *= k; w[2] *= k; w[1] *= k;`, in that order)
give retail's code exactly; none of the 720 orders of the scaled-product form did.

In the same function, a clamp written as an inline returning its result (the file's
`ClampBetween`) lets the clamp's result tie to the variable, and the scaled inputs reused in place
(`b *= s; a *= s;`, as retail's `mul.s $f3,$f3,$f0`) instead of new variables give retail's mode-1
registers and its size (a fresh `b0 * s` left the first clamp's store in the second clamp's delay
slot, one `b` longer). `t = 1.0f <? t` puts `t` first; an inline `MinF(1.0f, t)` gives retail's
constant-first `min.s`.

### A matrix returned by value: the stores order local-alloc's ranking (func_001BA5B0)

Read from local-alloc.c and haifa-sched.c of GCC 2.95.3 and the `-dS -dl` dumps (2026-11-08):

- **What differed.** The block that turns the three rows of a matrix by a rotation (an inline
  returning the matrix, assigned back to it) took $vf3, $vf5, $vf4 for the rotation's rows and
  $vf2 for the third row where retail has $vf2, $vf6, $vf5 and $vf3. Each row's product is
  tied by combine_regs to the input that dies in it (the rotation's first row, or the row
  rotated), so the block has three tied quantities of 6-8 refs and three plain rows of 2-4,
  and local-alloc places them by floor_log2(refs) * refs / (death - birth), births and deaths
  being twice the insn's index in the block.
- **The deaths are the stores.** The rotated rows die at their last store, and those stores
  are dead copies to the helper's local, the return temporary and the matrix, all with
  sched1 priority 11 (they precede the next call): they issue by INSN_LUID, the two that kill a
  register (weight -1) first. With `Mat02 out; ... return out;` the local's rows are stored as
  they are made and the return copy follows the last row, so sched1's tail is out0, out1, out2,
  tmp0, tmp1, tmp2 and row 0's product lives to the fifth store; its quantity (6 refs over 24)
  ranks below the plain row of 4 refs over 14, and the rotation's first row (8 refs) below the
  third row's (8 refs over a shorter life). Retail's registers need row 0 to die at its copy
  to the return slot and row 1 three insns before row 2: a tail of out0, tmp0, out1, tmp1, out2,
  tmp2.
- **The form.** g++'s named return value, as in the matrix file (func_0018A040 above):
  `Mat02 RotateRowsBy(const Mat02& r, const Mat02& m) return out` with a local `t`, each row
  written to `t` and then to `out` before the next row is made. The frame keeps its three
  48-byte objects (t, the return slot, the matrix), the tail becomes per row, and the whole
  function matches. The third function where retail writes a returned matrix's rows to a local
  and the result in turn, which supports the reading that the original's matrix helpers
  returned by value with named return values.

### The rotation's rows read first, and a rotated vector stored before its sum (func_001C6028)

Read from local-alloc.c of GCC 2.95.3 and the `-dl` dump, with lalloc2.py (an emulator of
local-alloc's VU quantities) (2026-11-09):

- **What differed.** CombineChildPoseRotations turns the three rows of `*outRot` and the
  vector `*outVec` by one product matrix, then adds a child's offset. Written as three
  in-place Rotate calls with two Mat02 copies and `Q(*outVec) = Add(Rotate(m, Q(*outVec)),
  Q(tmpVec))`, every instruction was retail's but six VU registers, the order of the dead
  stores and the two saved registers of outVec and &tmpRot (87.5%).
- **The two dead Mat02 copies are the return value.** `*outRot = RotateRowsBy(m, *outRot)`
  with func_001BA5B0's named-return helper (a local `t`, each row to `t` then to `out`) gives
  retail's dead-store order (out0 ... then t0, out1, t1, out2, t2 per row), and with it the
  saved registers (global-alloc's ranking of outVec and &tmpRot follows from the references).
- **The sum in the offset's register.** Retail's `vadd vf2, vf1, vf2` puts the sum in the
  second operand's register. combine_regs ties an asm's `=j` output to the first input that
  dies in it; the rotated vector does not die there when it was stored first:
  `Q(*outVec) = Rotate(m, Q(*outVec)); Q(*outVec) = Add(Q(*outVec), Q(tmpVec));` (the first
  store lives until flow2 deletes it, as in func_00130540 below), so the sum ties to tmpVec.
- **The rotation's rows read once, before the rows they turn.** With Rotate reading `r` where
  it is, each call's argument (`m.r[i]`) is expanded before the rows, so sched1's tie on LUID
  issues row 0 of `*outRot` first and its quantity (12 refs over 38) ranks below the
  rotation's rows; retail needs it between the rotation's second row and first (a life of 30).
  Reading r's rows into three Vu0::Vec locals at the top of the helper and turning each row
  with RotateRowsTied moves the loads of r ahead, and local-alloc's ranking becomes retail's
  (m2, m1, row 0, m0, row 1, row 2: vf3, vf4, vf5, vf6, vf7, vf8). The order was worked out
  from lalloc2.py's priorities (row 0 needs 12 refs over a life of 30, between 10 refs over
  24 and over 28) before the compile.

### A store after the call makes the jump every insn's dependent (func_0017B8C0)

Found from the `-dS -dR -fsched-verbose-6` dumps (2026-11-09). SetCountdownState's state-1
block sets eight fields of g_gaugeBarElement, then calls SetWorldActiveFollower. Two separate
things decided its order:

- **sched1: the stores by weight, then source order.** All eight stores are ready in the same
  cycle with one priority, so sched1 takes first those that kill a register (the -1.0, the 16,
  the 1.0, the 4's last store, the base pointer's last store: weight -1, -2 for both) in source
  order, then the rest in source order; sched2 keeps that order (LUID). Retail's
  27C, 270, 268, 278, 260, 26C, 264, 274 is the source order 260, 26C, 264, 270, 268, 278, 274,
  27C: `bar->f26C = bar->f260 = 4; bar->f270 = bar->f264 = 4;` (a chained assignment stores the
  inner field first) and changedAt (-1.0) last, the only order of the eight that a
  weights-then-LUID sort turns into retail's.
- **sched2: what follows the call.** With `self->mode = state;` in each case, the state-1 block
  ends `jal; sw s1,0x550(s0); b`: the block's jump then depends on every insn, so each mtc1 of a
  constant has three dependents (its store, the call through the call-used $f register, the
  jump) and the address's `lui` two (the addiu, the jump). On one priority, sched2 issues the
  1.0's mtc1 before the `lui`, whatever sched1 left. Written once after the switch, the block
  ends `jal; b`: the call collects those dependences instead, both have two, and the LUID tie
  keeps sched1's `lui` first, as retail. The store then sits in the join, where its `lui` of
  the clock would go first; the clock read as `g_gameClock[1]` (MEM_IN_STRUCT_P, see
  func_001CDB70) waits for the pointer store `self->mode = state`, so the store leads the join,
  and reorg's delay slots (`b tail; sw s1` stolen from the join) give retail's per-case look.
  Spot it: a constant's mtc1 placed before an address `lui` that retail issues first, in a block
  that ends with a call and a store after it.

### A flag test written at each use: GCSE's pseudo stays behind the calls (func_001BCD00)

Matched 2026-11-10 from the -dS dumps and haifa-sched.c. SolveColliderGroupContacts allocates
two arrays from back memory and clears one (three calls in one block, sched1's block 24) and
tests `flags & 1` and `flags & 4` many times further down. Written as named variables
(`s32 rest = flags & 1;` between the two allocations), both `and`s are initially ready at the
block's start (calls do not end blocks here, and a pseudo that crosses calls has no anti
dependence on the call before it). With priority 2 each they tie with the parts loop's `k = 0`,
which combine re-emits at the entry test's place (the 3-insn merge of `k = 0`, `slt`, `beqz`
into `blez nParts`), so the LUID tie picks the `and` for the free slot beside `$a0 = size`
in cycle 2 and ours computes `rest` before the first call and the mask before the second.
Retail computes each one call later. Written as `flags & 1` and `flags & 4` at every use, the
expressions are GCSE's: its pseudos appear where retail has them and the schedule is retail's,
spills and all (rest at 96(sp), the mask at 100(sp)). Spot it: a flag mask's `andi` and its
spill store one call later than a named variable puts them.

Three other differences closed the near miss, each shrinking the size gap first:

- **Each slot's real argument count.** Slots 51 to 53 (0xCC, 0xD0, 0xD4) take
  `(self, moved)`: retail sets only $a1. A cast array of three-argument pointers added a
  `move a2, zero` per call. Called through Desc02/Desc03's members, they are retail's.
- **A store from an asm stays out of the call's delay slot.** Retail's bounce loop has
  `sw a0, 200(s0); jal RandomFloatInRange; nop`: `Vu0::StoreX` (the store is the helper's
  asm, which reorg never puts in a delay slot) where `*(u32*)&c->speed = ToBits(..)` let reorg
  fill the slot with the plain `sw`.
- **A guarded do-while threads its exit test.** `i = 0; if (i < n) do { .. } while (i < n);`
  lets CSE record `i < n` false on the guard's path, so jump threading sends the guard's `blez`
  straight past the after-loop test to `flags &= ~2` (retail's `bnez; nop` with the `li` at a
  label of its own). `if (0 < n)` tests a different expression and is not threaded; `for` and
  `while` with a `break` keep the test at the top (not rotated).
- Per-loop counters (`for (s32 j = 0; ..)`) in the depth, rest, bounce and part loops, and the
  shared `i` for the scans and write-backs, give retail's counters (a3 for counters that cross
  no call, s0 for the shared one); `for (s32 j = flags & 1; j < n; j++)` in the else arm of
  `if (flags & 1)` gives retail's entry test `slt rest, n` with `j` set to 0.

### A member read again in the loop, and slots that loads wait for (func_001B8B90)

Matched 2026-11-10. The near miss was 8 bytes short, with no rodata at fault: retail's blend
loop has `move a2, v1` before it (and the loop label's 8-byte alignment then adds a `nop`).
That copy is loop.c's: the loop body read `self->hook` again (`((VertexBlend03*)self->hook)
->vectors[idx[j]]`), loop.c moved that load to the preheader as a pseudo of its own, and cse2
turned the preheader's load into a copy of the register the `vectors == 0` test had loaded.
A local `h` read in the loop is one pseudo and no copy. Spot it: a `move` of a just-tested
pointer into the register a loop reads it through.

The rest was the order of weight-slot stores and vector loads. In both loops retail stores
each weight's slot before the vector load that follows it in the source, and the loads wait
for the stores:

- **The blend loop** is retail's only in u128 form, `Q(sum) = MulAddX(Q(sum), Q(vec), ScalarAt(w[j]))`:
  every Vec form (Vec::ScalarAt, a named weight, a named vector) leaves the slot store late or
  adds copies. The u128 form also put the spilled `&w` and `&end->v10` at retail's 0x4C and
  0x48.
- **The face loop's sum** names its six operands in retail's order, each weight before its
  vector (`Vec s = Vec::Scalar(t); Vec a = Vec::Of(v0); Vec u = Vec::Scalar(-t); ...`), then
  `MulXSum3(a, s, b, u, c, v)`. Passed inline, the Scalars are expanded first and the vertex
  loads second (the two-pass argument rule), which gives our vf4/vf3 for the 1.0 and the
  second vertex and the 1.0's store after the sum. The named order also gave the kind's
  reloads retail's v1 (and with it the `beqzl` of the kind switch's delay slot).

## Conditional moves (jump.c)

What turns a lone `if (c) x = k;` into branch-free code, read from jump.c, optabs.c and
rtlanal.c of GCC 2.95.3 and the `-dj` dumps (2026-11-08, func_00175170):

- **The movsicc conversion runs first.** jump_optimize tries, for every conditional jump that
  jumps around one insn, a conditional move before the store-flag forms: the insn after the
  jump must be a single SET of a register (any source without side effects or traps), and the
  jump's label must follow it (or the next insn must jump to the same place). The old value of
  x is reg_set_last's (which stops at a label, so after a case label it is x itself): the
  result is `x = c ? k : x`, an `if_then_else` the R5900 has (movsicc needs `mips_isa >= 4`).
  The store-flag forms after it need BRANCH_COST of 2 or more unless x's old value is a known
  constant, and the R5900's BRANCH_COST is 1, so on this target it is the conditional move
  that acts. It runs in every jump pass before reload (after RTL generation, after CSE, after
  GCSE, before and after the second CSE).
- **What it becomes.** Where GCSE's constant propagation then knows x's old value (skip, 0 from
  the function's start), combine reduces the move to a store flag: `xori; sltiu; sw` in place
  of retail's `bne; li; sw`.
- **What keeps retail's branch.** Mode does not: a `bool`, `char` or `short` local is promoted
  to an SImode pseudo (PROMOTE_MODE), and the move is the same. The if's body has to be more
  than one set when the jump passes run: in SetPlayerState's sub-state 9 a dead `else anim =
  ...` (case 4's own else, the case setting anim again afterwards) does it, removed only later
  by flow as a dead store. No form with one set keeps the branch.

### An if/else of a constant: when jump.c hoists `x = 0` (func_00112698, func_00112968)

Read from jump.c, local-alloc.c and haifa-sched.c of GCC 2.95.3 and the `-da` dumps
(2026-11-08). AddScriptValues and SubtractScriptValues set the list's first node to 0 or to
`args[1].node`; retail has `lw v0; lw v1; beqz v0 [move s1,zero]; lw s1,12(s0)`, `sq ra`
before `sq s1` in the prologue, and the arguments in s0 and the node in s1.

- **jump.c's two hoists.** `if (c) x = a; else x = b;` becomes `x = b; if (c) x = a;` when b
  is a constant or cannot trap, and `if (c) { x = a; goto l; } x = b;` becomes `x = a; if
  (!c) goto l; x = b;` when a can (both in jump_optimize, every jump pass, before and after
  reload). Both need the arm that stays to be one insn directly after the conditional jump
  and the other arm's first insn to set x: with `n = args[1].node` either order of the arms is
  hoisted in the first jump pass, so `n = 0` sits in the first block, before the branch.
- **What that costs in sched2.** The first block runs from the prologue through the call to
  the constructor to the branch. `move s1,zero` there depends on the save of s1, so it issues
  with the call, and the save of s1 (three dependents against ra's two) goes before ra's.
  Retail's `move s1,zero` is not in that block: the hoist happened only in the jump pass after
  sched2, which puts it directly before the branch, and reorg moves it into the delay slot.
- **What blocks the hoist before reload.** An arm of two insns: `ScriptValue* m = &args[1];
  n = m->node;` expands to `m = args + 8; n = m[4]`, whose first insn does not set n; combine
  later makes it one load, and the jump pass after sched2 hoists `n = 0`.
- **Which arm comes first decides the registers.** update_equiv_regs (local-alloc.c) takes
  the sets of a pseudo in insn order: a set carrying a REG_EQUAL of a constant (CSE gives
  `n = 0` one) makes it REG_EQUIV and doubles REG_LIVE_LENGTH, unless an earlier set without
  one has already ruled the pseudo out. With `if (args[1].tag == 0) n = 0; else ...` the zero
  comes first and n's life doubles (123 to about 250 insns), global-alloc's priority puts the
  arguments' pointer first, and it takes s0 as retail's; with the arms the other way round n
  takes s0. The script machine's other built-ins test `args[1].tag == 0` first too.
- **The tag in the case.** With the if/else left as two blocks, CSE no longer follows a path
  from the first read of `args[0].tag` into the switch's cases: the case reads the local
  (`tag == 0x14`), or it reloads the tag.

### A preset of the fallback after cse2: a jump table reruns jump.c (func_00156718)

Read from jump.c, cse.c and toplev.c of GCC 2.95.3 and the `-dL -dt -dl` dumps (2026-11-10).
The spawn shape's point normalises three vectors with Vu0::NormalizeOr; retail loads each
fallback into a GPR before the test (`lq a0,0(a0)`) and moves it in the fallback's arm
(`b join; qmtc2 a0,$vf1`), the divide's result in the length's register. Ours loaded the
fallback straight into the result (`lqc2 $vf2`), with `bc1tl` and the store in its delay slot.

- **cse2 makes the divide's arm start with the set of the result.** Its "(set REG0 REG1)"
  special case turns `r = DivX(..); x = r;` into `x = DivX(..); r = x;` (x lives past the
  join, so it is the quantity's canonical register), in every function.
- **jump.c runs after cse2 only when cse2 says so**: toplev.c reruns jump_optimize if
  cse_main returns nonzero, which it does when a jump was altered or a LABEL_REF went into its
  table. A switch compiled as a jump table always records one: the table address's REG_EQUAL
  `(label_ref)`. That pass then applies the hoist above, `if (c) { x = fallback; goto l; } x =
  DivX(..);` to `x = fallback; if (!c) goto l; x = DivX(..);`, and combine folds the
  fallback's load into it. Without a jump table (every earlier user of NormalizeOr) the pass
  does not run and the arms stay: rewriting this function's outer switch as an if chain alone
  gives retail's arms.
- **What keeps the arms with a jump table.** The normalisation written over Vu0::Vec values,
  `Vec NormalizedOr(Vec v, Vec fallback)` with `Vec r; r.q = DivX(v.q, len); return r;` (or
  Vec internals over u128 arguments): the copies of the vector values put a copy first in the
  divide's arm, so the hoist does not apply, and they are gone before allocation. The all-Vec
  form (Vec Length, Vec DivX) keeps the arms too but adds a `vmove` and a GPR load.
- **A value reused as its own normalisation** (`d = NormalizeOr(d, fb)`, as func_00172EE0
  writes it) also blocks the hoist (the divide's arm reads x), but the result then takes d's
  register, not the length's.
- **The last normalisation's slots.** Its result and the position copy at 0x80 and 0x90 of the
  frame, above every case's locals, are u128 values crossing the jitter's call that reload
  spills (the slots go at the frame's end), not Vec02 locals (which reuse the cases' freed
  slots at 0x0 and 0x10).

### A clamp's constant in a register: `slt v1,v1(98),v0; movz` (func_00149190)

Read from mips.c of GCC 2.95.3 (gen_conditional_move, gen_int_relational) and measured
(2026-11-10). Retail clamps a counter with `li v1,98; li a0,99; addiu v0,v0,1; slt
v1,v1,v0; movz a0,v0,v1`: the constant compared sits in a register, not in an `slti`.

- **Where the register comes from.** gen_int_relational (a branch or a store flag) takes a
  constant within 16 bits as `slti`, adding 1 for GT and LE. gen_conditional_move (movsicc,
  what jump.c's conversion of `if (c) x = y;` expands to) does not: for GT and LE it forces
  the constant into a register and swaps the operands (`slt t, K, c`), with `movn` for GT and
  `movz` for LE. So `li K; slt t,K,c; movz` is a jump.c conditional move on `c <= K`.
- **Which source gives LE.** `s32 v = 99; if (c < 99) v = c;` reaches the move as `c <= 98`:
  retail's code, EXACT. `(c > 98) ? 99 : c` is folded into a MIN_EXPR (`slti 100; movn`),
  `if (c >= 99) c = 99;` and `s32 v = c; if (c >= 99) v = 99;` give `slti 99; movz` (GE),
  and an if/else storing in each arm keeps a branch (`beqzl`).
- **Rule.** A conditional move whose `slt` has the constant in a register as its first
  operand is a variable set to the clamp's value first and then to the value under a `<`
  test.

### A flag set from a && chain: a boolean, not `if (..) flag = 1` (func_001BC978)

Read from the `-dr`, `-dj` and `-dl` dumps (2026-11-10):

- **What differed.** A zero test `s32 still = 0; if (fabs(x) < k && fabs(y) < k && fabs(z) <
  k) still = 1;` whose lanes are read through `Vu0::Vec::Of(o->offset)` put the flag in v0 and
  the offset's GPR copy in v1, where retail has v1 and v0.
- **Why.** With the Vec copies in its operands the `&&` is expanded as a value: a temporary
  (r191) set to 0 and to 1, then jump.c turns `if (r191) still = 1;` into a conditional move,
  which combine reduces to `still = r191`. `still` lives one block and local-alloc gives it
  v0; the copy makes r191 prefer v0, and global-alloc's find_reg skips registers another
  allocno prefers on its first pass, so the offset (ranked first) takes v1. With u128 lanes
  (`Vu0::Q`, func_001B7D00) the same source keeps the branch form and has retail's registers.
- **Rule.** Where the flag and the vector swap registers in such a test, write the test as the
  flag's value: `s32 still = a && b && c;` (or the three tests nested, the same code). Matched
  the flag in func_001BC978 (near miss, one GPR left).

## Alias classes in the schedule

GCC 2.95 without `-fstrict-aliasing` separates a load from a store in sched1 and sched2 only
by alias.c's rules ("Reloads and stores" above for CSE). Three of them decided SetPlayerState's
order (2026-11-08, func_00175170):

- **A global scalar against a structure's store.** fixed_scalar_and_varying_struct_p: a load of
  a scalar global (`extern f32 D`, a fixed address, MEM_SCALAR_P, `mem/f` in the dumps) never
  conflicts with a store that is a structure's (MEM_IN_STRUCT_P, `mem/s`) through a varying
  address. `Vu0::Q(x) = v` and `Vu0::Set(x, v)` store through a `u128*` cast, neither flag, so
  the global's load waits for them; a vector stored as a `Vu0::Vec` (`*(Vu0::Vec*)&x = v`, or
  through an inline returning `Vu0::Vec&`) is a structure's store and the load moves above it,
  as retail's do: the sound's two floats before the zero velocity's sqc2 (sub-states 10/11),
  D_00263990 before the dot product that follows the direction's store (state 6/4, where after
  reload the store's address is a hard register of unknown base). Stored straight through
  `*(Vu0::Vec*)&local`, CSE forwards the value and the reload goes; through the reference it
  stays.
- **A global read as a structure's member is not a scalar.** `D_002639B8.f0` of an 8-byte
  struct conflicts with the member stores before it; read as `s32 D_002639B8` it does not, and
  sched2 interleaves retail's shift and lui between the stores (sub-states 37/38). A cast
  `*(s32*)&D` is neither scalar nor structure and does not help.
- **Register weight decides between equal stores.** Before reload rank_for_schedule prefers the
  insn with the lower INSN_REG_WEIGHT (sets minus REG_DEAD notes), so of two stores of one
  value the one that ends its life goes first: `a = b = x` stores b, then a (the last use);
  retail's 0x638 before 0x630 is `f638 = f630 = x`. The same rule ordered state 7's two loads
  through the track pointer: the one that kills the pointer goes first, so the source loads
  them in the other order (the shape at 0x34, then the turn kind at 0x58).
- **A last call is everyone's dependent.** In a block that ends with a call, every insn's
  dependence on the call is also its dependence on the block's end; with an insn after the call
  the argument moves for registers a later call clobbers count one dependent more, and
  rank_for_schedule's dependent count sets a3 before a1 (a1 then goes in the call's delay
  slot). State 6/5's `layers = 1` after SetFlaggedLinkContactMask gives retail's
  TriggerScriptEvent arguments.
- **The conversion's own priority.** ToFloat's qmfc2 is an asm statement with a cost of 1 and its
  mtc1 a second insn, so its chain to a division is one insn longer than a field's lwc1 and
  sched2 issues it first; ToFloatMoved's mtc1 alone leaves the qmfc2 to the compiler and the load
  goes first, as in sub-state 55 (`ToFloatMoved(len) / self->radius3CC`).
- **A spill store follows its set; the set's place is sched1's.** Reload puts a spilled local's
  store right after the insn that sets it, and sched2 breaks ties by that order, so the prologue's
  order of a spilled int's store and a float's constant is sched1's order of their sets. sched1
  issues one memory-unit insn (a float constant) and alu insns two to a cycle by declaration
  order, so which float constant shares a cycle with which integer follows the order the locals
  are declared in; the spilled locals' slots follow their declaration order too. SetPlayerState's
  `sound, start, anim, speed, flag` (start and anim taking the cycle before) gives retail's.
- **A structure's member store, named.** State 13's `f273C = hook` as a Player member (the field
  named where the struct had padding) rather than a byte-offset store let sched1 issue it first.

### Corner pointers read as a record's members (func_00191C78)

Read from alias.c and the -dS dump (2026-11-09). func_00191C78 weights a triangle's three corners
(`MulXSum3`, each weight a `Vu0::Scalar`). Retail loads each corner pointer (`lw v0,0(s0)`)
before the previous weight's slot store; ours waited behind it, so sched1's order and with it
local-alloc's VU registers (a in vf6, the second weight in vf5) differed, 24 words. The corners
were read as `((GraphPoint**)t)[k]`: a plain scalar load through a pointer of no known base,
which true_dependence cannot separate from the frame's slot store. Read as members of a
12-byte record, `struct GraphTri { GraphPoint* corner[3]; }`, the loads are MEM_IN_STRUCT_P
through a varying address and the slot stores scalars at a fixed one, so
fixed_scalar_and_varying_struct_p removes the dependence and the loads rise as retail's do. A
record's members read through a pointer where retail's loads pass a Scalar slot's store is the
lever; the record (here the graph's triangle) is plausibly the original's own type.

### A global array's element is not a scalar (func_001CDB70)

An element of a global array (`D[0]`) is MEM_IN_STRUCT_P like a structure's member, so
fixed_scalar_and_varying_struct_p does not separate its load from a store through a pointer.
ComputePlayerLinkPose's `BuildAxisAngleMatrix(&g_unitXVector, D_00274DD8[0], rotB)` had its lwc1
of the angle after the three `*rotA = r` stores (through a Mat02 parameter), five insns later than
retail; read as `float D_00274DD8` the load moved above the stores and the function matched. The
label's second word is 0, the padding before the array D_00274DE0 that the MIPS DATA_ALIGNMENT
puts on an 8-byte boundary, so the scalar gives the same .data. A two-word label whose second
word is 0 and never read, followed by an array at an 8-byte boundary, is a scalar.

### A pointer global read as an aggregate's word (func_eu_001AEC90)

The same rule for a pointer: PAL's func_eu_001AEC90 stores two flags through `self` and then
loads D_eu_0026ABE8 (a pointer whose neighbours at 0x26ABE4 and 0x26ABEC are written through a
base). Declared `Pal* D_eu_0026ABE8` the load is MEM_SCALAR_P, never conflicts with the
struct-member stores, and sched1 hoists it above them; read as `D_eu_0026ABE8[0]` it is
MEM_IN_STRUCT_P, waits behind the stores, and the function matches. func_eu_001AEEA0 reads the
same word and matches either way, so the unit declares it once, as the array.

### A rotation product through a pointer local (func_001B7D00)

- ApplyColliderPendingMove multiplies its rotation into its own matrix with
  MulRotationRowsIndexed (b's rows read by index after each row's stores). Written
  `Mat02* frame = &self->rot; MulRotationRowsIndexed(&m, rot, *frame); *frame = m;`, the three
  rows of b were loaded before any product row was stored; written `MulRotationRowsIndexed(&m,
  rot, self->rot); self->rot = m;` the second and third rows wait for the stores of the row
  before, as retail's do: EXACT. Not traced in the dumps; it fits the rule above that a base
  register with REGNO_POINTER_FLAG (here the pointer-typed variable `frame`) passes frame
  stores, where the address formed from `self` inside the helper does not.

### Memory dependences in sched1 (func_00149760)

sched1 keeps a load after a store it may alias, and the store then inherits the load's
priority (2026-11-08, read from alias.c and expr.c, -dS dumps):

- **Which MEMs are flagged.** expand_expr sets MEM_IN_STRUCT_P for a member or an element
  (COMPONENT_REF, ARRAY_REF) and for `*p` only when p is literally `&aggregate` or the pointed-to
  type is an aggregate; a declared scalar variable's own MEM (a global `f32`, a scalar local in
  memory) is MEM_SCALAR_P. A dereferenced cast pointer (`*(f32*)&self->value`, Vu0::Q's
  `*(u128*)&v`, Rotate's `((const u128*)&m)[i]`) has neither flag. The RTL dumps print the flags
  as `/s` (in struct) and `/f` (scalar).
- **The only rule that separates them** without known bases is
  fixed_scalar_and_varying_struct_p: a MEM_SCALAR_P reference at a fixed address never aliases
  a MEM_IN_STRUCT_P one at a varying address. A parameter's pointer has base `(address a0)`,
  which may alias any global (base_alias_check, no `-fargument-noalias`), and a pointer loaded
  from memory has no known base at all.
- **func_00149760, second switch, cases 0 and 1.** `*(f32*)&self->value = WrapAngle(...)`
  (neither flag) made the tilt clamp's bound loads `D_00261BFC` and `D_00261C00[0]` (an array
  element: in struct) depend on the store: sched1 issued the store first and the low bound took
  $f0. Retail loads both bounds first and stores in the branch's delay slot. Writing the store as
  a member (`self->g08 = ...`, a float in CameraController's union) and reading the upper bound
  as a scalar (`D_00261C00` an `f32` of its own, its 16-byte label padded by the 16-aligned
  `Vec02` offsets after it) gives retail's registers; either change alone does not.
- **Insn order instead of flags: case 2's Scalar slot.** Vu0::Scalar's slot store (neither
  flag) and Rotate's row loads through a u128 pointer (neither) may alias. Rotate loads the rows
  in its body, after its argument (MulX of a Scalar) has stored the slot, so the loads depend on
  the store, the store inherits their priority and goes first, and MulX's result takes the
  scalar's register. Retail stores the slot last. A dependence only runs forward in insn order:
  with the camera's rows loaded as values first (`const u128* rows = ...; r0.q = rows[0]; ...`)
  and rotated with the result tied to v (Vu0::RotateRowsTied, Rotate's tie with RotateRows'
  operands), the store comes after the loads, depends on nothing but the qmtc2, and with its low
  priority waits to the end of the block: retail's $vf6 and store. RotateRows (untied) gives
  the result row 0's register instead. Making the slot store scalar-flagged would need a scalar
  local in memory, which the helpers do not have.

### The weight slot of func_00181078 (ruled out in plain C++)

Read from alias.c, function.c, stmt.c and expr.c and the `-dS -fsched-verbose-6` dumps
(2026-11-08). func_00181078 computes `d = (Rotate(m, v) - v) * D` with the weight in a 16-byte
slot that the axis of MatrixToAxisAngle reuses (80(sp)); the near miss differs only around it.

- **What sched1 must do.** Retail's weight takes vf5 and the product takes the difference's
  register, so in sched1's order the weight's slot store comes after the vmulx: local-alloc then
  ranks row 1 before the weight (the weight lives longer) and the product does not tie to it.
  After the call before them, the memory unit issues row 0, row 1, row 2, v (priority 30) and
  then one of the loads of `self->fBC0`, `fBCC`, `fBD0` (26, 26, 25) or the slot store per
  cycle; the vmulx issues two cycles after row 2. The store (weight 0 or -1) beats an equal
  load (+1), so it must rank below all three: priority 24 or less. Its priority is 26 because
  the loads of the `parent` fields passed to TransformDirectionBetweenFrames (`lw a0, 24(v1)`,
  `lw a1, 24(v0)`, 24) depend on it: a pointer loaded from memory has no known base, so
  base_alias_check cannot separate it from the frame.
- **Insn order cannot do it.** With the loads before the store in the insn order, the store
  anti-depends on them, in sched1 and (its LOG_LINKS kept) in sched2, where retail stores before
  `lw a0`. Only fixed_scalar_and_varying_struct_p separates them: the loads as members
  (`((PlacedObject*)p)->parent`, `mem/s`) and the store MEM_SCALAR_P at a fixed address. With
  `u128 k` (a scalar local whose address is passed, so purged to a scalar slot) the whole block
  is retail's, and only the frame differs: purge_addressof puts k after the aggregates (144),
  where retail has it at 80, between d and m2.
- **No plain form gives a scalar-flagged slot in expansion order.** MEM_SCALAR_P comes from
  MEM_SET_IN_STRUCT_P (x, 0): expand_decl for a non-aggregate on the stack (never a TImode
  local: it is a pseudo unless TREE_ADDRESSABLE at its declaration, and g++ 2.95 expands each
  declaration before its address is taken, so `&k` gives an ADDRESSOF), put_reg_into_stack (at
  purge time, after the aggregates), assign_temp for a non-aggregate with memory_required: an
  asm input that allows only memory given a register (the asm then reads the slot, so the store
  must precede it: tried, the store stays first) and ADDR_EXPR of a value in a register (g++
  marks a reference temporary addressable, and purge_addressof folds it back into a register:
  no store at all). A 16-byte argument is passed in a register here, not by invisible
  reference (no copy in integrate.c or calls.c). Vu0::Slot is an aggregate and `Q(t) = x` has
  neither flag. So retail's slot behaves as a scalar-flagged 16-byte temporary that nothing
  reads, a construct the project's helpers do not have; func_00149760's case 2 met the same
  limit and got around it by insn order, which this function's later loads forbid.

### A weighted sum's operands in insn order (func_00191570)

An inline call evaluates its arguments in two passes (integrate.c, expand_inline_function):
first each argument in parameter order, where an inline call (Scalar, Vec::Of) emits its code
and a plain memory reference (`Vu0::Q(*p)`) emits nothing; then each memory reference is copied
to a register in parameter order. So `MulXSum(Q(*a), Scalar(1 - t), Q(*b), Scalar(t))` stores
both weights' slot (one stack slot, shared) before it loads either end, and with Vec::Of ends
it loads a, stores s, loads b, stores t. Every one of those references may alias (slot stores
with neither flag, loads through pointers read from memory), so sched1 and sched2 keep the insn
order (2026-11-08):

- **Retail's order s, a, t, b is the source's.** sqc2 s, lqc2 a, sqc2 t, lqc2 b comes only
  from the operands formed in that order, as locals: `Vec s = Vec::Scalar(1.0f - bestT);
  Vec pa = Vec::Of(*a); Vec t = Vec::Scalar(bestT); Vec pb = Vec::Of(*b);` then
  `MulXSum(pa, s, pb, t)` (each weight beside its end; the u128 locals give the same code).
- **The two pointer loads.** The end pointers' `lw` both anti-depend on the first slot store,
  so they have one priority, and rank_for_schedule's INSN_REG_WEIGHT picks the load that ends
  the pointer array's life (the later one in the source) first. Retail's `lw v0, 0(s3);
  lw v1, 4(s3)` is `b = nearest[1]` read before `a = nearest[0]`, and only with the operands
  above (a read first leaves the two loads swapped; with the single call, b first swaps their
  registers).

### Operands in insn order against sched2's stack addresses (func_001A15D8)

DrawPhasedEffect (two inner loops, each a MulRotationRowsX, a weighted sum of the strip's
points, a Splat scale and a draw call) matched on 2026-11-09 from 85.4%, with `-dS -dR -dL
-fsched-verbose-6` dumps. Four changes, each found from a dump:

- **sched2 cannot separate a frame store from a member load.** After reload rtx_varies_p calls
  an `sp`-based address varying (only the frame, hard frame and argument pointers are fixed), so
  fixed_scalar_and_varying_struct_p no longer applies and every stack store conflicts with a
  load through a pointer register. sched2 then keeps whatever order sched1 gave a weight's slot
  store and the point load: a slot store that sched1 issued first (it was the only ready insn
  while the load waited for the rotation's nine row stores) stays before the load, where retail
  stores it last, in the call's delay slot. So the order must already hold in the insn stream:
  retail's loads come before the slot stores they precede in its schedule.
- **Loop 2: `MulAddX(Vec::Of(p[1].base), Vec::Of(rot.r[2]), Vec::Scalar(k))`.** The Vec forms
  are inline calls, evaluated in parameter order in integrate.c's first pass, so the point is
  loaded before k's slot is stored. With `Q(p[1].base)` the load is copied in the second pass,
  after the slot store.
- **Loop 1: the operands as locals, each weight before its end** (`Vec w0 = Vec::Scalar(1 - t);
  u128 a = Q(p->base); Vec w1 = Vec::Scalar(t); u128 b = Q(p[1].base);`), retail's
  sqc2 w0, lqc2 a, sqc2 w1, lqc2 b, as in func_00191570. The weights as Vec locals add the
  movti copies that bring the loop to 77 insns at the first loop pass. move_movables' threshold
  starts at 79 in a loop with a call (the `-dL` dumps bound it: loop 2's pos - rest, life 1,
  moves at 79 insns) and drops by 3 per register moved. At 77 insns pos - rest moves (79 >= 77),
  and the axis's `%hi` (life 1), next in the list, does not (76 < 77): it moves in the rerun,
  after cam->rot3A0's and draw's addresses, which gives retail's preheader order (`addiu s2;
  addiu s1; lui s7`), as loop 2's (79 insns) already did. With u128 weights the loop is 68 insns
  and the `%hi` moves in the first pass, first; with every operand a Vec it is 91 and the 1.0 is
  not hoisted at all.
- **Both loops: the scale after the position.** `Q(scale) = Splat(scaleMin)` written before the
  sum stores scale (no alias flag) before the point loads, which must then wait for it; written
  after the sum, the store follows the loads, as retail's `sq v0, 0xCC0(sp)` does.
- **The first loop: `p->heading = h;` before `w = cam->f1E4 >? p->at.z`**, and the scale
  product named in the min (`scaleMin = s * c <? scaleMin`) rather than `s *= c` (a variable
  set twice, which global-alloc placed in s's register).

### A pointer read before the frame stores (func_001A2D88)

DrawStreakedEffect (normalise the velocity, `tail = place + dir * 100`, draw with the world's
template slot 11) matched on 2026-11-09 from 68.3%, with two changes read from the `.sched`
dump:

- **The weight as `Vu0::Scalar(100.0f)`** instead of the near miss's own `Vec02 k` slot: the
  cast's MEM_SCALAR_P temporary is stored last, in the call's delay slot, as retail's
  `sqc2 $vf4, 32(sp)` is (the Scalar-slot lever).
- **The template read first, `BaseObject* tmpl = g_currentWorld->slot1CE8[11];`, before the
  vector work.** The stores to `dir` and `tail` go through `u128` casts (no alias flag), so
  true_dependence makes a later load through a pointer register (`[r158+0x1d14]`) depend on
  every one of them: sched1's table showed the slot load with the three stores as its
  producers, issued after them, and the world pointer's own load pushed late with it. Read
  before them in the insn stream, the load only gives the stores anti dependences (they wait
  for it), and sched1 issues both loads in the square root's shadow, as retail does, with the
  dead store of the unnormalised velocity sliding after the multiply-add. That also gives
  local-alloc retail's VU registers (the velocity vf1, the Dot's 1.0 vf2). Spot it: retail
  loads a pointer's field before stack stores that ours issues first.

### A member store that kills two registers goes first (func_001A1030, near miss)

UpdateSpringEffect (two clamped quadratics, a spring towards them, `vel += acc * dt;
pos += vel * dt` with vel.y zeroed for the position) went from 81.1% to 86.1% on
2026-11-10, from the `-df -dS` dumps:

- **The tail: INSN_REG_WEIGHT counts every death.** With `Q(vel) = MulAddX(...);
  Q(self->qA0) = Q(vel);` the member store is the last use of both the new velocity and
  `self` (flow's REG_DEAD notes on it: weight -2, or -1 once the pointer dies later), while
  the dead stores of pa, pb, d1 and d2 kill nothing (weight 0). sched1 then issues the member
  store before them, and sched2 cannot undo it (after reload a store through `a2` conflicts
  with every `sp` store). Retail stores qA0 last: written `Q(self->qA0) = MulAddX(...);
  Q(vel) = Q(self->qA0);` (CSE reads the member back from the register), the velocity dies
  at the frame store instead, the member store ties with the dead stores at weight 0 and
  falls to INSN_LUID, after them. Spot it: retail's member store comes after dead frame
  stores of values computed earlier.
- **Two stores of one constant: the dying one first.** `b.x = 20; b.y = 20;` puts the
  constant's REG_DEAD on b.y's store, which sched1 then prefers by weight: retail's b.y
  store before the branch and b.x in its delay slot.
- **Ruled out for the head.** Retail's sched1 must issue b's clear after the life load
  (sched2 keeps a frame store after a load through `a2` in stream order) and the 20.0 after
  the divide (it shares `$f0` with the difference). Ours issues the clear at clock 3 (its
  priority 3 beats the dt copy's 2, the only other ALU insn) and the 20.0 at clock 5 (three
  dependents, the two stores and the jump, beat 125's and -25's two). None of the 280 orders
  of the seven a/b/t statements, the clamp as an inline, if/else, ?:, a reference output or
  named bounds, `g_gameClock[1]`, or `Vec02 a = {125, -25}` initialisers changes either; the
  difference lies in the RTL's shape, not in the order.

### A weight listed before its vector (func_001DDE90)

The chain relaxation's velocity update, `vel + rel * b + drag * vel + bend * c`, is one
file-local helper (vadda, two vmaddax, vmaddx). Its only difference from retail was the VU0
registers of that block (2026-11-08):

- **The near miss's diagnosis was half right.** sched1 does issue h's qmtc2 (the position
  update's weight, an asm with no unit and no input in the block) at clock 1, and it still
  does in the match: h lives across the block either way. What decides the registers is
  local-alloc's ranking (floor_log2(refs) * refs * 2 / life) of the other quantities. With
  the helper's parameters (a, b, s, c, t, d, u), the inline's first pass emits the second
  velocity load before drag's slot store; b's quantity (6 refs, life 30 to 56) ranks 9230,
  above h's 9000, and takes vf7 before h.
- **Weight first.** With the parameters (a, s, b, t, c, u, d), the sum as it reads, drag's
  slot store comes before the second velocity load (slot stores have no alias class, so the
  load waits for the store), the sum issues one insn later, b's life grows to 58 and its rank
  falls to 8571, under h's: h takes vf7 and b vf8. The same shift makes vel and rel tie
  (30000; the tie falls to the quantity number, vel first: vf4, vf5) and puts the second
  velocity load after drag (vf2, drag vf3), all retail's. The emulation of block_alloc
  (build/swarm/mech-149760/lalloc.py) on the `.lreg` dumps gives both allocations.
- **Locals give the same block and the wrong spill slots.** Naming the operands as Vec
  locals in that order (each weight before the vector it scales) matched the block too, but
  each Vec local is two movti copies: 638 insns at gcse, T = 321 buckets, and PRE's three
  spilled pseudos (`first << 6`, `first - 1`, the clock's `%hi`) came out in another bucket
  order. The inline arguments keep 624 insns and T = 313. Of the orders tried, the ones
  that give the block have the first velocity load before rel's weight, drag's weight before
  the second velocity load and bend's after it; b's load and c's may come anywhere there.

### Weight first, a Vec join and an out float (func_001218C0)

ApplyPoseSourcePosition matched from 35 differing lines with three changes (2026-11-09,
`-dS -dj -ds -dL` dumps, jump.c of 2.95.3):

- **Weight first for a two-term sum.** Case 1's `pos + dt v + (dt dt / 2) c` with MulAddX2's
  (a, b, s, c, t) and `Vu0::Q` operands emitted both slot stores before the loads of pos and v
  (u128 reads, no alias flag), so sched1 kept the loads behind the stores and the float chain of
  the second weight (priority 18) went first. Vu0::MulAddX2WeightFirst (a, s, b, t, c), the
  vectors read with Vec::Of, emits pos, dt's slot, v, the second weight's slot, c: the loads that
  come before a store in insn order need not wait for it, and retail's block follows (pos before
  dt's store, v after it). The sum's add of c (C + v170) then issues first, as retail's.
- **An if/else that jump.c leaves alone.** Retail normalises the direction with a branch: the
  fallback (lq into a GPR before the test) is moved to vf1 by qmtc2 in its arm, the division is
  the other arm, and vf1 is stored once at the join. A u128 variable set in both arms, or
  NormalizeOr inline, is hoisted by jump.c (`x = b; if (c) x = a;` or `x = a; if (!c) goto l;`):
  the switch's table address gives CSE a REG_EQUAL of a label_ref, so cse_main returns nonzero
  and jump_optimize runs again after cse2, and by then CSE has made the asm set the join pseudo
  directly (the copy swapped into the preceding insn), so each arm is the one insn the hoists
  need. A `Vu0::Vec` variable for the join (`Vu0::Vec n; if (..) n = fallback; else n =
  DivX(..);`) keeps the struct's movti copies in the arms at that pass, and the branch survives.
  Storing to the local in each arm (the near miss) keeps the branch too, but the fallback's store
  is then `sq` from the GPR. A matched NormalizeOr caller without a switch (func_0013BBA0) has no
  jump pass after cse2, which is why the helper keeps its branch there.
- **An out float allocated last.** ApproachValueWithRamp's last parameter is an `f32*` (camera.cpp
  declares it so): with a Vec02 record for the rate the record took 96 and the weights' Scalar
  slot 112, retail's the other way round. An `f32 speed;` whose address is passed is put in the
  frame by purge_addressof after the other locals and temporaries, at 112. The profile is a
  RampProfile local (`prof.maxSpeed = ...`).

### A Scalar slot against a load through a loaded pointer (func_001D87C8)

Read from alias.c, function.c, integrate.c, reorg.c and resource.c and the `-dS`
dumps (2026-11-08, still a near miss):

- **What retail shows.** In AdvancePathFollowerAlongPath the two weights of `lo = pos + dir *
  range.lo; hi = pos + dir * range.hi;` share the slot at 0x120, and the call after them takes
  `self->f848->curve`. Retail loads f848 between the sums, stores the lo weight after the three
  result stores, then loads `->curve` (`lw a0, 52(v0)`) and stores the hi weight last, in the
  call's delay slot. Reorg fills a call's slot backward only past insns that touch no memory and
  never forward with a store (the call sets memory, resource.c), so in sched2's input the hi
  store came after the curve load and the lo store before it. After reload a frame slot is
  `sp + n`, which varies (rtx_varies_p) and conflicts with a load through a hard register of no
  known base, so sched2 keeps the order sched1 gave them: sched1 put the curve load between the
  two slot stores.
- **Why ours does not.** sched1 can do that only if the curve load does not depend on the hi
  store. The load's address is a pointer loaded from memory, of no known base, so
  base_alias_check cannot separate it from a frame address, and the slot store (`Q(t) = ...`, a
  `u128*` store) has neither MEM flag: the load depends on both slot stores, which inherit its
  priority and go first; the f848 load (same priority, weight +1) then loses its memory cycle to
  the result stores. Without the slot stores (FromFloatAt alone, as an experiment) f848 is
  loaded in retail's cycle. The only rule that would separate them is
  fixed_scalar_and_varying_struct_p, with the slot MEM_SCALAR_P.
- **No scalar temporary stays in memory.** A u128 temporary bound to a `const u128&` (an inline
  parameter, a local reference, a template helper), a by-value parameter whose address is taken,
  or a local read through a pointer is a VAR_DECL that put_var_into_stack gives an ADDRESSOF
  (`mem/f`, scalar), and purge_addressof folds every one back into a register: the slot
  disappears (the frame is 16 bytes smaller). A scalar stays in a stack slot only if it is
  TREE_ADDRESSABLE when expand_decl runs, its ADDRESSOF escapes, or expand_expr takes the
  address of a value in a register (`assign_temp (type, 1, 1, 1)`, scalar for a scalar type);
  none of these comes from a plain helper, and an aggregate's slot (Slot, a Vec temporary) is
  MEM_IN_STRUCT_P, which still conflicts with a member load through a varying pointer.
- **The spills of that function are gcse's buckets.** Its `&lo`, `&hi`, `&out` are PRE's
  reaching registers, spilled in pseudo order: (13259 + C) mod T for C = 240, 256, 272 must not
  wrap, which T = 123 (the Vec form) and 125 (a for loop) do and T = 103 (the uniform u128 form,
  no movti copies) does not: retail's slots 0x134, 0x138, 0x13C.

### A base register's pointer flag, and the Scalar slot again (func_001C75B0)

Read from alias.c (find_base_value, find_base_term, init_alias_analysis), function.c,
integrate.c, stmt.c and haifa-sched.c with `-dS` dumps (2026-11-08, still a near miss):

- **A register's base counts only with the pointer flag.** init_alias_analysis gives an
  argument register the base `(address:VOID a0)`; a pseudo set from `self + 0x660` first gets
  `(reg self)` (pass 1 reads the old array, still empty) and the last loop folds that into
  self's base. find_base_term of `(plus R 16)` returns that base only when R has
  REGNO_POINTER_FLAG (the `-dl` dump's "pointer"); otherwise it takes it only if it is a
  symbol or a Pmode ADDRESS (the stack), and an argument's is VOIDmode: the address has no
  known base and conflicts with every frame store. `self` is a pointer parameter, so a load
  at `self + 0x660` never conflicts with a frame slot (stack against argument,
  base_alias_check), while the inlined Rotate's address pseudo (`r = &m`, user variable,
  no pointer flag) gives rows 1 and 2 no base: they wait for every frame store. A row read
  through an address register CSE makes (`m.r[1]` of a reference) is flagged and passes the
  frame stores: that is why rows read as Vec values moved up.
- **What retail needs.** In StepAgent's first branch retail loads row 0 before the vdiv
  and stores dt's Scalar slot after it. After reload every `sp + n` slot conflicts with the
  loads through s0 and s2, so in sched2's input row 0 came before the slot store: sched1 issued
  row 0 first. Ours cannot: rows 1 and 2 depend on the slot store, which inherits their
  priority (11 against row 0's 9) and wins the memory cycle. Without the slot store (FromFloat,
  an experiment) the first branch is retail's instruction order exactly. Rows 1 and 2 must still
  wait for v's store (retail loads them after it), and both stores are frame slots, so no base
  rule separates the slot from v: only fixed_scalar_and_varying_struct_p does, with the slot
  MEM_SCALAR_P and the rows MEM_IN_STRUCT_P (adjust_priority's birthing rule does not apply:
  row 0's register dies in the block).
- **No plausible form makes the slot scalar.** A frame MEM is MEM_SCALAR_P only from a scalar
  decl in memory at expand_decl (TREE_ADDRESSABLE or volatile before its declaration is
  expanded, which g++ 2.95, expanding as it parses, never sees), assign_temp of a scalar with
  memory required (expand_expr taking the address of a register value), an inline parameter
  living in memory (passed on the stack or by invisible reference), or put_reg_into_stack
  (an ADDRESSOF that escapes). Retail's slot is at 0x20, among the expand-time temporaries,
  which rules out the escape (purge_addressof allocates after every local). Tried and folded
  back into registers or made MEM_IN_STRUCT_P: a `const u128&` parameter bound to an inline
  call's result or to `Vec::FromFloat(dt).q`, a named return value (`return t`), a `const u128`
  local, a pointer parameter to a local, a union and a one-element array (`/s`), and eleven
  integer arguments before the vector (still in registers).

### The same slot against a twist rate's load (func_0016C528)

A second function with func_001D87C8's blocker (2026-11-08, ApplyLinkConstraint, `-dS
-fsched-verbose-6` dumps; still a near miss):

- **What retail shows.** The last block computes `swingSpin = n * Scalar(lr / lt)`, then
  `twistSpin = dir * ScalarAt(self->f224->f94)`; both weights share the slot at 0x3E0 and retail
  stores the swing weight there first and the twist weight last, as ours does. But retail loads
  f94 (`lw v0, 148(v0)`, then qmtc2) straight after the swing spin's store and before the swing
  weight's slot store, and computes the twist spin and the total before the transposed rotation
  of b's spin. So in retail's sched1 the rate's load depended on the swing spin's store (a Vec
  member store, `mem/s`) but not on the slot store.
- **Why ours does not.** The rate is FromFloatAt's memory operand, read through a pointer loaded
  from memory (no known base), and the slot store has neither flag: the asm depends on both
  stores, the slot store inherits its priority (12) and goes first, and the rate waits behind
  the rotation's row loads; sched2 cannot undo it (the stores are to the frame, the load has no
  base). Only fixed_scalar_and_varying_struct_p separates the slot store from the load and not
  the Vec store, which needs the slot MEM_SCALAR_P and the rate read MEM_IN_STRUCT_P. With the
  swing weight in a scalar global (an experiment, not a form) the load and the twist arithmetic
  move up as retail has them.
- **Ruled out here** (on top of func_001D87C8's list): Scalar of the field by value (the f32
  pseudo prefers an FPR: lwc1, mfc1), the rate read into an `f32` local before the swing line
  (the load then comes early, as retail's, but into an FPR: regclass gives an SF pseudo set from
  memory FP_REGS even when its one use is an asm's "r"), a u128 slot local in a plain or a template helper, a Slot
  copied from a u128 local, a helper taking the weight as `const u128&`: each is purged back
  into a register, or leaves the Slot's `mem/s` store. Two functions now show retail's weight
  slots behaving as MEM_SCALAR_P: the original's weight was a scalar 128-bit object in memory,
  by a construct still to be found.

### The Scalar slot against a method-table load (func_0017ABE8)

SetModeColliderMode's mode 2 (`aim = FromFloats(0, 0, 2000); rates = D_00248D30;
D_00270650.vt->m16(&D_00270650, 2)`) is the same wall, and all of its 20 differing words come
from it (read from haifa-sched.c, alias.c, expr.c, stmt.c, integrate.c and cp/class.c with `-dS
-fsched-verbose-6` dumps, 2026-11-09, still a near miss):

- **What retail shows.** Retail stores the rates, the aim, loads the object's table (`lw a3,
  -624(v1)`), then stores FromFloats' slot (`sq a2, 0(sp)`) and loads the method (`lw v0,
  64(a3)`). In sched2 the table load depends on the slot store (a frame slot after reload against
  a hard register of no known base), so retail's sched1 issued the table load first.
- **Why ours cannot.** In sched1 the table load (insn 134) has no dependence on the slot store
  (its base is CSE's `&aim`, a symbol, against the frame), but the method load (138, through the
  loaded table, no base) does. The slot store therefore inherits the method load's priority:
  both it and the table load are at 7 (cost 2 + 5). The tie goes to INSN_REG_WEIGHT, where the
  table load is +1 (it sets a register, and `&aim` dies at the `this` argument after it) and the
  store 0; even at equal weights the store comes first in insn order. Nothing about luids or
  weights can reverse it: any order of statements leaves the store's priority equal to the
  load's, because both reach the call through insn 138.
- **The experiment.** The slot written as a `volatile u128` local of the helper (only to get a
  MEM_SCALAR_P frame store: fixed_scalar_and_varying_struct_p then separates it from the method
  load, mem/s through a varying pointer) gives retail's instruction order and every register of
  the function; only the delay slot differs (reorg does not move the `li a1, 2` past a volatile
  store). So the whole difference is that dependence.
- **Ruled out besides the forms of func_001C75B0.** The method load cannot be RTX_UNCHANGING_P:
  expand_expr sets that for an INDIRECT_REF only with TREE_READONLY and TREE_STATIC, and g++
  2.95's virtual calls (class.c, build_vtbl_ref) index the vptr through a plain indirect
  reference, so a real C++ virtual call is no different from the method table struct. Alias sets
  do not apply (`-fstrict-aliasing` is off). A u128 or a one-u128 struct is passed in a GPR (no
  invisible reference, so integrate.c's scalar stack copy of an argument is not reached). A
  scalar u128 local whose address only Vu0::Q takes is folded back into a register by
  purge_addressof (`t = r; return Q(t);` and `Q(t) = r; return t;` both lose the slot store).
  A reload spill is ruled out too: its store would follow the asm, and sched2 keeps the table
  load behind it.
- **What this says about the helpers.** Three near misses (func_001D87C8, func_001C75B0 and this
  one) would match with a scalar slot, so retail's Scalar and FromFloats slots were probably
  MEM_SCALAR_P: the original helpers kept a scalar in memory, in some form not found yet.

### A caller's FromFloat slot against an inline parameter's loads (func_001A00A0)

DrawStreakEffect (`k = FromFloat(-m)`, `pos = MulAddX(q80, qA0, k)`, then the clamped quadratic
of the file's ClampedQuadratic) is a fourth function behind the wall (`-dS -fsched-verbose-6`
dumps, 2026-11-09, still a near miss):

- **No known base for an inline parameter set from a sum.** ClampedQuadratic::Get passes
  `(const QuadraticCoeffs*)&self->q40` to Eval, whose `p` becomes a pseudo set to `self + 0x40`.
  find_base_value of that PLUS replaces `self` by its base, `(address a0)`, and then asks
  find_base_value of the ADDRESS itself, which falls to the default case: 0. So `p->b` and `p->c`
  (`mem/s` through the pseudo) may alias k's frame store (`Q(k) = ...`, neither flag), while
  `p->a`, which CSE folded to `self + 0x40` directly, has the parameter's base and does not.
- **What it costs.** sched1 issues k's store at t=4, before the loads that depend on it; the
  quotient then takes $f5 and the upper bound $f4 (retail $f4, $f5), and the store sits before
  the coefficient loads where retail stores it in the first bc1f's delay slot.
- **Retail's slot is scalar.** Retail's k is at 16(sp), after pos (an aggregate at 0), and its
  store has no dependents in retail's order. The experiment of a `volatile u128` local given the
  FromFloat value (only to get a MEM_SCALAR_P frame store) gives every register and instruction
  order of retail; only the store stays out of the delay slot (reorg does not move a volatile
  store). It is not the effect method's signature: slot 5 of the kind-8 and kind-17 tables is a
  draw method `(self, camera)`, and retail calls no base method here.

### The weight slot is a cast's copy (func_001D87C8, func_001C75B0, func_0017ABE8)

The Scalar-slot wall of the two sections above, and of func_0016C528, func_00181078 and
func_0017ABE8, has one answer (2026-11-09, read from expr.c, stmt.c, function.c and cp/typeck.c
of 2.95.3, with `-dS` dumps): retail's weight slot is the copy g++ 2.95 makes of a cast bound by
reference.

- **The rule needed.** A store at a fixed frame address and a load through a pointer of no
  known base are separated only by fixed_scalar_and_varying_struct_p: the store MEM_SCALAR_P,
  the load MEM_IN_STRUCT_P (a structure member). A `volatile u128` slot gives it (func_0017ABE8's
  probe: retail's order and registers), and so does a u128 local whose address escapes
  (func_00181078's probe), but purge_addressof allocates that one after every local.
- **Where an expand-time scalar slot comes from.** expand_expr's ADDR_EXPR copies an operand
  that expanded to a register into `assign_temp (type, 1, 1, 1)`: a temporary allocated where the
  expression is expanded (so the weights of one sum share it, as retail's do), flagged
  MEM_SCALAR_P for a scalar type, stored once and, read back through the address, folded to the
  register by CSE. The C++ front end builds such an ADDR_EXPR for a cast of a variable: a cast
  is an lvalue to g++ 2.95 (lvalue_p_1: NOP_EXPR), `&(s128)r` is accepted (pedantic warns), and
  mark_addressable stops at the NOP_EXPR, so r stays a register and only the cast's value goes to
  memory. Binding a reference to the cast does the same (build_up_reference), so `Vu0::Q((s128)r)`
  or a `const s128&` parameter given `(s128)r`. A same-type cast is not an lvalue (non-lvalue
  error); the cast must change the type, here between the unsigned and signed 128-bit types.
- **The helpers.** Vu0::Scalar, ScalarAt, FromFloats and ScalarInGpr now return `Q((s128)r)`
  instead of storing to a 16-byte local of their own (Vu0::Slot, an aggregate, written through
  Q: no flag). Every function the build linked from C still matches with the change (US and PAL
  MATCH), and five near misses match with it: func_001D87C8, func_001C75B0 (with
  Vu0::RotateMembers, whose row loads are Vec members, MEM_IN_STRUCT_P, so rows 1 and 2 pass the
  weight's store but still wait for v's), func_0017ABE8 (FromFloats' slot against the method
  table's load), func_00184B58, func_001C57C8 and func_001A00A0 (whose caller-side
  `Q(k) = FromFloat(-m)` into a Vec02 local was the weight of `Scalar(-m)` passed straight to the
  MulAddX: its slot follows pos as an expand-time temporary). Retail's sources most plausibly had the same:
  Sony's headers have both 128-bit types (signed and unsigned), and a helper taking one by
  reference called with the other cast to it binds such a copy.
- **A float operand by value.** Vu0::ScalarAt reads its float through a `u32` cast pointer (no
  flag). func_0016C528's twist rate (`self->f224->f94`) must stay a member load to pass a weight's
  store: Vu0::ScalarAtValue takes the float as a `const f32` by value, which an inline call passes
  as the caller's own memory reference, flags included (integrate.c copies an argument to a
  register only for a parameter that is not read-only), as the asm's "rV" operand. Making it
  ScalarAt itself changes func_001DDE90.
- **Still short.** func_00181078's axis shares the weight's slot (0x50) and its address goes to
  two calls: `const s128& k = (s128)w;` gives retail's frame and block but for the reference's
  address, set at the binding (and so issued first by sched1) where retail forms &k at its first
  use, as for a named local; a named scalar local in memory from its declaration needs
  TREE_ADDRESSABLE before expand_decl, which g++ 2.95 never gives. func_0014F168 is now retail's
  size with only the call's `addiu a1, sp, 16` early.
- **A receiver loaded early (func_0015BC78).** Its `Q(k) = FromFloat(-1.0f)` into a Vec02 local
  held the virtual call's receiver load (`self->receiver678`, a member through a pointer) behind
  the weight's and the message's stores, so local-alloc tied it to a0. With `Scalar(-1.0f)`
  passed to MulX the load rises above the vmulx into a2 and the call's delay slot takes
  `move a0, a2`, as retail. Spot it: retail's receiver in a2 (or another free argument
  register) copied to a0 in the jalr's delay slot.

### Rows bound by reference as s128 (func_00181658)

RecomputeModeWalker rotates a basis's three rows by a product matrix, and retail stores each
result three times: to the basis (0x50), to a matrix local (0x80) and to three more 16-byte
slots at the frame's end (0xB0, 0xC0, 0xD0). The last store of the third group fills the first
virtual call's delay slot and the group interleaves with the call's loads (`self->fC08`, its
method table, the method), where every attempt with plain locals (Mat02 or Vec02 copies, the
mul_rotation.h forms) scheduled all nine stores before `lw a0, 0xC08(s2)` and left a nop: 296
bytes against 292.

- **The mechanism.** In sched2 (after reload the base of s2 is no longer known) a load through
  a register waits for every frame store that is not MEM_SCALAR_P at a fixed address
  (fixed_scalar_and_varying_struct_p). The first two groups are a struct's memory, so the loads
  wait for them; the third must be scalar. A `volatile u128` probe for it was EXACT.
- **The plain form.** A helper taking the rows as `const s128&` called with u128 values: each
  argument's conversion is a copy g++ makes into a temporary of the scalar type (the cast's copy
  of "The weight slot is a cast's copy"), and the three of one call get three slots, allocated
  after the block's locals. The helper writes the matrix local, which is then assigned to the
  basis: `Mat02 rot; SetMatrixRows(rot, x, y, z); m2 = rot;`. Three `const s128& a = (s128)x;`
  statements share one slot (each statement frees its temporaries), and the rotations written
  as the call's arguments change the order.
- **Spot it:** a group of dead 16-byte stores at the frame's end that sched2 lets pass loads
  through pointers, one slot per row: rows passed by reference across the two 128-bit types.

### A weight named before the normalisation it scales (func_0018DDD8)

LaunchContactListObjectWithoutGravity stores `MulX(NormalizeOrMoved(v150, unit x), speed)`.
Retail loads the speed (`lw v0, 0x6F0(s0)`) right after the velocity's lqc2, moves it into
vf4 after the dot's vmaddz and stores the weight's slot (`sqc2 vf4, 0(sp)`) in the branch's
delay slot. The near miss's own `Vec02 k; Q(k) = FromFloatAt(speed)` (an aggregate written
through Q: no alias flag) left the load after the square root and the store folded into the
result's address; `Vu0::ScalarAt(self->speed6F0)` written inside the MulX call is expanded after
the NormalizeOrMoved (the inline call's nested arguments, right to left), so its lw comes after
the branch. Named first, `u128 speed = Vu0::ScalarAt(self->speed6F0);` before the statement,
its lw and qmtc2 get the earliest LUIDs, and the slot is the expand-time MEM_SCALAR_P copy of
"The weight slot is a cast's copy": byte for byte retail's (2026-11-09). The same body with
Vu0::Vec::ScalarAt (a Vec value) is 4 bytes longer (a movti copy). The function also takes the
base method's two parameters and passes them on (a1, a2 untouched before the jal; the base,
func_0018DA40, stores them), though dropping them leaves the bytes unchanged here.

### A weight that dies at its multiply gives the product its register (func_001980B0)

StepGaugeColliderAgent rotates `MulX(v640, Scalar(-1.0f))` by the matrix at 0x110. Retail keeps
the -1 weight (vf6) live past the vmulx and stores its slot after it, so local-alloc ties the
product to v640's register (vf3, which Rotate's "0" ties on to the rotated result) and dt's
weight is vf7. With Vu0::Rotate (rows read through a `const u128*`, no alias flag) the `-dS`
dump shows the weight's slot store (`mem/f:TI`, MEM_SCALAR_P) scheduled before the vmulx: the
three row loads after it in the insn stream conflict with it, so sched1 must issue the store
first, and the weight's pseudo then dies at the vmulx (REG_DEAD on both inputs), where
local-alloc ties the product to it (MulX lists the scale first). Vu0::RotateMembers reads the
rows as Vec members (`mem/s:TI`, MEM_IN_STRUCT_P), which fixed_scalar_and_varying_struct_p
separates from the scalar slot: the store, with no dependents, sinks below the vmulx and the
rows, the weight outlives the multiply, and the product takes v640's register. Passing
`Vu0::Scalar(-1.0f)` straight to the MulX and the rows as RotateMembers is retail's code, byte
for byte. The near miss's notes (Scalar inline, Vec values, RotateUntied, RotateRows) had tried
every half of it but not RotateMembers, which came later. Spot it: a product that takes the
weight's register where retail's takes the vector's, in a rotation's argument, is a Rotate whose
rows should be RotateMembers.

### A method read as a descriptor member passes the weight slots (func_001EB698)

ContinueBeatPressColliderRequest (a MulXSum of two rows of the object's matrix, weights
`-D_00275CD0` and `D_00275CD4`, then the player's slot 0x90 method with the sum) matched on
2026-11-09 with the scalar slot and one more change (`-dS -dR -fsched-verbose-6` dumps):

- **The slot alone was not enough.** With Vu0::ScalarAt's cast-copy slot in place of the near
  miss's own Slot local, the order stayed the same: the method load `lw v1, 144(v0)` still
  waited for both weight stores. The call read the method through
  `((PlayerSlotFn*)self->desc)[0x90 / 4]`: an array element through a cast pointer, a MEM with
  no flag, which fixed_scalar_and_varying_struct_p cannot separate from a MEM_SCALAR_P frame
  store (it needs the varying side MEM_IN_STRUCT_P).
- **The fix.** `self->desc02()->m20(self, &dir)`, the descriptor's member (Desc02, as the rest of
  the project calls slot 0x90), is a `mem/s` load; it passes the second weight's store, so
  sched1 issues the table load first, the method load before that store, and reorg puts the store
  in the jalr's delay slot, as retail does. The method load still follows the sum's own store
  (`Q(dir)`, no flag), which retail shows too.
- **Lesson.** Where a near miss behind the Scalar-slot wall calls a method through a cast array
  of function pointers, write the call through the descriptor struct's member: both sides of
  the alias rule need their flag.

### A rotation product's vector slots are scalar (func_0014A8F8)

### Weights read where they are used, and a radius that is a call's argument (func_001719E8)

func_001719E8 (the player's per-part probe: three samples of an animation, the record's start,
radius and segment, then CollectBoundsSpans) went from 47 differing lines to retail's bytes on
2026-11-09 (`-dS -dR -fsched-verbose-6` dumps, tools/regalloc.py). Three levers, in cascade order:

- **The weights' loads ride on the rec stores.** The near miss read both weights
  (`Vu0::ScalarAt(D_00263880)`, `D_00263884`, scalar globals) into locals right after storing
  rec->v20, through ScalarAt's cast pointer (no flag) and with rec->v20 stored through `Q()` (no
  flag). Each qmtc2 then had a true dependence on the rec->v20 store and an anti dependence on the
  later rec->f08 store (the long path through the lengths), so the luis' priority was 12
  against the unit-Z address's 10, and sched1 hoisted the luis and qmtc2s to the top of the block. The
  hoisted `high(D_00263884)` overlapped the life of `obj->body` (v0), local-alloc gave it a2,
  and the a2 it then held after the third call gave that call's `move a2,s1` one more dependent,
  which moved it ahead of t0 and t1 (the first visible difference). With the weights passed
  straight to the MulAddX calls as `Vu0::Vec::ScalarAtValue(D_...)` (the caller's own
  MEM_SCALAR_P reference) and rec->v20 stored as a Vec (`*(Vu0::Vec*)&rec->v20 = ...`,
  MEM_IN_STRUCT_P), the loads come after the rec->f08 store in insn order and depend on neither
  store (fixed_scalar_and_varying_struct_p), the luis' priority falls to 9, the unit-Z address
  goes first, and the GPRs and VU registers (weights in vf6 and vf3) are retail's. Writing the two
  MulAddX statements in v60, v70 order puts the -50 product in vf3, as retail.
- **ToFloatMoved for the lengths.** ToFloat's separate mtc1 let sched2 put the first weight's
  slot store between the second qmfc2 and its mtc1; ToFloatMoved (the compiler's own qmfc2)
  gives retail's `sqc2; qmfc2; mtc1`.
- **A missing float argument.** Retail adds the radius into $f12 and never names $f12 again:
  CollectBoundsSpans (func_00141F48) starts `mul.s $f1, $f12, $f12`, so its last parameter is the
  radius, and the call passes `rec->f08`. The argument's copy to $f12 gives the sum a preference
  for $f12 in local-alloc (child_group_object.cpp and player_target.cpp already declared it so).
  With the sum tied to the second operand's register, the lengths are written
  `Length(f84->v100) + Length(v70)`: the RTL `(plus L2 L1)` is retail's `add.s $f12,$f12,$f0`.

Spot it: a float result that lands in $f12 with no call reading it is an argument the declared
prototype is missing; weights whose loads sched1 hoists to the top of a block read memory with
no flag next to stores through a pointer.

### A slot store after reload, and which load passes it (func_0015BFC0)

func_0015BFC0 (whether an active collider's position plus half its velocity is within f684 of
the cycler) matched on 2026-11-10 from 65.8%, with `-dS -dR -dc -fsched-verbose-6` dumps:

- **sched2 sees every frame store as varying.** After reload a slot's address is `$sp + n`, and
  rtx_varies_p counts only the frame, hard frame and argument pointers as fixed, not the stack
  pointer; so fixed_scalar_and_varying_struct_p no longer separates a MEM_SCALAR_P slot from a
  `mem/s` member load, and every load after the slot store in sched1's output waits for it in
  sched2. A member load that sched1 lets pass the slot is held behind it again unless it was
  already before the store in the insn order.
- **So the expansion order decides.** Retail loads the position (`lqc2 vf3, 320(v0)`) before
  the weight's `sqc2` and the velocity after. An inline call's argument that is itself an inline
  call is expanded first and a plain memory reference second (the two-pass rule): with both
  operands read in the MulAddX (`Q(a->v140)`, `Q(a->v150)`), both loads follow Scalar's store;
  with both as Vec::Of, both precede it. `Vu0::Vec pos = Vu0::Vec::Of(active->v140);` as its own
  statement before the sum puts the position's load first and leaves the velocity, read inside
  the sum, behind the store.
- **The registers came with it.** Before, sched1's tie between the two loads (same priority and
  dependents) went to the one with the lower INSN_REG_WEIGHT: the later load in the insn order
  carries `active`'s REG_DEAD note, so the velocity went first and took vf3. With the position
  loaded first, local-alloc gives retail's vf3 (position, then the sum) and vf2 (velocity, then
  the Dot's 1.0).
- **Then the conversion.** f684's load and square still came after the difference's load: in
  sched2 the difference's `lqc2` had priority 10 against the f684 load's 9, through the
  compiler's mtc1 (cost 2). Vu0::ToFloatMoved (the compiler's qmfc2, cost 1, then the helper's
  mtc1, 1) brings it to 9 and f684 goes first, as in retail (ToFloatViaBits also matches;
  ToFloatNow does not).

### A rotation product's vector slots are scalar (func_0014A8F8, unsolved)

Read from function.c, stmt.c, expr.c, alias.c and haifa-sched.c of 2.95.3 with `-dS -dR
-fsched-verbose-6` dumps (2026-11-09). The product of two rotations that mul_rotation.h writes
(each row stored to a matrix local r and to a vector local x, y or z, then `*out = r`) leaves
func_0014A8F8 two stores apart: after the third product retail stores 0x10, 0x20 (out's rows 1
and 2), 0x80 (r's row 2), 0x00 (out's row 0) and 0xb0 (z) last; ours stores z before out's row 0.

- **Why ours differs.** The five stores have priority 23; out's rows 1 and 2 hold the deaths of
  the row values (weight -1) and go first, and the rest tie on dependents (seven each: every
  later load through a pointer, `cam->f364` included, and the call), so INSN_LUID decides, and
  z's store precedes `*out = r` in every form whose copy follows the rows.
- **What retail's z is.** A MEM_SCALAR_P store at a fixed frame address does not conflict with
  a structure member's load through a pointer (fixed_scalar_and_varying_struct_p, in
  true_dependence and write_dependence_p alike), so it loses `cam->f364` (`mem/s:SF`) as a
  dependent and goes last: with x, y and z as Vu0::Scalar's cast copies (`Q(r.r[i]) =
  Q((s128)x)`), sched1 gives retail's exact order 0x80, 0x00, z, and the stores of rows 0 and 1
  stay where retail has them (r's store first: its priority is higher, since the next row's
  load waits for it and not for the scalar). Retail's slots are also where a scalar's slot goes:
  0x90, 0xa0, 0xb0 are the top of the locals, above the inlined body's frame (r at 0x60), which
  is where purge_addressof's put_reg_into_stack allocates a scalar whose ADDRESSOF escapes.
- **Why no plain form gives them.** The three slots are distinct and each is stored before the
  next row's load (a store made after that load anti-depends on it), so each must be made in its
  own row's statement and outlive it. A cast copy's slot
  (`assign_temp (type, 1, 1, 1)` in expand_expr's ADDR_EXPR, addr_taken) is freed when its
  statement ends: g++ wraps each statement and each declaration's initialiser in
  expand_start_target_temps (push_temp_slots plus expand_start_bindings, two levels) and
  expand_assignment pushes a third, while preserve_temp_slots (expand_expr_stmt's, expand_decl_init's)
  promotes an addr_taken slot one level at a time. Tried, all with one shared slot at 0x90 and a
  frame 32 bytes short: the cast as Q's argument, as `*(const u128*)&(s128)x`, as an inline call's
  `const s128&` argument statement (`SetRow(r.r[0], (s128)x)`), bound to a local reference or
  pointer (`const s128& x = (s128)v;`, `const s128* x = &(s128)v;`), in the inline's body or
  written in the caller, and as each row's own inline call returning `Q((s128)r)` (its frame is a
  temporary of the statement). A `const u128&` bound to the product's rvalue is a register, and a
  u128 local whose address only reaches Q or a `u128&` parameter is purged back into a register.
  Three casts in one statement do get three slots (0x90, 0xa0, 0xb0), but made after the rows they
  anti-depend on the row loads and are stored last. An escaping address does give the frame: a
  probe whose x, y and z are written by an asm `sqc2` with an `"=m"` output (not a permitted
  helper: the compiler emits sqc2) has retail's frame and first two groups, with z stored first
  in the third group because an asm has no function unit. Sweeping the declaration order (r
  before or after x, y, z) and the four ways to write each row's two stores (chained either way,
  or a statement and a struct copy either way) gives 2 to 5 lines, never fewer.
- **What would close it.** A plain construct that leaves a 16-byte scalar's address escaping
  after CSE (so put_reg_into_stack gives it a scalar slot at the top of the frame) without code of
  its own; the same construct would likely explain the varying store orders of mul_rotation.h's
  other sites, which are one inline helper in the original.
- **Solved (2026-11-10, w11-14A8F8).** The construct is one call with the rows computed in its
  arguments: mul_rotation.h's MulRotationIndexedSetRows, `SetRows(*out, x = Q(r.r[0]) =
  RotateRows(a0, a1, a2, q[0]), y = ..., z = ...)`, with x, y, z u128 variables. Each argument is
  an lvalue of a u128 variable (a register) bound to a `const s128&` parameter, so expand_expr's
  ADDR_EXPR copies it into an assign_temp slot (MEM_SCALAR_P) at that argument's expansion: right
  after its row's product and r's store, before the next row's load. All three temporaries
  belong to the one call statement, so their slots are distinct (0x90, 0xa0, 0xb0) and survive
  to its end. The first two have the next row's load (a u128 read, no alias class) as a
  dependent and are stored at once; z has none and goes last. SetRows then writes out's rows
  from the registers. Variants: the products as rvalues (`SetRows(r, RotateRows(..), ..)`) get
  no slots (the TARGET_EXPR's pseudo is purged back), an assignment to memory (`Q(r.r[0]) = ..`
  alone) binds the reference to r's row itself (no slots, frame 160), and separate statements
  before the call (`u128 x = ..; SetRows(..)`) store the slots after every load (26 lines). b's
  rows by index (`q[i]`) or as Vec members both match; Q(b.r[i]) differs. func_001721B0's
  product takes the same helper (98 lines to 5); func_00149760's do not (frame grows).
- **func_00172078's second product** (near miss on another branch) takes the same one-call form
  with the matrix local passed in and its rows read as Vec members (`SetRows(*out, x = Q(a.r[0])
  = RotateRows(.., q[0].q), ..)` after `Mat02 a;` in the caller): three slots at 0xa0 to 0xc0,
  5 lines to 2. It and func_001721B0 keep one tie: retail stores z's slot before r's row 2 at the
  block's end, ours after, whichever way each argument's chain is written.
- **Closed (2026-11-10, w11-1721B0).** The slot is copied first and r's row stored from it,
  `Q(r.r[i]) = Q((s128)(x = ...))` with SetRowsFrom's `const u128&` parameters (MulRotationCopied):
  all three functions match ("A rotation product's last two stores").

### Three row copies made by one call (func_00122B30)

GetIdentityPoseRotation matched from 69.3% (2026-11-09, `-dS -dl -dR -fsched-verbose-6`
dumps, alias.c and function.c of 2.95.3). It has a rotation product, `*rot = self->rot *
*rot`, then the spin turned by self->rot.

- **What retail shows.** The frame holds two 48-byte groups. One (0x00 to 0x20) is stored with
  the result's rows, before the spin's loads. The other (0x30 to 0x50) is stored after them: row
  0 between the spin's add and its store, rows 1 and 2 after the epilogue's restores. The spin's
  rows 1 and 2 are loaded through `v0 = s1 + 64`, a pseudo of no known base, so their loads
  wait for every frame store that may alias them.
- **The mechanism.** The late group is scalar memory. A MEM_SCALAR_P store at a fixed address
  never conflicts with a MEM_IN_STRUCT_P load through a varying address
  (fixed_scalar_and_varying_struct_p). Its rows have no dependents, so sched1 sinks them and
  local-alloc keeps their registers (vf7, vf8, vf5) live past the spin. The spin's rows must be
  struct loads, so the spin is Vu0::RotateMembers. With Vu0::Rotate's u128 reads (no flag) the
  late stores stay ahead (37 lines). The three slots are distinct and sit above the matrix
  local, so all three are alive at once.
- **The form.** mul_rotation.h's `SetRows(Mat02& m, const s128& x, const s128& y, const s128& z)`,
  called once with the three product rows as u128 variables. Each argument is converted from
  u128 to s128, so g++ binds a temporary of the parameter's scalar type to each reference. That
  gives three assign_temp slots (MEM_SCALAR_P), all alive for the one call statement. Then
  `*out = r`. Each of these alone gives 32 lines and one shared slot or none: `const u128&`
  parameters (the variables bound directly, purged back into registers), the products passed
  as rvalues (with either type), a u128 row read as `(Vec02&)x`, and a cast copy per statement.
  This is the construct func_0014A8F8's notes above ask for, and there the stores of those
  slots must come last too ("Three casts in one statement ... are stored last"). It may close
  that near miss and explain mul_rotation.h's other forms. There the rows must be computed in
  the call's own arguments (the section above, "Solved").

### A rotation product's row slots are cast copies (func_00172078, near miss)

func_00172078 (two rotation products, `c = rot m`, then `a = c f61C->rot`, `*out = a`) went from
32 differing lines to 5 on 2026-11-10 (`-dS -dR -fsched-verbose-6` dumps, a local-alloc emulator
on the `.lreg` dump). Read with alias.c (true_dependence, base_alias_check, find_base_term),
function.c (assign_stack_temp_for_type, purge_addressof_1), stmt.c (expand_decl), expr.c
(INDIRECT_REF, ADDR_EXPR) and integrate.c of 2.95.3.

- **The registers are local-alloc's priority, decided by one insn.** The second product's row 0
  of f61C's matrix and its result are one quantity (6 references); with a life of 20 its
  priority (1.2) beat the first product's `a0 + z` and `m1 + y` quantities (1.15, 1.09), so it
  took vf4 and pushed theirs to vf5/vf6 (retail: vf4, vf5, vf6 the other way). Any sched1 order
  that issues that row load one insn earlier (life 22) gives retail's allocation, by the
  emulator and by the compiler.
- **Why the load waited.** It went after every frame store of the first product: its address
  (`f61C + 0xD0`, a pointer loaded from memory) has no base, so base_alias_check cannot separate
  it from the stack, and neither MEM carried a flag (`*(u128*)&` stores and loads). Retail's
  sched2 issues it before the first product's y and z slot stores but after the stores to the
  matrix local, and loads rows 1 and 2 after the previous row's store to `a` but before its slot
  store: the slot stores are MEM_SCALAR_P at fixed addresses and the row loads MEM_IN_STRUCT_P
  (fixed_scalar_and_varying_struct_p), while `a`'s and `c`'s rows (no flag) conflict.
- **The plain form.** f61C's rows read as Vec members (`((const Vu0::Vec*)&b)[i].q`: `/s`)
  and each row value stored through a cast's copy (`Vu0::Q((s128)x)`, as Vu0::Scalar). With both,
  registers, frame and every store but the second product's slots are retail's.
- **What is left: three slots in per-row statements.** Retail's slots are distinct (0xA0, 0xB0,
  0xC0 in both products, the inline frame's). Three casts that are arguments of one inline
  call (`SetRows(out, Q((s128)x), Q((s128)y), Q((s128)z))`) get three: they are expanded in the
  caller's statement before the call's body. That suits the first product (its loads are frame
  slots at fixed offsets, which never conflict). The second product needs out's row stored
  before the next row is loaded (its rows wait for `a`'s stores in retail), so its stores are
  per row, and a cast's temporary (`assign_temp (type, 1, 1, 1)`, keep 1) is freed when its
  statement ends: every row's slot is 0xA0. With SetRows there too, the rows load before any
  store (37 to 42 lines). Ruled out for the second product: per-row stores then one call with the
  three casts (38: the slot stores move after the last product), the casts bound to references
  or a pointer (shared slot), a row helper returning `Q((s128)r)` per statement or in one comma
  expression (an inline's frame block is free again when the call returns: shared), a `const`
  reference bound to the product's rvalue (a register, no slot), volatile slots (56). What would
  close it: a plain construct that keeps three 16-byte scalar slots alive across three
  statements, which none of temporaries, reference bindings and inline frames gives in g++ 2.95.
- **Matched (2026-11-10).** Three slots alive across three statements are not needed: one call
  with the rows computed in its arguments gives them, each slot copied before r's row is stored
  from it ("A rotation product's last two stores", below).

### A rotation product's last two stores (func_001721B0, func_00172078)

Both near misses matched on 2026-11-10 (`-dS -dR -fsched-verbose-6 -dc` dumps, haifa-sched.c's
rank_for_schedule and find_insn_reg_weight, reorg.c's fill_simple_delay_slots, of 2.95.3). Each
was one tie from retail: after the product's out rows, retail stores z's slot and then the
matrix local's row 2 (into the delay slot of `jal`, or of `jr` after the epilogue); ours the
other way.

- **reorg is not it.** fill_simple_delay_slots scans back from the call and takes the first
  insn that fits; its resource model has one bit for memory, so if the store just before the
  call could not go, the one before it could not either. Retail's sched2 therefore ended with
  z's slot, then r's row 2.
- **sched1 decides by LUID.** The five stores have equal priority (9 in func_001721B0, 2 at the
  end of func_00172078's block) and equal dependents (the call and the jump, or none). The out
  rows carry the deaths of the row values (INSN_REG_WEIGHT -1, -2 where the out pointer dies too:
  func_00172078's out rows 0, 2, 1 order is this) and go first; the slot and r's row 2 have
  weight 0, so INSN_LUID, the expand order, breaks the tie. With MulRotationIndexedSetRows's
  `x = Q(r.r[i]) = product` arguments, the slot is the argument's conversion to s128, made after
  the whole argument, so r's store always precedes it, whichever way the chain is written. For
  retail's order the slot must be made first, and the row value must still die at the out row
  (func_00172078's out row 2, with weight -2, shows it), so r's row is stored between the slot
  and the call's body, from the slot.
- **The form.** `SetRowsFrom(*out, Q(r.r[i]) = Q((s128)(x = product)), ...)` with
  `const u128&` parameters (mul_rotation.h's MulRotationCopied, and MulRotationCopiedVia with
  the matrix local the caller's): the cast of the variable copies it into the scalar slot when
  its address is taken, r's row is stored from the slot (CSE reads it back from the register),
  and the parameter binds to r's row itself (a u128 lvalue: no second copy). The three slots
  stay one call's temporaries (distinct, 0xF0 to 0x110 or 0xA0 to 0xC0). Every row then has the
  slot's store first in LUID, so the earlier rows need b's rows read as Vec members
  (MEM_IN_STRUCT_P): the next row's load then waits for r's store but not for the slot's
  (fixed_scalar_and_varying_struct_p), r's store has the extra dependent and goes first, and the
  slot's store fills the load's latency, as retail's rows 0 and 1 show. With b's rows by index
  (u128, no flag) the earlier rows' two stores swap (7 lines). UpdateFrameCameraController
  (func_0014A8F8) matches with the same helper, so MulRotationIndexedSetRows is gone: one
  form for the three products.
- **func_001721B0's 0.0 in $f12 was a missing argument.** OrientPlayerSpinPart (func_00172078)
  reads a float t in $f12 (its angle is `f2434 - dt * f2430 * t`), and player.cpp already
  declared it so; the call passes 0.0f, which CSE shares with the two compares' 0.0 and which
  takes $f12 by the argument copy's preference. The near miss declared two parameters.

Spot it: two stores that tie at a block's end in retail's order opposite to their expand order
mean the later statement of the pair was expanded first; a constant whose register is an
argument register no call seems to read is an argument the declaration is missing.

### An inline method's this: a fresh pseudo with no pointer flag (func_00117FE0, matched 2026-11-10)

- **What differed.** FindScriptObjectsInBox computes `lo = min(a, b)` and `hi = max(a, b)` of
  its first two vector arguments. Retail reads `args[1].v` twice, once after the store of lo
  (`addiu v1,s0,8; lw a0,4(s0); lw v0,4(v1); ...; sqc2 $vf1,16(sp); lw v0,4(v1)`), but
  `args[0].v` once. Every plain form (locals, `ScriptValue* pb = &args[1]`, `args[1].v`
  written twice, Vec or u128 locals, Q or Set) keeps one load of each: CSE1 and CSE2 merge the
  two `lw`, because a store addressed from the frame never conflicts with a load whose base is
  an argument (alias.c's base_alias_check: "a stack reference can not alias a parameter").
- **When the base is unknown.** find_base_term of `(plus R c)` uses R's base value only if R
  has REGNO_POINTER_FLAG; otherwise it looks at both operands and returns a base only for a
  symbol or a non-argument ADDRESS. An argument's base is a VOIDmode ADDRESS, so through an
  unflagged register the load has no base, base_alias_check says "may alias", the frame store
  kills it in CSE and sched1 keeps it after the store (the scheduler re-runs alias analysis).
  A pointer variable set twice (`v = args; ...; v = &args[1];`) keeps both loads through CSE,
  but flow deletes the dead first set before sched1, which then hoists the second load above
  the store and postreload merges it: not enough.
- **Who makes such a register.** integrate.c's process_reg_param copies an inline argument that
  is not a register into a fresh pseudo with copy_to_mode_reg, which sets no pointer flag (the
  flag is set only when the argument already is a register, at expand_inline_function's
  mark_reg_pointer). A member function's `this` is read-only, so for `args[1].Method()` the
  argument `args + 8` is such a copy; for `args[0].Method()` it is `args` itself, flagged.
- **The form.** An inline accessor on ScriptValue, `Vec02* Vector() const { return (Vec02*)v; }`
  (include/script_value.h), called as `*args[0].Vector()` and `*args[1].Vector()` in both
  statements. The first argument's pointer is loaded once (known base), the second's twice,
  through one `this` register: retail's code, the prologue's order included. The original's
  value class plausibly had such an accessor; the asymmetry comes from the inliner, not from
  the source.
- **Spotting it.** A field of `args[k]` (k > 0), or of any `&array[k]` or `p + k` passed as
  `this`, reloaded after an unrelated frame store while the same field of the first element is
  not: read it through an inline member function.

### A pointer set three times has no base: its stores kill the frame (func_00187260)

alias.c's init_alias_analysis gives a pseudo a base (find_base_value) only when it is set
once: record_set wipes it to unknown on a second set. A pointer from an incoming argument
(`&out[n++]`, out in $t2) has the argument's base, which base_alias_check separates from every
frame address, so CSE keeps a frame local's stored value in its register across stores through
it. Retail's CollectMeshHits reloads its point (`lqc2 $vf2,5920(sp)`) after the hit's normal is
stored, and copies the edge hit's normal from its slot (`lq v0,4128(sp)`) after the point's
store: those stores may alias the frame. One `MeshHitEntry* o;` declared with the function's
other locals and assigned at each of the three places a hit is appended has three sets, no
base, and gives both reloads (the hits' other stores unchanged). The sibling func_00186568
reuses one face pointer for its three loops the same way. Spot it: a frame local reloaded
after a store through a pointer derived from a parameter, where ours keeps it in a register.

### An inline's pointer parameter and frame stores (func_001A2830)

MoveTumblingEffect matched on 2026-11-10 from 32.7%. Three mechanisms, each read from the
`.sched` and `.lreg` dumps:

- **find_base_term needs the pointer flag.** For an address `(plus P 16)`, alias.c's
  find_base_term takes P's base only when P has REGNO_POINTER_FLAG; otherwise it looks up both
  operands and keeps a base only if it is a symbol or a Pmode ADDRESS (the stack). An argument's
  base is a VOIDmode ADDRESS, so `(plus P 16)` with P an unflagged copy of `self + 0x50` has no
  base, base_alias_check answers "may alias", and the load depends on every earlier frame store
  through a `u128` cast. A declared pointer local (`Vec02* b = self->rot50;`) is flagged
  (expand_decl), so its loads never wait for the frame; an inline function's pointer or
  reference parameter is a pseudo of the inline's own without the flag. Retail's rows 1 and 2 of
  the placement, loaded at `0x10(s0)` and `0x20(s0)` each after the stores of the row before, with
  s0 set before the call that builds the turn, are a reference parameter of an inline that makes
  that call (`TurnEffectAboutRow(self, *(Mat02*)self->rot50, &turn, angle)`); row 0's load,
  `(mem P)`, is folded by CSE to `0x50(s1)` (self, flagged) and so issues early. The rows are
  stored through the effect (`*(Mat02*)o->rot50 = r`), so the stores use s1 and the turn's rows,
  loaded once, are not reloaded. Spot it: loads through a register that crosses a call and is
  never folded into the object's offset, each after the frame stores before it.
- **An in-place normalisation as an inline over a pointer**, `*v = fallback` in one arm and
  `Q(*v) = DivX(t, l)` in the other with `t` a `Vu0::Vec` copy of `*v`: retail's
  `lq v0,48(sp); qmtc2 v0,$vf3` (the copy through a GPR), the fallback's address before the
  branch and its `lq; sq` in the arm, and a store in each arm, with the length's two conversions
  (ToFloat for the test, ToFloatMoved for the returned length after the join).
- **One float scratch for two values** (`t = ToFloat(Dot(..))`, later `t = NormalizeInPlace(..)`):
  two sets and two deaths, so local-alloc leaves it to global-alloc, which places it above every
  local of both blocks ($f4 in both, where ours had $f0 and $f3), and a product no longer ties to
  it (retail's `mul.s $f0,$f4,$f0`). Spot it: the same high FPR for two unrelated values that
  each live in one block, with the block's other temporaries packed below it.

### Global allocation's preferences (func_00149760)

- find_reg's first pass skips every register in `regs_someone_prefers`: the full preferences
  of the lower-priority allocnos that conflict with this one (prune_preferences), unless it
  prefers them itself. A pseudo prefers the hard register of a copy's other side, and the
  register of the first operand of an arithmetic set whose other side is a hard register or
  a pseudo local-alloc already placed (set_preference); expand_preferences then pools the
  preferences of the destination and every allocno that dies in the set, if they do not
  conflict. `-dg` prints each allocno's conflicts and (pruned) preferences in the `.greg`
  dump, after the allocation order (`;; N regs to allocate:`), whose ranking is
  floor_log2(refs) * refs / live length.
- func_00149760's zoom clamp: the 0.0 bound (r399, 3 refs over 10 insns) ranks above the
  RangeFraction result (r386, 3 over 12), which conflicts with it and has $f1 among its full
  preferences, pooled from the zoom (`sub.s $f1, zoom, g18` later) through the clamp's
  variable. So the bound skips $f0 and $f1 and takes $f4; retail's $f1 needs r386 allocated
  first. The clamp written out, the fraction named and LimitFloat (another control flow) do not
  change it.

### A variable reused by a second loop: its conflicts prune a preference (func_001BBC38)

- prune_preferences drops from a pseudo's preferences every hard register it conflicts with.
  A user variable assigned in two loops (`tri = &tris[f]` in the edges' loop and again in the
  faces' loop) is one pseudo whose conflicts are the union of both lives: the faces' loop's
  local-alloc temporaries in $a0 make $a0 a hard conflict, so the edges' `tri = tris + f*12`
  (whose first operand, the `lw a0,8(s1)` load, is local-alloc's $a0) no longer prefers $a0.
  The search index `m`, ranked above `tri`, then finds $a0 outside `regs_someone_prefers` and
  takes it in find_reg's first pass; with a pointer per loop, `tri` keeps the preference, `m`
  skips $a0 and the whole edge loop's registers rotate (m $a1, bound $a3, count $t0, tri $a0).
- A value that local-alloc would place, set once and dying in its block (`s32 f =
  e->faces[j]`, used by `f * 12` and `f * 4`), ties to the shift that ends it (combine_regs:
  `sll v0,v0,2`) and takes $v0 ahead of the address it is loaded through. Retail's `lh a2` and
  `sll v0,a2,2` (not tied) mean a global pseudo: the face index declared once and reused as
  the faces' loop counter (`for (f = 0; f < faceCount; f++)`) is set three times, so
  local-alloc skips it; global-alloc's first pass then excludes $v0 (the counts pointer, a
  call's result, prefers it), $v1, $a0 and $a1 (the product, the triangles' base, `k`) and
  gives $a2.
- Spotting it: a pointer or an index that holds the same register in two consecutive loops of
  retail (here $t0 for the triangle in both, $a2 for the face index and its loop counter) is
  one variable. Retail's base-first address sums (`addu v0,t0,v0` for `tri->i[counts[f]]`,
  `addu a1,a1,a0` with the faces' base in $a1) came from the triangle as a struct with an
  array member (`MeshMotion::Tri`, whose `i[3]` gives get_inner_reference's base-first sum)
  and from a pointer initialised with the face (`MeshFace* face = &faces[f]`), see "The
  operand order of an address sum".

### An expression split into two statements adds references (func_001F7390)

- Sony's library compiler ranks global-alloc's pseudos the same way: floor_log2(refs) * refs /
  live length. In func_001F7390 (a double's bits to a rounded integer) the mantissa `m` (14
  references over 26 insns, 1.615) ranked behind the exponent `e` (10 over 15, 2.0), so the
  two swapped $a1 and $a2. Retail's `dsrl a1,v0,0xc; or a1,a1,v1` writes the masked mantissa
  back into m's own register: the original wrote `m = (m << 12) >> 12; m |= (u64)1 << 52;` as
  two statements, which makes the intermediate m itself (two more references: 16, so
  floor_log2 rises to 4 and the priority to 2.46). Spot it: a temporary that retail holds in
  a variable's register, next to a register swap that regalloc.py blames on the ranking.

### Statements in field order set the call-crossing ranking (func_00144BE8)

- func_00144BE8 blends five spherical differences (heading, pitch, distance, yaw, tilt) by
  springs whose velocities are five consecutive members (0x2B0..0x2C0). The pitch and distance
  differences cross WrapAngle's call, so global-alloc ranks them by floor_log2(refs) * refs /
  live length: with 5 references each, the one that dies first ranks first and takes the lower
  callee-saved register. Retail's pitch in $f22 and distance in $f23 need pitch's update before
  distance's, and the five divisions by the common scale in the same order make sched1 issue
  them as retail does. Both in field order (divisions and updates heading, pitch, distance,
  yaw, tilt) is EXACT; either alone left 71 to 73 lines different, and a permuted update order
  had stood at 91.1% before. Plausibly the original's: the source walks the members in order.

### A load hoisted over a conditional move takes a register from it (func_001C9DE0)

- sched1 may issue a load with a long chain behind it (`anim->f9C`, then `->pos`, `->vt` and
  the call) before a conditional move that jump.c made (`if (alt) to = alt;`, a `movn`). The
  load's pseudo is then born while the move's source is still live, so the two conflict; the
  load's pseudo, local-alloc's and ranked below the source, pools $v1 and $a0 from the curve
  it feeds (expand_preferences), and those enter the source's `regs_someone_prefers`. Pass 0
  of find_reg skips them and the source takes $a1, where retail has $v1; sched2 then sees an
  output dependence between `li a1, 432` and the source's copy, one dependent more, and fills
  the call's delay slot with another move.
- In func_001C9DE0's marker 0x1AC, `PositionCurve* c = anim->f9C->pos; c->vt->eval(c, ...)`
  gives that order; the curve read inside the call, `anim->f9C->pos->vt->eval(anim->f9C->pos,
  ...)` (a virtual call on the curve, as the original's C++ would read it), leaves the load
  after the move: no conflict, $v1, and retail's delay slots.
- The rest of the same function, matched 2026-11-09: global-alloc's ranking puts the animation
  (13 refs over 84 insns, 0.464) before the player it is read from (4 over 34, 0.235), and
  pass 0 of find_reg gives it $s0, the first saved register already in use. No naming of the
  player or the animation changes those counts (cse folds them), but nothing needs to: the
  animation also loses $s0 if $s0 is a *hard* conflict when it is placed. The chosen end marker
  as a variable of its own, `AnimEvent* end = alt != 0 ? alt : to;` (jump.c still makes the
  `movn`), is live only in the block of the two curve calls, crosses them, and so is
  local-alloc's: it takes $s0 there, before global-alloc runs. The animation, live in that
  block, then has $s0 in its hard-register conflicts and takes $s3; the player (not live there)
  takes the free $s0; `to`, now 3 refs over 10 insns, ends in the copy `end = to`, ties to $s0
  by its copy preference, and reload deletes the copy as `move s0,s0`.
- The lever in general: where retail keeps a long-lived pseudo out of a saved register that
  global-alloc's order would give it, look for a block-local variable crossing a call in that
  pseudo's life (a value picked between two others, a result named once): local-alloc places
  it first, in $s0 upward, and global-alloc's pseudos live across it must avoid that register.

### Call sites that cross-jumping merges still rank the allocation (func_001C1F20)

- global-alloc ranks its allocnos by floor_log2(refs) * refs / live length (allocno_compare,
  ties by pseudo number), with flow's references and sched1's live lengths (update_reg_usage
  overwrites flow's). Two values used together at every call site rank by where they are born
  and die: the object and the function pointer of `fn(p, x)` both gain one reference per call,
  but the pointer is live over the call's argument moves and the call itself, the object only
  until its move into $a0 (two insns where sched1 puts the $a1 load first). So each extra call
  site lengthens the pointer's life more than the object's.
- Cross-jumping runs only after reload (jump2), so identical call sites written in separate
  cases are separate code for flow, sched1 and global-alloc, and one call in the output.
  func_001C1F20 (WritePropertyValue) with cases 0, 2, 4, 9, 10 and 11 sharing one call (case
  labels inside the default's `if`): 6 refs each, object 78 insns, setter 75, the setter ranks
  first (0.160 against 0.154) and takes $s3, retail's $s4. With one call per case, as its
  counterpart ReadPropertyValue writes one call per kind: 12 refs each, setter 93, object 90,
  the object first (0.400 against 0.387): retail's registers, and jump2 merges the six calls
  into retail's one. An empty `do { } while (0)` matched too, by raising the loop depth that
  flow weights references with; it is a barrier and not used.
- The same holds for any repeated statement, not only calls, and it is how a whole set of
  registers swaps where the code is the same (PAL func_eu_001AB370, an escape-code string
  rewriter). With one escape call shared by the two font arms (`code = D[3]` or `D[4]`, then
  one `FormatToString(cur, fmt, code, *s)`) and one `*cur++ = c` for both of the slash test's
  failures (`c == '/' && digit(s[1])`), the three hoisted format %hi's are ranked by life
  alone (3 refs each, lives doubled by their REG_EQUAL notes: 174, 170, 168) and the string
  pointer s (44 refs, 93 insns, 2.37) outranks the buffer pointer cur (35, 91, 1.92). With a
  `FormatToString` call in each font arm, the first format's %hi has 4 refs (8/174, first:
  retail's $s5) and cur gains 6 refs (41 against 46); with `*cur++ = c` in both the inner
  `else` and the outer one (`if (c == '/') { if (digit(s[1])) ... else *cur++ = c; } else
  *cur++ = c;`), cur gains 3 more and outranks s: every register of retail. jump2 merges both
  pairs into retail's one copy (the escape tail is reached by `b` with `D[3]`'s load in its
  delay slot; the two failures branch to one `sb` by likely branches).
- Spot it: a value's priority short by about a sixth with nothing in the code to add
  references, and a branch to a shared tail (`b L; <delay>`) or two branches to one store.
  Write the tail in each arm before trying loop structures.

### A merged arm keeps its place: B0, the arm, the join (func_001EC7A8, unsolved)

- jump2's cross-jumping runs after sched2 (the .sched2 dump still has the branch and both
  arms), so where two identical arms merge, the final order is B0's schedule, the surviving
  arm's insns, then the join block's schedule, each scheduled apart. A dead compare constant
  (`li v0,1`) that sched2 placed among B0's prologue moves marks B0's end: whatever the arm
  held sits right after it.
- Arms that survive the passes before reload must be stores or loads: register and float
  copies in both arms are removed by jump.c's first pass or CSE (the branch is gone before
  flow), an arm reading `a[dir]` is folded by CSE in the `dir == 1` arm (record_jump_equiv;
  `dir != 1` is folded the same way in the other arm), and an arm ending in a call does not
  merge: the fall-through arm's call gets flow's `(use (const_int 0))`, the other ends in its
  jump.
- func_001EC7A8: `if (dir == 1)` straight after the read of dir, `self->fC40 = dir;` in each
  arm, gives every one of retail's registers (local-alloc and global-alloc see retail's
  blocks), but retail has no insn between the lw of dir and the join's first: its arm emitted
  nothing. A search over the arm's position and contents (3960 compiles) found none closer
  than 14 lines. What survives the early jump passes and emits nothing is still open.

### A named float argument lengthens a long life by one insn (func_eu_001AB2B0)

- global-alloc ranks by REG_LIVE_LENGTH as sched1 recomputes it, so an insn that exists in
  sched1's blocks and disappears later still counts. `PushFontScale(font, self->scale,
  self->scale)` is one load into $f12 and a copy to $f13; `f32 scale = self->scale;
  PushFontScale(font, scale, scale)` is a load into a pseudo and two copies (one becomes a
  no-op move after allocation and is deleted), one more insn inside every life around it.
- func_eu_001AB2B0's self (12 refs) and string (4 refs over 7 insns, 2*4/7 = 1.143) are both
  call-crossing: with the double read self's life is 31 (3*12/31 = 1.161) and self takes $s1;
  with the named scale it is 32 (1.125), the string goes first and takes $s1, self $s2, as in
  retail. The near miss had found the registers only with the else branch's store after the
  call (which lengthened self's life but put the store after the jal).
- The same named scale is how func_eu_001AB558 reads it (`f32 v = self->f51C;`).
- func_eu_001AB370 (s and cur swapped, $s1/$s0) was not a life of one insn: s ranked first
  (weighted refs 44 against 35 over nearly equal lives), and no loop structure of the same
  statements flips that. The statements were not the same: retail wrote repeated arms that
  cross-jumping merged after reload (see "Call sites that cross-jumping merges still rank the
  allocation").

### A literal initial value doubles a variable's life in the ranking (func_001BB290)

- update_equiv_regs (local-alloc.c) doubles REG_LIVE_LENGTH of a pseudo at each set that
  carries a REG_EQUAL note of an invariant, even when the pseudo is set more than once: the
  test lets a second set through as long as its note is a constant, and the first set has
  no earlier replacement to disagree with. A float initialised from a literal the compiler
  puts in its constant pool (`f32 best = 3.4028235e38f`, FLT_MAX: lwc1 from `$LC0`) gets the
  REG_EQUAL note and so a doubled life; the same value read from a named `const` global does
  not. global-alloc's priority (floor_log2(refs) * refs / life) of the running minimum is
  then halved. loop.c's hoisted float constants (lui/ori/mtc1) are doubled the same way.
- func_001BB290 (FindColliderFloorContact) keeps the smallest +0x18 value in a float over
  two nested loops, with 0.7 and -0.7 hoisted out of the inner one. Retail's order is -0.7,
  best, 0.7 ($f1, $f2, $f3). With the FLT_MAX `extern const` global, best ranked first (14/42
  = 0.333 against 10/62 and 10/64). The literal doubles best's life (14/84 = 0.167), still
  above -0.7 (0.161). The window is narrow: with sched1 lives b (best) and m (-0.7, the
  constant set second, one insn shorter than 0.7), it needs m < b/1.4 <= m + 1. Writing the
  inner loop as a `for` with the step `it = next` in its header, the floor test as one `?:`
  condition and `continue` for each rejection, leaves one copy of the step in the RTL
  instead of four (reorg copies it back into the delay slots, so the output is the same)
  and shortens the inner loop by 5 insns: best 37 (74 doubled, 0.189), -0.7 26 (0.192),
  0.7 27 (0.185), retail's registers. Two separate `if`s in that form are cross-jumped into
  a shared `bc1f` that retail does not have; the `?:` keeps retail's branch shape.
- So a running minimum or maximum that starts at FLT_MAX was written with the literal (or a
  macro of it) where its register points that way; a `const` global is a separate symbol.

### A constant's REG_EQUIV doubles a life for global-alloc (func_0012F210)

- update_equiv_regs (local-alloc.c, run before local-alloc and global-alloc) walks the sets
  in insn order. A pseudo set more than once still passes when the set's REG_EQUAL note is a
  constant and no other constant was recorded for it yet: the note becomes REG_EQUIV and the
  pseudo's REG_LIVE_LENGTH is doubled. A later set to a different constant (no_equiv) drops
  the equivalence but never halves the life back. So a variable set to 0.2 in one arm and to
  -0.2 in the other ranks in global-alloc with twice sched1's live length: the `.sched` dump's
  "life shortened from 58 to 57" is the `.lreg` dump's "across 114 insns".
- The doubling magnifies one insn of sched1's order into two. func_0012F210's bracketing step
  (5 refs, sched1 life 57, 114 doubled: 0.0877) ranked just ahead of the upper end's dot (7
  refs over 161: 0.0870), so the two took $f25 and $f26 the other way round from retail. The
  step's set is a li.s (the memory unit, cost 2) after the arm's two vector stores, which
  rank first for their deaths (INSN_REG_WEIGHT -1), so it always issues third; one alu insn
  more in the arm, issued after it, gives it 58, 116, 0.0862. Retail's `behind = 0` was in
  the arm, mirroring the other arm's `behind = 1` (written once before the `if`, sched1 put
  it into the block before; dbr fills the branch's delay slot with it either way).
- Diagnosing it: when tools/regalloc.py reports an `.lreg` live length about twice the
  `.sched` dump's "life shortened/extended" line for that pseudo, the pseudo had a constant
  REG_EQUIV at some point, and every insn of its sched1 life counts twice.

### The leading equal constants double again: a switch's default first (func_0017C428)

- update_equiv_regs doubles REG_LIVE_LENGTH once for every set, in insn order, whose
  REG_EQUAL constant equals the first one recorded, until a set without a note or with
  another constant calls no_equiv (which never halves it back). Two leading `x = 1` sets
  give four times sched1's life, three give eight. A switch's case bodies are in source
  order, so the order of its cases decides which constant sets come first.
- func_0017C428 (CheckQueueEntryDone) sets its result in every case (17 sets, 19 refs,
  sched1 life 68). With `default: done = 1;` last, the first set in insn order is case 4's
  `done = 1` and the second its `done = 0`: one doubling, 4*19/136 = 0.559, above the entry
  pointer's 2*5/24 = 0.417, so the result took s2 and the entry s3, retail's the other way
  round. With the default written first, its `done = 1` and case 4's come first: 272 insns,
  0.279, and the entry takes s2. The default's body is not where it was written: jump2
  cross-jumps it into the `done = 1` that ends case 12 and falls into the return (the
  jump table's entries 10, 11 and the range check then reach the end of the function, as
  in retail), so the layout gives no sign of it. Explicit `case 10: case 11:` bodies
  instead make GCC set `done = 1` before the switch.
- Case 12's shape follows from the same cross-jumping: `if (a) done = 0; else if (b)
  { call; done = 1; } else done = 1;` keeps `done = 0` in its arm (jump.c's "`if (...)
  { x = a; goto l; } x = b;` to `x = a; if (...) goto l; x = b;`" no longer applies,
  because the arm is not followed by a set of done), so jump2 merges it with the float
  cases' shared `done = 0; goto` tail. That label between the `bc1t` and `done = 0` stops
  reorg's optimize_skip (which turns "branch over one insn followed by a jump to the same
  label" into an inverted, annulled branch-likely): retail's `bc1t` takes the return's
  `move v0` from its target instead. relax_delay_slots then sends the branches whose
  target `done = 1` is already done in a delay slot past it (redundant_insn).
- Diagnosing it: two variables whose registers are swapped where the .lreg life of one is
  2^k times its .sched life; count the leading equal constants in insn order (`grep` the
  `.lreg` dump for the pseudo's sets) and reorder the cases or arms that set them.

### Two hoisted constants one insn apart: a store written after the join (PAL's func_eu_0015DF58)

- loop.c hoists every constant of a long loop (`li` of a compare's operand, of a stored
  value) into the preheader in the order its first set appears in the loop, and gives each a
  REG_EQUAL note, so update_equiv_regs doubles both lives. Two such constants with the same
  references live over the same loop, and the one hoisted first is live one insn longer
  (two after doubling): at equal references the later one outranks it in global-alloc and
  takes the lower callee-saved register. Their order in the preheader is fixed by the
  layout, so it cannot be changed to reverse the ranking; only the references can.
- PAL's text reader (func_eu_0015DF58, `~`, `&`, `^` markup) hoists `'.'` (3 compares) and
  1 (3 stores of a flag at +0xA0): 7 references each (the set at depth 1, uses weighted 2),
  lives 448 and 446, priorities 312 and 313, so 1 took s5 and `'.'` s6, retail's the other way
  round. In the `&` case the original stored the flag once after the found/not-found if/else
  instead of in each arm: 1 then has 5 references (2 * 5 / 444 = 0.0225 against 0.0313) and
  `'.'` takes s5. The output is the same either way: the not-found arm falls into the store
  and the case's `break`, reorg puts the store in the `b`'s delay slot, and the found arm's
  jump to it takes a copy into its own delay slot and is redirected past it.
- Spot it: two loop-wide constants swapped, their `.lreg` lives differing by 2 with equal
  references; look for a store or a use of the later-ranked constant that every arm of an
  if/else repeats and that could be written once after it.

### Local allocation's ranking (func_00149760)

- block_alloc (local-alloc.c) numbers the block's insns after sched1 (notes not counted),
  gives each local pseudo a quantity born at 2n where it is set and dying at 2n where a
  REG_DEAD note names it, and ties an asm's output to the first input operand that dies there
  (the quantity then holds both, with both's references). Quantities are allocated in the
  order floor_log2(refs) * refs / (death - birth), ties by creation order; each takes the
  lowest VU register free over its life widened by one insn at each end (the widened range is
  also what it marks taken), else over its real life. The references are recounted on the
  RTL just before local-alloc (recompute_reg_usage: every mention in a pattern, a set
  included), not flow's numbers, which the `.flow` dump shows larger.
- An emulation of this on the `.lreg` dump (build/swarm/mech-149760/lalloc.py in the
  mech-149760 worktree, not committed) reproduces every VU register of func_00149760's case 4.
  Retail's registers for its first rotation product follow from the same insns, in our
  order, if each product row's quantity has one reference more (9: 3 * 9 / 38 outranks mz's
  third row's 2 * 4 / 12); no sched1 order of the block's loads, rotations and stores gives
  them with our counts (100,000 random orders that keep the dependences). Every source form
  tried (b's rows first, Vec rows and results, struct copies of the rows, rows read per
  rotation, the product returned by value) recounts the same six references.

### MulAddX lists its weight before b (func_00187260)

Read from local-alloc.c (block_alloc, combine_regs) and the `.lreg`/`.greg` dumps of
CollectMeshHits (2026-11-10):

- **What differed.** Three MulAddX sums whose a (the centre) lives on or comes from an earlier
  block and whose b (a face's normal) is loaded for the sum: retail gives the result the
  weight's register (`qmtc2 a0,$vf1; ...; vmaddx.xyzw $vf1, $vf2, $vf1x`), where ours took
  b's, and the weight and the centre then moved up a register (the centre in vf4 for vf3).
- **The mechanism.** block_alloc tries the asm's input operands in order and ties the output
  to the first that is local to the block and dies there (combine_regs). With the inputs
  listed a, b, s, b wins whenever a does not die; listed a, s, b, the weight wins, which is
  every one of retail's sums here. Where a dies in the block (the second of two sums from one
  centre load) a still wins, as before. A sum whose result is a global pseudo (used in the next
  block) is never tied (reg_qty of the output is -1) and takes global-alloc's register.
- **The change.** Vu0::MulAddX now lists its inputs a, s, b (the text the same, `%3` and
  `%2` swapped). A clean build with the new order prints MATCH with all 4341 functions from C;
  of the near misses only CollectMeshHits (47.1% to 48.4% alone) and func_0017BCD0 (one byte)
  move, both closer. The order a, b, s had never been tested against a sum where a lives on.
- **Spot it:** a MulAddX whose result takes b's register where retail's takes the weight's.

### A Vec named from a Vec result adds a reference to the ranking (func_0016C528)

- `Vu0::Vec len = Vu0::Length(Vu0::Vec::Of(v));` copies Vec::Length's result into `len` (a movti
  from the inline's return value), and the copy ties the dot's and the root's pseudos into one
  quantity with both's references. In ApplyLinkConstraint's NormalizeVector that quantity had 4
  references over 8 insns (priority 1.0) and was placed before the dv/rest quantity (9 over 38:
  0.71), so it took vf2 and dv, a rotation row and t took the registers the other way round.
  With `u128 len = Vu0::Length(Vu0::Q(v));` the root (used again in the divide's block) is
  global-alloc's, the dot alone ranks 0.5 after dv/rest, and the block takes retail's registers.
  An emulation of block_alloc on the `.lreg` dump (build/swarm/w5-16C528/la.py in that worktree,
  not committed) reproduced every VU register of the block before the change was compiled.
- When two VU registers are swapped across a block, look for a Vec value named from another
  inline's Vec result: the copy merges two short lives into one higher-ranked quantity.
- The two fixes are independent and both are needed: the scalar-slot merge (`Vec::ScalarAtValue`
  for the twist rate, "The weight slot is a cast's copy") was made from a copy of the near miss
  that predated this one and put the Vec `len` back, which brought the swap back. With `u128 len`,
  ToFloatMoved for the rest's and the normal's lengths and ScalarAtValue together,
  ApplyLinkConstraint matches (2026-11-09). When merging two workers' fixes of one near miss,
  diff the code, not only the notes.

### A long-lived vector against short products: the conversions and the statement order (func_00187D08)

- IntersectSegmentWithSphere takes three dot products of two differences d and e in its first
  block. Retail has d in vf2 and each product in vf3 (its 1.0 in vf4): local-alloc gave d
  (8 references) its register before the products (2 each). A product that reaches its qmfc2
  with one insn between them in sched1's order has 2 * 4 / 4 = 20000 in the ranking
  (QTY_CMP_PRI, size 4), d has 3 * 8 * 4 / life; d wins only with a life of 48 or less (a
  tie goes to the older quantity, d's), so with one insn more between d's vsub and its last
  use, or a product whose qmfc2 follows it at once (40000), the products take vf2 and d vf3.
  Retail also stores e before d (sched2 keeps sched1's order for the two tied stores, which
  then decides which one reorg puts in the branch's delay slot), so d dies at its store,
  after e's.
- Each conversion moves this. ToFloat (asm qmfc2, reload's mtc1) adds one insn to sched1's
  block and has reload's latency of 2; ToFloatViaBits adds two (both asms, latency 1);
  ToFloatMoved adds one (its asm mtc1, latency 1) but makes the product a GPR pseudo that
  reload copies out of the asm's output register, so the product's 1.0 takes vf3 where it is
  local. Retail's schedule needs a latency of 1 after each of the three conversions (the
  sub.s of `dd - r * r` before the second product's qmfc2, `2 * bb` before the third's) and
  local products for the second and third: ToFloatMoved for d.d (its product is the only one
  whose register reload may choose: vf3 is free) and ToFloatViaBits for the other two.
- That alone lengthens d's life to 52. The statement order fixes it: with the two stores
  right after the differences and e.e taken before e.d, the cross product is the last use of
  both d and e in flow's notes, so its INSN_REG_WEIGHT (two sets, one unused, two deaths) is
  -1, equal to the sub.s's; it wins the tie on INSN_LUID, sched1 issues it before the sub.s,
  and its life spans the sub.s (20000, not 40000). Of 180 orders of the five statements, with
  the stores first, after the products or after the discriminant, only the eight with the stores
  first and e.e before e.d match; the rest are 26 lines off (about 750 variants compiled in
  all, the conversions swept over every product).
- build/swarm/w5-187D08/la.py (g4 worktree, not committed) emulates block_alloc for the VU
  quantities of an `.lreg` dump, asms with several outputs included (all born at 2n, an
  unused output dying at 2n+1); it reproduced the registers of every variant checked.

### A parameter passed on fills sched1's second slot (func_0018AD88)

- **What decided it.** UpdateGaugeAgentGoal opens with `switch (self->f724)` against 4. In its
  first block sched1 (issue rate 2, two ALU units) has three candidates at t=1: self's copy from
  $a0 (priority 4), the constant 4 (priority 2) and, at t=2, the load of f724 (it needs the
  copy). With only self as a parameter, the constant fills the second ALU slot of t=1 and comes
  before the load: the constant's quantity spans 2 insns, the state's 1, local-alloc's ranking
  (2 refs / span) places the state first in $v0 and 4 takes $v1. Retail has them the other way
  round. No form of the switch (a cast, a state local, the default first, an if/else, the
  operands swapped) changes the block: they all expand to the same three insns.
- **The fix was the signature.** The method's slot passes a second argument, and the base
  method it falls back on (UpdateAgentGoal, agent.cpp) reads it in $a1: the original was
  `UpdateGaugeAgentGoal(GaugeAgent* self, s32 flag)` with `UpdateAgentGoal(self, flag)` in the
  default case. The flag's copy from $a1 is then one more candidate at t=1, with the constant's
  priority (2: it is live into the default block, so the jump depends on it) and the earlier
  insn of the two (expanded with the parameters), so it wins the tie and takes the second slot;
  the constant drops to t=2 behind the load (priority 3 against 2), the
  constant spans 1 insn and the state 2: 4 is placed first in $v0 and the state takes $v1.
  The copy itself disappears: global-alloc gives the flag $a1, and reload deletes the move.
- **Rule.** A method that falls back on its base method passes the base method's arguments on;
  check the base's code for a read of $a1 (or later argument registers) the near miss's
  signature does not have. An argument register retail never mentions can still be in the C:
  its copy is a scheduled insn before register allocation.

### A parameter passed to the first call decides which %hi crosses it (func_0019DC98)

- **What differed.** SubmitDeferredRequests opens with a call (UploadLightVolumes), then reads
  D_0026AC10. Retail hoists that read's `lui s0,%hi(D_0026AC10)` above the `jal` and copies it
  to s4 for the final store; the near miss hoisted D_002622A8's %hi instead. The %hi of
  D_0026AC10 (insn 15) is ready at t=1 beside the call: both have priority 10 (both reach the
  load, which depends on the call), both weight 1 (the call's clobber of $ra counts as a set),
  and the call has twenty dependents against three, so the call is scheduled first and the
  %hi's pseudo lives in its block only: local-alloc gives it $v0.
- **The fix was the signature.** The caller (main_loop.cpp) passes the world and the camera,
  and UploadLightVolumes takes the world: `SubmitDeferredRequests(World* world, void* camera)`
  with `UploadLightVolumes(world)`. The parameter's copy from $a0 (priority 12) and the
  argument move (11) come first, the call waits for them, and the %hi is scheduled at t=1:
  its pseudo now crosses the call, global-alloc gives it s0 (the first callee-saved register
  free there), and reload deletes both moves, so retail shows no trace of the argument.
- **Then the store order.** With the %hi in place, sched1's tie on weight (a store that kills
  two pseudos, `D_00262474 = 0x214`, goes before one that kills one) left the %hi of
  D_00604784 the longest life, so local-alloc gave it $t1 where retail has $a2. Clearing the
  four words at D_00604780 in address order and D_00262474 last gives retail's a2, a3, t0, t1
  (found with tools/permute.py over the five statements).
- **Rule.** As for func_0018AD88: an argument register retail never mentions can still be a
  parameter. Check the callers' argument registers (here $a0 and $a1 from main_loop) and
  whether the first callee takes $a0.

### A variable set twice is global-alloc's: a return or argument register at its edge (func_0018AE38)

- **What local-alloc cannot give.** local_alloc takes a pseudo only when REG_BASIC_BLOCK >= 0
  and REG_N_DEATHS == 1 (local-alloc.c, `reg_qty[i] = -2`). Its first try for each quantity
  (with INSN_SCHEDULING and sched2 on) is the life widened by one insn at each end
  (`fake_birth`, `fake_death`), to avoid false dependences for sched2. A value loaded from
  the call's $v0 where $v0 dies (`lw v0,4(v0)`) therefore never gets $v0 from local-alloc:
  $v0 is live in the insn before. Likewise a value that dies in the insn that sets $a0
  (`lw a0,4(a0)` for the next call's argument) never gets $a0. It falls back to the real life
  only when every register is busy over the widened one.
- **What global-alloc gives.** global-alloc has no widening: a pseudo born where $v0 dies does
  not conflict with $v0, and it takes the lowest free register in REG_ALLOC_ORDER (v0 first).
  A user variable assigned twice has two deaths, so it is global-alloc's even in one block.
- **func_0018AE38.** UpdateGaugeAgentState's case 12 finds two entries (f610, f614) and reads
  each one's mover and the mover's sequence at 0x10 for FindCyclicRangeIndex. Retail keeps the
  mover in $v0 and the sequence in $a0 (`lw v0,4(v0); ... lw a0,16(v0); ... lw a1,8(a0); jal;
  lw a0,4(a0)`); per-call temporaries or locals, local-alloc's, took $v1 and $a3 (and pushed
  the f7E0 load from $v1 to $a0). One `Mover8B* m` and one `ClipSpan8B* a` assigned for the
  first object and again for the second is EXACT; the mover variable alone reused fixes the
  mover and the f7E0 load but not the sequence (10 lines still differ).
- **Rule.** A value retail holds in $v0 right after a call's `lw v0,N(v0)`, or in an argument
  register it is read from in the same insn that sets it, is a global-alloc pseudo: look for a
  variable the original reused (two lookups of the same kind, one after the other), or one
  live across blocks.

### A load read before a call in its arm: one register for two variables, and reorg's slots (func_00185498)

- **What differed.** func_00185498 sets an aim attachment's key from the owner's distance to the
  target: the far key (`lw s1,72(s0)`), or, after ClearRootTries(owner), the near key. Retail
  keeps the owner and the key in one register (s1) and fills the `bc1f`'s delay slot with the
  call arm's `move a0,s1` (reorg's eager fill from the branch target, the branch then aimed past
  it), and the `jal`'s slot with `lw s1,68(s0)`. Ours (the near key read after the call, the
  owner's variable reused for the key to share s1) left the `bc1f` slot empty: fill_simple_delay_slots,
  which runs before the eager fill, takes the `jal`'s slot from the insns before it, so the
  `move a0,s1` went there and the target thread began with the call.
- **Mechanism.** With the near key read before the call (`key = self->f44; ClearRootTries(owner);`),
  sched1 puts the argument copy first (`$4 = owner`, then `key = [self+0x44]`, one cycle,
  .sched insns 110 then 106), so the owner dies where the key is born: no conflict, and
  global-alloc gives the key the owner's s1. reorg's backward fill of the `jal` then takes the
  load (the insn just before the call), which leaves `move a0,s1` at the target for the
  `bc1f`'s eager fill. A separate key read before the call but in an `o`-reusing form, or a
  key read after the call, conflicts with the owner (a 64-byte frame or v1).
- **Rule.** Where retail's call slot holds a load that sets a callee-saved register the
  argument copy just read, the load was before the call in the source; and an empty
  conditional-branch slot whose target starts with an argument move that retail stole means
  the call's own slot was taken by something else first.

- **A store at a join sinks in sched1 (func_00185538, unsolved).** A store with no dependent in
  its block has priority 1, so sched1 issues it after every load of the block (the memory unit
  takes the loads first); the stored variable then lives into the next computation. Retail's
  store first in such a block means a later load there may alias it, or the store was in each
  arm and cross-jumped after reload (sched2 then keeps it first by the anti-dependence on its
  hard register).

### A reused parameter takes its argument register's preference (func_00127B20)

- **What differed.** func_00127B20 walks from `self` up to `top`, keeping
  each object in `chain[]`, then back down. A new local for the walk down (`PlacedObject* o =
  chain[i]`) was global-alloc's (it lives across the loop body's `if` blocks) and took $v0,
  the first free register of REG_ALLOC_ORDER: its last use, `q = &o->rot` (insn `r269 =
  r171 + 0xd0`), is where q is born, so the two do not conflict and q's local $v0 is free
  over o's whole life. Retail keeps the object in $a0, with q in $v0.
- **Why $a0.** sched1's order was retail's (the addiu after the row 0 load, from the
  priorities: the load heads the chain to the row stores that rows 1 and 2 wait for), so no
  conflict could take $v0 from o. The register is a preference: `self` is copied from $a0 at
  entry, so its pseudo has `;; N preferences: 4`. Writing `self = chain[i];` (the parameter
  reused as the cursor of the second walk, as the first walk already moves it) makes the
  walk down one pseudo with self, which global-alloc gives $a0; its life in the middle loop
  is dead, so no conflict there. 18 lines became 10.
- **The rest: an untied rotation.** Retail's first rotation (`o->pos` through M) loads the
  position into $vf2 and writes $vf4: the result is not tied to v. Vu0::Rotate ties it ("0"),
  so the load went straight into x's pseudo and both took x's $vf4, which moved M's rows
  (retail $vf6, $vf5, $vf3). Vu0::RotateUntied for that rotation only (the two later ones are
  tied in retail: $vf1 in and out, $vf3 in and out) is EXACT.
- **Rule.** An object held in an argument register across blocks, where a fresh local would
  take $v0, is the parameter reused (check the parameter's `preferences` line in `.greg`).

### A reused float variable joins two lives' conflicts and preferences (func_0016E738)

- **Preferences.** set_preference (global.c) gives a global pseudo set by an arithmetic insn
  the hard register of the first operand when local-alloc already placed it: a dot product
  `d = a * b + c * e` whose first product local-alloc put in $f1 prefers $f1.
  expand_preferences then pools that into every allocno set where d dies and that does not
  conflict with it (`rt = d / hi`), so both take $f1 in their turn. find_reg's pass 0 only
  removes from `regs_someone_prefers` what lower-priority conflicting allocnos prefer and the
  allocno does not.
- **A second life.** A user variable assigned again later in the function is one pseudo with
  both lives: the second life's hard-register conflicts (a sum dying into an asm's input,
  locals of another block) and its own preferences join the first's. func_0016E738
  (ReadAnalogStick) projects the stick on four axes and divides each projection by the axis's
  widest reach (`d`, the fraction `rt`), then clamps the best fraction and divides by the
  stick's length (`Fpu::Sqrt`). With a variable per value, d and rt took $f1 by preference
  and best, the hoisted 0.0 and the two squares followed at $f2, $f4, $f6, $f7 (retail: d $f4,
  rt $f2, best $f6, 0.0 $f7, squares $f8, $f9). One `len` for the projection and later the
  length, and one `frac` for the fraction and later the clamped response, is EXACT: len then
  conflicts with $f1 (the sum of squares dies into the sqrt) and takes the sqrt's $f4; frac
  conflicts with the clamp's $f0, $f1 and $f4 and takes $f2; the rest follow. Either reuse
  alone leaves 10 or 15 lines.
- **Rule.** When a high-priority float in a loop sits in retail's register for a value of
  the same kind later in the function (a length, a fraction), and our copy takes $f1 or $f0
  by preference, look for one variable the original reused for both.
- **A ratio divided into its own divisor (func_00186320).** MeasurePointToSegment tests the
  squared length, then divides the dot product by it and clamps the ratio. With a ratio
  variable of its own (`f32 r = dot / len2`) the ratio is a global pseudo set by a division:
  set_preference gives it the dividend's $f0 (the conversion, placed by local-alloc), and it
  ranks first (5 refs over 8 insns against the 1.0's 3 over 8), so it takes $f0 and the 1.0
  $f1. Retail divides into the length's $f1 and puts the 1.0 in $f0. One variable for the
  length and then the ratio (`r = ToFloat(Dot(e, d)) / r;`) is that: the pseudo is set twice,
  holds the length's $f1 from the head, the 1.0 then takes the lowest free $f0 and the 0.0 $f2.
  Three FPR differences in a cascade of nine lines went with it.

### A value used after a branch is global-alloc's; one used up before it ties to $f0 (func_001733B8)

- **A call's result in $f0.** local-alloc's combine_regs ties a block-local pseudo to the
  hard register an insn's first input dies in, so `len = call() - 30` keeps the call's $f0
  only if len dies in the block. func_001733B8 (the push object's edge force) read `len`
  again in the `else if (len - reach < at)` arm: len was a global pseudo, local-alloc gave
  the block's short temporaries (`len - 30`, the span) $f0, $f1, $f2 first, and those hard
  registers entered len's conflicts, so global-alloc put it in $f4 and the whole tail's
  floats shifted (retail: len $f0, the player's +0x23A4 $f4). Naming the arm's bound before
  the branch, `f32 highEdge = len - reach;`, ends len in the block: len ties to $f0, the bound
  (live into the arm) takes $f0 after it in global-alloc, and reorg fills the branch's delay
  slot with it unannulled (retail's `bc1f` + `sub.s $f0,$f0,$f2` rather than `bc1fl`).
- **One clamp variable for two arms.** The two arms clamp a fraction and square it
  (`-w * w * 150`, `w * w * 150`). With `w` declared in each arm, the second arm's w took
  the fraction's $f0 by preference (no conflict: its 150.0 is loaded after `w * w`), which
  removes a `mov.s` and reshapes the clamp's branches. One `f32 w;` before the if, assigned in
  both arms, is one pseudo carrying the first arm's conflicts ($f0 for `-w`, $f1 for 150.0),
  so it takes $f2 in both, as retail. Same rule as func_0016E738 above: a value of the same
  kind in the same register in two arms is one variable.

### A reused variable is not tied, and a Scalar slot store weighs +1 (func_001B9D10)

Read from local-alloc.c and haifa-sched.c and the `-dS -fsched-verbose-6` dumps of
TurnColliderTowardRotation (2026-11-09):

- **No tie for a variable set twice.** combine_regs ties an insn's output to any operand that
  dies there (block_alloc tries every operand of addsf3, which has no `%`) when that operand
  has a quantity: set once and local to the block. Ours tied `along + step` to the dot's float
  (both $f0), so the rest that followed took the angle's $f2 by set_preference. Retail's dot is
  in $f3, the register the speed `ToFloat(Length(v160))` has at the top of the function: one
  variable, `speed`, reused for the component of the spin along the axis. Set twice, it is a
  global pseudo, the sum is not tied to it, and step ($f4), the dot ($f3) and rest ($f0) follow.
- **A Scalar's slot store weighs +1.** find_pre_sched_live counts a SET for every store and
  takes one off per death; the Scalar's store comes before the asm that uses the weight, so the
  asm is the weight's death and the slot store weighs +1, against 0 for a store whose value
  dies there and for an argument move whose source dies. With the call's two argument moves
  ready from the block's start, sched1 issued them before the slot store and the result's store
  before it too: the weight lived longer than the product, local-alloc ranked the product
  first (vf1, the weight vf2; retail the other way). The store wins only when nothing of weight
  0 is ready in its cycle.
- **The product in each arm.** Retail's tail after the `error < rate * dt` test is one block
  in the final code, but it is jump's cross-jumping of two: `Q(torque) = MulX(diff,
  Scalar(1.0f / dt))` in one arm and `MulX(diff, Scalar(rate / error))` in the other, the call
  after the join. In each arm the division's latency keeps the vmulx late, so the slot store
  issues with it after nothing else is left, and after reload the two identical tails are
  merged (the second arm's division in the branch's delay slot). EXACT.

### A float parameter passed on fills a load's delay (func_00161B10)

- SelectVertexBatchLights opens with `if (*self->fF8 != 0)`: a pointer load, a byte load
  through it, a branch. With `(self, a1)` as its parameters, sched1 issues the copies from $a0
  and $a1 together at t=0 and the two loads back to back: both quantities span 1 insn, equal
  priority, and local-alloc places the pointer first ($v0, the byte $v1). Retail has the
  byte in $v0.
- The callee (CollectLightsForSphere) stores $f12 as the sphere's radius, and this function
  never sets $f12: the original took the radius as a third parameter and passed it on
  (trail_ribbon.cpp's caller already declares `(VertexBatch*, u8*, f32)`). The copy of $f12
  into its pseudo is one more candidate after the copies of $a0 and $a1, and sched1 puts it
  between the two loads (`.lreg`: lw, the SF copy, lbu). The pointer then spans 2 insns,
  priority 2/2 against the byte's 2/1: the byte is placed first in $v0. global-alloc gives the
  radius $f12 and reload deletes the copy, so retail shows no trace of it.
- Same rule as func_0018AD88: an argument register retail never mentions can still be a
  parameter, here a float one, found from the callee's reads ($f12) and the caller's call.

### A Load method's reader, passed on, ranks self below the counter (func_001EBF40)

- LoadTempoAgent (slot 10 of class 0x13) calls LoadAgent and resolves four clip ids into
  fC10 in a loop that loop.c reverses (`li s2,3` ... `bgez s2`). Written as `(TempoAgent*
  self)` it was retail's code with self and the counter in s2 and s3 swapped. global-alloc
  ranked 133 (the out pointer, 14/12), 135 (the id pointer, 14/18), self (5 refs: 2*5/15 =
  0.667) and the counter (7 refs; its `i = 3` carries a REG_EQUAL constant, so
  update_equiv_regs doubles its life 14 to 28: 2*7/28 = 0.5) in that order.
- Load methods take a reader as their second parameter: LoadAgent passes its $a1 on to
  LoadCollider untouched, and LoadCollider reads it. With `(TempoAgent* self, void* reader)`
  passed on to `LoadAgent(self, reader)`, the copy of $a1 into its pseudo and back is one
  more candidate before the call: sched1 now issues the counter's `i = 3` after the call
  (its life 11, doubled 22, crossing one call instead of two) and self spans 16. The counter
  (2*7/22 = 0.636) ranks above self (2*5/16 = 0.625) and takes s2: EXACT. The reader's
  copies vanish in reload, as in
  func_0018AD88 and func_00161B10: check what the callee reads before trusting a
  signature that drops a parameter.

### A time step passed on to a method lengthens two lives equally (func_00143418)

- func_00143418 copies the target's 0x50-byte record (Camera +0x2F0) into `out`, or asks the
  target's slot 0x124 to fill it and adds the offset behind the target. Written with three
  parameters, every instruction matched but the camera and `out` swapped $s1 and $s2: in
  global-alloc's ranking (floor_log2(refs) * refs / live length) the camera scored 2*5/14 =
  0.714 against `out`'s 2*6/17 = 0.706, so the camera took $s1 first.
- The lives were already as short as the final code allows (sched1's counts, block by block),
  and no form of the copy or the branches changes the references. The caller (func_001E2E68)
  sets $f12 = 0.0f before the call, and the other implementers of slot 0x124
  (CapturePlayerPose, CaptureColliderPose) take `(self, record, f32 dt)`: the original took the
  time step as a fourth parameter and passed it on to the slot.
- The copy of $f12 into its pseudo (block 0) and its move back into $f12 before the virtual
  call (block 4) are two more insns while both pointers are live: 16 and 19 insns, 0.625
  against 0.632, so `out` is placed first and takes $s1. global-alloc gives the time step $f12
  and reload deletes both moves. Adding the same length to two lives favours the one with more
  references, so a parameter passed on can reorder global-alloc as well as sched1
  (func_0018AD88, func_00161B10).

### A passed-on argument register is set twice, so adjust_priority leaves it (func_001A0C98)

- **The symptom.** InitCameraSpaceEffect (slot 0 of the kind-16 effect table) keeps the place
  and then the parameter block in one callee-saved register ($s0): the place's last use is the
  `move a1` for ProjectPointToCamera, the block's load (`lw s0, 0x130(s1)`) is issued before the
  jal and reorg puts it in the delay slot. Written with the slot-0 signature cut to (self,
  pos), the load came straight after `move a1` in sched1's order, and local-alloc's widened
  lifetimes (local-alloc.c, block_alloc: with `-fschedule-insns2` each quantity is first tried
  over `fake_birth`/`fake_death`, one insn more at each end, to avoid false dependences for
  sched2) made the place and the block conflict: the place took $s2. Read after the call, the
  two shared $s0 but the `move a1` filled the slot.
- **What decided it.** In the cycle after InitEffect's jal, `addiu a2, s1, 0x120` (the out
  pointer) outranked `move a1, pos` though both had priority 24: $a2 was set once in the whole
  function and never got a REG_DEAD note at the call, so birthing_insn_p held and
  adjust_priority raised it to max_priority (27). $a1 is set twice (InitEffect's argument too)
  and was not raised. The lui and the addiu took cycle 4, `lw a0` and `move a1` cycle 5, and the
  block's load (the memory unit was busy) cycle 6, adjacent to the place's death.
- **The fix was the signature.** InitEffect reads $a2 (stored at +0x24) and $f12 (the scale)
  besides $a1; slot 0's signature is `(Effect* self, void* pos, f32 scale, s32 flags)`
  (effect.h's Vt219C). Declared with it and passing all four on (`InitEffect(self, pos, scale,
  flags)`), the first call sets $a2 too: no longer set once, the addiu is not raised, `move a1`
  wins the tie on register weight (0 against 1) with the lui in cycle 4, the addiu goes with
  `lw a0` in cycle 5 and the load follows in cycle 6, one insn clear of the place's death. Both
  take $s0 and sched2 and reorg give retail's code. The copies for the passed-on registers
  vanish in reload, as in func_0018AD88.
- **Rule.** An argument register set once in a function (typically the last argument of the
  one call that has it) is a birthing insn for sched1 and goes first among equal-priority
  moves. A passed-on parameter that sets it for an earlier call takes that away; read the
  callee for every argument register it uses before trusting a shortened prototype.

### A passed-on float argument orders the prologue's saves (func_0019FD08)

- **The symptom.** InitImpactEffect (slot 0 of the kind-4 effect table) differed from retail
  only in its prologue: retail saves $f20 (`swc1 $f20,32(sp)`) before `move s0,a0`, ours
  after. Both are in cycle 3 of sched2's schedule (the memory unit and an ALU); which comes
  first in the output is the ready list's order (rank_for_schedule), that is their priority.
- **What decided it.** Declared `(Effect* self, f32 limit)` and calling `InitEffect(self)`,
  the save of $f20 had only `$f20=$f12` behind it, and `move s0,a0` outranked it. InitEffect
  (hand-written, func_0019EB28) reads $a1, $f12 and $a2: slot 0's signature is `(Effect*
  self, void* pos, f32 scale, s32 flags)`, as for func_001A0C98. Passing all four on puts a
  `$f12=$f20` copy before the call (the argument restored from the saved parameter), so the
  chain swc1 $f20 -> `$f20=$f12` -> `$f12=$f20` -> call is one insn longer and the save now
  outranks `move s0,a0` (sched2 verbose: ready list at t=3 `67 71 5` before, `73 5 77`
  after, best last). The extra copy is gone from the final code, as in func_0018AD88.
- **Rule.** A prologue save order that differs within one cycle is a priority tie in sched2:
  look for a parameter passed on to a callee (here a float one) that lengthens the chain behind
  the save.

### A constant set in an earlier block and used once (func_001549C8)

- **The widening blocks a register after a load's address dies.** local-alloc's first try
  widens each quantity by one insn at each end and marks the widened range taken. In
  InitSpawnRecord's B block sched1 always issues `li 200` in the cycle of the `lq` of
  g_unitZVector (the lq on the memory unit, priority 4; the constant the best ALU insn,
  priority 3), right after it. The address quantity (v0), widened past the lq, overlaps the
  constant's widened birth, so the constant took a0 and the copy loop's source (global-alloc)
  took v0: retail has them the other way round. No statement order changes the pairing
  (about 2000 orders tried).
- **update_equiv_regs moves the set to the use.** At the start of local_alloc, a pseudo set
  once to a constant (REG_EQUIV), referenced twice (one set, one use) and not local to one
  block has its use replaced by the constant, or, when that is not a valid insn (MIPS `sw`
  takes a register or $0), its set moved to just before the use and made local to that
  block (REG_LIVE_LENGTH 2, no calls crossed). sched1 has already run, so the moved `li` sits
  right before the store, away from the lq: its widened life is free of v0 and it takes v0;
  sched2 then hoists it to just after the lq, which is retail's code. A variable assigned
  200 before the guards (`s32 ringPoints = 200;`, passed to the constructor) gives every
  register of the function; GCSE's constant propagation leaves it alone for the same reason
  (the store cannot take the constant).
- **Rule.** A constant retail loads into the register a load's address has just freed
  (`lq v1,0(v0); ...; li v0,200`) is not local-alloc's: look for a value the original held
  in a variable set in an earlier block (a named default at the top of the function).
- **What remains (store order).** With the constant's store reading that variable, sched1
  issues the dead stores (weight 0: the constant's last use) first and the rest in LUID
  order. Retail's order after the count, f00, f08, f20, f50, f54, f70, f78, has no dead store
  of 1.0 or -1 in it, which no order of the constructor's statements gives (the near miss
  is 2 lines, f00 and f20 swapped).
- **Why no form reaches it.** Each constant is one pseudo (CSE merges repeated literals,
  chained assignments included: `a = b = x` stores b first and x dies at a), so each of 750,
  1.0 and -1 has exactly one dead store, and sched1 issues all six dead stores (those three,
  -1500, q30 and the count) before any live one; sched2 then keeps that order, since every
  store is ready by the time the memory unit frees. Retail's tail would need the 1.0 and -1
  pseudos to die outside the stores (a later use), and the function has no later float
  code. Tried: chained assignments in five groupings (5 to 10 lines), a span setter taking
  two floats (same as literals: integrate substitutes constants), and the floats as named
  locals or constructor arguments (they cross the FillMemory call and take saved FPRs:
  over 100 lines).
- **What retail's order needs (w8, 2026-11-09).** sched1's rank is priority, then
  INSN_REG_WEIGHT, which counts every REG_DEAD and REG_UNUSED note of the insn (a store whose
  value dies weighs -1), then LUID. Retail's stores, f04 f18 q30 i4C | f00 f08 f20 f50 f54
  f70 f78, are the four dead ones and then seven live ones in LUID order, so in sched1's view
  the 1.0 and -1 pseudos are still live after f54: either a scheduling-region boundary
  between f54 and f70 (f70 and f78 then die in the second region, dead first, in LUID order),
  or f70 and f78 waiting on the earlier stores through memory dependences (an output
  dependence costs 1 on MIPS, so a chain gives every earlier store priority 4, f70 3, f78 2:
  exactly retail's order). A probe with a do-while(0) after f54 (a loop-note barrier, never
  landable) gives retail's eleven stores exactly, but the barrier also keeps the copy loop's
  pointer setup (`move a0,sp`, `addiu a1,sp,128`) below it in sched1 and sched2 (42 lines);
  in retail sched2 issues them as ALU fillers before the stores, so whatever separated the
  stores in retail constrained memory insns only, or was gone by sched2.
- **Ruled out (w8).** Dead overwritten stores to carry the deaths (`f04 = 1.0f; ...
  f04 = 750.0f;`): flow1 deletes a store to the frame overwritten in its block before sched1,
  and flow2 never deletes one (flow.c keeps any store whose address mentions the stack
  pointer), so they either vanish too early or stay in the code. A branch around a body that
  life analysis empties (`if (k) k++;` on an unused local) is gone by the first jump pass.
  Static locals (`static B s_b = B(200);`): their guards are g++'s `_$tmp_N` words in .data,
  like retail's two guard words, but g++ constructs the object in place (no stack temporary
  and copy loop: about 145 lines). An inline maker returning the object by value copies it
  twice (147 lines). The memory-dependence form would need f70 and f78 stored through an
  address alias analysis cannot place in the frame while reload still turns it into
  `sp+0x70`; no plain form of that was found.

### A weight's store inside a short life (func_0013F290)

- Three products of one weight, `up * 100`, `pos + side * 100`, `pos + last * 100`, are one
  qmtc2 (CSE folds the Scalars' identical asm) but each Scalar keeps its own store to the
  helper's slot. With the weight named once (`u128 s = Scalar(100.0f)` for the first two),
  sched1 has nothing to issue between the up vector's load, its vmulx and the store to v850:
  the chain's quantity lives 4 (2 * 4 refs * 2 / 4 = 4) and outranks the side chain
  (load, vmaddx, the difference: 9 refs over 18, 3), so the up chain takes vf1 and the side
  chain vf2, retail's swapped. Written `Scalar(100.0f)` in each expression, the second slot
  store is ready after the up vector's load (the load reads memory the first store wrote,
  the second store waits for it) and sched1 issues it between the load and the store to v850:
  the up chain lives 6 (2.67), the side chain is allocated first and takes vf1, and the up
  chain, overlapping it by the widened insn, takes vf2, as retail's. The emulation of
  block_alloc (build/swarm/mech-149760/lalloc.py, mech-149760 worktree) on both `.lreg` dumps
  gives both allocations. The final code has retail's two slot stores either way.

### Two or three quantities: the small sort (func_001EDA80)

- block_alloc sorts its quantities with qsort only when the block has four or more. For two
  or three it exchanges in place (`case 3: if (qty_compare (0, 1) > 0) EXCHANGE (0, 1); if
  (qty_compare (1, 2) > 0) EXCHANGE (2, 1);` falling into `case 2: if (qty_compare (0, 1) >
  0) EXCHANGE (0, 1);`), and qty_compare is called on the fixed quantity numbers 0, 1 and 2,
  not on the entries of qty_order it has just exchanged. With three quantities the first and
  last steps compare the same pair and undo each other: the order comes out as the creation
  order unless the third quantity strictly outranks the second, and then it is third,
  second, first.
- An asm's outputs are numbered last first (the probes show it: Dot's 1.0, its second
  output, is quantity 0 and the product quantity 1). Dot's 1.0 is set and never read, so
  its rank is 0. A Dot whose product goes on to ToBits or ToFloat in a block of its own
  (the product, the 1.0 and the GPR the qmfc2 writes: three quantities) therefore gives the
  1.0 the first free VU register and the product the next (vf2 and vf1 swapped against a
  block with more pseudos, where qsort ranks the product first). Two quantities sort
  correctly (the product first); so do four or more.
- StoreX's product is used as "r", so regclass gives it TI_REGS (the GPRs and the VU
  registers cost the same) and local-alloc puts it in a GPR: the 1.0 takes vf1 and the
  asm's output reload the next free VU register.
- func_001EDA80's last block (the normalised normal moved to n, the Dot of n and u, the
  qmfc2 and sw of the distance, the sqc2 of the normal) has retail's product in vf1 and its
  1.0 in vf2. That needs the product ranked first in a VU class: two quantities with the
  product VU_REGS, four or more quantities, or a third that strictly outranks the product.
  Probes confirm each: ToFloatNow (four quantities) gives retail's vf1 and vf2 but an mtc1
  and swc1; a qmfc2 to a u128 in a GPR placed after the normal's store (the product living
  over two insns, rank 2 * 2 / 4, the GPR's 2 * 2 / 2) gives them with the stores swapped.
  The plain forms do not: StoreX (a GPR product), ToBits, ToFloat or a truncating cast
  (three quantities, the GPR's rank 1 at best against the product's 2, or a tie when the
  normal's store comes between), a Vec product or operand, a new variable for the unit
  normal. What retail's block had that ours lacks is open.
- Probes of 2026-11-09 confirm the sort is the whole difference and narrow what is left:
  - With the last Dot's asm listing its 1.0 first (`"=j"(one), "=j"(r)`), so that the product
    is quantity 0, ToBits gives EXACT. Changing Dot so for every user does not: this
    function's earlier Dots move, and a function of path_curve.cpp changes size. Retail's Dot
    is the project's; the last block is what differs.
  - A Dot and qmfc2 in one sequence (`DotBits`) matches here only with the 1.0 listed before
    the product, and the matched ToBits(Dot) users (func_00148938, CopyMeshTransformed) only
    with the product first (func_001BBEB8 with neither): not one recurring sequence.
  - The three-quantity arithmetic: the ranks are floor_log2(refs) * refs * size / life, with
    TImode two words and SImode one, births and deaths at 2 * insn. ToBits' GPR (2 refs,
    size 1) outranks the product (2 refs, size 2) only if the product lives more than twice
    as long: two insns between the Dot and the qmfc2. The only candidate, the normal's sqc2,
    cannot come before the sw: both stores go through parameters, which may alias each other
    (no -fargument-noalias), so sched1 and sched2 keep their source order, and retail's sw
    comes first.
  - ToFloat's float prefers FP_REGS (an mtc1 and swc1, 396 bytes). Copies of the normalised
    vector fold in CSE: `n.q = NormalizeOr(..).q`, a Vec m then `n = m`, a named fallback, the
    u128 NormalizeOr, Vu0::Copy (its vmove writes n). None adds a quantity to the block.
  - Still to find: a block-local quantity born before the Dot (by the sort, a TImode copy of
    the unit normal dying at the vmove would rank first, leave vf1 to the reload of StoreX's
    product and push the 1.0 to vf2 through local-alloc's widened lifetimes), or a product
    whose preferred class is VU_REGS (two quantities, the qmfc2 a reload).
- **Two quantities from a variable set twice (func_0017ECE8, 2026-11-10).** Where retail has
  two blocks of the same shape (here the Gram loop's and the right-hand sides' `Dot` and
  `qmfc2; sw`), one `u32 bits;` declared at the top and assigned in both
  (`bits = Vu0::ToBits(Vu0::Dot(na, nb).q); *(u32*)p++ = bits;`) has REG_N_SETS 2, so
  local-alloc leaves it to global-alloc (`reg_qty = -2`) and the inline's own result folds
  into it: the Dot's block has two quantities, the product and the 1.0, which sort product
  first (retail's vf1 and vf2). The GPR is then global-alloc's lowest free, v0, as retail's.
  A Vec for the product shared the same way does the opposite (the product leaves the block
  and the 1.0, alone, takes vf1). Worth trying in func_001EDA80 where a second Dot of the
  same shape exists.

### Loops over one list: one variable for every loop (func_0017ECE8)

- Retail's four walks of the contact rows (a count, the Gram matrix, the right-hand sides,
  the weighted sum) keep the row in a2 and the contact in a0 in every one, with the
  count loop's `move a2,v0` from row->next: one `ContactRow03* row; Contact03* c;` declared at
  the top and reused by each loop (one pseudo each, which global-alloc places once over all
  the loops), as camera.cpp's sibling func_00145B68 reuses `i` and `j`. A variable per loop
  gave other caller-saved registers in each (t0, a1, v1). The Gram loop's inner pair (the
  second row and contact) stays its own.
- The first normal of the Gram loop is copied (vmove vf3, vf4) after the inner loop's entry
  test: loop.c hoisted it out of the inner loop body. Written with Vu0::Vec values
  (`Vu0::Dot(na, nb)` taking na by value), the copy is the parameter's movti, which loop.c
  moves to the inner loop's preheader; a u128 `ac = na` before the inner loop puts it before
  the entry test instead, and plain u128 operands give no copy at all.
- Still open there: retail's reload of the spilled `down` vector for `acc = down` (after
  SolveActiveSetSystem) is in v1. order_regs_for_reload (reload1.c) skips a hard register that
  holds a pseudo live before or after the insn, so retail had a value in v0 across the copy:
  the sum loop's `self->contacts` load, scheduled first by sched1. Ours ties both at priority 5
  (the copy's unflagged TImode frame store is a true dependence of the `row->head` load
  through the loaded pointer) and INSN_REG_WEIGHT puts the copy first (-1, down dying,
  against the load's +1). Confirmed by a probe: acc as a u128 whose address the z read
  takes makes the copy's store MEM_SCALAR_P at a fixed address, which
  fixed_scalar_and_varying_struct_p keeps apart from the mem/s load; sched1 then issues the
  load first and reload takes v1, as retail. But purge_addressof allocates such a variable's
  slot after the expand-time weight slot (retail has the sum at 0, the slot at 0x10), so the
  form that has both is still to find.

- Probes of 2026-11-10 (after func_0017ECE8's variable set twice): taking the qmfc2's result
  out of local-alloc does give retail's VU order here. With `len2` reused for the distance
  (`len2 = Vu0::ToFloat(Vu0::Dot(n.q, u)); *dist = len2;`), len2 is set twice, global-alloc
  takes it and the inline's result folds into it, the last block has two quantities and the
  product gets vf1 and the 1.0 vf2, as retail's. But an f32 set twice is "pref FP_REGS, else
  GR_REGS" in the .lreg dump whatever its other uses, so the distance goes through an FPR
  (mtc1, swc1: 396 bytes). Every f32 the function has fails the same way: len2 (its compare
  and divides), a `dot` shared with the else arm's sign test, and the zero arm's `z` (only
  stored, but its 0.0f set gives FP_REGS too; retail's zero arm is an FPR anyway, mtc1 zero
  and two swc1, so z was never a GPR). A u32 set twice would give GR_REGS, but the function
  has no second bits value to share it with: the only one would be the squared length's
  (`u32 bits = ToBits(..); f32 len2 = ToFloatMoved(bits)`), whose u32 to u128 widening costs
  a dsll32, dsrl32 and por (404 bytes), and which is no plausible source. A u128 product
  shared between Dots (`p = Dot(n.q, n.q); .. p = Dot(n.q, u); StoreX(*dist, p)`) moves the
  product out of the block instead and swaps vf1 and vf2 in both Dots. Still open: a GR_REGS
  pseudo the original set twice, or a quantity born in the last block before the Dot.

### A 64-bit field's bits as an int: one truncate (func_00210970)

- **What decided it.** func_00210970 (Sony's 2.9-ee-991111) indexes a table by bits 5 to 8 of a
  u64 field. Written as `(s32)(((s64)p->f20 << 27) >> 32) & 0xF` (the shape of retail's
  `dsll 27; dsra32`), the RTL is a DImode shift and a separate truncate of a shift by 32: two
  insns before the `and`. Written as the original plausibly had it, `(u32)(p->f20 >> 5) & 0xF`,
  combine makes one `(truncate:SI (lshiftrt:DI x 5))` insn, which the R5900's truncdi pattern
  emits as the same two instructions (`dsll 27; dsra32`, the sign-extended low word). The
  register difference was this one insn of sched1's chain.
- **How.** With the longer chain, sched1 issued the table address's `addu` in the cycle after the
  load of the next field to be copied (`s->f5C`, ready as soon as the store before it), so that
  load's pseudo lived over 3 insns and the table entry's over 2: local-alloc's ranking
  (2 refs / span) placed the entry first, in $v1, and the field took $a3. One insn shorter, the
  `addu` issues with the field's load and before it in rank order; both pseudos then span 2
  insns, the tie goes to creation order (the field's load is first), the field takes $v1 and
  the entry $a2, the table base's register, free after the `addu`. sched2 then puts the field's
  load back before the `addu`: retail's code. The table load (u32, int alias set) does not
  depend on the u64 store before it, nor the field load on the u64 store, which is why only the
  chain's length moved them.
- **Rule.** Write a 64-bit field's bits read as an int as the shift and cast the source would
  have (`(u32)(x >> n)`), not the shift pair the disassembly shows: the pair is the truncate's
  expansion, and written out it is one insn more before register allocation.

### A conversion's latency in sched2 (func_00126270)

- **ToFloat's mtc1 is reload's, ToFloatMoved's is the asm's.** With ToFloat the qmfc2 is the
  asm (unit none, cost 1) and the mtc1 to the FPR is an insn reload makes (`$f12=$3`, on the
  memory and flop units), whose latency to the next float insn is 2 in the `-dR
  -fsched-verbose-6` dump. With ToFloatMoved the qmfc2 is the compiler's and the mtc1 is the
  asm, cost 1. In func_00126270's view test, `fabs(ToFloat(Dot(n, cam->f80)))` left abs.s
  queued a cycle after the mtc1, so the cubic's first coefficient load (c[3]) took the memory
  unit first, and c[0]'s load fell into the cycle before the first mul.s. With ToFloatMoved
  abs.s issues the cycle after the mtc1, ahead of the c[3] load (priority 29 against 28), the
  multiply is ready a cycle earlier and outranks c[0]'s load: retail's order. The mtc1 also
  holds the memory unit in its cycle, which is what keeps c[0]'s load (ready then) from going
  before the other coefficients. A swap of an FPR op and a load right after a mtc1 is worth
  trying with the other conversion first.

- **Retry the statement orders after the swap (func_00145E68).** The camera's sweep probe
  had been tried in every order of its three vector statements (direction, low corner, high
  corner) while its length still went through ToFloat; none was closer. With ToFloatMoved its
  four remaining lines were the two corners' constants and stores swapped, and the low corner
  written before the high one (the order GatherCollidersInBox takes them) matched: retail's
  code computes the high corner first, sched1 issuing the later-expanded sum first on a tie
  (measured; consistent with rank_for_schedule's last key, INSN_LUID). A conversion's latency
  shifts the whole block's schedule, so orders ruled out before the conversion swap are worth
  trying again after it.

- **Both asms: the value in its VU0 register and the mtc1's latency of 1 (func_001C5C10).**
  The kind-1 contact negates a dot product for the call's $f12 (`d = -d`). Retail sets $f12
  with neg.s before the jal and fills the delay slot with the last argument move (`move t2,
  a2`); ours put neg.s in the slot. reorg's fill_simple_delay_slots takes the first eligible
  insn scanning back from the call (a call's argument registers are not "needed" with
  include_delayed_effects 0, so neg.s qualifies), so the difference is sched2's order. With
  ToFloat the block's chain is fixed: the -1.0 constant (lui/mtc1, 2), its mfc1 (2), the
  qmtc2, vmulx (also waiting on the lqc2's 3), the dot, the qmfc2, reload's mtc1 (latency
  2), then neg.s at cycle 10; the seventeen other insns of the block fill the two issue
  slots of cycles 1 to 9 but one, so the last argument move takes cycle 9 alone, before
  neg.s. ToFloatMoved gives retail's order (its mtc1 is an asm of cost 1, so neg.s issues at
  cycle 9 and outranks the move, priority 5 to 3), but its "r" input makes the dot's result a
  GPR pseudo (TI_REGS: one "=j" def, one "r" use, a tie the class order breaks), so local-alloc
  no longer has it in vf2 while the -1.0 vector is live, and the VU0 registers renumber
  (k vf2 for vf3, the difference vf3 for vf2). Retail had both: the dot's result in a VU0
  register up to an asm qmfc2 into a GPR, and an asm mtc1 of its own. Vu0::ToFloatViaBits is
  that pair (ToBits, then `mtc1` of the u32): the bits through a plain pun
  (`*(f32*)&bits`) give the compiler's mtc1 again (latency 2, the old order), and
  ToFloatMoved of the u32 widens it to TImode first. Swept over the eleven near misses whose
  notes mention mtc1 or neg.s, it closed no other.

- **A call's argument move against the last stores (func_001EC3D8).** DrawTempoAgent fills a
  stack request (group, a float, the object, the callback) and passes `&r` (`move a0,sp`).
  With ToFloat, sched2 had the swc1 queued two cycles behind reload's mtc1, so the free alu
  slot took `move a0,sp` a cycle ahead of it, in every store order. With ToFloatMoved the
  mtc1 is the asm (cost 1): the swc1 and the move are ready in the same cycle, tied on
  priority (3), class and dependents (the call only), and INSN_LUID, sched1's output order,
  decides. sched1 issues the move in the first cycle where the memory unit is taken and the
  alu free; with the float stored before the object (`r.group; r.f04; r.arg; r.callback`)
  the swc1 wins that cycle over the object's store on INSN_LUID, the move follows it, and
  sched2 then keeps swc1 before the move: retail's code. The order is the struct's own
  field order after the group, an ordinary way to fill a record.

### A compiler copy's latency in sched2 (func_0014D3A8)

- **An asm copy and the compiler's copy schedule differently.** func_0014D3A8's tail stores a
  copy of the direction, takes the copy's length and divides the original (`vmove vf1, vf4`,
  the dot, `sqc2 vf1`, the vsqrt). With Vu0::Copy (an asm) sched2 put the store before the
  dot: both were ready the cycle after the vmove, at equal priority (9, both through the vsqrt,
  the store by its anti-dependence on vf1), in class 3 (a link out of an asm costs 1), and the
  store won on dependents (the branch, the vsqrt and the fallback's `lq`, which may alias
  the store; 3 to 2). Read in the arm instead (a `const Vec02&` fallback) the `lq` dependence
  goes and the order is retail's, but the load is then an `lqc2` into the result; read through a
  fixed `u128` it is independent and issues too early for reorg to put it in the delay slot.
- **What retail had: the compiler's vmove.** As Vu0::Vec values (`Vec dir = Sub(...);
  *(Vu0::Vec*)outDir = dir; *(Vu0::Vec*)outDir = Vu0::NormalizeOr(dir, Vec::Of(unitX));`) the
  argument copy is a movti between two live VU0 pseudos, which the allocator keeps as a
  vmove: a recognised insn on the vu0 unit with a latency of 2. The store's data dependence
  on it queues the store for two cycles while the dot (an asm, its link cost free) issues at
  once: retail's order, with no other change. Where retail stores a vmove's copy after an asm
  that reads it, the copy is the compiler's, not Vu0::Copy.
- **The same tail in func_0014D280.** InterpolatePathCurvePoint's tangent is the same
  three statements (`Vec d = Sub(Vec::Of(points[i + 1]), Vec::Of(points[i])); *(Vu0::Vec*)tan
  = d; *(Vu0::Vec*)tan = NormalizeOr(d, Vec::Of(g_unitXVector));`) and matched on the first
  compile; the near miss with Vu0::Copy and a file-local NormalizeOfCopy had stopped at 94.5%
  with exactly the store-before-dot order above.

### Three dots before a test: which conversion keeps the dot in VU0 (func_00141D88)

Read from haifa-sched.c and the `-dS -dl -dg -fsched-verbose-6` dumps, with the local-alloc
emulation of build/swarm/w5-1D2518/lalloc2.py (g11 worktree) (2026-11-09, still a near miss):

- **The loop's copy is the compiler's.** The segment-sphere test's loop stores a copy of the
  direction, takes the copy's length and divides the original, as func_0014D3A8's tail does,
  and Vu0::Copy put the store before the dot the same way: in sched2 the store and the dot tie
  on priority, and the store wins rank_for_schedule's class test (the vmove is the last insn
  scheduled; its link to the dot, an asm, is LINK_COST_FREE, cost 0, class 1, to the store cost
  1, class 3). `Vec d = Sub(...); *(Vu0::Vec*)&out->q[j + 2] = d; ... = NormalizeOr(d,
  Vec::Of(g_unitXVector));` gives the compiler's vmove and retail's loop at once. A fallback
  read as a const object (an RTX_UNCHANGING_P load) also frees the store but is hoisted out
  of the loop by loop.c, where retail loads it in each iteration.
- **A dot read through ToFloatMoved is not a VU0 pseudo.** Its "r" input makes the dot's
  result a TI_REGS pseudo (local-alloc gives it $v0) and reload picks its VU0 register, after
  local-alloc has placed the 1.0 scratches: the near miss's a=vf3, scratch vf4/vf3 against
  retail's a=vf4 and every scratch vf5. With ToFloat, ToFloatNow or ToFloatViaBits the results
  are VU0 pseudos: all three as ToFloat give retail's a=vf4, results vf3, vf4, vf3 and
  scratches vf5 (but not its order); all three as ToFloatViaBits give dot3's scratch vf4.
- **What retail's registers need of sched1.** With all three ToFloatViaBits, sched2 gives
  retail's head order provided dot3's scratch is vf5 (it then no longer anti-depends on dot2's
  qmfc2, which loses the tie with the 4.0 load on dependents). The emulation over orders of
  sched1's block gives vf5 only with dot3 issued before dot2's qmfc2 (dot2's result alive over
  dot3). sched1 cannot: dot2's conversion has priority 15 (qmfc2, mtc1, add, mul, sub, c.lt)
  and dot3 at most 13, and a dot (a PARALLEL of the result and the scratch) is never raised by
  adjust_priority's birthing rule. Statement order changes nothing (24 orders x 64 conversion
  mixes compiled). Open: what in the original made dot3 or its conversion outrank dot2's.
- **What retail's sched2 order needs of the conversions (func_00141F48, 2026-11-10).** The
  sibling's head is the same code. sched2 issues the 4.0 load (priority 15) before dot2's
  conversion only when that conversion ranks below it: one ToFloatNow asm for hb (priority 14;
  its qmfc2 and mtc1 are adjacent in retail too, `qmfc2 v1; mtc1 v1,$f1`), and the first dot's
  mtc1 is an asm (ToFloatViaBits: unit none, so it shares cycle 6 with the 4.0's memory slot).
  ToFloat for hb (compiler mtc1, 16) or for the first dot (compiler mtc1 on the memory unit)
  puts the qmfc2 or dot3 there instead.
- **Why sched1 then puts dot3 late: the doubling's register weight.** With c ToFloatViaBits, hb
  ToFloatNow and ha ToFloatViaBits, the local-alloc emulation gives retail's VU0 registers only
  with dot3 right after hb's conversion and an insn between dot3 and its qmfc2 (a dot followed at
  once by its qmfc2 has a two-slot life and outranks pa in local-alloc). At t=8 twoB's add and
  dot3 tie at priority 13; INSN_REG_WEIGHT is 0 for the add (hb dies in it) and 1 for the dot
  (two SETs, the scratch REG_UNUSED), so the add goes first. Doubling hb in place (`hb += hb;`,
  no death, weight 1) lets LUID put dot3 first and gives every VU0 register of retail, but hb
  and twoB are then one pseudo, and retail's `add.s $f5,$f1,$f1` has two registers (17 lines).
  Still open: a plausible form where hb lives on past the add or the add is not ready at t=8.
  SelfDot for the squared dots, named dots in any order, the 4ac product's other groupings and
  an inline quadratic solver were compiled against all 64 conversion mixes: none is closer.

### A pointer set after a call, and a call in each arm (func_0013FAE8)

ReleaseTriggerZoneContacts (2026-11-10, matched from a 62.5% near miss that had been blamed on
the first loop's registers and the tail's layout):

- **A variable assigned before a call crosses it.** `where = &p;` written before the
  TransformPointBetweenFrames that fills p made `where` a call-crossing pseudo (global-alloc, a
  callee-saved register); written after the call it dies before the next one and takes $a2,
  the argument it is passed in, as retail's `addiu a2,s1,0x140` / `move a2,s0` in the arms show.
  The callee-saved pseudo it no longer needs also changed global-alloc's order for the whole
  function: the first loop's zone and 0x7C0 cursor swapped to retail's $s1 and $s0, a
  difference that had looked like the loop's own.
- **Retail's first arm jumping to the call means a call in each arm.** One call after
  `if (...) plane = &w[0]; else { ...; plane = &w[1]; }` leaves the then arm one insn, which
  jump.c threads (`bc1t` to the call with the argument in the delay slot). A
  `CreatePooledContact(...)` and its store in each arm gives retail's `bc1f` to the second
  test and `b` to the shared call: jump2's cross-jumping merges the identical tails after
  reload.
- **Floats set by ToFloat in both arms and read after the join stay in GPRs.** The asm's "=r"
  output makes ga and gb GPR pseudos; reload's mtc1 at the join is retail's `mtc1 v0,$f1`.
  Only one conversion is the compiler's: the first dot of the first arm through ToFloatMoved,
  whose compiler qmfc2 sched2 issues after the second dot (the asm qmfc2 went before it). The
  near miss's earlier swap had put ToFloatMoved on the second dot.

### A conversion in each branch, before the epilogue (func_0014DA98)

- **sched2 runs before jump2's cross-jumping.** rest_of_compilation (toplev.c) schedules after
  reload and the prologue and epilogue (thread_prologue_and_epilogue_insns), then runs the
  last jump_optimize, the only one with JUMP_CROSS_JUMP, then reorg. Code written once after
  an if/else's join is scheduled with the epilogue's restores; code written in each branch is
  scheduled inside the branch, and only then are identical branch tails merged.
- **An asm mtc1 at the join loses to the restores.** MeasureSplinePathDistance returns a
  squared distance from either branch. Written `r = Dot(...)` in each branch and one
  `return ToFloatMoved(r)` after them, the compiler's qmfc2 and the asm mtc1 sat in the
  join block with `lq ra` and `lq s0`: the asm costs 1 (unit none), so its priority was 4 to
  the loads' 5 (each 2 to the epilogue's blockage, 3), and the mtc1 came after both. Retail
  has qmfc2, mtc1, `lq ra`, `lq s0`. ToFloat there is worse (its asm qmfc2 is never put in a
  branch's delay slot); ToFloat in each branch is merged by cross-jumping before reorg (the
  two asms come from the same header line, so their ASM_OPERANDS are equal), and the
  delay slot gets the dot's last instruction from the assembler. A statement-expression macro
  (an asm on each use's line) avoids the merge but is no plausible form and is not needed.
- **The form: a return in each branch.** `if (self->b != 0) { ...; return
  ToFloatMoved(Dot(d, d)); } ... return ToFloatMoved(Dot(e, e));` puts qmfc2 and mtc1 in each
  branch for sched2, so the join block holds the epilogue alone and the mtc1 stays before the
  restores; jump2 then merges the first branch's qmfc2 and mtc1 into the second's, and reorg
  fills the first branch's `b` with the qmfc2 stolen from the new target (it is the
  compiler's movti, eligible) and retargets the jump to the mtc1: retail's code exactly.
  Written as `if (b == 0) return ...; else return ...;` the compiler places the else branch
  first (31 lines differ); the early return for the anchored case keeps retail's block order.
  Where retail's float conversion comes before the epilogue's restores at a join, look for a
  return in each branch.

- **The compiler's qmfc2 waits for the vu0 unit; the asm's does not (func_0018A160).**
  BuildRotationBetweenVectors reads the cross product's length twice: for the 1e-4 test and,
  after the join, for the sine. Read both times with ToFloat (an asm qmfc2, unit none, cost 1)
  sched2 issued the sine's qmfc2 in the second cycle of the join block, beside the second
  lqc2 of the dot (priority 13, ready at once), where retail has the loop counter's `move
  t0,zero` (priority 1); the 1.0 constant then took a memory slot ahead of the divisions.
  With ToFloatMoved for the sine, the qmfc2 is reload's copy of the length into the asm's "r"
  input: a movti-class insn on the `vu0` unit, which the two lqc2 (`[memory vu0]`) hold for
  the first two cycles, so the free alu slot takes `move t0,zero`, the copy follows the dot,
  and every later insn falls into retail's order. Both reads as ToFloatMoved make the length a
  GPR pseudo instead (two "r" uses against DivX's one "j"), CSE shares its GPR copy and the
  branch arms renumber; the test as ToFloat and the sine as ToFloatMoved keep it in vf4 with
  two separate qmfc2 (v1 in the test, v0 at the join): retail's code. Where retail's qmfc2
  issues after a block's lqc2 although its value was ready, the conversion is ToFloatMoved.

### A scalar local's store and a call's argument registers (func_00188270)

Which register a pointer read for two call arguments takes can be decided by whether a store
before the call is a scalar's (2026-11-08, BuildObjectPairContacts, read from alias.c,
function.c and haifa-sched.c with `-dS -fsched-verbose-6` dumps):

- **The tie.** Retail loads the object into a1 and computes the second argument from it last
  (`lw a1, 0(sp); ... lwc1 $f12, 980(a1); addiu a1, a1, 992` in the jal's slot). local-alloc
  ties a pseudo to the destination of the insn where it dies, a hard register included
  (combine_regs), so the object is a1 only if sched1 puts the field load (`$f12`) before the
  address (`a1 = x + 992`).
- **The dependence.** The out-parameter's store before the call (`cur = buf`, its address passed
  as the fourth argument) was a member of a stack struct (`fr.cur`, `mem/s` at a fixed address);
  the field load `x->f3D4` is `mem/s` at a varying address. Two structure references are never
  separated (fixed_scalar_and_varying_struct_p needs one MEM_SCALAR_P), so the load waited two
  cycles for the store, the address was issued first, and the object died in the load: v0. The
  store cannot win the first cycle instead: both it and the object's load have priority 6 and
  weight 1, and the load has three dependents to the store's two (rank_for_schedule). A store
  through `Item** p = &fr.cur` has neither flag and depends the same way.
- **A scalar local is MEM_SCALAR_P.** `Item* cur;` declared on its own, with `&cur` passed to the
  call, is a pseudo made ADDRESSOF and given its slot by purge_addressof, which sets the flags
  with MEM_SET_IN_STRUCT_P (put_reg_into_stack: scalar for a non-aggregate type). The load no
  longer depends on the store, sched1 issues the field load before the address (priority 4 to
  3), and the object ties to a1; sched2 then gives retail's order exactly.
- **What the slots show.** purge_addressof gives scalar slots in insn order of the first
  address it cannot fold away, after every aggregate local (an aggregate's BLKmode slot is
  rounded to 16 bytes at its declaration). Retail's frame has the ordered pair at 0 (a struct of
  two pointers, rounded to 16), one byte at 0x10 that nothing reads, then `cur` at 0x14 and the
  result at 0x18. The byte is an empty object whose inline constructor and destructor call
  PushBackMemoryMark and PopBackMemoryMark: its address, the inline constructor's `this`, is
  met before `&cur` and not folded away (measured, not traced in purge_addressof), so it is put
  on the stack first, and the result's load comes after PopBackMemoryMark only when the
  object's scope closes before `return`. A frame with an unexplained small slot before the
  address-taken locals is worth reading as such a scoped object.

### An object with a destructor keeps a slot; one store counted twice (func_001DC4D0)

Measured 2026-11-08 on GatherCollidersInSphere (func_001DC4D0), whose code and registers now
match retail except the spill slot of its count pointer (retail 0x24, ours 0x20):

- **Spill slots come after the declared locals.** reload's first alter_reg loop gives each
  pseudo global-alloc left without a register a slot in pseudo order, after every slot expand
  made (declared aggregates) and every purge_addressof slot. A spilled parameter one word
  above the last declared local means retail declared something there that nothing reads.
- **An object of a class with a destructor keeps a small slot.** A class with a destructor is
  addressable, so its object is in memory even when it is empty and its destructor emits
  nothing. Declared inside a block after a 16-byte Vec local it takes a 1-byte slot at the
  next 16-byte boundary and the spill that follows lands 4 bytes later (0x20 and 0x24 here);
  declared at function scope before the vector it costs 16 bytes. An empty object with no
  destructor, with only a constructor (even one that calls a function), or one whose inline
  method ignores `this` gets no slot at all; a `u8[3]` is rounded to 16. GatherCollidersInBox
  (func_001DC238) has the same small unread object at 0x30 (its locals end at 0x34, the frame
  rounds to 0x40), so the two functions share it at the same point, before the parts loop. An
  empty class with an empty destructor there matches func_001DC4D0 exactly; it is not landed,
  since no type the original plausibly declared there is known (AGENTS.md: no invented type to
  size a frame).
- **Weighted references decide global-alloc's order.** flow counts each reference times its
  loop depth, so `*cursor++ = part;` written in both arms of the filter test (store, read and
  write in the innermost loop, twice) gave the cursor priority 1.039 against the skipped
  object's 0.472, and the cursor took the saved register retail gives the object. Retail
  has one store: its first `sw` sits in the delay slot of a `b` to the second, which reorg
  copied from the branch's target. Written once (the filter's outcomes as `continue` in a
  `for`) the object goes first and both registers are retail's.
- **`a = *p = call()` stores the call's value, not the variable.** `cursor = *out =
  Allocate(...)` gives retail's `sw v0,0(s7)` after `move s2,v0`; `cursor = Allocate(...);
  *out = cursor;` stores the saved register.
- **What the unread object can be, ruled out (2026-11-09, w8).** Read from function.c
  (assign_stack_temp_for_type, purge_addressof), stmt.c (expand_decl), integrate.c and
  toplev.c's pass order, and measured on func_001DC4D0:
  - Not an inline function's frame: that is one BLKmode temporary, rounded to 16 bytes
    (assign_stack_temp_for_type), so the spill would land at 0x30.
  - Not a reload slot whose accesses were inherited away (delete_output_reload): reload's
    first alter_reg loop gives slots in pseudo order, and only the parameters before the count
    pointer (pseudos 116 to 121) precede it; retail gives every one of them a register.
  - Not a scalar whose address was taken and then dropped: purge_addressof runs after jump,
    CSE and delete_trivially_dead_insns (toplev.c), so a dead copy of an ADDRESSOF is gone
    before purge decides, and a scalar that does go to the stack keeps its stores.
  - Not a temporary of the descriptor method calls (`desc03()->m38(a, b)` twice):
    InitContactPairFlags (func_00138F28) makes the same two calls with no local slot at all.
  - Not a `const f32&` temporary (`Square(radius + c->radius3D0)`): it changes the code and
    adds no slot.
  - What is left is a declaration expand_decl puts in memory with no access: a variable
    TREE_ADDRESSABLE before its RTL is made, that is of a class with a non-trivial destructor,
    whose constructor and destructor emit nothing. Its position is free after the vector: an
    empty class with an empty destructor declared before the parts loop or after `done:`, at
    the end of the function, both give EXACT; declared before the vector it takes 16 bytes.
    So the frame shows only that such an object exists, not where or what it is.

- **Approved as ScopeMarker (2026-11-10).** The maintainer approved one shared type for this
  object, `ScopeMarker` (include/scope_marker.h): an empty class whose destructor emits no
  code. Its limit: it is declared only where a retail frame shows an unread slot of 1 to 4 bytes
  of this kind after the aggregate locals, and it is the only such type, never a padding array,
  a byte array or an invented type of one function. GatherCollidersInSphere declares it with
  the loop body's vector (`Vec02 d; ScopeMarker scope;`), GatherCollidersInBox with its two
  bound vectors, in the same form as the sphere query (the walk as a class with a constructor
  and destructor, the filter's outcomes as `continue`, `lo` before `hi`); both match.

### A switch case that falls into the default; a third unread object (func_0014B6A8)

Measured 2026-11-09 on UpdateNumberedAgentGoal (func_0014B6A8), whose code and registers now
match retail except the slots of its two distance floats:

- **A fall-through is one store fewer in the weighted refs.** The hit count's switch sets the
  wall fraction in four places (1.0 for no hit, the exit for two or more, and the entry or exit
  of a lone span), plus one read, each counted twice in the outer loop: 10 references over 183
  insns, priority 0.164, above the neighbour loop's `next` and its 0.5, 1.0 and 0.0 (0.145 to
  0.135), so the fraction took f22. Retail's f26 means a priority under 0.135: the lone span's
  case falls through to the default's `frac = time[1]` (8 references, 0.131). The final code is
  the same, because reorg copies the shared load into the default's branch delay slot; retail's
  two `lwc1 $f26,132(sp)`, one in a delay slot just before the other's address, are that copy.
  The fraction is used uninitialised when the lone span covers the whole segment, so it is live
  around the loop and its length cannot change: the store count is the lever.
- **Operands named in order keep a load behind a Scalar slot.** `a + b * Scalar(3)` written as
  `Vec from = Of(p); Vec weight = Scalar(3.0f); Vec vel = Of(v);` puts the velocity's load
  after the weight's slot store in the insn order; it may alias the store (a load through a
  pointer returned by a call), so sched1 keeps it there and the sum moves next to the call,
  as retail has it. Written as one MulAddX of three nested calls, both loads come first.
- **The same small unread object after a collider query's span array.** The two distances are
  ADDRESSOF scalars that purge_addressof puts after every temporary (0x3C0 and 0x3C4 here);
  retail's 0x3C4 and 0x3C8 mean one more object of at most 4 bytes, allocated after the
  `ColliderSpan hits[8]` (0x40 to 0x3C0) while it is live and never read. An empty class with an
  empty destructor declared right after the array gives EXACT, as in func_001DC4D0 and
  func_001DC238 above: three functions that query colliders now share it. Not landed, for the
  same reason (no type the original plausibly declared there is known).
- **What the unread object can be (2026-11-09, after the scalar-slot change).** The Scalar
  cast copy does not reach it: it is a TImode temporary that reuses the TImode slots at 0x30
  and 0x40 (the 3000 and 3.0 weights) and is stored every time, while the object at 0x3C0 is
  never stored or read; one more Scalar slot would move the distances by 16, not 4. The
  object is not a BLKmode temporary either: assign_stack_temp_for_type rounds a new BLKmode
  slot to BIGGEST_ALIGNMENT (16 bytes) and aborts on less, so an aggregate, an inline call's
  saved frame or a padding array costs 16. It needs a slot of a scalar mode (1 to 4 bytes),
  made in memory with no reference left: a decl of a TREE_ADDRESSABLE type (a class with a
  destructor; a constructor alone keeps it in a register), or a char, short or bool whose
  address is taken, which put_var_into_stack cannot turn into an ADDRESSOF (its promoted mode
  is SImode, `decl_mode == promoted_mode` fails) and so gives a stack slot at once, at the
  point the address is taken. An unpromoted scalar whose address goes only to a dead copy gets
  none: cse1's delete_trivially_dead_insns removes the copy before purge_addressof sees it. In
  this function nothing of the second kind takes an address after `hits`, so the original
  plausibly had an object with an empty (or compiled-out) destructor in the span block or
  after it; which class that was is still unknown.

- **Landed with ScopeMarker (2026-11-10).** Approved by the maintainer as above
  (func_001DC4D0): UpdateNumberedAgentGoal declares `ScopeMarker scope;` right after `hits`
  and matches; SetSinCosPair's prototype is `(f32 value, SinCosPair* self)`, since its caller's
  argument moves follow the parameter order. GatherObjectsByMode (func_0015A198) has the same
  slot at 0x10 below its address-taken count, min and id and matches with the object among its
  function-scope locals, its two mark walks sharing one `p`, and `flags & 0x200` tested at the
  end (a local `all` set before the loop took the spill slot before `&min`'s; the tested
  expression gets the slot after it, as in retail, by a mechanism not yet read). The limit is the
  one above: only where a retail frame shows this unread 1 to 4 byte slot.

### A prototype's parameter order and the order of argument moves (func_0013A128)

The EE's ABI gives integer and float arguments their registers independently (a0-a3 and
$f12-$f19 each in order), so `f(Vec3* in, Vec3* out, f32 s, f32 t)` and `f(Vec3* in, f32 s,
f32 t, Vec3* out)` take the same registers and the callee's code cannot tell them apart. The
caller can (2026-11-08, read from calls.c and haifa-sched.c with `-dS -fsched-verbose-6`):

- **The moves come in parameter order.** load_register_parameters emits one move per argument
  in the prototype's order, and combine leaves each where its move was, so the order of `a0`,
  `a1`, `$f12` and `$f13` before sched1 is the parameter order.
- **That order is sched1's last tie-break, and sched2's.** Three such moves (`addiu a0`, `addiu
  a1`, `mov.s $f13` from a callee-saved zero) have the same priority, weight and dependents;
  the scheduler issues them by INSN_LUID, and sched2's LUIDs are sched1's output order. In
  func_0013A128's three RemapQuadraticParameter calls retail sets a0, then $f13, then a1:
  declared (in, out, s, t) the second call set a1 before $f13; declared (s, t, in, out), $f13
  before a0. Declared `(Vec3* in, f32 s, f32 t, Vec3* out)` all three match (the third's a0
  goes first in sched2 because the `still = 0` after the call, allocated to a0, is one
  dependent more). The definition (file_1E88D0) matches with either order, so it takes the
  order its caller proves.
- **A function-pointer type is a prototype too (func_0012F210).** The position curves'
  evaluate slot was declared (owner, mode, key, scale, ...): func_0012F210's first two calls
  set a2 before $f12, retail $f12 first, and func_001C9DE0's set a2 before $f13. Declared
  (owner, key, scale, mode, ...), the weight curves' own order, both come out as retail's and
  every other caller still matches. A call site that passed a non-zero int where a float now
  is compiles silently (the int converts): rebuild in full after such a change.
- **Diagnosing it.** Where argument moves of one call are issued in an order no rank explains,
  compare their order in the `.combine` dump with the prototype; the order of a function's own
  parameters is evidence only at its call sites.

- **The position curves' slot 0 (func_001C9DE0).** PositionCurveEval is declared `(owner, f32
  key, f32 scale, s32 mode, out value, out slope)`, the weight curves' order: in func_001C9DE0's
  marker 0x1AC the first call's `$f13` (from a zero in a saved register, ready late) and `move
  a2, zero` tie in sched1 at the same cycle, and retail issues `$f13` first; with `mode` before
  the floats `a2` went first. Every other caller matches with either order.

- **func_0012F210's own order (func_0012C9E8).** Its one caller sets `$f12`, `$f13`, a0, a1,
  a2, then `$f14`, then a3 to a5: the time `t` is declared after the point, `(end, radius,
  track, owner, point, t, outT, outPos, outDir)`. With `t` third, `$f14` went first (only
  that differed once the step was named, below). The order also shifts global-alloc's ranking:
  with `t` sixth and the step still set twice, step and best time swapped $f23 and $f24. The
  definition matches with either order. Before both, the near miss called FindEntryByObjectId
  without its key: declaring a callee with fewer parameters than it reads hides the argument
  register's copy and swapped s0 and s1.

- **FindFirstFreeSpan (func_001E4888).** Declared `(count, objs, thresh, a2, a3, lo, hi)`,
  func_001E4888's first and loop calls set `$f12` before a2 and a3; retail sets it after a3
  (into the call's delay slot in the first). Declared `(count, objs, a2, a3, thresh, lo, hi)`
  both match, and its definition (camera.cpp) and other callers match with either order.

### A loop variable declared before its loop: CSE2's copies and the preheader's order (func_001E4888)

func_001E4888's angle sweep had every instruction right but its loop constants in a rotated
set of saved registers (retail: 0.15*pi in $f22, the hoisted zero in $f23, the step in $f26,
the 1.0 copy in $f27; ours swapped each pair). Read from the `-dt -dL -dS -dl -dg` dumps:

- **What fixes global-alloc's order.** loop.c moves the constants in the order of their first
  use (zero, 1.25, 0.15*pi, 1.0, step, 0.25, pi); with five references each (loop depth
  doubles the uses) the zero and 0.15*pi rank by live length, and so does the 1.0 copy against
  the step (three each). The live length is the place sched1 gives each set in the preheader.
- **CSE2 turns two of the moved constants into copies.** After loop, CSE2 replaces `zero =
  0.0` by a copy of a pseudo it knows holds 0 and `one = 1.0` by a copy of the compare's 1.0
  (a CONST_DOUBLE costs two insns on MIPS, a register none). A copy is an alu insn of priority
  1 against the constants' 2, so sched1 places both last unless something raises them.
- **With `angle` declared at the top**, the zero's copy reads `angle`, set in another block:
  it has no dependence in the preheader, weight 1, and sched1 issues it last (shortest life,
  so it outranks 0.15*pi). **Declared just before the loop** (`f32 angle = 0.0f;` after
  `bestScore`), `angle`'s own set is in the preheader (CSE makes it a copy of the 0.0 pseudo
  the first call's literal left in $f20, which then dies there and ties to it), the hoisted
  zero copies `angle`, and its true dependence on that set makes adjust_priority's birthing
  rule raise it as soon as it resolves: it is set early, its life is the longer, and the
  ranking and the 1.0 copy's place follow. The whole function then matched.
- **Diagnosing it.** Where a loop's hoisted constants take a rotation of retail's registers,
  compare the `.loop` dump's movables (insn numbers in the 900s and up, in first-use order)
  with the `.cse2` dump: a constant CSE2 made a copy is ranked by its source's block. Where
  retail's copy is early, look for the copied variable's declaration in the preheader.
- **Stack slots of vectors in a branch.** In the same function the else branch's and the
  final mix's Scalar temporaries took 64(sp) in retail, the slot of the loop's direction
  vector, and 112(sp) (the loop's own temporary) in ours: declared at the top of the
  `if` block (`Vec02 dir, cand, mixed;`), the three slots are freed at its end, and
  assign_stack_temp_for_type takes the first exact fit of the free list.

### A named operand of `>?` (expand_expr's target, func_0012C9E8)

`f32 step = limit * 0.1f >? 0.5f;` expands the MAX_EXPR with the variable's pseudo as its
target, and expand_expr passes that target on as the subtarget of operand 0: the product is
computed straight into `step`, which is then set twice (`mul.s $f24,...; max.s $f24,$f24,$f1`)
and ranks lower in global-alloc (two sets, six references). Retail's `mul.s $f0,$f21,$f0;
max.s $f24,$f0,$f1` is a product in its own block-local pseudo that local-alloc places in $f0,
so the original named it: `f32 tenth = limit * 0.1f; f32 step = tenth >? 0.5f;`. Swapping the
operands (`0.5f >? limit * 0.1f`) does not help (fold puts the constant second). Spot it in the
`.lreg` dump: the variable `set 2 times` where retail's code shows one set.

### A named quotient before `>?` reorders a whole block's FPRs (func_001CE590)

ScorePlayerTargetPlacement's no-solution branch computes `tt = (-dz / g) >? 0.0f` and a
height from it. Written that way the division sets `tt` itself (the MAX_EXPR's target, as in
func_0012C9E8), and `tt`, read again in another block (`*outTime = tt`), is a global pseudo:
the negation `-dz` is then a lone block-local quantity of two references, which local-alloc
ranks below the chain tied to `g` (`g * (tt * 0.5f) * tt` ties each product to `g`, nine
references). The chain took $f0 and pushed every other value one register up (ours
vel.z $f1, g $f0, tt $f4; retail vel.z $f0, g $f1, tt $f0). Named, `f32 fall = -dz / g;
f32 tt = fall >? 0.0f;`, the quotient is a block-local pseudo that the negation ties to
(`-dz` dies in the division): one quantity of four references over a short life, ranked
first, in $f0; `g`'s chain follows in $f1, and global-alloc gives `tt` the free $f0. All
fifteen of the block's float values then match, and reorg's branch over the block becomes
retail's plain `bnez` with the solution path's `lwc1 $f1, t` in its slot (with `tt` in $f4,
ours was `bnezl`).

How it was found: build/swarm/w13-1CE590/sfenum.py (worktree g8, gitignored) emulates
local-alloc's ties (combine_regs: the first operand that is a local register, tied if it dies
there), QTY_CMP_PRI ranking and the fake one-insn-wider lifetimes for one block's SF pseudos
from an `.lreg` dump. It reproduced ours exactly; sampling sched1 orders found few that gave
retail's registers, while raising the negation's quantity by two references gave all of them
at once: a tie the source was missing, i.e. a pseudo of its own for the quotient.

The same function's `if (extra != 0) vel = vel + *extra;` must be a struct store
(`*(Vu0::Vec*)&vel = Vu0::Add(Vu0::Vec::Of(vel), Vu0::Vec::Of(*extra));`): CSE's skip-blocks
path then forgets memory over the skipped body (func_001B2140), and `*outTime = t` reads `t`
again from its slot (`lwc1 $f0, 80(sp)`), retail's four bytes; through `u128` casts CSE kept
the `t` of the min in $f1.

### A float parameter last: the entry copies' order and a0 (func_001CE800)

PlaceOnTargetObject's first statement loads `node->f34` and tests a method of it, then calls
the method with the shape in a0. Declared `(f32 t, Player* self, ...)`, the entry copies are
emitted in parameter order, $f12's first; in sched1 they all have priority 2 and the tie falls
to INSN_LUID, so `t`'s copy took the cycle's second slot and the shape's load issued before
self's copy out of a0. The shape was then born while a0 was live, a conflict, and global-alloc
gave it v1 (`lw v1,52(s3)` and a `move a0,v1` before the call: four bytes). Its two matched
callers already declared it `(Chooser*, TargetCand*, Vec02*, Vec02*, f32 t)`, and one sets $f12
before the integer arguments, as calls.c's reversed evaluation does for a last parameter. With
`t` last, self's copy comes first and the shape takes a0. ApproachValueWithRamp likewise takes
its three floats first (`(f32, f32, f32, RampProfile*, f32*)`, as the file's other callers
declare it), which gives retail's argument order around its call. The ramp record is filled
`y` before `x`, as the same file's other ramp fill does (func_001CFFD0's `i.y = ...; i.x = ...`),
and the clamp of the dot is file_1793C0.cpp's ClampBetween, which returns each outcome into one
value (retail's merge in $f0).

### A call's result register ends a use's dependences in sched2 (func_00131198)

SetupTextPanel (2026-11-09, `-dS -fsched-verbose-6`, haifa-sched.c's sched_analyze):

- **A call clobbers, it does not set.** sched_analyze makes a CALL_INSN depend on the last
  uses and sets of every call-used hard register, but it does not clear `reg_last_uses`: a
  use of v0 stays on the list, and every later call gets one more anti dependence on it,
  until an insn really sets v0 (a call_value, whose pattern sets it). So in sched2 an insn
  that reads v0 (`sw v0,608(s1)`, the -1 of `state = -1`) has one dependent per void call
  up to the next call that returns a value, and rank_for_schedule counts them.
- **What it decided.** InitGifPacket (func_001611B8) ends `daddu v0,s0,zero`: it returns its
  object, as a constructor does, and other files already declare it `void*`. Declared
  `void`, the store had six dependents (the SetTextPanelState, PushBackMemoryMark,
  InitGifPacket and AllocateBackMemory calls, the `li s1,1`, the block end), tied with
  `move a1,zero`'s six and beat `move a0,s1`'s five, issued in cycle 2 and freed the memory
  unit a cycle early: every float constant sched moves up the block (0.171875, 1/24, 640,
  1728, 16, 0.4545, 1936, each a memory-unit insn) went one call earlier. Declared `void*`,
  the store has five, loses the LUID tie to `move a0`, issues in cycle 3 (reorg puts it in
  the call's delay slot) and every constant is retail's.
- **Rule.** Where a store or move of a call-clobbered register goes a cycle early in sched2
  for no rank you can see, count its dependents in the `.sched2` table and check whether a
  callee declared `void` really returns something in v0 (retail's callee setting v0 at its
  end, a constructor returning `this`).
- **Two more ties in the same function.** `for (t = step, i = 1; ...)` puts the copy of
  `step` before the counter's `li` in insn order (they tie on everything else) and gives
  retail's `mov.s` after the UsePacketBufferMemory call; and InitCurveSpan is
  `(span, src, f32 x, f32 y, s32 n)`: with `n` before the floats, `li a2,24` won the LUID tie
  with `mov.s $f12,$f20` at the first call (the prototype rule above). Its definition matches
  with either order.

### Integration: an inline function's parameters and results (func_001316E8)

PAL's DrawCompassStrip (2026-11-09, `-dr -ds -dF -dG`, integrate.c, cse.c, gcse.c, local-alloc.c
and reload1.c of GCC 2.95.3). Retail forms the layout's address again (`addiu a0, sp, 0x240`)
for each of the six setter calls, passes the colour buffer's address from a spill slot (`lw
a1, 0x2B4(sp)`) and the layout's address to the three draw calls from another (`lw a1,
0x2B0(sp)`). Written as plain calls (`L.Pos(...)`, ... `L.Color(col.w)`), the layout's address
was one pseudo for all nine calls and took s6, which moved self and the readers' addresses
one register each (95.5%).

- **A call's argument is a pseudo; an inline's is substituted.** expand_call computes `&L`
  into a pseudo at each call; CSE makes them one, and gcse's PRE replaces its computation with
  a copy of the address it hoists before the loop: a long-lived pseudo with no equivalence.
  An inline function's parameter that its body never sets is TREE_READONLY (save_for_inline
  clears it only for a modified one), so expand_inline_function takes the argument as it is:
  a frame address `(plus vsv N)` gets a constant equivalence (process_reg_param,
  FIXED_BASE_PLUS_P) and try_constants writes it into each insn of the copied body. The
  calls inside then set a0 from `(plus fp N)` directly; no pseudo holds the address, and CSE
  keeps the constant (the integration's own copy of it is a user variable). The same holds for
  the inline's own locals: virtual_stack_vars maps to a pseudo with the frame block's address
  as its equivalence, so `&local` is substituted too.
- **What escapes substitution.** A parameter the inline modifies (copied through a register
  first), and a value an inline function returns: the result goes to a fresh pseudo set from
  the address, which a following call takes as an ordinary argument. That pseudo is in gcse's
  table, PRE hoists it, and global-alloc leaves it in a spill slot: retail's `lw a1, 0x2B4(sp)`.
- **The form.** The six setter calls in an inline helper taking the layout and the colour
  (`Reset(Layout_137228* l, s32 color)`), the colour written into the helper's own Quad4 and
  passed as `l->Color(Words(col))`, `Words` an inline returning `q.w`: EXACT. The helper's
  frame (the Quad4 at 0x260) is the block temporary the later SpanHead reuses, as retail's.
  `l->Color(col.w)` in the helper gives `addiu a1, sp, 0x260`; the buffer as the caller's local
  passed in (`Reset(&L, col.w)`, also with `&col.w[0]`, `(s32*)&col` or a `void*` parameter) is
  substituted the same way; the colour as a parameter whose address the helper takes (`s32
  color`, `const s32&`) goes through ADDRESSOF and purge_addressof places it after every other
  local (0x2B0), and the buffer built in the caller stores the colour before Pos.
- **Rule.** Where retail forms a frame address again at each call (`addiu aN, sp, K`) but
  keeps the same address in a register or spill slot for other calls, the calls that form it
  were inside an inline function whose parameter or local it is. func_00134B48 (US, not yet
  matched) has the same setter sequence (Pos(0, 0), Size(640, 492.8), the grey colour from a
  spill slot, the two words cleared) and is likely the same helper.

- **Confirmed in US func_00134B48** (2026-11-09, near miss, 99.1%). The same five setters in
  an inline helper (`ScreenLayout::Reset(Layout_137228* l)`, the colour a constant in the helper:
  as a parameter, loop.c hoisted it into s4) give retail's `addiu a0, sp, 0x1B0` at each call and
  the buffer from a spill slot. The rule finds a second inline in the same function: retail
  forms `&layout` again for the font's `drawBox` call but passes `&style` from a spill slot, so
  that call sat in an inline taking the layout (the file family's `StyleDrawer::Draw(Font** h,
  Layout* out, void* tbl)`, `if (*h) (*h)->vt->drawBox(...)`). With both, `&layout`'s pseudo has
  one use left (DrawFontString), loses s4 to the clock's address and spills, and the frame grows
  by retail's 16 bytes (a fifth spill slot). Then gcse's bucket order (T = 187 against 189, one
  Vec value) and loop.c's pass order (below) gave retail's registers.
- **Which pass moved an invariant decides global-alloc's tie of two hoisted addresses.** In that
  function the clock's address (`g_gameClock`, read twice) and the coefficient table's (read
  three times) both live from the preheader over the loop; retail's preheader has the table's
  `%lo` first and gives the clock s4. loop.c moved the clock's `%lo` in its first pass (savings
  2, life 10) and found the table's not desirable there (savings 1, life 3: move_movables
  lowers its threshold by 3 for every insn it moves, so threshold * savings * life fell short
  of the loop's 282 insns), moving it only in the second pass; the clock's address then lived
  longer and won the tie. The table read through a pointer named before the projection call
  (`const f32* k = D_002611A0;`, life 30) moves in the first pass ahead of the clock's: retail's
  order and registers.
- **What is left there: sched1's order of the preheader.** sched1 puts a `%lo` that ends its
  `%hi` (register weight 0) before a frame address (weight 1), and the float constants (memory
  unit, priority 2) one per cycle beside them; retail's spill stores between the constants
  need `&pos` beside the first constant, so retail's preheader had one invariant `%hi`/`%lo`
  pair fewer than ours (three: the table's, the clock's, g_unitRange's). The likely one is
  g_unitRange's `%lo` (Limit's `this`), which loop.c's second pass moves with a life of 4 (the
  inline's two block notes count); no clamp form tried keeps it in the loop with retail's code.
- **loop.c's threshold for a loop with a call is 79** (1 + n_non_fixed_regs; measured
  2026-11-09 on synthetic loops of N calls: a life-1, savings-1 invariant moves at 79 real
  insns and not at 80). In func_00134B48's second pass (234 insns) a move-insn moves when
  its life is 3 or more. Limit's `this` copy is set before expand_inline_function's contour
  (`pushlevel`/`expand_start_bindings` come after the arguments), so the two BLOCK_BEG notes
  sit between it and its uses; CSE folds the `lo` read into `lo_sum(%hi)`, leaving the `hi`
  read as the last use: life 4. Loading `hi` first gives life 3 (237 >= 234, still moved)
  and puts `lo` in $f5 where retail has $f4. An inline's `this` that is read only inside its
  body can never have a life under 3.
- **Keeping the address in the loop gives retail's preheader, and loses s4.** A clamp that
  reads `hi` only in its else arm (`if (v < lo) r = lo; else if (hi < v) r = hi; else r =
  v;`, as an inline member) uses the address in another basic block after the loop's first
  branch, which scan_loop refuses to move at all (maybe_never). Its preheader then has
  retail's sched2 order (the spill stores between the constants exactly as retail), the
  result in $f13 copied to $f23, `lo` in $f4. But gcse's PRE pseudo for g_unitRange's `%hi`
  (moved in loop.c's first pass, priority 1 in sched1, so after `&pos` by LUID) has 5 refs
  over 466 (doubled) against the clock address's 5 over 486 (its `%lo` is raised to cycle 2
  by the birthing rule), outranks it in global-alloc and takes s4; retail leaves it
  unallocated (the `lui a2, 0x27` rematerialized in the body). With equal references the
  `%hi` set later in the preheader always outranks the clock, so retail's preheader had
  either no g_unitRange `%hi` at all or one that lost on references.
- **What fits every constraint and is not found.** Retail's body code is that of a
  hoisted, unallocated `this` (REG_EQUIV constant: reload rematerializes `&g_unitRange` for
  the `+4` read, reload_cse turns its `lui a3` into `move a3, a2`) whose `lo` read was folded
  by CSE. A hoisted `%lo` is raised to the front only because its `%hi` is set in the same
  block (adjust_priority runs when a dependence resolves); with the `%hi` set in an earlier
  block, the `%lo` would be ready from the start at priority 1 and follow `&pos` by LUID, and
  the `%hi`'s longer life would lose s4. No form tried puts g_unitRange's `%hi` before the
  loop while CSE still folds the `lo` read (a reference declared before the loop or at the
  top of the body breaks the fold: `lwc1 $f4, 0(a2)`; a `const` pointer is substituted as
  a constant, as Limit's `this`; two calls for the f58 ramp, which would raise the clock's
  references, are not cross-jumped into retail's single call).

### The colour of a band: const pointers that only lend their `%hi` (func_00131F60)

DrawTextPanelControlLabels (US, 2026-11-10, `-dj -dG -dL -dS -dg`, jump.c, gcse.c, loop.c of
GCC 2.95.3; near miss at 95.7%). Retail's gauge loop picks a colour per band with `bc1t join`,
`addiu v0, s4, %lo(D_002610D8)` in the delay slot, `addiu v0, s3, %lo(D_002610E0)` on the
fall-through, and keeps both `%hi`'s (and g_camera's, s5) from the prologue on.

- **Where each candidate failed.** An if/else of `&D_002610D8` / `&D_002610E0` keeps both
  arms (each a `%hi` and a `%lo` with a REG_EQUAL note, which jump.c's `x = b; if (c) x = a`
  hoist refuses), but loop.c leaves the `%hi`'s in the arms: each has life 1, savings 1, and
  the loop is 90 insns against a threshold below 80 (1/9 and 1/15 sit before them and stay
  too). PRE cannot hoist them: an expression in one arm only is not anticipated at the loop
  header. References or pointers to the colours at the top of the body make the `%hi`'s
  anticipated (PRE hoists them), but the arms become plain copies, which jump.c's first pass
  hoists before the branch, and sched1 then issues that copy first (the ALU is free at cycle
  2): retail's delay slot never appears.
- **The form.** `const PanelColor* const lit = &D_002610D8;` (and `dim`) at the top of the loop
  body. g++ substitutes a const pointer's constant initialiser at each use, so the arms are
  the direct addresses (two insns each, REG_EQUAL notes: no hoist before reload), while the
  declarations still emit their own `%hi`/`%lo` at the top. Those make each `%hi` anticipated:
  PRE hoists them and the arms' `%hi`'s become copies; the dead `%lo`'s go. After sched2 the
  arms are one `addiu` each, and reorg takes the target arm's `addiu` into the delay slot.
- **Which saved register.** pre_edge_insert places the hoisted `%hi`'s in expression-index
  order (first appearance) and global-alloc ranks the last placed highest (shortest life):
  retail's camera s5, D8 s4, E0 s3 needs the camera's read first, `f32 zoom = g_camera->f478;`
  before the two pointers.
- **The state-1 half** (all of it retail's now): the five setters in `ScreenLayout::Reset(l,
  color)` with the colour copied into a local of the helper (`s32 c = color; l->Color(&c);`:
  ADDRESSOF places it after the other locals and stores it after Size, the colour in s0
  across Pos and Size; with the helper's own Quad4 the buffer's address is the inline frame's
  pseudo, hoisted into a saved register, and with `&color` the store moves before Pos); `char
  buf[16]` declared before the layout (sp+16, layout sp+32, buffer sp+64); the first two
  words stored through `Layout_137228* lay = &L;` (PRE copies lay into the pseudo the draw
  calls use, retail's `addiu v1, sp, 32; move s6, v1`), the later stores as `L.`, and the
  move colour stored before PushFontScale.
- **Still open.** 55 and 372.8 stay in the loop only as a variable assigned twice (as literals
  CSE makes each one pseudo of life 4-5 that loop.c moves); retail has them in f6 and f2 by
  local-alloc, which a twice-set variable never is. "Move"'s `sw a0, 20(s6)` needs its store's
  address formed as a pointer there (a reference made at that point does it; no plainer form
  found).

### An inline method's member read is not the caller's: a tested value stays local (func_001A8C90)

The object pool's release (2026-11-10, `-dl -dg -dG`). Retail tests the random spin's upper
bound and then passes both ends to RandomFloatInRange: `lwc1 $f1, 0xD4(s2)`, `c.lt.s $f0, $f1`,
then in the arm `lwc1 $f12, 0xD0(s2)` first and `mov.s $f13, $f1` in the call's delay slot.
Written `if (0 < self->spinHi) RandomFloatInRange(self->spinLo, self->spinHi)` (or with a local
for the bound), CSE makes the call's read the test's pseudo; that pseudo lives into the arm, so
global-alloc takes it, and its copy to $f13 is a preference: `lwc1 $f13` for the test, the
copy gone, the tail one instruction short.

- **The read through an inline's `this` is a different address until after GCSE.** With the
  pair a ValueRange and the call its inline method (`self->spinRange.Random()`, include/value_range.h),
  the body reads `hi` as `(mem (plus this' 4))`, `this'` the integrated copy of the parameter:
  the .gcse dump still has it, so neither CSE nor GCSE replaces the load with the test's value.
  The test's pseudo then dies at the compare: local-alloc gives it the lowest free FPR ($f1,
  $f0 holding the zero), and after reload, reload_cse_regs sees $f1 holds the word and turns
  the arm's load into `mov.s $f13, $f1`. A variable set twice (`m = self->spinHi; ... m =
  Random(lo, m)`) gives the same schedule but crosses the calls ($f22).
- In the same function: a `switch` whose `case 0: case 1: default:` block retail lays out before
  case 2 is written in that order (the cases in retail's block order); `if (frame != 0 ||
  self->target == 0) at = &self->at; else { ... }` gives retail's fall-through and the target's
  pointer in the address's register; and the length's second conversion after the
  normalisation is ToFloatMoved with the test's ToFloat (the other way round, CSE merges the two
  GPR copies; both ToFloat, the asm qmfc2 is scheduled before the coefficients' address).

### A float parameter last moves an asm's quantity (func_001D2518)

Read on func_001D2518's three CreatePooledContact calls (2026-11-08, `-dS -dl
-fsched-verbose-6`, local-alloc.c and haifa-sched.c), each passing `ToFloatMoved(Dot(delta,
v))`: retail loads delta into vf1 for the first two dots and into vf2 for the third (dir in
vf1), ours vf1 for all three.

- **local-alloc.** The Dot asm's output is tied to delta, its first dying input, so that
  quantity has 3 + 2 references and lives from delta's load to the mtc1 that reads the result
  (Local allocation's ranking above): 2 * 5 / 12 outranks the other input's 1 * 3 / 4, and it
  takes vf1. One insn more between the asm and the mtc1 (life 14) makes the other input go
  first and take vf1, retail's third dot.
- **sched1.** At the cycle after the dot the mtc1 to $f12 (weight 0: it sets one register, the
  result dies) ties with the a3 move, whose `&dir` pseudo dies there (weight 0 too); the class
  and the dependents are equal, so INSN_LUID decides, and LUIDs follow the prototype's
  parameter order (the section above). With `CreatePooledContact(f32 f, a0, ...)` the $f12 move
  is first and issues first; declared with the float last, `(a0, a1, a2, a3, s32, s32, s32,
  a7, f32 f)`, as func_0013B9D8's matched call already has it, the a3 move goes first, the mtc1
  one insn later, and the third dot takes retail's registers. In the first two calls the a3
  move's pseudo does not die there (weight 1), so the mtc1 wins either way and nothing changes.
- **reorg steals the else arm's first insn.** Retail sets the list head (`addiu s7,s0,1204`) in
  the delay slot of the first branch to the else arm, and both branches go to the insn after
  it. That is the assignment made only in the else arm (`} else { link = &self->contacts4B4;
  ...`): fill_slots_from_thread copies the target's first insn into the slot (s7 is dead on
  the fall-through, which sets it before use) and redirects the branch past it. Initialised at
  its declaration the add is in the entry block, where its anti-dependence on `sq s7` gives the
  save one dependent more than the others, and sched2 issues it first; and in the else arm the
  `move s4,s7` then precedes the copies PRE put there instead of following the first.

### The operand order of an address sum (expr.c, func_0013A128)

`addu a0, v0, t0` (index first) and `addu a0, t0, v0` (base first) come from two different
paths in expand_expr's PLUS_EXPR (2026-11-08, read from expr.c and optabs.c):

- **A pointer initialised with a sum keeps the source order.** `u8* out = &colors[k * 4];`
  (C++ folds `&*(p + i)` to `p + i`) is expanded outside an address, so it goes to
  expand_binop, which swaps commutative operands only when the second is a register and the
  first is not (or the first is a constant): two registers stay base first.
- **An address expanded as a memory reference puts the multiplication first.** Inside a MEM
  the sum is expanded with EXPAND_SUM; the multiplication by the element size comes back as a
  `(mult k 4)` and the both_summands code ("put a constant term last and put a multiplication
  first") returns `(plus (mult k 4) base)`, which force_operand turns into `addu index, base`.
  So the store written as an element (`self->color[k][j] = ...`, or `colors[k * 4 + j]`) gives
  retail's operand order, and loop.c's strength reduction then makes the pointer that is
  incremented by one, as retail has it. The reads in the same loop (`(colors + i * 4)[j]`)
  show the same order for the same reason.
- **A constant base folds into the index.** `self->color[0] + k * 4` and `&self->color[k][0]`
  as a pointer's initialiser fold the member's offset into the index (`sll; addiu 1424; addu
  base`), losing the hoisted base: the form that keeps both is the element store.
- **An array member indexed is base first (func_001F2840).** `out->f[k]`, where `f` is a
  `f32[4]` member, is an ARRAY_REF: expand_expr takes it through get_inner_reference, which
  returns the object (`*out`) and the variable offset `k * 4`, and the address is built as
  `(plus base offset)`: `addu v0, s1, v0` with `out` first, retail's order. Pointer
  arithmetic (`out[k]` with `f32* out`) gives the multiplication first. A pointer to an array
  (`f32 (*out)[4]`, `(*out)[k]`) does not help: the C++ front end's build_array_ref turns an
  array reached through INDIRECT_REF back into pointer arithmetic, so the array must be a
  member (or a declared array).

### Sony's compiler separates memory by type; a stack argument's load (func_001F8290)

Read from local-alloc.c, haifa-sched.c and the `-dS -dl -dg -fsched-verbose-6` dumps of
CallRemoteService (src/lib/remote_call.cpp, 2.9-ee-991111, 2026-11-08):

- **2.9-ee-991111 at -O2 has type-based alias analysis on.** Its sched1 lets a store of a
  pointer member (`self->packet`, `self->callback`) pass an int load through another pointer
  (`packet->id`), and an int load wait for an earlier int store (`self->callbackArg`); with
  `-fno-strict-aliasing` the pointer stores depend on the load too. Signed and unsigned ints are
  one class, each pointer type is its own (a `Packet*` store depends on a `Packet*` store, not
  on a `void*` one). The game's SN 2.95.3 has no such separation ("Alias classes in the
  schedule" above), so this applies to Sony's libraries only.
- **A stack argument used once is loaded where it is used.** The ninth argument (192(sp))
  gets a pseudo set at the entry with a REG_EQUIV note; update_equiv_regs, at the start of
  local-alloc (after sched1), cannot put the stack slot into the store that uses it, so it moves
  the load to just before that store. The pseudo is then a local quantity of two references
  over one insn, the first that local-alloc places: $v0 here.
- **The widened lives decide the neighbour's register.** block_alloc first tries each quantity
  over its life widened by one insn at each end (fake_birth/fake_death). So a quantity takes
  the register of one placed before it not only when their lives overlap but also when the
  other is born in the insn right after its death or dies right before its birth.
- **What it gives func_001F8290.** Retail's id (`self->id = packet->id`) is in $v1 and
  `mode & 2` in $a0 because the argument's load sits inside (or next to) the id's life in
  sched1's order. Written with the id first (`self->id = packet->id;` before
  `self->callbackArg = ...`), sched1 issues the id's load, the argument's store, then the id's
  store, and every register is retail's; written after the argument's store, the int load must
  wait for it, the id's life is after the argument's and takes $v0.
- **What is left: the weight wall.** Retail stores the client's fields in the order argument,
  packet, id, callback. sched2 breaks the tie between the packet's and the id's store at t=4
  on INSN_LUID, sched1's order, so sched1 must have issued the packet's store first; but the
  id's store is ready at t=3 (its load at t=1, two cycles) and weighs 0 (its value dies) where
  the packet's store weighs +1, and the argument's store has taken t=2. With every field an int
  (or `-fno-strict-aliasing`) the function is two instructions off for that reason alone; with
  the header's pointer types the pointer stores fall to the end of the block (priority 2).
  A sweep of about 1,000 combinations of the client's and packet's field types (int, the pointer
  type, void*) and store orders found nothing closer. Retail's sched1 order is not reachable in
  this model; something in the original's block is still unknown.

### sched1's weight puts a dying value's store first (func_001F8290)

Read from haifa-sched.c (find_insn_reg_weight, rank_for_schedule) and the `-dS -fsched-verbose-6`
dumps of CallRemoteService with Sony's 2.9-ee-991111 (2026-11-09):

- **A store weighs too.** find_insn_reg_weight counts +1 for any SET pattern, a store to memory
  included, and -1 for each REG_DEAD or REG_UNUSED note. So a store whose value dies there weighs
  0 and one whose value lives on weighs +1, and before reload rank_for_schedule prefers the lower
  weight right after priority, before the last-insn class, the dependents and the LUID.
- **What it costs func_001F8290.** With the client's packet and callback words as ints (u32, as
  the packet's own self and client words are) all four client stores depend on the packet's int
  stores and have priority 7; the id's load (priority 9) issues at t=1 and its store is ready at
  t=3. The argument's store (its value dies: 0) takes t=2, and at t=3 the id's store (0) beats
  the packet's (+1). sched2 then breaks the packet/id tie on LUID, sched1's order, and retail's
  argument, packet, id, callback becomes argument, id, packet, callback. With one memory unit no
  order of these four stores and their types gives retail's: the packet's store can only be
  issued before the id's in the one cycle before the id's value arrives, and the argument's
  store (weight 0) takes that cycle.
- **Proved by experiment.** One more later use of the id (`packet->f38 = id;` after the packet's
  stores) makes the id's store weigh +1; sched1 then issues argument, packet, id, callback, and
  the block, its registers included, is exactly retail's. So in the original the id's value
  outlives its store when sched1 runs (or a barrier, such as a loop note, separates the packet's
  store from the id's), and nothing of it is left in retail's code: an insn deleted after sched1
  (a move reload drops, a dead set flow2 deletes) or a form not yet found. Ruled out: the
  packet's, callback's and argument's words as int, pointer or void* with every store order and
  the id read in place or into a local (864 compiles), and -O3, -fno-gcse, -fno-strict-aliasing,
  -fno-sched-interblock, -fno-regmove, -fno-rerun-cse-after-loop.
- **Spot it.** Two stores swapped against retail where the earlier one's value dies in it and the
  later one's lives on: the tie is the weight, and moving statements does not change it.

### A run of stores in two alias classes (func_001F7BE8)

Read from the `-dS -dl -fsched-verbose-6` dumps of InitRemoteCalls (src/lib/remote_call.cpp,
2.9-ee-991111, 2026-11-09):

- **The `%lo` store is a barrier for its own alias class only.** The record's word at offset 0
  is stored through `(lo_sum hi sym)` (combine folds the zero offset), the others through the
  record's base register. After reload sched2 cannot tell the two addresses apart and makes the
  `%lo` store depend on every store of the same alias set issued before it in sched1, and every
  later one on it; with Sony's type-based aliasing a store of another type (the pool pointers,
  `RemoteCallPacket*`) is free of it. The near miss declared every word an int, so all nine
  stores were chained to the `%lo` one; the file's own record type (the packet pointers as
  pointers) frees the three pointer stores, and sched2 then puts them out in retail's order.
- **The int stores' order is sched1's weight, then the source order.** Before reload every
  store has priority 16 (they all feed the next call); a store whose value dies there weighs 0
  (the last of the three `0x20` stores in insn order, and the `%lo` store of 1), the zeros and
  the earlier `0x20` stores weigh +1, and ties fall to INSN_LUID. Retail stores the last pool
  size before the id counter and the rest after it in field order: the fields in order with
  the id counter set last (`s->next_id = 1;` after `s->cursor = 0;`) gives exactly that. The
  id counter written first gives the `%lo` store first and the run of ints behind it, the one
  difference left by the near miss.
- **Spot it.** In Sony's code, a store through `%lo(sym)` of a struct whose other stores go
  through a register: which stores sched2 lets pass it shows their types, and the stores that
  stay on its far side give the source order around it.

### Sony's compiler balances a chain of | and + (func_00202140)

Measured with 2.9-ee-991111's `-dr` dumps (2026-11-10), on test functions and on
sceGsSetDefDispEnv's DISPLAY register (src/lib/graph.c, func_00202140):

- **A left chain is rebuilt as a balanced tree as it is folded.** SN 2.95.3 expands
  `a | b | c | d` as written; the libraries' compiler re-associates each step (the same for `+`,
  so it is not fold-const.c's `associate:` of mainline 1999, which only moves constants). For
  parameters a, b, c, ... the .rtl shows:
  - 3 terms: `(a|b)|c` (unchanged); 4: `(a|d)|(c|b)`; 5: `((a|e)|(c|b))|d`;
    6: `((a|f)|(d|c))|(b|e)`; 7: `((a|g)|(b|e))|((d|c)|f)`; 8: `((a|h)|(d|f))|((b|c)|(e|g))`;
  - `(a|b)|(c|d)` gives `(a|c)|(b|d)`; `a|(b|c)` is unchanged.
  So the order of the ORs in retail's code (`or rd,rs,rt` keeps the tree's operand order) is a
  fingerprint of the source's term order, not that order itself: read it back through this table.
- **With a ternary among the terms, fold distributes the ORs into both arms** (fold's COND_EXPR
  rule: `X | (c ? a : b)` becomes `c ? X|a : X|b`, X made a SAVE_EXPR evaluated before the test).
  Every term ORed in after the ternary is saved too, so all terms are computed before the branch
  and each arm ORs them, in a tree balanced from the arm's own chain; cross-jumping then merges
  the arms' common tails (here across two video modes as well). The terms before the ternary are
  one save: ORs before the branch mean the ternary came late in the chain, none (retail here)
  that it was first or second.
- **What it gave func_00202140.** Retail ORs `((magh | dw) | (dx | dh)) | dy` in all four
  display arms with every term computed before the field test; of the 120 orders of the macro's
  five terms only `magh, dh, dx, dy, dw` gives it (a sweep, scored with check.py), and with it
  the size and every block but the division's are retail's. A second lever: `magh` declared in
  each arm, not once for the function; one variable assigned in four arms is a global pseudo,
  which local-alloc cannot tie the quotient to (`mflo v1; move v0,v1`).
- **Unsolved: the zero trap's place.** In both interlaced arms retail issues the division's
  `beqzl/break` before dy's `dsll a3,v1,12`; sched2 gives the shift priority 5 (an anti
  dependence: the dx term's `daddiu` writes the v1 it reads) and the trap 4 (`1 +` the field
  load it orders), with retail's own registers, so retail's sched2 had a dependence ours lacks
  (a sched1 link to the trap, which only memory references after it get, or a field load with a
  longer chain). The ternary's spellings and a named `magh * w - 1` (which moves the multiplies)
  do not change it.

### Reading a library function's source off its code: types, sums and spill slots (func_0020CAF8)

Measured 2026-11-10 on the MPEG macroblock prediction (src/lib/mpeg_macroblock.cpp, 2.9-ee-991111;
nonmatching/func_0020CAF8.cpp). The near miss had the wrong frame (0xA0 against 0xB0) and 49% of
retail's code; these readings gave the frame, the spill slots in retail's order (but one), the
branch layout and 68% of the code:

- **A constant kept with the index means a pointer.** Retail adds `(yo << 4) + 0x300` first and
  then the base (`addiu t2,t1,768; addu t2,s2,t2`). With an integer base fold re-associates
  `base + ((yo << 4) + 0x300)` to `(base + 0x300) + (yo << 4)`; with a `u8*` base the integer sum
  is converted before the pointer addition and stays one operand. So the work buffer, the
  destination and the parts' rows are pointers.
- **Which loads are reused shows the types (type-based aliasing).** Retail loads the frame's data
  word once for both source rows and its width again at the end, re-reads the count for the
  final `count++`, and keeps the chroma rows' stores before the source rows' store. That is: the
  frame's data an int (as func_0020C1A0's frame record has it), the parts' rows and the source
  rows the same pointer type (their stores chain), the count an int read again after the int
  stores.
- **A four-term sum's operand order reads back through the balance table** ("Sony's compiler
  balances a chain of | and +"): retail's `(A + y) + (dstY + srcField)` is the source
  `A + srcField + dstY + y`.
- **A test whose `then` is the split.** Retail branches from both row tests into one shared
  `rows = height; rest = 0;` tail after both arms (bnezl into it): written `if (... >= 16) split;
  else whole;` cross-jumping merges the two `else` tails; written the other way round the first
  test jumps into the second arm.
- **Spill slots in declaration order.** reload gives the pseudos global-alloc leaves without a
  register their slots in pseudo order, and pseudos are numbered as the front end meets them:
  retail's slots (dstField, x, the destination, the routine index, the luma block, `&count`'s
  base, `average << 2`) put the count's address after the luma block, which needs the locals
  declared at the top C-style with the count read after them (`s32 n; ... n = ...count;`); an
  initialised `s32 n = ...` first numbers the address before them.
- **A value computed once before a branch was named.** `height >> 1` and `dstY >> 1` are computed
  once before the chroma part's `if (half)` in retail (each arm uses them); written in each arm
  they are computed in each arm (PRE does not hoist what is only anticipated). Likewise the
  half-pixel flags `dx & 1`, `cdx & 1`, computed before the row tests.
- **What is left.** The routine index keeps a register (s5) where retail spills it at 12(sp):
  local-alloc gives `yo << 4` t2 in the block after the luma row tests (retail t1), and its
  preference pulls ys and yo into t2 (retail a2), the first difference in global-alloc's order;
  the registers cascade from there.

### A copy keeps two tests of one flag apart (func_001F8DB8, func_001F9028)

Read from the `-dr -ds -dG` dumps of ReadFile and WriteFile (src/lib/iop_file_client.cpp,
2.9-ee-991111, 2026-11-10), with gcse.c's hash_scan_set, cprop and pre_delete:

- **What retail shows.** Both functions test the handle's mode `& 0x8000` before registering the
  semaphore and again after the reply, and retail computes `andi v0,s3,0x8000` at each test. Written
  with one variable (`if (p == 0 || (mode = p->used) == 0)`), PRE finds the second `and` fully
  redundant, keeps the first's result in a pseudo across every call, and that pseudo takes the
  callee-saved register retail gives to a hoisted `%hi` (0x20000000 or D_006284C0's high half): one
  instruction longer, and every later register moves.
- **The mechanism.** Written as `if (p == 0 || p->used == 0) { ... } mode = p->used;`, the null test
  loads the field into a temporary, and cse1 (following the jump) turns the second load into a copy
  `mode = temp`. GCSE's copy propagation then replaces `mode` by the temporary in the uses in later
  blocks (the 0x20000000 test and the last test) but not in the first test, which sits in the copy's
  own block (cprop is global only). The two tests are now `(and mode 0x8000)` and
  `(and temp 0x8000)`: different expressions, nothing redundant, and global-alloc ties the copy's
  two pseudos into one register (s3), so the only trace is the recomputed `andi`.
- **Ruled out.** A copy written by hand (`s32 m = mode;`) or an inline function's parameter: cse1
  canonicalises them back to `mode` along its jump-following path. `(s16)mode < 0` gives sll/bgez,
  `(mode >> 15) & 1` keeps the shift, and `(u16)mode & 0x8000` folds back to the same expression.
- **The rest followed once the size was right.** The reply's address written in place
  (`D_006284C0` as the argument and `(u32)D_006284C0 | 0x20000000`, as ControlFile has it) leaves
  three `%hi` that PRE hoists into the first test's arms (D_006284C0, D_00628500, D_00628B40, all
  anticipated after the join and blocked by the registration loop); global-alloc gives the callee-saved
  register to D_006284C0's, as retail. WriteFile also needed: the zero arm first
  (`if ((buf & 0xF) == 0) head = 0; else ...`) for retail's block order; the head as
  `((buf >> 4) << 4) + 16 - buf`, which Sony's reassociation turns into retail's `A - (buf - 16)`
  (written `A - (buf - 16)` it becomes `(A + 16) - buf`); the uncached address stored back into
  `buf` (retail's `or s1,s1,s3`); and the copy loop's own index variable (retail's two loops count in
  different registers, a2 and a1).
- **Spot it.** A test of a flag in a callee-saved register that retail recomputes from the variable
  each time: look for the variable assigned after its first test as a load (`if (!p || !p->field)`
  then `x = p->field;`).
- **A check.py caveat.** check.py printed `lui v0,0x62` against retail's `0x63` for these functions
  while the full build matched: it pairs a `%hi` of a file's static (a `.bss` section symbol) with the
  next `%lo` of the section in address order, and a hoisted `%hi` whose `%lo` is far away takes
  another static's. A `.bss` `%hi` off by one in check.py alone is worth a full build.

### A result scaled where it is stored: a fourth reference and a fresh register (func_00130540, func_00130748)

- **The form.** Both Hermite steps end in a weighted sum scaled by a parameter (the velocity
  by k, the spin by e). Retail's vmulx gives the product a register of its own (vf3, vf2)
  where `Q(*out) = MulX(sum, Scalar(e))` ties it to the sum (vf1), and in func_00130748 the
  output pointer takes s5 ahead of the two spin pointers (s6, s7) where ours took s7. Both come
  from storing the sum and then scaling it in place:
  `Q(*out) = MulXSum3(...); Q(*out) = MulX(Q(*out), Scalar(e));`. That matched
  func_00130540 whole and left func_00130748 two instructions off.
- **Why the product is fresh.** CSE replaces the reload of `*out` with the sum's register, but
  the first store stays until flow2 (life analysis after reload) deletes it as overwritten
  with no read between. In local-alloc's view (after sched1, which puts that store after the
  vmulx) the sum is still live past the vmulx, so it has no REG_DEAD there and combine_regs
  cannot tie the product to it; the product takes a free register.
- **Why the pointer moves up.** The dead store still counts: flow's REG_N_REFS (taken before
  combine and never recounted) gives out four references (its copy, the test, two stores)
  against three for each pointer read twice. global-alloc's priority,
  floor_log2(refs) * refs / live length, is then 2 * 4 / 165 against 1 * 3 / 151, so out is
  placed first and takes the lowest free saved register.
- **Ruled out first.** An early-clobbered MulX (`"=&j"`) gives the same fresh register, which
  is how the tie was diagnosed; Vec against u128, a named sum (`r = MulX(r, ...)`, which CSE
  folds to the same insns) and the order of the sum's operands do not.

### A length returned as a float joins the allocation's preferences (func_00130748)

- **The form.** NormalizeAxis (an axis made unit length, or a fallback when shorter than
  1e-4) returning the length as a float (`return Vu0::ToFloat(len);` after the join, the
  caller's `f32 len` assigned at both calls) rather than the u128 the caller converts.
- **The mechanism.** The caller's len is one variable assigned twice, so a global pseudo.
  local-alloc then sees only uvv * dur in the call's block with $f12 suggested (the
  argument's product), and it takes $f12 where the length's local float had won it on a
  shorter span. set_preference gives uvv the preference $f12 from that insn (the first
  operand of a set of a hard register), and expand_preferences passes it on to v (1 - u),
  which dies where uvv is born and does not conflict with it: global-alloc then takes $f12
  for v instead of $f4, retail's register. The length itself gets $f2 from global-alloc's
  pass 0, which skips $f0 and $f1 that uvv (lower in priority, conflicting) prefers. With v
  in $f12 the prologue's `mov.s $f21,$f12` and the uuv/uuu products fall into retail's order
  (uuu declared before uuv).
- **What is left.** At the first call's join retail issues `mul.s $f12,$f0,$f21` (uvv * dur)
  before the length's `qmfc2 v1,$vf2`; sched2 ranks them equal (priority 16: the asm 1 plus
  reload's mtc1 2 plus the product 13, against the mul.s 3 plus 13) and takes the qmfc2,
  which has six dependents (reload's mtc1, the product through sched1's stale LOG_LINK, the
  next length's vaddw.x into vf2, the next qmfc2 into v1, the call, the jump) against the
  mul.s's four. ToFloatNow (one asm, cost 1) gives retail's order but its GPR is local-alloc's
  v0, not reload's v1, which shifts reload's round robin in the spin. Ruled out: the product's
  operand orders, the conversion of the test and of the return in every helper, a temporary
  for the return, the axis copied inside the helper, a length variable per call (12 lines),
  and permute.py over every run of simple statements.
- **Both conversions are the compiler's qmfc2 (2026-11-09, w8).** The tie breaks only on
  priority: the length's chain must cost 15, which a compiler-made qmfc2 (a movti reload,
  cost 1) followed by an asm mtc1 (cost 1) gives and ToFloat's asm qmfc2 plus reload's
  movsf (cost 2, units memory and flop) does not. ToFloatNow and ToFloatViaBits also cost
  15, but their GPR is local-alloc's, so reload's round robin (retail's v0 at the test, v1
  at the join, and every later reload) shifts by one. The test needs the same pair: with
  ToFloat's reload mtc1 the flop unit is busy at its cycle, the uuu product waits a cycle
  and the lui of the fallback's address (priority 4 to its 3) goes first; ToFloat's test
  also moves the second length's lqc2 of vf5 before its c.lt.s. So retail converted the
  length with ToFloatMoved twice (player_path's NormalizeVector, ToFloat test and
  ToFloatMoved return, fixes the join but leaves those two swaps). Two ToFloatMoved reads
  make the length a TI_REGS pseudo in regclass (two "r" operands against the Sqrt's "=j"
  and DivX's "j": a tie, so the union) and global-alloc puts it in v1, with a qmtc2 back
  for the division. Diagnosed: one more VU0 operand on the length, `__asm__ volatile("#"
  : "=j"(d) : "j"(len))` after the join (no code), makes it VU_REGS and the function
  EXACT. Asm statements without outputs are not scanned by regclass (any number of `""
  : : "j"(len)` leaves TI_REGS). Retail therefore had one more VU0-class reference to each
  length than any form found, the wall func_00186230 hit too. Ruled out for it: Vec
  values for the length and its helpers (the inline copies are folded before regclass),
  the length as a u128 the caller converts (one variable for both calls or one each), a
  return in each arm (three "r" reads), `u128 len = Dot(v, v); len = Sqrt(len);` (one
  pseudo for both values, where retail has vf1 then vf2).

### An asm store issues beside an epilogue restore (func_001EDC08)

FindClosestPointsOnSegments went from 49 differing lines to 2 (2026-11-10, w12, `-dS -dl
-dg -dR -fsched-verbose-6` dumps):

- **Vec operands named in pairs fix two register cascades at once.** MulXSum4 over u128
  operands gave the weights and the first point the wrong VU0 registers, and in the same
  block local-alloc ranked `1 - v` (2 refs over 3 insns, 0.667) above the shared 1.0 (3 refs
  over 5, 0.6), so the 1.0 took f3, the second clamp's result (global) lost f3 and took the
  zero's f2 by preference, and the clamp's `c = 0` copy vanished (bc1tl where retail has bc1t
  with the copy in its slot). With the operands as Vu0::Vec values named weight before point
  (`Vec w0 = Vec::Scalar(s - 1); Vec a0 = Vec::Of(*p0); ...`, a Vec MulXSum4) sched1's order
  changes, the 1.0 ranks first (f2) and every FPR and VU0 register is retail's: one cause for
  what looked like a clamp written differently from the first.
- **A pointer local set before a test keeps its address in the test's block.** Retail's
  `lui/addiu v0` of the fallback vector come before the branch and its `lq` in the arm:
  `const Vec02* fallback = &g_unitXVector;` before the test (a TImode load cannot take a
  `%lo` address, so CSE leaves the pseudo). Haifa schedules one block per region here (no
  loops: find_rgns makes single-block regions), so no interblock motion does it.
- **An asm's sw has no function unit.** The epilogue's restores after `sw v0,0(s6)` are
  `lq s5, lq s6` in retail, the only such order in the executable: with a plain store (unit
  memory) at cycle 2, `lq s6` (anti-dependent, cost 1) is ready at cycle 3 and wins the tie on
  LUID. StoreX's asm sw issues at cycle 2 beside `lq s5`, so s6 comes a cycle later, as
  retail. StoreX with the test's ToFloatMoved gives the length two "r" operands against
  Sqrt's and DivX's "j": regclass's tie (TI_REGS, the wall above). ToFloatNow or ToFloat for
  the test with StoreX keep the length in VU0 but move the test's GPR (local-alloc's v0, or
  reload's mtc1 of latency 2). A Vec copy of the length for either use is folded by cse2
  before regclass (the copy survives cse1 and gcse).

## Stack slots

### An inline function's frame is one temporary of its saved size (func_00125138)

How the frame's locals get their offsets (function.c, stmt.c, integrate.c of GCC 2.95.3):

- **Locals are temporaries.** expand_decl gives a BLKmode or address-taken local
  `assign_temp (type, 1, 1, 1)`: a temp slot kept until its block ends, then free for
  reuse. assign_stack_temp_for_type reuses a free slot only of the same machine mode, with
  room enough; a bigger BLKmode slot is split. Strict aliasing is off in SN's 2.95.3 (an
  inline's frame slot, alias set 0, is reused by the next call's), so the alias set never
  blocks reuse. The frame grows upward from 0 in allocation order (MIPS does not define
  FRAME_GROWS_DOWNWARD).
- **Vec02 is BLKmode, Vu0::Vec is TImode.** Vec02's `aligned(16)` comes after layout chose
  BLKmode for four floats at 4-byte alignment; Vu0::Vec has a u128 member. A Vec02 declared
  after a block can therefore take part of an earlier BLKmode slot (an inline's frame); a
  Vu0::Vec whose address is taken never can, and gets a new 16-byte slot at the frame's end.
- **An inline call's frame is one BLKmode temporary of DECL_FRAME_SIZE.** rest_of_compilation
  saves an inline function's RTL straight after RTL generation, with its frame size then
  (save_for_inline_nocopy, DECL_FRAME_SIZE). At each call copy_rtx_and_substitute gives the
  first reference to virtual_stack_vars `assign_stack_temp (BLKmode, size, 1)`: all of the
  inline's locals move together, at their own offsets, and every call in a later block reuses
  the slot. So the frame shows the inline's own locals, used or not: an unused local
  declared in the inline still takes its bytes in every call's copy of the frame.
- **No unused 16-byte slot from the caller.** An unused BLKmode local in a block after the
  inline's block splits the free slot (no new bytes); one at the function's top is allocated
  first, at 0, and moves everything up; a scalar that purge_addressof puts on the stack comes
  last but has accesses.

func_00125138 (ComputePlacedObjectWorldFrame): retail's locals are 112 bytes, the product's
x, y, z at 0, 0x10, 0x20 and its matrix at 0x30..0x60, then 16 bytes nothing touches; the
direction (a Vec02 at 0) and Scalar's slot (0x10) of the later block reuse the product's slot.
The other rotation products' frames are 96 bytes. A Vec02 declared after the matrix in this
product's inline (its fourth row, never set) gives a 112-byte saved frame and the function
matches. The 0x60 slot is the inline's own, not the caller's.

The same function's parent pointer: one variable assigned in both arms of the first if/else
and in the else arm is one pseudo across all three lives, which global-alloc gives a0 (r206,
the else arm's row pointer, took v1 in local-alloc first). Retail's v1 in the first arm and
a0 in the else arm are two variables: the else arm declares its own `parent`.

### A by-value inline passed to a call: the call's return slot comes first (func_001DEBE8)

From calls.c and integrate.c of GCC 2.95.3 and the frames of func_001DEBE8 (2026-11-10):

- **expand_call allocates the return temporary before it expands the arguments.** For
  `rot = MultiplyByTransposedMatrix3x3(a, RotatedRows(m, a))`, the out-of-line call's
  hidden return slot (a 48-byte BLKmode temporary) is taken first; the inline argument's
  frame (its local `t` and its named return value `out`, one BLKmode temporary of its saved
  size) is taken while the argument is expanded, after it. Retail's frame shows exactly that:
  the result at 0xE0, the inline's rows at 0x110 and 0x140, the call passed 0x110.
- **Declared locals come in the other order.** `Mat02 p, q; RotateRowsBy(&q, ...); p = q;
  Mat02 r = Multiply(..., p);` puts p and q (declared at the top) before the call's slot, so
  the result lands after them (0x140) and the out-parameter product at 0xE0: same size, wrong
  offsets. Spot it: a call's return slot below an argument's rows means the argument was an
  expression (an inline returning by value), not a local.
- The call's slot is freed at the end of the statement, so a later Vec02 (the velocity at
  0xE0) and its Scalar slots (0xF0) reuse it.

### A local's size is the frame (func_00203FD0)

Sony's 2.9-ee-991111, like SN's 2.95.3, adds nothing to the locals' area: mips.c's
compute_frame_size takes get_frame_size(), the sum of the locals' slots, and rounds it to 16.
The three other callers of StartIopDma have exactly their records' bytes below their saves
(0x10 for one record in func_0018E7C0 and func_001F9AD8, 0x20 for command_channel's
`recs[2]`). SendPadDma (src/lib/pad.c) has 0x100, with its one record at 0: its local was
256 bytes. Ruled out, with dumps of the frame (2026-11-09):

- **A variable's alignment does nothing.** expand_decl allocates a BLKmode local from its
  size and then resets DECL_ALIGN to BIGGEST_ALIGNMENT, so `PadDmaTransfer t
  __attribute__((aligned(64)))` keeps a 0x60 frame.
- **A type's alignment changes its size.** `aligned(64)` on the record's typedef makes it 64
  bytes (a 0x90 frame); `aligned(256)` gives retail's 0x150 frame and the function matches,
  but nothing in retail asks for a 256-byte-aligned DMA record (the library's own DMA words
  and request buffer are 64-aligned in .bss).
- **No temporary or inline frame.** The function has no struct value, call returning a
  struct or inline call that could leave a 0xF0-byte temporary.

What matches, and is landed: a table of sixteen records (`PadDmaTransfer transfers[16]`),
of which the first is filled and `StartIopDma(transfers, 1)` sends one, as a sender written
for a record table of fixed capacity would. The failure message is a string literal in both
places (one .rodata copy, at D_0024F738, where the near miss's named global was).

The maintainer allowed this form (2026-11-09), and its limit matters: AGENTS.md forbids a local
that exists only to size the frame. A local whose size a retail frame proves is accepted only as
an array of the real record type, passed through the callee's real interface (a pointer and a
count), with the other callers' frames showing nothing else is padded. A byte array, a scratch
array of an unrelated type, an invented wrapper type or an alignment attribute is still not
allowed.

### Best fit places a later block's locals: a 16-byte frame difference far above (func_00125C90)

assign_stack_temp_for_type takes the smallest free slot of the mode that is big enough, splits
off the rest of a BLKmode slot, and otherwise makes a new slot at the frame's end; freed
neighbours are combined at each block's end (combine_temp_slots, always at -O2). So the
offsets of a block's locals depend on how far earlier, finished blocks pushed the frame's end,
not only on their own sizes and order: with earlier blocks reaching 0x120, a block declaring
an 80-byte ScaledTransform, a 64-byte Mat4A and an 80-byte one gets 0x50, 0xA0 and a new
0x120 (0xE0..0x120 is too small), where retail had 0x50, 0xA0, 0xE0. Retail's frame reached
0x130: the earlier block's rotation product is the 112-byte inline frame of the entry above
(MulRotationIntoWorld's unset fourth row, in the same file). Read a shifted block's offsets
as "which earlier allocation was bigger", and simulate the free list before adding locals.

### A by-value result's slot is a movable; an address passed once is not (func_00125C90)

loop.c (scan_loop) deletes a movable set once and used once in a loop with a call: it
substitutes the source into the use (reg_single_usage), so a local's `&world` passed to one
call stays `addiu a0,sp,N` in the loop. A call returning a struct by value into a temporary
(`*(Mat4A*)&ct = MultiplyMatrices(a, b)`, matrix.cpp's by-value product) uses the temporary's
address twice, as the hidden first argument and for the copy, so loop.c moves it to the
preheader and it takes a saved register (retail's s7). Retail's child loop nests the products,
`MultiplyMatrices(MultiplyMatrices(*xf, inv), local)`, with const Mat4A& parameters; the
two arms' calls share one jal only when their temporaries share an offset (cross-jumping
needs the copies into ct that follow them to be identical).

Still open there: retail moves d, a spilled u128 that PlaneSigns read through a reload into
vf6, to the first call with `qmfc2 a1,$vf6`; ours reloads it (`lq a1`). The argument move
`(set a1 d)` takes movti's memory alternative, whose source class is NO_REGS, so find_reloads
makes no optional reload and inheritance never sees vf6: retail must have had a second pseudo
in vf6 for the asm and the first call. d as Vu0::Vec, as a Vec02, through Vu0::Q, and an inline
helper taking d for PlaneSigns and the call do not give it.

### A pointer field's type picks its store's partner (func_002042C8)

Read from haifa-sched.c (priority, rank_for_schedule) and the `-dS -dl -dg -fsched-verbose-6`
dumps of OpenPadPort (src/lib/pad.c, 2.9-ee-991111, 2026-11-09):

- **A store's priority is its type's next store.** In a run of stores into one struct through
  separate address computations, a store's only dependents in sched1 are the later stores of
  its own alias class (an output dependence, cost 1): different symbols (the slots, the DMA
  words, the request buffer) never conflict there, and other types never do at -O2. So a
  pointer field's store has priority 2 when no later store has its type and 1 + the next one's
  otherwise, and that priority reaches back to the load of its value (the reply's word) and the
  address it is stored through, which decides sched1's order and so local-alloc's registers.
- **sched2 sees the same chains, with longer ones after reload.** After reload the bases are
  hard registers and every int store and load of the block conflicts, so the int stores form
  one chain to the return value's load (priority 4 for the last one), while a pointer store
  still only chains to the next store of its type. The slot's last stores (the DMA id `= 0`
  and the IOP address from the reply) tie at sched2 when the address is a `u8*` like the
  buffer's (1 + the buffer store's 3); its store then goes first on insn order, two instructions off
  retail. With an `s32`, every int store and the reply's load chain together and the load is
  issued two cycles early (nine instructions differ); with `void*` the address's store is a leaf, its load
  and address lose priority in sched1 and the registers change (20 bytes differ in the best order).
- **Retail's: the type of the DMA words' pointer.** With the address field and the reply's
  word typed `u32*`, the pointer type of the DMA words that the slot also holds, the address's
  store chains to the DMA pointer's store (a leaf: priority 3, so sched1's order and registers
  are the `u8*` ones) and in sched2 it ranks below the DMA id's (4): retail's code. It is the
  natural type too: SendPadDma adds the frame's offset to that address and sends the slot's DMA
  words there. Writing the stores in any of the 5,040 orders (tools/permute.py) never reached it
  with the other types: the order was right, the types were not.

### A stack record filled by an inline: only the constant-zero store loses the pointer (func_001A7800)

Read from integrate.c (expand_inline_function, try_constants) and cse.c (find_best_addr), with
the `-dr -ds` dumps of UpdateObjectCreator (src/main/file_19E040.cpp, 2026-11-09):

- **Retail's mark.** A local profile filled with three constants and passed by address: retail
  stores the first two fields frame-relative (`swc1 $f1,16(sp)`, `sw zero,20(sp)`) and the third
  through the register that also holds the call's argument (`addiu a1,sp,16`, `move a0,a1`,
  `swc1 $f0,8(a1)`). Written `ramp.f = k;` all three are frame-relative and the argument is made
  at the call (54 bytes differ); written through `RampProfile* p = &ramp;` the second store also
  goes through the pointer, which keeps it live past the `a1 = 0` argument move and moves it to
  `$v0` (17 lines differ).
- **CSE alone never mixes them.** find_best_addr returns at once for a frame-relative address,
  so a store written on the frame keeps it. A bare pointer address `(mem p)` is replaced by its
  class's `(plus fp 16)` (equal address cost, and the tie goes to the higher rtx cost), but
  `(plus p 4)` and `(plus fp 20)` cost the same both ways, so `p->endSpeed` keeps the pointer.
- **The inliner does.** A pointer parameter whose argument is a frame address
  (FIXED_BASE_PLUS_P) gets a pseudo with that address as its constant equivalent, and so do the
  constant float arguments. try_constants then substitutes every equivalent into each copied
  insn as one change group: all or nothing. The store of `3000.0f` and of `0.2f` cannot take an
  immediate (no SFmode store of a non-zero constant), so the whole group fails and the address
  keeps the pointer pseudo too; the store of `0.0f` is a valid `sw zero` with the address
  `(plus fp 20)`, so both substitutions stay. CSE then turns the first store's bare `(mem p)`
  into `16(sp)`, which gives retail's three addresses exactly.
- **The form.** A setter on the record, `void RampProfile::Set(f32 max, f32 end, f32 time)`
  (include/ramp_profile.h), called as `ramp.Set(3000.0f, 0.0f, 0.2f);`: the original filling
  its profile with one call. A free inline taking the record by pointer or by reference matches
  too. Spot it: in a record filled with constants, a zero store frame-relative among stores
  through the record's address register means an inline call's arguments.

### Reading a frame's slots back to the declarations (func_0019B378)

UpdateObjectGatherer's near miss had a frame 0x10 too large, its locals in other slots, and
nine versions of the scopes had not moved them. assign_stack_temp_for_type (function.c) explains
retail's layout once its rules are applied:

- **Free slots are reused newest first, and adjacent free ones combine.** The search walks
  temp_slots from the head (the newest slot) and stops at the first free slot of the same mode,
  size and alignment; free_temp_slots and pop_temp_slots call combine_temp_slots, which merges
  adjacent free BLKmode slots, and a larger slot is split from its bottom. So a 16-byte local
  placed when 0x20 to 0x50 is free lands at 0x20, and one placed while 0x20 is still in use
  lands in the newest free slot, not the lowest.
- **A slot created last was created last.** On the R5900 the frame does not grow downward, so
  offsets follow creation order. Retail's side index at 0x40, above the weights' slot at 0x30
  that is used after it, cannot be a local placed at its declaration. It is an `s32` whose
  address is passed (FindColliderFloorContact's third argument, `s32* out`: func_001BB290
  stores the contact's side there), and purge_addressof gives it its slot after every
  temporary. The near miss's `u8 floor[0x10]` record took 0x30 at its declaration instead.
  Check a callee's real out-parameter type before giving a local a size.
- **A slot reused after a block means the block ended.** Retail's list frame of state 4 at
  0x20, the push vector's slot, shows the push vector is not live there: it is declared in each
  case's `if`, not in the switch's enclosing block.
- **The tail written twice.** Each case's push written in full (state 1 with `f614 * 0.7f`,
  state 2 with `f618 * 0.5f`) instead of a `goto` into state 2's code: jump2's cross-jumping
  merges the two tails after reload from the first insn after the lift constant, which leaves
  the `lui` of g_unitZVector in each case's own block. Retail's branch into the middle of the
  other case's block (`b .L0019B76C`, past its speed and lift) is that merge.
- **What was left.** A clamp of a cosine to 0..1 with both bounds named (`f32 lo = 0.0f;
  f32 hi = 1.0f;`): retail loads 1.0 before the first test and branches on both. And the
  position named before the weighted sum that reads it (`u128 pos = Q(act->v140);`), so its
  `lqc2` comes before the Scalar's slot store (the two-pass argument rule, func_00191570). A
  method called through desc02() rather than a cast table, and an `if (any != 0)` written in
  retail's block order, finished it.

### A block's local slot taken by a Scalar's copy; a frame address named before a call (func_00158480)

func_00158480 (TurnMatrixBySpin) went from 86.6% to a match with three changes, each read from
retail's frame offsets and registers:

- **The weight's slot is the axis's.** Retail passes ScaleMatrix's scale as `mfc1 v0; por a2,
  zero, v0` with `sq v0, 128(sp)` in the call's delay slot, and 128 is the axis that
  TransformDirectionBetweenFrames fills in the `if`. Vu0::ScalarInGpr gives the mfc1 and the
  cast's copy (its `(s128)` temporary); declared at the function's top, the axis keeps its slot
  and the copy takes a new one (a 448-byte frame). Declared inside the `if`, its assign_temp slot
  is freed at the block's end and the copy reuses it (same mode, same size): retail's 432 bytes.
  A conversion written in C (`(u128)*(s32*)&f` into the axis) extends the int and costs three
  moves.
- **Locals declared where they are first needed.** With the axis in the `if`, the frame is in
  allocation order (it grows upward): the two matrices at the top, the axis, then the three
  declared after the `if`. Retail's 144, 208, 272 for the copy, the scaled matrix and the
  product mean they are declared in that order after the block (C++ declarations mid-block).
- **`&b` at each use, no pointer variable.** A `Mat4A* p = &b;` at the top makes CSE use p in the
  branch (`move a1, s2`); writing `&turn` at each use gives retail's fresh `addiu v0, sp, 64` in
  the branch and its copy to s2 in the call's delay slot.
- **A frame address in a saved register before a call.** Retail sets `addiu s1, sp, 208` (the
  scaled matrix) before MultiplyMatrices and passes s1 to ScaleMatrix after it. Written as
  `ScaleMatrix(&scaled, ...)`, the address is computed straight into a0 after the call: sched1
  does not move a pseudo's set above a call unless the pseudo already crosses one. Retail's
  register means the source named the address before the call: `Mat4A* result = &scaled;`
  above the MultiplyMatrices line, then `ScaleMatrix(result, ...)`. Placed after the call, the
  same pointer is propagated away (one use) and changes nothing.

### Ramp copies live through a tail: a goto over function-scope locals (func_001C54D0, near miss)

func_001C54D0 (a turning collider's contact push) had a frame 16 bytes short of retail's 208,
every frame offset after the ground push wrong, and 8 bytes too many. Read from function.c
(assign_stack_temp_for_type, combine_temp_slots, free_temp_slots), stmt.c (expand_decl) and
integrate.c (the inline frame's `assign_stack_temp (BLKmode, size, 1)`), with the -dr dumps
(2026-11-10, w13):

- **Retail's offsets, as allocations.** The ground push stores its difference at 0 and its
  Scalar weight at 32 (16 untouched bytes between); the push block stores two differences at 0
  and 16 and the ramp profiles at 32 and 48; the tail stores both weights at 64; the two
  out-parameters are at 80 and 84 (purge_addressof, after every expand-time slot). Every one of
  these is BLKmode (Vec02 and an inline's frame are BLKmode, the profile union too), so a
  later BLKmode request of 16 bytes takes any free slot: the tail's weight at 64 means 0..64 is
  still in use at the tail, and the profile at 32 reusing the ground push's freed weight slot
  means it was allocated after that block ended.
- **So the profiles are function-scope and declared after the ground push.** Declared in the
  else arm of `if (zero) push = 0; else { ... }` they are freed (and combined) at the arm's end
  and the tail's weight takes 0 (ours: 192 bytes). A function-scope declaration after the inner
  `if`, with the zero-push path jumping over it (`push = 0.0f; goto apply;`, legal since the
  locals have no initializers), gives retail's 208 bytes and every offset. The 16 untouched
  bytes of the ground push are the second difference vector, declared at the top with the
  first, which the ground push reuses for its own difference (C-style scratch locals).
- **Two copies of one address: an argument read first.** Retail's `addu a0,s3,s2; move a1,a0`
  (loads through a0, the store through a1) is the address expanded inside each memory reference
  (multiplication first) with the vector read into a named `u128 v = Q(c->end[e].v10);` at the
  block's top; `ContactEnd03* end = &c->end[e]` gives `addu a0,s2,s3` and one register. The read
  first also puts the load before the weight's computation, which gives the block's VU0
  registers.
- **A store of a vector's x from a GPR of reload's choosing.** The separation stored as bits:
  Vu0::StoreX (the compiler's qmfc2, a reload into a0 after the block's pseudos) where ToBits'
  own pseudo takes v0.
- **sched2's tie between profile loads and dot loads.** With the dots written before the
  profile copies (after them, the copies' BLKmode move kills CSE's knowledge of the
  differences and they are reloaded: 8 bytes), each dot's load ranks by its chain to the first
  call: an asm mtc1 (ToFloatMoved) costs 1, the compiler's (ToFloat's reload) 2, and the
  push's division waits for the call (anti dependence on $f0). Both conversions as
  ToFloatMoved give the dot loads priority 18 against the profile loads' 19, and the profile
  loads go first as retail's do; with either ToFloat one dot load ties at 19 and wins on its
  dependents count (six against five).
- **Still open: the tail's sched1 order.** Ours loads v640 first (its Vec::Of argument is
  expanded before Rotate's rows, so its LUID is lower), then rows 2 and 1 (their address
  pseudo has no known base, so they conflict with the weight-slot stores and have four
  dependents against row 0's two), then row 0, and puts the f63C weight's qmtc2 early as
  filler. The lalloc2 emulator gives retail's VU0 registers for row 0 first, then row 2, then
  row 1 (v anywhere before row 1), with the -push weight's qmtc2 early and the f63C one after
  the dot. Row 0 has to beat v at the first cycle (rows 1 and 2 wait for the addiu of the
  matrix's address); Vec or u128 forms, RotateMembers, RotateRowsTied over the rows, v named
  first, and ScalarAtValue or ScalarAtCall for the f63C weight do not give it.

### Which induction variable loop.c keeps: combine_givs' totals (func_001575D8)

func_001575D8 adds particles to chunks of six parallel arrays (this frame's position, velocity
and record, and a copy of each for the frame before). Retail walks the record array in one
register (`s0`, the positions and velocities at -0x580 and -0x2C0 from it, and `s0` itself is
FillMemory's argument) and the copy in another (`s2`, from `addiu a2, s1, 0x840` before the
loop). Ours folded everything into one register based on the positions. The -dL dump's "Sorted
combine statistics" line says why:

- **combine_givs keeps the giv with the largest total.** Each giv's total is its own benefit
  (+1 for a zero addend, `no_const_addval`) plus, for every other giv it can absorb, that giv's
  benefit + 3. A DEST_ADDR giv (a memory reference) can be absorbed by any giv whose difference
  is a valid address; a DEST_REG giv (a pseudo) only by an identical one. Written as
  `chunk->pos[k]` everywhere, CSE makes one `k*16 + chunk` pseudo for the top of the body and,
  after the ifs' join, a second one for the copy; each absorbs the other (identical) and so
  totals 9 more than the record pointer `rec` (182 against 173): the position register wins and
  `rec` stays a register of its own (an extra spilled giv, 12 bytes).
- **One pointer per array.** `Quad16* p = &chunk->cur.pos[k]; Quad16* v = ...; Quad16* rec =
  ...;` at the top of the body, used for every access including the copy, leaves no CSE pseudo
  after the join; `rec` (benefit 10 against p's 7+1) then wins and absorbs every memory
  reference; p and v die.
- **A copy through a pointer of its own.** `ParticleState* last = &chunk->prev;` before the inner
  loop makes `last + k*16` a giv whose addend is a register, not `chunk + constant`, so it
  cannot be combined with the record's: loop.c moves `chunk + 0x840` out and reduces a second
  register, retail's s2. Written as `chunk->prev.pos[k]`, get_inner_reference folds 0x840 into
  the constant offset and the copy joins the first register.
- **`while (a && b)`, not `if (a && b) do { } while (a && b)`.** The `while` is expanded with
  its test at the top and jump.c copies the whole exit test to the bottom (retail: both tests
  at the bottom, no jump into the loop); the do-while left a `b` into the second test (4 bytes).
- **The increments' order is the bivs' order.** `i++; k++;` (the counter of the inputs first)
  puts i's givs' initialisations first in the preheader, so `i * 16` reuses the `lw v1` of the
  entry test as retail's does; `k++; i++;` reloads i.
- **`x & 0xFFFFFFFE` is `lui; ori`.** An unsigned constant above 0x7FFFFFFF is not a SMALL_INT
  here; `~1` gives `li -2`.
- **A 32-byte record taken by index.** `ParticleExtra* x = &chunk->extra[k]; x->a = ..; x->b =
  ..;` gives retail's `addu a0, a0, v0` (base first); `chunk->extra[k].a = ..` repeated costs
  8 bytes, and the byte-offset form puts the index first.

## Shapes of large functions

What retail's larger functions showed the night of 2026-11-07 (func_001C61E0,
func_00146518, func_001CC818, func_0019ED58, func_00134B48):

- **An object's matrix is written through the object.** `MulRotation(&self->rot,
  ...)` makes the destination a pointer pseudo that PRE carries to the end of
  the function and spills; retail stores the rows through the object's own
  pointer (`o->rot = r` in a function taking the object).
- **A product's rows as values, in retail's load order.** Loading b's rows as
  values in the order retail's registers show (b0, b2, b1) gives its
  registers.
- **A struct-typed vector store lets loads pass it.** `*(Vu0::Vec*)&p = v` is a
  struct store, so a later load of a float global may be scheduled before it,
  as retail's is; a u128 store through `Q()` keeps the two in order.
- **The game clock through inline accessors.** Accessors taking the clock's
  address (`ClockDt(const LinkClock*)`) give retail's form: the high part in a
  saved register and `addiu sX, sY, %lo` per use; a plain field read folds the
  offset into the address and costs a saved register.
- **Normalising in place.** An inline that normalises a vector in place,
  taking the fallback by reference, loads the fallback's address before the
  difference, as retail does.
- **A fallback's address in the block before the test.** Where retail forms a
  fallback vector's address (`lui; addiu`) among the length's VU0 code and
  only its `lq` in the short arm, the source named the address first: `const
  Vec02* fb = &g_unitXVector;` before the length, then `dir = *fb;` in the
  arm. The pointer is a pseudo set where it is written, so its two insns stay
  in the earlier block and sched1 puts the `lui` first; `dir =
  g_unitXVector;` expands the address inside the arm (func_001DF700, as
  func_0016D490 does with its `fb`).
- **A vector's three floats in a loop.** Two pointers indexed by i (`cur[i]`,
  `vel[i]`) give retail's induction variables; separately incremented
  pointers do not.
- **A list's head read through the walk's frame.** `*(T**)frame.list` keeps the
  read after the frame push; `self->children.head` is scheduled before it.
- **Case blocks in retail's order, with labels and gotos where its blocks are
  shared or entered sideways** (func_001C61E0's states 1 and 2 sharing one
  call and falling into case 0, state 3 jumping into cases 4 to 7).

- **A variable for each live range.** One variable reused across separate
  live ranges (two loops, three calls) is one pseudo for global allocation and
  loses the argument-register preference; a variable for each range gives
  retail's a0/a1 (func_001A3D40, func_001CE800). Where retail keeps one value
  in one register across the ranges, the reverse holds: one variable.
- **An inline clamp loads its bounds before each test** (ClampBetween with early
  returns), which keeps a preceding store out of the branch's delay slot
  (func_001796D0, func_001B4330).
- **A product inside an inline function is not CSE'd** with the caller's
  identical product: retail's second multiply (func_0013F1D8).
- **One nested expression forms the destination first.** `Q(d) = F(..., G(Q(d)),
  ...)` forms d's address before G's test, as retail's early `move a1, sp`
  (func_00198BD8).
- **MinF/MaxF with the constant first.** `a >? b` / `b <? a` in an inline
  called with the constant first gives retail's constant-first operand and
  result register (func_00141F48, func_0017FB78).

- **A two-node switch needs a third case for retail's tree.** With two case
  nodes the tree stays lopsided, the lowest as its root; retail's range-rooted
  tree needs a third node, an extra `case N: break;`, whose test jump.c then
  removes (func_001733B8).
- **A struct-typed store keeps a frame-held pointer from being reloaded**, by
  the scalar-against-struct rule of "Reloads and stores" (func_00185D20's
  second end, stored as `*(Vu0::Vec*)&...`).
- **A rotation product writing straight into the caller's rows**, through an
  inline with shared vector locals and no matrix local, gives retail's frame in
  the rotation family (func_00172078, func_001A3730): a candidate for
  include/mul_rotation.h.

- **A store at the local's own address.** Vu0::Q and Vu0::Set both take the
  local by reference; after inlining, its address can sit in a pseudo that CSE
  reuses for a later `&v` passed to a call, costing a saved register and 16
  bytes of frame. `*(u128*)&v = x` at the use addresses the frame directly, as
  retail's fresh `addiu a1, sp, n` shows (four functions of the size pass).
- **A matrix's rows read as a struct alias the stack temporaries.**
  `*(const Vu0::Vec*)&m.r[i]` makes stores to stack temporaries alias the rows,
  which brings back retail's reloads of the rows after each product (the
  scalar-against-struct rule of "Reloads and stores").
- **Block-local variables per switch case.** A function-scope variable shared
  across cases ties each case to one register; retail's per-case registers come
  from variables local to each case.

- **A global assigned a call's converted result forms its address first.**
  When the global's type differs from the call's return type (a conversion
  around the call), its address is formed before the call, so the high part
  crosses the call and sched1 hoists it into the prologue: retail's early
  `lui sN` for stores of call results (LoadWorld, func_001DCEA0).
- **A constant as a Vec value can be hoisted.** `Vec::FromFloat(c)` becomes a
  pseudo that loop.c can move into a saved GPR, where `Vu0::FromFloat(c)`
  folds the constant into the asm (func_00157B88).
- **One Vec value stored twice gives the compiler's vmove** between two VU0
  registers (func_001CAB10).
- **Stores of constants to globals: source order picks the registers, the
  callee's return type the order.** With `-G0` every store to a global is a
  `lui` of its own high part and a `sw` (ResetScreenResources, func_001B40C8).
  sched1 hoists all the `lui`s of a run of such stores, in source order, and
  keeps the stores in source order. local-alloc then gives the high parts
  their registers in the order of its priority (local-alloc.c `QTY_CMP_PRI`:
  references over lifetime, the shorter lifetime first, ties by birth order),
  each the lowest free register of v0, v1, a0... (those of a call's arguments
  are taken while live). So the first store of the run gets v0, the second v1
  and so on: retail's registers name its source order (v0 first), which for
  func_001B40C8 is the order of the globals in .data. sched2 then issues the
  independent `lui`s and stores by priority, then by how many later insns
  depend on each (`rank_for_schedule`: more first), then by sched1's order. A
  register a later call clobbers adds the call and what follows it to its
  `lui`'s dependents, unless the call *sets* the register: a call declared to
  return a value sets v0, which cuts v0's `lui` off from everything after the
  call and sends it (and its store) last, into the call's delay slot. That is
  why ResetScreenResources needs FillMemory (func_001F5C0C, memset, which
  returns its pointer in v0) declared `void*`: declared `void`, the store of
  v0's global came first. A `void` declaration of a value-returning callee
  changes the caller's schedule even where nothing reads the value, as it
  changes its registers (docs/AGENT_WORKFLOW.md, `tools/decls.py`). To read
  retail's order: list the stores by the register of their `lui` (v0, v1, a2...,
  skipping the argument registers of the call that follows) and write them in
  that order; then fix the callee's return type for the delay slot. Dumped
  with `-dS -dR -dl -fsched-verbose-5` (the `sched2` dump lists each insn's
  priority and dependents). func_00203548 (libcdvd) has the same shape, but
  the 2.9-ee-991111 compiler interleaves its stores with the call's arguments
  so that lifetime, not order, decides two of its registers, and the function
  is blocked by its volatiles anyway.
- **The memory and string routines return their pointer.** The same return
  value matters after any call: FillMemory (memset), CopyBytes (memcpy),
  MoveMemory (memmove) and CopyStringBounded are original assembly that
  returns the destination in v0, and EnableInterrupts, WaitGsPaths and
  DefineClearPacket return a value too. Declared `void`, a value loaded right
  after the call takes v0 where retail's takes v1 (func_001A2E68,
  func_001CAF38 after FillMemory, func_001790B8 after MoveMemory: all three
  matched once declared `void*`). Every declaration in src/ now says so.
  `tools/decls.py` cannot see it, since no caller reads the value and the
  callees have no C: an original-assembly function that writes v0 in its
  return's delay slot is the evidence.
- **Open: constructor stores kept in source order.** In func_001D5FA8,
  func_001D61C8, func_001D60B0, func_0018A510 and func_001930B8 (a static
  record built by FillMemory and an inline constructor), retail keeps the
  field stores in source order and loads each constant late enough to reuse
  a register (75.0 into -100.0's f0), as if each store depended on the one
  before. Stores through one base register at different offsets never
  depend on each other (alias.c, `memrefs_conflict_p`); only volatile, a
  different base pseudo or a mix of `this->f` and the global's own name
  makes them, and volatile alone does not give retail's registers. The
  return types above do not change them.

  What is now settled (2026-11-08, worked on func_001D5FA8, dumped with
  `-dS -fsched-verbose-5`):
  - **sched2 and the allocators are not the difference; sched1 is.** Built
    with `-fno-schedule-insns` (a probe only: player_request.cpp needs
    sched1, 16 of its 21 matched functions differ without it), an
    explicit-guard copy of the function whose locals put the insns in this
    order compiles to retail's sequence but for two registers (-1 and the
    guard's 1 swap v0 and v1): the constants 5.0, 1.0, 0.5 and -100.0
    loaded first, then the stores f44, f4, f40, f8, i28, f34, i48, the load
    of 75.0, i68, the guard, f50, f60, f54. That order is what retail's
    sched1 put out, and local-alloc then gives retail's f0/f1/f2/f3/f0.
  - **What sched2 does with it.** After reload the record's base is s0,
    which is set twice in the function, so alias analysis knows no base for
    it, and a store through a `%lo` address (the guard; a field at offset 0
    such as func_001D60B0's i0, stored as `sw v1,%lo(cfg)(s2)`) conflicts
    with every store through s0: those stores are barriers in sched2, and
    the stores between two of them keep sched1's order. A store whose
    register a later constant reuses is pulled first (f44 before 75.0 takes
    f0; f4, f24 and f44 in func_001D60B0; f20 before -1.0 in
    func_001930B8), so the "source order" the near misses are written in is
    partly sched2's, not the original's.
  - **Why sched1 does not give that order here.** Pre-reload the stores are
    independent (one pseudo base with a REG_EQUIV of the symbol) and every
    constant load outranks every store (priority 4 against 2), so all five
    float constants are loaded first (75.0 cannot then share -100.0's
    register), and the stores come out by `INSN_REG_WEIGHT` (+1 for any
    SET, -1 per REG_DEAD or REG_UNUSED note) before insn order: the store
    where the base or a constant dies, and the guard store (two deaths),
    go first. A full chain of dependent stores (the volatile probe) gives
    the stores' order and the late 75.0, but interleaves the first loads
    with the first stores, so local-alloc reuses f0 for 1.0 where retail
    has four registers live. Retail's order needs the first stores not
    ahead of the loads and the later ones chained: no plain C form found
    gives that.
  - **Ruled out besides the above:** an inline setter per field (through a
    pointer), a constructor taking the values as parameters, memset
    declared and called instead of FillMemory, an aggregate initialiser
    (store_constructor clears with memset and stores the fields, but
    through a temporary that is then copied), a label between the stores
    (jump deletes it before sched1), `-g`, one local reused for -100.0 and
    75.0 (it shares the register but the stores still sort by weight), the
    record's fields mixed between `p->f` and its static's name (CSE gives
    them one base), and the constants set before the FillMemory call (CSE
    and the scheduler give the same code). func_001F7BE8 is a libkernel
    function built by 2.9-ee-991111 and was not taken further.
  - **What retail's sched1 order must have been (func_0018A510, 2026-11-09,
    `-dS -dl -fsched-verbose-6`, alias.c read).** In sched2 the two stores
    through a `%lo` address (the field at offset 0, `sw v1,%lo(cfg)(s2)`,
    and the guard) are barriers for every store through s0, so retail's
    sched1 put out the stores as A = {f4, f24, f44, f34}, then i0, then
    B = {f8, i28, i48, i68}, then the guard, then C = {f50, f60, f64, f54}
    (each group's inner order free). func_001D5FA8 has the same shape
    without an i0: its guard also splits off {f50, f60, f54}, the last
    stores of the constructor. Here, before reload, the constructor's
    `this` is one pseudo set once from `(lo_sum hi cfg)`, and CSE gives that
    set a REG_EQUAL of the symbol, so init_alias_analysis knows its value:
    i0's `(lo_sum hi cfg)` (combine folds offset 0) and every `this+N` are
    told apart, and nothing orders the stores. Probes (not plain C) that
    take the pointer's value away show what each property does:
    - pointer with no base at all (an empty asm on it): i0 and the guard
      both conflict with every store, so A comes out right (all four
      constants loaded first, 1.0 into 5.0's f2 after f4's store, retail's
      f0-f3), but the guard is last;
    - pointer with cfg as base but no known value (`this + off`, off from
      an asm): i0 alone conflicts, A and the late loads come out as retail
      has them (100 and 50 swap f0/f1), and after i0 the stores sort by
      INSN_REG_WEIGHT, so the guard (two deaths) goes second, not after B;
    - every field volatile, in retail's group order: one chain, the guard
      last, and the first loads interleaved with the first stores.
    So retail needs the stores before the guard chained (or otherwise
    given priority) and the C stores free, with i0 a barrier after A; no
    form tried gives that, and the plain forms all give `this` a known
    value. Also ruled out: one variable reused for 5.0/1.0, 100/75 and
    50/-100 (retail's register pairs; the anti-dependences pull 5.0's
    store first and push 0.5 late), and a zeroing base class with
    sub-records whose constructors set the colours (an empty base shifts
    the fields).
  - **The guard's place and the late constant, reproduced; the order inside
    the groups is not a weight sort (func_001D61C8, 2026-11-09).** g++
    2.95's expand_static_init (cp/decl.c) always emits `guard = 1` after
    the whole constructor, so in the RTL the guard store is the last store.
    A probe (not plain C: an explicit guard, the record through a pointer
    hidden by an empty asm, `guard = 1` written between i68 and f50) gives
    retail's guard position, 25.0 loaded after i48 into -100.0's f0, and
    retail's first four loads (18 words differ, against 21). What is left
    is the order inside the groups: sched1 sorts the free stores of a
    group by INSN_REG_WEIGHT, and sched2 keeps that order. Retail's group
    before the guard is f44, f4, f40, f8, i28, f34, i48, i68, which no
    source order gives as a weight sort: -1 (`lui; ori` into one pseudo,
    stored by i48 and i68) dies at whichever of the two comes last, giving
    it weight -1, so it sorts ahead of f8, i28 and f34 (weight 0). So in
    retail's sched1 the stores of that group were not all ready at once
    with equal priority: they had dependences (or sat in separate blocks)
    that this compiler only gives with volatile. Two further mechanisms
    checked and ruled out as the source of the late loads: local-alloc's
    update_equiv_regs moves a constant's set next to its single use only
    for a pseudo live across blocks (`REG_BASIC_BLOCK < 0`), and a pseudo
    set twice from `(lo_sum hi cfg)` loses its base (alias.c, record_set),
    which makes the guard conflict with the stores but needs a variable
    the original would not have reassigned.
  - **What retail's order needs, in sched1's priorities (static-record
    research, 2026-11-10, all four static records, func_001EC190 and
    func_001930B8; `-dS -fsched-verbose-6`, haifa-sched.c and mips.h
    read).** A float constant's set is a memory-unit insn of cost 2; a
    store with no dependent has priority 2, so its constant has 4. An
    output or anti link costs 1 (mips.h's ADJUST_COST zeroes it and
    insn_cost raises it to 1). In every case retail loads a constant only
    after some earlier stores (1.0, 75 and -100 after f4, f24 and f44 in
    func_0018A510; 75 after i48 in func_001D5FA8; -1.0 after -0.5's store
    in func_001930B8, whose constants reuse $f0 as local-alloc can only
    give them that way): a ready constant of priority 4 waits behind a
    store only if the store has priority 4 or more, which needs a chain of
    two links after it (store, then something of priority 3, then
    something of 2). Ties at equal priority go to the smaller
    INSN_REG_WEIGHT, which counts every SET (stores too) as +1 and each
    REG_DEAD or REG_UNUSED note as -1, then to the earlier insn. Stores
    through one pointer whose value alias.c knows have no dependents at
    all, so every plain form tried gives all constants first.
  - **The guard needs more than a conflict.** A probe (not plain C) with
    func_0018A510's A and B stores through a copy of `this` hidden by an
    empty asm (no base) and C through `this` gives retail's three groups
    A, i0, B and retail's late loads (A has priority 5 through i0, B 3
    through C). The guard then still lands after f54, not before C: the
    last C store in RTL order is where `this` and 1.0 die (weight 1 - 2),
    which ties the guard's (its 1 and its `%hi` die) and wins on the
    earlier insn. So retail's guard ahead of C also needs the last C store
    to kill one register fewer, or C not yet ready when the guard is.
  - **Ruled out tonight (all give the base's fully independent stores).**
    The record as sub-records (`Entry e1, e2, e3` members, fields
    through `e1.f4`); C's two pairs set by an inline `Pair::Set(x, y)` on
    members; the static inside an inline accessor
    (`inline Cfg* GetCfg() { static Cfg cfg; return &cfg; }`, its guard
    and record unchanged); a reference bound to the static. In each, an
    inline call's `this` is substituted as `(plus this N)` (integrate.c
    copies a non-readonly parameter into a pseudo, CSE folds it back), so
    one pseudo with a known value addresses every store. In a block with
    no call or branch the only plain sources of a store's dependents are
    a memory conflict (a base or value alias.c cannot see) and a register
    reused after the store (a reassigned variable, or a PRE copy such as
    the `(set r149 r149)` of `%hi(cfg)` GCSE leaves in the init block,
    which gives i0 one anti link of cost 1, too short). func_001930B8 has
    the same requirement on frame stores, so the missing form is common
    to the file-scope initialiser and the function-local statics.

  - **func_001930B8, the static initialiser (2026-11-10, `-dS -dl -dg`,
    local-alloc.c read).** Its two records go to a stack temporary that a
    `movstrsi` loop copies to the global, so every store is frame-relative
    and sched2 is free to reorder them; only the registers carry sched1's
    order. Retail has -0.5 (f20) and -1.0 (f74) both in $f0, and 1000,
    1200, -1750, 0.5, 2.0, 1.0 in $f5, $f2, $f1, $f3, $f4, $f6. Read
    backwards through local-alloc (QTY_CMP_PRI, ties by qty number, the
    fake birth and death one insn wider when sched2 runs), that needs
    -0.5's store before -1.0's load in sched1's output, and -1750's life
    shorter than 1200's, 1200's than 0.5's and 2.0's, and 1000's the
    longest of the single-use constants. In sched1 every constant load
    (priority 4) outranks every store (2), so with independent stores no
    source order can give it. A 40-line emulator of the allocation
    (build/swarm/w10-1930B8/emu.py, rsearch.py in the g7 worktree)
    confirms both directions: sampled schedules with -0.5 stored first and
    -1.0 loaded after it reproduce retail's eight registers, and none
    where all loads lead.
    - **One variable for -0.5 and -1.0 cannot be it.** Reusing it gives
      the anti-dependence that makes sched1 store -0.5 first and load
      -1.0 late (retail's instruction order but for f8, 26 lines differ
      against 33), but the variable then has two deaths, so global-alloc
      places it after local-alloc has given $f0 to a constant live across
      it ($f6 here). The emulator with the variable global finds no
      schedule at all that gives retail's registers.
    - **Written as the file's real static initialiser** (inline functions
      returning each record by value, `static Blk05 D_00604700 = MakeA();`,
      checked against the generated `__static_initialization_and_destruction_0`)
      the code is the near miss's exactly: the first record exact, the same
      34 lines in the second. An aggregate initialiser instead stores the
      fields straight into the globals (no temporary, no copy loop): not
      retail's form.

## Constants in one very long block

func_00109488 (FillObjectPropertyTable) is 9,348 instructions of stores of
constants with no call and no branch: one basic block. How GCC 2.95 gives
such a block its registers (2026-11-08, `-dl -dg` dumps, global.c,
reload.c and reload1.c read):

- **CSE starts over every 1,001 insns** (cse_basic_block), in both passes,
  so a constant gets a new pseudo in each window (nonmatching/func_00109488.cpp
  has the landmarks).
- **sched1 runs constants ahead of their stores.** A constant's set depends
  on nothing, so the list scheduler issues it in any free slot, and the lead
  grows along the block: the 4 of entries 142-237 is set at entry 79, the 18
  of entries 656-750 at entry 235. Retail's births are the same (its `li t8,4`
  is at entry 79), so this is not where the two differ.
- **local-alloc places the pseudos by priority** (`floor_log2(refs) * refs /
  lifetime`), each in the lowest register free over its whole life; a pseudo
  it cannot place goes to global-alloc. In one long block most do: 1,865 of
  2,068 here.
- **global-alloc evicts a whole register.** When an allocno finds no free
  register, find_reg scans the registers from the end of the allocation
  order and takes the first whose local pseudos have fewer refs per insn of
  life (summed over the function) than the allocno, unassigning every
  pseudo in it. The other allocnos still record conflicts with the evicted
  pseudos, so nothing else ever gets that register: here s1, s3, s5 and s6
  each hold one pseudo, and retail's s3 holds only 4 (entries 0-89).
- **reload takes the cheapest register per insn.** order_regs_for_reload
  prefers, for each insn, the registers with no live pseudo in allocation
  order, then the fewest refs of live pseudos. Ours ends with s1, s3 and s6
  as the reload registers (about 270 sets each), retail with t9 and s1, then
  s4, s8, t8 and s2.
- **A constant reloaded is looked for in the last register set to it.**
  find_equiv_reg (reload.c) walks back to the nearest insn that sets any
  hard register to the constant and returns nothing if that register has
  changed since; it does not look further back. So a constant held in a
  register that nothing else takes is reused to the end of the block (ours
  stores every 4 from s5), and once a later pseudo of it is given a register
  that is then reused, every reload of it is rebuilt (retail's 24 `li 4`
  after entry 237). Merging Set10's three equal arguments (one argument
  stored to fC, f14 and f18) gives the window-2 pseudo of 4 t8 in local-alloc,
  as retail has it, and retail's exact count of `li 4`; in this file's form it
  loses t8 to the 18 born at entry 235, whose life overlaps its last 35
  insns, and t9 to the 4242 born at entry 169.
- **A pseudo local-alloc could place is not always placed, and placed is not
  kept.** Its priorities and lifetimes are in its own numbering, and with
  INSN_SCHEDULING it retries a qty with a lifetime one insn longer at each
  end. A register that a model built from the `.lreg` lengths shows as free
  can therefore still be refused. After local-alloc, global-alloc's
  eviction and reload's spills can take the register back. Only the final
  code says whether a constant kept its register.
- **The constants are coupled.** In searches on func_00109488
  (build/swarm/big-109488/dsearch.py), Set10 merges on a few calls kept 8
  of the 10 window landmarks once Set8m calls were unmerged to make up the
  count. Each Set10 merge takes two insns from the `.jump` count and each
  unmerge adds one, and the landmarks before entry 553 allow a net -1 to +7.
  With the window-2 4 placed, `li 4` went from 1 to 24-40 (retail has 24).
  But func_00155778 then went from +7 to +16, 0x880 to +8 and 6 to +7. The
  distance in per-value build counts (the sum over values of
  |ours - retail| builds) was 107 at best, against 89-90 for the near miss
  that keeps 4 in s5. Freeing one constant's register re-permutes the rest.

What decides the bytes is therefore which handful of long-lived constants
local-alloc places, which follows the number and lives of the pseudos at
each point, that is the source's argument and statement shapes, and through
the CSE windows the instruction counts before each window edge.
func_00109488 has no call, so no callee's return type is involved.

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

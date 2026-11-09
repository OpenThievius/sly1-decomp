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
  the arguments written inline are expanded in another order than retail's; a
  named start point gives its registers. A tie ("+j" or "0") on a instead raises
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

### A global array's element is not a scalar (func_001CDB70)

An element of a global array (`D[0]`) is MEM_IN_STRUCT_P like a structure's member, so
fixed_scalar_and_varying_struct_p does not separate its load from a store through a pointer.
ComputePlayerLinkPose's `BuildAxisAngleMatrix(&g_unitXVector, D_00274DD8[0], rotB)` had its lwc1
of the angle after the three `*rotA = r` stores (through a Mat02 parameter), five insns later than
retail; read as `float D_00274DD8` the load moved above the stores and the function matched. The
label's second word is 0, the padding before the array D_00274DE0 that the MIPS DATA_ALIGNMENT
puts on an 8-byte boundary, so the scalar gives the same .data. A two-word label whose second
word is 0 and never read, followed by an array at an 8-byte boundary, is a scalar.

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
- Still open in the same function: global-alloc's ranking puts the animation (13 refs over 84
  insns, 0.464) before the player it is read from (4 over 34, 0.235), and find_reg's pass 0
  gives it $s0; retail's registers need the player (or the marker `to`, 6 over 39) first. No
  plain source changes these counts: cse folds every way of naming the player into one
  pseudo, and copies of the animation fold away (nonmatching/func_001C9DE0.cpp lists what is
  ruled out).

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

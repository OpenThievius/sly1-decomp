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
  FromFloatAt passes the float's bits, which the compiler loads with lw.
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
  listing the last vector first: retail's result takes its register
  (func_00198BD8). A weight read from memory is ScalarAt: FromFloatAt into
  Scalar's slot, the lw retail has (func_00198BD8's two, func_001D4698's speed).

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
  func_001A6788's `min.s f1, f0, f1` (two values) is still a near miss.
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
  but no function that has it matches yet: in func_00141D88 retail's store and length
  use the copy where NormalizeOr's one vector is used for both.

The sequences still without a helper: a float stored as a quadword (func_00191AC8,
func_00118CF0: mfc1 once into a saved GPR, then per use a copy (`daddu`) and sq,
read back with lqc2; an asm `sq` of an "r" float gives the sq straight from the saved
GPR, without the copy). The rest have helpers: the Q-register forms (Sqrt, DivX,
Length, NormalizeOr), the matrix forms (Transform, Transform4, RotateRows and
RotateUntied, RotateTransposed, MulTransposed, Transpose), the weighted sums (MulXSum,
MulXSum3, MulXSum4, MulAddX, MulAddX2), the dots (Dot, DotXY), the view test
(PlaneSigns, Ones), the cross product, Min and Max, the copy (Copy), and the GPR forms
(ToFloatMoved, ToFloatY, ToFloatZ, FromFloats, Splat, ToBits). The assembler takes
`vsqrt` (the disassembler prints it as a `.word`).

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

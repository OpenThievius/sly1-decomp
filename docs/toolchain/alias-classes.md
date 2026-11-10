<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Alias classes in the schedule

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
- What else was read for the same copy (2026-11-10, alias.c, expr.c, stmt.c, function.c and
  haifa-sched.c), each ruled out:
  - *A base for the loaded pointer.* find_base_value gives a register loaded from memory no
    base (only arguments in the copying block do), and canon_rtx has no known value for it
    (reg_known_value comes from REG_EQUAL or REG_EQUIV notes), so base_alias_check cannot
    separate `row->head` from the frame store; only the flags can.
  - *A scalar store from a cast.* expand_expr's INDIRECT_REF sets MEM_IN_STRUCT_P for an
    aggregate type, or the address of an aggregate, and never MEM_SCALAR_P, so no form of
    `Q(acc) = ..` (Vu0::Set, the template Q, a struct copy) gives the store a scalar flag.
    MEM_SCALAR_P comes only from a non-aggregate decl's own memory (expand_decl puts it on the
    stack only when TREE_ADDRESSABLE is already set, which g++ 2.95, expanding as it parses,
    never knows at the declaration; later the address gives an ADDRESSOF, purged after the
    weight slots exist), from put_reg_into_stack at purge time, and from temporaries. A
    promoted-mode variable would go to the stack at once, but TImode is not promoted.
  - *sched1's other levers.* The load's destination is a temporary that dies at `->head` and
    the row is set more than once, so birthing_insn_p does not raise it. The copy is a store:
    its weight is at best 0 (down live after it), never above the load's +1. The two loads
    cannot hold the copy between them by an anti dependence: `self->contacts` has self's
    argument base, which never conflicts with a frame address.
  - Probes: acc as a plain u128 (ToFloatZ for the test) leaves the sum in vf3 for the loop,
    with a caller save around PopBackMemoryMark (58 lines); with `((f32*)&acc)[2]` the frame
    is 160 and s5 is used (200 lines); down as a Vec02 in memory (`acc = down`) moves the
    count loop's registers and the slots (128 lines).

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

### Three of file_1D62E0's near misses closed by known levers (func_001D6DD8, func_001D9AC8, func_001DA320)

Wave 14 (2026-11-10). None needed a new mechanism; each was a lever above applied where the
near miss's notes had stopped.

- **func_001D6DD8 (StepStandIn): the quadword product as an inline.** Written with the four
  helper calls (StoreFloatAsQuadword, CopyQuadword, ScaleQuadword, StoreQuadword) at the call
  site, `&q50` and `&q60` were call arguments, so CSE and PRE made each one pseudo that lived
  across the helpers in s2 and s4 (20 bytes longer). Retail forms both again with `addiu` at
  each use: they are the parameter of an inline, substituted as a constant (integration, above).
  agent.cpp's `StoreScaledQuadword(dst, k, p)` is that inline; with it the size was retail's.
  Then: the clamp is ValueRange::Limit (its own result variable: `mov.s $f20` in each arm), the
  two weights are `Vu0::ScalarAt(D_x)` (retail's `lw` into a GPR for the qmtc2), the steer calls
  take `&q60` directly (one pseudo, set into a4 and copied to s3 as retail does; a `Vec02* c`
  variable set s3 first), and StepCollider takes the step `t` it reads in $f12.
- **func_001D9AC8 (ProcessPathFollowerContacts): `Vu0::ScalarAtCall` in a loop.** The two
  weights were `Slot k; Q(k) = FromFloat(D_x)` (lwc1 and mfc1, 12 bytes longer). ScalarAt's
  reference hoisted both `lui`s out of the loop into saved registers (s6, s7); the by-value
  ScalarAtCall keeps `lui; lw` at the use, and the two slot stores land as retail's.
- **func_001DA320: a reread generation counter, a store order and a flag from an inline.**
  `s32 cur = self->f6A0;` kept an extra pseudo that took s1 ahead of self in global-alloc;
  writing `self->f6A0 + 1` at both uses, and the slot's `f0C` stored first (before the two
  vectors, `v20` then `v30`), lets CSE reuse the one load (retail's `move a0,v0`) and gives
  self s1. Retail's replace test sets a flag (`li v0,1` ... `bc1fl; move v0,zero; beqz v0`)
  only on the path that compares, with the first test branching straight to the stores: an
  inline function's result (`IsLowerAlong(a, b, axis)`) inside `if (x != n || ...)`; the same
  comparison written in the `if`, or a `replace` variable, branches on the FPU flag or tests
  the flag on both paths. The mesh object `self->fB4C` is read at each use (retail reloads it).
  The last instruction, `lwc1 $f12, 0x3CC(a0)` where ours read `(s0)`, is AddMeshContacts'
  parameter order: declared `(Collider* a, f32 radius, ...)` the move to a0 comes before the
  float's load, and CSE takes the base from a0. Every other caller (agent.cpp, file_1F2758.cpp,
  player.cpp) and the definition (collider_contact.cpp, which never reads the float) match with
  that order, so all now declare it.

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

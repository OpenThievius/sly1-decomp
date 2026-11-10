<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# CSE

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

### A dead compare left by reorg: equal arms, and the join forgets memory (func_0017FB78)

Read from jump.c (delete_jump, delete_computation), reload1.c (reload_cse_regs), reorg.c and
local-alloc.c (block_alloc's widened lifetimes) with `-ds -dG -dl -dg -dR -dJ` dumps and the
`-dp` assembly (2026-11-10, ComputePlayerJumpVelocity, src/main/file_17D248.cpp). Retail's tail
is `lq; li v1,3; sq; swc1 $f0,8(a1); lw v0,0x2220(a2); lwc1 $f1,0x158(a2); lwc1 $f0,8(a1);
max.s`: a dead constant, a dead load, and out->z read back right after it was stored.

- **The dead pair is a compare whose branch reorg deleted.** The source is `out->z = z; if
  (self->f2220 == 3) out->z = z; else out->z = z;` (the arms equal). reload_cse_regs deletes
  the then-arm's store (the fall-through keeps its record that 8(a1) holds $f0; the else arm
  starts at a label and is kept); jump2 inverts the branch over the else store; reorg finds
  that store redundant with the one before the test, deletes it and then the branch to the
  next insn, and never deletes what set the branch's operands. The sched2 dump still has the
  store and the branch; the `-dp` assembly does not.
- **Other forms lose the pair.** An `if` without an else (`if (s == 3) out->z = z;`) has its
  store deleted by reload_cse and its branch by jump2's delete_jump, whose delete_computation
  deletes the load and the constant too. A mode test (`f224C`) held in a local dies earlier.
- **The join forgets memory.** At the if/else's join label (two uses) CSE starts with no
  memory, so out->z is loaded again for the max. With the max inside each arm instead, CSE
  forwards the stored z in both arms (the fall-through arm is in the same extended block, the
  else arm is followed by `-fcse-follow-jumps`) and z stays in $f1 (204 bytes, not 200).
- **Registers by widened lifetimes.** block_alloc first tries each quantity's life widened by
  one insn at each end (INSN_SCHEDULING). With only the copy before the test and the z store in
  the arms, sched1 issues `li 3` beside the `lq` and the TImode copy's widened life covers the
  `lw`'s: f2220 takes v1, the constant a0. With `*out = v150; out->z = z;` before the test, the
  `lw` waits for the swc1, the copy's widened life ends before it, and f2220 takes v0, the
  constant v1, as retail. With the copy in each arm, the test block holds only the lw and the
  li, and the li (shorter span) is placed first, in v0.
- Plausibility: the test is retail's own (the dead `li 3`, `lw 0x2220`); the arms must be
  equal after reload, so the original's two arms stored the same z, the shape the source keeps.

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

### One pointer variable for every loop: non-replaceable givs (func_001D5678, near miss)

Found 2026-11-10 from the `-dL` dump. Retail's loops over `entries[i]` show a reduced pointer
copied at the loop top and stepped from the copy (`addu v0,v0,sp; move s1,v0` before the label,
`move s1,v0` / `addiu v0,s1,-32` inside), not one register stepped in place. That is loop.c's
reduction of a giv that is not *replaceable* (strength_reduce inserts `giv = reduced` where the
giv was computed): record_giv marks a giv replaceable only when its insn is the register's first
set (REGNO_FIRST_UID) and its last use is inside the loop. A fresh pseudo for `&entries[i]` (an
expression, or a block-local pointer) is replaceable and is substituted away; a pointer variable
declared once at function scope and assigned in every loop (`RingEntry* e;` ... `e =
&entries[i];`) is not, in every loop, and gives retail's copies.

- A non-replaceable giv that is a user variable pays `copy_cost` in the benefit test as well as
  `add_cost` per biv increment; with a benefit of 6 that is negative, so the giv is left alone and
  recomputed each iteration (`sll v0,s5,5; addu s1,sp,v0`), while the memory references through
  it after the biv's increment are reduced to a register of their own from `sp-32`
  (`e = &entries[n]; Call(e); n++; e->z = ...`).
- The threshold of that test is `(has_call ? 1 : 2) * (1 + n_non_fixed_regs)`, so a positive
  benefit is almost always worth it: a giv retail leaves unreduced has a benefit of zero or less.
- The variable's value after a loop is live: retail read the first point of the next loop through
  it (`addu a1,s2,s1`, s1 the pointer's last value), which only `e[n]` reproduced.

Also from this function: a member read as the weight of a long-lived pointer's last loop
(`Vec::ScalarAtValue(params->rows[r].lift)` against `Vec::ScalarAt`) changes the pointer's life
in insns, and with it global-alloc's ranking of the parameters (`floor_log2(refs) * refs / life`):
params at 4*17/438 = 0.155 against nOffsets at 2*5/68 = 0.147 took s8 from it.

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

### A break with a body: the copied exit test enters the loop from outside (PAL func_001366A0, unsolved)

PAL's DrawTextPanel cuts a copied lines record at the line being typed:
`for (i = 1; i < lines.count; i++) if (at < lines.lines[i].start) { lines.count = i; lines.height
= i * h; break; }`. stmt.c rolls the `if` with its body into the exit test, jump.c copies the
test before NOTE_INSN_LOOP_BEG (retail's peeled `i = 1`, its height stored unmultiplied), and the
copy's path that goes on looping is a conditional jump to the increment's label inside the loop:
mark_loop_jump (loop.c) invalidates any loop entered by a jump from outside, the .loop dump says
"ignored due to multiple entry points", and the index stays `sll; addu`. The US twin's search
(an empty break body) is valid because its copy falls through into the loop. Retail's PAL loop
is reduced (`addiu a0,s5,24`, `addiu a0,a0,8`) with the count reloaded each pass, so either its
loop was valid or the walk was written: an explicit pointer (`for (s32* start =
&lines.lines[1].start; ...; i++, start += 2)`) gives retail's loop insn for insn, but CSE folds
its base to the frame (`addiu a0,sp,0x538`) where retail keeps the record copy's block-move
address (`move s5,a2`); `goto` past the loop keeps it valid but hoists the count. Copying the
record through a pointer, `TextLines* p = &lines; *p = self->lines;`, keeps the base a register
(`lw 24(s0)`, `addiu a0,s0,24`): the whole function is then retail's code but for five saved
registers, because p has one reference more than retail's (ours sets the block move's address
from p, retail sets p from it) and global-alloc ranks it first. Writing the copy first and taking
`&lines` after lets CSE fold p to the frame. Still open.

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

### The 30-insn window of the roll, and a record taken by index (func_0019A6A8)

ControlC17Collider checks three dials in a loop: each marker's walker must have no target key
(-1) and its current key must equal one digit of the code (`c - 0x390 == code / 100 % 10`,
`code *= 10` per dial); all three matching completes the lock, any mismatch goes on to the step
queue. Retail lays the loop out as: entry jump into the body; the increment and `i < 3` test at
the top; the completion falling out of that test; the body last, its match branching back to
the increment and its mismatch falling into the queue code. -1 and 100 are in s5 and s4 (moved
by loop.c), the marker pointer is set in the entry jump's delay slot, after them.

- **The roll needs the whole head within 30 insns.** expand_end_loop (stmt.c) counts INSNs and
  JUMP_INSNs (not CALL_INSNs) from the loop's start label and stops looking for jumps to the
  loop's end label once one is found and the count passes 30. With the body's two exits as
  `break` and the exit test in the header, the region is test (3) + target key (7: the
  address-of, the two argument moves, the load, the -1, the conditional jump and the break's
  jump) + current key (15: `code / 100 % 10` is two divmodsi4 with a constant and a trap each)
  = 25, so all of it rolls and only the increment stays at the top: retail's shape. The
  completion after the loop is then `if (i >= 3 && ...)`: CSE and jump threading fold the test
  on both paths (the exit test's, where i >= 3, and the breaks', which come from the body after
  `i < 3`), so retail shows no compare of i after the loop.
- **What does not.** The completion inside the loop (`if (i >= 3) { ...; break; }` at the top)
  is 33 insns to the second break, so the roll stops at the first and the body's tail stays at
  the top (ours entered the dials at the current key). Removing one division (29) rolls it,
  removing one insn (32) does not: the limit is exact. The completion in the increment part
  (body first, then `i++; code *= 10; if (i >= 3) {...}`) gives retail's layout, but the body
  then begins the loop with `&t`, which PRE hoists after NOTE_INSN_LOOP_BEG: loop.c calls the
  loop phony and moves nothing (-1 and 100 stay in the loop, &t takes a saved register).
- **A record by index.** A walking `m++` pointer is set where its statement is, before loop.c's
  moved constants; retail's comes after them, which is where loop.c puts a reduced giv's
  initialisation. `C17Marker* m = &markers[i];` at the top of the body (4 insns more, still 29
  in the window) gives that, where `markers[i].walker` at each call (twice the multiply) breaks
  the window.
- **The key.** `s32 key = target; if (key == -1) key = cur;` makes key's pseudo the target
  load's (s0, copied to a1 for the later compares); `key = target == -1 ? cur : target` (or the
  if/else) keeps the load in its own pseudo (a1, copied to s0), as retail. EXACT.

The tell: a loop whose increment and test sit at its top, entered by a jump into a body that
falls out into the following code, is a fully rolled top-test loop: count the head's insns
against the 30 in the `.rtl` dump.

### A search loop that loop.c leaves alone: a member read at each use (func_00165AE8)

Retail's strip search in CopyAttachmentPart (src/main/file_15F678.cpp) is a rolled `break`
loop (`b` into the test, the increment above it) that reloads the mesh's count, its strips and
its frame on every pass: loop.c moved nothing. Ours, with `StripMesh* mesh = e->mesh;` before
the loop, had the count hoisted (`Insn 485 ... moved`), and jump2 then copied the test in
front of the loop (`blez`), 8 bytes longer (2026-11-10).

- **Mechanism.** Written `e->mesh->nstrips`, `e->mesh->strips[n]` at each use, the load of
  `e->mesh` is partially redundant around the back edge, and PRE inserts it at the end of the
  loop's entry block: after NOTE_INSN_LOOP_BEG, before the entry jump (retail's `lw t1,24(s2)`
  in the `b`'s delay slot). scan_loop then finds an insn, not the entry jump or a label, as the
  first thing in the loop and reports "Loop from N to M is phony": nothing moves, as in
  retail. It is the barrier of func_0014D680 used the other way.
- **Two more forms in the same function.** The comparison against the strip's end was named
  first (`u32 limit = base + ((frame * stride) << 4);` then the two tests): retail computes the
  end before the first branch. `D_0027DC20[m].dstAddr` in a search over the queue expands as
  `(D + 8) + m*16` and hoists `&D[0].dstAddr` into a saved register; `FrameTarget* q =
  &D_0027DC20[m]; q->dstAddr` gives retail's `(m*16 + D) + 8` (expr.c's address order).
- **Spot it.** A loop in retail that reloads invariant members every pass while ours keeps one
  in a register: read the pointer at each use instead of through a local, and look for "is
  phony" in the .loop dump.

### The value read before a store, kept in its own variable (func_00165AE8)

- Retail's `lw v0,20(s1); move s0,v0` before `sw zero,20(s1)` (take a list, clear the head,
  walk it): `FrameLink* links = cursor->links; cursor->links = 0; for (FrameLink* link = links;
  ...)`. combine cannot merge the load into the copy across the store to the same memory, and
  the block-local `links` (v0) and the loop's `link` (s0) stay apart. One variable for both
  loads straight into s0.
- A count before a test of the same pointer: `if (p->a) owner->n++; s32 x = p->a && ...;`
  puts the `&&`'s clear after a label, so sched1 cannot raise it above the count's store
  (retail's `sw zero,4(sp)` in the second `beqz`'s delay slot). Written inside the `if`
  (`{ owner->n++; x = p->a && ...; } else x = 0;`), the clear has no dependences and issues
  in the first cycle, before the count. The separate form still gives retail's first `beql`
  straight to the join (which pass threads it past the second test was not checked).

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

### A loop test's reference pseudo, hoisted by PRE, takes a saved register (func_001C8590)

Read from the -dj/-dF/-dG/-dl dumps (2026-11-10). `BuildAgentPath` walks a point toward the
goal while it is still within reach of the agent (`while (IsNearPoint(c, self->v140, reach))`,
the test at the bottom, the body calling `SnapPointToOwnerGraph(f928, &c, &c)`). Ours was 12
bytes long: an `addiu s1,sp,32` before the loop, a `nop` after the entry `b`, and the clock's
`lui` twice (retail keeps it in `s8` from before the first branch).

- **The chain.** The test's `Vu0::Q(c)` is an inline taking `c` by reference: its parameter
  is a pseudo set to `&c` in the test. CSE follows the entry jump into the test and the
  branch back into the body, so the call's `&c` arguments become that pseudo; PRE then
  hoists it, loop-invariant, into the preheader. Live across the loop's call, it takes a
  saved register, and the clock's high part (PRE's pseudo from the entry block to the end,
  the lowest priority of all) gets none: reload rematerialises the `lui` at both reads.
- **Not loop.c.** The loop is "phony" in the .loop dump; nothing there moved it.
- **The form.** Pass the points to the test as `Vu0::Vec` values (`Vu0::Vec::Of(c)`) with the
  helper over Vec: CSE's table then has no register holding `&c` at the body, the body
  expands `&c` itself (retail's `addiu a1,sp,32`, reorg's delay-slot copy, and `move a2,a1`),
  and the clock's pseudo takes `s8`. Vec values are the project's convention.
- **Two smaller lessons.** GCSE numbers expressions in the order it first meets them, and
  PRE's insertions in the preheader follow that index: `Vu0::Q(d1) = MulAddX(..)` expands
  `&d1` before the operands, `Vu0::Set(d1, MulAddX(..))` the operands (the global's high part)
  first, as retail's `lui s6,0x25` before `addiu s2,sp,48` shows. And two floats tied in
  global-alloc's ranking (11 refs each, lives of 66 and 67 insns; a `min` counts each operand
  twice) swapped with the order of the first statements: `pos`, its store to the path,
  `maxLen`, then `goal` and the length.

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

- **Again in func_001C8920 (2026-11-10).** Retail stores the facing direction and loads it
  straight back (`sqc2 vf1,0(sp); lqc2 vf1,0(sp)`) for its length, after a join where both
  arms' `vsub` and store were merged by cross-jumping. One `Set(dir, Sub(a, b))` after the
  join, with `a` and `b` chosen in the arms, is forwarded by CSE (no reload, 4 bytes short);
  `Set(dir, Sub(..))` written in each arm leaves the join's read to memory. The remaining
  `lwc1` order in the pitch arm was the conversion: ToFloatMoved for the distance.

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

Measured again 2026-11-10 (cse.c's cse_end_of_basic_block and cse_basic_block, gcse.c's cprop,
`-ds -dG` dumps):

- **Follow-jumps is the whole difference.** The near miss built with `-fno-cse-follow-jumps`
  (both CSE passes, to explore only) has retail's registers: self in t0, the key in t1, the tag
  in t5.
- **A jump that the first CSE folds does not stop it.** A second use of the tag label that CSE
  can decide (`if (n->key == key && n->owner == self)` inside the owner test) gives the label
  two uses when the path is chosen, but cse_basic_block, once the folded jump drops the label's
  count back to its own, continues past the label (the `to_usage` test) and the tag test still
  reads the first load's register: the near miss's code, no PRE copy.
- **A jump that only GCSE removes does.** A local set to 1 before the walk and tested with the
  key (`if (flag && n->key == key)`, or `n->key == key && flag`) is EXACT: the first CSE cannot
  see the constant (the walk's body starts at the loop label), so the tag label has two uses all
  through CSE, PRE copies the key load (`move v1,v0` in the bne's slot), the second CPROP pass
  replaces the flag with `(const_int 1)` and the jump pass after GCSE deletes the test; cse2
  then leaves the copy alone. So retail's source had a second use of that label, or a loop
  note, that ends the first CSE's path and is gone after GCSE: a test GCSE's constant
  propagation decides, a `do { } while (0)`, or something not yet seen. A constant flag that is
  never anything else is not plausible original code and is not kept (nonmatching/).
- **Also ruled out (34 words or more):** the walk with `continue` for other objects' calls and
  `prev = n` in the for's increment, a `do { } while` with `goto next` (as RemoveQueuedCalls is
  written), the owner test repeated around each key test (65), and one test of both keys
  (`n->key == key || n->key == tag`) with the key's body inside (62, the tag test then comes
  first).
- **The comparison's block before the loop is loop.c's.** The `return n->data->f4 == *q` block
  sits between the switch's cases and the loop in both builds: find_and_verify_loops moves a
  block entered by a conditional jump and ending in a jump out of the loop to the last barrier
  before it.

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

### A 2-bit field's type in its read, and a switch's dispatch (func_00128598)

Measured 2026-11-10 on a follow step of src/main/placed_object.cpp. Two causes, both in the
source's shape, not in a pass's tie:

- **The field's type.** Retail reads a 2-bit field at bits 30-31 of the doubleword at 0x2C8 as
  `ld; dsll 2; dsra32; andi 3` and stores it as the doubleword's `ld; and; or; sd`. A `u64 : 2`
  field reads as `dsrl 30` instead; a `u32 : 2` field in the same union (as bits24, read with
  `dsll 8; dsra32; andi 3` by func_00125138) gives retail's extraction, a 32-bit field taken out
  of a 64-bit word, and the same doubleword stores. The written-out read `(s32)((s64)flags << 2
  >> 32) & 3` gives the same instructions but is an expression of its own: sched1 raised its `ld`
  above both Lengths and the qmfc2 results lost v0 to it. The field's read keeps the `ld` where
  the switch is. Where retail shows `dsll k; dsra32; andi m` on a doubleword field, declare it an
  int field.
- **The dispatch.** Retail tests `beqz v; li v0,1; beq v,v0; b end` and then the cases' bodies:
  a `switch` with cases 0 and 1 and no default. An `if (f == 0) ... else if (f == 1)` chain gives
  `bnezl` into the second test instead, one block shorter.
- **A value set in both arms, then read.** `if (c) g = a; else g = 0; t = g + v;` with `g` a
  stack Vec02: retail stores `g` once at the join (cross-jumping merged the arms' stores after
  reload) and reloads it for the add. A `u128 push` set in the arms and stored once (`Q(g) =
  push`) lets CSE forward the register and drops the reload: assign the memory in each arm.

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

### A float constant declared in the loop body: loop.c's hoist, cse2's copy (func_001D36F0)

Read from gcse.c (cprop_insn, one_cprop_pass) and the `.gcse`, `.loop` dumps of
func_001D36F0 (2026-11-10, src/main/player_request.cpp):

- **Retail's sign.** `items[0].weight = 1.0f` is stored from `$f0` (`lui at,0x3f80; mtc1`)
  and `mov.s $f20,$f0` follows; the loop's four mover calls pass `mov.s $f13,$f20`, with
  `$f20` saved in the frame. Ours (`f32 one = 1.0f;` at function scope, stored and passed)
  rebuilt `lui/mtc1 $f13` at each call: 4 bytes less code, 16 less frame.
- **Why.** A function-scope `one` is one pseudo set once to a CONST_DOUBLE, available on the
  loop's entry and back edges, so GCSE's constant propagation replaces it in every argument
  move inside the loop (`CONST-PROP: Replacing reg 120 in insn 133 ...` in the `.gcse` dump):
  nothing is left for global-alloc to give a saved FPR.
- **Retail's form.** The local declared in the loop body (`f32 one = 1.0f;` at the top of the
  `if (o != 0)` block) and the store written with the literal: the body's set is not
  available at the loop's head (it is set again on the back edge), so cprop leaves it; loop.c
  hoists the invariant set to the preheader, and cse2 finds the store's pseudo still holding
  1.0 in that block, so the hoist becomes a copy of it: retail's `mov.s $f20,$f0`.
- **Spot it.** A constant loaded once before a loop and copied (`mov.s`) into a saved register
  the loop's calls read: the constant was a local of the loop body. Compare func_0016BEA0
  above, where an inline's parameter keeps the copy from forming.
- **Also in this function.** Vu0::ScalarAt returned `Q((s128)r)`, a reference, which left the
  weight slot's address in a pseudo, as Vu0::Scalar's did (func_0017BCD0 above): the division's
  slot (32(sp)) is reused by the block-scope `Vec02 a20` declared after it, and CSE then read
  `&a20` through that pseudo, which loop.c hoisted into a saved register (s6) for the whole loop.
  ScalarAt now ends `return *(u128*)&(s128)r;`, the same slot and store; every matched function
  builds the same (full US and PAL builds MATCH). The two Vec02 results read last (a20, a30)
  are declared in the body before their calls, where the slot order shows them (the division's
  slot shared with a20, the 0.5's slot after a30, `&blend` last); the second loop has its own
  counter (`for (s32 j = 0; ...)`), as retail's caller-saved a2 shows.

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

### Frame addresses and a constant's copy in the arc's frame (func_001E7C60)

Read from function.c (assign_stack_temp_for_type, combine_temp_slots), integrate.c and cse.c with
`-dr -dF -dc -dl -dg` dumps (2026-11-10). The near miss was 16 bytes long (s6, s7 and 0x30 more
frame); four changes matched it:

- **A block local takes its slot where it is declared.** g++ expands a declaration at its
  statement (expand_decl, `assign_temp (type, 1, 1, 1)`), so `Vec02 pos;` at the top of a case's
  block holds its 16 bytes before the block's weight temporaries are made, and they go to the
  next slot (0xD0). Declared just before its assignment, after the weights' statements, pos
  takes the freed slot the weights used (0xC0), as retail's does; the outline's 0x80-byte request
  then fits after one slot (0xD0), not two (free BLKmode slots combine only when adjacent, and
  two 16-byte ones are too small for it). Spot it: retail's frame reuses one offset for weights
  and a later local.
- **FromFloats took its slot's address through Q.** As Scalar's did (func_0017BCD0, above),
  `return Q((s128)r);` left `(set (reg) (plus fp 192))` for CSE, which made that pseudo the
  canonical register of the frame address; the case blocks' `&pos` and the ticks' request, given
  the same slot, were read through it, live from the unprojection to the end (s6). FromFloats now
  ends `return *(u128*)&(s128)r;`; every matched function builds the same (full build MATCH).
- **An address passed through an inline is no pseudo.** `FillMemory(&request, 0, 0x80);
  ...; QueueDeferredRequest(&request);` expands each `&request` into a pseudo, and CSE replaces
  the second with the first, which then lives across FillMemory's call in a saved register (s0).
  Retail forms `addiu a0,sp,0xD0` at both calls. A small inline that clears the record
  (`ClearArcQueueRequest(&request)`, as matrix.cpp's ClearMatrix) gives it: integrate.c
  substitutes the unmodified parameter's frame address as a constant, so the argument is set
  straight into a0 (`(set (reg a0) (plus fp 208))`), no register holds the address after the
  call, and the second `&request` stays a one-use pseudo that combine folds into a0. Spot it:
  `addiu a0,sp,N` both before FillMemory's call and after it; among US's 170 FillMemory calls
  this shows only at a handful (BuildScaleAboutFrame's ClearMatrix, 0x163218, 0x1CB244, here).
- **A literal CSE'd into a copy that outlives its source.** Retail's stick arm has
  `mov.s $f4,$f6` (150 copied from `dist`, still 150) before the height's product. With
  `dist = |x|*x*150.0f + dist; height = |y|*y*150.0f + height;` the first 150's pseudo becomes a
  copy of `dist` (the cheaper equal register) whose use CSE replaces with `dist`; the second 150
  finds that pseudo still holding 150 after `dist` changed, so it is read through it and the copy
  stays. Written `* dist` in the first line, or height first, there is no copy (the 150s are
  `dist` itself); the else arm, off CSE's path from the initialisation, loads 150 afresh.
- Also: the first aim term as `Vu0::Vec::Of(cam->f40).q` puts the load before the height's slot
  store (an inline call, integrate.c's first pass; above, "A weighted sum's operands in insn
  order"), so the fA0 load after it anti-depends on the store, the store keeps its place before
  the vmulx and the weight dies at the vmulx, which takes its register as retail's does
  (`vmulx vf3, vf1, vf3x`). `place.scaleX = place.scaleY = 1.0f;` stores scaleX first.

### A frame address CSE keeps in a pseudo across a call: an inline's arguments (func_00112C38, func_00113240)

MultiplyScriptValues and DivideScriptValues scale a matrix with ScaleMatrix (func_00188628) into a
stack matrix, then copy it with CopyBytes: retail forms the matrix's address afresh for each call
(`addiu a0, sp, 0x60; jal ScaleMatrix` ... `addiu a0, sp, 0x20; addiu a1, sp, 0x60; jal CopyBytes`),
where every direct form kept it in a saved register (s0, 16 bytes too long with the cross-jumped
tails). The mechanism, from the .rtl and .cse dumps:

- **A call's arguments are pseudos; CSE keeps the first.** expand_call computes each register
  argument (and a struct return's hidden address, force_reg) into a pseudo, then moves it to
  a0-a3. A second `&r` after the call is the same (plus fp 0x60), and CSE's cheapest equivalent is
  the first pseudo (cost 1 against the PLUS), so one pseudo lives across the call: a saved
  register. An out pointer, a value return, a reference, an operator= or the returned
  temporary's address all go through such a pseudo.
- **An inlined call's arguments go straight into the hard registers.** In an inline function's
  saved body the call's argument moves are `(set a0 (plus fp K))`; integrated, they stay so, and
  a0 is invalidated by the call, so the later address is formed again. Retail's shape is a matrix
  class whose copy constructor calls CopyBytes and an inline function that scales into its own
  matrix and returns it: `M r; ScaleMatrix(&r, m, s); return r;`, the return copy-constructing the
  caller's `M c = ScaledMatrix(m, s)` (the helper over the asm routine that a matrix class would
  have; func_001C75B0 and ComputeColliderInverseInertia copy their scaled 3x3 matrices with
  CopyBytes the same way).
- **A pseudo for the freed slot's address does the same.** Where the weight's slot (ScalarInGpr's
  temporary) was freed and the inline's matrix took the same offset (0x50 in the matrix case),
  the pseudo that read the slot back was again CSE's equivalent of (plus fp 0x50). It came from
  Vu0::Q: integrate.c copies a parameter that is not read-only through a register
  (process_reg_param), and Q's reference parameter is one, so `*(const u128*)&v` loads through a
  pseudo holding the slot's address. Bound to a local reference instead (`const s128& slot =
  (s128)r; return *(const u128*)&slot;`), the address is a set-once frame address that
  integrate.c substitutes into the load, and no pseudo holds it: ScalarInGpr and the new
  ScalarInGprAt end so (include/vu0.h). Every other ScalarInGpr caller is unchanged (full build).
- **A callee's v0.** CopyBytes declared `void*` sets v0 at the call (unused), and the lq/sq copy
  after it then starts in v1 where retail's starts in v0; declared void, as the file does, v0 is
  free. Likewise StoreFloatAsQuadword (func_00118CF0, defined in the same file) returns its out
  pointer: declared so, sched1 orders `mov.s $f12` before `move s6, v0` as retail.
- **A float in memory into a 128-bit GPR.** Retail loads the float operand's word with lw straight
  into the GPR it passes (`lw v0, 4(s2); por a2, zero, v0; sq v0, 0x50(sp)`); ScalarInGpr's
  operand would be lwc1 then mfc1. Vu0::ScalarInGprAt is that lw, as FromFloatAt is to FromFloat.

### A case that seems to store the compare's register: reorg's redundant constant (func_001E8A50)

The keyed cone agent's state hook (src/main/file_1E88D0.cpp) was 8 bytes long. Read from cse.c
and reorg.c with `-dj -dJ -dd` dumps (2026-11-10):

- **The size was a wrong constant.** In its inner switch, retail's case 0x2DA is `b S; li s3,2`,
  where S is the `sw v0,3160(s1)` shared with cases 0x2D9 and 0x2DB, and v0 seemed to hold the
  tree's 730 (`li v0,730; beq v1,v0`). The near miss wrote `self->fC58 = 0x2DA;`, and CSE, which
  follows the tree's jump into the case (the label has one use and a barrier before it),
  merged the index (reg 168, which lives on to the next compare) with the constant's register:
  make_regs_eqv keeps the longer-lived index as the class's canonical register, so the store
  took v1 and cross-jumping could not merge it (one store more). The real value is 0x2DB: the
  beq's delay slot holds the next compare's `li v0,731`, and reorg (fill_slots_from_thread),
  finding the case's own `li v0,731` redundant with it, deletes it. **Spot it**: a case's store of a
  register that its compare does not leave holding the expected value; read the delay slot.
- **`.p2align 3` before loop labels.** SN's compiler aligns each loop top to 8 bytes, so a nop
  appears or goes away in front of a loop when the code before it changes size. Fix the size
  first; such nops then follow.
- **Two loops, two counters.** Both loops counted with one `u32 i` declared at the top, so both
  got s2; retail's first loop counts in s0 and the second in s2. A `for (u32 i = 0; ...)` in
  each case gives each loop its own pseudo, and global-alloc places them as retail does.
- **A constant hoisted by jump.c moves in sched1.** `v = ... ? 8 : 5; self->fC5C = v;` lets jump.c
  hoist `v = 8` in front of the float test, where sched1 places it first in the block (low priority, ready
  from the start); retail's `bc1t X; li v0,8` needs it next to the branch. A store in each arm
  (`self->fC5C = 8;` / `= 5;`, merged by cross-jumping after reload) gives that, and the
  annulled `beql ...; li v0,5` of the test above it.
- **key = 0 in the else arm.** `key = 0; if (near) key = Find(..);` lets sched1 put the zero before
  the first call; written as `if (near) key = Find(..); else key = 0;`, reorg moves the zero into
  the branch's slot, as retail has it.

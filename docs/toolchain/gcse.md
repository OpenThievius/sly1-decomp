<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# GCSE

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

### Eight spilled frame addresses: the table size from their slot order (func_001CC490)

SolvePlayerLinkSystem matched from a size difference (932 against 904 bytes) with `-dF -dG -dL
-dl -dg` dumps (2026-11-10). What each difference came from:

- **The size.** Each weight of the two sums read with `ScalarAt` (its "rV" memory operand) was
  its own qmtc2; with `ScalarAtValue` the second use of each weight is CSE's copy, one qmtc2 and
  two slot stores, as retail. And retail's row address (`li s0,96; mtlo; madd`) is loop.c's giv
  left alone: in the second loop pass the constant 96 moves (80 x 1 x 1 >= the loop's insns)
  when the inner loop has 80 insns or fewer, and the multiply is then reduced. Naming the mass
  weight (`Vu0::Vec mass = ...ScalarAtValue(...)`) and the arm's operands keeps it at 81 or more.

- **The table size, solved from the slots.** PRE's reaching registers for the addresses of eight
  locals (cross, scaled, rows, vel, m, factor, rhs, sol) are all spilled; reload gives them stack
  slots in pseudo order, which is PRE's bucket order. With `(plus (reg 1) N)` hashing to
  13258 + 1 + N, the only odd T from 31 to 400 that orders the offsets as retail's slots do
  (cross, m, scaled, rows, factor, `j << 5`, vel, rhs, sol) is 153: 304 to 307 insns at gcse.
  Ours had 271 (T = 135). Each named `Vu0::Vec` operand is about two insns there (its movti
  copies), so retail's operands were named: weight then vector for each term of the two
  MulXSum3 sums (which also gives retail's chain of slot stores and row loads, the lever of
  func_001DDE90), the two velocities, the dot product's two rows and the arm's two points.
- **Order of the PRE insertions.** The entry block's address insns follow each address's first
  use as a value, and reload's round robin (v0, v1, a2, t3) follows that order: retail's
  `&scaled, &rows[i][j].a, &cross` (the calls' arguments) means the stores into cross and scaled
  were `Vu0::Set`, addressed from the frame; `Vu0::Q(cross) =` forms `&cross` as a value
  first.
- **The row's base.** `m[j][k]` folds the array's offset into the memory reference, so loop.c
  forms `sp+384` afresh in the preheader; `f32* row = m[j]; row[k]` keeps the address an
  expression PRE replaces with its reaching register (retail's `lw t4,544(sp)`). The element is
  stored with `Vu0::StoreX` (its qmfc2 is a reload, t3, after the loop's registers).
- **The constant 1 of `i == 1`** in retail is a reload (`li a2,1` between the rotation's v1 and
  t3), so it was a function-wide pseudo with no register, not a block-local one (local-alloc's
  v0): a named local set once, `s32 flipped = 1;`. loop.c cannot move the literal: its life and
  savings are 1 and the loop has 99 insns (the `li s0,96` beside it stays for the same reason).
- **`addu v0,v1,a2` (base first) for `target[j]`.** g++ turns a subscript of a pointer, or of
  `*p`, into pointer arithmetic, whose address inside a memory reference has the index first; an
  array member (`target->v[j]`) stays an ARRAY_REF, base first, as a local array's.

### A splat split between a GPR and a VU0 copy: what gcse's copy propagation does (func_00155868, unsolved)

Read from cse.c (make_regs_eqv, the copy swap at the end of cse_insn, cse_end_of_basic_block),
gcse.c (hash_scan_set, cprop_insn), reload.c (find_equiv_reg) and reload1.c (reload_cse_regs_1)
of GCC 2.95.3 and the -ds/-dG/-dl dumps (2026-11-10). func_00155868 splats the margin
(`Q(size) = Splat(m)`) and then, by arm, either `lo = t - size, hi = t + size` or `hi = size,
lo = size * -1`. Retail keeps the splat in a GPR (`pextlw v0,v1,v1`: an output register apart
from the input, so a real GPR pseudo), copies it to vf2 for the size store and the then-arm's
vsub/vadd, stores `hi` from the GPR in the else arm (`sq v0,32(sp)`) and copies it again to vf3
for the MulX (`qmtc2 v0,vf3`, which reorg takes from the else arm into the `beqz` slot). Ours
has one VU0 pseudo (`VU_REGS or none`): the asm's output is reloaded through v0 into vf2 and
everything reads vf2. One instruction short.

- **cse1 makes the split; gcse's cprop undoes it.** With the splat named (`u128 s = Splat(m)`)
  the inline's return copy `s = r` survives cse1 in two orientations by path: on the jump path
  (head and else, whose cuid range covers the whole if/else) the copy's destination does not
  live outside the range, so the asm's register stays canonical and the else arm's uses become
  it; on the fall-through path (head and then) the destination lives past the range, becomes
  canonical, and cse_insn's swap moves the asm's output into it (the copy follows the asm
  directly). After cse1: `asm -> s; r = s; size = s; then: s; else: r`. gcse's copy
  propagation then finds `r = s` available at the else arm's entry and rewrites both uses
  ("COPY-PROP: Replacing reg 121 in insn 191/232 with reg 119"): one pseudo. With a statement
  between the asm and the copy (a diagnostic, not a form) there is no swap and cse1 leaves the
  other orientation, `asm -> s; h = s; then: h; else: s`, which is retail's; cprop then rewrites
  the then arm's uses instead. cprop replaces a copy's destination wherever the copy is
  available at a block's entry and its source is not set earlier in that block, in any insn whose
  pattern is a SET (asm operands included); only PRE's copies, made after cprop in the single
  pass, escape it, and cse2's paths then canonicalise them back the same way.
- **The class of the GPR value.** A test unit shows regclass's balance for a Splat result:
  `=r` output, one store and one `j` use give VU0 (`qmtc2` after the asm, `sqc2`); two stores
  and one `j` use give a GPR (`pextlw v0,v1,v1; sq v0; qmtc2 v0,vf3` before the MulX: retail's
  else arm). So retail's GPR pseudo had at most one VU0 use against two stores at regclass
  time, and the then arm's two uses were on another (VU0) pseudo.
- **Reload would supply the rest.** find_equiv_reg stops only at a CODE_LABEL, so a reload in
  the fall-through arm finds a register copied in the head (`vf2`); reload_cse_regs forgets at
  labels, not jumps; reload_cse_simplify_set turns a load of a slot a register was just stored
  to into a register move. A form whose then arm reads `size` from memory up to reload, with
  the copy to vf2 in the head, would give retail's head; no plain form tried keeps the loads
  past cse2.
- **Ruled out** (all one VU0 pseudo, 572 bytes): the splat as a named `u128` read by either
  or both arms, as a `Vu0::Vec` with Vec helpers in the arms, `Vec::Of(size)` reads, `hi = size`
  after the MulX, `Q(hi) = Q(size)` and MulX of `Q(hi)`, a second Splat in the else arm (cse1's
  jump path merges the identical asm), `s` reassigned in the else arm or after the join.
- **The loop is retail's.** `Vec02* pts = r->points[r->bank];` before the loop and `Vec02* p =
  &pts[i];` in its body: loop.c reduces the address to a pointer giv initialised in the
  preheader after the entry test (`addu v1,a0,s1` in the `blez` slot, `move s0,v1`), where a
  pointer stepped by the `for` (`p++`) is the variable itself. With it the loop and the tail
  equal retail's instruction for instruction; only the head's missing instruction is left (it
  also moves the loop label's alignment `nop`).

### The same lever for a parameter block's two quadwords (func_001EC190)

- The scale of a static parameter block's two quadwords (`StoreFloatAsQuadword(&t, k);
  CopyQuadword(&u, &params.q30); StoreQuadword(&params.q30, ScaleQuadword(t, u));`, twice)
  kept `&params.q30` and `&params.q50` in two saved registers (a 0x160 frame for retail's
  0x140). Through the file's inline `StoreScaledQuadword(dst, k, p)` (the one file_1D62E0.cpp
  and agent.cpp use), called with the member's address for both `dst` and `p`, integrate.c
  substitutes each address at its use and retail's frame and saved registers follow; the
  remaining difference is the block's constructor stores ("What retail's order needs",
  large-functions.md).

### PRE hoists an exit block's expressions above a loop; a variable whose address is taken keeps them (func_0015F320)

- **What PRE does after a loop.** In this release's lcm.c, `latein` is `delayin` for every
  block but the last, and `delayin` stops at a loop's header (its back edge starts as not
  delayed and stays so). An expression the block after a loop computes from a register set
  before the loop (`frame & 0x1FF`, `frame >> 24`) is anticipatable through the loop and
  delayed only up to the block before it, so that block is "latest": PRE computes the
  expression there (`PRE/HOIST: end of bb 6`), deletes the computation after the loop, and the
  value lives in a saved register across the loop. A computation earlier in the function does
  not help: this LCM never uses availability, only anticipation from the last kill. Constants
  are not expressions, so `frame & 0xF000000` (its `lui` set in the same block) stays.
- **Retail's sign.** After the loop retail recomputes a FRAME word from the register the value
  was loaded into (`andi v0,s3,0x1ff; lui a2,0xf00; and a2,s3,a2; or`) and no masked value
  crosses the loop. Ours kept `frame & 0x1FF` and `frame >> 24` in s3 and s4 (one more saved
  register, a different frame and loop registers), or `fbp | psm` in s3 when they were locals.
- **What keeps them after the loop.** A variable whose address is taken is an ADDRESSOF
  until purge_addressof, which runs after cse1 and turns each read into a fresh copy
  `(set (reg 174) (reg/v 172))` in the reading block. cse never sees those copies and gcse's
  cprop only propagates copies set in other blocks, so the expression's operand is set in its
  own block: not anticipatable at the block's start, never hoisted. combine then folds the copy
  away and the `andi` reads the variable's register. func_0015F320 passes its FRAME word by
  `const u64&` to a small inline that keeps the base and format bits; `*(u64*)&frame` at one
  read does the same.
- **fold merges two masks of one operand.** `(f & 0x1FF) | (f & 0xF000000)` is
  `f & 0xF0001FF` from the front end on (distribute_bit_expr), `lui; ori; and` in the output.
  Retail's two `and`s and `or` come from `(f & 0x1FF) | (((f >> 24) & 0xF) << 24)`, which
  combine turns into the second `and` after fold has run.
- **Spotting it.** The gcse dump's `PRE/HOIST: end of bb N` for an expression whose only
  occurrence is after a loop, and retail computing the same thing after the loop from a
  saved register.

### A clear and a query of one frame record: `q.Clear()` keeps PRE off `&q` (func_0017E710)

Read from gcse.c (compute_hash_table, pre_insert) and lcm.c (pre_lcm) of GCC 2.95.3, with an
emulation of pre_lcm over the `-dG` dump (build/swarm/w15-17E088/lcm.py, 2026-11-10):

- **What differed.** Each of the player's two query loops clears a NodeQuery on the stack
  (`FillMemory(&q, 0, 0x40)`), fills it, normalises a direction (two arms) and calls
  FindNodeForQuery(&q, 0, 0). Ours kept `sp+32` in s0 from before the arms to the call (8 bytes
  more over both loops); retail forms `addiu a0,sp,32` at each call.
- **Why.** A frame address is never killed: on a call gcse marks every call-used hard register
  set except the frame pointer (`regno != FRAME_POINTER_REGNUM`), so `(plus fp 32)` is
  transparent through FillMemory's call and the query's `&q` is fully anticipated and redundant
  with the clear's. lcm.c's compute_latein sets LATEIN to DELAYIN in every block but the last
  (its successor test is skipped), so the "optimal" point is the entry of the clear's block and
  pre_insert puts the copy at that block's end, before the arms' test. Both loops share the
  expression and so one reaching register; loop 2's copy crosses RandomIntInRange's call in one
  arm, and the pseudo takes a saved register.
- **The form.** The clear as an inline method of the record, `void Clear() { FillMemory(this,
  0, sizeof(*this)); }` (node_query.h, as file_14EE40.cpp's HeldTouchQuery has one): `this` is
  substituted as a constant and set straight into `$a0`, which gcse never records, so the
  query's `&q` is the only occurrence. A free inline function does the same only if its pointer
  parameter is `const` (`NodeQuery* const q`); a plain parameter is copied into a pseudo.

### A stack array read through `(rows + r)->`: the frame constant stays out of PRE's reach (func_001D5678, near miss)

DrawAngleSortedRing copies three rows of its parameter block into a stack array, scales them, and
reads them again in the draw loop. Retail forms `sp + 14512` once at the entry (spilled, read by the
copy loop) and again in the draw's i-loop preheader (spilled to a slot of its own); ours had one
pseudo for both (2026-11-10, w15):

- **The expression.** `rows[r].x`, `&rows[r]` and `Vec02* row = rows + r;` all expand the address
  of the element first, `(plus (plus fp 14512) (ashift r 4))` forced into a register, which
  computes `fp + 14512` as an insn of its own: expression `(plus fp 14512)`, which PRE then finds
  redundant with the copy loop's and replaces by its entry pseudo.
- **Pointer arithmetic inside the memory reference.** `(rows + r)->x` is a PLUS_EXPR expanded with
  EXPAND_SUM as the address of a MEM: expand_expr puts the sum's constant outside
  (`((ashift r 4) + fp) + 14512`), and memory_address leaves 14512 as the offset, so GCSE has no
  `fp + 14512` there. loop.c's giv for the rows then has the add value `fp + 14512`, which it
  forms in the row loop's preheader and moves out of the i loop in its next pass: retail's
  `addiu v0,sp,14512; sw v0,14644(sp)` and two more instructions than ours had.
- **Bucket order.** The four addresses PRE hoists to the entry (sp+32, sp+8288, params+112,
  sp+14512) spill in pseudo order, which is the table's bucket order, (13258 + regno + offset) mod
  T. For retail's order T = 323 (or 339) with params as pseudo 121; `*(Vu0::Vec*)&x = F(...)`
  stores (two more insns each than `Vu0::Q(x) = F(...).q`), Vec locals for the weighted sums'
  operands and a named row weight bring the table from 305 to 323 with the final code unchanged.

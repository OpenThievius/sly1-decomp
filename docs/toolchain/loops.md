<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Loops

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

### jump.c's copy of a loop test has a life of 2: three constants, two moved (func_00192DD0)

Measured with `-dL` dumps (2026-11-10, the switched collider's segment walk,
src/main/switched_collider.cpp). Retail's outer loop over the segments holds 1.0 (the walk's guard) and
0.0001 (the length test) in f24 and f23, in that order in the preheader, and loads 5.0 in the
else arm before the divide.

- **The order says two passes.** The three constants are in the loop in the order 0.0001, 5.0,
  1.0, each a one-insn load. With life 1 each, one pass moves them first to last while
  `80 - 3k >= insns`, so moving 0.0001 and 1.0 but not 5.0 needs 1.0 to have a longer life, and
  1.0 ahead of 0.0001 in the preheader needs 1.0 moved in pass 1 and 0.0001 in pass 2 (see the
  next section).
- **The walk as a `for`.** `for (f32 t = step; t < 1.0f; t += step)` (with `step` set in both
  arms of the length test) makes jump.c copy the exit test ahead of the loop; the copied 1.0 is a
  fresh pseudo whose load sits two luids from its compare (life 2), where the near miss's
  `if (t < 1.0f) do { } while (t < 1.0f);` gives life 1. So it moves at `80 * 2 >= insns`.
- **The size: 82 in pass 1, 79 in pass 2.** With Length and MulXSum on Vu0::Vec values
  (Distance, and the interpolated point stored as a Vec) and the endpoint's copy into the message
  written `*(Vu0::Vec*)&msg.vb = Vu0::Vec::Of(b)`, pass 1 counts 82 insns: 0.0001 (80) and 5.0
  stay, 1.0 (160) moves; pass 2 counts 79: 0.0001 moves, the threshold falls to 77 and 5.0
  stays. The same with a plain `msg.vb = b` is 78 and 74 (5.0 moves in pass 2); the final store
  to the collider also as a Vec makes 86 and 83 (0.0001 never moves).
- **The prologue's save order** followed from `target = 0` being set before the `if (sink)`:
  its `move s4,zero` in the first block ties `sq s4` to it in sched2. Declared inside the `if`
  (reorg still fills the branch's delay slot with it) the saves come in retail's order.
- **The node scan.** Retail starts its walk pointer at `self + 0x59C` (`addiu s0,s3,1436`); a
  cast array indexed at each use gives `move s0,s3` and offset 1436 in each load. The giv's add
  value must be a register: the array named once, `void** nodes = (void**)((u8*)self + 0x59C);`.

### A call's frame-address arguments that GCSE does not hoist (func_00191AC8, unsolved)

Read from the `-dF` dumps (2026-11-10, nonmatching/func_00191AC8.cpp). In a loop, a call's argument
`&local` is expanded into a pseudo (`(set (reg) (plus sp N))`) that PRE hoists to the function's entry
like any frame address, and global-alloc then gives it a saved register. Retail's `addiu a0,sp,192`
and `addiu a1,sp,256` at the CopyBytes call inside the loop (with `&p` and `&span` hoisted into
s5/s4) mean those two never were pseudos:

- **An inline's address parameters are substituted.** Called through an inline whose parameters are
  the two pointers, integrate.c substitutes the constant frame addresses into the argument moves
  themselves (`(set (reg a0) (plus sp 192))`), which PRE does not touch (its destination is a hard
  register).
- **But a reference in the same block undoes it.** Rows stored as `Vu0::Q(s.r[i]) = ...` pass s.r[0]
  to Q by reference, which copies its address into a pseudo; CSE then uses that pseudo for the later
  `&s` argument, and PRE hoists it. Stored as `*(Vu0::Vec*)&s.r[i] = ...` the address stays a
  constant in the memory reference.
- **Not a struct assignment.** `rot = s` of two Mat02 is moved by pieces (lq/sq), of two Mat3U by
  ldl/sdl pieces, and an inline returning a Mat02 by value copies it by pieces too: none calls
  CopyBytes (memcpy), so retail's call was written.

- **The scale as a spilled Vec value (2026-11-10, w16-191AC8).** Held as a `Vu0::Vec` value
  instead of a Vec02 in memory, the scale has 10 refs and crosses 3 calls: CALLER_SAVE_PROFITABLE
  (4 * calls < refs) fails, global-alloc leaves it unallocated and reload gives it the spill slot
  after the locals (304). Every load in the loop then is retail's: row 0's in vf2, rows 1 and 2
  sharing vf4 (inheritance), and `k2 = k` as a memory-to-memory move through v0
  (`lq v0,304; sq v0,240`). Two things remain. Retail's set of the scale stays in the loop as a
  copy of a saved GPR (`mfc1 s6,$f12` before the loop, `move v0,s6; sq v0,304` in it), where
  loop.c moves ours out: after CSE the asm's output is the variable itself, set once with an
  invariant source, so it is moved whatever its lifetime; retail's set was not invariant to
  loop.c (a partial or second set). And retail loads the scale into vf4 right after
  TestOwnerGraphSpan, before the branch (so not reorg's: vf4 is live into the exit), and after
  the loop stores vf4 to rot's freed slot and divides by it: a value set in the loop after the
  last call and live only to the exit. A separate copy written there is moved out with the
  scale; a union of a float and a u128 stays in memory (swc1, lq), not a register.

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

### Solved: the samples' byte offsets formed before the switch (func_00118988)

SampleScriptAnimation matched on 2026-11-10 (src/main/script_machine.cpp), read from `-dL`
dumps:

- **The threshold is 79 here, and the 48 is sixth.** Varying the loop's size with the 48 left
  after the compare tree: 64 insns moves it, 65 does not, so `79 - 15 = 64` is its limit behind
  the tree's five moves (li 2, the `bit < 3` slt, li 1, li 4, li 8). The `li 48` always sits
  right before its `mult` (expand_binop forces the constant after both operands, and
  `-fforce-mem` loads a memory operand before it), so its lifetime is 1, and it can move in
  pass 1 only from ahead of the tree or with a loop of 64 insns.
- **Which giv is reduced last.** strength_reduce prepends each giv it finds, so it reduces them
  in reverse order of the loop and the last one's start value sits nearest the loop: the
  shortest life, global-alloc's first choice (s4). Retail's increments and start values (q8,
  q4, rotations, positions) say positions' giv came first: its address in case 1 is a memory
  giv, so the rotations' surviving giv (the add of the base) has to be found after case 1.
- **Both at once: the multiply ahead, the add in case 2.** Computing the offsets at the top of
  the body, `s32 quad = i * sizeof(ScriptSampleQuad); s32 rot = i * sizeof(ScriptSampleRotation);`,
  and adding them to the buffers in the cases (`rotations + rot`), puts the `li 48` first in
  the movables (moved at 79) and the add giv in case 2: pass 1 reduces every giv, pass 2
  reverses the counter, and the registers are retail's. The buffers are AllocateBackMemory's
  untyped memory, so they are `u8*` and the cases cast at the read. Ruled out: a pointer local
  `r = &rotations[i]` ahead of the switch (the add is then found first: rotations takes s4),
  pointers for all four (each case's memory giv is reduced separately, the same swap), an
  inline taking the index by `const s32&` (ADDRESSOF loads: 74 insns), `u32` counters and
  switch copies (no change), and pointer walks with a count (`if (n > 0) do { } while (--k)`:
  registers right, but the walks' starts are the source's, ahead of loop.c's moved slt, so
  sched2 places its spill store last).

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

### An int parameter used as a pointer: no base for the alias test (func_0019C9C8)

func_0019C9C8 took its cell as `s32 b` (the caller's word from func_0019D0E0) and read
`((s32*)b)[i]` after storing three Vec02 locals. With an int parameter the cell's address has no
REGNO_POINTER_FLAG (the rule in "Alias classes": a pointer parameter's base never conflicts with
frame stores; seen in the output, not traced in alias.c), so the read may alias the frame stores:
sched1 kept the load after the normal's stores, and the body's order, the VU0 registers
and global-alloc's ranking (every register one too high from the first insn) followed. Typed as a
pointer (`GridCell* cell`), the read has the argument's base, never conflicts with a frame store,
and the whole first loop matches (100 lines to 7). The tell: a word read through a parameter
scheduled late behind `sqc2 ...(sp)` stores in ours and early in retail; check the parameter's
type before anything else. The same function needed one `i` for both outer loops (retail keeps
`i` in one register in each and reuses it for `i * 4`) and its corner array read as a struct
member (`cell->corner[k]`, base first in the `addu`, where `corner[k]` through a plain pointer
puts the index first).

Still open there: retail copies `block` into a fresh register at the top of each iteration of the
second outer loop and starts the inner loop's reduced pointer from the copy. Ruled out: a
per-iteration `f32* out = block` (GCSE's cprop propagates the copy into the inner loop and it
dies); `out = (f32*)self->slots` (PRE turns it into a copy in pass 1, cprop pass 2 propagates it,
and PRE's reaching register is inserted in loop 1 and hoisted to the top by loop.c); a biv
`out += 8` (it is the inner pointer itself); the same loop in an inline helper; `*record++`.

### A switch's case constants in a loop with calls: savings and life 1 (func_00130C58)

Read from loop.c (scan_loop, combine_movables, move_movables), stmt.c (emit_case_nodes) and
mips.c (gen_conditional_branch) with `-dL` dumps (2026-11-10, nonmatching/func_00130C58.cpp,
the curve-window search: four quadratics per curve chosen by `switch (j)` over `j < 4`):

- **What retail shows.** The inner loop's compare tree is `beq j,1; slti j,2; beqz j; beq j,2;
  beq j,3`. Retail keeps 2 in s6 and 3 in s8 (both hoisted before the outer loop, between the
  float constants: 4.0, 2, 6.0, 3, -2.0, -6.0) and loads the 1 in the loop (`li v0,1`). Ours
  keeps the 3 in the loop: s8 is not saved, the frame is 16 bytes smaller and the case-2 branch
  keeps `li v0,3` in its slot.
- **Why ours stays.** Each EQ compare against a non-zero constant forces the constant into its
  own pseudo right before the jump (gen_conditional_branch), so the set has life 1 and savings 1
  (savings is n_times_set). combine_movables adds the life and savings of other sets of the same
  constant: the 2 matches `found == 2` (life 2, savings 2) and moves at threshold 79; the 3,
  considered next at 76, needs `76 * 1 * 1 >= 104` (the inner loop's count in pass 1; 90 in
  pass 2 at 79) and stays. The 1 stays for the same reason. Luids count non-line notes, but
  nothing sits between a tree constant and its jump.
- **Retail moved the 3 in pass 1, probably the 1 too.** Built with `-fmove-all-movables` (to
  explore only) the 1, the 2 and the 3 all move in pass 1, global-alloc gives 2 and 3 s6 and s8,
  the 1 gets no saved register and reload rematerialises `li v0,1` in the loop: retail's code
  and preheader order exactly, apart from one block (below). So retail's 1 and 3 each had
  `savings * life >= 2` with the loop near 104 insns, or the loop was at most 73 insns in pass
  1 (or 76 in pass 2). With four calls in the loop (each case sets a0 and calls; cross-jumping
  merges cases 2 and 3 only after sched2) no form found is that small: one call after the
  switch gives 88 and 74 insns, and pass 2 then moves the 1 and the 3, but its code is not
  retail's.
- **Ruled out:** the case order (sorted anyway, the tree is fixed by balance_case_nodes), `j <=
  3` (gen_int_relational turns LE into `lt 4` with no register), the counter's type (u32, s16,
  u16, s8, u8), the switch inside an inline function, `j == 3 ? -t : t` in case 3 (cse1 folds
  it on the case's path, so no second 3 reaches loop.c), `case 2: case 3:` with a shared body
  (grouped into a range: a different tree). A second set of the constant that cse1 cannot fold
  and a later pass removes is what is missing; not found.
- **The one other block.** Even with every constant moved, the block after the outer loop
  differs: PRE hoists FLT_MAX's `%hi` (the search's start value) to the end of the entry block
  (LCM puts an expression anticipated through the loop at its earliest point), update_equiv_regs
  moves it back before its use, and local-alloc gives it v0 (2 refs over 2 insns outranks the
  window count's subtraction, over 3), so `lui v0` leads and the subtraction takes v1; retail
  subtracts into v0 and loads `lui v1` right before the `lwc1`. The order of `found = w -
  windows`, `best` and `k = -1` and a named global for FLT_MAX change nothing.

### The 3's second set: what cse1 cannot fold behind a LOOP_END, loop.c matches and cse2 folds (func_00130C58)

Read from cse.c (cse_end_of_basic_block, record_jump_cond, fold_rtx), loop.c (scan_loop,
combine_movables), jump.c, flow.c and haifa-sched.c of GCC 2.95.3 with the `-dj -ds -dG -dL -dt
-df -dS -dl` dumps (2026-11-12, w35; nonmatching/func_00130C58.cpp). It answers the section
above with a probe that is EXACT on US and PAL under the file's own flags. The probe is not
plain C++ as AGENTS.md has it (two `do { } while (0)`), so it is a result about the compiler
and not a match:

    case 3:
        do { } while (0);
        found = SolveQuadratic(j == 3 ? -t : t, c[1] * -2.0f - c[3] * 4.0f, ..., w);
        break;
    ...
    do { found = w - windows; k = -1; } while (0);
    best = 3.4028234663852886e+38f;

- **A second set that leaves no reference.** Retail's 3 takes s8 after n (s7) and the 2 (s6),
  which global-alloc gives only when the hoisted 3 has the tree's use alone at flow time (the
  probe's r196: "used 4 times across 186 insns", the set at depth 1 and the use at depth 3).
  `if (j == 3) { k = 0; i2 = 0; }` after the switch (two dead stores, so that jump.c does not
  make it a conditional move) does hoist the 3: loop.c matches its `(set X 3)` with the tree's
  (savings 2, life 2), flow deletes the stores and jump2 the jump to the next insn. But the
  jump is a third reference of the 3 until then, the 3 outranks the 2 and n, and the registers
  come out s6 = 3, s7 = 2, s8 = n. So in retail the second set's use was gone before flow.
- **cse1 stops at a NOTE_INSN_LOOP_END, cse2 does not.** cse_end_of_basic_block ends a path at
  a LOOP_END note unless it runs after loop.c ("Don't cse out the end of a loop"). Behind such
  a note in case 3, cse1 no longer knows `j == 3` from the tree's jump, so the test keeps its
  own `(set X 3); bne j,X` through gcse (the .cse and .gcse dumps have two sets of 3). loop.c
  matches X with the tree's pseudo ("Insn 318: regno 196 (life 2), move-insn savings 2 moved":
  76 * 2 * 2 >= 107), deletes X's set and rewrites the test as `bne j,H`. cse2 follows the
  tree's `beq j,H` into the case (one use, a barrier before the label), runs through the note
  and folds the test, the jump pass after it removes the dead arm, and nothing is left: the
  .loop, .cse2 and .flow dumps have one set of 3. The 1 is not moved; retail's `li v0,1` is the
  loop's own.
- **What cse2 can fold.** After the move the constants are registers set outside the loop, so
  cse2 knows no values, only the path's facts: `j` equal to the register of the case it
  followed, and one remembered inequality per quantity (qty_comparison_code, the last `beq`
  not taken; read from fold_rtx, not measured). A test of j against its own case's constant
  folds; `j == 1 ? t : -t` in case 3 does not (measured: the 1 moves too, the test stays, 114
  lines differ). That rules out one generic expression repeated in every case.
- **cse1 folds everything it can reach.** An inline `SignedLimit(j, t)` with a `switch (j)` of
  four cases, used as the first argument in every case: cse1 follows the tree's jumps
  (follow-jumps takes each label with one use behind a barrier, also the inner tree's), folds
  all of it and deletes the sets (106 insns, no second 3, the near miss's code). What cse1
  cannot reach is code behind a label with two uses (a join) or behind a LOOP_END.
- **The block after the loops: loop depth and a barrier.** Retail has `subu v0; li a1,-1; sra
  s2,v0,2; lui v1; lwc1; addiu a2`; ours had the `lwc1` between `subu` and `sra`, the `%hi` in
  v0 and the subtraction in v1. With `found = w - windows; k = -1` inside a loop's notes and
  `best` after its LOOP_END: (1) the first insn after a LOOP_BEG or LOOP_END note depends on
  everything before it in sched1 and in sched2 (sched1.md, func_0014D680), so the load stays
  behind `sra`; (2) flow counts references with the loop depth, so the subtraction's pseudo has
  4 references over 3 insns ("Register 200 used 4 times across 3 insns in block 20") and
  local-alloc ranks it (2 * 4 / 3) above FLT_MAX's `%hi` (1 * 2 / 1, moved back before its
  load by update_equiv_regs): it takes v0, and the `%hi`, whose widened life touches it, v1.
  All 60 placements of one `do { } while (0)` (or of one unreachable loop, whose two notes stay
  when flow deletes it) over the three statements in their six orders were compiled with
  `-fmove-all-movables` (to explore only): the two with `found` and `k` inside, in either
  order, and `best` behind are the only ones that match. Notes around `best` alone give the
  order and the subtraction's v0 but the `%hi` in v0 too; a dead loop between `k` and `best`
  gives the order with v0 and v1 swapped.
- **The alignment test passes.** final.c's shorten_branches gives the first CODE_LABEL after
  every LOOP_BEG note the loop alignment (sched1.md, func_001DEBE8). The labels that follow the
  probe's two notes are at 0x130DD0 and 0x130E68 in retail, both 8-aligned with no nop, so
  retail does not contradict a LOOP_BEG at either place (the probe's assembly has `.p2align 3`
  before both, which pads nothing; one in two by chance, each).
- **Not found: the plain source.** The i loop cannot own the second pair of notes: the copy of
  its exit test jumps past its LOOP_END to the subtraction, and written with the two
  statements in a break's body (`for (i = 0; ; i++) { if (i >= n) { found = ...; k = -1;
  break; } ...`) jump.c's copy enters the loop from outside and loop.c ignores the loop
  ("multiple entry points": the constants stay in the loop, 161 lines differ). The search
  after it as a `while`, a `for (;;)` with a `break` or with a `return` is rolled or reduced by
  loop.c (retail's is neither). What retail's source needs is a loop statement that runs once
  around the two assignments, and in case 3 a test of j against 3 behind such a statement's
  end (or behind a join that the jump pass after cse1 removes).
- **The tell, for other walls.** A constant hoisted with life 1 in a loop over 80 insns, a
  pseudo ranked as if it had twice its references, or an order only a barrier gives, with
  retail's next label 8-aligned: look for a statement the original wrote as a loop that runs
  once. A label at 4 mod 8 with no label between it and the place rules a LOOP_BEG out there; a
  LOOP_END aligns nothing.

### An inline's constant parameter is a variable with a life: the strip loop's UNPACK words (func_00166690)

Matched 2026-11-10 (DrawModelPart, src/main/placed_object_model.cpp; the form found by worker
w14-1536C8, the mechanism read from w15-166690's `-dL` dump). The part drawer's strip loop is
333 insns in pass 1 and 304 in pass 2 and makes no call (threshold 160, less 3 a move). Retail's
preheader holds `&D_002623E0` (s8), the constant 1 (t9, both `q.hi = 1` and `count == 1`) and
D_00262474's `%hi` (t8); the UNPACK command words 0x6C0BC000 and 0x6C01C01A are built in the loop.

- **Why ours hoisted the command words.** Passed as a parameter (`Unpack(w, 0x6C0BC000, src,
  size)` calling `Word(w, cmd)`), the constant goes through integrate.c's parameter copy: the
  argument is copied into a REG_USERVAR pseudo at the inline's entry with a constant
  equivalence, which try_constants cannot put into the store (a MIPS store needs a register), so
  the pseudo stays and lives from the inline's entry to the store: `.loop` shows `reg/v` with
  life 5 and 6, moved at `160 * 5 >= 333`. Hoisted, they live over the whole loop and
  global-alloc gives them t9 and t8; `&D_002623E0` and 1 are then spilled and rematerialised at
  each use (24 bytes more, every register after them shifted).
- **Retail's form.** `UnpackV4(w, src, num, addr)` stores `(num << 16) | addr | 0x6C00C000`
  itself: the literal is formed at the store (life 1, "not desirable"), as `(n << 16) |
  0x6000C000` already was for the skin's words. The S-32 size is written `n << 2`, and UnpackAt
  takes its source first (`(w, src, size, cmd, addr)`), so the source's address is expanded
  before the command in the bone loops' preheaders, in retail's order.
- **The jump tables.** The function's two switches emit jtbl_0024A750 and jtbl_0024A780, so
  their INCLUDE_RODATA lines go (left in, .rodata is 0x50 bytes too large).
- **The tell.** A command word or other constant hoisted into a saved register in a big loop
  where retail loads it at its store: look in `.loop` for a `reg/v` constant with a life above 1;
  it is an inline's parameter, and retail formed the word inside the helper.

### A PRE'd invariant ahead of the entry jump makes the loop phony (func_001EEA40)

- **What differed.** A plane-tree walk (`for (;;) { ... if (d < -radius) ...; if (next &
  0x80000000) { ...; break; } node = next; }`) tested bit 31 with `bgez` and had no `s3`; retail
  hoists `lui s3,0x8000` before the loop and tests `and v0,a1,s3; beqz v0` at each use, with a
  frame 16 bytes larger for the saved s3.
- **Why.** GCSE runs before loop.c. PRE hoisted `-radius` (loop-invariant, used in the body) to
  just after NOTE_INSN_LOOP_BEG, in front of the loop's entry jump to its rolled exit test.
  scan_loop then finds an insn, not a label or the entry jump, as the first thing in the loop
  and prints "Loop from N to M is phony" (`-dL`): nothing moves. The mask's set stays in the
  loop, combine folds `(ne (and x 0x80000000) 0)` into a sign test, and the constant disappears.
  Once loop.c moves the set to the preheader, the mask is a register set once outside the loop
  and used twice inside: combine cannot merge it (it does not die at the use), so the `and`
  stays.
- **The form.** `f32 near = -radius;` named before the loop puts the negation ahead of
  NOTE_INSN_LOOP_BEG. That gives the `and`, but `for (;;)` with `break` still leaves an entry
  jump whose delay slot reorg fills with the negation (the `li` of 0x80000000 has length 2 and
  cannot go there), so the preheader read `lui; neg.s` where retail has `neg.s; lui`. A
  `do { ... node = next; } while (!(next & 0x80000000));` followed by the leaf's expansion has
  no entry jump: retail's order, EXACT. The middle test reads `else if (radius < d) next =
  n->back; else { next = n->back; ... }` (retail branches out to the bottom test on `radius <
  d`), and the recursive call's argument moves (`mov.s $f12` before `move a3`) need the radius
  before `out` in the prototype, as the caller QueryValueListMask's own `(self, radius, vec,
  out)` has it.
- **Spotting it.** A `bgez`/`bltz` where retail keeps `and` with a register holding
  0x80000000 (or any constant that needs a `lui`): read `-dL` for "phony", and look for a PRE'd
  expression right after the loop note.

### Two passes in the preheader, and a loop 15 insns too big (func_001D9488, near miss)

Read from `-dL` dumps (2026-11-10, AdvancePathFollowerEntry, nonmatching/func_001D9488.cpp).
Retail's preheader, after the entry test, is `li s8,1; addiu s2,s0,0x874; li s7,-1; li s6,0x42F;
li s5,0x430; lui s4,%hi(D_00261EF0)`, with `move s3,zero` in the `blez` delay slot.

- **The marker is taken by index.** `addiu s2` after the entry test is a reduced giv's start
  value (loop.c puts it in the preheader), not a walked pointer's (`e = self->f874; ... e++`
  sets it before the test, in the first block). `PathMarker* e = &self->f874[i];` at the top of
  the body is retail's: `li 40; mult` reduced to s2, and the prologue's save order then matches
  too.
- **1 in pass 1, the rest in pass 2.** The giv's start sits between 1 and -1, so pass 1 moved
  the `li 40` (life 1) and the kind test's 1 (life 1), reduced the giv, and stopped at -1; pass 2
  moved -1, 0x42F, 0x430 (life 1 each) and the `%hi` (life 2 once pass 1 folds its `lo_sum`
  into the argument move). With threshold T falling 3 per move that needs T >= N1, T-3 >= N1,
  T-6 < N1 in pass 1 and T-6 >= N2 in pass 2.
- **Measured.** The file's threshold is 79 (a loop of 80 does not move a life-1 constant, 79
  does). Ours counts N1 = 91, N2 = 87, so nothing moves in pass 1. The same source is EXACT
  with `-mvu0-use-vf0-vf30` or `-vf31` (T = 94, 95: each freed VU0 register adds one), and
  `-dL` then shows retail's exact split. So the source is retail's in everything but the loop's
  size at the loop pass: at T = 79 retail's pass 1 must count 74 to 76 insns, 15 fewer than ours.
- **Not a flag.** vf30/vf31 for every game file changes 115 functions in 22 files, among them
  the loop-tuned matches of this chapter (func_00140258, func_001971B8, func_00192DD0,
  func_001CF158, func_00154370) and two in this file (func_001D66A8, func_001D9AC8); the
  threshold 79 stands.
- **Where 15 insns could go: not found.** Accounted for in pass 1: the giv's four insns, five
  moved constants, four call-result copies that combine removes, the `&key` copy, flow's
  `(use (const_int 0))`, two single-use pseudos pass 1 substitutes, a jump: ours' 91 is the
  final code's 74 plus exactly these. Statement forms change one insn at most (an if/else for
  the key's switch: 90; `self->f874 + i` and byte-offset index forms: 91). Lifetimes can't do it:
  a compare's constant is forced into its register right before the jump (life 1), and a named
  constant at the loop's top moves in pass 1, before the giv's start, against retail's order.

Solved (2026-11-10, w15): the copy is a PRE copy kept by being used in its own block. Retail
had no `block` variable: each loop takes the slots' address itself, inside its body
(`f32* out = (f32*)self->slots; out[k * 8] += ...;`, the zero loop the same, the call passing
`self->slots`). Read from the `-dG` and `.loop` dumps:

- **PRE inserts the address once and copies it at each use.** `self + 0xE4` is never locally
  anticipatable in the entry block (the parameter's copy from a0 sets `self` before it), and 2.95's
  lcm only counts ANTLOC occurrences as computations, so a computation at the top is not
  available to the later ones: PRE inserts the expression into a new pseudo (here in loop 1's
  body, which loop.c hoists to the entry: retail's `addiu t4,t3,228`) and turns every occurrence
  into a copy of it.
- **cprop removes a copy only into other blocks.** Its copy propagation is global only: a copy
  used in its own block survives. In the inner loop's body, `out = R; mem(out + k*32)` keeps the
  copy; loop.c's inner pass moves it to the inner preheader (the outer body) and reduces the giv
  from it (`move v0,a2`), and the outer pass moves it again to the outer preheader, after the
  constant 100 (`move a2,t4`). The same copy declared in the outer body (`out = ...` once per
  corner) is used only in the inner loop's block, so cprop pass 2 propagates it and it dies.
- **No separate `block` pseudo.** With `f32* block = (f32*)self->slots;` at the top, the entry
  computation is a second pseudo beside PRE's (two registers, `move t8,t4` at the entry);
  declared just before the zero loop it is a PRE copy in another block that cprop removes (also
  EXACT). Writing the address in each loop, as the near miss's callers' `self->slots` already
  did, is the form landed.
- `((f32*)self->slots)[k * 8]` and `*(f32*)&self->slots[k]` fold the 0xE4 into the memory
  offset (`lwc1 228(v0)`): the address has to be a named pointer.

The tell: a reg-reg copy in a loop's preheader that feeds only the inner loop's reduced pointer
is a PRE copy of an address the original wrote inside the inner loop's body.

### A pointer set in an inner loop too is no giv of the outer loop (func_00187260)

CollectMeshHits's vertex pass searches the edge hits (`out[q]`, an inner loop) and then writes
a hit through `o = &out[n++]`. Ours reduced the whole address `out + n * 48` into one register
(`addiu a3,a3,48`, stores at -48(a3)); retail reduces `n * 48` alone (`mult t3,s2,v1` in the
preheader, `addiu t3,t3,48` per hit) and adds the base in the loop (`addu a1,s8,t3`). The .loop
dump of ours: `Insn 2396: giv reg 130 src reg 124 ... mult 48 add (reg/v:SI 122)`, combined with
every store's DEST_ADDR giv and reduced.

- **strength_reduce takes a DEST_REG giv only where the register is set once in the loop**
  (`VARRAY_INT (n_times_set, REGNO (dest_reg)) == 1`, or consecutive sets that make one giv).
  n_times_set counts every set between the outer loop's start and end, the inner loops'
  included. When the inner search reads its records through the same pointer (`o = &out[q];
  ed = (MeshEdge*)o->part;`), o is set twice in the outer loop and is no giv there; `n * 48`
  (its own pseudo) stays a giv and is reduced alone, and the stores, addresses off a non-giv,
  stay as they are. In the inner loop o is set once, but there the record's `part` address
  (`q * 48 + 40` plus out) was already the reduced giv, and the code does not change.
- **The reload side.** Ours's whole-address giv was set in the preheader by a `madd`
  (`*mul_acc_si_r5900`, four scratch clobbers), whose reload made a1 a spill register
  (`Spilling for insn 2712. Spilling reg 5.` in .greg). That one spill register, 1,400 bytes
  later, shifted the round robin ("The reload register's round robin", reloads-and-stores.md)
  of every qmfc2/mfc1 temporary at the top of the function: a0, a1, a3, v0 where retail has
  a0, a3, a0, a3. The register set of the whole function is the tell: count the `Spilling reg`
  lines of .greg and look for the one that retail's rotation skips.

### A loop's own counter frees a saved register for a hoisted %hi (PAL func_eu_001DDC68)

PAL's copy of LoadWorld adds a 14-entry loop to US's two counted loops. Reusing US's `i` for it
makes the counter one user variable set six times over all three loops: one pseudo, one saved
register (s3), with the third loop's pointer reusing another. Global-alloc then has a saved register
left for the `%hi` of g_activeListFrames that PRE hoisted to the entry block (4 refs across 314
insns, the lowest-ranked of the candidates that still get one), so ours keeps it in fp as US does.
Retail allocates nothing for it (a fresh `lui` at each use) and holds the first two loops' counter
in s0 and the new loop's in s1, with the five member addresses in s4-fp: the new loop had a counter
of its own. `for (s32 k = 0; k < 14; k++)` instead of `for (i = 0; ...)` was EXACT. Spot it: a
counter in a different saved register in one loop than in the loops before it.

### A count-up loop with no vtop, and a giv loop.c never finds (func_0013AD80, solved below)

The draw of the frames list in func_0013AD80 (for each mesh, `for i < count` over 0x50-byte
frames, ten calls in the body) counts up in retail (`addiu s4,1; lw v1,count; slt; bnez`,
`addiu s2,s2,0x50` for the frame) where a `for` with a pointer walk (`f++`) is reversed. From
the `-dL -dl -dg` dumps (2026-11-10):

- **The count is a spilled pseudo, not memory.** frames, count, the Ones vector and sent sit at
  0xB8, 0xBC, 0xC0 and 0xD0 after every expand-time local (the second loop's p and q are at
  0xB0/0xB4): reload's slots, given in regno order, so `sent` is declared where it is set (after
  the first walk) and the Ones vector's pseudo, from the first loop's body, comes before it.
  count is re-read each pass because it is spilled; at the loop pass it is an invariant register.
- **check_dbra_loop with a register bound.** A counter used only for counting is reversible
  even with calls (`no_use_except_counting`). With a non-constant bound the first form (a
  constant comparison) does not apply and the NE form needs `loop_info->vtop`: a loop with no
  NOTE_INSN_LOOP_VTOP is not reversed ("Can reverse loop" in the dump, then nothing). jump.c's
  duplicate_loop_exit_test gives every `for` and `while` a vtop here, so the counter has to be
  used in a giv (loop.c then cannot reverse it with calls) or the loop has to be a do/while.
- **The doubling of a counter's life.** In a do/while behind `if (count > 0)`, `i = 0` keeps
  its REG_EQUAL note and update_equiv_regs doubles i's life (88 to 178 insns): i then ranks
  below the bank pointer and the two saved registers swap. Behind `if (i < count)` combine
  folds `i = 0` into the guard's compare, as it does with jump.c's copied test of a `for`, and i
  keeps its life (s4, as retail).
- **Retail's shape is a reduced giv.** Retail sets i = 0 before the guard and the frame pointer
  after it, and PRE does not hoist `&fade` (sp+112, also the first loop's rotation): exactly
  what `for (i...) { ViewedFrame* f = &frames[i]; ... }` gives when strength reduction finds f
  (the reduced giv's start value is emitted by loop.c in the preheader, after GCSE; a source
  `f = frames` inside the guard instead gives PRE a block to insert &fade in). Measured by
  removing calls: the giv is found once the `li 80` before the `mult` moves, which at life 1
  and savings 1 needs at most 79 insns in pass 2 (76 moves it, 80 does not); this loop has 84
  (95 in pass 1). Not found yet: what gives retail's 80 a longer life or a second matching
  movable. Ruled out: `frames + i`, `&frames[i]` in the call, a byte-offset cast, the fade read
  as `frames[i].fade` (one mult after CSE), four WriteVifFlush calls (one after the switch is
  retail's tree and 7 insns fewer).

- **The `li 80` needs a life of 2, not a second movable (w37-f2, 2026-11-12).** Three compiles
  of the `for` form with `-dL`. (1) `ViewedFrame* f = &frames[i];` at the top of the body: the
  `li 80` is the loop's first movable in both passes (threshold 79), life 1, 95 and 84 insns:
  `not desirable` twice, the mult stays (1720 bytes). By my count the 84 are the final code
  plus three argument copies (`t0 = hdr[0] + n`) and two of flow's `(use (const_int 0))`. (2) A second index expression behind a CSE path break (a probe:
  `&frames[i]` in the call, a run-once loop, `frames[i].fade`) gives a second `li 80`, which
  combine_movables matches (`regno 398 (life 2), move-insn savings 2 moved`, `regno 404 done
  matches 1095`), but each expression is then a giv family of its own and loop.c reduces two
  pointers (`move s4,v1; addiu s5,v1,64`): retail's one `addiu s2,s2,0x50` means one family, so
  one `li 80`. (3) loop.c's luids count every note that is not a line number (the func_001D7778
  section below), so a single `li 80` separated from its `mult` by a note has a life of 2 or
  more and moves in pass 1 (79 x 2 >= 95). A probe with the stride as an inline's constant
  argument (the copy to the parameter is emitted before the expansion's two block notes: life 3)
  shows it: `Insn 1092: regno 396 (life 3), move-insn savings 1 moved`, both givs found, `giv
  at 1123 combined with giv at 1096`, and the function's first loop then has retail's s1 and s2
  (obj and the frame pointer), which the unreduced forms swap. That probe is 1732 bytes: from
  the first loop's exit on, the two early-exit tails are no longer merged; not followed
  further. What is still to find is the plain form that leaves one non-line note between the
  `li 80` and its `mult` (or a loop of 79 insns at most in pass 2).
- **Solved (w38-f5, 2026-11-12): neither; the threshold is 94 in this file.** The `for` form
  of item (1) is EXACT once the file builds with `-mvu0-use-vf0-vf30`: the `li 80` stays in
  pass 1 (94 < 95) and moves in pass 2 (94 >= 84). See "A threshold of 94" at the end of this
  chapter.

### Life-1 invariants that reload rematerialises: a `lui` in a loop with every saved register taken (func_0013A618, near miss)

Read from loop.c (move_movables) with `-dL` dumps (2026-11-10, nonmatching/func_0013A618.cpp, the
scratchpad transfer loop of a WorldListedObject's owned records). Retail's loop starts with `lui
a3,%hi(g_toSprChannel)` (copied by reorg into the bnez slot and before the label) and forms
`lui a3; addiu a3,%lo(D_002748F0)` again inside the loop; ours forms the first in v0. All nine
saved registers (s0-s8) hold values here, so an invariant loop.c moves gets no register and
reload rematerialises it from its REG_EQUIV at each use, in a reload register (a3 in both
places). That is what retail shows for the `%hi` of g_toSprChannel: loop.c moved it. Ours stays
in the loop because its life is 1 (the `%hi` and the `lw` that uses it are adjacent: the call's
argument is expanded into the move to a0): `80 * 1 * 1 < 95` insns in pass 1 (87 in pass 2).
Written `void* const& ch = g_toSprChannel;` at the loop top (a reference makes the address its own
insn, life 2, so `160 >= 95`), the `lui a3` comes out exactly as retail's, which confirms the
mechanism; but the preheader then loses retail's `move v1,v0` (the move happens in pass 1 and
changes the preheader's order), and the form is not plausible code. Retail's 1 of `1 -
D_00274990` (`li v0,1` with the result in the loaded register's v1, where ours ties the result to
the constant's pseudo) is probably the same: a moved, rematerialised constant. As func_00130C58
above: what gives retail's life-1 invariants their move is not found.

### Memory givs absorbed by a multi-use address giv (func_0013A940, near miss)

Read from loop.c (combine_givs, combine_givs_p) with `-dL` (2026-11-10). Retail's particle loop
keeps the four call-argument addresses (&cur->pos[j], &cur->vel[j], &nxt->pos[out],
&nxt->vel[out]) as reduced registers of their own and bases every memory reference on the rec
arrays' givs (cur + 0x580 + 16j, nxt + 0x580 + 16out, with negative offsets). combine_givs sorts
by total benefit (own benefit, +1 for a zero addend, + each combinable giv's benefit + 3) and
breaks ties by the giv list's order (newest first); a DEST_REG giv used once may not absorb
others. Ours computes &cur[j] once into a pseudo that several statements share (CSE), a
DEST_REG giv with several uses: it ties at 116 with another and absorbs every memory giv, so the
loop has one reduced register fewer, the bivs (removed, j, out) take the saved register left over
instead of retail's caller-saved a7/t0/t1 (saved around both calls with sq/lq), and the function
is 12 bytes short. The array form (Vec02 indexing or a bank struct of three arrays) does not
change it.

### Three invariants ranked by their place in loop.c's move list (func_001D7778, solved below)

Measured on 2026-11-10 with tools/globalalloc.py and tools/sched1.py (StepPathFollower's wheel
loop, nonmatching/func_001D7778.cpp). The loop's saved registers s6, s7, s8 go to three
invariants moved in pass 1: the push curves' addresses D_002753D0 (pseudo 288) and D_002753E0
(316), and the copy of PRE's `&spin` (381, `381 = 966`, 966 being PRE's `sp+112` inserted
before the loop for delta's use after it). Each has 5 refs (a set outside the loop plus two uses
at loop depth 2) and lives to the loop's end, so global-alloc ranks them by birth alone; the
fourth candidate, B0's address (227, also 5 refs, born first), loses and is rematerialized.

- **The ranking needed.** `--set 381:length=402 --set 288:length=400 --set 316:length=398` (or
  381 at 404) gives retail's s8, s7, s6 with every other disposition unchanged. 381 has to be
  born after 227 (at 406 or longer it falls to 246 and below, ties go to the lower pseudo, and
  227 takes s8 while spin is spilled) and before 288.
- **sched1 keeps loop.c's order.** In the preheader block every moved `lo_sum` and the copy are
  raised to priority 2 (birthing), all have weight 1 (no deaths yet in `.regmove`), class 3 and
  no dependents, so the LUID decides: replaying the block with the copy moved earlier in the
  block (a small script around sched1.Replay) gives retail's birth order for any place after
  B0's `lo_sum` and before D0's `%hi`; before B0's `lo_sum` it issues ahead of it (bad); after
  D0's `%hi` it stays last (ours). Removing the zero copy (3060) or the load before it changes
  nothing. Giving the copy weight 0 (its source dying) issues it at cycle 2, ahead of B0 (bad).
- **loop.c's order is the body's.** All of 497/498 (B0), 516/517 (C0), 626 (0.0), 728/729
  (D0), 812/813 (E0) and 1052 (the copy) move in pass 1, in insn order (the threshold falls by
  3 per move, 80 to 50, far above what lifetimes 5 to 12 need at 189 insns). The copy sits where
  cse1 computed `&spin`, at ApplyColliderInverseInertia's arguments after the push test; retail
  needs it between the slip statement (B0, C0) and the push (D0), where no statement takes
  spin's address. D0's `%hi` cannot move to pass 2 instead (it would need a lifetime of 3 in
  both passes; its `lo_sum` and c[0] load give 9).
- **Ruled out.** `Vec02* out = &spin;` or `Vec02& out = spin;` after the slip statement, with
  the calls taking `out` (697 lines): the user variable's copy has lifetime 0 in loop.c ("not
  desirable"), the loop reads PRE's 966 directly and B0's address takes s8.
- **The only other ranking that works (wave 22, 2026-11-11).** With the copy born last, retail's
  order (E0, D0, spin, then B0 left without a register) also follows if D0 and E0 each had one
  more use in the loop (7 refs, floor_log2 2: priority 14 per life against spin's 10). Retail's
  code rules it out: c[0] is read through the symbol's own %hi/%lo and only c[1] and c[2] through
  the pointer, as in ours. The along and sum conversions as the "*r" ToFloatMoved change nothing.

### Solved: a curve indexed in place has a life of 3, and loop.c's second pass moves it (func_001D7778)

Matched on 2026-11-12 (w37-f2). The copy of `&spin` was never out of place: the push curves'
addresses were. Retail's preheader order (B0, C0, the copy, then D0 and E0) is what loop.c gives
when D0's and E0's `lo_sum` are left by the first pass and moved by the second
(`-frerun-loop-opt`), whose insns come after everything the first pass moved.

- **What decides it.** move_movables moves an invariant when `threshold * savings * lifetime >=
  insn_count`. The loop has 189 insns in pass 1; this file's threshold is 79 (the func_001D9488
  section above) and falls by 3 per move, so it is 58 when D0's `lo_sum` is reached (after 163,
  228, 227, 239, 238, 268 and D0's `%hi`) and 55 at E0's. With a lifetime of 5 the products are
  290 and 275 (moved, ours); with 3 they are 174 and 165, under 189, and the dump says `not
  desirable`. Pass 2 starts again at 79 with 175 insns: 237 and 228, both moved, after pass 1's
  copy of `&spin`. B0's `lo_sum` is reached at 73, so it moves in pass 1 with either lifetime
  (219 at 3). The dumps give the decisions, not the threshold: any start from 69 to 83 gives the
  same split here.
- **Where the lifetime comes from.** loop.c's luids count every insn and every note that is not
  a line number (compute_luids), so NOTE_INSN_BLOCK_BEG and NOTE_INSN_DELETED count. An inline
  method called on a constant address (`((QuadraticCurve*)D_002753D0)->Eval(t)`) copies the
  address into its `this` before the two block notes of the inline expansion (integrate.c:
  process_reg_param runs before expand_start_bindings): `lo_sum`, BLOCK_BEG, BLOCK_BEG, load
  c[2], mult, load c[1] is a lifetime of 5. The global array indexed in place
  (`D_002753D0[0] + t * (D_002753D0[1] + t * D_002753D0[2])`) forms the base address at the
  first element with an offset, right before its load: `lo_sum`, load, mult, load is 3 (the
  second element's own `%hi`/`lo_sum` pair folds into the first in cse1). Both forms read c[0]
  through the symbol's own `%hi`/`%lo` and c[1], c[2] through the base, so the loop's code is
  the same; only the pass that moves the base differs.
- **Confirmed.** With the two push curves indexed in place the loop dump reads `Insn 796: regno
  306 (life 3), move-insn savings 1 not desirable` and `Insn 822: regno 324 (life 3) ... not
  desirable` in pass 1, both `moved` in the second `Loop from 94`, and tools/check.py prints
  EXACT on us and eu. A pointer local inside the inline (`const f32* p = c;`) changes nothing
  (the copy folds into `this`, lifetime 5).
- **Reading it elsewhere.** An invariant address that retail's preheader issues after a later
  statement's invariants, with the same loop code, may be a second-pass move: check its
  lifetime against `threshold * lifetime < insn_count` at its place in the first pass, and
  count the block notes between its set and its uses. Two notes are the difference between an
  inline's parameter and an expression written in place.
- **A second route, probed and not needed.** A dead early copy of PRE's reg also reorders the
  list: with `Vec02* out = &spin;` after the slip statement and the calls still taking `&spin`,
  the pointer's `247 = 966` is a movable of lifetime 0 that the calls' `382 = 966` matches
  (combine_movables: same source), so the pair moves at the pointer's place (`Insn 551: regno
  247 (life 12), savings 2 moved`, `Insn 1056: regno 382 done matches 551`) and global-alloc
  gives retail's s8, s7, s6. It needs a use that keeps the pointer through cse1's dead-insn
  pass and leaves no code, which no plain source gave (the probe used an extra call). Why the
  earlier pointer attempt failed is GCSE's second copy-propagation pass: a copy of PRE's reg set
  in an earlier block than its uses is propagated into them (`a2 = 966`), the pointer is left
  with no use, and the loop reads the spilled 966. A copy in the same block as its uses (ours,
  at the first call) is not propagated: cprop only uses sets available at a block's start.
  loop.c also substitutes a single-use copy into its use in a loop with calls (scan_loop's
  `reg_single_usage` case): that is why `&torque` is read from PRE's spill slot
  (`lw a1,280(sp)`).

### Named constants that lose their registers: five loads reload forms again in the loop (func_00131F60)

Matched on 2026-11-12 (w38-f6). The gauge loop of DrawTextPanelControlLabels loads 1/9, 1/15, 55,
0.5 and 372.8 inside the loop (`lui at; mtc1`) and keeps 1.0, 9, 60, 320, 1728, 16, 0.4545 and
1936 in $f27, $f31, $f30, $f26, $f25, $f23, $f29 and $f28. The near miss read the five loads as
the loop's own: two scratch floats set more than once (`d` = 1/15, then a product, then 372.8;
`k` = 55, then 0.5), which loop.c does not move, and the eight as locals set before the loop.
That gave retail's code but for one local-alloc tie against a global-alloc ranking that no order
of the statements satisfied (long-block-constants.md, "A scratch float in a loop"). Both were
artefacts of the invented scratch variables. Read from the `-dL`, `-dl` and `-dg` dumps:

- **Every constant of the loop was moved out; five got no register.** The loop holds four values
  across its calls (x0, x1, y0, y1), so eight of the twelve saved float registers are left and
  twelve constants want them. global-alloc ranks by `floor_log2(refs) * refs / life`, a use in
  the loop counting 2 and the preheader's set 1: 16.0 (13 refs), 320 and 1728 (9), 1.0 (7) go
  first; the constants with two uses (5 refs) are ranked by their life, which is the loop plus
  their place in the preheader, so the ones loop.c moved first (the earliest in the loop) come
  last; the ones with one use (3 refs) after them. A moved constant with no hard register has
  a REG_EQUIV note, so reload deletes its set and loads the constant before each insn that
  uses it, in the first register (reg_alloc_order) that no pseudo live before or after that
  insn holds (order_regs_for_reload), and a later use in the block inherits the load: one
  `mtc1` each for 55 ($f6, two multiplies) and 372.8 ($f2, two subtractions).
- **A literal has a life of 1; a variable has the life of its uses.** A constant in an
  expression is forced into a register right before the insn that uses it, so it moves only
  when cse1 has merged several uses (55: life 6; 9, 60: life 6 and 4) and otherwise stays
  (`79 * 1 * 1 < 94` insns in pass 1). `(f32)i * (1.0f / 9.0f)` is such a literal: pass 2 moves
  it (`Loop from 61 to 365: 79 real insns. Insn 103: regno 133 (life 1) ... moved`, the loop
  being 79 insns once pass 1 has emptied it), last in the preheader, with three refs.
- **What retail's registers require.** (1) 1/15 and 0.5 are not the block's own pseudos: a
  block-local 1/15 dies in `hi = lo + 1/15` and local-alloc ties it to hi (combine_regs tries
  the second operand when the first does not die), putting it in hi's $f3 where retail has
  $f2; a block-local 0.5 is issued early by sched1 (priority 9) and takes $f5 before the zoom
  ($f6) with 55 pushed to $f7. Moved and reloaded they take the first free register at their
  use: $f2 and $f6. (2) 372.8 is ranked under 9 and 60. In `372.8f - lo * 60.0f` the product is
  expanded first, so 60 precedes 372.8 in the loop, 372.8 has the shorter life and outranks 9:
  retail's loser is then 9 (measured: `lui at,0x4110` in the loop). So 372.8 was moved before
  9 and 60: it was set before the x statements.
- **The source.** Three variables of the loop body, `f32 step = 1.0f / 15.0f; f32 top =
  372.800018f; f32 half = 0.5f;`, and literals everywhere else (no locals before the loop).
  The dump: `Insn 90: regno 128 (life 10) moved`, `Insn 94: regno 129 (life 27) moved`, `Insn
  98: regno 130 (life 28) moved` first, then 1.0 (136), 55 (138), 9 (140), 60 (150), 320, 1728,
  16, 0.4545 and 1936; the dispositions give 128, 129, 130, 133 and 138 no register. EXACT in
  the five placements of the three declarations tried (four orders before `lo`; `top` and
  `half` after `hi`; `half` after the y statements), in seven of the twelve orders of the x
  and y statements tried, and with 55 named as well; not with `mid = (lo +
  hi) * 0.5f` (the 0.5 has life 1 again and stays the block's own: 37 lines).
- **The tell.** Constants loaded inside a loop whose saved registers are all taken are not
  evidence of a variable set twice: each may be a moved constant that lost its register. Rank
  the constants by refs and by preheader place; a loser with more uses than a winner was moved
  earlier, which a literal cannot be if its statement comes later: a named variable (or an
  inline's parameter, loops.md, func_001D7778) is what sets a constant ahead of its use. A
  register that seems reused for unrelated constants (`$f2`: 1/15, a difference, 372.8) is
  reload's first free register, not one pseudo.

### A threshold of 94: functions that only a wider VU0 range builds (func_0013AD80, matched; func_001D9488, func_00130C58)

Measured on 2026-11-12 (w38-f5) with `tools/check.py --flags` and `-dL` dumps. loop.c's
threshold is `1 + n_non_fixed_regs`, and `-mvu0-use-vf0-vfN` un-fixes $vf1..$vfN, so the
threshold of a loop with a call is 64 + N: 79 with the default row (vf15), 94 with vf30, 95 with
vf31. Three near misses whose notes all read "a life-1 constant moved out of a loop too big for
79" are retail's code under one value of N, with their plain sources:

- **func_001D9488** (the section "Two passes in the preheader" above). The near miss unchanged
  is EXACT for N = 30 and 31 and for no smaller N. Its decisions give the window: pass 1 has 91
  insns and moves the `li 40` and the 1 and leaves the -1, so `T >= 91`, `T - 3 >= 91` and
  `T - 6 < 91`: T is 94, 95 or 96. Pass 2 (87 insns) then moves the rest at 94, 91, 88.
- **func_0013AD80** (the section "A count-up loop with no vtop" above). The plain form that
  section names as retail's shape, `for (s32 i = 0; i < count; i++) { ViewedFrame* f =
  &frames[i]; ... }`, is EXACT for every N from 23 to 30 (on US and PAL at 30), and not at 22
  or below (15, 18 to 22 tried) nor at 31. The `li 80` is the loop's first movable, life 1:
  it must stay in pass 1 (95 insns: `T < 95`) and move in pass 2 (84 insns), after which the
  giv is found and its start value is emitted behind GCSE's insertions. At 95 it moves in
  pass 1 (1732 bytes). The lower edge, 87, is measured and not derived.
- **func_00130C58** (the sections on its switch constants above). The near miss with no
  `do { } while (0)` goes from 179 differing lines to 49 at N = 27 and to 6 at N = 29, 30 and
  31: the 2 and the 3 move and the 1 is rematerialised, as retail. The 6 lines left are the
  block after the outer loop (the `%hi` of FLT_MAX against the window count's subtraction),
  which the threshold does not touch.
- **One value fits all three: 94, `-mvu0-use-vf0-vf30`.** 001D9488 needs 94 to 96, 0013AD80 87
  to 94, 00130C58 93 or more.
- **It is not the game's threshold.** Thirty matched functions in 26 files stop matching at
  some N between 16 and 30 (measured with `tools/check.py --flags "-O2 -G0 -fno-exceptions
  -fno-rtti -mvu0-use-vf0-vfN" FILE FUNC` for N = 16, 20, 22, 24, 26 to 30): func_001A15D8,
  func_001CC120 and func_001DDE90 at 16 already (T = 80), fourteen more by 20, and every one
  of them by 30 (func_00138C00 only there). Those functions hold retail's decisions of a
  threshold of 79 to 93 the same way the three above hold 94.
- **Both kinds sit in one file.** src/main/file_1D62E0.cpp has func_001D66A8 (matches up to
  N = 28), func_001D7778 (up to 16 to 19) and func_001D9AC8 (up to 24 or 25) around
  func_001D9488 (30 or 31 only), all four methods of the path follower's family;
  src/main/placed_object.cpp has func_00127B20 (up to 20 or 21) and func_0012CD78 (up to 24 or
  25) before func_00130C58, which is its last function. src/main/world_listed_object.cpp has
  no function that changes for any N from 15 to 31, so its row in config/cflags.tsv now reads
  vf30 and func_0013AD80 is matched there; nothing else in the build moves.
- **What can make the threshold differ, read from regclass.c.** `n_non_fixed_regs` is counted
  once from the options (init_reg_sets_1) and only falls afterwards, by one for each file-scope
  register variable that names a register not yet fixed (globalize_reg). Nothing raises it
  inside a compilation. So two thresholds in one file mean either two translation units built
  with different options (file_1D62E0.cpp "could be several", its header says), or one unit
  whose threshold falls partway down at file-scope register declarations. The second is ruled
  out for this compiler (the next section): only the first remains, and it is not proved.
  Not the cause: whether the function uses VU0 or the FPU (func_001D9488 uses neither,
  func_0013AD80 both), `-g`, `-O3`, `-fno-gcse`, `-p` (same decisions as the default).
- **Reading it elsewhere.** A near miss whose only wall is a constant, a `%hi` or a stride that
  retail moved out of a loop of 80 to 94 insns with calls: build it with `--flags "-O2 -G0
  -fno-exceptions -fno-rtti -mvu0-use-vf0-vf30"` before looking for a second movable or a
  longer life. If it becomes EXACT, check which matched functions of its file change under the
  same flags; a file where none does can take the row.

### The threshold by function: one value for every matched function, and where a second would cut

Measured on 2026-11-12 (w39-tu): every file of src/main built whole with `tools/check.py --flags
"-O2 -G0 -fno-exceptions -fno-rtti -mvu0-use-vf0-vfN" FILE FUNC...` for each N from 8 to 31 (94
files with C functions, 24 builds each), every near miss in nonmatching/ but func_00109488 for N
from 15 to 31, and every earlier version of a threshold-sensitive function's near miss in the
git history (79 files) for N from 15 to 31. The scripts and their output are in the worker's
scratch folder (build/swarm/w39-tu/: scan.py, nmscan.py, histscan.py, analyze2.py, fixtest.sh).
The previous section's sampled windows (N = 16, 20, 22, 24, 26 to 30) all agree with the full
scan.

**The map.** Of the 3975 matched game functions (EXACT under their file's flags), 3930 are
EXACT for every N from 9 (or 8, where the file compiles at 8) to 31. The other 45, and the three
near misses that reach retail or come closest at some N (marked *), by address:

| Function | File | EXACT for N |
| --- | --- | --- |
| func_00120470 | pose_source.cpp | 8-17 |
| func_00127B20 | placed_object.cpp | 9-21 |
| func_0012CD78 | placed_object.cpp | 9-25 |
| func_00130C58* | placed_object.cpp | none; 6 lines off at 29-31 (49 at 26-28, 179 at 15-25) |
| func_00138C00 | world_contacts.cpp | 8-29 |
| func_0013AD80* | world_listed_object.cpp | 23-30 (matched there, row at vf30) |
| func_0013BF68 | child_group_object.cpp | **15**-17 |
| func_00140258 | zone_collider.cpp | 8-17 |
| func_00142278 | collider_span.cpp | 8-19 |
| func_00142B78 | collider_span.cpp | 12-31 |
| func_00146518 | state_notifier.cpp | 9-31 |
| func_0014D3A8 | path_curve.cpp | 10-31 |
| func_0014D680 | path_curve.cpp | 8-25 |
| func_00154370 | active_set_solver.cpp | 10-17 |
| func_00157B88 | file_1549C8.cpp | 9-18 |
| func_0015E318 | font.cpp | 14-31 |
| func_0015FD78 | file_15F678.cpp | 8-17 |
| func_0016C528 | file_16C470.cpp | 13-31 |
| func_00177990 | player.cpp | **15**-31 |
| func_00178678 | player.cpp | 9-20 |
| func_0017D5D8 | file_17D248.cpp | 10-19 |
| func_00180108 | colored_triangle_set.cpp | 8-25 |
| func_001821B0 | file_180EB0.cpp | 11-31 |
| func_00188B48 | matrix.cpp | 10-31 |
| func_00192DD0 | switched_collider.cpp | **15**-17 |
| func_001971B8 | file_1963D8.cpp | 11-22 |
| func_0019CF68 | file_198980.cpp | 14-31 |
| func_001A15D8 | effect.cpp | 13-**15** |
| func_001AF108 | timed_object.cpp | 8-22 |
| func_001B2140 | range_record.cpp | 9-31 |
| func_001B55C0 | state_walker.cpp | 8-20 |
| func_001BC978 | collider.cpp | 9-17 |
| func_001C57C8 | turning_collider.cpp | 8-17 |
| func_001C9AF8 | agent.cpp | 10-31 |
| func_001CC120 | agent.cpp | 9-**15** |
| func_001CC490 | player_link.cpp | 9-19 |
| func_001CF158 | player_target.cpp | 13-18 |
| func_001CFFD0 | player_target.cpp | 12-31 |
| func_001D5678 | player_request.cpp | 14-31 |
| func_001D66A8 | file_1D62E0.cpp | 9-28 |
| func_001D7778 | file_1D62E0.cpp | 9-19 |
| func_001D8E40 | file_1D62E0.cpp | 12-31 |
| func_001D9488* | file_1D62E0.cpp | 30-31 |
| func_001D9AC8 | file_1D62E0.cpp | 9-24 |
| func_001DDE90 | tint_blend_collider.cpp | 9-**15** |
| func_001DF520 | tint_blend_collider.cpp | 10-31 |
| func_001F2840 | file_1F2758.cpp | 9-24 |
| func_001F2EF0 | file_1F2758.cpp | 9-20 |

A lower edge of 8 or 9 is where the file stops compiling (VU0 helpers that need more vector
registers than N leaves), not a threshold. Every range is one interval: no function matches
at two N with a gap between. Of the other near misses, func_00134B48 (text_panel.cpp) is best at
15-16 (11 lines; 140 or more above), func_0013A618 (world_listed_object.cpp) is 30 lines off at
15, 20 at 26-28 and 159 at 29-30, func_0013A940 (same file) 205 or 207 throughout, and the
other 32 do not change.

- **Proved: the default unit's threshold is exactly 79.** The 3975 matched functions have one
  N in common, 15, the default row: func_001A15D8, func_001CC120 and func_001DDE90 stop at 16,
  and func_0013BF68, func_00192DD0 and func_00177990 stop at 14. None of the six uses a vector
  register above $vf9, and the dependence is the count alone: built with `-mvu0-use-vf0-vf16
  -ffixed-$f31` (a register the function never uses fixed, so the count is that of vf15 with
  $vf16 allocatable) the three upper ones are EXACT again, and built with `-mvu0-use-vf0-vf15
  -ffixed-$f31` (the count of vf14) the three lower ones differ as at vf14. The same test at
  each function's first failing N (one unused FPR fixed) gives EXACT for all 30 functions
  with an upper edge, and at vf31 with up to 16 unused FPRs fixed, EXACT wherever the count
  gets back into the function's range (26 of 30; the other four run out of unused FPRs). So
  what N changes in these functions is n_non_fixed_regs, that is loop.c's two thresholds
  (move_movables' `1 + n` and strength_reduce's `3 + n`, doubled without a call; stmt.c's
  third use, preserve_subexpressions_p, returns 1 at -O2), never which vector registers are
  allocatable.
- **One cut in address order is not enough: three are needed, and they fall inside two
  files.** Taking the proved file edges (config/us/files.tsv) as free cuts, every file but two
  has a common N: world_listed_object.cpp (23-30, with func_0013AD80's plain form) and every
  other file at 15. placed_object.cpp needs one cut between func_0012CD78 (at most 25) and
  func_00130C58 (29 or more); file_1D62E0.cpp needs two, one between func_001D7778 (at most
  19) and func_001D9488 (30-31) and one between func_001D9488 and func_001D9AC8 (at most 24).
  func_001D8E40 (12-31) and the insensitive functions between can go either way. So the units
  would take two values of N, 15 everywhere and 30 for three short stretches (30 is the only
  value func_0013AD80's 23-30, func_001D9488's 30-31 and func_00130C58's 29-31 share; 15 is the
  only one the matched functions share).
- **Inferred, not proved: what the data says about the three cuts.** A unit's .text, .data,
  .rodata and .bss are each contiguous, so each cut in .text needs a place in each data section
  where its two sides' labels separate.
  - placed_object.cpp before func_00130C58: allowed. Every label of the file's .data
    (0x260E70 to 0x261090) is read only by functions up to func_0012B760, so the second unit
    has no .data; its .rodata would start at 0x249B20, 0x249C10 or 0x249C90 (the two jump
    tables and func_00130C58's FLT_MAX, each on 16), depending on where the cut is. Nothing
    shows a boundary either: no padding gap, no vtable, no `_GLOBAL_$I$`. func_00130C58 is
    called by func_00130C20 just before it and by func_0015B7B8 (object_cycler.cpp), so it is
    not file-local, and func_00130C20 would go with it.
  - file_1D62E0.cpp around func_001D9488: allowed only with a cost. func_001D9488 reads no
    data of the file; it is called by func_001D9338 before it and by func_001D9C98 after it
    (class 0x19's method at +0x54, a class whose method at +0x80 is func_001D7778, on the other
    side of the first cut). For every cut between func_001D7778 and func_001D9AC8 the best
    .data cut leaves globals defined in one unit and read only by another: at least 0x2751D4
    and 0x2751DC (60 and 0.75, read only by func_001D9D78 and func_001DAF08 after the cut, in a
    block of four words whose other two, 850 and 1.25, are read by functions before it), and
    the cleanest place, 0x275518, is on 8 only while the unit after it begins with a 16-aligned
    Vec02 at 0x275530 in our source (the type is ours: retail only shows the address). A cut
    before func_001D8E40 adds D_00275240 to the globals read across it. The .rodata (0x24DC90
    to 0x24DCA8) splits cleanly: the "%s" and the float are the first unit's, the pairs at
    0x24DC98 (func_001DCD28) the last's, and func_001D9488's unit has none.
  - None of the three cuts is where a signal of docs/AGENT_WORKFLOW.md ("Finding and proving
    a file") puts a boundary; none is excluded by one either. A split would be proved only by
    building the pieces whole as separate units and getting `MATCH`.
- **Ruled out: something inside one unit lowering the count between functions.** In GCC 2.95.3
  (regclass.c, varasm.c, toplev.c), n_non_fixed_regs is set once in init_reg_sets_1, from
  FIXED_REGISTERS, CONDITIONAL_REGISTER_USAGE and the -ffixed-, -fcall-used- and -fcall-saved-
  options, before the first declaration is read; afterwards only globalize_reg changes it, by
  one for each file-scope `register` variable on a register not already fixed. Measured with
  SN's cc1plus: such a declaration is refused with `global register variable follows a function
  definition` even as the first line of a file (`register int g asm("s7");` alone), because
  g++ gives its built-in functions RTL before the source is read, which sets varasm.c's
  `function_defined`. A register variable on an already fixed register (`register u128 g
  asm("vf20");` at vf15) is accepted and changes nothing; at vf31 it is refused the same way.
  So no C++ file can lower the count at all, let alone between two functions, and nothing
  raises it. The strings of cc1plus show no pragma beyond g++'s own (`interface`,
  `implementation`, `vtable`, `unit`, `weak`) and no option that sets the VU0 range other than
  `-mvu0-use-vf0-`. The other SN builds the toolchain has (2.95.2, 2.96-ee-001003-1) keep the
  same count at vf15: func_001D9488 differs there and is EXACT at vf30 under both, as under
  2.95.3, so a unit built by another release with another default is not it either. What SN
  changed in its EE backend is not public, but every measurement fits a count fixed per unit:
  whole files at one N reproduce retail for every matched function.
- **The reverse risk: matched forms that compensate.** Every earlier near miss of the 30
  functions with an upper edge (from `git log -- nonmatching/FUNC.cpp`; 72 of the 79 compile
  today) was built at N = 15 to 31: none is EXACT at any N other than the matched function's
  own range. Three get closer at a higher N, the candidates for a source shaped to fit 79:
  - func_001CF158 (player_target.cpp): its last near miss before the match (3b7dde15, without
    the `const f32&` references at the top of the loop that matched it, "Solved: the weight and
    the limit named at the top of the loop" above) goes from 17 lines at 15 to 6 at every N
    from 20 to 31; what is left is the round-robin of the spilled `%hi` reloads (v0, v1 against
    v1, a0). The matched form is EXACT at 13-18 only. The strongest candidate.
  - func_001C57C8 (turning_collider.cpp): two versions (907d7889, 9981717e) go from 86 lines to
    31 at N = 23-24 only, and back to 86 at 25. Weak.
  - func_0017D5D8 (file_17D248.cpp): ce5e76ad goes from 304 lines to 270 at 20-22. Weak.
  The other 27 (and func_00177990, which has no history) show nothing. This does not show
  they were shaped to fit: a form plainer than the matched one that is EXACT elsewhere would.
- **Where this leaves the vf30 row.** world_listed_object.cpp holds no matched function that
  depends on N, and func_0013AD80's plain form needs 23-30, so the row costs nothing that is
  matched; its two other near misses do not support it (func_0013A618 is worse at 29-30 than
  at 15, func_0013A940 the same). placed_object.cpp could take a vf30 unit for func_00130C58
  alone (with func_00130C20, or from any function after func_0012CD78), and file_1D62E0.cpp one
  for func_001D9488 between two vf15 units; neither has a data edge to show it, and
  func_00130C58 also has an EXACT form at the file's own threshold (the two loop notes of the
  section "The 3's second set"), which the rules do not allow but which shows the threshold is
  not the only way to its code.

### The splits on the threshold (2026-11-12)

The maintainer decided on 2026-11-12 to split the files the map above shows needing two values
of N, on the threshold evidence alone: no boundary signal of docs/AGENT_WORKFLOW.md ("Finding and
proving a file") shows these edges, and none excludes them. The new units build at
`-mvu0-use-vf0-vf30`, as world_listed_object.cpp; every other unit keeps the default. Each was
built whole and the full builds print `MATCH` on US and PAL.

- **file_1D62E0.cpp in three.** file_1D62E0.cpp (0x1D62E0 to 0x1D8E40, vf15),
  file_1D8E40.cpp (0x1D8E40 to 0x1D9AC8, vf30) and file_1D9AC8.cpp (0x1D9AC8 to 0x1DDCE0,
  vf15). func_001D9488 is matched in the middle one from its near miss, unchanged. The calls
  give no edge: func_001D9488 calls func_001D9338 before it, and it, func_001D8E40 and
  func_001D9678 are called only by UpdatePathFollower (func_001D9C98, class 0x19's method at
  +0x54) after it, func_001D92F0 only by ControlPathFollower (+0x134). The edges are the data's.
  The middle unit holds the 16-aligned Vec02 at 0x275530 (retail has eight zero bytes before it,
  after D_00275524: an object on 16, or a new file's `.data`), so its `.data` starts on 16;
  0x275518, the place with the fewest crossings, would need D_00275524 to be a 12-byte object
  that no reader shows. Of the places on 16, 0x275500 (the middle unit from func_001D8E40, whose
  three range pairs start there) leaves three globals defined in file_1D62E0.cpp and read only
  across (D_00275240 by func_001D8E40; D_002751D4 and D_002751DC, 60 and 0.75, by
  func_001D9D78 and func_001DAF08 in file_1D9AC8.cpp), and D_002751D8 read on both sides;
  0x275530 (from func_001D92F0) leaves four (D_00275518 and D_00275524, read only by
  func_001D9678, and the same two). The middle unit has no `.rodata` and file_1D9AC8.cpp's
  starts at 0x24DC98, its pairs (on 8; the unit has no jump table). The functions that
  constrain N, each checked in its unit: func_001D66A8 and func_001D7778 EXACT at vf15,
  func_001D8E40 and func_001D9488 at vf30, func_001D9AC8 at vf15. func_001D92F0, func_001D9338
  and func_001D9678 could sit on either side of their unit's edges as far as N goes.

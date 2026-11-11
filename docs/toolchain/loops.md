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
src/main/file_18F988.cpp). Retail's outer loop over the segments holds 1.0 (the walk's guard) and
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
pointer (`Cell8B* cell`), the read has the argument's base, never conflicts with a frame store,
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

### An inline's constant parameter is a variable with a life: the strip loop's UNPACK words (func_00166690)

Matched 2026-11-10 (DrawModelPart, src/main/file_15F678.cpp; the form found by worker
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

### A count-up loop with no vtop, and a giv loop.c never finds (func_0013AD80, near miss)

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

### Three invariants ranked by their place in loop.c's move list (func_001D7778, near miss)

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

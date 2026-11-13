<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# sched1

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
- **No loop notes in retail there (2026-11-10, w15).** final.c's shorten_branches gives the
  first CODE_LABEL after every NOTE_INSN_LOOP_BEG the loop alignment (8 bytes here), however far
  away it is, which is the `nop` the `do { } while (0)` adds. Retail's labels from 0x1DEEF8 on
  are at 0x1DF10C, 0x1DF11C, 0x1DF134, ... (4 mod 8), so no LOOP_BEG note follows 0x1DEEE4; one
  before it would have to enclose the whole tilt/turn block, and loop depth 2 there changes
  local-alloc's VU0 registers (vf10/vf11 for retail's vf6/vf7, tried: `do {` at the lean join,
  and from the stick heading on, which gives pad retail's s2 through the doubled refs but loses
  the block's registers). The only plain-C++ barrier is ruled out, so the argument moves must be
  held back by a dependence of their own, not a barrier.

- **A block boundary there gives retail's order with no loop note (w40-fc, 2026-11-12, a
  probe).** `if (self != 0) k = 0.0f;` between `rot = m;` and the third call, with k assigned
  again on every later path, is a conditional over a store flow1 deletes as dead (the reading
  that fits: k has other uses, so it is not trivially dead after cse, and a float has no
  conditional move; in func_001EC7A8 the same store of a float used only in its own block was
  gone before reload, branch and compare with it). The branch
  and its label stay through sched1, both allocators and sched2, so the call's `lui`, `a1`,
  `lwc1` and `a0` are the first insns of a block of their own and issue in retail's order;
  jump2 then deletes the branch to the next insn, and a test of a register alone leaves
  nothing behind (jump.c's delete_computation keeps a compare's operands after reload, so a
  test that loads or builds a constant would leave that insn in the code). The probe is 1700
  bytes with (b) gone (build/swarm/w40-fc/a2.cpp, 56 lines, registers only). With the block
  split, block A's VU0 registers move: local-alloc now wants the tilt's second row to live at
  least 9 insns (7 in the probe, 10 when the three argument insns were scheduled among the
  loads) and the first row with the product's last row at least 25 (23), so retail's block
  holds two more insns between the tilt loads and the last row's product that leave no code.
  What the original had at the boundary is not found; a test of pad there takes pad to s1.

- **The invisible insns can be jumps (w44-fc, 2026-11-12).** An if/else whose two arms only
  set a register that is set again before its use is emptied by flow1, and its two jumps (the
  conditional one and the then-arm's jump over the else) stay in the insn stream through
  sched1, local-alloc, global-alloc and sched2 until jump2 deletes them: two insns that leave
  no code and count in every life around them, and two block boundaries (func_001EC7A8,
  alias-classes.md, "A merged arm keeps its place"). As a probe here, one such if/else on
  `self != 0` between the two key reads gives the two insns W23 asked for (&cur and pad two
  longer, &tgt not): pad in s2 and &cur in s3, 56 lines to 42 on top of the boundary probe.
  The probe is not the original (the first key read's address comes out as `addiu a1` with a
  copy to s3), and what tested a register for free there is not known. In sched2 retail's
  block shows the boundary as well: three loads in a row with their alu slots idle
  (`lqc2 vf1,64(sp); lqc2 vf6,32(sp); lqc2 vf4,80(sp); lqc2 vf7,96(sp)`), where ours fills the
  slots with the next call's `lui`, `addiu a1` and `move a0`; so the label is still there when
  flow2 rebuilds the blocks.

- **What a register weight is, and why the 660 rows' order has no plain form yet (w49-f,
  2026-11-13).** haifa-sched.c's find_insn_reg_weight counts the SETs and CLOBBERs of an insn's
  pattern less its REG_DEAD and REG_UNUSED notes, so a store weighs 1, or 0 where a register
  dies in it, and rank_for_schedule issues the lower weight first at equal priority. After a
  block is scheduled, attach_deaths_insn puts the deaths back in the new order, so local-alloc
  ties copies by sched1's order, not the source's. Retail's order (0x670, 0x680, 0x660, then
  m's rows) is the replay's with the stores of rows 1 and 2 at weight 0, so their products die
  there, while m's and rot's rows 1 and 2 are stored later from the same VU0 registers. The
  three ways to a second register with the same value were each ruled out against the dumps:
  a copy ahead of the store in the stream (cse rewrites both stores to its canonical register,
  and the copy feeds m's store at priority 61, so it issues before the 0x670 store and both
  registers live: a `vmove`); a reload of the row after the store that reload_cse would delete
  in the product's register (a pseudo only loaded and stored ties in regclass, movti and
  stores being neutral, so it is TI_REGS and local-alloc gives it a GPR); m and rot stored
  before the 660 rows (frame stores feed RotateTransposed's loads at priority 61, so rot's go
  early, and rot written after the transpose holds the products' last use).

- **The 660 rows' order is the stream's order; what block A still needs (w50-f, 2026-11-13).**
  The six stores of the block (three rows to `self + 0x660`, three to m) have one priority
  (61: the transposed product's row loads wait for the frame stores as well as the stores to
  self; read from alias.c and not tested, the reason is that their address register has no
  pointer flag, so find_base_term gives it no base), one weight and the same number of dependents, so rank_for_schedule
  falls through to the LUID: as each becomes ready, the earliest in the stream goes. Retail's
  order (0x670, 0x680, 0x660, then m's rows) is therefore the stream's with row 0's store to
  self written after rows 1 and 2 and before `m = self->m660`; no register weight and no
  second pseudo is needed (the weights of the entry above were another way to the same order
  in the replay). Compiled: with the first product kept in a local and stored last, block A
  is retail's insn for insn but for the three argument insns of this section's wall, and with
  the two probes above (the if/else between the key reads, the test before the third call)
  26 lines differ, registers only (build/swarm/w50-f/f/f2.cpp). What original statement put
  row 0's store last is not known; a structure copy whose first row cse forwards issues its
  rows 1, 2, 0 as well (the copy of the call's result into rot further down), but there it is
  the deaths of rows 1 and 2, which the products here cannot have: their registers stay busy
  to rot's stores (the transposed product's scratch registers are vf8 to vf11 in retail).
  On that probe local-alloc's replay (tools/globalalloc.py's LocalModel) gives the two ranks
  that are still wrong: tilt's row 1 (4 references over 7 insns, 11428) against turn's row 2
  (2 over 2, 10000), and the quantity of tilt's row 0 and the last product (8 over 23, 10434)
  against the transposed product's result (2 over 2, 10000). Retail has each pair the other
  way: two more insns in sched1's order between the tilt loads and the last product (9 and
  25), or turn's row 2 loaded directly before its product (a tie between that load and the
  second product would give it, the product's weight being lower: reasoned, not replayed) and v640 stored directly
  after the transposed product. Three tied copies of the products would not do: the last
  product's quantity then has 10 references over 26 insns (11538).
- **The boundary is there after reload (w50-f).** In our sched2 the third call's `addiu a1`
  and `move a0` take the idle alu slots beside the tilt loads again, whatever sched1 did, and
  retail's slots are idle; so what holds them exists in sched2. A CLOBBER of a brace
  initialiser (docs/toolchain/large-functions.md) is deleted by reload and cannot be it. Left:
  a jump that jump2 deletes, or an asm without operands. From toplev.c's pass order, jump runs
  after cse1, delete_trivially_dead_insns after that, and jump again before cse2: an arm that
  only holds an inline's unused result is emptied and its jump removed before sched1. A jump
  survives to jump2 only where flow1 or a later pass empties the arm (a register that is used
  elsewhere and dead here). flow.c also ends a block after every call inside an exception
  region, with no code, but the file is built without exceptions. Compiled and ruled out as
  the common cause of this function's walls: a run-once loop from each of six statements to
  `rot = m` (1704 bytes, or VU0 registers vf10/vf11); the w clamp in both arms of the speed
  test (the copies are scheduled differently, so cross-jumping leaves both: 1796 bytes); the
  two key tests as switches (1704 to 1716 bytes).

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
- **Why no barrier fits exactly** (second pass, 2026-11-10, from haifa-sched.c's
  get_block_head_tail, sched_analyze_insn, schedule_insn, mips.h's ADJUST_COST and reorg.c's
  fill_slots_from_thread). Retail's cycles are ours with the v0 chain (the address, its spill
  store `sw v0,68(sp)` and the next addresses) and the two picture stores one cycle later,
  while the other chain (`li s0,384`, the mults, `addiu s1`, `move a0,s1`) keeps its cycles:
  in retail's cycle 1 the memory unit and the second issue slot are both unused although the
  stores and `li s0,384` are ready. A loop note is a barrier only after the block's first
  insn (get_block_head_tail skips leading notes; an empty loop at the top of the body has no
  effect, 123 lines), and the barrier insn is the one after the note, which then depends on
  every earlier insn: no insn order makes the address both first and the barrier. A note
  after the address makes the next insn the barrier and serialises cycles 2 and 3 (the
  previous attempt's 35 lines). Anti and output dependences cost 0 on MIPS (ADJUST_COST), but
  a dependent made ready by an issue is not issued in the same cycle (it is swapped behind the
  loop index), so a second copy of the address cannot share cycle 1.
- **No invisible insn either.** An insn that takes the slot and vanishes later would also fit:
  jump2 deletes no-op moves only after sched2, but none reaches sched2 (reload_cse_regs
  deletes them first; no `(set (reg N) (reg N))` in 650 sched2 dumps of this project); flow's
  `(use (const_int 0))` follows a call that ends a block, never a block's head; reorg deletes
  a thread insn redundant with one before the branch (redundant_insn), and only `lw v1,0(a1)`
  is redundant at both branches, but a dead re-read of the width never reaches sched2. The
  other grouping of retail's order (address and height store in cycle 1, every later pair
  alu first) needs the v0 chain below `li s0,384` and the mults, the reverse of ours (64 to
  62), and the width store below 63 while the height store stays at 65.
- **Also ruled out:** `-funroll-loops` with the plane calls as loops (151, 166: not unrolled
  completely), the plane array through a local pointer (102 after the test, 42 at the top: the
  pointer is kept in s5), the size test as an inline (134), the body as an inline (not
  inlined: over the integration threshold).
- **Third pass (w47-h, 2026-11-13): what this compiler's insns that leave no code are, and
  none is here.** Measured on the 36 library files this cc1 builds (their `.sched2`, `.jump2`
  and `.dbr` dumps and the verbose trace): (1) a `trap_if` with an anti dependence on another
  trap prints nothing (func_00202140, matched with it: the section "The zero trap of
  func_00202140"); this function has no division by a variable, so no trap to repeat. (2)
  flow's `(use (const_int 0))` follows a call that is the last insn before a label; the
  scheduler ties it behind that call at its block's end. (3) `blockage` (an
  `unspec_volatile`, a true barrier that prints nothing) stands only before the stack
  pointer's adjustment in each epilogue, the tail call's included. (4) jump2 deletes
  conditional jumps, labels and no-op moves that sched2 still saw, and no dead single set
  reaches sched2 in any of the 36 files, so a dead re-read is not kept. (5) In no block of
  the 36 files does one insn issue alone in the first cycle while an ALU insn with no
  predecessor waits for the second: retail's body is the only one, so its first cycle is
  not a rank this scheduler gives a single block. gcse here is edge-based
  (`PRE/HOIST: edge (6,8), copying expression 16`): a probe that makes the last plane's
  address partly available (a jump into the body from a block that computes it) has PRE
  compute it on both edges into the body, which is retail's test and both delay slots, but
  copy propagation then leaves one pseudo for the address (it took `s5` in the probe, whose
  extra block freed a register; spilled, its store would follow its set), where retail's
  `sw v0,68(sp)` sits in the body after the two picture stores. The address set in each arm
  of the test by hand (`if (w != pic->width) last = ...; else { if (h == pic->height) return;
  last = ...; }`) gives the same: test and slots exact, 35 lines left, the spill store
  beside the address and in slot 48. So retail's shape is the address alone in a block
  ahead of the body with its spill store inside the body: the value in `v0` crosses a
  boundary that leaves no code, and the stored pseudo is the last one made. Compiled and
  ruled out (102 lines or worse): the callees' return types (void or s32, three ways), the
  test as nested ifs, as two gotos, as a flag local (116, 134), one variable for the rows
  and the height (64 lines but with s6 and s7 swapped: not closer), one for the rows and
  the size (79, the same), the height set in each arm (136), the size kept in `w` (135).
- **Fourth pass (w49-i, 2026-11-13): retail's body block is ours without the address, and
  what that excludes.** Replayed by hand on our own `.sched2` dependency table of the body
  (block 8 of the near miss; issue rate 2, one memory unit): delete insn 345 (`addiu
  v0,s8,1320`) and let `v0` be live into the block, so that 659 (`sw v0,68(sp)`, priority
  64) is ready at once. The scheduler then issues 142+146, 138+148, 659+163, 335+165,
  662+329, 337+150, 665+331, 339+333, 668+472, 341+152, 671, 343, 674 and the call: retail's
  order insn for insn up to the first `jal` (the sort at each cycle is the one the table
  gives; nothing else changes). So in sched2 the address is set outside the body's block, or
  shares cycle 1 with an insn that leaves no code and takes the second issue slot ahead of
  the stores. Each reading needs something no allowed form has given:
  (1) *A value set before the body's label and copied inside it* (two pseudos: R in `v0`, set
  ahead of the label, and the spilled one, set in the body by `Q = R`). PRE cannot place R:
  with lazy code motion the address is anticipatable only at the body (the return path does
  not use it), so it is inserted on the two edges only when it is available on some other
  incoming path, which retail's code would show (it has no other computation of it). And
  cse2 removes the copy: in make_regs_eqv (cse.c) a new register becomes the class's
  canonical one only if it lives outside the current cse block, so R stays canonical, Q's
  uses become R and R is the pseudo spilled, with its store beside its set. Measured: the
  PRE probe built with `-fno-rerun-cse-after-loop` keeps both pseudos, Q spilled to slot 68
  (retail's slot) with its copy's store in the body (`sw s2,68(sp)`; R took s2 there). So
  this reading needs a label inside the body at cse2 that is gone by sched2, or Q
  referenced before the body's label; no plain source found does either (a named label
  before the last call is deleted and changes nothing, 133 lines in the PRE probe).
  (2) *An insn that leaves no code in cycle 1.* The only candidate reorg removes is a re-read
  of the width identical to the test's `lw v1,0(a1)` (redundant_insn on both paths, deleted
  from the beq's own thread), but redundant_insn refuses an insn with a REG_UNUSED note and
  flow2 deletes a dead set, so the re-read needs a reader that also vanishes before final;
  no such reader (a no-op move, a USE of a register other than the return value, a silent
  trap) arises from this function's statements.
  Also compiled (no closer): one named local for the last plane's address set at the top, before the test,
  after it or before the set-up call, with the last call using it or not (146, 122, 107,
  107); the probe that sets the address in each arm with a body copy whose source is
  reassigned after it (cse2 then keeps the copy: 48 lines, the copy late and slot 48).
  Not kept: the size written at each of its three uses scores 40 lines, but it computes the
  size after the first call where retail computes it before, so it trades this wall for a
  structural difference.
- **Fifth pass (w50-i, 2026-11-13): two of the three readings are out, and combine makes
  the insn the third needs.** About 75 compiles, with the `-da` dumps (scratch
  `build/swarm/w50-i/`).
  (1) *The address set on the edges is out by its register.* A pseudo set on the two edges
  into the body and copied there into the spilled one dies in the copy, so global-alloc
  hands it the copy's preferences (expand_preferences): the spilled pseudo is copied to
  `a0` for the tail call and the edge pseudo takes `a0` (`;; 122 preferences: 4`), not
  retail's `v0` (three probes: the arms by hand, the copy written before the first call).
  With the copy written at the set-up call sched1 moves it above the calls, but haifa
  never lowers REG_N_CALLS_CROSSED of a pseudo that lives in more than one block
  (`Register 122 ... across 10 insns ... crosses 4 calls`), so the edge pseudo takes a
  call-saved register (`s2`, the fourth pass's `s2`). gcse's own copy propagation folds a
  body copy whose source is not set again, as cse2 does (a label later in the body does
  not keep it). Retail's `v0` is what reload's first spill register gives the near miss:
  the address is computed in the body's block.
  (2) *A barrier at the address is out by the stores.* With the address the first insn of
  the block's stream its spill store follows it (reload emits it there), the picture
  stores come later in the stream and so depend on that store (two stores that may
  alias), and `sw v0,68(sp)` issues ahead of them. Compiled: an insn that prints nothing,
  loop notes, then the address (`do { } while (0); p8 = ...` with six pointer locals
  declared in slot order) scores 21 lines with exactly that order (address, spill store,
  picture stores); retail has the picture stores first. So in retail's stream the picture
  stores precede the address and its store, as in the near miss, and the address is free
  to issue first: no barrier.
  (3) *What is left: the near miss's stream with an insn that prints nothing ahead of the
  picture stores, which they must wait for.* A read of memory they may alias does it: it
  holds both stores, takes the second issue slot of cycle 1 beside the address, and the
  block then schedules as retail's, insn for insn (replayed by hand on the near miss's
  table: the fourth pass's replay with the slot taken instead of the address removed).
  combine makes such an insn. When a combination removes the last reference to a register
  that is live into the block, distribute_notes finds no insn for its REG_DEAD note and
  emits `(use (reg N))` after the block's label (combine.c, "insert a USE insn for the
  register at that label"). Measured: an uninitialised local read in an expression
  combine folds away (`x & (w & 15)`, `w` a multiple of 16) leaves `(insn 667 134 664
  (use (reg/v:SI 212)))` at the body's label; it reaches sched2 (a USE issues
  `on unit none` and counts against the issue rate, as `(use (const_int 0))` does in
  func_00204AA8), reorg skips it and final prints nothing. A register that crosses calls
  gets no hard register here (the nine call-saved ones are taken) and reload makes the
  insn `(use (mem:SI (plus sp 72)))`, a seventh slot inside the same frame, or
  `(use (mem (plus sp 68)))` when the register is the last plane's own variable.
  (4) *Why no probe matched: sched1 decides where the USE lands, and it must land ahead of
  the picture stores (priority 42: the first call waits for every store).* A USE of a
  register that crosses no call is tied before the next call (42, and its death gives it
  the lower weight: measured, `(use (reg a3))` issued between the mult and the height
  store), but such a register gets a hard register, and a USE of a register holds no
  store. A USE of a register that crosses calls has the priority of that register's next
  set in the block (35 for the last plane's variable, 3 for a register never set), so it
  lands after the stores and depends on them. Retail therefore needs a register that ends
  in memory and whose USE has priority 42 or more in sched1: its next set in the block
  tied before the first call (a copy from a temporary that crosses no call, or a value
  an early store needs), with its old value's last reference removed by combine. No
  source form found; a temporary and a copy do not survive (cse's swap of `(set T E)
  (set Q T)`, then combine).
  (5) *Measured on the way.* A conditional around dead code leaves no block boundary
  (flow removes the arm and the branch before sched2: the base's code), so only jump2's
  cross-jumping of identical arms could hide a boundary from the final code. An empty
  loop at the head of the body only adds the loop's alignment nop (its notes lead the
  block: 123). The early return as a value (the last plane's address) puts the address
  in the `beq` slot from the return path but restructures the exit (121). A copy of the
  picture pointer that survives cse (`p = pic`, `p` set earlier) issues alone ahead of
  both stores and is copied into both slots (`move v0,a1`): the dependence retail's
  first cycle needs, from an insn that prints. The size written at each use lands after
  the first call because sched1 ties a temporary that crosses no call behind the
  previous call, so retail's size before the call is its source order. No flag gives the
  function (`-fno-expensive-optimizations` 42 lines, `-fno-schedule-insns2` 56: other
  code). Eighteen plain statements at the head of the body (blocks, casts to void, empty
  ifs and switches, labels, empty or early-returning inlines) leave the base's code.

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

- **Resolved (2026-11-10, w20).** The second VU0 reference was never there: the conversion's
  operand added no preference at all. ToFloatMoved now takes the vector as `"*r"`, which regclass
  skips, and both functions are EXACT with ToFloatMoved for the length and the division
  (docs/toolchain/vu0-helpers.md, "A GPR operand that leaves the class to the producer").

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

### An argument's frame address that sched2 holds back (func_0014F168, matched 2026-11-13: see the end of the third section below)

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

### A store in each arm leaves the join block to sched2 (func_0013BE18, matched 2026-11-13: the theory was wrong, see the end of the next section)

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

### Why the arms' stores cannot be written plainly (func_0014F168, func_0013BE18; matched 2026-11-13 another way)

Read from cse.c, jump.c and haifa-sched.c of GCC 2.95.3 with dumps and probes (2026-11-10):

- **jump2 does merge them.** A probe that stores `*p` in each arm with `p` hidden from CSE
  (an empty asm on `p`, a probe only) gets both arms' `sqc2 vf1,0(v1)` merged by jump2's
  cross-jumping (find_cross_jump with minimum 1 for a simple jump: the .jump2 dump puts a new
  label before arm B's store) and reorg then fills arm A's `b` slot from before the jump:
  retail's layout. So a store in each arm, merged after sched2, is a consistent explanation of
  retail's head.
- **CSE rules out `p = &d` in the same block.** `&d` (d at frame offset 0) is a register copy of
  the frame pointer ($1 before elimination), and make_regs_eqv always makes a fixed hard
  register the canonical register of its class, so canon_reg rewrites `(mem p)` to `(mem fp)`
  in every insn of the extended basic block that holds p's set. Arm A (the then-arm) falls
  through from the test and is always in that block; arm B is reached by a jump to a label used
  once, which -fcse-follow-jumps follows. Written plainly the arms store through sp (`0(sp)`),
  and retail's `move v1,sp` with `0(v1)` in both arms cannot come from `p = &d` set before the
  test in the same block. With the store after the join (the near misses' form) p survives
  because the join label starts a new CSE block. func_0014F168 has no label before the test at
  all; in func_0013BE18, p set before the first `if` survives but crosses the call into s2.
- **Arm A's VU copy has the same problem.** `n = x; *p = n;` stores x (the fallback, a GPR
  pseudo: `sq v0`) unless n is the canonical register; make_regs_eqv prefers the new register
  only if it lives past the CSE block (or was set before it) and longer than the old one. A
  reused variable n first set in func_0013BE18's first else arm (the Sub result, probe g1)
  still gives `sq v0,0(sp)`: CSE's path from block 0 follows the first if's arms, so the block
  starts at the function's start.
- **Isolating the store is not enough in func_0014F168.** With the probe's merged stores the tail
  loses retail's `move v1,sp` life into the join block: local-alloc then gives the first
  weight's %hi a0 (retail v1) and `addiu a1` comes one slot late (after `sqc2 vf1`). In
  func_0013BE18 the same probe gives the e1/e4 tail above, but for the weights' lw order.
- **Stale scheduling state, checked.** haifa-sched.c 2.95 never clears flow's LOG_LINKS or
  SCHED_GROUP_P before sched2 (the "clear out stale" lines came later), so a group or link made
  before reload survives; the sched2 dump marks a SCHED_GROUP_P insn with '+'. On MIPS only a
  USE before a call sets SCHED_GROUP_P, and no insn of these blocks has it. jump2's
  delete_noop_moves (after sched2) also deletes a move whose value find_equiv_reg finds
  already in its register, so sched2 can see an insn that the final code lacks: a candidate for
  the missing dependence of `addiu a1`, not found.

- **What a stale link would have to be (w37-f2, 2026-11-12).** haifa-sched.c only drops the
  LOG_LINKS that point into another block when a pass starts (schedule_insns, the
  `INSN_BLOCK (x) != b` loop) and skips links to deleted insns when it builds the forward
  lists, so every same-block dependence sched1 computed is still a dependence in sched2. In
  ours' sched2 trace the join block issues 301 and 171 in cycle 5, 228 and 205 in 6, 224 and
  251 in 7, 131 and 233 in 8, then 181 alone in 9; `addiu a1,sp,16` (253) lands where retail
  has it, after 181, if it waits for the weights' qmtc2s (171, 205), unit Z's load (228),
  `move a0,s0` (251) or the MulXSum asm (233); a link to the table load (131), d's reload (224)
  or the slot store (181) leaves it after r's store. But sched1 gives the insn `a1 = sp + 16`
  only what it names: the last users and setters of hard register 5 and the setter of the
  address pseudo. None of the five candidates names a1 or sets an address, and combine's
  distribute_links keeps a merged insn's links only on insns that still use the linked
  register. A loop note is no help either (reasoned from the two passes' rules, not compiled):
  with the first insn after it a barrier in both passes, every placement puts a slot store, r's store or `move a0,s0` on the wrong side of it
  (the slot stores are expanded before the asm, the call's own moves after r's store). So a
  dependence, stale or not, is not what holds the insn back; the block's contents at sched2 are
  (the per-arm stores above).

**What it was (w46-a, 2026-11-13): one memory dependence of the join's store, not its place.**
Both functions matched with the store where the near misses had it, at the join. The sched2
replay (w44-fc's s2.py over tools/sched1.py's Replay, which reproduces every block of the near
miss) with one edge cut, from the store of `*p` to the first weight's load, issues the join
block in retail's exact order (func_0013BE18: 197 254 220 244 245 390 393 226 283 260 279 204
288 236 314 298 270 308 310 312 316); dropping the store from the block, the per-arm theory,
does not (the three `lui` and the two `lw` come out in another order). With the edge, the
load waits three cycles for the store (`Ready-->Q: insn 390: queued for 2 cycles` after its
`lui`), and the free issue slot beside `addiu v0` goes to the next ready ALU insn, `&r`;
without it the weight's `lw` takes that slot and every later slot is filled by the chain, so
`&r` and the argument moves come where retail has them. The second weight's edge may stay:
its load is not ready before the fourth cycle either way.

alias.c gives the edge its condition (true_dependence, fixed_scalar_and_varying_struct_p): a
load does not depend on an earlier store when one is a scalar (MEM_SCALAR_P) at a fixed
address and the other a structure member (MEM_IN_STRUCT_P) at a varying one. Ours had
neither flag on either side: `Vu0::Q(*p) = ...` stores through a `u128*` (no flag), and
ScalarAt reads the weight's word through a cast pointer (no flag). The source that gives
both:

    Vec02* p = &d;
    *(Vu0::Vec*)p = Vu0::NormalizeOr(Vu0::Vec::Of(d), Vu0::Vec::Of(g_unitXVector));
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAtValue(D_00261360), ...);

The store is a structure's through the pointer (`(set (mem/s:TI (reg/v:SI 3 v1)) (reg:TI 80
vf1))` in `.sched2`), and ScalarAtValue's operand is the float variable itself, a scalar at
its symbol's address (a `lo_sum` is not a varying address). Measured on each function, the
store as `Q(*p)`, as a Vec through the pointer, or as `p->q` of a `Vu0::Vec*`, against
ScalarAt or ScalarAtValue for each weight: EXACT exactly when the store is a structure's and
the *first* weight is ScalarAtValue (four of twelve forms in func_0013BE18, two of four in
func_0014F168); the second weight may be either. Either change alone leaves the near miss's
15 (12) lines.

The tell, for other near misses: an ALU insn (a frame address, an argument move) that ours
issues early in a block headed by a store through a pointer, with retail's loads of globals
packed right behind the store. Look at the store's dependents in the `.sched2` table: a load
of a global scalar among them is an edge that a structure store and a plain scalar read do
not have. The per-arm stores and jump2's cross-jumping were a consistent explanation of the
head, but not the cause.

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
- Read again in sched2's `-fsched-verbose-6` dump (2026-11-10): at the radius's tie the last
  scheduled insn is `move v1,v0` (the %hi kept for the second read of the radius), so both
  candidates are class 3; had the lqc2 of p been last, the vsub would be its data dependent
  (class 1) and lose, but retail issues `move v1,v0` after that lqc2 too. The qmfc2's third
  dependent, the c.lt.s, is a stale LOG_LINK from sched1 (before reload the asm's output was
  the comparison's operand; reload's mtc1 now stands between them). The radius read before
  the subtraction, or `f32 rr = r * r;` named before the distance, changes nothing (4 lines).

- Replayed again with sched2's dump (2026-11-10, w19): the pass that decides both pairs is
  sched2; sched1 already issues the lwc1 before the vsub. ToFloatNow (qmfc2 and mtc1 in one asm,
  cost 1) makes the chain 1 + 1 + 1 + 4 = 7: the mul.s then goes ahead of the dot and the asm's
  GPR is local-alloc's v0 (10 lines). Retail needs a chain of exactly 8 with reload's a0, which
  only a compiler qmfc2 into a reload register followed by a one-cycle mtc1 gives.

### The copy and the list's load after a call (func_0017ECE8)

Replayed with tools/sched1.py (2026-11-10). After SolveActiveSetSystem, block 34 holds the copy
of the spilled down vector into the sum (871, `mem:TI` through the frame, no alias flag), `p =
sol` (875), `self->contacts` (880, r307) and its `->head` (882, mem/s through r307).

- **The tie.** 871 and 880 are both ready at t=4 with priority 5 (each 2 + 882's 3: 882 is a
  true dependent of the store, since a load through a loaded pointer has no alias base), and
  only one memory unit. INSN_REG_WEIGHT decides: 871 is -1 (down dies there), 880 +1.
- **What retail's order needs.** `--prio 880=6` or `--prio 871=4` replays 880 875 871 882 1186:
  r307 is then live in v0 across the copy, so reload's register for down is v1, retail's
  `lq v1,32(sp); sq v1,0(sp)` (sched2 puts the load and store back ahead of the lw).
- **Not reload's round robin.** The spill registers are v0, v1 and vf3 (the .greg dump's
  "Spilling reg" lines), and the reload just before 871 in insn order is down into vf3 in the
  rhs loop, so allocate_reload_reg's rotation starts at v0; a v1 from rotation would need
  another reload in between, which retail does not have.
- **Ruled out.** The weight cannot favour a load over a dying store; adjust_priority's
  birthing raise needs r307 set once and live at the block's end (it dies at 882); every
  insn of the block is retail's, so no other dependent can lengthen 880's chain; and the
  store becomes MEM_SCALAR_P only as an addressable scalar (acc as a u128 read through
  `((f32*)&acc)[2]`), which purge_addressof allocates late (frame 0xA0, an extra saved s5
  in the 2026-11-10 probe). down as a Vec02 in memory (copy = load + store, 880 between
  them) swaps the frame slots and renumbers the counting loop's registers.

- **No barrier (w37, 2026-11-12).** A loop note between the contacts load and the copy (`ct =
  self->contacts; do { } while (0); Vu0::Q(acc) = down.q;`, a probe) makes the copy wait for
  the load in sched1 and reload then takes v1, but the note binds sched2 as well: the `lw`
  stays ahead of the `lq`/`sq` and the call's argument moves come out in another order, where
  retail has `lq v1; sq v1; lw v0`. So retail's sched1 order came from a rank, with nothing
  sched2 still sees. A frame variable for down is ruled out by the rest of the function (the
  product's vf3 is an output reload's register; local-alloc would tie a pseudo's to vf1), and
  the callee's return type by measurement. What would give the rank and leave no code: a copy
  between the contacts load and the head load (880's chain one insn longer, priority 6), a
  TImode copy feeding the store (871 ready a cycle later), or the birthing raise.

- **The order is not the lever (w40-fa, 2026-11-12).** A CLOBBER of the sum's slot before the
  copy (the sum as a union built in place by a brace initialiser at the copy, from a `const`
  source so that expr.c's safe_from_p allows it) gives exactly the order asked for above:
  the contacts load issues in the cycle after the call, the copy's store a cycle later, and
  reload takes v1. sched2 then keeps the `lw` ahead of the `sq`: after reload the load is
  through a hard register, which has no alias base, so it conflicts with the frame store and
  the two keep sched1's order (the -dR table lists the store among the load's dependents;
  in the near miss the link runs the other way). Even without the link the `lw` would issue
  between the `lq` and the `sq`, which waits two cycles for the `lq`. Retail has `lq v1; sq v1;
  lw v0`, so its sched1 had the store first, as ours has, and the loop-note probe above failed
  for this reason, not because of the note. What retail needs is in reload only: when
  order_regs_for_reload ranks the hard registers for insn 871, v0 is either forbidden (live as
  a hard register before or after the insn) or counted as holding a live pseudo, although the
  contacts pointer is not set yet. No instruction of retail's shows what that is. The
  candidates of the last paragraph (a copy, a TImode copy, the birthing raise, a CLOBBER) all
  work by moving the load first and are closed with this.

- **Solved (w44-fb, 2026-11-13): it is the round robin, and the reload in between is one whose
  code is the same either way.** Nothing occupies v0. finish_spills gives insn 871 every spill
  register of the function that no live pseudo holds (v0, v1, vf3), and allocate_reload_reg
  starts one past the register the previous reload took. The dots were written `bits =
  Vu0::ToBits(...); *(u32*)p++ = bits;`: the qmfc2's v0 was a pseudo's, so the last reload
  before 871 was the product's vf3 and the rotation wrapped to v0. Retail stored each dot with
  the asm store (`Vu0::StoreX(*p, Vu0::Dot(na, nb).q); p++;`, as its sibling
  ComputeConstrainedPushOut does): the qmfc2 is then StoreX's input reload, in v0 because the
  loop's pseudos leave it free, and the instructions are the same `qmfc2 v0,$vf1; sw
  v0,0(a3)`. The last reload before 871 is that v0, so 871 takes v1. Both loops need it (the
  Gram loop alone or the rhs loop alone: 5 lines differ). EXACT on US and PAL. The "not
  reload's round robin" entry above looked for a reload retail has and ours lacks in the
  final code; a reload that replaces a pseudo with the same register shows no difference
  there (docs/toolchain/reloads-and-stores.md, "A reload where ours had a pseudo").

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

### A burst's two records, emulated (func_00156288, 2026-11-10)

An emulator of sched1 for the block (build/swarm/w15-156288/sim.py in the g10 worktree, with
lasf.py for local-alloc's SFmode quantities and hyp.py for trying changes) reproduces the
`-dS -fsched-verbose-6` order of all 50 insns exactly. What it needed, read from haifa-sched.c:

- **Weights come from the notes before sched1.** find_pre_sched_live counts +1 for every SET
  pattern (a store too) and -1 for each REG_DEAD and REG_UNUSED, then removes the REG_DEAD
  notes; read them from the `.combine` dump, not the `.sched` one (recomputed after). A copy
  that GCSE placed after the last use of its source carries that source's death.
- **An insn made ready in a cycle waits for the next one** (the issue loop walks the ready
  array sorted at the cycle's start), and adjust_priority's max_priority is the larger of the
  issued insn's priority and that of ready[0], the lowest-ranked insn still ready.

What it showed, with `-1.0`, `5.0`, `1.047` and `0.39` the block's four constants:

- **Retail's FP registers are impossible with the constants loaded in this block.** Retail
  shares $f0 between 5.0 and -1.0, so -1.0's load came after 5.0's store. Every constant
  load has priority 4 and every store after the gravity load 2 (they wait for it: the world
  pointer is loaded from memory, no base), so sched1 loads every constant still pending before
  it stores any; no statement order, weight or single extra dependence changes that (searched
  with the emulator). A pseudo set once to -1.0 in an earlier block and used once is moved to
  its store by update_equiv_regs after sched1 ("A constant set in an earlier block and used
  once", alias-classes.md): an `f32 m1 = -1.0f;` at the function's top gives retail's 5.0
  $f0, 1.047 $f1, 0.39 $f2 and -1.0 $f0 (the stores' order then differs: 32 lines).
- **The tail's registers and its delay slot are one weight.** Retail's tail (8.0 $f1, 12.0
  $f0, the 1.0 store before the call and the cfg store in its delay slot) is the LUID order
  of its six stores when all weigh 0; ours weighs the 1.0 store +1 (the value lives on into
  the block record). With the tail's 1.0 a variable that dies at its store (`f32 rate = 1.0f;`
  at the top, an experiment) the tail is retail's exactly, but CSE then merges the function's
  earlier 1.0 literals into that variable (262 lines). Retail stores both records' 1.0 from
  one $f20 loaded once, so how its tail's 1.0 died there is still open.
- **The copy's destination.** Retail's a0/a1/a2 for the copy loop need `sp+64` born after the
  world pointer dies; ALU slots are never short in this block, so the address issues as soon
  as the call is done. Writing `blk.up` before `blk.gravity` gives retail's three registers
  (the world pointer is then loaded after up's store) but breaks the FP registers.
- **Ruled out.** An inline builder returning the record by value (two copies; with
  initialization one copy and retail's frame, the inline's frame at sp+192 reused by the
  position, but integrate.c's try_constants keeps the frame register for the non-immediate
  constants' stores and the world pointer is loaded before FillMemory); a constructor
  temporary assigned to the record (the same two differences); an inline holding the whole
  burst (`&blk` substituted as a constant: two insns short); the gravity through a `const
  Vec02&` (CSE folds the address back); one float variable reused for 5.0 and -1.0 (they
  share a register, but its first set rises to priority 7 and loads too early).

**Matched 2026-11-12 (w40-fa).** The last two lines (the up vector's store before the
gravity's) were a second CLOBBER in the block's brace initialiser, before the angles at 0x44:
docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER".

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

### The link swing's last block: what the two rankings need (func_001CC818, unsolved)

Second pass on the same block (w15, 2026-11-10), with the emulators above corrected to count
only the block's own pseudos (`used N times across M insns in block 36` in the .lreg dump):

- **The two rankings retail needs.** Local-alloc gives the six wrong registers through two
  comparisons. Scalar(r)'s quantity (3 refs: qmtc2, vmulx, slot store; a life of 32) must
  rank above off's (3 refs: vmulx, cross, p's vadd; 26), and the v150-to-quotient chain
  (6 refs over 14) below acc's (4 over 10), which one more insn inside the chain's life does.
- **Why the first one is hard.** Scalar(r)'s qmtc2 has priority 10 and only memory loads
  rank above it, so sched1 issues it in the first cycle after the call whatever else ties: the
  graph fixes its birth. Its death is the slot store, priority 4 behind the loads. Only a
  higher-priority store (a load that truly depends on it) or p's vadd moved to the block's end
  fixes the order.
- **What the emulators accept.** No single added or removed dependence, no swap of two
  LUIDs, no single priority, and no one or two insns added to the block give retail's
  fourteen registers. Pairs of added dependences do. One is the v150 load waiting for the
  Scalar(r) slot store, which fixes the first ranking, together with p's store before the
  f22AC load (or before ang's store). The other is the f22AC load ready only mid-block, after
  the v150 load, which ends the birthing raise in the first cycle after the call, together
  with the rate slot store ranked above a later store. Each is two changes, and no plain form
  gives either: the loads through `self` have the parameter's base, so they never wait for a
  frame store.
- **A second Scalar(r) gives the first ranking.** Writing p as `Add(pos, MulX(nd, Scalar(r)))`
  (CSE merges the qmtc2 and the vmulx with off's) gives Scalar(r) 4 refs, and the registers up
  to the cross product become retail's: m.r[1] vf3, Scalar(r) vf6, off vf7, acc vf2. It costs a
  second slot store, which retail does not have (54 lines).
- **Ruled out by compiling (16 lines unless noted).** v2 as a u128 (a spill slot at the top
  of the frame, 58). The quotient over Vec values. off and Scalar(r) as Vec values.
  ScalarAtValue and ScalarAtCall for r, rate and dt. ScalarAt(r) (r goes to memory, 182). p
  computed in place from off, and v built in two statements (the dead stores stay: flow1 keeps
  them, 52 and 57). Rotate's result stored to ang first. RotateMembers. RotateRowsTied (23).
  g computed from a named sum before v's store (23).
- **Confirmed by replay (wave 22).** tools/globalalloc.py --local with Scalar(r)'s quantity at
  2400 (off is 2307, ours 1875) and acc's at 17200 (the v150 chain is 17142) gives all fourteen
  retail registers and changes nothing else: the two comparisons above are sufficient as well as
  necessary.

- **The tail's order is the birthing raise, not a weight (w46-b, 2026-11-13).** Retail issues
  p's `vadd` before g's last `vsub`; the near miss had the reverse. In the `-dS` trace and the
  replay (`tools/sched1.py FILE func_001CC818 --block 36 --trace 2468 --trace 2503`) both are
  ready in cycle 21 with the same weight (one birth, two deaths) and the same table priority
  (3). The vsub's output is read by the else arm after the block, so it is set once and live
  at the block's end: adjust_priority raises it to 4, the priority of the DivX just issued,
  and it goes first; sched2 keeps that order. The earlier weight explanation (the vsub killing
  one value) is wrong. The raise is retail's too, so the vadd has to be issued a cycle before
  the two meet, which is p's statement written first.
- **Matched (w46-b, 2026-11-13): p first, and the offset written at each use.** The source is
  `p = pos + nd * Scalar(r); v = v2 + cross(acc, nd * Scalar(r)) + nd * rate; g = ...; ang =
  nd`, with no local for the offset. cse1 merges the two `vmulx` and the two `qmtc2`; the
  second Scalar's slot store stays through `.lreg` and depends on the first, so Scalar(r) has
  one more reference and its first store outranks the block's other stores (the first of the
  two rankings above), and reload deletes the repeat (the section "A weight written again in
  the next statement" below, func_00144540, whose worker gave the lead). With p's statement
  first its load and `vadd` are ahead of g's in insn order, which is the second ranking and
  the tail's order. The earlier trial of the second Scalar(r) (54 lines, "a second slot
  store") had p's statement after v's: rate's Scalar had taken the slot between the two, so
  the repeat was a real store. A grid of the offset named or in place at each use and of p's
  place: EXACT with p first and the offset in place at either or both uses, and with the
  offset in place in v only and p before g; 2 lines with p last; 54 with p's Scalar after
  rate's. Tried before the lead and not it: a twice-set variable for g's value (sched1's
  order of the two insns is retail's, but a pseudo of two blocks is global-alloc's and the
  early block moves), p's value live out of the block.

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

- **Block A's three stores are ranked by register weight, not by an alias fact (w46-c,
  2026-11-13).** Replayed on the probe's block (the row loads through `self + 0x660`, insns
  725 and 726; the stores of rows 0, 1, 2 to self, 589, 631, 673; m's rows 686 to 694): with
  the loads cut from row 0's store, and from each other's row, row 0's store falls to
  priority 2 and issues last, after rot's rows, where retail has it third. Retail's order of
  the block's whole second half (0x670, 0x680, 0x660, m's rows, the offset, the two row
  loads, the product, rot's row 0, v640, rot's rows 1 and 2) comes out when the stores of
  rows 1 and 2 weigh one less than row 0's, i.e. carry their products' REG_DEAD notes: the
  three tie on priority 6 with m's rows, and rank_for_schedule's second key is the weight.
  Row 0's product lives on (the transposed rotation reads it from its register). A raised
  priority gives the same order in the replay but not in a compile: rows 1 and 2 stored a
  second time right after the product leave no code and put row 1's store first, and its
  product ahead of row 0's with it (the priority passes down the chain). So m's and rot's
  rows 1 and 2 are stored from two other pseudos in the same registers, two copies that
  leave no code: the two insns local-alloc's lives asked for. What makes them is open; a
  copy through a pointer local (`m = *p`) gives the deaths and the order, but moves the rows
  through a GPR (lq, sq). The tilt's rows loaded in the order 1, 2, 0 give tilt row 1 and
  turn row 2 retail's vf3 and vf2 (row 1 then lives 9 insns). The tail is exact with the
  rows of frame->m110 read as Vu0::Vec members (the near miss's RotateTransposedMembers).

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

### A reader passed on and a void return: the counter's own register (PAL func_eu_001DDA10)

A PAL-only loader stored a count read from a stream, allocated a word per entry and read each
entry through a callee, `for (i = 0; i < count; i++) read(a0, &table[i]);`. Our attempt (53.8%)
called the reader as `ReadBufferedU16()` and returned the table; retail has one more saved
register (s5), the counter in s2 from the prologue, and no load of the table after the loop.
Both were signature errors, not scheduling ones:

- **The reader takes the stream.** Retail's first `jal` has no argument move because `$a0` is
  still the incoming parameter: ReadBufferedU16 is `s32 (void* self)` (its other callers pass
  it). With the argument, the parameter's copy to `$a0` sits before the call, and sched1 then
  puts combine's `i = 0` (which combine sinks to the rotated loop test, merging the test into
  `blez count`) before the count's load instead of after it. The counter is born while the
  count's `%hi` pseudo is still live, conflicts with it, and global-alloc gives it a register of
  its own (s2) rather than reusing the dead `%hi`'s s0; sched2 then hoists `move s2,zero` into
  the prologue.
- **It returns nothing.** The `v0` retail has at the return is the table's reload that reorg
  copied into the loop's delay slot; `return table;` adds a load at the exit and a blez target
  before it. The caller (func_eu_001DDC68) never reads `v0`.

Check a callee's first argument register even where retail never sets it: an unchanged `$a0`
passed on is invisible in the caller's code but shifts sched1 (as in func_0018AD88).

### A product's operand order sets the next constant's register (func_0017E710)

- **What differed.** Before FindNodeForQuery the second loop of func_0017E710 has
  `q.weight = self->mass * D_00264034; q.kind = 0x20;`. Ours put the 0x20 in v0 after the
  weight slot's `qmtc2 v0` and sched2 placed the `sw` of the slot in the call's delay slot;
  retail sets `li v1,32` while v0 still holds the weight slot's word and stores the weight
  before the call. The first loop, with the same statements, is retail's in both forms.
- **The form.** `q.weight = self->mass; q.weight *= D_00264034;` (or the constant named first,
  `f32 k = D_00264034; q.weight = self->mass * k;`) gives the constant's load an earlier LUID
  than the member's: the multiply keeps `mul.s $f0,$f0,$f1` with the mass in $f0, and the
  0x20 takes v1. `D_00264034 * self->mass` gives the same order with the registers swapped.
  Found by trial (three forms); the dumps were not traced, so the pass that decides it is a
  guess: the load order changes sched1's ties and with it the order local-alloc sees.

### The quadratic's head: a priority wall between dot2's conversion and dot3 (func_00141D88, unsolved)

Resolved 2026-11-10 (w20): not a priority wall but regclass's. With ToFloatMoved's operand
`"*r"` each dot is a VU0 pseudo, and func_00141D88 and func_00141F48 are EXACT with all three
conversions as ToFloatMoved (docs/toolchain/vu0-helpers.md, "A GPR operand that leaves the class
to the producer"). The analysis below is kept for its reading of sched1.

Read from the `-dS -fsched-verbose-6`, `.combine` and `.lreg` dumps (2026-11-10, w15), for
func_00141D88 and func_00141F48 (the same head: `c = Dot(pa,pa) - r*r`, `hb = Dot(ab,pa)`,
`ha = Dot(ab,ab)`, `disc = (hb+hb)^2 - ha*(c*4)`):

- **What each pass needs.** Local-alloc (emulated with lalloc2.py over the `.lreg`) gives
  dot3's 1.0 retail's vf5 only when dot2's result (vf4) is still live at dot3: dot3 issued
  in sched1 before dot2's qmfc2, or directly after it. Retail's `qmfc2 v1` for dot2 needs
  dot1's ToBits GPR to die (its mtc1) directly before dot2's qmfc2, as the near miss has.
  sched2 then gives retail's order only with dot3 in vf3/vf5: with dot3 in vf4 it is
  anti-dependent on dot2's qmfc2 (3 dependents), which then wins the priority-15 tie with
  the 4.0 load (`lui at,0x4080`) by LUID; in vf3/vf5 the qmfc2 has 2 dependents, the load
  goes first and the sequence m1, 4.0, sub.s c, qmfc2 v1, mtc1 v1, dot3 is retail's.
- **Why sched1 cannot.** dot3's longest path is dot, qmfc2, mtc1, `ha*(4c)`: priority 13 at
  most (ToFloatViaBits; 12 with ToFloat, ToFloatNow or ToFloatMoved). dot2's qmfc2 is 15
  (ViaBits) or 14 (Now, ToFloat), dot1's mtc1 17, `c - r*r` 16, the 4.0 load 15, and all
  are ready from cycle 6 while dot3 is ready from cycle 5: dot3 can never issue before or
  right after dot2's conversion. When dot3 finally ties, twoB's add has been raised by
  adjust_priority to 14 (it sets a pseudo set once and live at the block's end: the
  roots' `-twoB`) and goes first. INSN_REG_WEIGHT is 0 for both (dot3 kills ab and has
  one REG_UNUSED), so the earlier note that the dot weighs 1 was wrong; the raise decides.
- **Probe.** `ha = ToFloatViaBits(...) + 0.0f` (dot3's path +3) puts dot3 before dot2's
  qmfc2 and gives every VU0 register of retail: the lever is dot3's priority, by at least
  one cycle, with nothing visible in the code (a copy kept until allocation and deleted by
  reload would do it).
- **Ruled out (w15).** All 64 ToFloat/ToFloatNow/ToFloatViaBits/ToFloatMoved mixes for the
  three dots (the near miss's ViaBits/ViaBits/Moved stays best at 9 lines; all ToFloat and
  all ToFloatNow give every VU0 register of retail but 17-18 lines of order and GPRs);
  each dot written over Vec values (`Dot(Vec::Of(x), Vec::Of(y)).q`, the movti copies are
  gone before sched1: the 448 forms score as their u128 twins); `twoB = hb; twoB += twoB`
  (combine merges the copy, twoB is set once again); an inline root solver taking
  `(roots, a, b, c)` (CSE propagates its parameter copies, and the returned count adds a
  test).

### Two axes through one inline method: the clamp's store first in its block (func_00185538)

GetAimRotation (main_loop.cpp) runs the yaw and the pitch toward its target each through a
quadratic `a + x*(b + x*c)` and a clamp to a range, from two 0x20-byte records at +0x50 and
+0x70 of the aim (curve at +0, ValueRange at +0x10). Retail clamps the yaw in one register (sum,
result and the store all `$f3`), stores it first in the block that starts the pitch, and
clamps the pitch with a separate result (`$f13` in, `$f3` out). Written by hand, the yaw's
store had priority 2 in sched1 (no dependent: the pitch's loads go through `self` plus a
constant, whose base alias.c knows, and the frame store cannot conflict with them), so it sank
to cycle 6 and kept the yaw live into the pitch (global-alloc then gave it `$f4`, with lo and hi
in `$f5` and `$f0`). Every hand form of the yaw clamp tried (in place, in the array, with a
reused variable, through a pointer) left it there or worse.

Written as one inline method of the record, `f32 AimAxis::Apply(f32 x) { return
limits.Limit(a + x*(b + x*c)); }`, called once per axis, both clamps are retail's: the inline's
`this` is a pseudo alias.c gives no base, so the pitch's loads through it may alias the yaw's
frame store, which becomes their dependent's head (priority 20) and is issued first; the yaw's
sum, result and store then share `$f3` while the pitch, with the same code, keeps its sum in
`$f13` (the argument register it is copied to). The same inline giving the two axes different
code is the sign: where two retail sequences differ only in their registers and in whether a
result copy survives, try one shared inline before writing each by hand.

The rest of the function was two smaller things: `Vu0::Q(d) = ...` left the inline's `&d` in a
pseudo that the later `GetVectorAngles(&d, ...)` reused (a0 set before the range test, retail
sets it in the branch's delay slot), fixed by storing through `*(u128*)&d` as vu0.h's Set note
says; and BuildYawPitchMatrix's parameter order (alias-classes.md, "A prototype's parameter
order").

### sched2: a variable set after the first call keeps its save late in the prologue (func_00187260)

Retail's prologue saves s6 and s2 after the others (`sq s3; move s4,a0; swc1 $f21; move s3,t1;
sq s6; mov.s $f21,$f12; sq s2; move s6,zero; sq ra; move s2,zero`), ours in register order.
In sched2 every insn of the first block is a predecessor of the block's last insn; the
parameter copies and anything else before the call (here `PushBackMemoryMark()`) are also
predecessors of the call, so they have priority 3 and the saves they wait for (anti
dependences) 4. `n = 0; nv = 0;` written in the declarations are such copies; retail's two
zero moves have priority 2, so they come after the call in the source (`PushBackMemoryMark();
nv = 0; n = 0;`): they set call-saved registers, sched2 lifts them above the call, and their
saves fall to priority 3, where the rank's dependents count (two: the move and the call) puts
them before ra's save (one). The order of the two moves follows their order in the source.

### A length turned into a depth in place (func_00187260)

Retail's edge hit takes the square root into $f2, divides 1.0 by it, and only then subtracts
the radius into the same register (`sqrt.s $f2,$f1; ... div.s $f0,$f0,$f2; ... sub.s
$f2,$f2,$f21`). With `f32 len = Fpu::Sqrt(dsq); f32 depth = len - radius;` sched1 issued the
subtraction before the division and the depth took a register of its own ($f3), with a `mov.s`
of the root. Reusing the variable, `f32 depth = Fpu::Sqrt(dsq); ... (the normal, scaled by
1.0f / depth) ...; depth -= radius;`, gives retail's code: the variable is set twice (two
lives of one pseudo, no birthing raise in adjust_priority) and the subtraction stays where it
is written, writing the register it reads.

### A product written into a dying operand's variable keeps sched2's order (func_001D7778)

In StepPathFollower's first loop `force = dir * Scalar(push * mass)` and `accel = force /
Scalar(mass)`. FromFloat's asm reading `mass` is ready one cycle after the load (an asm
consumer's link is cost-free in insn_cost) while the multiply waits two, so sched1 puts the asm
first; `mass` then dies at the multiply and local-alloc gives the product mass's `$f0`, and
after reload the mfc1 of mass must precede `mul.s $f0` (anti-dependence). Retail's `mul.s
$f1,$f1,$f0` is the product in push's register: `push *= mass;` makes the product push's own
pseudo (global, `$f1`), and sched2 is free to issue the multiply first. In the same block the
torque's cross product before the accel's division (`vdiv` first in retail) is the source order
force, torque, accel: their asms tie on priority and LUID decides.

### The zero trap of func_00202140: what sched2 needs (matched 2026-11-13)

**Matched (w47-h, 2026-11-13).** The magnification is not a local: it is written out at each
of its three uses in the register's macro (`#define MAGH(w) (((w) + 0x9FF) / (w))`, in
`dx * MAGH(w)`, `MAGH(w) - 1` and `MAGH(w) * w - 1`). Each use expands its own `divmodsi4` and
its own `trap_if`. cse1 folds the three divisions into one (12 `div` in `.jump`, 4 in `.cse`), but
nothing deletes a `trap_if`: all three live to the `.dbr` dump (12 in the
function against 4 with a local), and only the first of a run writes code (the `.s` has one
`beql/break` per arm): a trap whose LOG_LINKS hold an anti dependence on another trap prints
nothing (the `div_trap` pattern's output code in GCC's public mips.md looks for exactly that
link; in the `.dbr` dump the second trap carries `(insn_list:REG_DEP_ANTI 158)` and the third
`169`). Two divisions by one divisor in a block share a trap the same way. In sched2 each trap waits for the one before it (a TRAP_IF flushes the
pending memory lists) and the field load waits for the last, so the first trap's priority is
`1 + 1 + 1 + 3 = 6` where the single trap had 4: above dy's shift (5), level with dy's mask
and after it on luid, which is retail's `div; andi; beqzl/break; dsll`. The two later traps
issue after the shift and leave no code. So the "dependence ours lacks" below was a chain of
two insns that emit nothing, between the trap and the field load. The tell for other
functions: a zero trap issued earlier than its priority allows, or a memory load held back
after a division, where the quotient is used more than once: write the division at each use.
The analysis below is kept as it was written.


Measured 2026-11-10 with 2.9-ee-991111's `-dS -dR -fsched-verbose-6` dumps of the near miss
(src/lib/graph.c's DISPLAY register; build/swarm/w15-202140/tp.sh prints the sched2 table of
the block holding the first trap):

- **A TRAP_IF only orders memory.** haifa's sched_analyze_2 calls `flush_pending_lists (insn,
  1)` for it: it waits for earlier stores, and every later memory reference waits for it. In
  the interlaced arm the only later reference is the field load (`lh a2,4(a2)`, cost 2, read
  only by the beqz), so the trap's priority is 1 + 3 = 4.
- **sched2 keeps sched1's links.** Block 7's sched2 RTL lists the same producer twice
  (`(insn_list 157 (insn_list 157 ...`) and keeps pseudo-era links such as the multiplies'
  to the div after reload added the `mflo`: a link sched1 made still counts in sched2.
- **What retail's order needs.** At t=3 the trap and dy's `dsll a3,v1,12` are both ready;
  the shift has priority 5 through its anti dependence on the dx term's `daddiu v1` (which
  has 4: `andi a1,v1` and the dw term's `dsll32 v1` write and read v1 after it). With
  retail's registers the shift's 5 is fixed, so retail's trap had 5 and won on the tie (luid,
  dependents): an edge from the trap to the `daddiu` (priority 4), or from the field load to
  the magh or dw shift (priority 2), or the dw term's `dsll32` absent from the block at sched2
  (the `daddiu` then has 3 and the shift 4, tied with the trap). The last fits a `dsll32`
  computed at the start of each field arm, which reorg moves into the beqz's delay slot from
  the fall-through and redirects the branch past the target's copy; but fold saves every
  term that is not a plain variable before the test (its COND_EXPR rule's COMPOUND_EXPR), so
  no spelling of the macro tried puts the shift in the arms.
- **Ruled out** (all leave the six instructions or worse): the field read into a local (in
  the arm or for the function), its casts, the arms as `== 0`, `2 * h`, `h + h`, the dw term
  as a product or through a (u32) or (s64) cast, the dy mask after the shift, a sixth MAGV
  term (a constant or a local 0, all 720 orders), the interlace arms swapped, a dh local, the
  word built in a u64 local.

- **Second look (w46-d, 2026-11-13): the shift is not in the arms; the block ends before it.**
  reorg.c's fill_simple_delay_slots takes a conditional branch's slot from the insns before
  the branch first. With dw's shift at the head of each arm the slot would hold the block's
  last insn and the arms would start `sll v0,s3,1; dsll32` (the dh chain ranks above the
  shift); compiled with the shift in the ternary's text over a dw local, that is what comes
  out (`beqz; andi`). Retail's `addiu a0,a0,-1; beqz a2; dsll32 v1,a0,0` has the shift as the
  last insn before the branch, so the third option above is out as stated. What the
  priorities need is the trap level with dy's shift and below dy's mask (retail issues
  div+andi, then trap+dsll). A block that ends before dw's shift does it: without the
  `dsll32 v1` and the jump in the block the chain shift -> daddiu -> andi is 3 and the trap ->
  lh is 3, the trap wins on luid, and the rest replays to retail's order (the dx term's andi
  must be in the first block: with it in the second the trap rises above dy's mask and issues
  a cycle early). So retail's sched2 saw `[... lh field ...] | [dsll32 v1,a0,0; beqz]`, a
  boundary that leaves no code, with the field loaded and sign extended before dw's shift was
  expanded. A probe with a dead if/else between the product and its shift (a statement
  expression, not a form) puts the trap first. Not found: a source form. This cc1 is a late
  1999 snapshot (its dumps carry `[bb N]` notes): jump turns an if/else of two plain sets
  into a conditional move (movn/movz; CountFrameBufferPages' `/ 64` is one), so an emptied
  if/else needs arms that are not plain sets, and fold treats `w * magh` and `magh * w` as
  equal. The interlace word needs no local: written `p->interlace` at each test, PRE keeps
  the HImode load in a register (the `lhu`) and the later tests extend it (`sll; sra`),
  retail's code (the dump: "PRE: redundant insn 143 (expression 10) in bb 6").

### Thirty-two products of equal priority: the order is the deaths (func_0019CC10, matched 2026-11-13)

**Matched (w49-g, 2026-11-13).** The statements in this order: `0 4 8 1 5 12 9 13 2 6 3 10 14
11`, then `16 20 17 21 7 15 18 22 19 23` (out indexes). The deaths are those asked for below:
every pair still dies in its x product, xa in out[7], xb in out[15], x in out[23], and out[7]
and out[15] come before z1's x products. But that alone is not enough: the order of the weight +1
products (the first fourteen) decides which of them fill the cycles while the pairs' later
products are not yet ready, and every swap of two neighbours in the first fourteen changes the
registers (from 4 to 43 lines). It was found by a hill climb over insertions and swaps of
the 24 statements, scored by bytes against retail (build/swarm/w49-g/f2/climb2.py; about
2,000 compiles from the near miss's order, the step that mattered being z3's ny and y products
exchanged). The fourteen are a diagonal walk (xa ahead of xb by a z weight) rather than a nest,
which is why the 1,728 regular nests missed it. The analysis below is kept as it was written.

Read from the `.sched` trace of ComputeGridBlendWeights' last block (file_198980.cpp,
2026-11-13, w46-d): eight pair products (priority 8), 24 triple products (5) and 24 stores,
one multiply a cycle and a store beside it.

- **The tie-break is INSN_REG_WEIGHT, then LUID.** The weight is the sets less the REG_DEAD
  notes of the source's order. Pairs: `z2*y`, the last pair written, has z2 and y dying (-1)
  and goes first; a z weight's second product and `z2*ny` (ny dies) are 0; the rest +1.
  Triples: out[23] has its pair and x dying (-1); every x product is its pair's last use (0),
  out[7] and out[15] are xa's and xb's last uses (0); the rest +1. The trace is exactly that:
  `z2*y z3*y z*y z1*y z2*ny z3*ny z*ny z1*ny | 23 16 20 17 21 18 22 7 15 19 | 0 4 8 12 ...`.
- **What retail's registers need.** local-alloc ranks `z2*y` (4 refs over 22 insns, 3636)
  below `z2*y*x` (2 refs over 4, 5000), so the triple takes f0 and the pair f1; retail has
  them the other way round. The pair's life must be 15 insns or less: out[7] and out[15]
  issued within the first eight triples, as retail's final order has them (23, 16, 20, 17, 7,
  18, 15, 22). In the weights' terms: out[7] and out[15] still the last uses of xa and xb, but
  written before z1's x products. No regular nest order has that (all 1728 were compiled).
- **ny.** global-alloc's first pass over the registers only takes one already in use; ours
  gives ny f10 because `z1*ny`'s quantity used it first, retail's ny has f2 and z1 f10.

### Two equal clears that retail issues apart: a rank sched1 cannot give (func_001A1030, matched 2026-11-12)

**Matched (w37-f3, 2026-11-12).** The two quadratics are brace initialisers of a type whose
first float is a union's member (`Quadratic16 a = { 125.0f, -25.0f, 0.0f }; Quadratic16 b =
{ 20.0f, 20.0f, 0.0f };`, include/shapes.h). store_constructor clears each local (`sq`), then
emits `(clobber (mem/s:BLK slot))` for the union before the first coefficient's store; a
BLKmode reference conflicts with every frame store, so b's CLOBBER depends on a's clear, a's
CLOBBER and both of a's stores, and b's stores depend on it. In the `.sched` table that is
exactly the rank asked for below: a's clear 6 and its constants 6, a's stores 4, b's clear 4,
b's CLOBBER 3, the 20.0 4 and b's stores 2, so b's clear issues after the life load and the
20.0 after the divide. Reload deletes the CLOBBERs (docs/toolchain/large-functions.md, "A
brace initialiser's union member is a CLOBBER"). The analysis below is kept as it was written.

UpdateSpringEffect's first block (two quadratics' coefficients cleared and set on the
stack, `t = (g_gameTime - start) / life`, the clamp's first test) is the only part still
off (2026-11-10, `-dS -fsched-verbose-6` dumps, haifa-sched.c and alias.c read):

- **What retail's sched1 order must be.** After reload every `sp` store conflicts with
  every load through `a2` in sched2: `sp` is set twice (prologue and epilogue), so
  init_alias_analysis gives it no base and base_alias_check answers "may alias". Retail's
  final order therefore fixes sched1's: a's clear (`sq 80`) before the `start` load, b's
  clear (`sq 96`) after the `life` load. local-alloc fixes the rest: the 20.0 shares `$f0`
  with the difference, so its set comes after the divide.
- **Why no statement order gives it.** The issue rate is 2 and the loads use the one
  memory unit, so the start load is at clock 3, the life load at 4, and the second slot of
  clock 2 and of clock 3 goes to the best non-memory insn ready: a's clear, b's clear (each
  priority 3, INSN_REG_WEIGHT 1: a store is a SET; three dependents) and dt's copy from
  `$f12` (priority 2, weight 0: `$f12` dies). Retail needs a's clear at clock 2 and dt's
  copy at clock 3, b's clear at 4 behind the life load. The two clears have the same rank
  but for INSN_LUID, so anything that beats b's clear at clock 3 beats a's at clock 2 too
  (a dt copy of priority 3 wins both on weight). And the 20.0 (priority 4, three
  dependents: two stores and the jump) beats 125 and -25 (two each) at clock 5, so it is
  set before the divide. The b member stores' output dependences on the clear give it
  priority 3 whatever the order (mips_adjust_cost makes an output link cost 1; a store's
  own priority is 2), and frame stores never wait for loads through a parameter or a
  global in sched1 (a stack base never aliases), so nothing delays it.
- **What would.** b's clear and the 20.0 both ranked lower: the 20.0 read by one store only,
  or b's clear with priority 2 (it would then lose to dt's copy on weight), or an insn ready
  at clock 3 only (a dependence on a's clear) raised by adjust_priority's birthing rule. A
  reused float variable (`k = g_gameTime - start; t = k / life; k = 20.0f;`) puts the 20.0
  after the divide by its anti-dependence and gives retail's issue order for it, but it is
  not plausible source and leaves the registers off (18 lines).
- **Ruled out (w15).** `b.y = 20; b.x = b.y`, `b.x = b.y = 20`, `b.y = b.x = 20`,
  `Vec02 b = a` (CSE folds the copy to the constant store), b's initialisation after the
  clamp (the stores move to the join block), an inline setter for b or a, an inline
  `(g_gameTime - e->start) / e->life`, the quadratic as an inline over `const Vec02&`, the
  clamp's parameters by const reference, dt's weight through a `const f32&` inline, and the
  whole update as an inline taking `(self, a, b, dt)` (the frame moves).

### Spill stores between float constants: counting a preheader's %hi/%lo pairs (func_00134B48, matched 2026-11-12)

Wave 15 (2026-11-10). The second loop's preheader differs from retail's only in where two
spill stores fall among four float constants (`sw a1,540(sp)` / `sw a2,544(sp)`, &pos's and
&screen's frame addresses, loop invariants that PRE put at the loop header and loop.c's first
pass moved out, spilled because nothing rematerializes `sp+N`). The detail is in
alias-classes.md ("Confirmed in US func_00134B48"); what this wave added:

- **sched2 only replays sched1's LUIDs here.** In sched2 the constants (`lui at; mtc1`, the
  memory unit, one per cycle) and the spill stores all have priority 2, class 3 and no
  dependents, so they issue in LUID order, and a spill store's LUID is its `addiu`'s place in
  sched1's output. Retail's order needs sched1 to emit `1728.0, &pos, 16.0, x, 0.4545, &screen,
  1936.0`: &pos picked second in the first constant's cycle.
- **Exactly two pairs may rank ahead.** At issue rate 2, only a `%hi` with an in-block `%lo`
  (priority 2, one dependent) and a `%lo` raised by adjust_priority (priority 2) rank before
  &pos (priority 1, no in-block predecessor). Two pairs fill cycles 1 and 2 and leave the
  first constant and &pos to cycle 3; a third pair (or one extra priority-2 ALU insn, at
  any LUID) always puts something between them. A `%lo` that ends its `%hi` (weight 0) beats
  a constant; one whose `%hi` lives on (weight 1) falls behind it by LUID; a lone `%hi` beats
  a weight-1 `%lo` on its dependent count.
- **Where our third pair comes from.** Limit's `this` (REG_EQUAL `&g_unitRange`, a move-insn)
  is re-emitted by loop.c's second pass with emit_move_insn: a fresh `%hi` (a new pseudo) and
  the `%lo`, at the end of the preheader. cse2 then replaces the fresh `%hi` with PRE's pseudo
  for the same `high`, set earlier in the same block by the first pass, and deletes it: the
  `%lo` now depends on that `%hi`. An experiment reading g_unitRange before the first loop
  (not a candidate form) kept the pair: PRE then left the body's `%hi` alone and the second
  pass moved it too, set again in the preheader. So any hoisted `this` brings its pair;
  retail's body code (`move a3,a2; addiu a3,a3,%lo` for the `+4` read: an unallocated pseudo
  with a constant equivalence, or an allocated one whose input reload took the output
  register, reload_cse then copying a2's `%hi`) fits both a hoisted and an in-loop `this`.
- **Ruled out (w15).** A range pointer declared before the second loop or at the function's
  top (the `lo` read is no longer folded into `%lo(g_unitRange)`: `lwc1 $f4,0(a2)`, s4/s8
  swap); the coefficient table addressed from D_00261190 (`&D_00261190[4]`: g++ forms
  `high(D_00261190+16)`, its own GCSE expression, nothing shared with the first loop);
  the clamp with early returns reading `hi` after the first test (retail's preheader order,
  but g_unitRange's `%hi` takes s4, as the else-arm clamp did, and the code grows 4 bytes);
  two ApproachValueWithRamp calls in an if/else for f58 (not cross-jumped back, 1764-1772
  bytes).

Matched on 2026-11-12 (w46-a). The count above was right but its conclusion was not: a third
pair does not have to go, it has to come *before the constants*. All six insns of three pairs
rank ahead of the first constant when each `%lo` either ends its `%hi` (weight 0) or has an
earlier LUID than the constants (weight 1, no dependents, as a constant: the LUID decides).
Then cycles 1 to 3 hold the three pairs and cycle 4 the first constant with &pos, which is
retail's order. Our third `%lo` (Limit's `this`) lost that tie only because loop.c moved it in
its second pass, to the end of the preheader, after the constants the first pass had moved.

Why the second pass: move_movables lowers its threshold by 3 for every insn it moves
(`threshold -= 3`), so the 79 the pass starts with is 22 by the time it reaches the clamp (18
PRE-hoisted insns and the table's `%lo` moved before it): `22 x 1 x 4 = 88 < 282` insns, "not
desirable"; the second pass starts at 79 again and moves it (`79 x 4 >= 234`). A life of 13 or
more is moved in the first pass. The source is the form the coefficient table already had:

    const f32* k = D_002611A0;
    const ValueRange* lim = &g_unitRange;
    ProjectPointToCamera(...);
    ...
    f32 alpha = lim->Limit(scale);

The pointer is named before the projection, so its life spans the call (`Insn 709: regno 292
(life 47), move-insn savings 1 moved to 1459` in the first pass, between the table's `%lo` at
1457 and the clock's at 1461); cse1 still
folds the `lo` read into `%lo(g_unitRange)` because the declaration and the clamp are in one
extended block (the call between them does not end it), which a pointer at the top of the
body, above the string loop's labels, did not give. Named before `k` the code differs in 6
lines (its `%lo` is then issued before the table's and the two address pairs swap); named
after the projection it is EXACT as well. The tell: an insn of a preheader that retail issues
earlier than ours, when ours was moved by the second pass; `-dL` prints the pass, and the
threshold at an insn is 79 less three times the insns moved before it.

### The side test and the half-width: what retail's order needs of each conversion (func_00142278, unsolved)

Read from haifa-sched.c (priority, insn_cost, rank_for_schedule), the `-dS -dR -dl -dg
-fsched-verbose-6` dumps and a model of sched2's list scheduler (build/swarm/w15-142278/sim2.py
in the g10 worktree: hard-register dependences, sched1's stale true links, link cost 1 into an
asm or for an anti or output dependence, two issues a cycle, one insn per unit; it reproduces the
near miss's sched2 order of the block exactly) (2026-11-10, w15):

- **The side test's block needs ToFloatViaBits for all three, and the s dot before side's qmfc2
  in sched1's output.** Retail's order (dot side; both crosses; the zero; dot s; side's qmfc2 and
  mtc1; dot u; the compare; the qmfc2s of s and u; their mtc1s) comes out of sched2, with retail's
  registers (side v1, s a0, u v0), only for side ToFloatViaBits (or Moved) and s and u
  ToFloatViaBits or Moved, and only when the s dot's LUID is below side's qmfc2: they tie at
  sched2 priority 6 with three dependents each, so the LUID decides. ToFloatNow for side loses
  the zero's tie on dependents (its asm also writes the FPR the u conversion writes), ToFloat for
  side adds the compiler mtc1's 2 cycles. Moved for side, its qmfc2 a reload right after the dot,
  never gives it. u's qmfc2 and mtc1 are split in retail (`qmfc2 v0; mtc1 a0; mtc1 v0`), so u
  is not ToFloatNow either.
- **sched1 cannot.** sched1's output is sched2's LUID order. With ToFloatViaBits side's qmfc2 has
  priority 6 (qmfc2, mtc1, the compare's 3, the branch), the s dot 5 (the division's link to
  the branch costs 1), and the qmfc2 is ready a cycle before the s dot can be: it always goes
  first. No conversion of s or u lengthens the s chain (ToFloat, Moved and Now are shorter), and
  the zero named in an earlier block (update_equiv_regs moves its set after sched1) frees a slot
  but not the tie. This is the quadratic's head's wall again: a dot's chain one cycle short of
  a conversion's, with nothing visible in the code to lengthen it.
- **The half-width's conversion is Moved whose pseudo lives in VU0.** Retail's `qmfc2 a0` (w),
  `qmfc2 v0` (k), `qmfc2 v1` (kk) are reload's spill registers in turn: ToFloat for w (its "=r"
  float reloaded through a GPR) gives exactly those, where Moved's TI_REGS pseudo, tied to
  nothing (cd lives on, m is global), takes $v0 from local-alloc (the GPRs come first in its
  order, VU0 registers still free). ToFloat also gives retail's dot vf3 and scratch vf4 (a VU0
  pseudo allocated before the scratch). But its qmfc2 is an asm with no unit, so sched2 issues
  ab's `lqc2` beside it and the mtc1 a cycle later; retail's order (qmfc2, mtc1, lqc2, div.s) is
  the compiler's qmfc2, which needs the vu0 unit the lqc2 also takes, as Moved's reload copy
  does (the near miss has that order). So retail read a VU0-allocated dot result through an
  "r" operand. Not reached: the Vec forms of the dot (their copies are gone before regclass), the
  dot named before or after the square root, the division written apart, and all 64 mixes of
  the four conversions for w, k and kk (Moved for all three stays best, at 8 lines).
- **With the "*r" ToFloatMoved (wave 22, 2026-11-11), one local-alloc comparison is left.** The
  side block's order is now retail's and 13 lines differ, all from local-alloc: side's dot
  quantity (2 refs, life 8, priority 5000) is placed after the second cross product's (4 refs
  over 16, 10000), which takes vf1. tools/globalalloc.py's local replay with the side dot at
  10000 (a tie, won on the lower quantity number) gives every retail register of the block. That
  is a death 4 earlier: side's conversion issued first in sched1's second cycle, which needs
  priority 6 (the crosses tie at 5 and win on dependents). ToFloatViaBits for side gives exactly
  that and retail's side registers, but its extra insn puts s's and u's dots side by side, so u's
  1.0 takes vf6 and the global n moves to vf7 (39 lines).

### A curve's value named before the clamp that scales it (func_001A3250)

DrawFacingEffect scales its object by `Eval(q30, t) * near`, where `near` is a quadratic of the
camera distance clamped to a range (the file's `ClampedQuadratic::Clamp`). Written with the
distance `k` first, then `t`, the clamp, and `Eval(q30, t)` inside the Splat after it, the code
was 8 bytes short: the q30 quadratic was computed after the clamp's join, so the clamp's result
could share its input's register in the first two clamps, and `t`'s loads and its `div.s` were
scheduled after the distance's. Retail computes `t` first (g_gameTime's `lui` is hoisted above
the Length), evaluates the q30 quadratic in the block that ends in the clamp's first compare
(its last `add.s` fills the `bc1f` delay slot) and keeps the clamp's result in its own register
(`mov.s $f0,$f5` / `mov.s $f0,$f4; mov.s $f0,$f6`). `f32 t = ...; f32 k = ...; f32 s =
Eval(q30, t);` then the clamp and `Splat(s * near)` give retail's blocks and sizes; the last 22
differences, all of the order inside the first block (the 0.001 constant before the `qmfc2`,
`sub.s` before the `mul.s` by 0.001), went with `Vu0::ToFloatMoved` for the length instead of
`ToFloat` (the conversion lever above). The clamps stayed the file's own inline; ValueRange's
Limit gives the same code here.

### A variable reused for a second half: no birthing raise, more references (func_0020CAF8)

Measured 2026-11-10 on the MPEG macroblock prediction (src/lib/mpeg_macroblock.cpp,
2.9-ee-991111; nonmatching/func_0020CAF8.cpp), which computes a luma and a chroma part with the
same arithmetic. The near miss was three words short with separate chroma variables; retail's
registers show some of the luma variables holding the chroma values (the column sum in t0 both
times, the vertical flag in t9 both times).

- **Reusing the column sum (`xs = (cdx >> 1) + (x >> 1);`) makes it a pseudo set twice.**
  adjust_priority's birthing rule then no longer raises the luma add `xs = (dx >> 1) + x` in
  block 0, so sched1 issues it after the count's address add instead of right after the shift.
  The shift's life now spans that add's v1, local-alloc gives the shift t2 (x's incoming
  register, already copied), and reload cannot inherit x from t2 for the add: retail's
  `sw t2,4(sp); lw a3,4(sp)`, one of the three missing words.
- **Reusing the flag (`fy = cdy & 1;`) gives it six references** (two sets, two tests, two
  selector terms). Its global-alloc priority rises from 0.057 to 0.110, it is placed before the
  long-lived saved-register values, and the routine index (2 refs over 81 insns) no longer finds
  a free register: it is spilled at 12(sp) as in retail, which also moves the later slots to
  retail's offsets. Reusing the other flag, the row sum, the offsets or the base as well
  lengthens lives and spills more (64 subsets tried; xs and fy are the best, at retail's size).
- **Spot it.** Two parallel halves of a function where a luma value and its chroma
  counterpart share a register in retail although both lives are long: try one variable for
  both, assigned again for the second half. A missing reload of a parameter just after its
  spill store points at a birthing raise that should not have happened (a variable set twice).
- **Still differs** (85.9% "order"): fy is placed 16th and takes s0 (retail t9), which shifts
  three parameters one saved register; half and the luma part swap t4 and t5.

### Two literal %hi's issued in one cycle (func_0013A618, func_0013A940; solved 2026-11-12, see the end)

Both bound vectors of these two functions start as `{FLT_MAX, FLT_MAX, FLT_MAX, 0}` and its
negative, loaded from the function's literal pool (the file's .rodata). Retail: `lui v0; lwc1
$f0; ... lui v0; lwc1 $f1`, the second `%hi` reusing v0 after the first load, the TI zero of the
clears in v1. Ours: both `lui`s in the first cycle (v0, v1), so the clears' zero takes v0 and the
list-frame push that follows takes other registers. In sched1 both `%hi`s have priority 26 (every
bound store feeds the load of the list's link offset, which may alias the frame), issue_rate is 2,
and both are ALU insns ready at t = 1, so the second is issued with the first; retail's order
needs the second at priority 25 or less, or another insn of 26 ahead of it. Ruled out: chained
assignments after `= {}` clears (worse store order), the initialisers (retail's z, x, y store
order, kept), named extern const bounds (folded to the same literals), the list-head pointer as
an OffsetList* (the load no longer waits for the stores: not retail), the bounds' assignments
after the frame push, and declaration orders (the frame slots follow declaration order).

Solved on 2026-11-12 (w40-fb): the bounds are brace-initialised union-first vectors
(`Quadratic16 lo = { { FLT_MAX }, FLT_MAX, FLT_MAX, 0 };`, include/shapes.h). store_constructor
puts a CLOBBER before the union member's store (docs/toolchain/large-functions.md, "A brace
initialiser's union member is a CLOBBER"), each bound's stores hang on it, and the second
`%hi` no longer shares the first's priority: both prologues are retail's, with the clears' zero
in v1, the second `lui v0` after the first load and the frame push's registers (e in v1, &fr in
a3, the `%hi` of g_activeListFrames in a2). The functions' literal pools check exact with it.

  three parameters one saved register; half and the luma part swap t4 and t5. (Resolved
  through global-alloc's pass 0 the same day: docs/toolchain/long-block-constants.md, "Pass 0
  takes no new saved register" (func_0020CAF8).)

### Two weights' qmtc2s tied on priority: dependents decide local-alloc (func_001C54D0, matched 2026-11-12)

The tail of func_001C54D0 is `end->v30 + m110.r[2] * -push + tangent * f63C` through MulAddX2,
with `Scalar(-push)` (insn 865, after a neg.s) and `ScalarAt(self->f63C)` (insn 901, its word an
asm memory operand) sharing one weight slot. Retail gives the f63C weight vf5 and a1, the -push
weight vf6 and a0; ours the reverse. tools/sched1.py replays the block exactly, and the g11
local-alloc emulator (build/swarm/w5-1D2518/lalloc2.py) fed the replayed order with 865 moved
ahead of 901 gives retail's VU registers (the f63C quantity is born late enough to outrank the
-push one and take vf5, which row 0 frees), and reload's round-robin then gives 865 a0 first.
In sched1 both are ready at cycle 4 with priority 4 and register weight 0 (865 kills the neg's
result, 901 kills self); 901 wins on its dependents, three (the MulAddX2 asm, its slot store, and
an anti dependence from the store to end->v30, which may alias its unflagged read) against two.
What would flip the tie each costs something retail shows: a later use of self gives 901 weight
1 but only by reading m110.r[2] after it (self then dies at that load, which takes the cycle);
naming the f63C weight first puts its slot store ahead of -push's in the shared slot (retail
stores -push's first); ScalarAtValue, ScalarAtCall and Scalar read the word the same way or
through an FPR. Spot it with `--trace 901` and a lalloc2.py order: when a ready list holds two
asm insns of equal priority, the dependents count (slot stores and anti dependences included)
is the tie-break to check.

The w24 pass closed the rank: both insns are asms, so every link into them costs 1
(LINK_COST_FREE) and both are class 3 against whatever issued last; 901 depends on nothing in the
block, so 865 can come first only by outranking it or by 901 gaining a predecessor. The anti
dependence from end->v30's store stays: self and c are both incoming arguments, which alias.c
lets alias (base ADDRESS of VOIDmode, -fargument-noalias and -fstrict-aliasing off). An edge
865 -> 901 injected into the replay gives retail's VU registers through lalloc2.py; an edge from
the -push slot store to 901 does not. A plain "r" u32 operand splits the f63C load into its own
pseudo (no memory in the qmtc2, so 2 dependents against 2, and 865 wins on its LUID): -push then
takes retail's a0 and vf6, but local-alloc gives the loaded pseudo v0 where retail has a reload's
a1. What is left is a source fact that makes the f63C weight wait on the -push one, or keeps its
load out of the qmtc2 until reload; no plain form of either was found
(nonmatching/func_001C54D0.cpp, W24).

Matched on 2026-11-12 (w46-a) by the rank's second field, the register weight, which the
passes above had tied at 0 against 0. An insn's weight is its sets less the REG_DEAD notes it
carries *in the insn stream's order, before sched1*. With the tangent in a local ahead of the
sum, the f63C read was self's last use in that order, so 901 weighed 0 and the dependents
decided. Written as one expression with each weight before its vector,

    Vu0::Q(end->v30) = Vu0::MulAddX2WeightFirst(Vu0::Vec::Of(end->v30).q, Vu0::Scalar(-push),
        Vu0::Vec::Of(self->m110.r[2]).q, Vu0::ScalarAt(self->f63C),
        RemoveAlong(Vu0::RotateMembers(self->m660, Vu0::Vec::Of(self->v640).q),
                    Vu0::Vec::Of(c->v80).q));

the inline call emits its arguments in parameter order, so the rotation's loads follow both
weights and the up axis in the insn stream. Self then dies at the rotation's first row: the
f63C qmtc2 weighs 1 (a set, no death) and the -push one 0, so -push issues first at the tie
(retail's a0 and vf6); the up axis's load weighs 1 as well and loses to the f63C qmtc2 on
dependents (2 against 3), so it stays the later use of self and reload's `lw` takes a1 rather
than self's own register. The same order explains the second difference, which the tied form
had only approximated with RotateRowsTied: v640 is read before the rows (RotateMembers takes
it by value, its rows as Vec members that no weight slot holds back), row 0 carries self's
death (weight 0) and wins the first cycle over v640, row 2 carries the row pointer's death and
wins the second, and v640 then beats row 1 on its LUID: retail's row 0, row 2, v640, row 1.
RemoveAlong is a file-level inline (the rotated vector is used twice). The tell for other
near misses: when two insns tie on priority and the wrong one wins on dependents, look at
which statement holds the last use, in source order, of a register one of them reads; moving
a later statement's loads behind it (one expression instead of named locals, or the reverse)
changes the weight and is decided before the dependents are.

### The 33rd memory reference of a block is a barrier (WriteMemoryCardSaveHeader)

Read from haifa-sched.c (sched_analyze_1, add_insn_mem_dependence, flush_pending_lists,
compute_block_backward_dependences) and checked in the `-dS` dump (w25, 2026-11-11):

- **The rule.** sched_analyze keeps every memory reference of the block (reads and writes) in
  its pending lists, and `pending_lists_length` counts them. A *store* analysed while the count
  is above 32 does not look for aliases: flush_pending_lists makes it depend (anti, cost 1) on
  every pending read and write, empties the lists, and makes it `last_pending_memory_flush`,
  which every later memory reference of the block (loads too) then depends on. The count starts
  at 0 for each single-block region (a loop's region carries it from block to block), and every
  call resets it (a call is itself a flush). The same happens in sched2 on the reloaded insns,
  where spill loads and stores count as well.
- **Where it acts.** WriteMemoryCardSaveHeader (func_0018CA10, matched, src/main/memory_card.cpp)
  fills a 0x3C4-byte frame record after FillMemory: two loads and 34 stores in one block. Insn
  209 (`c.f0A0 = 0.33f`, the 34th reference after the call) carries anti links to all 33
  references before it, and every store after it (215, 221, ...) has exactly one memory link,
  to 209. So a long run of field stores is one free group, then a barrier, then a second free
  group: retail's order can show a "chain" there that no alias rule explains.
- **What it means for source changes.** Adding or removing a memory reference before the flush
  point (a field read twice, a store split, a Scalar slot, an asm's memory operand) moves the
  barrier to another store. tools/sched1.py replays the links the dump prints, so it already
  follows the barrier of the compiled form; a form with another count needs a new compile.
- **Not the wall of the missing-dependence near misses.** Counting each block of the pre-sched
  RTL (`.regmove`) and of the reloaded RTL (`.greg`) for func_001D5FA8, func_001D60B0,
  func_001D61C8, func_001930B8, func_001549C8, func_001A1030, func_001C54D0, func_0013BE18,
  func_0014F168 and func_00144540, the most pending references before any store is 12, 14, 12,
  12, 12, 24, 19, 8, 10 and 28 (29 after reload): none reaches the flush. (The static records'
  FillMemory call resets the count, so their eleven to fourteen stores are far below it.)

### Invisible instructions: what the lives the allocators rank are counted over (w25, unsolved walls)

Several walls need a life or a priority a little longer than ours with retail's code unchanged
(func_001DEBE8's &cur, func_00109488's 2194, the sched1 ties of func_00142278 and
func_0017ECE8), as if retail had insns that left no code. Read from GCC 2.95.3's source and the
`-dr ... -dS -dl -dg` dumps of all six (2026-11-11):

- **The lengths are sched1's, the references flow's.** After sched1, haifa-sched.c's
  update_reg_usage overwrites REG_LIVE_LENGTH with find_post_sched_live's count: every insn
  (class `i`) of each block, in sched1's order, while the register is live. REG_N_REFS is not
  recounted (flow's, before combine). So global.c's `floor_log2(refs) * refs / length` and
  local-alloc see every insn of sched1's output, whether or not it reaches the code.
- **What reaches sched1 and leaves no code.** In the six functions' dumps: (1) flow's
  `(use (const_int 0))` after a call that ends a block (gcse.md, "The nop"); (2) the copy at the
  join of an inline's result set in several arms (a clamp's local: func_001D7778 insn 1416,
  func_001CC818 insn 2599), which global-alloc's copy preference puts in one register, so reload
  deletes it; (3) a copy into an argument register from a pseudo that local-alloc places in that
  register (func_001DEBE8 insns 357, `$f13` from a float variable, and 373, `a0`; three in
  func_001CC818, six in func_001D7778), or out of the return register into a pseudo placed there
  (func_001D7778 insn 1795, `$f0`); (4) GCSE's copies and those of long or looped blocks
  (loops.md; func_00109488's argument copies that survive CSE1's window flushes,
  long-block-constants.md).
- **A fifth kind, before sched1: what leaves between two passes (w35, func_00130C58).** An insn
  can also live only from one pass to a later one: a test cse1 cannot fold because a
  NOTE_INSN_LOOP_END ends its path, whose constant loop.c matches with another set of the same
  value (and so moves out of a loop it would have left), and which cse2, run after loop.c, folds
  away. And the notes of a loop that runs once leave no code but double the references flow
  counts inside them and make the insn after each note a barrier (loops.md, "The 3's second
  set"). Both were proved with a probe that is EXACT; the plain source is not found.
- **Inline parameter and return copies are not among them.** integrate.c copies each argument
  of a parameter not declared const into a new pseudo, and each inline's return value goes
  through its own; in straight-line code cse1 and combine remove them before flow counts
  anything. func_00142278's .rtl has 26 pseudo-to-pseudo SF and TI copies, its .cse 2, its
  .combine none; side's dot written over `Vu0::Vec` values (`Vu0::Dot(Vu0::Vec::Of(ca),
  Vu0::Vec::Of(n))`, the by-value struct copies of include/vu0.h) gives the same 26, 2 and 0 and
  the same code. Inline helpers, `const` parameters and Vec copies are therefore no lever on a
  life or a priority inside one block; only the four kinds above are.
- **The walls.** func_001DEBE8's (a) needs two such insns where &cur and &tgt are both live
  (the first key reads to the teleport arm's GetStateWalkerCurrentKey). None of the four fits
  there without changing code: the then-arm's call ends in its jump over the else, the teleport
  arm's nop (insn 1340) follows the last key read where both are dead, the region has no
  inline's result, and every argument loads straight into its register (combine's merge).
  Written as an inline predicate (`StickPushed(pad)` returning `0.7f < pad->f7C`, used by both
  stick tests), the test keeps a store-flag (`li v0,1; move v0,zero; beqz`): 1724 bytes.
  func_00142278's side conversion, func_001DEBE8's (b) and func_0017ECE8's load need a longer
  chain inside one block, where only an argument copy could be invisible, and none of those
  chains ends in a call's argument.

### Which of two sums issues first: a structure store ends a chain that a u128 store extends (func_0019ED58)

HandleEffectContact (src/main/effect.cpp) adds an impulse to the effect's velocity and its spin
after MeasurePointToSegment, then tests the velocity's z against a floor. Read from the `-dS
-dR -fsched-verbose-6` dumps and alias.c (w40-fc, 2026-11-12):

- **The chain behind each sum decides the order.** The velocity sum feeds its add, the store
  to qA0 and the z load the test reads (a true dependence: 168 is inside 160..175). The spin
  sum feeds its MulAddX and the store to v100. Stored through a u128 pointer (no alias flag)
  that store holds the load of the floor D_0026B54C behind it, the spin chain is as long as
  the velocity's (priority 10 each) and the later statement's sum issues first. Stored as a
  structure (`*(Vu0::Vec*)&self->v100 = ...`, MEM_IN_STRUCT_P at a varying address) it cannot
  alias a scalar at a fixed address (fixed_scalar_and_varying_struct_p), the spin chain ends
  at the store (priority 4) and the velocity sum issues first, as written.
- **That order frees c2.** With the velocity sum first, the weight s dies at the spin sum,
  local-alloc ties the sum's result to s (retail's vf1) and c2's quantity keeps its own 3
  references: 4 x 1 call is not below 3, so local-alloc refuses it a call-clobbered register
  and reload keeps it at 112(sp), loaded at each use. c2 is a local pseudo; it only had to
  stop being tied to the sum.
- **A scalar global against a member store.** `ShortenEffectLife(self, D_0026B550)` after
  `((Vec02*)&self->qA0)->z = D_0026B54C` loads the life before the z store only when the
  store is a member's (mem/s) and D_0026B550 a scalar float (mem/f): as an array element it
  is mem/s itself and waits. Retail's `lui; swc1; lwc1; move a0; jal` with the caller-save of
  vf8 in the delay slot is the independent form.
- 141 differing lines to 38 at retail's size. Left: sched2's order of the reloads after the
  call (retail reloads c2 into vf5 while the velocity sum's vf3 is live, ours into vf3), the
  third slot store against the MulAddX, and the first impulse's constant and slot store.

### A weight written again repeats its slot store, which takes an issue slot and leaves no code (func_0019ED58, matched)

What was left of HandleEffectContact after the section above (w44-fc, 2026-11-12), read from
the `-da -fsched-verbose-6` dumps, reload1.c's order_regs_for_reload and a replay of sched2
(tools/sched1.py's Replay on the `.sched2` trace, the dependence kinds taken from the insns'
sets and uses: it reproduces every block of the function):

- **What retail needed.** c2 is a spilled pseudo, loaded for the spin's MulXSum. Reload takes
  the first register of REG_ALLOC_ORDER that no live pseudo holds: retail's vf5 means the new
  velocity (vf3) was still live there, so in sched1's output the spin sum came after the
  velocity's add and before the store to qA0. With the weights in locals (`Vu0::Vec s`, `s2`)
  the store (priority 8) and the second weight's slot store (9) both beat the spin sum (4):
  the store issued first and reload took the freed vf3. sched2's order after the call (the
  restores of dir and d1 before the loads of qA0 and v100, c1's before the weights) followed
  from that register: the reload's `lqc2 vf5` is an output dependence on the velocity sum's
  chain, where `lqc2 vf3` hung on the store.
- **The source form.** The weights written at each use:
  `MulXSum(d1, Scalar((1 - along) * j1), dir, Scalar(along * j2))` in the velocity's statement
  and the same two Scalars again in the spin's. cse1 merges each second qmtc2 with the first,
  but each Scalar is a statement of its own slot store: the insn stream has the slot stores of
  s, s2, s again, s2 again, then k's. The repeat of s is a deleted note by the `.flow` dump
  (it is there in `.cse2`). The repeat of s2 stores what the slot holds: it stays through
  sched1 (`(insn 2211 ... (set (mem/f:TI (plus fp 48)) (reg/v:TI 795))`, priority 9) and
  reload deletes it as a no-op store (`(note 2211 ... NOTE_INSN_DELETED)` in `.greg`). In
  sched1 it takes the issue slot beside the spin sum in the cycle after the velocity's add,
  and the store to qA0 waits one cycle: velocity sum, s's slot, add, s2's slot, s2's repeat,
  spin sum, store. One more insn that leaves no code (large-functions.md's CLOBBER, loops.md's
  `(use (const_int 0))`): a value stored twice to a slot nothing reads.
- **The impulses as statements, their dot products through ToFloatMoved.** The inline
  ImpulseAlong evaluated all its arguments before its body and added insns: with the weights
  at each use PRE's expression table had 251 buckets, which numbers the hoisted frame
  addresses sp+64, sp+68, sp+16, sp+32 (bucket = (13259 + offset) mod 251 wraps between 32
  and 64) and gave s3, s4, s5 in another order than retail (gcse.md, "One reaching
  register"). Written out twice the table has 239 buckets and retail's order. The last twelve
  lines were sched2's: retail issues `sub.s` (-1 - bounce) right after the first dot product's
  `mtc1` and the product before the second dot product. ToFloat's `mtc1` is the compiler's own
  move (units memory and flop, latency 2), which blocks the `sub.s` (fmac, flop) in its cycle
  and the next move's; ToFloatMoved's is an asm (no unit, latency 1). Both dot products of
  each impulse go through ToFloatMoved.
- EXACT on US and PAL with `f32 D_0026B550 = 0.25f` (a scalar, which the life's load needs) and
  the size curve after it a Vec02, whose alignment leaves retail's twelve zero bytes.
- **The tell.** A reload register one higher than the first free one, or a store that retail
  issues one cycle late with nothing in the gap: look for a weight (or any Scalar) the near
  miss named in a local and used twice, and write it at each use.

### A weight written again in the next statement, and the rows read before a later store (func_00144540, matched)

UpdateCameraMatrices (src/main/camera.cpp) had two walls that earlier passes read as one alias
fact: the product's rows `0x10(s0)`, `0x20(s0)` loaded before corner's store, and the weight in
vf5. Read from the `-da -fsched-verbose-6` dumps and the replay (w46-c, 2026-11-13):

- **The rows needed no known value.** A load through a pointer of unknown base waits for every
  frame store before it in the insn stream, and every frame store after it waits for the load
  (an anti dependence, cost 1). Retail's two row loads come before corner's store, row 0
  (`0x80(s4)`, a parameter's base) long after: the loads were ahead of corner's store in the
  insn stream, so the store's priority (17) passed to them (18) and left row 0 at its own (11).
  The source order is the product first and corner after it. No REG_EQUAL note is involved;
  the same reading applies wherever a row load "must not wait" for a store: ask first whether
  the store was written after the load.
- **corner after the product kept the dead row store only because of its slot.** flow1 deletes
  the product's `r.r[2]` store when the next store to that slot (0xB0) follows with no load
  through a pseudo address between. A Scalar's slot is the first free one when its statement
  is expanded: with `Vec02 tilt; Mat4 proj;` declared before corner's statement they take
  0x60 and 0x70, and corner's Scalar gets 0xB0 right after the product (its vector loads are
  expanded after the slot store, as an inline's by-value memory arguments are). Declared after
  corner's statement, the Scalar takes 0x60 and the row store stays (780 bytes).
- **The weight at each use.** `Vu0::Scalar(swing)` in pos, dir, corner and tilt: cse1 merges
  the four `qmtc2`, and each Scalar stores its slot. The `.sched` dump has four slot stores,
  two to 0x50 (insns 193 and 254, priorities 24 and 23) and two to 0xB0 (493 and 556, 6 and
  5): the repeat depends on the first (an output dependence), so the first outranks the other
  stores of its group and issues ahead of them, where retail has `sqc2 vf5,80(sp)` before the
  stores of pos and dir and `sqc2 vf5,176(sp)` before the product's. Both repeats are in
  `.lreg` and gone in `.greg` (reload deletes a store of what the slot holds). With the weight
  in a named local the slot store ties with the others and loses on register weight (it is
  not the weight's death): it came last, and local-alloc gave the weight vf7.
- A grid over the four uses (named or in place) and the place of corner's declaration: EXACT
  with all four in place and corner, tilt and proj declared together after the product (and
  with corner declared before the product, or pos on a named weight). PAL's projection uses
  256 where US has 224 (src/versions/eu/main/camera/func_00144540.cpp).

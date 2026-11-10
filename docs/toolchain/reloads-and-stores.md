<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Reloads and stores

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

- **func_00187260.** One `madd` in a loop preheader (a strength-reduced address, loops.md, "A
  pointer set in an inner loop too is no giv of the outer loop") made a1 a spill register and
  shifted every qmfc2 temporary of the function's first loop, 1,400 bytes before it.

### Which dot reaches a GPR through local-alloc (func_001BC978)

Read from the `-dS -dl -dg -fsched-verbose-6` dumps (2026-11-10, w15):

- **A TI_REGS pseudo takes a GPR unless it has a suggestion.** A Dot whose result only feeds
  ToFloatMoved (asm "=j" out, "r" in) costs the same in GPRs and VU0 registers, so regclass
  gives it TI_REGS (`TI_REGS or none` in .lreg). local-alloc tries the suggested registers
  first: d's dot (r368), whose input rn dies in the asm, takes rn's vf1, and its qmfc2 is then
  the mtc1 asm's input reload (v0, reload's turn). offsetSq's dot (r393) has none (the offset
  lives on to ro's Rotate), and the register order gives it v0 itself; retail's v1 is what
  reload's round robin (above) would give a second qmfc2 reload after d's v0, i.e. offsetSq's
  dot in a VU0 register. Neither the conversion helper (ToFloat gives v1 but its mtc1 has the
  compiler's latency and moves), the member read inside the expression (o->mass) nor
  ToFloatViaBits gives it.


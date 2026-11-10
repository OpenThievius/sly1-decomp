<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Conditional moves (jump.c)

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

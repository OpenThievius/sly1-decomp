<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Shapes of large functions

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
- **A fallback's address in the block before the test.** Where retail forms a
  fallback vector's address (`lui; addiu`) among the length's VU0 code and
  only its `lq` in the short arm, the source named the address first: `const
  Vec02* fb = &g_unitXVector;` before the length, then `dir = *fb;` in the
  arm. The pointer is a pseudo set where it is written, so its two insns stay
  in the earlier block and sched1 puts the `lui` first; `dir =
  g_unitXVector;` expands the address inside the arm (func_001DF700, as
  func_0016D490 does with its `fb`).
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
- **Constructor stores kept in source order (solved 2026-11-12: see "A brace initialiser's
  union member is a CLOBBER" below, for the five ring records and
  func_001930B8).** In func_001D5FA8,
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
  - **What retail's sched1 order must have been (func_0018A510, 2026-11-09,
    `-dS -dl -fsched-verbose-6`, alias.c read).** In sched2 the two stores
    through a `%lo` address (the field at offset 0, `sw v1,%lo(cfg)(s2)`,
    and the guard) are barriers for every store through s0, so retail's
    sched1 put out the stores as A = {f4, f24, f44, f34}, then i0, then
    B = {f8, i28, i48, i68}, then the guard, then C = {f50, f60, f64, f54}
    (each group's inner order free). func_001D5FA8 has the same shape
    without an i0: its guard also splits off {f50, f60, f54}, the last
    stores of the constructor. Here, before reload, the constructor's
    `this` is one pseudo set once from `(lo_sum hi cfg)`, and CSE gives that
    set a REG_EQUAL of the symbol, so init_alias_analysis knows its value:
    i0's `(lo_sum hi cfg)` (combine folds offset 0) and every `this+N` are
    told apart, and nothing orders the stores. Probes (not plain C) that
    take the pointer's value away show what each property does:
    - pointer with no base at all (an empty asm on it): i0 and the guard
      both conflict with every store, so A comes out right (all four
      constants loaded first, 1.0 into 5.0's f2 after f4's store, retail's
      f0-f3), but the guard is last;
    - pointer with cfg as base but no known value (`this + off`, off from
      an asm): i0 alone conflicts, A and the late loads come out as retail
      has them (100 and 50 swap f0/f1), and after i0 the stores sort by
      INSN_REG_WEIGHT, so the guard (two deaths) goes second, not after B;
    - every field volatile, in retail's group order: one chain, the guard
      last, and the first loads interleaved with the first stores.
    So retail needs the stores before the guard chained (or otherwise
    given priority) and the C stores free, with i0 a barrier after A; no
    form tried gives that, and the plain forms all give `this` a known
    value. Also ruled out: one variable reused for 5.0/1.0, 100/75 and
    50/-100 (retail's register pairs; the anti-dependences pull 5.0's
    store first and push 0.5 late), and a zeroing base class with
    sub-records whose constructors set the colours (an empty base shifts
    the fields).
  - **The guard's place and the late constant, reproduced; the order inside
    the groups is not a weight sort (func_001D61C8, 2026-11-09).** g++
    2.95's expand_static_init (cp/decl.c) always emits `guard = 1` after
    the whole constructor, so in the RTL the guard store is the last store.
    A probe (not plain C: an explicit guard, the record through a pointer
    hidden by an empty asm, `guard = 1` written between i68 and f50) gives
    retail's guard position, 25.0 loaded after i48 into -100.0's f0, and
    retail's first four loads (18 words differ, against 21). What is left
    is the order inside the groups: sched1 sorts the free stores of a
    group by INSN_REG_WEIGHT, and sched2 keeps that order. Retail's group
    before the guard is f44, f4, f40, f8, i28, f34, i48, i68, which no
    source order gives as a weight sort: -1 (`lui; ori` into one pseudo,
    stored by i48 and i68) dies at whichever of the two comes last, giving
    it weight -1, so it sorts ahead of f8, i28 and f34 (weight 0). So in
    retail's sched1 the stores of that group were not all ready at once
    with equal priority: they had dependences (or sat in separate blocks)
    that this compiler only gives with volatile. Two further mechanisms
    checked and ruled out as the source of the late loads: local-alloc's
    update_equiv_regs moves a constant's set next to its single use only
    for a pseudo live across blocks (`REG_BASIC_BLOCK < 0`), and a pseudo
    set twice from `(lo_sum hi cfg)` loses its base (alias.c, record_set),
    which makes the guard conflict with the stores but needs a variable
    the original would not have reassigned.
  - **What retail's order needs, in sched1's priorities (static-record
    research, 2026-11-10, all four static records, func_001EC190 and
    func_001930B8; `-dS -fsched-verbose-6`, haifa-sched.c and mips.h
    read).** A float constant's set is a memory-unit insn of cost 2; a
    store with no dependent has priority 2, so its constant has 4. An
    output or anti link costs 1 (mips.h's ADJUST_COST zeroes it and
    insn_cost raises it to 1). In every case retail loads a constant only
    after some earlier stores (1.0, 75 and -100 after f4, f24 and f44 in
    func_0018A510; 75 after i48 in func_001D5FA8; -1.0 after -0.5's store
    in func_001930B8, whose constants reuse $f0 as local-alloc can only
    give them that way): a ready constant of priority 4 waits behind a
    store only if the store has priority 4 or more, which needs a chain of
    two links after it (store, then something of priority 3, then
    something of 2). Ties at equal priority go to the smaller
    INSN_REG_WEIGHT, which counts every SET (stores too) as +1 and each
    REG_DEAD or REG_UNUSED note as -1, then to the earlier insn. Stores
    through one pointer whose value alias.c knows have no dependents at
    all, so every plain form tried gives all constants first.
  - **The guard needs more than a conflict.** A probe (not plain C) with
    func_0018A510's A and B stores through a copy of `this` hidden by an
    empty asm (no base) and C through `this` gives retail's three groups
    A, i0, B and retail's late loads (A has priority 5 through i0, B 3
    through C). The guard then still lands after f54, not before C: the
    last C store in RTL order is where `this` and 1.0 die (weight 1 - 2),
    which ties the guard's (its 1 and its `%hi` die) and wins on the
    earlier insn. So retail's guard ahead of C also needs the last C store
    to kill one register fewer, or C not yet ready when the guard is.
  - **Ruled out tonight (all give the base's fully independent stores).**
    The record as sub-records (`Entry e1, e2, e3` members, fields
    through `e1.f4`); C's two pairs set by an inline `Pair::Set(x, y)` on
    members; the static inside an inline accessor
    (`inline Cfg* GetCfg() { static Cfg cfg; return &cfg; }`, its guard
    and record unchanged); a reference bound to the static. In each, an
    inline call's `this` is substituted as `(plus this N)` (integrate.c
    copies a non-readonly parameter into a pseudo, CSE folds it back), so
    one pseudo with a known value addresses every store. In a block with
    no call or branch the only plain sources of a store's dependents are
    a memory conflict (a base or value alias.c cannot see) and a register
    reused after the store (a reassigned variable, or a PRE copy such as
    the `(set r149 r149)` of `%hi(cfg)` GCSE leaves in the init block,
    which gives i0 one anti link of cost 1, too short). func_001930B8 has
    the same requirement on frame stores, so the missing form is common
    to the file-scope initialiser and the function-local statics.

  - **func_001930B8, the static initialiser (2026-11-10, `-dS -dl -dg`,
    local-alloc.c read).** Its two records go to a stack temporary that a
    `movstrsi` loop copies to the global, so every store is frame-relative
    and sched2 is free to reorder them; only the registers carry sched1's
    order. Retail has -0.5 (f20) and -1.0 (f74) both in $f0, and 1000,
    1200, -1750, 0.5, 2.0, 1.0 in $f5, $f2, $f1, $f3, $f4, $f6. Read
    backwards through local-alloc (QTY_CMP_PRI, ties by qty number, the
    fake birth and death one insn wider when sched2 runs), that needs
    -0.5's store before -1.0's load in sched1's output, and -1750's life
    shorter than 1200's, 1200's than 0.5's and 2.0's, and 1000's the
    longest of the single-use constants. In sched1 every constant load
    (priority 4) outranks every store (2), so with independent stores no
    source order can give it. A 40-line emulator of the allocation
    (build/swarm/w10-1930B8/emu.py, rsearch.py in the g7 worktree)
    confirms both directions: sampled schedules with -0.5 stored first and
    -1.0 loaded after it reproduce retail's eight registers, and none
    where all loads lead.
    - **One variable for -0.5 and -1.0 cannot be it.** Reusing it gives
      the anti-dependence that makes sched1 store -0.5 first and load
      -1.0 late (retail's instruction order but for f8, 26 lines differ
      against 33), but the variable then has two deaths, so global-alloc
      places it after local-alloc has given $f0 to a constant live across
      it ($f6 here). The emulator with the variable global finds no
      schedule at all that gives retail's registers.
    - **Written as the file's real static initialiser** (inline functions
      returning each record by value, `static Blk05 D_00604700 = MakeA();`,
      checked against the generated `__static_initialization_and_destruction_0`)
      the code is the near miss's exactly: the first record exact, the same
      34 lines in the second. An aggregate initialiser instead stores the
      fields straight into the globals (no temporary, no copy loop): not
      retail's form.
    - **A compound literal is the plausible form of the records (wave 15,
      2026-11-10).** `D_00604700 = (Cfg_1930B8){ ..., D_00248D30 };` and
      the same for D_00269C10, with no FillMemory call written:
      expand_assignment expands the global's address first (so it is in
      s0 before the call, which the near miss gets only by declaring the
      pointer before the memset), store_constructor clears the temporary
      with the compiler's own memset call (FillMemory is memset) and
      stores the non-zero fields in field order, and the struct copy is
      the `movstrsi` loop. The first record is exact and the second has
      the near miss's differences (34 lines against 33: 1200 and -1750
      swap $f0/$f2). Retail's loads after the first two (1000, 1200,
      -1750, 0.5, 2.0, -1.0) are in field order too, which fits an
      initialiser.
    - **What the registers need, read again.** Retail's locals avoid $f0
      altogether (-1750 has the shortest life and still takes $f1), so
      $f0 went to a quantity that local-alloc ranked first: -0.5 and
      -1.0 as one local quantity (four references, so
      `floor_log2(4) * 4` against 2 for the single-use constants). With
      the reused variable and the fields in offset order (26 lines), the
      emulator (build/swarm/w15-1930B8/emu2.py in the g6 worktree, the
      variable as one quantity) gives that quantity $f0 and 1.0 $f6, as
      retail; the other five still come out f1-f5 in load order where
      retail has -1750, 1200, 0.5, 2.0, 1000, so their stores also run
      in a different order. A pseudo with two values is a local quantity
      only if `REG_N_DEATHS` is 1 (local-alloc.c), and a variable stored
      twice dies twice. The only code in 2.95.3 that takes a death away
      from a pseudo with several values is regmove's
      `optimize_reg_copy_2` (`d = s` where s dies, d modified, `s = d`
      where d dies: d is renamed s and both lose a death), and combine's
      note bookkeeping; CSE removes such copies before regmove sees them
      in every plain form tried. Not found: the source of the anti-link
      from -0.5's store to -1.0's load with -0.5 and -1.0 in separate
      pseudos.
    - **Ruled out in wave 15:** a 16-byte vector field whose type is
      BLKmode (a struct of a 12-byte struct and a float, or of an array):
      a 16-aligned 16-byte copy is TImode pieces (`lq`/`sq`), never a
      BLKmode move whose unknown size would conflict with the frame
      stores; `-c.f70` for -1.0 (CSE does not fold the negation: a
      `neg.s` stays); `c.f20 + c.f20` or `k *= 2.0f` (folded to the
      constant, same code as the literal); loop notes around the first
      stores (a `do { } while (0)` probe: a barrier in sched2 as well,
      which retail's `lq` before -0.5's store rules out).
  - **Dependence sources enumerated (w25, 2026-11-11, haifa-sched.c, alias.c,
    integrate.c, cp/decl.c and reload1.c read).** In one block with no call
    after the stores, a store gets a dependent only from: a later insn that
    sets a register it reads (a reassigned variable, or GCSE's `(set r r)`
    self-copy, an alu insn of priority 1, which adds nothing to a store's own
    2); a later memory reference alias.c cannot separate (a base pseudo with
    no known value: loaded from memory, a call's result, set twice); the
    pending-list flush at the 33rd memory reference (sched1.md, "The 33rd
    memory reference of a block is a barrier": these blocks peak at 12-14);
    a barrier (volatile asm, loop or EH note); add_branch_dependences, which
    links every insn without a dependent to a block-ending jump, call or USE
    (a uniform +1 that reorders nothing, and the init block falls through);
    and sched_before_next_call, which needs a call later in the block. For a
    function-local static `this` is a constant with a REG_EQUAL note, so
    canon_rtx resolves every address, also those that keep an inline
    member's own `this` pseudo (`(plus r c)` is never folded by
    find_best_addr, but its set gets the folded constant as REG_EQUAL).
  - **The guard cannot be raised.** With tools/sched1.py on func_001D5FA8,
    the A∪B stores at priority 4 (their constants 6) and the guard at 3
    give retail's groups (A, the late 75.0, the guard, then f50/f60/f54).
    A guard of priority 3 needs a dependent after `guard = 1` in the block,
    and expand_static_init emits after it only the cleanups of the
    initialiser's temporaries and, for a type with a destructor, the
    atexit call: both would be calls retail does not have. So retail held
    the C stores back instead of raising the guard.
  - **A hidden second constant is possible.** reload_cse_regs (after
    reload, before sched2) deletes a set of a hard register to a constant
    it already holds (reload_cse_noop_set_p). Two 1.0 pseudos that
    local-alloc puts in the same FPR therefore leave one `lui; mtc1` in
    retail's code. With C's 1.0 a pseudo of its own (probe: 1.0000001f for
    f60/f54) and A∪B at priority 5, the replay loads C's 1.0 and 75.0
    after every A∪B store and issues the guard before f50 and f60; only
    f54 still precedes it (C's 1.0, two dependents against 75.0's one, is
    loaded first, and f54 then ties the guard's weight and wins on LUID):
    retail's group order is one tie away. What
    gives A∪B priority 5 and keeps C's constants apart from A's (CSE merges
    equal constants in one extended block) is still not found.
  - **Ruled out (w25).** The record as a base class holding every field,
    its constructor setting A∪B after FillMemory and a derived class's
    constructor setting f50/f60/f54: the same code (21 lines, as the near
    miss): the base constructor's `this` is the derived one's register.
  - **The tie is the statement order of C; the second constant is not
    needed (w26, 2026-11-11, tools/sched1.py, haifa-sched.c, alias.c and
    toplev.c read).** With C written `f60 = 1.0f; f54 = 1.0f; f50 = 75.0f;`
    (f50 last), A∪B at priority 5 (their constants at 7) replays to the
    stores of A∪B, then 75.0, the guard, f50, f54, f60, with *one* 1.0
    pseudo for A and C: f50 is the store where `this` and 75.0 die, and it
    is not ready until two cycles after 75.0's load, so when the guard's
    `li` has issued the ready C stores are f54 (1.0 dies, weight 0) and f60
    (+1) against the guard's -1. The same order follows from the near
    miss's C order when `this` does not die at f54 (its REG_DEAD note
    removed from the dump). So retail's groups need only A∪B at priority 5
    and that C order; with A∪B at 4, 75.0 still comes before f8. In
    func_001D60B0 a uniform raise is not enough: with A, i0 and B all at 5
    the replay issues f8 and i68 before i0; A and i0 at 6 and B at 5 give
    A, i0, B, i.e. the chain A → i0 → B that a base with no known value
    gives (2026-11-09 probe), not a raise of the whole group.
  - **What cannot be the source (w26).** No pass between sched1 and sched2
    merges blocks or deletes labels (toplev.c: local_alloc, global_alloc
    with reload, reload_cse_regs, rebuild_jump_labels, the splits, then
    sched2's own find_basic_blocks), so C was not a block of its own in
    sched1. sched_analyze's remaining sources of a link are a call-used
    hard register (an anti link to the last call), a pseudo with a
    REG_EQUIV of a MEM (only the address is analysed, not the memory),
    CLOBBERs, TRAP_IF and asm; none occurs in these blocks. A pseudo set
    twice from `(lo_sum hi cfg)` loses its base (record_set), which makes
    the guard conflict with C as well, so the guard comes last.
  - **Screened (w26, all compiled with the replay; 21 lines unless
    noted).** C's 1.0 as `f60 = f54 = f8` (20 lines: the chained store
    order only), a `static const f32` member, a `double` literal, a static
    inline returning 1.0f, an enumerator: each is one 1.0 pseudo after CSE
    with the same order. -100.0 and 75.0 in one variable with C reordered:
    22 lines (75.0 then follows f44 at once). The record as a POD with an
    aggregate initialiser holding a non-constant element (dynamic
    initialisation through store_constructor, guarded): constants first
    as before, and store_constructor skips i28's zero, where retail stores
    `sw zero,40(s0)`, so the original assigned the fields (40 lines).

### A brace initialiser's union member is a CLOBBER (the ring records, matched 2026-11-12)

(Also the two FLT_MAX bound vectors of func_0013A618 and func_0013A940, 2026-11-12, w40-fb:
written as brace-initialised `Quadratic16` locals their prologues are retail's; see
docs/toolchain/sched1.md, "Two literal %hi's issued in one cycle". A wall of the form "two
constants' `%hi`s issue in one cycle" or "one object's stores come out interleaved with
another's" is this one when the objects are constant-initialised vectors.)

func_001D5FA8, func_001D60B0, func_001D61C8, func_0018A510 and func_001EC190 (w37-f3) match
as `static RingParams params = { ... };` (include/ring_params.h): the records are brace
initialisers, and the dependence between their stores is a union member's CLOBBER. What was
established, in the order it was found (haifa-sched.c, alias.c, expr.c, cp/typeck2.c,
cp/semantics.c and cp/decl.c read; `-dr -dN -dS -dR -fsched-verbose-6` dumps):

- **The source order is the declaration order.** Read back through sched2 (after reload a
  constant load and a store of equal priority keep sched1's order, and an FPR reused by a later
  constant raises its first store's priority by one anti link), retail's sched1 output is: the
  first constants; the stores up to row 1's colour (0x48), those whose constant dies first, then
  the others in offset order; the constants of row 2; row 2's colour (0x68); the guard; row 2's
  other stores, the dying ones first (f50, f60, [f64], f54). Every tie in it is INSN_REG_WEIGHT
  and then LUID with the fields in *offset* order, so the "source order" of the near misses
  (f44, f4, f40, ...) was the scheduler's, not the programmer's.
- **One insn splits the block.** With the fields in offset order, tools/sched1.py reproduces
  that output when one insn D sits between the store at 0x48 and the store at 0x50, every
  earlier store links to D and D links to every later store (build/swarm/w37-f3/h2.py: the
  stores before D get priority 4, the same as row 2's constants, and win the tie on weight or
  LUID; after D the colour at 0x68, where the base and the colour die, ties the guard's weight
  -1 and wins on LUID). D emits no code, does not hold the constants in sched2 (`li v1,1` for
  the guard and the loads of row 2's constants cross its place there) and does not conflict with
  the guard in sched1: it is a memory reference of unknown size on the record's own symbol.
- **D is `(clobber (mem/s:BLK (plus this 80)))`.** expr.c's store_constructor emits a CLOBBER of
  its target ("the whole union value is dead") for every UNION_TYPE constructor; for a record it
  does so only when the constructor has as many elements as the type has TYPE_FIELDS, which a
  C++ class never has (cp/semantics.c's build_self_reference adds the class's own TYPE_DECL to
  TYPE_FIELDS), and for an array only when the enclosing object was not cleared. A BLKmode MEM
  has size 0, so alias.c's memrefs_conflict_p reports a conflict with every reference to the
  same symbol at any offset, and base_alias_check still separates it from the guard's symbol. A
  CLOBBER emits nothing, and reload deletes every CLOBBER insn when it is done (reload1.c: the
  `.lreg` dump still has it, `.greg` and `.sched2` do not), so sched2 never sees it: there the
  stores through s0 are held only by the guard's store and the constants move freely, as
  retail's do.
- **A brace initialiser gives the rest.** g++ expands `static T x = { ... };` at run time,
  behind the guard, when T needs constructing or an element is not a constant (typeck2.c's
  store_init_value returns the initialiser for a TYPE_NEEDS_CONSTRUCTING type, and an aggregate
  with a member that has a constructor is one). store_constructor then clears the whole record
  with the compiler's own memset call (config/us/libcalls.tsv: FillMemory) because a C++
  constructor never lists as many elements as TYPE_FIELDS, stores the non-zero members in
  declaration order straight into the static, and skips a zero member (is_zeros_p) unless it is
  a constructor call: func_001D5FA8's and func_001D61C8's `sw zero,40(s0)` is row 0's colour,
  built by its constructor from 0. A zero union member is skipped before its CLOBBER, so only
  row 2's first float (75, 25) has one; rows 0 and 1 leave theirs zero. A union over the whole
  vector is ruled out (row 1's y is not zero: its CLOBBER at 0x30 would hold f4 and f8 before
  f44, which retail stores first; compiled, 32 lines differ).
- **The colour only has to be a call.** Compiled: a POD colour with a constant initialiser makes
  the whole initialiser constant and the record static data (no guard, no init block); a colour
  with a constructor (include/ring_params.h's RingColor, the form landed: the reader copies the
  colour as four unaligned bytes and the initialiser stores it as one word) and a POD colour
  returned by an inline function are both EXACT, since either makes the initialiser run at run
  time and stores its zero. The union may likewise have other members than the one written; only
  its place (a row's first float) and its being a union are retail's.
- **Ruled out on the way.** Compiled or replayed: a nested struct or array constructor (no
  CLOBBER inside a cleared record: build/swarm/w37-f3/v2.cpp, v5.cpp); a union over the whole
  vector (above); the hidden insn placed before row 2's colour instead (the colour then follows
  the guard). Reasoned from the source only: a loop note between the groups (a barrier in sched2
  as well, where retail's `li v1,1` and row 2's constants cross it); a second set of `this` (a
  self copy loses the base in alias.c's record_set, so the guard would follow every store; an
  increment keeps the base but emits an `addiu`); update_equiv_regs moving a constant's set next
  to its use (needs a pseudo used in two blocks).
- **Spot it:** a record cleared by a memset call and filled with constants in one block, whose
  stores come out in two groups with the second group's constants loaded late: a brace
  initialiser with a union member at the first offset of the second group.
- **func_001930B8, the file-scope records (matched the same day).** switched_collider.cpp's
  static initialiser is the compiler's own, made from `static Blk05 D_00604700 = { ... };` and
  `Blk05 D_00269C10 = { ... };` (config/us/generated.tsv names it and its `_GLOBAL_$I$`). A
  vector member copied from a global (`*(Quad16*)&g_unitZVector`) is not safe to store straight
  into the target (expr.c's safe_from_p: an INDIRECT_REF against a MEM), so each record is built
  in a stack temporary and copied, as retail's are. Which members are unions was read off
  retail's registers by compiling every choice (build/swarm/w37-f3/svar.py: the constants' FPRs
  and the order of loads and stores, 8 of 8 only with the vectors at 0x00 and 0x70, or with 0x10
  as well, whose first float is zero): the CLOBBER before 0x70 holds its two stores (1.0, -1.0)
  behind every other store, so -1.0 is loaded after -0.5 is stored and takes its $f0, and the
  one before 0x00 gives the first vector's constants their lives. The vectors at 0x20 (-0.5) and
  0x50 (0.5, 2.0) have a non-zero first float and no CLOBBER: they are plain (with either as a
  union, 1 to 3 of 8).
- **func_001549C8, two function-local statics built the same way.** Its vectors and its spawn
  block (the same Blk05, with 750, 750, 1.0 and 1.0, 0, -1.0 in the two Quadratic16s) are
  `static` brace initialisers behind two guards, each through a temporary; the CLOBBER at 0x70
  is what held f70 and f78 behind the other stores (docs/toolchain/alias-classes.md, "A constant
  set in an earlier block and used once").
- **A local is the same (func_001A1030).** `Quadratic16 a = { 125.0f, -25.0f, 0.0f };` on the
  stack is cleared with one `sq` and gets the same `(clobber (mem/s:BLK slot))` before its first
  float's store; two such locals in a row order their frame stores as retail's emitter has them
  (docs/toolchain/sched1.md, "Two equal clears that retail issues apart"). The type is shared: a
  quadratic's coefficients (include/shapes.h's Quadratic16), which the ring's rows and the spawn
  block's first and last vectors are too.
- **A CLOBBER raises the stores before it to the constants' priority (func_00156288, matched
  2026-11-12, w40-fa).** The splash's burst block is the same Blk05 as a local, with the
  gravity (0x10) and the up vector (0x30) copied from memory and two angles at 0x44 and 0x48.
  Retail stores the up vector before the gravity. With plain floats at 0x40 both stores have
  priority 4 (store, the CLOBBER at 0x70, its two stores) against 6 for the loads of the
  block's single-use constants, so both wait until every constant is loaded, are then both
  ready, and go in LUID order: gravity first. With 0x44 (or 0x48) a union's member there is a
  second `(clobber (mem/s:BLK (plus at 0x104)))` before the angles' stores, every earlier
  store links to it and it links to the CLOBBER at 0x70: the two vector stores rise to 6, the
  constants' own priority, and the first of them that is ready takes the memory unit ahead of
  the constants still to load (LUID). That is the up vector's: its load issued one cycle before
  the gravity's, which waits two cycles for the last store before it (the world pointer is
  loaded from memory, no base). `-dS -fsched-verbose-6`: `521 r224=[r222]` at 21, `515
  r221=[r220+0x1ee0]` at 22, `523 [$1+0xf0]=r224` at 23, `517 [$1+0xd0]=r221` at 24, then the
  1.047 and 5.0 loads. The registers do not change. Read it backwards: two stores that tie
  on priority and weight but come out in ready order, ahead of constant loads that outrank
  them, have a CLOBBER between them and the next group. Which of the two angles is the union's
  member cannot be told (both are EXACT; include/switched_collider.h keeps 0x44); a union over
  the whole group at 0x40 is ruled out (79 lines).
- **Where the guard puts the data.** The compiler writes a static's guard out with its function,
  so a file's globals that retail has after the guard are defined after the function
  (gauge_agent.cpp's D_002649B0 on, warp_menu.cpp's D_00275DB8 on, declared `extern` above for
  the functions that use them earlier), and the record's address is the file's `.bss` entry in
  config/us/files.tsv.

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
- **Open: constructor stores kept in source order.** In func_001D5FA8,
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

<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Stack slots

### An inline function's frame is one temporary of its saved size (func_00125138)

How the frame's locals get their offsets (function.c, stmt.c, integrate.c of GCC 2.95.3):

- **Locals are temporaries.** expand_decl gives a BLKmode or address-taken local
  `assign_temp (type, 1, 1, 1)`: a temp slot kept until its block ends, then free for
  reuse. assign_stack_temp_for_type reuses a free slot only of the same machine mode, with
  room enough; a bigger BLKmode slot is split. Strict aliasing is off in SN's 2.95.3 (an
  inline's frame slot, alias set 0, is reused by the next call's), so the alias set never
  blocks reuse. The frame grows upward from 0 in allocation order (MIPS does not define
  FRAME_GROWS_DOWNWARD).
- **Vec02 is BLKmode, Vu0::Vec is TImode.** Vec02's `aligned(16)` comes after layout chose
  BLKmode for four floats at 4-byte alignment; Vu0::Vec has a u128 member. A Vec02 declared
  after a block can therefore take part of an earlier BLKmode slot (an inline's frame); a
  Vu0::Vec whose address is taken never can, and gets a new 16-byte slot at the frame's end.
- **An inline call's frame is one BLKmode temporary of DECL_FRAME_SIZE.** rest_of_compilation
  saves an inline function's RTL straight after RTL generation, with its frame size then
  (save_for_inline_nocopy, DECL_FRAME_SIZE). At each call copy_rtx_and_substitute gives the
  first reference to virtual_stack_vars `assign_stack_temp (BLKmode, size, 1)`: all of the
  inline's locals move together, at their own offsets, and every call in a later block reuses
  the slot. So the frame shows the inline's own locals, used or not: an unused local
  declared in the inline still takes its bytes in every call's copy of the frame.
- **No unused 16-byte slot from the caller.** An unused BLKmode local in a block after the
  inline's block splits the free slot (no new bytes); one at the function's top is allocated
  first, at 0, and moves everything up; a scalar that purge_addressof puts on the stack comes
  last but has accesses.

func_00125138 (ComputePlacedObjectWorldFrame): retail's locals are 112 bytes, the product's
x, y, z at 0, 0x10, 0x20 and its matrix at 0x30..0x60, then 16 bytes nothing touches; the
direction (a Vec02 at 0) and Scalar's slot (0x10) of the later block reuse the product's slot.
The other rotation products' frames are 96 bytes. A Vec02 declared after the matrix in this
product's inline (its fourth row, never set) gives a 112-byte saved frame and the function
matches. The 0x60 slot is the inline's own, not the caller's.

The same function's parent pointer: one variable assigned in both arms of the first if/else
and in the else arm is one pseudo across all three lives, which global-alloc gives a0 (r206,
the else arm's row pointer, took v1 in local-alloc first). Retail's v1 in the first arm and
a0 in the else arm are two variables: the else arm declares its own `parent`.

### A by-value inline passed to a call: the call's return slot comes first (func_001DEBE8)

From calls.c and integrate.c of GCC 2.95.3 and the frames of func_001DEBE8 (2026-11-10):

- **expand_call allocates the return temporary before it expands the arguments.** For
  `rot = MultiplyByTransposedMatrix3x3(a, RotatedRows(m, a))`, the out-of-line call's
  hidden return slot (a 48-byte BLKmode temporary) is taken first; the inline argument's
  frame (its local `t` and its named return value `out`, one BLKmode temporary of its saved
  size) is taken while the argument is expanded, after it. Retail's frame shows exactly that:
  the result at 0xE0, the inline's rows at 0x110 and 0x140, the call passed 0x110.
- **Declared locals come in the other order.** `Mat02 p, q; RotateRowsBy(&q, ...); p = q;
  Mat02 r = Multiply(..., p);` puts p and q (declared at the top) before the call's slot, so
  the result lands after them (0x140) and the out-parameter product at 0xE0: same size, wrong
  offsets. Spot it: a call's return slot below an argument's rows means the argument was an
  expression (an inline returning by value), not a local.
- The call's slot is freed at the end of the statement, so a later Vec02 (the velocity at
  0xE0) and its Scalar slots (0xF0) reuse it.

### A local's size is the frame (func_00203FD0)

Sony's 2.9-ee-991111, like SN's 2.95.3, adds nothing to the locals' area: mips.c's
compute_frame_size takes get_frame_size(), the sum of the locals' slots, and rounds it to 16.
The three other callers of StartIopDma have exactly their records' bytes below their saves
(0x10 for one record in func_0018E7C0 and func_001F9AD8, 0x20 for command_channel's
`recs[2]`). SendPadDma (src/lib/pad.c) has 0x100, with its one record at 0: its local was
256 bytes. Ruled out, with dumps of the frame (2026-11-09):

- **A variable's alignment does nothing.** expand_decl allocates a BLKmode local from its
  size and then resets DECL_ALIGN to BIGGEST_ALIGNMENT, so `PadDmaTransfer t
  __attribute__((aligned(64)))` keeps a 0x60 frame.
- **A type's alignment changes its size.** `aligned(64)` on the record's typedef makes it 64
  bytes (a 0x90 frame); `aligned(256)` gives retail's 0x150 frame and the function matches,
  but nothing in retail asks for a 256-byte-aligned DMA record (the library's own DMA words
  and request buffer are 64-aligned in .bss).
- **No temporary or inline frame.** The function has no struct value, call returning a
  struct or inline call that could leave a 0xF0-byte temporary.

What matches, and is landed: a table of sixteen records (`PadDmaTransfer transfers[16]`),
of which the first is filled and `StartIopDma(transfers, 1)` sends one, as a sender written
for a record table of fixed capacity would. The failure message is a string literal in both
places (one .rodata copy, at D_0024F738, where the near miss's named global was).

The maintainer allowed this form (2026-11-09), and its limit matters: AGENTS.md forbids a local
that exists only to size the frame. A local whose size a retail frame proves is accepted only as
an array of the real record type, passed through the callee's real interface (a pointer and a
count), with the other callers' frames showing nothing else is padded. A byte array, a scratch
array of an unrelated type, an invented wrapper type or an alignment attribute is still not
allowed.

### Best fit places a later block's locals: a 16-byte frame difference far above (func_00125C90)

assign_stack_temp_for_type takes the smallest free slot of the mode that is big enough, splits
off the rest of a BLKmode slot, and otherwise makes a new slot at the frame's end; freed
neighbours are combined at each block's end (combine_temp_slots, always at -O2). So the
offsets of a block's locals depend on how far earlier, finished blocks pushed the frame's end,
not only on their own sizes and order: with earlier blocks reaching 0x120, a block declaring
an 80-byte ScaledTransform, a 64-byte Mat4A and an 80-byte one gets 0x50, 0xA0 and a new
0x120 (0xE0..0x120 is too small), where retail had 0x50, 0xA0, 0xE0. Retail's frame reached
0x130: the earlier block's rotation product is the 112-byte inline frame of the entry above
(MulRotationIntoWorld's unset fourth row, in the same file). Read a shifted block's offsets
as "which earlier allocation was bigger", and simulate the free list before adding locals.

### A by-value result's slot is a movable; an address passed once is not (func_00125C90)

loop.c (scan_loop) deletes a movable set once and used once in a loop with a call: it
substitutes the source into the use (reg_single_usage), so a local's `&world` passed to one
call stays `addiu a0,sp,N` in the loop. A call returning a struct by value into a temporary
(`*(Mat4A*)&ct = MultiplyMatrices(a, b)`, matrix.cpp's by-value product) uses the temporary's
address twice, as the hidden first argument and for the copy, so loop.c moves it to the
preheader and it takes a saved register (retail's s7). Retail's child loop nests the products,
`MultiplyMatrices(MultiplyMatrices(*xf, inv), local)`, with const Mat4A& parameters; the
two arms' calls share one jal only when their temporaries share an offset (cross-jumping
needs the copies into ct that follow them to be identical).

Still open there: retail moves d, a spilled u128 that PlaneSigns read through a reload into
vf6, to the first call with `qmfc2 a1,$vf6`; ours reloads it (`lq a1`). The argument move
`(set a1 d)` takes movti's memory alternative, whose source class is NO_REGS, so find_reloads
makes no optional reload and inheritance never sees vf6: retail must have had a second pseudo
in vf6 for the asm and the first call. d as Vu0::Vec, as a Vec02, through Vu0::Q, and an inline
helper taking d for PlaneSigns and the call do not give it.

### A pointer field's type picks its store's partner (func_002042C8)

Read from haifa-sched.c (priority, rank_for_schedule) and the `-dS -dl -dg -fsched-verbose-6`
dumps of OpenPadPort (src/lib/pad.c, 2.9-ee-991111, 2026-11-09):

- **A store's priority is its type's next store.** In a run of stores into one struct through
  separate address computations, a store's only dependents in sched1 are the later stores of
  its own alias class (an output dependence, cost 1): different symbols (the slots, the DMA
  words, the request buffer) never conflict there, and other types never do at -O2. So a
  pointer field's store has priority 2 when no later store has its type and 1 + the next one's
  otherwise, and that priority reaches back to the load of its value (the reply's word) and the
  address it is stored through, which decides sched1's order and so local-alloc's registers.
- **sched2 sees the same chains, with longer ones after reload.** After reload the bases are
  hard registers and every int store and load of the block conflicts, so the int stores form
  one chain to the return value's load (priority 4 for the last one), while a pointer store
  still only chains to the next store of its type. The slot's last stores (the DMA id `= 0`
  and the IOP address from the reply) tie at sched2 when the address is a `u8*` like the
  buffer's (1 + the buffer store's 3); its store then goes first on insn order, two instructions off
  retail. With an `s32`, every int store and the reply's load chain together and the load is
  issued two cycles early (nine instructions differ); with `void*` the address's store is a leaf, its load
  and address lose priority in sched1 and the registers change (20 bytes differ in the best order).
- **Retail's: the type of the DMA words' pointer.** With the address field and the reply's
  word typed `u32*`, the pointer type of the DMA words that the slot also holds, the address's
  store chains to the DMA pointer's store (a leaf: priority 3, so sched1's order and registers
  are the `u8*` ones) and in sched2 it ranks below the DMA id's (4): retail's code. It is the
  natural type too: SendPadDma adds the frame's offset to that address and sends the slot's DMA
  words there. Writing the stores in any of the 5,040 orders (tools/permute.py) never reached it
  with the other types: the order was right, the types were not.

### A stack record filled by an inline: only the constant-zero store loses the pointer (func_001A7800)

Read from integrate.c (expand_inline_function, try_constants) and cse.c (find_best_addr), with
the `-dr -ds` dumps of UpdateObjectCreator (src/main/file_19E040.cpp, 2026-11-09):

- **Retail's mark.** A local profile filled with three constants and passed by address: retail
  stores the first two fields frame-relative (`swc1 $f1,16(sp)`, `sw zero,20(sp)`) and the third
  through the register that also holds the call's argument (`addiu a1,sp,16`, `move a0,a1`,
  `swc1 $f0,8(a1)`). Written `ramp.f = k;` all three are frame-relative and the argument is made
  at the call (54 bytes differ); written through `RampProfile* p = &ramp;` the second store also
  goes through the pointer, which keeps it live past the `a1 = 0` argument move and moves it to
  `$v0` (17 lines differ).
- **CSE alone never mixes them.** find_best_addr returns at once for a frame-relative address,
  so a store written on the frame keeps it. A bare pointer address `(mem p)` is replaced by its
  class's `(plus fp 16)` (equal address cost, and the tie goes to the higher rtx cost), but
  `(plus p 4)` and `(plus fp 20)` cost the same both ways, so `p->endSpeed` keeps the pointer.
- **The inliner does.** A pointer parameter whose argument is a frame address
  (FIXED_BASE_PLUS_P) gets a pseudo with that address as its constant equivalent, and so do the
  constant float arguments. try_constants then substitutes every equivalent into each copied
  insn as one change group: all or nothing. The store of `3000.0f` and of `0.2f` cannot take an
  immediate (no SFmode store of a non-zero constant), so the whole group fails and the address
  keeps the pointer pseudo too; the store of `0.0f` is a valid `sw zero` with the address
  `(plus fp 20)`, so both substitutions stay. CSE then turns the first store's bare `(mem p)`
  into `16(sp)`, which gives retail's three addresses exactly.
- **The form.** A setter on the record, `void RampProfile::Set(f32 max, f32 end, f32 time)`
  (include/ramp_profile.h), called as `ramp.Set(3000.0f, 0.0f, 0.2f);`: the original filling
  its profile with one call. A free inline taking the record by pointer or by reference matches
  too. Spot it: in a record filled with constants, a zero store frame-relative among stores
  through the record's address register means an inline call's arguments.

### One layout helper for three layouts, and what each difference was (func_001366A0)

DrawTextPanel (src/main/text_panel.cpp, matched 2026-11-10) was a near miss 72 bytes too long,
with its registers off in every block. Each difference had its own cause, found from the bytes
and the `-dr -ds -dG -dl -dg` dumps:

- **The size: an inline layout helper.** Retail rebuilds the layout's address (`addiu a0,sp,N`)
  before each of the five setter calls and passes the colour buffer from a fresh `addiu a1`.
  Written out at each layout, our `&box` stayed in a saved register (18 insns more over three
  layouts). One inline helper, `PanelLayout::Set(l, x, y, w, h, color)` (Pos, Size, the colour
  through a four-word buffer, the two words cleared; as PAL func_001316E8's ScreenLayout::Reset),
  substitutes the unchanged pointer parameter at each use ("Integration: an inline function's
  parameters and results"). The glyph's layout, whose two words are then set to 1 through the
  pointer retail keeps in v0 (`addiu v0,sp,80; sw v1,24(v0)`), takes the helper's result:
  `Layout_137228* l = PanelLayout::Set(&at, ...)`.
- **A constant colour defeats the substitution.** The glyph's call passed `0xFF808080` as a
  literal; the colour store `col.w[0] = color` cannot take that immediate, so try_constants's
  group fails for the insn and the inline frame's base pseudo stays its address; CSE then makes
  that pseudo the buffer's canonical register and it lives in s1 across the calls (retail's s1
  is the font). A variable (`s32 glyphColor = 0xFF808080;`, as the box's `grey`) keeps every
  substitution: the same mechanism as func_001A7800's record, from the other side.
- **The %hi of a pointer passed to an inline is live across the block before it.** The style's
  box (`drawBox` through the style's first word) written in place left the `lwl/lwr` copies of
  the colours (movstrsi with four scratches) choosing their scratches from {v0 .. a2}: retail
  uses a3 for several copies and a1/a0 for the style's, so a3 is one of retail's spill registers.
  The file's StyleDrawer::Draw (the inline other files use, `Draw(Font** h, out, tbl)`), called
  as `StyleDrawer::Draw(self->frame, &box, &g_gsPacketWriter)`, gives retail's `lui v0` before
  the frame word's reload and `addiu a3,v0,%lo` at the call, and with it every scratch register
  of the copies (reload's round robin, "The reload register's round robin"); 40 lines at once.
- **A two-character string from an aggregate initializer.** `char glyph[2] = { c, 0 };` builds a
  temporary and block-copies it (`sb; sb; lb; lb; sb; sb`), retail's code. A struct returned by
  an inline function (`PanelGlyph::Of(c)`) is BLKmode returned in registers by this compiler and
  packs the bytes through `and/or/dsll`; a constructor builds in place with no copy.
- **A search loop with `break`.** `for (row = 0; row < n; row++) if (shown < breaks[row]) break;`
  gives retail's copy of the count after the entry test (`move a0,v1`); the same test written as
  one `while (row < n && !(shown < breaks[row]))` keeps one register ("A search loop that leaves
  by `goto`").
- **The order of two divisions.** `start` declared before `end` loads `breaks[row]` first and
  computes `end - start` before `elapsed - start`, retail's order; the reverse order swaps both.
- **A flag set in both arms.** `s32 cursor; if (shown < total) cursor = 1; else cursor = .. & 1;`
  gives retail's v0 for both sets; `cursor = 1;` then a reassignment in an `if` gives v1.
- **A named zero for `>?`.** `f32 noScroll = 0.0f; noScroll >? (y - height)` loads the zero into
  the result's register (`mtc1 zero,$f13; max.s $f13,$f13,$f0`, retail); with the literal, the
  difference takes the result's register.
- **Constants the near miss had wrong.** The glyph's x in state 4 is 532.0 (`lui at,0x4405`), not
  533, and the cursor's string (D_00249D58) is `"&.~ffffff|"` with six f's: read both from the
  bytes (the `.word`s of a string are little-endian). The glyph's byte is a `char` (`lb` for the
  test), T217D_440::f2F8 in include/screen_element.h.

### Reading a frame's slots back to the declarations (func_0019B378)

UpdateObjectGatherer's near miss had a frame 0x10 too large, its locals in other slots, and
nine versions of the scopes had not moved them. assign_stack_temp_for_type (function.c) explains
retail's layout once its rules are applied:

- **Free slots are reused newest first, and adjacent free ones combine.** The search walks
  temp_slots from the head (the newest slot) and stops at the first free slot of the same mode,
  size and alignment; free_temp_slots and pop_temp_slots call combine_temp_slots, which merges
  adjacent free BLKmode slots, and a larger slot is split from its bottom. So a 16-byte local
  placed when 0x20 to 0x50 is free lands at 0x20, and one placed while 0x20 is still in use
  lands in the newest free slot, not the lowest.
- **A slot created last was created last.** On the R5900 the frame does not grow downward, so
  offsets follow creation order. Retail's side index at 0x40, above the weights' slot at 0x30
  that is used after it, cannot be a local placed at its declaration. It is an `s32` whose
  address is passed (FindColliderFloorContact's third argument, `s32* out`: func_001BB290
  stores the contact's side there), and purge_addressof gives it its slot after every
  temporary. The near miss's `u8 floor[0x10]` record took 0x30 at its declaration instead.
  Check a callee's real out-parameter type before giving a local a size.
- **A slot reused after a block means the block ended.** Retail's list frame of state 4 at
  0x20, the push vector's slot, shows the push vector is not live there: it is declared in each
  case's `if`, not in the switch's enclosing block.
- **The tail written twice.** Each case's push written in full (state 1 with `f614 * 0.7f`,
  state 2 with `f618 * 0.5f`) instead of a `goto` into state 2's code: jump2's cross-jumping
  merges the two tails after reload from the first insn after the lift constant, which leaves
  the `lui` of g_unitZVector in each case's own block. Retail's branch into the middle of the
  other case's block (`b .L0019B76C`, past its speed and lift) is that merge.
- **What was left.** A clamp of a cosine to 0..1 with both bounds named (`f32 lo = 0.0f;
  f32 hi = 1.0f;`): retail loads 1.0 before the first test and branches on both. And the
  position named before the weighted sum that reads it (`u128 pos = Q(act->v140);`), so its
  `lqc2` comes before the Scalar's slot store (the two-pass argument rule, func_00191570). A
  method called through desc02() rather than a cast table, and an `if (any != 0)` written in
  retail's block order, finished it.

### A block's local slot taken by a Scalar's copy; a frame address named before a call (func_00158480)

func_00158480 (TurnMatrixBySpin) went from 86.6% to a match with three changes, each read from
retail's frame offsets and registers:

- **The weight's slot is the axis's.** Retail passes ScaleMatrix's scale as `mfc1 v0; por a2,
  zero, v0` with `sq v0, 128(sp)` in the call's delay slot, and 128 is the axis that
  TransformDirectionBetweenFrames fills in the `if`. Vu0::ScalarInGpr gives the mfc1 and the
  cast's copy (its `(s128)` temporary); declared at the function's top, the axis keeps its slot
  and the copy takes a new one (a 448-byte frame). Declared inside the `if`, its assign_temp slot
  is freed at the block's end and the copy reuses it (same mode, same size): retail's 432 bytes.
  A conversion written in C (`(u128)*(s32*)&f` into the axis) extends the int and costs three
  moves.
- **Locals declared where they are first needed.** With the axis in the `if`, the frame is in
  allocation order (it grows upward): the two matrices at the top, the axis, then the three
  declared after the `if`. Retail's 144, 208, 272 for the copy, the scaled matrix and the
  product mean they are declared in that order after the block (C++ declarations mid-block).
- **`&b` at each use, no pointer variable.** A `Mat4A* p = &b;` at the top makes CSE use p in the
  branch (`move a1, s2`); writing `&turn` at each use gives retail's fresh `addiu v0, sp, 64` in
  the branch and its copy to s2 in the call's delay slot.
- **A frame address in a saved register before a call.** Retail sets `addiu s1, sp, 208` (the
  scaled matrix) before MultiplyMatrices and passes s1 to ScaleMatrix after it. Written as
  `ScaleMatrix(&scaled, ...)`, the address is computed straight into a0 after the call: sched1
  does not move a pseudo's set above a call unless the pseudo already crosses one. Retail's
  register means the source named the address before the call: `Mat4A* result = &scaled;`
  above the MultiplyMatrices line, then `ScaleMatrix(result, ...)`. Placed after the call, the
  same pointer is propagated away (one use) and changes nothing.

### Ramp copies live through a tail: a goto over function-scope locals (func_001C54D0, near miss)

func_001C54D0 (a turning collider's contact push) had a frame 16 bytes short of retail's 208,
every frame offset after the ground push wrong, and 8 bytes too many. Read from function.c
(assign_stack_temp_for_type, combine_temp_slots, free_temp_slots), stmt.c (expand_decl) and
integrate.c (the inline frame's `assign_stack_temp (BLKmode, size, 1)`), with the -dr dumps
(2026-11-10, w13):

- **Retail's offsets, as allocations.** The ground push stores its difference at 0 and its
  Scalar weight at 32 (16 untouched bytes between); the push block stores two differences at 0
  and 16 and the ramp profiles at 32 and 48; the tail stores both weights at 64; the two
  out-parameters are at 80 and 84 (purge_addressof, after every expand-time slot). Every one of
  these is BLKmode (Vec02 and an inline's frame are BLKmode, the profile union too), so a
  later BLKmode request of 16 bytes takes any free slot: the tail's weight at 64 means 0..64 is
  still in use at the tail, and the profile at 32 reusing the ground push's freed weight slot
  means it was allocated after that block ended.
- **So the profiles are function-scope and declared after the ground push.** Declared in the
  else arm of `if (zero) push = 0; else { ... }` they are freed (and combined) at the arm's end
  and the tail's weight takes 0 (ours: 192 bytes). A function-scope declaration after the inner
  `if`, with the zero-push path jumping over it (`push = 0.0f; goto apply;`, legal since the
  locals have no initializers), gives retail's 208 bytes and every offset. The 16 untouched
  bytes of the ground push are the second difference vector, declared at the top with the
  first, which the ground push reuses for its own difference (C-style scratch locals).
- **Two copies of one address: an argument read first.** Retail's `addu a0,s3,s2; move a1,a0`
  (loads through a0, the store through a1) is the address expanded inside each memory reference
  (multiplication first) with the vector read into a named `u128 v = Q(c->end[e].v10);` at the
  block's top; `ContactEnd03* end = &c->end[e]` gives `addu a0,s2,s3` and one register. The read
  first also puts the load before the weight's computation, which gives the block's VU0
  registers.
- **A store of a vector's x from a GPR of reload's choosing.** The separation stored as bits:
  Vu0::StoreX (the compiler's qmfc2, a reload into a0 after the block's pseudos) where ToBits'
  own pseudo takes v0.
- **sched2's tie between profile loads and dot loads.** With the dots written before the
  profile copies (after them, the copies' BLKmode move kills CSE's knowledge of the
  differences and they are reloaded: 8 bytes), each dot's load ranks by its chain to the first
  call: an asm mtc1 (ToFloatMoved) costs 1, the compiler's (ToFloat's reload) 2, and the
  push's division waits for the call (anti dependence on $f0). Both conversions as
  ToFloatMoved give the dot loads priority 18 against the profile loads' 19, and the profile
  loads go first as retail's do; with either ToFloat one dot load ties at 19 and wins on its
  dependents count (six against five).
- **Still open: the tail's sched1 order.** Ours loads v640 first (its Vec::Of argument is
  expanded before Rotate's rows, so its LUID is lower), then rows 2 and 1 (their address
  pseudo has no known base, so they conflict with the weight-slot stores and have four
  dependents against row 0's two), then row 0, and puts the f63C weight's qmtc2 early as
  filler. The lalloc2 emulator gives retail's VU0 registers for row 0 first, then row 2, then
  row 1 (v anywhere before row 1), with the -push weight's qmtc2 early and the f63C one after
  the dot. Row 0 has to beat v at the first cycle (rows 1 and 2 wait for the addiu of the
  matrix's address); Vec or u128 forms, RotateMembers, RotateRowsTied over the rows, v named
  first, and ScalarAtValue or ScalarAtCall for the f63C weight do not give it.

### Which induction variable loop.c keeps: combine_givs' totals (func_001575D8)

func_001575D8 adds particles to chunks of six parallel arrays (this frame's position, velocity
and record, and a copy of each for the frame before). Retail walks the record array in one
register (`s0`, the positions and velocities at -0x580 and -0x2C0 from it, and `s0` itself is
FillMemory's argument) and the copy in another (`s2`, from `addiu a2, s1, 0x840` before the
loop). Ours folded everything into one register based on the positions. The -dL dump's "Sorted
combine statistics" line says why:

- **combine_givs keeps the giv with the largest total.** Each giv's total is its own benefit
  (+1 for a zero addend, `no_const_addval`) plus, for every other giv it can absorb, that giv's
  benefit + 3. A DEST_ADDR giv (a memory reference) can be absorbed by any giv whose difference
  is a valid address; a DEST_REG giv (a pseudo) only by an identical one. Written as
  `chunk->pos[k]` everywhere, CSE makes one `k*16 + chunk` pseudo for the top of the body and,
  after the ifs' join, a second one for the copy; each absorbs the other (identical) and so
  totals 9 more than the record pointer `rec` (182 against 173): the position register wins and
  `rec` stays a register of its own (an extra spilled giv, 12 bytes).
- **One pointer per array.** `Quad16* p = &chunk->cur.pos[k]; Quad16* v = ...; Quad16* rec =
  ...;` at the top of the body, used for every access including the copy, leaves no CSE pseudo
  after the join; `rec` (benefit 10 against p's 7+1) then wins and absorbs every memory
  reference; p and v die.
- **A copy through a pointer of its own.** `ParticleState* last = &chunk->prev;` before the inner
  loop makes `last + k*16` a giv whose addend is a register, not `chunk + constant`, so it
  cannot be combined with the record's: loop.c moves `chunk + 0x840` out and reduces a second
  register, retail's s2. Written as `chunk->prev.pos[k]`, get_inner_reference folds 0x840 into
  the constant offset and the copy joins the first register.
- **`while (a && b)`, not `if (a && b) do { } while (a && b)`.** The `while` is expanded with
  its test at the top and jump.c copies the whole exit test to the bottom (retail: both tests
  at the bottom, no jump into the loop); the do-while left a `b` into the second test (4 bytes).
- **The increments' order is the bivs' order.** `i++; k++;` (the counter of the inputs first)
  puts i's givs' initialisations first in the preheader, so `i * 16` reuses the `lw v1` of the
  entry test as retail's does; `k++; i++;` reloads i.
- **`x & 0xFFFFFFFE` is `lui; ori`.** An unsigned constant above 0x7FFFFFFF is not a SMALL_INT
  here; `~1` gives `li -2`.
- **A 32-byte record taken by index.** `ParticleExtra* x = &chunk->extra[k]; x->a = ..; x->b =
  ..;` gives retail's `addu a0, a0, v0` (base first); `chunk->extra[k].a = ..` repeated costs
  8 bytes, and the byte-offset form puts the index first.

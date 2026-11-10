<!-- Part of docs/TOOLCHAIN.md, split by chapter. -->
# Constants in one very long block

func_00109488 (FillObjectPropertyTable) is 9,348 instructions of stores of
constants with no call and no branch: one basic block. How GCC 2.95 gives
such a block its registers (2026-11-08, `-dl -dg` dumps, global.c,
reload.c and reload1.c read):

- **CSE starts over every 1,001 insns** (cse_basic_block), in both passes,
  so a constant gets a new pseudo in each window (nonmatching/func_00109488.cpp
  has the landmarks).
- **sched1 runs constants ahead of their stores.** A constant's set depends
  on nothing, so the list scheduler issues it in any free slot, and the lead
  grows along the block: the 4 of entries 142-237 is set at entry 79, the 18
  of entries 656-750 at entry 235. Retail's births are the same (its `li t8,4`
  is at entry 79), so this is not where the two differ.
- **local-alloc places the pseudos by priority** (`floor_log2(refs) * refs /
  lifetime`), each in the lowest register free over its whole life; a pseudo
  it cannot place goes to global-alloc. In one long block most do: 1,865 of
  2,068 here.
- **global-alloc evicts a whole register.** When an allocno finds no free
  register, find_reg scans the registers from the end of the allocation
  order and takes the first whose local pseudos have fewer refs per insn of
  life (summed over the function) than the allocno, unassigning every
  pseudo in it. The other allocnos still record conflicts with the evicted
  pseudos, so nothing else ever gets that register: here s1, s3, s5 and s6
  each hold one pseudo, and retail's s3 holds only 4 (entries 0-89).
- **reload takes the cheapest register per insn.** order_regs_for_reload
  prefers, for each insn, the registers with no live pseudo in allocation
  order, then the fewest refs of live pseudos. Ours ends with s1, s3 and s6
  as the reload registers (about 270 sets each), retail with t9 and s1, then
  s4, s8, t8 and s2.
- **A constant reloaded is looked for in the last register set to it.**
  find_equiv_reg (reload.c) walks back to the nearest insn that sets any
  hard register to the constant and returns nothing if that register has
  changed since; it does not look further back. So a constant held in a
  register that nothing else takes is reused to the end of the block (ours
  stores every 4 from s5), and once a later pseudo of it is given a register
  that is then reused, every reload of it is rebuilt (retail's 24 `li 4`
  after entry 237). Merging Set10's three equal arguments (one argument
  stored to fC, f14 and f18) gives the window-2 pseudo of 4 t8 in local-alloc,
  as retail has it, and retail's exact count of `li 4`; in this file's form it
  loses t8 to the 18 born at entry 235, whose life overlaps its last 35
  insns, and t9 to the 4242 born at entry 169.
- **A pseudo local-alloc could place is not always placed, and placed is not
  kept.** Its priorities and lifetimes are in its own numbering, and with
  INSN_SCHEDULING it retries a qty with a lifetime one insn longer at each
  end. A register that a model built from the `.lreg` lengths shows as free
  can therefore still be refused. After local-alloc, global-alloc's
  eviction and reload's spills can take the register back. Only the final
  code says whether a constant kept its register.
- **The constants are coupled.** In searches on func_00109488
  (build/swarm/big-109488/dsearch.py), Set10 merges on a few calls kept 8
  of the 10 window landmarks once Set8m calls were unmerged to make up the
  count. Each Set10 merge takes two insns from the `.jump` count and each
  unmerge adds one, and the landmarks before entry 553 allow a net -1 to +7.
  With the window-2 4 placed, `li 4` went from 1 to 24-40 (retail has 24).
  But func_00155778 then went from +7 to +16, 0x880 to +8 and 6 to +7. The
  distance in per-value build counts (the sum over values of
  |ours - retail| builds) was 107 at best, against 89-90 for the near miss
  that keeps 4 in s5. Freeing one constant's register re-permutes the rest.
- **One eviction costs both big values** (2026-11-10, from the near miss's
  `.lreg`). local-alloc puts 256 (entries 3-76) and func_00155778 (18 refs
  over 5,134 insns) in s5, 0.00477 refs per insn of life in all. The first
  4 (10 refs over 1,836 insns, 0.00545) gets no free register, and
  find_reg's "utilized poorly" scan, from the last register down, takes
  the first register whose local pseudos have fewer refs per insn than it:
  s5. Both are unassigned, so 4 is held to the end (retail builds it 24
  times, ours once) and func_00155778 is rebuilt at each store (8 builds,
  retail 1). Those two values are the whole of the near miss's 10-insn
  deficit; the rest cancel. Retail keeps 256 in s5 and evicts s3. The
  `.greg` dispositions come after reload's spills and retry_global_alloc,
  so they cannot show which registers had been evicted by 4's turn: that
  needs an emulation of global-alloc's allocno order.
- **The eviction order, replayed** (2026-11-10, w18; tools/globalalloc.py,
  which reproduces the dumps of 4,501 functions exactly). Before the 4's
  turn (step 579 of 2,068), s8 was opened in pass 1 by a 6-insn %hi (step
  35), s7, s4 and s2 were taken in pass 0 by other 6-insn %hi pseudos
  (steps 48, 29, 363: pass 0 reuses any register already in use, so a
  short pseudo free there takes it and the register stops being local-only),
  and t9, t8 and s6 were evicted (steps 446, 518, 576, by two 10-insn %hi
  pseudos and 0x80000000). So the scan for the 4 passes s8, t9, t8, s7, s6
  and takes s5 (0.00477 < 0.00545); s4 is not evictable and s3 (0.00449)
  is never reached. Then 66 evicts s3 and 9 evicts s1.
- **Retail's choice comes from local-alloc's order of four long constants.**
  Retail holds 2194 (from entry 257) in s7, func_00155778 in s4, an 18 in
  s5, 146 in s6, then 1 in s6 and 1025 in s7; ours has 2194 (pseudo 1701)
  in s4, func_00155778 (2072) in s5, the 18 (3199) in s7. local-alloc
  places quantities by floor_log2(refs) * refs / life: ours 1701 157, 2072
  155, 146 (1841) 150, 3199 144, so 1701 takes s4 first and pushes 2072 to
  s5. With 1701's priority below 144 (`globalalloc.py --pri 1701=140`) the
  local replay gives retail's placements, and the global replay then gives
  every retail register this function shows: the 4 in s3 (s5 is denser
  without func_00155778, s4 not local-only), 256 kept in s5,
  func_00155778 kept in s4 (built once), 66 in s1, 0x80000000 in s8. 1701
  needs 16 refs instead of 18, or a life at least 210 insns longer (4,578 to
  5,000 in local-alloc's half-insn units).
- **The lives are sched1's, and retail's final code does not show them.**
  The constant sets are inline-parameter pseudos set just before their
  stores, and sched1 hoists them by hundreds of entries (1701: set at entry
  292 before sched1, at entry 128 after; 1 (6194): 1129 to 364). The block
  is memory-bound (one store a cycle, 3,870 of 6,739 cycles issue only a
  store), so the ALU slot takes the ready constant loads in priority order,
  and a load's priority is one more than its first store's place on the
  store chain: it issues once every ALU insn feeding an earlier store has
  issued (798 before the 2194 load here, no cycle without an ALU issue).
  Retail's `li s7,2194` 345 instructions before ours is sched2's doing,
  not sched1's: in both, the load sits right after the last store of the
  register's previous value (anti-dependence), and the ALU counts per
  entry of the two final codes agree within 5 up to entry 1000.
- **Replayed with tools/sched1.py** (which reproduces this block's 8,808
  insns cycle for cycle) and `--alloc`, which runs both allocators on the
  replayed order: raising the 2194 load's priority from 1,978 to about
  2,150 (`--prio 8206=2150`) issues it 139 cycles earlier and gives every
  retail register checked (2194 in s7, func_00155778 kept in s4, the 4 in s3,
  256 kept in s5, 66 in s1, 0x80000000 in s8); 2,050-2,100 give the 4 in s3
  but lose the 2194. Moving the 18 (3199), the 146 (1841) or
  func_00155778's load alone does not. A priority 170 higher means a first
  store about 35 entries earlier, which retail's code does not show (entries
  134-248 store 2194 from t6 on both sides), so the difference is more
  likely spread over several lives than in that one load. Source variants
  should now be screened by compiling (6 s) and running `sched1.py --alloc`
  and `globalalloc.py --local` on the dumps, against the registers above.
- **A guided search** (2026-11-10, w18; build/swarm/w18-109488/search/drive.py
  with the big-109488 worker's renderer: per-call merges of equal arguments,
  single fields set after the call, Set10's three-way merge, Set8m undone;
  about 1,300 compiles, each screened on the CSE landmarks, then exact
  instructions plus retail's 256 long register holds, five of them key:
  4 in s3, 256 in s5, 66 in s1, 2194 in s7, func_00155778 in s4). Nothing
  keeps 8 landmarks and gets a key hold. Merging Set10 on any one call that
  stores 2194 (entries 134 to 336) gives three: 4 in s3, 256 kept in s5,
  66 in s1, as the replays predicted for a 2194 pseudo set earlier; but the
  2194 is still not in s7, func_00155778 is rebuilt (lui +19, addiu +18),
  the 553 landmark moves (7 of 8) and exact falls from 2,990 to about 1,600.
  600 compiles searching around that merge with three key holds required
  never restored the landmark (best: 9,380 instructions, 1,620 exact). The
  best overall, 7 single-field splits and a merge (3,050 exact, 9,340
  instructions), keeps no key hold and is per-call noise, so the near miss
  is unchanged.

What decides the bytes is therefore which handful of long-lived constants
local-alloc places, which follows the number and lives of the pseudos at
each point, that is the source's argument and statement shapes, and through
the CSE windows the instruction counts before each window edge.
func_00109488 has no call, so no callee's return type is involved.

### A scratch float in a loop: local-alloc's tie against global-alloc's ranking (func_00131F60)

Measured 2026-11-10 (w15) from the -dS and -dl dumps, with local-alloc.c and global.c read.

- **A scratch set to a constant, then to a product, then to another constant.** The gauge loop
  keeps 1/15 and 372.8 in the loop because one float is set to both (set more than once,
  loop.c does not move it). Retail's sched2 order puts the 372.8 load after `x0 = d - inset`,
  where ours issued it right after `hi = lo + d`: the scratch also holds `(1 - lo) * 55`
  (`d = (one - lo) * k; x0 = d - inset; ... d = 372.8f;`), so the constant's set has an anti
  dependence on x0's subtraction and sched1 keeps it there; global-alloc then gives the scratch
  one register for all three lives ($f2).
- **local-alloc's ties count in its ranking.** combine_regs ties `hi * height` to `hi` (hi dies
  there), adding its references (qty_n_refs, 8 + 4) and moving the quantity's death to the
  product's last use. QTY_CMP_PRI is floor_log2(refs) * refs / (death - birth), with birth and
  death at twice the insn's index in the block (labels count, notes do not): hi's quantity is
  3 * 12 / 2(n_y1 - n_hi) and a two-insn temporary's 2 * 4 / 2 * 3. With hi at insn 9 the
  temporary goes first only when y1's subtraction is at insn 23 or later.
- **global-alloc's ranking of the same insn.** y1 lives across three calls; its live length is
  the insns after its subtraction, so each insn later in block 1 shortens it by one. 16.0 is a
  preheader constant with a REG_EQUIV note, whose live length update_equiv_regs doubles (87
  insns counted as 174). 16.0 goes first (retail's $f23) only while 8 / life(y1) is below
  39 / 174, that is while y1's subtraction is at insn 22 or earlier. The two rankings want
  y1's subtraction on either side of one insn: retail's loop must have one more insn in y1's
  life (or one fewer before hi) that is gone by the final code. Written `y1` before `y0`,
  sched1 puts y1's subtraction last and local-alloc's registers are retail's but global-alloc's
  are not; the other way round, the reverse.

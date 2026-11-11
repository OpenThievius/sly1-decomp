// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 37352/37392, checked 2026-11-11
// DECLS (2026-11-11, w28-nmdecls): the 224 host-function declarations flagged by tools/decls.py are now s32 (value in v0, as their definitions and callers); they are only stored as function pointers, so no effect: 6692/9348 before and after.
#include "common.h"
// NEAR (2026-11-07, kind-130 merge, worker match-00109488-b): 9,338 instructions against retail's
// 9,348 (li -25, lui +7, addiu +7, move +1), as before. 2,990 instructions match exactly (2,842
// before), 6,692 ignoring registers (6,305 before), 758 of 1,179 entries store in retail's order
// (728 before). The CSE1 window landmarks (build/swarm/g4/winprobe.py) are all on retail's side
// (8 of 10, against 7); the two CSE2 ones (entries 122 and 1065) are still off.
//
// Source: the earlier shape, with the merge moved. The 21 Set8 entries with flags 130 (fC = f18 in
// every one) use Set8m, one argument stored to both fields. Set4 entries take fC and f14 apart again
// (no Set4m). The kind-130 merge removes 16 insns before entry 553 and un-merging Set4 adds 8, so
// the CSE1 windows land at 554, 841 and 1129 as retail's do. Parameter and body orders come from a
// climb on that shape (build/swarm/match-00109488-b/search.py, about 270 variants). Its objective
// was the window landmarks, then exact, then allocstruct.py: whether each store uses the same
// register as the previous store of the same value, compared with retail's (4,704 of 5,051 agree
// here, 4,541 before). Also found: Set16 (flags 4226, also kind 130) merged, with Set4 unmerged,
// gives retail's exact instruction count and opcode counts (9,348, no opcode off). But it puts the
// 553 window 13 insns early and matches only 1,183 exactly.
//
// Why 4 is rebuilt or not (2026-11-08, worker big-109488; docs/TOOLCHAIN.md, "Constants in one
// very long block"; scripts in build/swarm/big-109488/). The function has no call, so no callee's
// return type is involved. Reload looks for a reloaded constant only in the hard register of the
// nearest earlier insn that sets one to it (find_equiv_reg), and gives up if that register has
// changed since. Retail's window-2 pseudo of 4 (set at entry 79, stored at 142-237; ours is pseudo
// 951, born and used at the same entries) has t8; t8 is reused after 237, so every later 4 is
// rebuilt. Ours never places 951: local-alloc finds every register taken somewhere in its life by
// a pseudo of higher priority (t8 by the 18 born at entry 235 for entries 656-750, overlapping 951's
// last 35 insns; t9 by the 4242 born at entry 169), and global-alloc fails too, so the only hard
// register ever set to 4 is s5 (pseudo 118, which evicted s5's local pseudos in global-alloc's
// "poorly used" rule and so keeps it alone), and every 4 is stored from s5. Merging Set10 (one
// argument for fC, f14 and f18) gives 951 t8 in local-alloc and retail's 24 `li 4` exactly, but
// moves the windows (9,425 instructions, 1,190 exact). func_00155778 (+7) is the same kind of loss:
// pseudo 2083 gets no register. Reload's registers are s1, s3 and s6 here (about 270 sets each),
// t9 and s1 then s4, s8, t8 and s2 in retail: order_regs_for_reload takes, per insn, the
// registers holding no live pseudo first, so they name where the long pseudos sit.
// Checked on that measure (build/swarm/big-109488/pperm.py): 47 random parameter orders of one
// helper each (call sites rewritten). All keep one `li 4`. 36 compile to this file's bytes, and the
// rest lose the store order (Set14, Set5, Set0, Set1). Next: a search whose objective is the
// window-2 4 placed (a `li 4` count near retail's 24) with the CSE window landmarks held. Moves:
// the merges and splits that change where pseudos are born and die between entries 79 and 237, plus
// compensating merges elsewhere, scored from the .lreg dump (build/swarm/big-109488/blk.py lists the
// higher-priority pseudos that take each register over a pseudo's life).
// That search, run unattended (2026-11-08, build/swarm/big-109488/search.py and dsearch.py, about
// 700 compiles). Its moves were merges of equal arguments and splits of single fields, per call;
// Set10's fC = f14 = f18 merge per call; and Set8m calls unmerged back to Set8. It scored the CSE
// window landmarks, the final `li 4` count and the per-value build-count distance to retail (l1.py:
// the sum of |ours - retail| builds per constant, 90 for this file). The landmarks hold (8 of 10)
// with the window-2 4 placed: Set10 merged on about 13-18 calls between 182 and 1034, and 16-18
// Set8m calls unmerged to restore the count before entry 553. That gives 24-40 `li 4` (retail 24),
// but other values overshoot (func_00155778 +16, 0x880 +8, 6 +7). The best such form is 9,398
// instructions, 1,296 exact, distance 107 (build/swarm/big-109488/s/d4_best_107_1296.cpp). Without
// the 4 placed, the climb stays at 89-93, as this file. A pseudo the .lreg model shows as free is
// not always placed (local-alloc's own lifetimes, one insn longer at each end), and one local-alloc
// places can be lost in global-alloc or reload, so the score has to come from the final code. This
// file stays the best. With all moves together, a climb on the distance alone (gsearch.py, 90
// compiles) went from 90 to 86. It got there only by piling up 50 coincidental per-call edits, and
// exact fell to 2,527, so the gain is noise. The next attempt needs moves that change several
// long-lived constants together; no single-constant objective found a descent.
//
// Where the 10 instructions are (2026-11-10, worker w17-109488; build/swarm/w17-109488/: cum.py,
// ratio.py; re-scored 37,352 against 37,392, unchanged). They are not in one region. Aligned on the
// entry steps (`addiu v0,v0,32`), ours runs -5 to +6 instructions against retail through the
// first 700 entries and drifts to -10 by entry 825 and -12 at the end: scheduling noise over a
// register-allocation difference, not a constant rebuilt after a moved CSE flush or one entry's
// statements (the function has no branch). By value: 4 is built once against retail's 24 (-23),
// func_00155778 (lui 0x15, addiu 22392) 8 times against 1 (+14), 9 is -4, and the rest are +-1 or
// 2 and cancel. One global-alloc decision explains the two big ones. local-alloc puts both 256
// (pseudo 136, entries 3-76) and func_00155778 (pseudo 2072, 18 refs over 5,134 insns) in s5, whose
// local pseudos then have 38 refs over 7,974 insns (0.00477 per insn). The first 4 (pseudo 118,
// 10 refs over 1,836 insns, 0.00545) finds no free register, and find_reg's "utilized poorly" scan
// (global.c, from the last register down, the first whose local refs per insn are below the
// allocno's) takes s5 and unassigns both, so 4 is never rebuilt and func_00155778 is rebuilt at
// each store. Retail keeps 256 in s5 (its `li s5,256` is at insn 28) and evicts s3 for the first
// 4. Which higher registers were still local at 118's turn is not in the dumps: t9, t8, s6 and s3
// each end with one pseudo, but the dispositions are after reload's spills and
// retry_global_alloc, so the order of evictions needs an emulation of global's allocno order
// (priority floor_log2(refs) * refs / length). A form that matches must keep s5 from being the
// first register below 118's density at that point (func_00155778's pseudo out of s5, or s5
// denser), with the CSE window landmarks held. No variant was compiled this round.
//
// The allocators replayed (2026-11-10, worker w18-109488; tools/globalalloc.py, which reproduces
// both allocators' dumps of this file exactly; docs/toolchain/long-block-constants.md, "The
// eviction order, replayed"). Before the first 4's turn (step 579), s8, s7, s4 and s2 were taken by
// 6-insn %hi pseudos (pass 0 reuses registers in use) and t9, t8 and s6 evicted, so the scan takes
// s5. Retail's registers all follow from local-alloc's order of four long constants: ours ranks
// 2194 (pseudo 1701, 157) above func_00155778 (2072, 155), 146 (1841, 150) and an 18 (3199, 144),
// so 2194 takes s4 and func_00155778 s5. `globalalloc.py --dumps DIR func_00109488 --pri 1701=140`
// gives retail's local placements (2194 s7, func_00155778 s4, 18 s5, 1 s6, 1025 s7) and then
// retail's global ones: 4 in s3, 256 kept in s5, func_00155778 kept, 66 in s1, 0x80000000 in s8.
// 1701 needs 16 refs instead of 18, or a life 210 insns longer. These lives are sched1's: it hoists
// each constant load hundreds of entries above its first store (1701 from entry 292 to 128).
// tools/sched1.py replays this block cycle for cycle; `sched1.py --dumps DIR func_00109488 --prio
// 8206=2150 --alloc 118 ...` (the 2194 load issued 139 cycles earlier) gives every retail register
// checked, and moving the 18, the 146 or func_00155778 alone does not. Retail's `li s7,2194`, 345
// instructions before ours, is sched2's hoist into a freed register, not evidence of sched1's order,
// and the per-entry ALU counts of both final codes agree, so the needed change is likely spread over
// several lives. Screen variants by compiling (6 s) and running sched1.py --alloc and
// globalalloc.py --local on the dumps.
// Guided search (2026-11-10, build/swarm/w18-109488/search/, about 1,300 compiles screened on the
// landmarks, exact instructions and retail's long register holds): merging Set10 (fC = f14 = f18)
// on any one 2194 entry from 134 to 336 gives the 4 in s3, 256 in s5 and 66 in s1 as retail, but
// not 2194 in s7 or func_00155778 in s4, moves the 553 landmark and halves exact (about 1,600);
// nothing near it restored the landmark. The best form that keeps the landmarks (3,050 exact,
// 9,340 instructions) is 8 coincidental per-call edits with no key register, so this file stays.
// Whole-kind changes (2026-11-10, worker w19-109488; build/swarm/w19-109488/; docs/toolchain/
// long-block-constants.md, "The CSE windows from the source"; re-scored 37,352 against 37,392,
// 2,990 exact). Entry by entry, both codes store the same (offset, value) set in all 1,179
// entries (421 in another order): no entry has another form. A model of the windows from the
// source alone (win.py: per call, one insn per nonzero argument, two per function address, one
// per store and step; CSE1 flushes at .jump index 1002k - 2; a deleted argument's copy survives
// when its store lies past the flush) gave the landmark count of 210 of 211 compiled variants.
// Every kind-wide merge of equal arguments (Set5 146, Set14, Set10, Set11, Set6 288, Set16, Set5
// 162 and 290, Set4 18) removes 8 to 176 insns before entry 553, where the landmarks allow -1 to
// +7, and only undoing Set8m adds any (+16); of 4,566 kind-wide combinations with fields moved
// out of their helper, none holds all ten landmarks (1065 is always lost), and the 60 best
// compiled to 9 with 2,199 to 2,686 exact and at most one key register. Moving the flags
// parameter of Set10 and Set11 to any position compiles to this file's bytes. The 2194 pseudo
// (18 refs) starts at CSE1's third flush in entry 291; it would need both 292's and 293's 2194
// in the window before, 25 insns earlier, which moves the value 1 landmark at 293. About 260
// compiles; no uniform form was closer, so this file stays.
// All ten landmarks (2026-11-10, worker w20-109488b; build/swarm/w20-109488b/: pc.py, shift.py,
// joint2.py, walk.py; docs/toolchain/long-block-constants.md, "Why the 1065 landmark was lost";
// re-scored DIFFER, 37,352 against 37,392). The window model was one insn off: CSE1 flushes at
// .jump index 1002k - 1, not 1002k - 2. With that, it gives every entry's .cse2 count of this file
// and of every variant compiled since exactly, except where a flush falls between a function
// address's high and lo_sum (then 3 insns short; such forms are now rejected). The 1065 landmark
// was lost because our flushes fall inside entries' argument blocks: at 291 (256), 383 (4242 and
// 224, flush after the third of six arguments), 461 (the function address) and 937 (146) a
// deleted argument's store lies past the flush, so its copy survives, and the values set before
// the flush in 383 are set again in 384 and 450. That is 5 .cse2 insns by entry 1065 against
// retail, and no single local edit gains more than 1 (5,000 per-call merges, splits and Set8m
// undone, all screened). Uniform forms that hold all ten, found by a greedy search on the model:
// parameter orders Set0 (v0, v4, vc), Set5 (v4, v0, v14, vc, v18), Set6 (v0, v4, v18, v14) and
// Set14 (v4, v0, vc, v1c, v14, v18), with Set1's body flags-f10-fC-f0-f14 (entry 122) and Set14's
// f0 first (entry 1065); or Set1's f0 and f10 and Set0's flags moved out of their helpers. 112
// such forms compiled hold 10 of 10 as predicted. None is closer: at best 2,338 exact (this file
// 2,990), 9,309 instructions, 73 of retail's long register holds (this file 50), and of the five
// key holds only 256 in s5. So the windows are necessary and now reachable, but the allocation
// (4 in s3, 2194 in s7, func_00155778 in s4) still differs. Best: build/swarm/w20-109488b/
// best_10lm.cpp. About 125 compiles.
// The key holds inside the ten-landmark space (2026-11-10, worker w21-109488; build/swarm/
// w21-109488/: ev21.py, score.py, mwalk.py; docs/toolchain/long-block-constants.md, "The key holds
// inside the ten-landmark space"). 17 such forms compiled (w20's best, its start and 15 from its
// walks): local-alloc's priorities of the long constants are the same in all of them, 2194 157,
// the 146 of 321-343 150, the 146 of 572-654 158, the 18 of 554-650 148 or 149, and
// func_00155778 155 or 163 (20 or 21 refs; 163, with Set0's flags and Set1's f0 and f10 moved out,
// gives 256 in s5 but puts func_00155778 in s3). No key hold besides 256 in s5. On such a form
// (w/b1_2) the replays give all five key holds once the 2194 load's sched1 priority is raised from
// 1,978 to 2,100 (2,150 for this file): 4 in s3, 256 in s5, 66 in s1, 2194 in s7, func_00155778
// in s4. The 2194's refs cannot fall instead: that needs CSE1's third flush after entry 292's
// 2194 store, and a model search (16,000 mutations of ten-landmark forms) gets no closer than 3
// insns. The lever is outside the uniform forms tried. 20 compiles.
//
// Macro or table in the original? (2026-11-11, worker w23-109488-macro): PAL's 9,348 instructions
// are identical to US's apart from the %hi/%lo targets, so the source was not edited between
// versions. Retail steps one pointer by 32 in all 1,178 entries with no re-basing at any boundary,
// its opcode mix equals ours apart from li/lui/addiu/move, and its store orders inside a kind are as
// scheduler-chaotic as ours (266 distinct orders against 290). The table is in per-class source order
// (descriptor first-use runs in property_registry.cpp), which the code does not show. No evidence of
// a different source form.
// Value 4 (2026-11-07, -dl/-dg dumps): pseudo 118 is the first 4. It is the inlined flags of
// entry 0, and CSE1 extends it to every 4 in the first window: 10 uses over 1,836 insns, to entry 89.
// Global alloc gives it a callee-saved register (s5 here). In this form and every earlier one, no
// other pseudo ever gets that register: it is the only pseudo in hard reg 21. The later 4 pseudos
// get no register, and reload finds s5 still holding 4 (the function is one block, and nothing
// clobbers s5), so every 4 to the end is stored from s5 and never rebuilt. After reload the
// function sets 4 exactly once. Retail holds 4 in s3 for entries 0-89 and t8 for 142-237 (a second
// pseudo given t8 by local alloc), then rebuilds it at almost every use (24 li 4), because s3 is
// reused. Merging Set10 (fC = f14 = f18 in all 47 calls) reproduces that pattern exactly: s6 for
// 0-89 is later reused, and the second pseudo gets t8. So do merging Set16 or Set8's kind 130
// (53 to 57 of 60 stores of 4 agree), but not Set14, Set5's kinds 162 and 290, or any order
// change: about 600 order variants on three shapes all keep 4 in one register. The trigger is
// global: Set10 merged only at entries 240-340 gives it, at 0-230 or 500 on it does not, and window
// counts alone don't predict it. Every form that frees the register shifts the CSE1 windows, by
// 16 to 40 insns before entry 553. None found keeps the windows and fixes 4. This form still holds
// 4 in s5 throughout, which accounts for most of li -25.
//
// Previous near miss (branch night, 2026-11-07, natural orders on the CSE windows): 9,338 instructions against retail's 9,348
// (li -27, lui +8, addiu +8, move +1). 2,842 instructions match exactly (2,815 before), 6,305 ignoring
// registers (7,574 before), 728 of 1,179 entries store in retail's order (1,059 before), and 2,194
// stores come from retail's register (2,019 before).
//
// Why the function is chaotic: GCC 2.95's CSE flushes its hash table every 1,001 non-note insns
// (cse_basic_block), and the function is one block, so each constant gets a new pseudo per window,
// in both passes (CSE1 on the .jump stream, CSE2 after loop on what CSE1 leaves). The window edges,
// set by instruction counts that no order change moves, decide the pseudos, their live ranges and so
// the allocation. A model of the flush (build/swarm/g1/sim.py, validate.py) predicts 4,227 of 4,243
// surviving constant sets. Retail's window edges show in where value 1 changes register (entries
// 124, 192, 293, 397, 466, 554, 657, 752, 841, 939, 1067, 1129): the earlier form matched all but 122
// and 1064, and needed 8 to 16 fewer insns before entry 553 (window landmarks from worker g4).
//
// Source: one inline helper per field set, parameters 4-0-8-C-... by default. Set4 entries whose fC
// and f14 are equal (40 entries) use Set4m, one argument for both: that alone puts the CSE1 windows
// on retail's (exact 1,353 to 2,602 from plain natural orders). A greedy climb (build/swarm/g1/
// climbn.py) then chose the parameter and body orders above. Left: the CSE2 window at entry 1065 is 10
// insns late in CSE1's output (no merge or order found that moves it; CSE1 flush shifts move it by at
// most 4), and the climb's body orders put the windows at 122 and 553 one insn off again.
//
// Constructor shapes (placement new per entry, member initialisers, a base constructor, temporaries)
// all score far worse, and two inline expansions per entry overflow the stock cc1plus.exe's stack
// (wibo hangs; wine fails), so the original was not one. Inline member functions p->Set(...) compile
// to the same bytes as the static helpers.
//
// Previous best (to 2026-11-06), 9,336 instructions: 9,336 instructions against retail's 9,348 (li -27, lui +7, addiu +7, move +1). 7,557
// instructions match ignoring registers, 2,815 exactly, and 1,059 of 1,179 entries store in
// retail's order. The stores, constants and functions are right; what differs is register
// allocation, which sched2 then follows: retail spills and rebuilds more constants.
//
// Source: one inline helper per field set, parameters reversed for 0-4-C-14-18, 0-4-C-10-14,
// 0-4-18 and 0-4-C-14, default 4-0-8-C-10-14-18-1C elsewhere, bodies in offset order with f8 last.
//
// Overnight search (2026-11-04 to 05, stock compiler): 63,982 random changes to the parameter and
// body order per field set, none EXACT. Its top form scored 9,338 instructions, 7,560 ignoring
// registers, 2,849 exact, 1,047 in order: not clearly closer, so this file stays the best.
// Highest seen on any one measure: 2,888 exact, 7,566 ignoring registers. Its parameter orders:
// 0-4-C-14-18 14-18-C-4-0; 0-4-C-10-14 10-14-C-4-0; 0-4-18 18-4-0; 0-4-C-14 14-C-4-0;
// 0-4-C 0-4-C; 0-4-18-1C 4-0-1C-18; 0-4-C-14-18-1C 0-4-14-1C-C-18; 0-4-8-C-14-18 4-0-18-8-C-14;
// 0-4-8-18 18-4-8-0. Body orders: 0-4-18-1C 18-0-4-1C; 0-4-14-18 0-14-4-18; 0-4-8-C-18 0-8-18-C-4.
//
// decomp-permuter has not been run on this function.
//
// Compile conditions ruled out (2026-11-06, build/swarm/o101/sweep.txt): 129 flag sets on top of
// the default and the other compiler releases; none is closer (2.95.2 gains 2 li but breaks
// matched Vec/Mat code; 2.9-ee-991111 saves in 8 bytes). The extra rebuilt constants come from
// the inliner's argument pseudos (each constant 4 is one; only the first gets a register), so
// they follow the source's shape. Lead: in every call fC = f14 = f18 (Set10, Set11, Set14) and
// fC = f18 (Set16, Set17); the original may pass one offset stored to several fields. Merging
// Set16's alone gives opcode counts much closer to retail's (9 off, against 42) but fewer exact
// instructions; a search would have to be redone on that shape.
//
// Same scores as this file: a reference per entry; s16/u16 for flags, s16/s8 for an integer f8; a
// shared base helper for f0 and flags (the last overflows the stock compiler, below). Nothing
// here moved the RTL. Function-pointer types were tried earlier and compile to the same bytes.
//
// Worse (8,779 to 16,600 instructions; at most 5,208 ignoring registers): an inline setter per
// field, chained setters, a helper with a local copy of the pointer, helpers returning the next
// pointer, the pointer by reference, `(p++)->` on the last store, `Prop* q = p++`, `Set(p++, ...)`
// and `D_002505D8[i].f` for every store. A constructor shape is untested (the attempt had
// ambiguous overloads).
//
// Those forms, and the shared base helper, overflow cc1plus.exe's 1 MiB stack: SIGSEGV after about
// 3 s under wibo, which also looks like a hang under Rosetta (not confirmed), and 0xC00000FD run
// natively on Windows for the one form tried. Their scores come from a private copy with the PE
// stack reserve raised to 64 MiB, whose output for this file's form was byte-identical to stock's.
// That is for measuring only: a candidate must compile on the stock compiler to land.
//
// The function is one basic block: no call, no branch. func_00155778 (2026-11-05, -dl/-dg
// dumps with -dumpbase): retail holds it in two values, s4 (16 stores at +0x1C, asm lines
// 3043-3183) and a copy in a7 = r11 (36 stores, 3193-3490), both loaded near line 1370. This
// form has the same two after CSE: pseudo 2196 (the copy, 37 refs) gets r11 as retail's does, but
// pseudo 2083 (18 refs over 5132 insns, a user variable from the helpers' parameters) gets no
// register in global alloc, so reload rebuilds it at each store (lui/addiu into s1, s3, s6...).
// Its priority, floor_log2(refs) * refs / live length, is low, so it is allocated late; by then
// s4 is held here by the 2194 of entries 257 on (retail holds that one in s7; entries 134-248
// hold 2194 in t6 on both sides).
//
// The whole allocation is permuted, from entry 0 (value 4: s5 here, s3 in retail). Per value,
// this form builds 4 23 times fewer than retail and func_00155778 7 times more: it keeps one 4
// in s5 across the whole table, where retail rebuilds 4 at almost every use after entry 237 and
// spends the register on func_00155778. The 4s are eleven pseudos here (user variables from the
// helpers' parameters), each live over thousands of insns: sched1, before allocation, moves the
// constant loads far from their stores, so the live lengths behind every priority come from
// sched1's choices, whose ties go to insn order (LUID), that is to the order of the source's
// parameters and statements. That is why only orders move this function; byte-exact counts barely
// move until everything is right.
//
// Next: score candidates on the allocation instead of the bytes. build/swarm/lead/f109/trace.py
// gives, per store (entry, offset), each side's register and value (the values all agree), and
// builds.py the per-value build counts; a search that minimises the register differences, or the
// build-count distance (4 and func_00155778 first), has a gradient where EXACT has none.
//
// Tried (2026-11-05, build/swarm/lead/f109/): hill-climbing the statement order inside the helpers
// on that score took the register differences from 3,537 to 3,133 of 5,503 stores and the size to
// retail's (37,392 bytes, 13,045 matching), but only by giving up the store order: 159 of 1,179
// entries in retail's order, against this file's 1,059. 4 and func_00155778 did not move. The
// parameter orders (call sites rewritten to match), with the store order held, found nothing in
// 1,500 tries: most swaps compile to the same bytes, the rest lose the store order. This file stays
// the best. Neither order reaches retail's allocation in this shape; what is left is the shape of
// the entries themselves, of which the plain stores and the forms above score worse.

//
// Further findings (worker g4, CSE windows and reload; measured on the previous form):
// CSE windows (2026-11-07, build/swarm/g4/: winprobe.py, pmerge.py, split.py, tr.py, cnt.py).
// cse_basic_block flushes its hash table every 1,002 insns (1,001 counted, then the flush), in
// both passes, so each constant gets a fresh pseudo per window: in the first pass by the .jump
// count (every parameter load counts, including the copies of repeated arguments), in the second by
// the .cse2 count (only what survives the first). Our register for value 1 changes exactly at the
// predicted entries. Retail's register runs for 1 give the landmarks: first pass, entry 553 still
// old and 554 new, 838 old and 841 new, 1122 old and 1129 new; second pass, 122 old and 124 new,
// 1065 old and 1067 new. This file passes 5 of the 10, being a few first-pass insns too long by
// entry 553: retail has about 8 to 16 fewer by then. That rules out merging repeated arguments in
// the big kinds (flags 146, 4242, 2194: ~94 insns by entry 553), and leaves the 16 calls with
// flags 162 (fC = f18, one parameter: s5 in that folder, 9,331 instructions, 2,864 exact, 7,576
// ignoring registers, 1,066 in order, 8 of 10) or the 21 with flags 130 (s8, 8 of 10). Entry 1065
// is then met by also merging the coincidental f0 = flags of the three flags-2 Set0 calls (9 of
// 10). Entry 122 needs 2 fewer surviving insns before its flags store, which no merge gives; taking
// Set1's f10 (the function pointer) out of the helper as a plain `p->f10 = ...;` after the call
// does it, and gives Set1 retail's commonest store order, 0-4-C-14-10. With both, every register
// run of value 1 lands on retail's entries. None of these forms scores closer than this file
// (s5 + f10 split: 2,544 exact; all three: 2,273): fitting the windows looks necessary, not
// sufficient. About 360 merge and split combinations were probed.
// What is left is reload's choice of spill registers. In .lreg, local-alloc gives the first
// window's 256 (pseudo 137, entries 3 to 76) s5, as retail has it; in .greg it has lost s5, and
// every pseudo of 4 takes s5 for the whole function, where retail holds 4 in s3, then t8, then
// rebuilds it. Our rebuild registers in the first window are s3, s1 and s6, retail's t9 and t6:
// reload spilled other hard registers, by a cost summed over the whole function.
// Spill choice (2026-11-07, build/swarm/g4/spill.py, disp.py): scored by the registers that rebuild
// a constant inside one entry, per 50 entries, against retail's, and by where 4 lives. Every form
// with this file's store order keeps all of 4's pseudos in s5 (0 of retail's 60 stores of 4 in
// retail's register): this file, s5, s8, the f10 split, flags as literals per kind, every parameter
// order of the merged helper, and the lead's hill-climbed body orders (build/swarm/lead/f109/
// best13.cpp and best22.cpp, up to 2,370 stores in retail's register). The only forms that move 4
// out of s5 (up to 16 of 60) are the merges of the big kinds (flags 146, 4242, 2194), which break
// the windows above and the store order (about 500 entries in order, two fewer spills). The .greg
// dump shows why it is global: reload spills v1, a1, s1 and t2 hundreds of times and s3 in the
// first window, where retail rebuilds in t9 and t6, and its spill cost is summed over the whole
// function. No plausible source change tried steers that choice; this lead is closed.
//
s32 TestScriptObjectOfKind();
s32 AddScriptObjectKeyToOwner();
s32 RemoveScriptObjectFromParentList();
s32 AddScriptObjectToParentList();
s32 CreateScriptObjectCopy();
s32 ReparentScriptObject();
s32 TestScriptObjectDescendantOf();
s32 TestScriptObjectIdMatch();
s32 SetScriptExtraObjectPropertyBool();
s32 SetScriptExtraObjectPropertyInt();
s32 SetScriptExtraObjectPropertyFloat();
s32 SetScriptExtraObjectPropertyVectorB();
s32 SetScriptExtraObjectPropertyPair();
s32 SetScriptExtraObjectPropertyWord();
s32 SetScriptExtraObjectPropertyVectorA();
s32 ClearScriptObjectRecordValues();
s32 ClearScriptAimHold();
s32 SetScriptAimHold();
s32 SetScriptValueAttachment();
s32 SetScriptElementsScrollScale();
s32 SetScriptCrossfadeRatioDeep();
s32 StartScriptSoundWithParams();
s32 StopScriptPlayingSound();
s32 FadeInScriptPlacedObject();
s32 FadeOutScriptPlacedObject();
s32 FindScriptObjectHandle();
s32 FindScriptObjectAnimationPlayer();
s32 FindScriptTrackPlayer();
s32 CopyScriptPlacedObjectFrame();
s32 SetScriptFollowObjects();
s32 SetScriptColliderFlagNibble36();
s32 TestScriptPointInsideCollider();
s32 SetScriptTransformObjectKeyedValue();
s32 PlaceScriptAtArrivalPoint();
s32 StartScriptObjectSubGroupFinish();
s32 CreateScriptAnimationPlayer();
s32 FindOrCreateScriptSeekedAnimationPlayer();
s32 GetScriptAnimationMarkerTime();
s32 SeekScriptAnimationPlayer();
s32 StopScriptAnimationPlayer();
s32 ApplyScriptListedPoseSources();
s32 ReleaseScriptPlayerAttachment();
s32 ClearScriptAttachedSetTrackedNodes();
s32 HandleScriptMaskedColliderActivation();
s32 SetScriptTriggerZoneEntry();
s32 SetScriptZoneColliderEntry();
s32 ActivateScriptSwitchedColliderUnlessActive();
s32 TestScriptRequestBlocked();
s32 SetScriptStateTriggerStateFromMessage();
s32 AddScriptStateTriggerTableEntry();
s32 SetScriptTimedObjectMode();
s32 RequestScriptTimedObjectEnd();
s32 SetScriptTimedGroupFadeInTime();
s32 SetScriptTimedGroupFadeOutTime();
s32 SetScriptEffectSpawnerActiveFor();
s32 SetScriptEffectSpawnerActiveForever();
s32 SetScriptEffectSpawnerInactive();
s32 AddScriptSpawnRangeEntry();
s32 AddScriptRecordMemberRangeEntry();
s32 SendScriptEmptyMessageC7A();
s32 SendScriptTwoVectorMessageC7A();
s32 SendScriptEmptyMessageC78();
s32 SendScriptTwoVectorMessageC78();
s32 CreateScriptStateWalker();
s32 DestroyScriptStateWalker();
s32 ScatterScriptRandomObjects();
s32 SetScriptIopChannel2Setting();
s32 PushScriptIopChannel2Setting();
s32 PopScriptIopChannel2Setting();
s32 TestScriptLevelEntryFlag1();
s32 TestScriptLevelEntryFlag2();
s32 TestScriptLevelEntryFlag4();
s32 TestScriptLevelEntryFlag8();
s32 CheckScriptEntryOneBitRequirement();
s32 CheckScriptEntryTwoBitRequirement();
s32 CheckScriptEntryThreeBitRequirement();
s32 SetScriptEntrySlotValue();
s32 GetScriptEntrySlotValue();
s32 IsScriptLevelRecordComplete();
s32 IsScriptLevelDone();
s32 RecomputeScriptSaveCompletion();
s32 PopScriptActiveSequenceElement();
s32 ShowScriptPauseMenuPageWith();
s32 ShowScriptCountedScreenElement();
s32 HideScriptCountedScreenElement();
s32 PushScriptSoundLevel();
s32 RemoveScriptSoundLevel();
s32 SetScriptCachedVoiceParam();
s32 GetScriptCachedVoiceParam();
s32 RefreshScriptCachedVoiceParam();
s32 AcquireScriptPadSelectFlag();
s32 ReleaseScriptPadSelectFlag();
s32 ClearScriptWorldFlagBit();
s32 SetScriptWorldFlagBit();
s32 PushScriptCameraStackValue();
s32 PopScriptCameraStackValue();
s32 PeekScriptCameraStackValue();
s32 SetScriptCameraControllerSettings();
s32 RecordScriptCameraTimestamp();
s32 RequestScriptPlainCameraSnap();
s32 TestScriptSphereInCameraView();
s32 PushScriptObjectCameraController();
s32 RemoveScriptObjectCameraController();
s32 ClearScriptTrackedNodes();
s32 CollectScriptNumberedItem();
s32 SetScriptAgentStateClipId();
s32 SetScriptAgentStateClip();
s32 GetScriptAgentStateClip();
s32 AddScriptAgentClipGroup();
s32 AddScriptAgentMeshKey();
s32 AddScriptAgentExtraClip();
s32 ForceScriptAgentState();
s32 SetScriptAgentSecondaryClipId();
s32 SteerScriptAgentAlongPath();
s32 SetScriptAgentMainClip();
s32 SetScriptCompanionAgentLookId();
s32 StartScriptChildGroupDelay();
s32 StepScriptChildGroupObject();
s32 PlaceScriptPlayerOnGround();
s32 ReleaseScriptPlayerToState2();
s32 IgnoreScriptPlayerArgument();
s32 SetScriptPlayerPath();
s32 SwitchScriptPlayerState11();
s32 SeekScriptObjects105Animations();
s32 SwapInScriptPlayerStandIn();
s32 QueueScriptPlayerWalkerActivation();
s32 QueueScriptPlayerFirstActivation();
s32 QueueScriptPlayerSecondActivation();
s32 SetScriptC8BObjectVector();
s32 SetScriptC8BObjectVectorFlagged();
s32 ResetScriptCollectedItems();
s32 CollectScriptItem();
s32 AddScriptContactListId();
s32 AddScriptContactListKind();
s32 AddScriptStateResetEntry();
s32 SetScriptCurrentTargetFollower();
s32 ClearScriptCurrentTargetFollower();
s32 AddScriptObjectPoolEntry();
s32 EnableScriptObjectPoolEntry();
s32 DisableScriptObjectPoolEntry();
s32 SetScriptObjectPoolEntryCount();
s32 ChooseScriptObjectPoolItem();
s32 ReleaseScriptObjectPoolItem();
s32 ResetScriptPlacementRecord();
s32 ResetScriptObjectPoolReleaseRecord();
s32 ClearScriptObjectPoolHeadingRecord();
s32 SetScriptStepSequenceModeOne();
s32 SetScriptStepSequenceCameraMode();
s32 AddScriptSequenceExtraTarget();
s32 ChooseScriptStepSequenceState();
s32 ResetScriptStepSequence();
s32 QueueScriptWalkerActivationOnPlayer();
s32 AddScriptOscillatorXEntry();
s32 AddScriptOscillatorYZEntry();
s32 AddScriptOscillatorEntryVectorA();
s32 AddScriptOscillatorEntryVectorB();
s32 AdvanceScriptGaugeAgentPhase();
s32 AddScriptEntryRecordKey();
s32 AddScriptPathFollowerEntry();
s32 AddScriptPathFollowerActiveEntry();
s32 ResetScriptPathFollower();
s32 TestScriptPointAgainstObjectShape();
s32 TestScriptPointInsideFaceTreeObject();
s32 AddScriptSeekingAgentObject();
s32 StartScriptC24ObjectPath();
s32 ResetScriptEntryQueue();
s32 BindScriptEntryQueueToObject();
s32 UnbindScriptEntryQueue();
s32 AddScriptQueueEntryKind0();
s32 AddScriptQueueEntryKind1();
s32 AddScriptQueueEntryKind10();
s32 AddScriptQueueEntryKind2();
s32 AddScriptQueueEntryKind3();
s32 AddScriptQueueEntryKind4();
s32 AddScriptQueueEntryKind5();
s32 AddScriptQueueEntryKind6();
s32 AddScriptQueueEntryKind7();
s32 AddScriptQueueEntryKind8();
s32 AddScriptQueueEntryKind9();
s32 AddScriptQueueEntryKind11();
s32 AddScriptQueueEntryKind12();
s32 StartScriptColorFade();
s32 PlayScriptGaugeModeObjectTarget();
s32 SetScriptGaugeModeObjectTarget();
s32 PlaceScriptModeColliderAtAnchor();
s32 SetScriptTempoAgentPendingTimeline();
s32 EndScriptHeldTimeline();
s32 AddScriptC13Entry();
s32 RemoveScriptTempoAgentEntry();
s32 DecrementScriptTempoAgentGauge();
s32 AppendScriptTimelineKind0Entry();
s32 AppendScriptTimelineKind1Entry();
s32 AppendScriptTimelineKind2Entry();
s32 AppendScriptTimelineKind3Entry();
s32 AppendScriptTimelineKind4Entry();
s32 AppendScriptTimelineKind5Entry();
s32 SetScriptGaugeBarAgentValues();
s32 SendScriptHitCountColliderRequest();
s32 AddScriptHitCountColliderId();
s32 AddScriptHitCountColliderItem();
s32 TakeScriptCountedColliderTouch();
void AddStateTriggerCountedId();
void AddStateTriggerItemId();
void AddStateTriggerAgentId();
s32 TestStateTriggerItemsAccepted();
void SetObjectTreeRecordValue();
void SetObjectRecordValue();
void SetPlacedObjectLocalVelocity();
void GetPlacedObjectLocalVelocity();
s32 TestChildrenAccepted();
void StorePlacedObjectLocalVelocity();
void StorePlacedObjectLocalSpin();
s32 EnsureTimerRecord();
void SetPlacedObjectScaleXY();
void GetPlacedObjectScaleXY();
void SetPlacedObjectScaleZ();
void GetPlacedObjectScaleZ();
void SetRangeRecordPresent();
void SetRangeRecordKey();
void SetRangeRecordNear();
void SetRangeRecordFar();
void SetRangeRecordInner();
void SetRangeRecordOuter();
void SetRangeRecordInnerAndOuter();
void SetRangeRecordVector();
void SetRangeRecordCode();
void GetRangeRecordPresent();
void GetRangeRecordKeyValue();
void GetRangeRecordNear();
void GetRangeRecordFar();
void GetRangeRecordInner();
void GetRangeRecordOuter();
void GetRangeRecordAngle();
void GetRangeRecordVector();
void GetRotationDegrees();
void SetRotationDegrees();
void SetScaledPositionSpring();
void SetPositionSpring();
void SetScaledVelocitySpring();
void SetVelocitySpring();
void SetScaledRotationSpring();
void SetRotationSpring();
void SetScaledSpinSpring();
void SetSpinSpring();
void SetScaledPositionRamp();
void SetPositionRampAccelScale();
void SetPositionRamp();
void SetScaledRotationRamp();
void SetRotationRampAccelScale();
void SetRotationRamp();
void SetDefaultPositionMode();
void SetDefaultOrientationMode();
void SetPositionSourceEnabled();
void SetGroupActivityModeEnabled();
void SetGroupActivityMode();
void GetGroupActivityMode();
void SetPositionSourceMode();
void SetOrientationSourceEnabled();
void SetOrientationSourceMode();
void SetBaseAttachmentSortKey();
void SetAimOrientationMode();
void SetAimRange();
void GetAimRange();
void SetAimYawCurve();
void GetAimYawCurve();
void SetAimYawLimits();
void GetAimYawLimits();
void SetAimPitchCurve();
void GetAimPitchCurve();
void SetAimPitchLimits();
void GetAimPitchLimits();
void SetAimNearKey();
void GetAimNearKey();
void SetAimFarKey();
void GetAimFarKey();
void SetAimTargetId();
void GetAimTargetId();
void SetAimTarget();
void GetAimTarget();
void SetClass75ObjectCount();
void SetClass75ObjectScale();
void SetClass75ObjectField90();
void SetSoundRecordId();
void RestartSoundWithId();
void GetSoundRecordId();
void SetSoundOuterRange();
void GetSoundOuterRange();
void SetSoundInnerRange();
void SetSoundRecordPair();
void GetSoundInnerRange();
void SetSoundRecordScale();
void SetSoundStartParam();
void GetSoundStartParam();
void SetPlayingSoundVolume();
void GetSoundRecordScale();
void SetSoundStartPitch();
void SetPlayingSoundPitch();
void GetSoundStartPitch();
void GetSoundRecordPair();
void SetColorPreset();
void GetColorPreset();
void SetColorRecordFirstColor();
void GetColorRecordFirstColor();
void SetColorRecordSecondColor();
void GetColorRecordSecondColor();
void SetColorRecordFactor();
void GetColorRecordFactor();
void SetTintRgb();
void GetTintRgb();
void SetTintByte0();
void GetTintByte0();
void SetTintByte1();
void GetTintByte1();
void SetTintByte2();
void GetTintByte2();
void SetTintByte3();
void GetTintByte3();
void SetTintByte4();
void GetTintByte4();
void SelectValueEntryByKey();
void SetObjectCameraTracked();
void SetPlacedObjectFrameStepClock();
void SetPlacedObjectSpecialFlag();
void GetPlacedObjectSpecialFlag();
void SetAnimationPlayerPadSelect();
void SetAnimationPlayerSpeed();
void SetAnimationPlayerSpeedScale();
void SetAttachmentSortKeys();
void AddIdFilterObjectId();
void AddIdFilterClassId();
void GetObjectClassId();
s32 GetChildGroupSoundParams();
void SetObjectHold();
void AddMaskedColliderKeyKind0();
void AddMaskedColliderKeyKind1();
void AddMaskedColliderKeyKind2();
void AddMaskedColliderKeyKind3();
void SetAcceptsPlayer();
void GetAcceptsPlayer();
void SetAcceptsFlaggedObjects();
void GetAcceptsFlaggedObjects();
void AddAcceptedObjectId();
void AddAcceptedKind();
void AddMaskedColliderListEntry();
s32 GetMaskedColliderSoundParams();
void SetTimedState();
void SetTriggerZoneMode();
void SetZoneColliderMode();
s32 TestListedEntriesAccepted();
void AppendTriggerZoneFirstQueue();
void AppendZoneColliderFirstQueue();
void AppendTriggerZoneSecondQueue();
void AppendZoneColliderSecondQueue();
void AddIncludedId();
void AddExcludedId();
void AddIncludedKind();
void AddExcludedKind();
void AddZoneColliderId();
void AppendFlaggedObjectIdB();
void AppendFlaggedObjectIdA();
void SetFlaggedChildId();
void SnapCurrentCameraZoom();
void SetCurrentCameraNearDistance();
void SetCurrentCameraFarDistance();
void SetCurrentCameraFogNear();
void SetCurrentCameraFogFar();
void SetCurrentCameraFogStrength();
void SetCurrentCameraFogColor();
void SetCurrentCameraDistanceScale();
void SetCameraPosition();
void SetCameraOrientation();
void SnapCameraZoom();
void SetCameraNearDistance();
void SetCameraFarDistance();
void SetCameraFogNear();
void SetCameraFogFar();
void SetCameraFogStrength();
void SetCameraDistanceScale();
void SetOffsetScale();
s32 GetGaugeParams();
void AppendGaugeSlot();
void SetPooledObjectState();
void AddPooledHolderItem();
void ReadSequenceTarget();
void WriteSequenceTarget();
void SetStepSequenceState();
s32 GetScatterController();
s32 GetOwnSpawnRecord();
s32 MarkEffectSpawnerChanged();
void SetEffectSpawnerDisabled();
void GetEffectSpawnerInactive();
void GetEffectSpawnerActive();
void SetEffectSpawnerLimit();
void SetEffectSpawnerContinuous();
void SetEffectSpawnerKind();
void SetOwnedSpawnRecordKind();
s32 GetOwnedSpawnRecord();
s32 GetOrCreateSoundParams();
void SetObjectCyclerState();
s32 GetPlacedObjectFrozen();
void AddLookupId();
void FollowObjectById();
void SetPlayerProbeContactsDisabled();
void SetGaugeModeObjectMode();
s32 PlayGaugeModeObjectLoop();
void SetCountdownState();
void SetModeWalkerMode();
void AddObjectKeyIfLevelInRange();
void GetObjectAttached();
void GetObjectAliasId();
void SetConeVolumeMode();
void SetConeVolumeColor();
void SetConeVolumeSecondLevel();
void SetConeVolumeThirdLevel();
void SetConeVolumeFirstAngle();
void SetConeVolumeSecondAngle();
void SetConeVolumeThirdAngle();
void SetConeVolumeDirection();
void SetConeVolumeValue();
void SetConeVolumeRange();
void SetConeVolumeOuterAngle();
void SetConeVolumeInnerAngle();
void SetConeVolumeVector340();
void SetConeVolumeOuterLevels();
void GetConeVolumeSecondLevel();
void SetConeVolumeColorRgb();
void GetConeVolumeColorRgb();
void GetGaugeAgentLevelFactor();
void SetSeekingAgentStateTarget();
void SetSeekingAgentTarget();
void PickRandomPointOnPointGraph();
void ConvertPositionToWorld();
void StoreSwitchedColliderAccepted();
void SetSwitchedColliderEnabled();
void AddObjectSetKey();
void SetC5DObjectMaskBit();
void AddC5DObjectId();
void GetNumberedItemFlag();
void SetPairControllerFirstTemplateId();
void SetPairControllerSecondTemplateId();
void SetPairControllerHostId();
void SetPairControllerExtraId();
void AppendPairControllerId();
s32 GetPairControllerPose();
s32 GetObjectPoolShare();
void AddTimedObjectAcceptedObjectId();
void AddTimedObjectExcludedObjectId();
void AddTimedObjectAcceptedClassId();
void AddTimedObjectExcludedClassId();
void SetStateWalkerTarget();
void GetStateWalkerTargetKey();
void GetStateWalkerCurrentKey();
void GetStateWalkerNextKey();
void SetStateWalkerSpeed();
void TeleportStateWalker();
void AddCompanionAgentExcludedId();
void SetColliderMass();
void SetColliderOverrideRadius();
void ResetColliderAnchors();
void SetColliderTurnAnchorPreset();
void SetColliderMoveAnchorPreset();
void SetColliderFlagNibble32();
void SetColliderFlagBit47();
void SetColliderFlagBit48();
void SetColliderSurfaceKind();
void SetColliderGravityDisabled();
void SetColliderTreeContactsDropped();
void SetColliderContactsDropped();
void SetColliderKindContactsDropped();
s32 CollectContactingPartsToScriptList();
void SetColliderFlagBit52();
void GetColliderFlagBit52();
void AddWorldSoundEntry();
void SetLastWorldSoundEntryFromPoint();
void SetLastWorldSoundEntryValues();
void SetObjectLinkId();
void SetHitCountColliderState();
void ScaleTurningColliderRamp();
void SetTurningColliderGravityScale();
void IsAgentNearPathEnd();
void SetAgentMemberGroupId();
void SetAgentTargetSetId();
void SetAgentPathObjectId();
void StoreAgentTarget();
void SetAgentSecondaryTarget();
void SetAgentAngleLimitDegrees();
void AddOwnedWantedId();
void AddListedWantedId();
void SetPlayerPadSelectMode();
void SetPathFollowerPath();
void SetPathFollowerSecondPath();
void SetPathFollowerMode();
void SetWorldLightingParamA();
void SetWorldLightingParamB();
void SetWorldSoundLevel();
void SetScatterLevelBuiltin();
void GetGameStateDeltaTime();
void SetCurrentScatterLevel();
void GetCurrentScatterLevel();
void GetHasStreamVoice();
void SetWorldValueAndTarget();
void SetWorldValueTarget();
void GetSaveSpareCount();
void GetReserveUnitCount();
void SetTintBlendColliderState();
void SetOnOffObjectForcedState();
void SetOnOffObjectBlockValue();
void AddPlayerLinkedColliderId();
void SetTempoAgentTempo();
void SetTempoAgentSpanBeats();
s32 GetAttachedSetTrackedNodes();
s32 GetOscillatorEntryForPeriod();
s32 GetOscillatorEntryForVectors();
void SetOscillatorEntryPeriod();
void GetOscillatorEntryPeriod();
s32 GetObjectWorldPosition();
s32 GetObjectWorldRotation();
void StoreValueAndMarkSet();
void SetObjectSubGroupState();
s32 GetContactTrackerRecord();
void AddTrackedKey();
void AddTrackedNode();
void RemoveTrackedNode();

struct PropertyDescriptor { s32 f0; s32 flags; union { f32 f; s32 i; } f8; s32 fC; s32 f10; s32 f14; s32 f18; s32 f1C; };
extern PropertyDescriptor D_002505D8[1179];

struct PropInit {
    static void Set0(PropertyDescriptor* p, s32 v4, s32 v0, s32 vc) { p->f0 = v0; p->flags = v4; p->fC = vc; }
    static void Set1(PropertyDescriptor* p, s32 v10, s32 vc, s32 v0, s32 v4, s32 v14) { p->f10 = v10; p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; }
    static void Set2(PropertyDescriptor* p, s32 v0, s32 v4, s32 v18) { p->f0 = v0; p->flags = v4; p->f18 = v18; }
    static void Set3(PropertyDescriptor* p, s32 v0, s32 v4, s32 v18, s32 v1c) { p->f18 = v18; p->f0 = v0; p->f1C = v1c; p->flags = v4; }
    static void Set4(PropertyDescriptor* p, s32 v4, s32 v0, s32 vc, s32 v14) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; }
    static void Set5(PropertyDescriptor* p, s32 v4, s32 v14, s32 vc, s32 v0, s32 v18) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; p->f18 = v18; }
    static void Set6(PropertyDescriptor* p, s32 v14, s32 v0, s32 v4, s32 v18) { p->f0 = v0; p->flags = v4; p->f14 = v14; p->f18 = v18; }
    static void Set7(PropertyDescriptor* p, s32 v0, s32 v4) { p->flags = v4; p->f0 = v0; }
    static void Set8(PropertyDescriptor* p, s32 v0, s32 v4, s32 vc, s32 v18) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = v18; }
    static void Set8m(PropertyDescriptor* p, s32 v0, s32 vc, s32 v4) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = vc; }
    static void Set9(PropertyDescriptor* p, s32 v4, s32 v0, s32 v14) { p->f14 = v14; p->flags = v4; p->f0 = v0; }
    static void Set10(PropertyDescriptor* p, s32 v0, s32 v4, s32 v18, s32 vc, s32 v14, f32 v8) { p->f0 = v0; p->f14 = v14; p->f8.f = v8; p->fC = vc; p->f18 = v18; p->flags = v4; }
    static void Set11(PropertyDescriptor* p, s32 v18, s32 v8, s32 v14, s32 vc, s32 v0, s32 v4) { p->f18 = v18; p->f14 = v14; p->f8.i = v8; p->fC = vc; p->f0 = v0; p->flags = v4; }
    static void Set12(PropertyDescriptor* p, s32 v4, s32 v18, s32 v8, s32 v0) { p->f0 = v0; p->flags = v4; p->f8.i = v8; p->f18 = v18; }
    static void Set13(PropertyDescriptor* p, s32 v14, s32 v4, s32 v0, s32 v1c) { p->f1C = v1c; p->flags = v4; p->f14 = v14; p->f0 = v0; }
    static void Set14(PropertyDescriptor* p, s32 v4, s32 v0, s32 vc, s32 v14, s32 v18, s32 v1c) { p->flags = v4; p->f0 = v0; p->fC = vc; p->f14 = v14; p->f18 = v18; p->f1C = v1c; }
    static void Set15(PropertyDescriptor* p, s32 v18, f32 v8, s32 v0, s32 v4) { p->f0 = v0; p->flags = v4; p->f8.f = v8; p->f18 = v18; }
    static void Set16(PropertyDescriptor* p, s32 v0, s32 vc, s32 v18, s32 v1c, s32 v4) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = v18; p->f1C = v1c; }
    static void Set17(PropertyDescriptor* p, s32 vc, s32 v18, s32 v8, s32 v0, s32 v4) { p->flags = v4; p->f8.i = v8; p->fC = vc; p->f0 = v0; p->f18 = v18; }
};

void FillObjectPropertyTable()
{
    PropertyDescriptor* p = D_002505D8;
    PropInit::Set0(p, 4, 7, (s32)GetObjectClassId); p++;
    PropInit::Set1(p, (s32)TestScriptObjectOfKind, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)RemoveScriptObjectFromParentList, (s32)AddScriptObjectKeyToOwner, 18, 1025, 0); p++;
    PropInit::Set2(p, 10, 256, (s32)AddObjectKeyIfLevelInRange); p++;
    PropInit::Set1(p, (s32)AddScriptObjectToParentList, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)CreateScriptObjectCopy, 0, 8193, 1, 2); p++;
    PropInit::Set0(p, 2, 8300, 20); p++;
    PropInit::Set0(p, 4, 0, (s32)GetObjectAttached); p++;
    PropInit::Set0(p, 2, 8194, 24); p++;
    PropInit::Set1(p, (s32)ReparentScriptObject, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)TestScriptObjectDescendantOf, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 2, 6, 8); p++;
    PropInit::Set0(p, 4, 6, (s32)GetObjectAliasId); p++;
    PropInit::Set1(p, (s32)TestScriptObjectIdMatch, 0, 0, 1, 1); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyBool, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyInt, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyFloat, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyVectorB, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyPair, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyWord, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptExtraObjectPropertyVectorA, 18, 1024, 2); p++;
    PropInit::Set2(p, 2, 256, (s32)StorePlacedObjectLocalVelocity); p++;
    PropInit::Set2(p, 2, 256, (s32)StorePlacedObjectLocalSpin); p++;
    PropInit::Set3(p, 6, 4224, 4, (s32)EnsureTimerRecord); p++;
    PropInit::Set3(p, 1, 4224, 12, (s32)EnsureTimerRecord); p++;
    PropInit::Set3(p, 1, 4224, 16, (s32)EnsureTimerRecord); p++;
    PropInit::Set3(p, 4172, 4224, 8, (s32)EnsureTimerRecord); p++;
    PropInit::Set1(p, (s32)ClearScriptObjectRecordValues, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)GetPlacedObjectFrozen); p++;
    PropInit::Set4(p, 66, 2, 256, 132); p++;
    PropInit::Set4(p, 18, 2, 400, 400); p++;
    PropInit::Set0(p, 2, 2, 320); p++;
    PropInit::Set4(p, 66, 4, 208, 136); p++;
    PropInit::Set4(p, 18, 4, 416, 416); p++;
    PropInit::Set0(p, 2, 4, 272); p++;
    PropInit::Set5(p, 292, (s32)SetRotationDegrees, (s32)GetRotationDegrees, 2, (s32)SetRotationDegrees); p++;
    PropInit::Set4(p, 36, 2, (s32)GetPlacedObjectLocalVelocity, (s32)SetPlacedObjectLocalVelocity); p++;
    PropInit::Set4(p, 66, 2, 352, 148); p++;
    PropInit::Set0(p, 2, 2, 368); p++;
    PropInit::Set0(p, 2, 2, 384); p++;
    PropInit::Set0(p, 2, 8194, 80); p++;
    PropInit::Set5(p, 292, (s32)SetPlacedObjectScaleXY, (s32)GetPlacedObjectScaleXY, 1, (s32)SetPlacedObjectScaleXY); p++;
    PropInit::Set5(p, 292, (s32)SetPlacedObjectScaleZ, (s32)GetPlacedObjectScaleZ, 1, (s32)SetPlacedObjectScaleZ); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordPresent, (s32)GetRangeRecordPresent, 0, (s32)SetRangeRecordPresent); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordKey, (s32)GetRangeRecordKeyValue, 6, (s32)SetRangeRecordKey); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordNear, (s32)GetRangeRecordNear, 1, (s32)SetRangeRecordNear); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordFar, (s32)GetRangeRecordFar, 1, (s32)SetRangeRecordFar); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordInner, (s32)GetRangeRecordInner, 1, (s32)SetRangeRecordInner); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordOuter, (s32)GetRangeRecordOuter, 1, (s32)SetRangeRecordOuter); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordInnerAndOuter, (s32)GetRangeRecordAngle, 1, (s32)SetRangeRecordInnerAndOuter); p++;
    PropInit::Set5(p, 292, (s32)SetRangeRecordVector, (s32)GetRangeRecordVector, 2, (s32)SetRangeRecordVector); p++;
    PropInit::Set2(p, 6, 256, (s32)SetRangeRecordCode); p++;
    PropInit::Set6(p, (s32)SetGroupActivityModeEnabled, 0, 288, (s32)SetGroupActivityModeEnabled); p++;
    PropInit::Set5(p, 292, (s32)SetGroupActivityMode, (s32)GetGroupActivityMode, 4196, (s32)SetGroupActivityMode); p++;
    PropInit::Set2(p, 0, 256, (s32)SetPositionSourceEnabled); p++;
    PropInit::Set2(p, 4110, 256, (s32)SetPositionSourceMode); p++;
    PropInit::Set6(p, (s32)SetScaledPositionSpring, 1, 288, (s32)SetScaledPositionSpring); p++;
    PropInit::Set6(p, (s32)SetPositionSpring, 9, 288, (s32)SetPositionSpring); p++;
    PropInit::Set6(p, (s32)SetScaledVelocitySpring, 1, 288, (s32)SetScaledVelocitySpring); p++;
    PropInit::Set6(p, (s32)SetVelocitySpring, 9, 288, (s32)SetVelocitySpring); p++;
    PropInit::Set2(p, 0, 256, (s32)SetOrientationSourceEnabled); p++;
    PropInit::Set2(p, 4110, 256, (s32)SetOrientationSourceMode); p++;
    PropInit::Set6(p, (s32)SetBaseAttachmentSortKey, 5, 288, (s32)SetBaseAttachmentSortKey); p++;
    PropInit::Set6(p, (s32)SetScaledRotationSpring, 1, 288, (s32)SetScaledRotationSpring); p++;
    PropInit::Set6(p, (s32)SetRotationSpring, 9, 288, (s32)SetRotationSpring); p++;
    PropInit::Set6(p, (s32)SetScaledSpinSpring, 1, 288, (s32)SetScaledSpinSpring); p++;
    PropInit::Set6(p, (s32)SetSpinSpring, 9, 288, (s32)SetSpinSpring); p++;
    PropInit::Set6(p, (s32)SetScaledPositionRamp, 1, 288, (s32)SetScaledPositionRamp); p++;
    PropInit::Set6(p, (s32)SetPositionRamp, 12, 288, (s32)SetPositionRamp); p++;
    PropInit::Set6(p, (s32)SetScaledRotationRamp, 1, 288, (s32)SetScaledRotationRamp); p++;
    PropInit::Set6(p, (s32)SetRotationRamp, 12, 288, (s32)SetRotationRamp); p++;
    PropInit::Set6(p, (s32)SetPositionRampAccelScale, 1, 288, (s32)SetPositionRampAccelScale); p++;
    PropInit::Set6(p, (s32)SetRotationRampAccelScale, 1, 288, (s32)SetRotationRampAccelScale); p++;
    PropInit::Set2(p, 4110, 256, (s32)SetDefaultPositionMode); p++;
    PropInit::Set2(p, 4110, 256, (s32)SetDefaultOrientationMode); p++;
    PropInit::Set7(p, 3, 0); p++;
    PropInit::Set2(p, 4110, 256, (s32)SetAimOrientationMode); p++;
    PropInit::Set5(p, 292, (s32)SetAimRange, (s32)GetAimRange, 1, (s32)SetAimRange); p++;
    PropInit::Set5(p, 292, (s32)SetAimYawCurve, (s32)GetAimYawCurve, 9, (s32)SetAimYawCurve); p++;
    PropInit::Set5(p, 292, (s32)SetAimYawLimits, (s32)GetAimYawLimits, 10, (s32)SetAimYawLimits); p++;
    PropInit::Set5(p, 292, (s32)SetAimPitchCurve, (s32)GetAimPitchCurve, 9, (s32)SetAimPitchCurve); p++;
    PropInit::Set5(p, 292, (s32)SetAimPitchLimits, (s32)GetAimPitchLimits, 10, (s32)SetAimPitchLimits); p++;
    PropInit::Set5(p, 292, (s32)SetAimNearKey, (s32)GetAimNearKey, 5, (s32)SetAimNearKey); p++;
    PropInit::Set5(p, 292, (s32)SetAimFarKey, (s32)GetAimFarKey, 5, (s32)SetAimFarKey); p++;
    PropInit::Set8(p, 6, 260, (s32)GetAimTargetId, (s32)SetAimTargetId); p++;
    PropInit::Set4(p, 36, 8194, (s32)GetAimTarget, (s32)SetAimTarget); p++;
    PropInit::Set1(p, (s32)ClearScriptAimHold, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptAimHold, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptValueAttachment, (s32)SetScriptValueAttachment, 18, 1025, 3); p++;
    PropInit::Set0(p, 4, -2147475455, (s32)TestChildrenAccepted); p++;
    PropInit::Set1(p, (s32)SetScriptElementsScrollScale, 0, 18, 1, 2); p++;
    PropInit::Set6(p, (s32)SetClass75ObjectCount, 4127, 288, (s32)SetClass75ObjectCount); p++;
    PropInit::Set6(p, (s32)SetClass75ObjectScale, 1, 288, (s32)SetClass75ObjectScale); p++;
    PropInit::Set6(p, (s32)SetClass75ObjectField90, 0, 288, (s32)SetClass75ObjectField90); p++;
    PropInit::Set1(p, (s32)SetScriptCrossfadeRatioDeep, 0, 18, 1, 1); p++;
    PropInit::Set6(p, (s32)SetObjectRecordValue, 5, 288, (s32)SetObjectRecordValue); p++;
    PropInit::Set9(p, 32, 5, (s32)SetObjectTreeRecordValue); p++;
    PropInit::Set5(p, 292, (s32)SetColorPreset, (s32)GetColorPreset, 4160, (s32)SetColorPreset); p++;
    PropInit::Set5(p, 292, (s32)SetColorRecordFirstColor, (s32)GetColorRecordFirstColor, 2, (s32)SetColorRecordFirstColor); p++;
    PropInit::Set5(p, 292, (s32)SetColorRecordSecondColor, (s32)GetColorRecordSecondColor, 2, (s32)SetColorRecordSecondColor); p++;
    PropInit::Set5(p, 292, (s32)SetColorRecordFactor, (s32)GetColorRecordFactor, 1, (s32)SetColorRecordFactor); p++;
    PropInit::Set5(p, 292, (s32)RestartSoundWithId, (s32)GetSoundRecordId, 14, (s32)SetSoundRecordId); p++;
    PropInit::Set8(p, 1, 260, (s32)GetSoundOuterRange, (s32)SetSoundOuterRange); p++;
    PropInit::Set8(p, 1, 260, (s32)GetSoundInnerRange, (s32)SetSoundInnerRange); p++;
    PropInit::Set5(p, 292, (s32)SetPlayingSoundVolume, (s32)GetSoundRecordScale, 1, (s32)SetSoundRecordScale); p++;
    PropInit::Set5(p, 292, (s32)SetPlayingSoundPitch, (s32)GetSoundStartPitch, 1, (s32)SetSoundStartPitch); p++;
    PropInit::Set8(p, 10, 260, (s32)GetSoundRecordPair, (s32)SetSoundRecordPair); p++;
    PropInit::Set1(p, (s32)StartScriptSoundWithParams, 0, 18, 1, 5); p++;
    PropInit::Set1(p, (s32)StopScriptPlayingSound, 0, 18, 1, 0); p++;
    PropInit::Set8(p, 1, 260, (s32)GetSoundStartParam, (s32)SetSoundStartParam); p++;
    PropInit::Set5(p, 292, (s32)SetTintRgb, (s32)GetTintRgb, 4163, (s32)SetTintRgb); p++;
    PropInit::Set5(p, 292, (s32)SetTintByte0, (s32)GetTintByte0, 4163, (s32)SetTintByte0); p++;
    PropInit::Set5(p, 292, (s32)SetTintByte1, (s32)GetTintByte1, 4163, (s32)SetTintByte1); p++;
    PropInit::Set5(p, 292, (s32)SetTintByte2, (s32)GetTintByte2, 4163, (s32)SetTintByte2); p++;
    PropInit::Set5(p, 292, (s32)SetTintByte3, (s32)GetTintByte3, 4163, (s32)SetTintByte3); p++;
    PropInit::Set5(p, 292, (s32)SetTintByte4, (s32)GetTintByte4, 4163, (s32)SetTintByte4); p++;
    PropInit::Set9(p, 32, 6, (s32)SelectValueEntryByKey); p++;
    PropInit::Set1(p, (s32)FadeInScriptPlacedObject, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)FadeOutScriptPlacedObject, 0, 18, 1, 1); p++;
    PropInit::Set8(p, 0, 258, 660, (s32)SetPlacedObjectFrameStepClock); p++;
    PropInit::Set1(p, (s32)FindScriptObjectHandle, 0, 8339, 1, 1); p++;
    PropInit::Set1(p, (s32)FindScriptObjectAnimationPlayer, 0, 8338, 1, 1); p++;
    PropInit::Set1(p, (s32)FindScriptTrackPlayer, 0, 8338, 1, 0); p++;
    PropInit::Set6(p, (s32)SetObjectCameraTracked, 0, 288, (s32)SetObjectCameraTracked); p++;
    PropInit::Set1(p, (s32)CopyScriptPlacedObjectFrame, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 292, (s32)SetPlacedObjectSpecialFlag, (s32)GetPlacedObjectSpecialFlag, 0, (s32)SetPlacedObjectSpecialFlag); p++;
    PropInit::Set1(p, (s32)SetScriptFollowObjects, 0, 18, 1, 2); p++;
    PropInit::Set4(p, 34, 1, 872, (s32)SetColliderMass); p++;
    PropInit::Set6(p, (s32)SetColliderSurfaceKind, 4111, 288, (s32)SetColliderSurfaceKind); p++;
    PropInit::Set5(p, 146, 848, 848, 2, 848); p++;
    PropInit::Set2(p, 0, 256, (s32)ResetColliderAnchors); p++;
    PropInit::Set6(p, (s32)SetColliderTurnAnchorPreset, 4096, 288, (s32)SetColliderTurnAnchorPreset); p++;
    PropInit::Set6(p, (s32)SetColliderMoveAnchorPreset, 4096, 288, (s32)SetColliderMoveAnchorPreset); p++;
    PropInit::Set2(p, 1, 256, (s32)SetColliderOverrideRadius); p++;
    PropInit::Set10(p, 1, 2194, 864, 864, 864, 0.5f); p++;
    PropInit::Set10(p, 1, 2194, 868, 868, 868, 1.0f); p++;
    PropInit::Set6(p, (s32)SetColliderFlagBit47, 0, 288, (s32)SetColliderFlagBit47); p++;
    PropInit::Set2(p, 0, 256, (s32)SetColliderFlagBit48); p++;
    PropInit::Set6(p, (s32)SetColliderGravityDisabled, 0, 288, (s32)SetColliderGravityDisabled); p++;
    PropInit::Set6(p, (s32)SetColliderTreeContactsDropped, 0, 288, (s32)SetColliderTreeContactsDropped); p++;
    PropInit::Set6(p, (s32)SetColliderContactsDropped, 0, 288, (s32)SetColliderContactsDropped); p++;
    PropInit::Set6(p, (s32)SetColliderKindContactsDropped, 0, 288, (s32)SetColliderKindContactsDropped); p++;
    PropInit::Set0(p, 4, -2147475453, (s32)CollectContactingPartsToScriptList); p++;
    PropInit::Set5(p, 146, 1248, 1248, 4129, 1248); p++;
    PropInit::Set0(p, 2, 1, 976); p++;
    PropInit::Set2(p, 4132, 256, (s32)SetColliderFlagNibble32); p++;
    PropInit::Set1(p, (s32)SetScriptColliderFlagNibble36, (s32)SetScriptColliderFlagNibble36, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)TestScriptPointInsideCollider, 0, 0, 1, 1); p++;
    PropInit::Set5(p, 292, (s32)SetColliderFlagBit52, (s32)GetColliderFlagBit52, 0, (s32)SetColliderFlagBit52); p++;
    PropInit::Set4(p, 18, 2, 64, 64); p++;
    PropInit::Set4(p, 18, 4, 80, 80); p++;
    PropInit::Set0(p, 4, 2, (s32)GetObjectWorldPosition); p++;
    PropInit::Set0(p, 4, 4, (s32)GetObjectWorldRotation); p++;
    PropInit::Set4(p, 18, 2, 128, 128); p++;
    PropInit::Set5(p, 146, 128, 128, 1, 128); p++;
    PropInit::Set5(p, 146, 132, 132, 1, 132); p++;
    PropInit::Set5(p, 146, 136, 136, 1, 136); p++;
    PropInit::Set8m(p, 0, 144, 130); p++;
    PropInit::Set8m(p, 0, 148, 130); p++;
    PropInit::Set5(p, 146, 176, 176, 6, 176); p++;
    PropInit::Set5(p, 290, (s32)StoreValueAndMarkSet, 156, 1, (s32)StoreValueAndMarkSet); p++;
    PropInit::Set1(p, (s32)SetScriptTransformObjectKeyedValue, (s32)SetScriptTransformObjectKeyedValue, 18, 1025, 4); p++;
    PropInit::Set1(p, (s32)PlaceScriptAtArrivalPoint, 0, 18, 1, 0); p++;
    PropInit::Set11(p, 768, -1, 768, 768, 6, 2194); p++;
    PropInit::Set11(p, 772, -1, 772, 772, 4159, 2194); p++;
    PropInit::Set11(p, 780, -1, 780, 780, 6, 2194); p++;
    PropInit::Set11(p, 792, 0, 792, 792, 4106, 2194); p++;
    PropInit::Set11(p, 800, 0, 800, 800, 1, 2194); p++;
    PropInit::Set11(p, 720, 0, 720, 720, 0, 2194); p++;
    PropInit::Set11(p, 724, 0, 724, 724, 0, 2194); p++;
    PropInit::Set11(p, 736, 0, 736, 736, 0, 2194); p++;
    PropInit::Set11(p, 728, 0, 728, 728, 0, 2194); p++;
    PropInit::Set11(p, 732, 0, 732, 732, 0, 2194); p++;
    PropInit::Set5(p, 146, 804, 804, 1, 804); p++;
    PropInit::Set1(p, (s32)StartScriptObjectSubGroupFinish, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 34, 4200, 740, (s32)SetObjectSubGroupState); p++;
    PropInit::Set4(p, 18, 2, 64, 64); p++;
    PropInit::Set0(p, 4, 2, (s32)ConvertPositionToWorld); p++;
    PropInit::Set12(p, 2176, 68, 0, 4098); p++;
    PropInit::Set12(p, 2176, 72, 0, 0); p++;
    PropInit::Set12(p, 2176, 76, 0, 0); p++;
    PropInit::Set2(p, 5, 128, 120); p++;
    PropInit::Set10(p, 1, 2194, 124, 124, 124, 1.0f); p++;
    PropInit::Set2(p, 9, 128, 128); p++;
    PropInit::Set2(p, 10, 128, 144); p++;
    PropInit::Set1(p, (s32)CreateScriptAnimationPlayer, 0, 8338, 1, 4); p++;
    PropInit::Set1(p, (s32)FindOrCreateScriptSeekedAnimationPlayer, 0, 8338, 1, 5); p++;
    PropInit::Set1(p, (s32)GetScriptAnimationMarkerTime, 0, 1, 1, 1); p++;
    PropInit::Set0(p, 2, 1, 52); p++;
    PropInit::Set8m(p, 0, 80, 130); p++;
    PropInit::Set0(p, 2, 8323, 8); p++;
    PropInit::Set0(p, 2, 8194, 12); p++;
    PropInit::Set0(p, 2, 1, 20); p++;
    PropInit::Set4(p, 34, 1, 24, (s32)SetAnimationPlayerSpeed); p++;
    PropInit::Set4(p, 34, 1, 28, (s32)SetAnimationPlayerSpeedScale); p++;
    PropInit::Set4(p, 34, 5, 232, (s32)SetAttachmentSortKeys); p++;
    PropInit::Set4(p, 34, 0, 36, (s32)SetAnimationPlayerPadSelect); p++;
    PropInit::Set1(p, (s32)SeekScriptAnimationPlayer, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)StopScriptAnimationPlayer, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ApplyScriptListedPoseSources, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)ReleaseScriptPlayerAttachment, 0, 18, 1, 2); p++;
    PropInit::Set11(p, 1408, 1, 1408, 1408, 0, 2194); p++;
    PropInit::Set11(p, 1420, 1, 1420, 1420, 0, 2194); p++;
    PropInit::Set5(p, 146, 1392, 1392, 2, 1392); p++;
    PropInit::Set3(p, 6, 4352, (s32)AddTrackedKey, (s32)GetAttachedSetTrackedNodes); p++;
    PropInit::Set13(p, (s32)AddTrackedNode, 4128, 8193, (s32)GetAttachedSetTrackedNodes); p++;
    PropInit::Set13(p, (s32)RemoveTrackedNode, 4128, 8193, (s32)GetAttachedSetTrackedNodes); p++;
    PropInit::Set1(p, (s32)ClearScriptAttachedSetTrackedNodes, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1432, 1432, 1, 1432); p++;
    PropInit::Set5(p, 146, 1436, 1436, 0, 1436); p++;
    PropInit::Set5(p, 146, 1412, 1412, 0, 1412); p++;
    PropInit::Set5(p, 146, 1416, 1416, 0, 1416); p++;
    PropInit::Set2(p, 6, 256, (s32)AddMaskedColliderKeyKind0); p++;
    PropInit::Set2(p, 6, 256, (s32)AddMaskedColliderKeyKind1); p++;
    PropInit::Set2(p, 6, 256, (s32)AddMaskedColliderKeyKind2); p++;
    PropInit::Set2(p, 6, 256, (s32)AddMaskedColliderKeyKind3); p++;
    PropInit::Set11(p, 1660, 0, 1660, 1660, 0, 2194); p++;
    PropInit::Set5(p, 146, 1572, 1572, 1, 1572); p++;
    PropInit::Set12(p, 2176, 1592, -1, 6); p++;
    PropInit::Set5(p, 146, 1576, 1576, 10, 1576); p++;
    PropInit::Set10(p, 1, 2194, 1584, 1584, 1584, 300.0f); p++;
    PropInit::Set10(p, 1, 2194, 1588, 1588, 1588, 3.0f); p++;
    PropInit::Set2(p, 6, 256, (s32)AddAcceptedObjectId); p++;
    PropInit::Set2(p, 7, 256, (s32)AddAcceptedKind); p++;
    PropInit::Set2(p, 7, 256, (s32)AddMaskedColliderListEntry); p++;
    PropInit::Set5(p, 292, (s32)SetAcceptsPlayer, (s32)GetAcceptsPlayer, 0, (s32)SetAcceptsPlayer); p++;
    PropInit::Set5(p, 292, (s32)SetAcceptsFlaggedObjects, (s32)GetAcceptsFlaggedObjects, 0, (s32)SetAcceptsFlaggedObjects); p++;
    PropInit::Set5(p, 146, 1676, 1676, 5, 1676); p++;
    PropInit::Set1(p, (s32)HandleScriptMaskedColliderActivation, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 34, 0, 1664, (s32)SetObjectHold); p++;
    PropInit::Set5(p, 146, 1684, 1684, 0, 1684); p++;
    PropInit::Set11(p, 1564, 1, 1564, 1564, 4162, 2194); p++;
    PropInit::Set5(p, 146, 1568, 1568, 1, 1568); p++;
    PropInit::Set5(p, 146, 1688, 1688, 5, 1688); p++;
    PropInit::Set5(p, 146, 1696, 1696, 2, 1696); p++;
    PropInit::Set5(p, 146, 1712, 1712, 0, 1712); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)GetMaskedColliderSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)GetMaskedColliderSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)GetMaskedColliderSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)GetMaskedColliderSoundParams); p++;
    PropInit::Set2(p, 6, 128, 1556); p++;
    PropInit::Set5(p, 146, 1668, 1668, 0, 1668); p++;
    PropInit::Set5(p, 146, 1728, 1728, 1, 1728); p++;
    PropInit::Set5(p, 146, 1732, 1732, 4096, 1732); p++;
    PropInit::Set5(p, 146, 1736, 1736, 4096, 1736); p++;
    PropInit::Set4(p, 18, 8195, 1740, 1740); p++;
    PropInit::Set5(p, 146, 1744, 1744, 4124, 1744); p++;
    PropInit::Set10(p, 1, 2194, 1372, 1372, 1372, 1.5f); p++;
    PropInit::Set10(p, 1, 2194, 1368, 1368, 1368, 10.0f); p++;
    PropInit::Set5(p, 290, (s32)SetTimedState, 1360, 4146, (s32)SetTimedState); p++;
    PropInit::Set5(p, 146, 1380, 1380, 0, 1380); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendTriggerZoneFirstQueue); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendTriggerZoneSecondQueue); p++;
    PropInit::Set2(p, 6, 256, (s32)AddIncludedId); p++;
    PropInit::Set2(p, 6, 256, (s32)AddExcludedId); p++;
    PropInit::Set2(p, 7, 256, (s32)AddIncludedKind); p++;
    PropInit::Set2(p, 7, 256, (s32)AddExcludedKind); p++;
    PropInit::Set10(p, 1, 2194, 1660, 1660, 1660, 1.0f); p++;
    PropInit::Set12(p, 2176, 1360, 0, 4105); p++;
    PropInit::Set15(p, 1644, 1.0f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 1672, 0, 0); p++;
    PropInit::Set12(p, 2176, 1676, 0, 0); p++;
    PropInit::Set12(p, 2176, 1680, 0, 0); p++;
    PropInit::Set12(p, 2176, 1648, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptTriggerZoneEntry, (s32)SetScriptTriggerZoneEntry, 18, 1025, 4); p++;
    PropInit::Set2(p, 6, 128, 1684); p++;
    PropInit::Set4(p, 34, 4187, 1664, (s32)SetTriggerZoneMode); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendZoneColliderFirstQueue); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendZoneColliderSecondQueue); p++;
    PropInit::Set10(p, 1, 2194, 1768, 1768, 1768, 1.0f); p++;
    PropInit::Set15(p, 1752, 1.0f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 1780, 1, 0); p++;
    PropInit::Set12(p, 2176, 1784, 0, 0); p++;
    PropInit::Set12(p, 2176, 1756, 0, 0); p++;
    PropInit::Set11(p, 1932, 1, 1932, 1932, 0, 2194); p++;
    PropInit::Set2(p, 6, 256, (s32)AddZoneColliderId); p++;
    PropInit::Set1(p, (s32)SetScriptZoneColliderEntry, (s32)SetScriptZoneColliderEntry, 18, 1025, 4); p++;
    PropInit::Set11(p, 1936, 0, 1936, 1936, 0, 2194); p++;
    PropInit::Set0(p, 4, -2147475455, (s32)TestListedEntriesAccepted); p++;
    PropInit::Set2(p, 6, 128, 1792); p++;
    PropInit::Set4(p, 34, 4187, 1772, (s32)SetZoneColliderMode); p++;
    PropInit::Set5(p, 290, (s32)SetSwitchedColliderEnabled, 1360, 0, (s32)SetSwitchedColliderEnabled); p++;
    PropInit::Set1(p, (s32)ActivateScriptSwitchedColliderUnlessActive, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)TestScriptRequestBlocked, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 4, 4198, (s32)StoreSwitchedColliderAccepted); p++;
    PropInit::Set2(p, 6, 256, (s32)AddLookupId); p++;
    PropInit::Set15(p, 1360, 100.0f, 1, 2176); p++;
    PropInit::Set2(p, 6, 256, (s32)AddObjectSetKey); p++;
    PropInit::Set5(p, 146, 1368, 1368, 0, 1368); p++;
    PropInit::Set2(p, 6, 256, (s32)AddStateTriggerCountedId); p++;
    PropInit::Set2(p, 6, 256, (s32)AddStateTriggerItemId); p++;
    PropInit::Set2(p, 6, 256, (s32)AddStateTriggerAgentId); p++;
    PropInit::Set11(p, 1576, 0, 1576, 1576, 0, 2194); p++;
    PropInit::Set11(p, 1376, 0, 1376, 1376, 1, 2194); p++;
    PropInit::Set0(p, 2, 4137, 1360); p++;
    PropInit::Set0(p, 4, -2147475408, (s32)TestStateTriggerItemsAccepted); p++;
    PropInit::Set1(p, (s32)SetScriptStateTriggerStateFromMessage, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)AddScriptStateTriggerTableEntry, (s32)AddScriptStateTriggerTableEntry, 18, 1025, 4); p++;
    PropInit::Set0(p, 2, 8239, 1728); p++;
    PropInit::Set2(p, 6, 256, (s32)AddTimedObjectAcceptedObjectId); p++;
    PropInit::Set2(p, 6, 256, (s32)AddTimedObjectExcludedObjectId); p++;
    PropInit::Set2(p, 7, 256, (s32)AddTimedObjectAcceptedClassId); p++;
    PropInit::Set2(p, 7, 256, (s32)AddTimedObjectExcludedClassId); p++;
    PropInit::Set11(p, 1460, 0, 1460, 1460, 0, 2194); p++;
    PropInit::Set10(p, 1, 2194, 1464, 1464, 1464, 1.0f); p++;
    PropInit::Set10(p, 1, 2194, 1468, 1468, 1468, 1.0f); p++;
    PropInit::Set11(p, 1376, 1, 1376, 1376, 4140, 2194); p++;
    PropInit::Set0(p, 2, 8239, 1360); p++;
    PropInit::Set0(p, 2, 4140, 1368); p++;
    PropInit::Set0(p, 2, 4139, 1364); p++;
    PropInit::Set4(p, 18, 0, 1472, 1472); p++;
    PropInit::Set1(p, (s32)SetScriptTimedObjectMode, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)RequestScriptTimedObjectEnd, 0, 18, 1, 0); p++;
    PropInit::Set11(p, 1488, 0, 1488, 1488, 4141, 2194); p++;
    PropInit::Set10(p, 1, 2194, 2796, 2796, 2796, 0.25f); p++;
    PropInit::Set1(p, (s32)SetScriptTimedGroupFadeInTime, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SetScriptTimedGroupFadeOutTime, 0, 18, 1, 1); p++;
    PropInit::Set10(p, 1, 2194, 1504, 1504, 1504, 0.25f); p++;
    PropInit::Set10(p, 1, 2194, 1508, 1508, 1508, 1.0f); p++;
    PropInit::Set10(p, 1, 2194, 1512, 1512, 1512, 0.75f); p++;
    PropInit::Set0(p, 2, 4142, 1496); p++;
    PropInit::Set5(p, 146, 1488, 1488, 5, 1488); p++;
    PropInit::Set5(p, 146, 1492, 1492, 5, 1492); p++;
    PropInit::Set5(p, 146, 1496, 1496, 1, 1496); p++;
    PropInit::Set11(p, 1500, 0, 1500, 1500, 4143, 2194); p++;
    PropInit::Set5(p, 146, 1504, 1504, 5, 1504); p++;
    PropInit::Set5(p, 146, 1508, 1508, 5, 1508); p++;
    PropInit::Set5(p, 146, 1512, 1512, 1, 1512); p++;
    PropInit::Set11(p, 1516, 0, 1516, 1516, 4143, 2194); p++;
    PropInit::Set5(p, 146, 1520, 1520, 5, 1520); p++;
    PropInit::Set5(p, 146, 1524, 1524, 5, 1524); p++;
    PropInit::Set5(p, 146, 1528, 1528, 1, 1528); p++;
    PropInit::Set11(p, 1532, 0, 1532, 1532, 4143, 2194); p++;
    PropInit::Set5(p, 146, 1536, 1536, 5, 1536); p++;
    PropInit::Set10(p, 1, 2194, 1540, 1540, 1540, 8.0f); p++;
    PropInit::Set10(p, 1, 2194, 1544, 1544, 1544, 2.0f); p++;
    PropInit::Set10(p, 1, 2194, 1548, 1548, 1548, 2.0f); p++;
    PropInit::Set8m(p, 4113, 160, 130); p++;
    PropInit::Set5(p, 146, 164, 164, 1, 164); p++;
    PropInit::Set5(p, 146, 168, 168, 14, 168); p++;
    PropInit::Set5(p, 146, 172, 172, 14, 172); p++;
    PropInit::Set5(p, 146, 176, 176, 1, 176); p++;
    PropInit::Set5(p, 146, 184, 184, 0, 184); p++;
    PropInit::Set5(p, 146, 180, 180, 1, 180); p++;
    PropInit::Set2(p, 6, 256, (s32)AddIdFilterObjectId); p++;
    PropInit::Set2(p, 7, 256, (s32)AddIdFilterClassId); p++;
    PropInit::Set2(p, 0, 128, 1360); p++;
    PropInit::Set2(p, 6, 128, 1424); p++;
    PropInit::Set5(p, 290, (s32)SetEffectSpawnerLimit, 728, 5, (s32)SetEffectSpawnerLimit); p++;
    PropInit::Set5(p, 290, (s32)SetEffectSpawnerContinuous, 776, 0, (s32)SetEffectSpawnerContinuous); p++;
    PropInit::Set14(p, 4242, 4148, 724, 724, 724, (s32)MarkEffectSpawnerChanged); p++;
    PropInit::Set14(p, 4242, 10, 732, 732, 732, (s32)MarkEffectSpawnerChanged); p++;
    PropInit::Set14(p, 4242, 1, 756, 756, 756, (s32)MarkEffectSpawnerChanged); p++;
    PropInit::Set14(p, 4242, 1, 744, 744, 744, (s32)MarkEffectSpawnerChanged); p++;
    PropInit::Set14(p, 4242, 10, 748, 748, 748, (s32)MarkEffectSpawnerChanged); p++;
    PropInit::Set4(p, 36, 0, (s32)GetEffectSpawnerInactive, (s32)SetEffectSpawnerDisabled); p++;
    PropInit::Set8m(p, 0, 740, 130); p++;
    PropInit::Set8m(p, 6, 760, 130); p++;
    PropInit::Set8m(p, 6, 764, 130); p++;
    PropInit::Set8m(p, 6, 768, 130); p++;
    PropInit::Set8m(p, 6, 772, 130); p++;
    PropInit::Set8m(p, 6, 784, 130); p++;
    PropInit::Set1(p, (s32)SetScriptEffectSpawnerActiveFor, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SetScriptEffectSpawnerActiveForever, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptEffectSpawnerInactive, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)GetEffectSpawnerActive); p++;
    PropInit::Set16(p, 4118, 16, 16, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 2, 32, 32, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 2, 32, 32, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 2, 48, 48, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set8m(p, 6, 780, 130); p++;
    PropInit::Set14(p, 4242, 4119, 80, 80, 80, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 112, 112, 112, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4121, 128, 128, 128, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 160, 160, 160, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 168, 168, 168, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 176, 176, 176, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 192, 192, 192, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 196, 196, 196, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 208, 208, 208, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4120, 224, 224, 224, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 228, 228, 228, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 5, 236, 236, 236, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 240, 240, 240, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 244, 244, 244, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 248, 248, 248, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 256, 256, 256, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 272, 272, 272, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set16(p, 4117, 288, 288, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set2(p, 4115, 256, (s32)SetEffectSpawnerKind); p++;
    PropInit::Set16(p, 4115, 436, 436, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 10, 464, 464, 464, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 448, 448, 448, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set16(p, 4116, 484, 484, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 1, 488, 488, 488, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set16(p, 6, 308, 308, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 9, 320, 320, 320, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 336, 336, 336, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 352, 352, 352, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 368, 368, 368, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 372, 372, 372, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 376, 376, 376, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4149, 304, 304, 304, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set16(p, 6, 392, 392, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 4150, 400, 400, 400, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 404, 404, 404, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4151, 408, 408, 408, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 412, 412, 412, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 420, 420, 420, (s32)GetOwnSpawnRecord); p++;
    PropInit::Set1(p, 0, (s32)AddScriptSpawnRangeEntry, 18, 1024, 6); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 0, 500, 500, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 6, 496, 496, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 496, 496, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 504, 504, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)GetOwnSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 4118, 16, 16, 16, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 48, 48, 48, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set8m(p, 6, 148, 130); p++;
    PropInit::Set8m(p, 6, 152, 130); p++;
    PropInit::Set14(p, 4242, 4119, 80, 80, 80, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 112, 112, 112, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4121, 128, 128, 128, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 160, 160, 160, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 168, 168, 168, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 228, 228, 228, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 5, 236, 236, 236, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 240, 240, 240, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 248, 248, 248, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set1(p, 0, (s32)AddScriptRecordMemberRangeEntry, 18, 1024, 6); p++;
    PropInit::Set5(p, 146, 164, 164, 10, 164); p++;
    PropInit::Set8m(p, 6, 172, 130); p++;
    PropInit::Set8m(p, 6, 180, 130); p++;
    PropInit::Set8m(p, 6, 176, 130); p++;
    PropInit::Set5(p, 146, 184, 184, 1, 184); p++;
    PropInit::Set5(p, 146, 188, 188, 0, 188); p++;
    PropInit::Set14(p, 4242, 2, 176, 176, 176, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 192, 192, 192, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 196, 196, 196, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 2, 208, 208, 208, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4120, 224, 224, 224, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 244, 244, 244, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 256, 256, 256, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 272, 272, 272, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set16(p, 4117, 288, 288, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set2(p, 4115, 256, (s32)SetOwnedSpawnRecordKind); p++;
    PropInit::Set16(p, 4115, 436, 436, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 10, 464, 464, 464, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 448, 448, 448, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set16(p, 4116, 484, 484, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 1, 488, 488, 488, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set16(p, 6, 308, 308, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 9, 320, 320, 320, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 336, 336, 336, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 9, 352, 352, 352, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 368, 368, 368, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 372, 372, 372, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 376, 376, 376, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4149, 304, 304, 304, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set16(p, 6, 392, 392, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 4150, 400, 400, 400, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 1, 404, 404, 404, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 4151, 408, 408, 408, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 10, 412, 412, 412, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set14(p, 4242, 0, 420, 420, 420, (s32)GetOwnedSpawnRecord); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 0, 500, 500, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)GetOrCreateSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)GetOrCreateSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)GetOrCreateSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)GetOrCreateSoundParams); p++;
    PropInit::Set1(p, (s32)SendScriptEmptyMessageC7A, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SendScriptTwoVectorMessageC7A, 0, 18, 1, 6); p++;
    PropInit::Set16(p, 6, 496, 496, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 496, 496, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 1, 504, 504, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)GetOwnedSpawnRecord, 4226); p++;
    PropInit::Set1(p, (s32)SendScriptEmptyMessageC78, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SendScriptTwoVectorMessageC78, 0, 18, 1, 6); p++;
    PropInit::Set5(p, 290, (s32)SetConeVolumeMode, 720, 4122, (s32)SetConeVolumeMode); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeColor, 736, 2, 736); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeSecondLevel, 752, 1, 752); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeThirdLevel, 756, 1, 756); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeFirstAngle, 760, 1, 760); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeSecondAngle, 764, 1, 764); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeThirdAngle, 768, 1, 768); p++;
    PropInit::Set5(p, 290, (s32)SetConeVolumeDirection, 784, 2, (s32)SetConeVolumeDirection); p++;
    PropInit::Set5(p, 290, (s32)SetConeVolumeValue, 772, 0, (s32)SetConeVolumeValue); p++;
    PropInit::Set5(p, 290, (s32)SetConeVolumeValue, 772, 0, (s32)SetConeVolumeValue); p++;
    PropInit::Set5(p, 146, 776, 776, 0, 776); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeRange, 816, 10, 816); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeOuterAngle, 824, 1, 824); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeInnerAngle, 828, 1, 828); p++;
    PropInit::Set5(p, 162, (s32)SetConeVolumeVector340, 832, 2, 832); p++;
    PropInit::Set5(p, 292, (s32)SetConeVolumeOuterLevels, (s32)GetConeVolumeSecondLevel, 1, (s32)SetConeVolumeOuterLevels); p++;
    PropInit::Set5(p, 292, (s32)SetConeVolumeColorRgb, (s32)GetConeVolumeColorRgb, 2, (s32)SetConeVolumeColorRgb); p++;
    PropInit::Set7(p, 0, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set2(p, 0, 128, 68); p++;
    PropInit::Set1(p, (s32)CreateScriptStateWalker, 0, 8339, 1, 3); p++;
    PropInit::Set0(p, 2, 8194, 28); p++;
    PropInit::Set4(p, 36, 6, (s32)GetStateWalkerTargetKey, (s32)SetStateWalkerTarget); p++;
    PropInit::Set0(p, 4, 6, (s32)GetStateWalkerCurrentKey); p++;
    PropInit::Set0(p, 4, 6, (s32)GetStateWalkerNextKey); p++;
    PropInit::Set4(p, 34, 1, 56, (s32)SetStateWalkerSpeed); p++;
    PropInit::Set0(p, 2, 8338, 36); p++;
    PropInit::Set9(p, 32, 6, (s32)TeleportStateWalker); p++;
    PropInit::Set1(p, (s32)DestroyScriptStateWalker, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 2, 8328, 24); p++;
    PropInit::Set12(p, 2176, 7544, 1, 0); p++;
    PropInit::Set15(p, 7548, 1.0f, 1, 2176); p++;
    PropInit::Set5(p, 162, (s32)SetWorldLightingParamA, 7532, 1, 7532); p++;
    PropInit::Set5(p, 162, (s32)SetWorldLightingParamB, 7528, 1, 7528); p++;
    PropInit::Set2(p, 13, 128, 7524); p++;
    PropInit::Set2(p, 1, 256, (s32)SnapCurrentCameraZoom); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraNearDistance); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraFarDistance); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraFogNear); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraFogFar); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraFogStrength); p++;
    PropInit::Set2(p, 13, 256, (s32)SetCurrentCameraFogColor); p++;
    PropInit::Set2(p, 1, 256, (s32)SetCurrentCameraDistanceScale); p++;
    PropInit::Set10(p, 1, 2194, 8968, 8968, 8968, 15.0f); p++;
    PropInit::Set10(p, 1, 2194, 8972, 8972, 8972, 180.0f); p++;
    PropInit::Set4(p, 34, 1, 8984, (s32)SetWorldSoundLevel); p++;
    PropInit::Set4(p, 34, 1, 9036, (s32)SetWorldValueAndTarget); p++;
    PropInit::Set4(p, 34, 1, 9040, (s32)SetWorldValueTarget); p++;
    PropInit::Set14(p, 4242, 5, 4, 4, 4, (s32)GetScatterController); p++;
    PropInit::Set14(p, 4242, 5, 8, 8, 8, (s32)GetScatterController); p++;
    PropInit::Set14(p, 4242, 5, 12, 12, 12, (s32)GetScatterController); p++;
    PropInit::Set14(p, 4242, 5, 16, 16, 16, (s32)GetScatterController); p++;
    PropInit::Set1(p, (s32)ScatterScriptRandomObjects, 0, 18, 1, 3); p++;
    PropInit::Set4(p, 36, 1, (s32)GetGameStateDeltaTime, (s32)SetScatterLevelBuiltin); p++;
    PropInit::Set4(p, 36, 1, (s32)GetCurrentScatterLevel, (s32)SetCurrentScatterLevel); p++;
    PropInit::Set6(p, (s32)AddWorldSoundEntry, 14, 288, (s32)AddWorldSoundEntry); p++;
    PropInit::Set6(p, (s32)SetLastWorldSoundEntryFromPoint, 10, 288, (s32)SetLastWorldSoundEntryFromPoint); p++;
    PropInit::Set6(p, (s32)SetLastWorldSoundEntryValues, 10, 288, (s32)SetLastWorldSoundEntryValues); p++;
    PropInit::Set1(p, 0, (s32)SetScriptIopChannel2Setting, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)PushScriptIopChannel2Setting, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)PopScriptIopChannel2Setting, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)TestScriptLevelEntryFlag1, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)TestScriptLevelEntryFlag2, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)TestScriptLevelEntryFlag4, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)TestScriptLevelEntryFlag8, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)CheckScriptEntryOneBitRequirement, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)CheckScriptEntryTwoBitRequirement, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)CheckScriptEntryThreeBitRequirement, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)SetScriptEntrySlotValue, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)GetScriptEntrySlotValue, 0, 5, 1, 2); p++;
    PropInit::Set1(p, (s32)IsScriptLevelRecordComplete, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)IsScriptLevelDone, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)RecomputeScriptSaveCompletion, 0, 5, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)GetHasStreamVoice); p++;
    PropInit::Set1(p, (s32)PopScriptActiveSequenceElement, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ShowScriptPauseMenuPageWith, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)ShowScriptCountedScreenElement, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)HideScriptCountedScreenElement, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 9044, 9044, 0, 9044); p++;
    PropInit::Set1(p, (s32)PushScriptSoundLevel, 0, 5, 1, 1); p++;
    PropInit::Set1(p, (s32)RemoveScriptSoundLevel, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SetScriptCachedVoiceParam, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)GetScriptCachedVoiceParam, 0, 5, 1, 1); p++;
    PropInit::Set1(p, (s32)RefreshScriptCachedVoiceParam, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)AcquireScriptPadSelectFlag, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ReleaseScriptPadSelectFlag, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ClearScriptWorldFlagBit, (s32)ClearScriptWorldFlagBit, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)SetScriptWorldFlagBit, (s32)SetScriptWorldFlagBit, 18, 1025, 1); p++;
    PropInit::Set0(p, 4, 5, (s32)GetSaveSpareCount); p++;
    PropInit::Set0(p, 4, 5, (s32)GetReserveUnitCount); p++;
    PropInit::Set4(p, 34, 2, 64, (s32)SetCameraPosition); p++;
    PropInit::Set4(p, 34, 4, 128, (s32)SetCameraOrientation); p++;
    PropInit::Set4(p, 34, 1, 452, (s32)SnapCameraZoom); p++;
    PropInit::Set4(p, 18, 1, 456, 456); p++;
    PropInit::Set4(p, 18, 12, 464, 464); p++;
    PropInit::Set4(p, 34, 1, 484, (s32)SetCameraNearDistance); p++;
    PropInit::Set4(p, 34, 1, 488, (s32)SetCameraFarDistance); p++;
    PropInit::Set4(p, 34, 1, 504, (s32)SetCameraFogNear); p++;
    PropInit::Set4(p, 34, 1, 508, (s32)SetCameraFogFar); p++;
    PropInit::Set4(p, 34, 1, 512, (s32)SetCameraFogStrength); p++;
    PropInit::Set4(p, 34, 1, 448, (s32)SetCameraDistanceScale); p++;
    PropInit::Set1(p, (s32)PushScriptCameraStackValue, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)PopScriptCameraStackValue, 0, 4177, 1, 0); p++;
    PropInit::Set1(p, (s32)PeekScriptCameraStackValue, 0, 4177, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptCameraControllerSettings, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)RecordScriptCameraTimestamp, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)RequestScriptPlainCameraSnap, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)TestScriptSphereInCameraView, 0, 0, 1, 3); p++;
    PropInit::Set2(p, 6, 128, 720); p++;
    PropInit::Set2(p, 2, 128, 736); p++;
    PropInit::Set2(p, 2, 128, 752); p++;
    PropInit::Set2(p, 2, 128, 768); p++;
    PropInit::Set1(p, (s32)PushScriptObjectCameraController, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)RemoveScriptObjectCameraController, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 720, 720, 0, 720); p++;
    PropInit::Set5(p, 146, 1364, 1364, 4124, 1364); p++;
    PropInit::Set3(p, 6, 4352, (s32)AddTrackedKey, (s32)GetContactTrackerRecord); p++;
    PropInit::Set13(p, (s32)AddTrackedNode, 4128, 8193, (s32)GetContactTrackerRecord); p++;
    PropInit::Set13(p, (s32)RemoveTrackedNode, 4128, 8193, (s32)GetContactTrackerRecord); p++;
    PropInit::Set1(p, (s32)ClearScriptTrackedNodes, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1368, 1368, 1, 1368); p++;
    PropInit::Set5(p, 146, 1372, 1372, 0, 1372); p++;
    PropInit::Set5(p, 146, 136, 136, 4127, 136); p++;
    PropInit::Set5(p, 146, 140, 140, 1, 140); p++;
    PropInit::Set5(p, 146, 144, 144, 0, 144); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendFlaggedObjectIdB); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendFlaggedObjectIdA); p++;
    PropInit::Set2(p, 6, 256, (s32)SetFlaggedChildId); p++;
    PropInit::Set1(p, (s32)CollectScriptNumberedItem, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1448, 1448, 1, 1448); p++;
    PropInit::Set0(p, 4, 0, (s32)GetNumberedItemFlag); p++;
    PropInit::Set5(p, 290, (s32)SetOffsetScale, 1360, 1, (s32)SetOffsetScale); p++;
    PropInit::Set10(p, 1, 2194, 92, 92, 92, 50.0f); p++;
    PropInit::Set11(p, 88, 0, 88, 88, 4131, 2194); p++;
    PropInit::Set5(p, 146, 104, 104, 0, 104); p++;
    PropInit::Set2(p, 6, 128, 96); p++;
    PropInit::Set5(p, 146, 108, 108, 0, 108); p++;
    PropInit::Set5(p, 146, 112, 112, 1, 112); p++;
    PropInit::Set5(p, 146, 116, 116, 0, 116); p++;
    PropInit::Set11(p, 64, 0, 64, 64, 4131, 2194); p++;
    PropInit::Set5(p, 146, 76, 76, 0, 76); p++;
    PropInit::Set2(p, 6, 128, 68); p++;
    PropInit::Set5(p, 146, 80, 80, 4164, 80); p++;
    PropInit::Set5(p, 146, 84, 84, 0, 84); p++;
    PropInit::Set5(p, 146, 88, 88, 1, 88); p++;
    PropInit::Set5(p, 146, 92, 92, 0, 92); p++;
    PropInit::Set10(p, 1, 2194, 1376, 1376, 1376, 50.0f); p++;
    PropInit::Set11(p, 1380, 10, 1380, 1380, 5, 2194); p++;
    PropInit::Set5(p, 146, 1384, 1384, 1, 1384); p++;
    PropInit::Set5(p, 146, 64, 64, 2, 64); p++;
    PropInit::Set5(p, 146, 80, 80, 14, 80); p++;
    PropInit::Set5(p, 146, 84, 84, 14, 84); p++;
    PropInit::Set5(p, 146, 88, 88, 4178, 88); p++;
    PropInit::Set7(p, 18, 0); p++;
    PropInit::Set5(p, 146, 96, 96, 0, 96); p++;
    PropInit::Set2(p, 6, 128, 100); p++;
    PropInit::Set4(p, 18, 8302, 104, 104); p++;
    PropInit::Set5(p, 146, 92, 92, 1, 92); p++;
    PropInit::Set5(p, 162, (s32)SetAgentPathObjectId, 2340, 6, 2340); p++;
    PropInit::Set5(p, 146, 1848, 1848, 10, 1848); p++;
    PropInit::Set5(p, 146, 1856, 1856, 10, 1856); p++;
    PropInit::Set5(p, 274, 1868, 1868, 1, (s32)SetAgentAngleLimitDegrees); p++;
    PropInit::Set1(p, 0, (s32)SetScriptAgentStateClipId, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)SetScriptAgentStateClip, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)GetScriptAgentStateClip, 0, 8323, 1, 1); p++;
    PropInit::Set5(p, 146, 2672, 2672, 1, 2672); p++;
    PropInit::Set1(p, 0, (s32)AddScriptAgentClipGroup, 18, 1024, 4); p++;
    PropInit::Set1(p, 0, (s32)AddScriptAgentMeshKey, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)AddScriptAgentExtraClip, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)ForceScriptAgentState, 0, 18, 1, 2); p++;
    PropInit::Set1(p, 0, (s32)SetScriptAgentSecondaryClipId, 18, 1024, 2); p++;
    PropInit::Set5(p, 146, 2664, 2664, 5, 2664); p++;
    PropInit::Set5(p, 146, 2668, 2668, 0, 2668); p++;
    PropInit::Set1(p, (s32)SteerScriptAgentAlongPath, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 2972, 2972, 10, 2972); p++;
    PropInit::Set5(p, 146, 2944, 2944, 0, 2944); p++;
    PropInit::Set5(p, 146, 2892, 2892, 6, 2892); p++;
    PropInit::Set4(p, 36, 8195, (s32)StoreAgentTarget, (s32)SetAgentSecondaryTarget); p++;
    PropInit::Set5(p, 146, 2884, 2884, 0, 2884); p++;
    PropInit::Set5(p, 146, 2844, 2844, 0, 2844); p++;
    PropInit::Set5(p, 146, 2848, 2848, 1, 2848); p++;
    PropInit::Set5(p, 146, 2864, 2864, 9, 2864); p++;
    PropInit::Set5(p, 146, 2336, 2336, 4174, 2336); p++;
    PropInit::Set1(p, (s32)SetScriptAgentMainClip, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 2904, 2904, 5, 2904); p++;
    PropInit::Set5(p, 146, 2912, 2912, 2, 2912); p++;
    PropInit::Set5(p, 146, 2928, 2928, 0, 2928); p++;
    PropInit::Set2(p, 6, 256, (s32)SetAgentMemberGroupId); p++;
    PropInit::Set2(p, 6, 256, (s32)SetAgentTargetSetId); p++;
    PropInit::Set2(p, 1, 128, 2840); p++;
    PropInit::Set5(p, 146, 3024, 3024, 1, 3024); p++;
    PropInit::Set5(p, 146, 3028, 3028, 0, 3028); p++;
    PropInit::Set0(p, 2, 4133, 1828); p++;
    PropInit::Set5(p, 146, 2752, 2752, 0, 2752); p++;
    PropInit::Set0(p, 4, 0, (s32)IsAgentNearPathEnd); p++;
    PropInit::Set5(p, 146, 3040, 3040, 10, 3040); p++;
    PropInit::Set5(p, 146, 3036, 3036, 0, 3036); p++;
    PropInit::Set5(p, 146, 3048, 3048, 1, 3048); p++;
    PropInit::Set5(p, 146, 3032, 3032, 0, 3032); p++;
    PropInit::Set5(p, 146, 3080, 3080, 0, 3080); p++;
    PropInit::Set2(p, 6, 256, (s32)AddOwnedWantedId); p++;
    PropInit::Set2(p, 6, 256, (s32)AddListedWantedId); p++;
    PropInit::Set5(p, 146, 3096, 3096, 1, 3096); p++;
    PropInit::Set5(p, 146, 3100, 3100, 1, 3100); p++;
    PropInit::Set5(p, 146, 3104, 3104, 1, 3104); p++;
    PropInit::Set5(p, 146, 3108, 3108, 1, 3108); p++;
    PropInit::Set5(p, 146, 3112, 3112, 6, 3112); p++;
    PropInit::Set2(p, 6, 128, 3088); p++;
    PropInit::Set0(p, 2, 8288, 3092); p++;
    PropInit::Set1(p, 0, (s32)SetScriptCompanionAgentLookId, 18, 1024, 2); p++;
    PropInit::Set5(p, 146, 3272, 3272, 0, 3272); p++;
    PropInit::Set5(p, 146, 3276, 3276, 0, 3276); p++;
    PropInit::Set5(p, 146, 3280, 3280, 4197, 3280); p++;
    PropInit::Set5(p, 146, 3052, 3052, 6, 3052); p++;
    PropInit::Set2(p, 6, 256, (s32)AddCompanionAgentExcludedId); p++;
    PropInit::Set15(p, 1740, 35.0f, 1, 2176); p++;
    PropInit::Set6(p, (s32)ScaleTurningColliderRamp, 1, 288, (s32)ScaleTurningColliderRamp); p++;
    PropInit::Set5(p, 290, (s32)SetTurningColliderGravityScale, 1792, 1, (s32)SetTurningColliderGravityScale); p++;
    PropInit::Set5(p, 146, 1372, 1372, 1, 1372); p++;
    PropInit::Set5(p, 146, 1376, 1376, 1, 1376); p++;
    PropInit::Set5(p, 146, 1360, 1360, 4135, 1360); p++;
    PropInit::Set5(p, 146, 1544, 1544, 4136, 1544); p++;
    PropInit::Set5(p, 146, 1380, 1380, 0, 1380); p++;
    PropInit::Set5(p, 146, 1384, 1384, 1, 1384); p++;
    PropInit::Set5(p, 146, 1396, 1396, 1, 1396); p++;
    PropInit::Set5(p, 146, 1388, 1388, 10, 1388); p++;
    PropInit::Set5(p, 146, 1472, 1472, 1, 1472); p++;
    PropInit::Set1(p, (s32)StartScriptChildGroupDelay, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)StepScriptChildGroupObject, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1652, 1652, 0, 1652); p++;
    PropInit::Set5(p, 146, 1656, 1656, 0, 1656); p++;
    PropInit::Set5(p, 146, 1660, 1660, 4124, 1660); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)GetChildGroupSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)GetChildGroupSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)GetChildGroupSoundParams); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)GetChildGroupSoundParams); p++;
    PropInit::Set5(p, 146, 1368, 1368, 1, 1368); p++;
    PropInit::Set8m(p, 0, 1668, 130); p++;
    PropInit::Set1(p, (s32)PlaceScriptPlayerOnGround, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)ReleaseScriptPlayerToState2, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)IgnoreScriptPlayerArgument, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 8640, 8640, 0, 8640); p++;
    PropInit::Set4(p, 34, 4178, 10008, (s32)SetPlayerPadSelectMode); p++;
    PropInit::Set1(p, (s32)SetScriptPlayerPath, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SwitchScriptPlayerState11, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SeekScriptObjects105Animations, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SwapInScriptPlayerStandIn, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 11220, 11220, 0, 11220); p++;
    PropInit::Set5(p, 162, (s32)SetPlayerProbeContactsDisabled, 11224, 0, 11224); p++;
    PropInit::Set1(p, (s32)QueueScriptPlayerWalkerActivation, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)QueueScriptPlayerFirstActivation, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)QueueScriptPlayerSecondActivation, 0, 18, 1, 1); p++;
    PropInit::Set2(p, 4144, 128, 68); p++;
    PropInit::Set2(p, 6, 128, 52); p++;
    PropInit::Set2(p, 6, 128, 56); p++;
    PropInit::Set2(p, 4127, 128, 76); p++;
    PropInit::Set1(p, 0, (s32)SetScriptC8BObjectVector, 18, 1024, 3); p++;
    PropInit::Set1(p, 0, (s32)SetScriptC8BObjectVectorFlagged, 18, 1024, 3); p++;
    PropInit::Set10(p, 1, 2194, 1552, 1552, 1552, 500.0f); p++;
    PropInit::Set10(p, 1, 2194, 1556, 1556, 1556, 500.0f); p++;
    PropInit::Set10(p, 1, 2194, 1520, 1520, 1520, 15.0f); p++;
    PropInit::Set10(p, 1, 2194, 1560, 1560, 1560, 1000.0f); p++;
    PropInit::Set10(p, 1, 2194, 1520, 1520, 1520, 15.0f); p++;
    PropInit::Set10(p, 1, 2194, 1572, 1572, 1572, 3000.0f); p++;
    PropInit::Set5(p, 146, 1544, 1544, 1, 1544); p++;
    PropInit::Set10(p, 1, 2194, 1568, 1568, 1568, 300.0f); p++;
    PropInit::Set0(p, 2, 4154, 1360); p++;
    PropInit::Set5(p, 146, 1636, 1636, 5, 1636); p++;
    PropInit::Set5(p, 146, 1640, 1640, 0, 1640); p++;
    PropInit::Set15(p, 736, 50.0f, 1, 2176); p++;
    PropInit::Set15(p, 740, 25.0f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 744, 0, 1); p++;
    PropInit::Set15(p, 748, 3.5f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 752, 1, 5); p++;
    PropInit::Set5(p, 146, 768, 768, 2, 768); p++;
    PropInit::Set5(p, 146, 784, 784, 0, 784); p++;
    PropInit::Set5(p, 146, 800, 800, 2, 800); p++;
    PropInit::Set2(p, 6, 256, (s32)SetPairControllerFirstTemplateId); p++;
    PropInit::Set2(p, 6, 256, (s32)SetPairControllerSecondTemplateId); p++;
    PropInit::Set2(p, 6, 256, (s32)SetPairControllerHostId); p++;
    PropInit::Set2(p, 6, 256, (s32)SetPairControllerExtraId); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendPairControllerId); p++;
    PropInit::Set14(p, 4242, 1, 0, 0, 0, (s32)GetPairControllerPose); p++;
    PropInit::Set16(p, 1, 4, 4, (s32)GetPairControllerPose, 4226); p++;
    PropInit::Set14(p, 4242, 9, 16, 16, 16, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 1, 32, 32, 32, (s32)GetPairControllerPose); p++;
    PropInit::Set16(p, 1, 36, 36, (s32)GetPairControllerPose, 4226); p++;
    PropInit::Set14(p, 4242, 9, 48, 48, 48, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 10, 64, 64, 64, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 10, 72, 72, 72, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 9, 80, 80, 80, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 10, 96, 96, 96, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 10, 104, 104, 104, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 9, 112, 112, 112, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 1, 128, 128, 128, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 1, 132, 132, 132, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 9, 144, 144, 144, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 1, 160, 160, 160, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 1, 164, 164, 164, (s32)GetPairControllerPose); p++;
    PropInit::Set14(p, 4242, 9, 176, 176, 176, (s32)GetPairControllerPose); p++;
    PropInit::Set5(p, 146, 816, 816, 2, 816); p++;
    PropInit::Set5(p, 146, 832, 832, 1, 832); p++;
    PropInit::Set5(p, 146, 836, 836, 1, 836); p++;
    PropInit::Set5(p, 146, 840, 840, 1, 840); p++;
    PropInit::Set5(p, 146, 844, 844, 1, 844); p++;
    PropInit::Set5(p, 146, 848, 848, 1, 848); p++;
    PropInit::Set8m(p, 5, 952, 130); p++;
    PropInit::Set8m(p, 4147, 1612, 130); p++;
    PropInit::Set5(p, 146, 1568, 1568, 5, 1568); p++;
    PropInit::Set5(p, 146, 976, 976, 9, 976); p++;
    PropInit::Set5(p, 146, 1576, 1576, 1, 1576); p++;
    PropInit::Set5(p, 146, 1412, 1412, 10, 1412); p++;
    PropInit::Set2(p, 5, 128, 1384); p++;
    PropInit::Set5(p, 146, 1392, 1392, 1, 1392); p++;
    PropInit::Set5(p, 146, 1388, 1388, 1, 1388); p++;
    PropInit::Set5(p, 146, 1424, 1424, 9, 1424); p++;
    PropInit::Set4(p, 34, 4145, 1360, (s32)SetPooledObjectState); p++;
    PropInit::Set10(p, 1, 2194, 1368, 1368, 1368, 2500.0f); p++;
    PropInit::Set10(p, 1, 2194, 1372, 1372, 1372, 20.0f); p++;
    PropInit::Set10(p, 1, 2194, 1376, 1376, 1376, 30.0f); p++;
    PropInit::Set10(p, 1, 2194, 1380, 1380, 1380, 1.5f); p++;
    PropInit::Set10(p, 1, 2194, 1384, 1384, 1384, 10.0f); p++;
    PropInit::Set2(p, 6, 128, 1728); p++;
    PropInit::Set12(p, 2176, 1732, 5, 5); p++;
    PropInit::Set10(p, 1, 2194, 1744, 1744, 1744, 1.0f); p++;
    PropInit::Set10(p, 1, 2194, 1748, 1748, 1748, 20.0f); p++;
    PropInit::Set2(p, 6, 256, (s32)AddPooledHolderItem); p++;
    PropInit::Set1(p, (s32)ResetScriptCollectedItems, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)CollectScriptItem, 0, 18, 1, 1); p++;
    PropInit::Set10(p, 1, 2194, 1680, 1680, 1680, 800.0f); p++;
    PropInit::Set4(p, 18, 8194, 1684, 1684); p++;
    PropInit::Set4(p, 18, 2, 1696, 1696); p++;
    PropInit::Set5(p, 146, 1720, 1720, 0, 1720); p++;
    PropInit::Set1(p, 0, (s32)AddScriptContactListId, 18, 1024, 1); p++;
    PropInit::Set1(p, 0, (s32)AddScriptContactListKind, 18, 1024, 1); p++;
    PropInit::Set10(p, 1, 2194, 1776, 1776, 1776, 2000.0f); p++;
    PropInit::Set10(p, 1, 2194, 1780, 1780, 1780, 5000.0f); p++;
    PropInit::Set4(p, 18, 2, 1792, 1792); p++;
    PropInit::Set5(p, 146, 1776, 1776, 1, 1776); p++;
    PropInit::Set10(p, 1, 2194, 1780, 1780, 1780, 1500.0f); p++;
    PropInit::Set10(p, 1, 2194, 1784, 1784, 1784, 1.0f); p++;
    PropInit::Set5(p, 146, 1792, 1792, 2, 1792); p++;
    PropInit::Set10(p, 1, 2194, 88, 88, 88, 100.0f); p++;
    PropInit::Set12(p, 2176, 92, -1, 6); p++;
    PropInit::Set5(p, 146, 728, 728, 1, 728); p++;
    PropInit::Set8m(p, 6, 736, 130); p++;
    PropInit::Set1(p, 0, (s32)AddScriptStateResetEntry, 18, 1024, 4); p++;
    PropInit::Set5(p, 146, 3088, 3088, 1, 3088); p++;
    PropInit::Set5(p, 146, 3092, 3092, 1, 3092); p++;
    PropInit::Set2(p, 6, 128, 3096); p++;
    PropInit::Set4(p, 18, 8315, 3100, 3100); p++;
    PropInit::Set5(p, 146, 3104, 3104, 10, 3104); p++;
    PropInit::Set5(p, 146, 3112, 3112, 10, 3112); p++;
    PropInit::Set2(p, 6, 128, 3120); p++;
    PropInit::Set4(p, 18, 8315, 3124, 3124); p++;
    PropInit::Set5(p, 146, 3132, 3132, 0, 3132); p++;
    PropInit::Set5(p, 146, 3136, 3136, 0, 3136); p++;
    PropInit::Set5(p, 146, 752, 752, 1, 752); p++;
    PropInit::Set5(p, 146, 768, 768, 9, 768); p++;
    PropInit::Set5(p, 146, 816, 816, 10, 816); p++;
    PropInit::Set5(p, 146, 784, 784, 9, 784); p++;
    PropInit::Set5(p, 146, 824, 824, 10, 824); p++;
    PropInit::Set5(p, 146, 800, 800, 9, 800); p++;
    PropInit::Set5(p, 146, 832, 832, 10, 832); p++;
    PropInit::Set5(p, 146, 912, 912, 1, 912); p++;
    PropInit::Set5(p, 146, 840, 840, 1, 840); p++;
    PropInit::Set5(p, 146, 844, 844, 1, 844); p++;
    PropInit::Set5(p, 146, 848, 848, 1, 848); p++;
    PropInit::Set5(p, 146, 852, 852, 1, 852); p++;
    PropInit::Set5(p, 146, 856, 856, 1, 856); p++;
    PropInit::Set5(p, 290, (s32)SetOnOffObjectBlockValue, 864, 1, (s32)SetOnOffObjectBlockValue); p++;
    PropInit::Set5(p, 146, 864, 864, 2, 864); p++;
    PropInit::Set5(p, 146, 896, 896, 0, 896); p++;
    PropInit::Set5(p, 146, 1044, 1044, 4108, 1044); p++;
    PropInit::Set5(p, 146, 1048, 1048, 0, 1048); p++;
    PropInit::Set5(p, 146, 1052, 1052, 0, 1052); p++;
    PropInit::Set5(p, 146, 904, 904, 5, 904); p++;
    PropInit::Set5(p, 146, 900, 900, 0, 900); p++;
    PropInit::Set5(p, 146, 1072, 1072, 4165, 1072); p++;
    PropInit::Set5(p, 146, 1056, 1056, 1, 1056); p++;
    PropInit::Set5(p, 146, 1060, 1060, 1, 1060); p++;
    PropInit::Set5(p, 146, 1064, 1064, 1, 1064); p++;
    PropInit::Set5(p, 146, 1068, 1068, 1, 1068); p++;
    PropInit::Set5(p, 146, 1076, 1076, 0, 1076); p++;
    PropInit::Set5(p, 146, 1080, 1080, 1, 1080); p++;
    PropInit::Set5(p, 146, 1088, 1088, 0, 1088); p++;
    PropInit::Set4(p, 18, 8194, 1092, 1092); p++;
    PropInit::Set5(p, 146, 1104, 1104, 9, 1104); p++;
    PropInit::Set5(p, 146, 1120, 1120, 10, 1120); p++;
    PropInit::Set0(p, 2, 4109, 916); p++;
    PropInit::Set5(p, 162, (s32)SetOnOffObjectForcedState, 920, 4109, 920); p++;
    PropInit::Set5(p, 146, 880, 880, 1, 880); p++;
    PropInit::Set5(p, 146, 884, 884, 1, 884); p++;
    PropInit::Set6(p, (s32)FollowObjectById, 6, 160, 1400); p++;
    PropInit::Set1(p, (s32)SetScriptCurrentTargetFollower, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ClearScriptCurrentTargetFollower, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1472, 1472, 0, 1472); p++;
    PropInit::Set5(p, 146, 1476, 1476, 1, 1476); p++;
    PropInit::Set5(p, 146, 1480, 1480, 1, 1480); p++;
    PropInit::Set5(p, 146, 1496, 1496, 0, 1496); p++;
    PropInit::Set2(p, 6, 128, 1952); p++;
    PropInit::Set4(p, 18, 8318, 1956, 1956); p++;
    PropInit::Set2(p, 6, 128, 1960); p++;
    PropInit::Set4(p, 18, 8292, 1964, 1964); p++;
    PropInit::Set5(p, 146, 788, 788, 4170, 788); p++;
    PropInit::Set5(p, 146, 796, 796, 1, 796); p++;
    PropInit::Set5(p, 146, 800, 800, 1, 800); p++;
    PropInit::Set5(p, 146, 792, 792, 4171, 792); p++;
    PropInit::Set5(p, 146, 804, 804, 1, 804); p++;
    PropInit::Set5(p, 146, 808, 808, 1, 808); p++;
    PropInit::Set5(p, 146, 812, 812, 1, 812); p++;
    PropInit::Set5(p, 146, 816, 816, 1, 816); p++;
    PropInit::Set5(p, 146, 820, 820, 1, 820); p++;
    PropInit::Set1(p, 0, (s32)AddScriptObjectPoolEntry, 18, 1024, 4); p++;
    PropInit::Set16(p, 0, 4, 4, (s32)GetObjectPoolShare, 4226); p++;
    PropInit::Set5(p, 146, 64, 64, 4158, 64); p++;
    PropInit::Set4(p, 18, 5, 68, 68); p++;
    PropInit::Set1(p, (s32)EnableScriptObjectPoolEntry, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)DisableScriptObjectPoolEntry, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)SetScriptObjectPoolEntryCount, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)ChooseScriptObjectPoolItem, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ReleaseScriptObjectPoolItem, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 2, 8195, 72); p++;
    PropInit::Set1(p, (s32)ResetScriptPlacementRecord, 0, 18, 1, 0); p++;
    PropInit::Set2(p, 6, 128, 76); p++;
    PropInit::Set4(p, 18, 8194, 104, 104); p++;
    PropInit::Set4(p, 18, 8318, 96, 96); p++;
    PropInit::Set4(p, 18, 8307, 100, 100); p++;
    PropInit::Set5(p, 146, 112, 112, 2, 112); p++;
    PropInit::Set5(p, 146, 128, 128, 4, 128); p++;
    PropInit::Set5(p, 146, 176, 176, 2, 176); p++;
    PropInit::Set5(p, 146, 192, 192, 2, 192); p++;
    PropInit::Set5(p, 146, 208, 208, 10, 208); p++;
    PropInit::Set5(p, 146, 216, 216, 1, 216); p++;
    PropInit::Set1(p, (s32)ResetScriptObjectPoolReleaseRecord, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 80, 80, 6, 80); p++;
    PropInit::Set4(p, 18, 8194, 224, 224); p++;
    PropInit::Set4(p, 18, 8309, 228, 228); p++;
    PropInit::Set5(p, 146, 240, 240, 2, 240); p++;
    PropInit::Set5(p, 146, 256, 256, 4166, 256); p++;
    PropInit::Set5(p, 146, 304, 304, 9, 304); p++;
    PropInit::Set5(p, 146, 304, 304, 9, 304); p++;
    PropInit::Set5(p, 146, 320, 320, 10, 320); p++;
    PropInit::Set5(p, 146, 272, 272, 9, 272); p++;
    PropInit::Set5(p, 146, 288, 288, 10, 288); p++;
    PropInit::Set1(p, (s32)ClearScriptObjectPoolHeadingRecord, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 336, 336, 4153, 336); p++;
    PropInit::Set2(p, 6, 128, 84); p++;
    PropInit::Set4(p, 18, 8307, 352, 352); p++;
    PropInit::Set5(p, 146, 340, 340, 1, 340); p++;
    PropInit::Set5(p, 146, 344, 344, 1, 344); p++;
    PropInit::Set5(p, 146, 348, 348, 1, 348); p++;
    PropInit::Set2(p, 6, 128, 88); p++;
    PropInit::Set0(p, 2, 8194, 92); p++;
    PropInit::Set17(p, 1360, 1360, 0, 4155, 2178); p++;
    PropInit::Set17(p, 1376, 1376, 0, 4156, 2178); p++;
    PropInit::Set4(p, 34, 4156, 1364, (s32)SetObjectCyclerState); p++;
    PropInit::Set5(p, 146, 1552, 1552, 10, 1552); p++;
    PropInit::Set5(p, 146, 1560, 1560, 10, 1560); p++;
    PropInit::Set5(p, 146, 1568, 1568, 10, 1568); p++;
    PropInit::Set5(p, 146, 1576, 1576, 10, 1576); p++;
    PropInit::Set2(p, 6, 128, 1584); p++;
    PropInit::Set10(p, 1, 2194, 1592, 1592, 1592, 0.800000011920929f); p++;
    PropInit::Set5(p, 146, 1596, 1596, 10, 1596); p++;
    PropInit::Set10(p, 1, 2194, 1604, 1604, 1604, 0.019999999552965164f); p++;
    PropInit::Set5(p, 146, 1616, 1616, 10, 1616); p++;
    PropInit::Set5(p, 146, 1624, 1624, 10, 1624); p++;
    PropInit::Set5(p, 146, 1632, 1632, 10, 1632); p++;
    PropInit::Set5(p, 146, 1648, 1648, 10, 1648); p++;
    PropInit::Set10(p, 1, 2194, 1668, 1668, 1668, 300.0f); p++;
    PropInit::Set5(p, 146, 1680, 1680, 5, 1680); p++;
    PropInit::Set5(p, 146, 1684, 1684, 0, 1684); p++;
    PropInit::Set4(p, 34, 4167, 724, (s32)SetStepSequenceState); p++;
    PropInit::Set2(p, 6, 128, 768); p++;
    PropInit::Set5(p, 146, 804, 804, 0, 804); p++;
    PropInit::Set5(p, 146, 808, 808, 0, 808); p++;
    PropInit::Set5(p, 146, 812, 812, 0, 812); p++;
    PropInit::Set1(p, 0, (s32)SetScriptStepSequenceModeOne, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)SetScriptStepSequenceCameraMode, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)AddScriptSequenceExtraTarget, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)ChooseScriptStepSequenceState, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)ResetScriptStepSequence, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 780, 780, 6, 780); p++;
    PropInit::Set4(p, 36, 0, (s32)ReadSequenceTarget, (s32)WriteSequenceTarget); p++;
    PropInit::Set8m(p, 0, 816, 130); p++;
    PropInit::Set5(p, 146, 732, 732, 6, 732); p++;
    PropInit::Set5(p, 146, 736, 736, 1, 736); p++;
    PropInit::Set4(p, 66, 4169, 720, 204); p++;
    PropInit::Set5(p, 146, 820, 820, 0, 820); p++;
    PropInit::Set5(p, 146, 904, 904, 1, 904); p++;
    PropInit::Set5(p, 146, 832, 832, 0, 832); p++;
    PropInit::Set5(p, 146, 912, 912, 10, 912); p++;
    PropInit::Set5(p, 146, 912, 912, 10, 912); p++;
    PropInit::Set7(p, 0, 0); p++;
    PropInit::Set5(p, 146, 720, 720, 13, 720); p++;
    PropInit::Set5(p, 146, 724, 724, 1, 724); p++;
    PropInit::Set5(p, 146, 728, 728, 1, 728); p++;
    PropInit::Set5(p, 146, 732, 732, 1, 732); p++;
    PropInit::Set5(p, 146, 736, 736, 1, 736); p++;
    PropInit::Set5(p, 146, 752, 752, 2, 752); p++;
    PropInit::Set5(p, 146, 768, 768, 2, 768); p++;
    PropInit::Set5(p, 146, 800, 800, 1, 800); p++;
    PropInit::Set5(p, 146, 804, 804, 1, 804); p++;
    PropInit::Set6(p, (s32)SetObjectLinkId, 6, 160, 812); p++;
    PropInit::Set5(p, 146, 784, 784, 2, 784); p++;
    PropInit::Set5(p, 146, 808, 808, 1, 808); p++;
    PropInit::Set2(p, 6, 256, (s32)AddC5DObjectId); p++;
    PropInit::Set1(p, (s32)QueueScriptWalkerActivationOnPlayer, 0, 18, 1, 0); p++;
    PropInit::Set2(p, 5, 256, (s32)SetC5DObjectMaskBit); p++;
    PropInit::Set1(p, 0, (s32)AddScriptOscillatorXEntry, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)AddScriptOscillatorYZEntry, 18, 1024, 0); p++;
    PropInit::Set14(p, 4242, 2, 16, 16, 16, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set5(p, 292, (s32)SetOscillatorEntryPeriod, (s32)GetOscillatorEntryPeriod, 1, (s32)SetOscillatorEntryPeriod); p++;
    PropInit::Set14(p, 4242, 1, 104, 104, 104, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 1, 108, 108, 108, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 2, 64, 64, 64, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 10, 48, 48, 48, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 10, 80, 80, 80, (s32)GetOscillatorEntryForPeriod); p++;
    PropInit::Set14(p, 4242, 2, 16, 16, 16, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set14(p, 4242, 10, 48, 48, 48, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set14(p, 4242, 1, 56, 56, 56, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set1(p, 0, (s32)AddScriptOscillatorEntryVectorA, 18, 1024, 4); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set14(p, 4242, 10, 128, 128, 128, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set14(p, 4242, 1, 136, 136, 136, (s32)GetOscillatorEntryForVectors); p++;
    PropInit::Set1(p, 0, (s32)AddScriptOscillatorEntryVectorB, 18, 1024, 4); p++;
    PropInit::Set0(p, 2, 5, 56); p++;
    PropInit::Set4(p, 18, 5, 1744, 1744); p++;
    PropInit::Set5(p, 146, 3088, 3088, 0, 3088); p++;
    PropInit::Set0(p, 2, 8339, 3600); p++;
    PropInit::Set5(p, 146, 3604, 3604, 8307, 3604); p++;
    PropInit::Set1(p, (s32)AdvanceScriptGaugeAgentPhase, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 1, (s32)GetGaugeAgentLevelFactor); p++;
    PropInit::Set4(p, 34, 4175, 1824, (s32)SetTintBlendColliderState); p++;
    PropInit::Set5(p, 146, 1852, 1852, 0, 1852); p++;
    PropInit::Set5(p, 146, 88, 88, 1, 88); p++;
    PropInit::Set5(p, 146, 92, 92, 0, 92); p++;
    PropInit::Set5(p, 146, 64, 64, 0, 64); p++;
    PropInit::Set10(p, 1, 2194, 68, 68, 68, 1000.0f); p++;
    PropInit::Set10(p, 1, 2194, 72, 72, 72, 2.0f); p++;
    PropInit::Set5(p, 146, 76, 76, 1, 76); p++;
    PropInit::Set5(p, 146, 80, 80, 0, 80); p++;
    PropInit::Set2(p, 6, 128, 84); p++;
    PropInit::Set4(p, 18, 8302, 88, 88); p++;
    PropInit::Set0(p, 2, 8339, 1556); p++;
    PropInit::Set5(p, 146, 1584, 1584, 0, 1584); p++;
    PropInit::Set5(p, 146, 1604, 1604, 4177, 1604); p++;
    PropInit::Set5(p, 146, 1588, 1588, 0, 1588); p++;
    PropInit::Set2(p, 6, 256, (s32)AddPlayerLinkedColliderId); p++;
    PropInit::Set5(p, 146, 1616, 1616, 10, 1616); p++;
    PropInit::Set5(p, 146, 1624, 1624, 10, 1624); p++;
    PropInit::Set5(p, 146, 1600, 1600, 5, 1600); p++;
    PropInit::Set1(p, 0, (s32)AddScriptEntryRecordKey, 18, 1024, 2); p++;
    PropInit::Set2(p, 6, 128, 1612); p++;
    PropInit::Set2(p, 6, 128, 1604); p++;
    PropInit::Set5(p, 146, 1620, 1620, 0, 1620); p++;
    PropInit::Set2(p, 1, 128, 1672); p++;
    PropInit::Set0(p, 2, 8339, 1556); p++;
    PropInit::Set0(p, 2, 8339, 1720); p++;
    PropInit::Set2(p, 2, 128, 1360); p++;
    PropInit::Set2(p, 1, 128, 1384); p++;
    PropInit::Set2(p, 10, 128, 1376); p++;
    PropInit::Set5(p, 146, 724, 724, 5, 724); p++;
    PropInit::Set5(p, 146, 728, 728, 1, 728); p++;
    PropInit::Set2(p, 6, 256, (s32)AppendGaugeSlot); p++;
    PropInit::Set14(p, 4242, 1, 0, 0, 0, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 9, 16, 16, 16, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 64, 64, 64, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 32, 32, 32, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 40, 40, 40, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 9, 48, 48, 48, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 68, 68, 68, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 76, 76, 76, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 9, 96, 96, 96, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 112, 112, 112, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 116, 116, 116, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 9, 128, 128, 128, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 144, 144, 144, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 1, 148, 148, 148, (s32)GetGaugeParams); p++;
    PropInit::Set14(p, 4242, 9, 160, 160, 160, (s32)GetGaugeParams); p++;
    PropInit::Set5(p, 146, 1680, 1680, 5, 1680); p++;
    PropInit::Set5(p, 146, 1136, 1136, 9, 1136); p++;
    PropInit::Set0(p, 2, 8339, 1068); p++;
    PropInit::Set5(p, 146, 3108, 3108, 5, 3108); p++;
    PropInit::Set5(p, 146, 1552, 1552, 1, 1552); p++;
    PropInit::Set5(p, 146, 1556, 1556, 1, 1556); p++;
    PropInit::Set5(p, 146, 1560, 1560, 1, 1560); p++;
    PropInit::Set5(p, 146, 1564, 1564, 1, 1564); p++;
    PropInit::Set4(p, 34, 8302, 2096, (s32)SetPathFollowerPath); p++;
    PropInit::Set4(p, 34, 8302, 2120, (s32)SetPathFollowerSecondPath); p++;
    PropInit::Set5(p, 146, 2820, 2820, 5, 2820); p++;
    PropInit::Set1(p, (s32)AddScriptPathFollowerEntry, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)AddScriptPathFollowerActiveEntry, 0, 18, 1, 5); p++;
    PropInit::Set4(p, 18, 8330, 2876, 2876); p++;
    PropInit::Set5(p, 290, (s32)SetPathFollowerMode, 2868, 4183, (s32)SetPathFollowerMode); p++;
    PropInit::Set1(p, (s32)ResetScriptPathFollower, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 2864, 2864, 4184, 2864); p++;
    PropInit::Set5(p, 146, 2820, 2820, 5, 2820); p++;
    PropInit::Set4(p, 18, 8311, 2840, 2840); p++;
    PropInit::Set4(p, 18, 8311, 2844, 2844); p++;
    PropInit::Set4(p, 18, 8272, 2836, 2836); p++;
    PropInit::Set5(p, 146, 2152, 2152, 1, 2152); p++;
    PropInit::Set5(p, 146, 2136, 2136, 5, 2136); p++;
    PropInit::Set5(p, 146, 1584, 1584, 9, 1584); p++;
    PropInit::Set5(p, 146, 1600, 1600, 10, 1600); p++;
    PropInit::Set5(p, 146, 1616, 1616, 9, 1616); p++;
    PropInit::Set5(p, 146, 1632, 1632, 10, 1632); p++;
    PropInit::Set1(p, (s32)TestScriptPointAgainstObjectShape, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)TestScriptPointInsideFaceTreeObject, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)AddScriptSeekingAgentObject, 0, 0, 1, 1); p++;
    PropInit::Set4(p, 34, 8307, 3112, (s32)SetSeekingAgentStateTarget); p++;
    PropInit::Set4(p, 34, 8307, 3108, (s32)SetSeekingAgentTarget); p++;
    PropInit::Set0(p, 4, 2, (s32)PickRandomPointOnPointGraph); p++;
    PropInit::Set5(p, 146, 1740, 1740, 1, 1740); p++;
    PropInit::Set5(p, 146, 1744, 1744, 1, 1744); p++;
    PropInit::Set5(p, 146, 1748, 1748, 1, 1748); p++;
    PropInit::Set5(p, 146, 1752, 1752, 1, 1752); p++;
    PropInit::Set1(p, (s32)StartScriptC24ObjectPath, 0, 18, 1, 2); p++;
    PropInit::Set4(p, 34, 4176, 2992, (s32)SetModeWalkerMode); p++;
    PropInit::Set1(p, (s32)ResetScriptEntryQueue, (s32)ResetScriptEntryQueue, 18, 1025, 0); p++;
    PropInit::Set1(p, (s32)BindScriptEntryQueueToObject, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)UnbindScriptEntryQueue, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind0, (s32)AddScriptQueueEntryKind0, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind1, (s32)AddScriptQueueEntryKind1, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind10, (s32)AddScriptQueueEntryKind10, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind2, (s32)AddScriptQueueEntryKind2, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind3, (s32)AddScriptQueueEntryKind3, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind4, (s32)AddScriptQueueEntryKind4, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind5, (s32)AddScriptQueueEntryKind5, 18, 1025, 4); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind6, (s32)AddScriptQueueEntryKind6, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind7, (s32)AddScriptQueueEntryKind7, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind8, (s32)AddScriptQueueEntryKind8, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind9, (s32)AddScriptQueueEntryKind9, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind11, (s32)AddScriptQueueEntryKind11, 18, 1025, 1); p++;
    PropInit::Set5(p, 146, 104, 104, 0, 104); p++;
    PropInit::Set1(p, (s32)AddScriptQueueEntryKind12, (s32)AddScriptQueueEntryKind12, 18, 1025, 0); p++;
    PropInit::Set1(p, (s32)StartScriptColorFade, (s32)StartScriptColorFade, 18, 1025, 0); p++;
    PropInit::Set5(p, 146, 60, 60, 13, 60); p++;
    PropInit::Set5(p, 146, 64, 64, 13, 64); p++;
    PropInit::Set5(p, 146, 68, 68, 13, 68); p++;
    PropInit::Set5(p, 146, 72, 72, 1, 72); p++;
    PropInit::Set5(p, 146, 80, 80, 1, 80); p++;
    PropInit::Set5(p, 146, 76, 76, 1, 76); p++;
    PropInit::Set5(p, 146, 88, 88, 4188, 88); p++;
    PropInit::Set4(p, 18, 8195, 1544, 1544); p++;
    PropInit::Set4(p, 34, 4190, 1360, (s32)SetGaugeModeObjectMode); p++;
    PropInit::Set9(p, 32, 0, (s32)PlayGaugeModeObjectLoop); p++;
    PropInit::Set1(p, (s32)PlayScriptGaugeModeObjectTarget, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)SetScriptGaugeModeObjectTarget, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 1788, 1788, 1, 1788); p++;
    PropInit::Set5(p, 146, 1792, 1792, 1, 1792); p++;
    PropInit::Set1(p, (s32)PlaceScriptModeColliderAtAnchor, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1368, 1368, 5, 1368); p++;
    PropInit::Set5(p, 162, (s32)SetCountdownState, 1360, 4191, 1360); p++;
    PropInit::Set5(p, 290, (s32)SetTempoAgentTempo, 3164, 5, (s32)SetTempoAgentTempo); p++;
    PropInit::Set5(p, 290, (s32)SetTempoAgentSpanBeats, 3168, 5, (s32)SetTempoAgentSpanBeats); p++;
    PropInit::Set1(p, (s32)SetScriptTempoAgentPendingTimeline, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)EndScriptHeldTimeline, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 2, 8339, 3156); p++;
    PropInit::Set4(p, 18, 8307, 3144, 3144); p++;
    PropInit::Set1(p, (s32)AddScriptC13Entry, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)RemoveScriptTempoAgentEntry, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)DecrementScriptTempoAgentGauge, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 18, 8307, 1660, 1660); p++;
    PropInit::Set4(p, 18, 8335, 1576, 1576); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind0Entry, (s32)AppendScriptTimelineKind0Entry, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind1Entry, (s32)AppendScriptTimelineKind1Entry, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind2Entry, (s32)AppendScriptTimelineKind2Entry, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind3Entry, (s32)AppendScriptTimelineKind3Entry, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind4Entry, (s32)AppendScriptTimelineKind4Entry, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)AppendScriptTimelineKind5Entry, (s32)AppendScriptTimelineKind5Entry, 18, 1025, 2); p++;
    PropInit::Set4(p, 18, 5, 3088, 3088); p++;
    PropInit::Set1(p, (s32)SetScriptGaugeBarAgentValues, 0, 18, 1, 3); p++;
    PropInit::Set4(p, 18, 0, 3108, 3108); p++;
    PropInit::Set4(p, 34, 4199, 1552, (s32)SetHitCountColliderState); p++;
    PropInit::Set1(p, (s32)SendScriptHitCountColliderRequest, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 1680, 1680, 5, 1680); p++;
    PropInit::Set5(p, 146, 1684, 1684, 5, 1684); p++;
    PropInit::Set1(p, (s32)AddScriptHitCountColliderId, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)AddScriptHitCountColliderItem, 0, 18, 1, 1); p++;
    PropInit::Set4(p, 18, 5, 1360, 1360); p++;
    PropInit::Set4(p, 18, 8311, 1368, 1368); p++;
    PropInit::Set1(p, (s32)TakeScriptCountedColliderTouch, 0, 18, 1, 2);
}

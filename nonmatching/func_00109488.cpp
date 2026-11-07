// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 37352/37392, checked 2026-11-07
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
void func_001000C8();
void func_00100178();
void func_00100218();
void func_001002C0();
void func_00100368();
void func_00100438();
void func_001004F0();
void func_001005A0();
void func_00100650();
void func_00100720();
void func_001007F0();
void func_001008B8();
void func_00100998();
void func_00100A78();
void func_00100B48();
void func_00100C28();
void func_00100CC8();
void func_00100D68();
void func_00100E08();
void func_00100EE0();
void func_00100FA8();
void func_00101058();
void func_00101168();
void func_00101208();
void func_001012B8();
void func_00101368();
void func_00101418();
void func_001014C8();
void func_00101568();
void func_00101620();
void func_001016F0();
void func_001017A0();
void func_00101860();
void func_00101950();
void func_001019F0();
void func_00101A90();
void func_00101B80();
void func_00101C88();
void func_00101D38();
void func_00101E10();
void func_00101EB0();
void func_00101F60();
void func_00102030();
void func_001020D0();
void func_00102178();
void func_00102268();
void func_00102358();
void func_001023F8();
void func_001024B0();
void func_00102560();
void func_00102650();
void func_00102710();
void func_001027C0();
void func_00102870();
void func_00102920();
void func_001029D0();
void func_00102A70();
void func_00102B10();
void func_00102C28();
void func_00102D40();
void func_00102DE0();
void func_00102F10();
void func_00102FB0();
void func_001030E0();
void func_001031C0();
void func_00103260();
void func_00103350();
void func_00103420();
void func_001034F0();
void func_00103590();
void func_00103640();
void func_001036F0();
void func_001037A0();
void func_00103850();
void func_00103900();
void func_001039B0();
void func_00103A60();
void func_00103B40();
void func_00103C10();
void func_00103CC0();
void func_00103D70();
void func_00103E10();
void func_00103EB0();
void func_00103F80();
void func_00104020();
void func_001040C0();
void func_00104170();
void func_00104220();
void func_001042F0();
void func_001043A0();
void func_00104470();
void func_00104510();
void func_001045B0();
void func_00104660();
void func_00104710();
void func_001047C0();
void func_00104860();
void func_00104900();
void func_001049D8();
void func_00104A78();
void func_00104B18();
void func_00104C00();
void func_00104CA0();
void func_00104D40();
void func_00104DE0();
void func_00104E80();
void func_00104F50();
void func_00105020();
void func_001050D0();
void func_001051C0();
void func_00105290();
void func_00105360();
void func_00105430();
void func_00105500();
void func_001055A8();
void func_00105658();
void func_00105728();
void func_001057D8();
void func_00105878();
void func_00105960();
void func_00105A00();
void func_00105AB0();
void func_00105B60();
void func_00105C10();
void func_00105CC0();
void func_00105D60();
void func_00105E10();
void func_00105EC0();
void func_00105F70();
void func_00106048();
void func_00106120();
void func_001061C0();
void func_00106270();
void func_00106320();
void func_001063D0();
void func_001064C0();
void func_00106560();
void func_00106600();
void func_001066F0();
void func_001067A0();
void func_00106850();
void func_00106920();
void func_001069C0();
void func_00106A70();
void func_00106B10();
void func_00106BB0();
void func_00106C50();
void func_00106CF0();
void func_00106D90();
void func_00106E60();
void func_00106F00();
void func_00106FA0();
void func_00107040();
void func_001070E0();
void func_00107180();
void func_00107268();
void func_00107350();
void func_001073F0();
void func_001074C0();
void func_00107570();
void func_00107678();
void func_00107718();
void func_001077D8();
void func_00107898();
void func_00107948();
void func_00107A10();
void func_00107AB0();
void func_00107B60();
void func_00107C00();
void func_00107CB0();
void func_00107D60();
void func_00107E10();
void func_00107EC0();
void func_00107F70();
void func_00108038();
void func_00108128();
void func_00108208();
void func_001082E8();
void func_001083C8();
void func_00108498();
void func_00108548();
void func_001085E8();
void func_00108688();
void func_00108728();
void func_001087D8();
void func_00108878();
void func_00108928();
void func_001089C8();
void func_00108A98();
void func_00108B48();
void func_00108BE8();
void func_00108CC8();
void func_00108DA8();
void func_00108E70();
void func_00108F38();
void func_00109000();
void func_001090C8();
void func_001091A8();
void func_00109258();
void func_00109308();
void func_001093B8();
void func_00123C90();
void func_00123CB8();
void func_00123CE0();
void func_00123D40();
void func_00126A48();
void func_00126AB0();
void func_00127628();
void func_00127678();
void func_001288F0();
void func_001290B8();
void func_001290E0();
void func_00129108();
void func_00129170();
void func_00129188();
void func_001291A0();
void func_001291B8();
void func_00129228();
void func_00129288();
void func_001292B8();
void func_001292E8();
void func_00129318();
void func_00129348();
void func_00129378();
void func_001293A8();
void func_001293D8();
void func_00129440();
void func_00129450();
void func_00129480();
void func_001294B0();
void func_001294E0();
void func_00129510();
void func_00129540();
void func_00129598();
void func_001295C8();
void func_00129648();
void func_00129E10();
void func_00129E88();
void func_00129EE0();
void func_00129F58();
void func_00129FB0();
void func_0012A028();
void func_0012A080();
void func_0012A0F8();
void func_0012A150();
void func_0012A1A0();
void func_0012A200();
void func_0012A270();
void func_0012A2C0();
void func_0012A320();
void func_0012A390();
void func_0012A398();
void func_0012A3A0();
void func_0012A3C8();
void func_0012A3E8();
void func_0012A418();
void func_0012A430();
void func_0012A478();
void func_0012A4A0();
void func_0012A4E8();
void func_0012A528();
void func_0012A580();
void func_0012A5B8();
void func_0012A5D0();
void func_0012A610();
void func_0012A630();
void func_0012A678();
void func_0012A6A0();
void func_0012A6E0();
void func_0012A700();
void func_0012A748();
void func_0012A770();
void func_0012A7A8();
void func_0012A7C0();
void func_0012A7F8();
void func_0012A810();
void func_0012A848();
void func_0012A860();
void func_0012A888();
void func_0012A9C8();
void func_0012AA00();
void func_0012AA28();
void func_0012ABD0();
void func_0012AC08();
void func_0012AC88();
void func_0012ACA0();
void func_0012ACD8();
void func_0012ACF8();
void func_0012AD30();
void func_0012AD78();
void func_0012AD98();
void func_0012ADD0();
void func_0012AE08();
void func_0012AE20();
void func_0012AE58();
void func_0012AE78();
void func_0012AEB0();
void func_0012AEE8();
void func_0012AF00();
void func_0012B0B0();
void func_0012B128();
void func_0012B140();
void func_0012B180();
void func_0012B1A0();
void func_0012B1E0();
void func_0012B200();
void func_0012B238();
void func_0012B250();
void func_0012B260();
void func_0012B270();
void func_0012B278();
void func_0012B288();
void func_0012B290();
void func_0012B2A0();
void func_0012B2A8();
void func_0012B2B8();
void func_0012B2C0();
void func_0012B2D0();
void func_0012B2D8();
void func_0012B2F8();
void func_0012B420();
void func_0012B4C8();
void func_0012B550();
void func_0012B590();
void func_0012D448();
void func_0012F6B0();
void func_0012F6D0();
void func_0012F718();
void func_0012FCB0();
void func_0012FCD0();
void func_00130158();
void func_0013C950();
void func_0013D820();
void func_0013D868();
void func_0013D8B0();
void func_0013D900();
void func_0013D950();
void func_0013D9A0();
void func_0013D9E0();
void func_0013D9F0();
void func_0013DA30();
void func_0013DA48();
void func_0013DA80();
void func_0013DAB8();
void func_0013DAF0();
void func_0013DD78();
void func_0013F6F8();
void func_00140238();
void func_00140550();
void func_001405F0();
void func_00140618();
void func_00140660();
void func_00140688();
void func_001406B0();
void func_001406D0();
void func_001406F0();
void func_00140710();
void func_00140730();
void func_001419A0();
void func_001419C0();
void func_001419E0();
void func_001437C0();
void func_001437E8();
void func_00143810();
void func_00143838();
void func_00143860();
void func_00143888();
void func_001438B0();
void func_001438D8();
void func_00143900();
void func_00143920();
void func_00143940();
void func_00143968();
void func_00143988();
void func_001439A8();
void func_001439C8();
void func_001439E8();
void func_00143A38();
void func_00146240();
void func_0014C820();
void func_0014C838();
void func_0014F110();
void func_001503E0();
void func_00150770();
void func_00150780();
void func_00150790();
void func_00151A58();
void func_00155778();
void func_001557B8();
void func_00156000();
void func_00156030();
void func_00156060();
void func_00156108();
void func_00156178();
void func_00156218();
void func_00156250();
void func_00158DD8();
void func_00159068();
void func_0015B7B8();
void func_0015FBA0();
void func_00160050();
void func_0016D040();
void func_00177828();
void func_0017B410();
void func_0017B510();
void func_0017B8C0();
void func_00181DA8();
void func_00182E40();
void func_00183028();
void func_00183478();
void func_00184768();
void func_001847F0();
void func_00184818();
void func_00184838();
void func_00184858();
void func_00184878();
void func_00184898();
void func_001848B8();
void func_00184968();
void func_00184990();
void func_001849D0();
void func_00184A08();
void func_00184A38();
void func_00184CD0();
void func_00184D10();
void func_00184D20();
void func_00184D58();
void func_0018B460();
void func_001906E8();
void func_001906F0();
void func_00191C78();
void func_001920B0();
void func_00192498();
void func_00192990();
void func_00198ED8();
void func_00199380();
void func_00199398();
void func_00199C10();
void func_001A4858();
void func_001A4860();
void func_001A4868();
void func_001A4870();
void func_001A4878();
void func_001A6480();
void func_001A8110();
void func_001AF000();
void func_001AF028();
void func_001AF050();
void func_001AF078();
void func_001B64D8();
void func_001B6568();
void func_001B6598();
void func_001B65C8();
void func_001B65F8();
void func_001B6628();
void func_001B7100();
void func_001B9418();
void func_001BAFE0();
void func_001BB000();
void func_001BB058();
void func_001BB0C8();
void func_001BB138();
void func_001BB168();
void func_001BB1A0();
void func_001BB1D8();
void func_001BB378();
void func_001BB3B0();
void func_001BB400();
void func_001BB450();
void func_001BB710();
void func_001BC710();
void func_001BC748();
void func_001C0A50();
void func_001C0AB8();
void func_001C0B08();
void func_001C1030();
void func_001C3FC8();
void func_001C5E50();
void func_001C5EA8();
void func_001C8D40();
void func_001CA878();
void func_001CA888();
void func_001CA998();
void func_001CAAD0();
void func_001CAB00();
void func_001CAD28();
void func_001CB6A8();
void func_001CB6D0();
void func_001D27C0();
void func_001DAFB8();
void func_001DB0C8();
void func_001DB238();
void func_001DD5F8();
void func_001DD610();
void func_001DD628();
void func_001DD9A0();
void func_001DD9C0();
void func_001DD9D8();
void func_001DDA08();
void func_001DDA90();
void func_001DDAB8();
void func_001DDAC8();
void func_001DDCB0();
void func_001DDCC8();
void func_001DFBE0();
void func_001E2840();
void func_001E29E8();
void func_001E53F8();
void func_001ED050();
void func_001ED070();
void func_001EF828();
void func_001F3810();
void func_001F3830();
void func_001F3850();
void func_001F38A0();
void func_001F3BD8();
void func_001F3C08();
void func_001F4308();
void func_001F4760();
void func_001F5208();
void func_001F5840();
void func_001F5868();
void func_001F5930();

typedef void (*PropFn)();
struct Prop_2505D8 { s32 f0; s32 flags; union { f32 f; s32 i; } f8; s32 fC; s32 f10; s32 f14; s32 f18; s32 f1C; };
extern Prop_2505D8 D_002505D8[1179];

struct PropInit {
    static void Set0(Prop_2505D8* p, s32 v4, s32 v0, s32 vc) { p->f0 = v0; p->flags = v4; p->fC = vc; }
    static void Set1(Prop_2505D8* p, s32 v10, s32 vc, s32 v0, s32 v4, s32 v14) { p->f10 = v10; p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; }
    static void Set2(Prop_2505D8* p, s32 v0, s32 v4, s32 v18) { p->f0 = v0; p->flags = v4; p->f18 = v18; }
    static void Set3(Prop_2505D8* p, s32 v0, s32 v4, s32 v18, s32 v1c) { p->f18 = v18; p->f0 = v0; p->f1C = v1c; p->flags = v4; }
    static void Set4(Prop_2505D8* p, s32 v4, s32 v0, s32 vc, s32 v14) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; }
    static void Set5(Prop_2505D8* p, s32 v4, s32 v14, s32 vc, s32 v0, s32 v18) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f14 = v14; p->f18 = v18; }
    static void Set6(Prop_2505D8* p, s32 v14, s32 v0, s32 v4, s32 v18) { p->f0 = v0; p->flags = v4; p->f14 = v14; p->f18 = v18; }
    static void Set7(Prop_2505D8* p, s32 v0, s32 v4) { p->flags = v4; p->f0 = v0; }
    static void Set8(Prop_2505D8* p, s32 v0, s32 v4, s32 vc, s32 v18) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = v18; }
    static void Set8m(Prop_2505D8* p, s32 v0, s32 vc, s32 v4) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = vc; }
    static void Set9(Prop_2505D8* p, s32 v4, s32 v0, s32 v14) { p->f14 = v14; p->flags = v4; p->f0 = v0; }
    static void Set10(Prop_2505D8* p, s32 v0, s32 v4, s32 v18, s32 vc, s32 v14, f32 v8) { p->f0 = v0; p->f14 = v14; p->f8.f = v8; p->fC = vc; p->f18 = v18; p->flags = v4; }
    static void Set11(Prop_2505D8* p, s32 v18, s32 v8, s32 v14, s32 vc, s32 v0, s32 v4) { p->f18 = v18; p->f14 = v14; p->f8.i = v8; p->fC = vc; p->f0 = v0; p->flags = v4; }
    static void Set12(Prop_2505D8* p, s32 v4, s32 v18, s32 v8, s32 v0) { p->f0 = v0; p->flags = v4; p->f8.i = v8; p->f18 = v18; }
    static void Set13(Prop_2505D8* p, s32 v14, s32 v4, s32 v0, s32 v1c) { p->f1C = v1c; p->flags = v4; p->f14 = v14; p->f0 = v0; }
    static void Set14(Prop_2505D8* p, s32 v4, s32 v0, s32 vc, s32 v14, s32 v18, s32 v1c) { p->flags = v4; p->f0 = v0; p->fC = vc; p->f14 = v14; p->f18 = v18; p->f1C = v1c; }
    static void Set15(Prop_2505D8* p, s32 v18, f32 v8, s32 v0, s32 v4) { p->f0 = v0; p->flags = v4; p->f8.f = v8; p->f18 = v18; }
    static void Set16(Prop_2505D8* p, s32 v0, s32 vc, s32 v18, s32 v1c, s32 v4) { p->f0 = v0; p->flags = v4; p->fC = vc; p->f18 = v18; p->f1C = v1c; }
    static void Set17(Prop_2505D8* p, s32 vc, s32 v18, s32 v8, s32 v0, s32 v4) { p->flags = v4; p->f8.i = v8; p->fC = vc; p->f0 = v0; p->f18 = v18; }
};

void func_00109488()
{
    Prop_2505D8* p = D_002505D8;
    PropInit::Set0(p, 4, 7, (s32)func_00130158); p++;
    PropInit::Set1(p, (s32)func_001000C8, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00100218, (s32)func_00100178, 18, 1025, 0); p++;
    PropInit::Set2(p, 10, 256, (s32)func_00182E40); p++;
    PropInit::Set1(p, (s32)func_001002C0, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00100368, 0, 8193, 1, 2); p++;
    PropInit::Set0(p, 2, 8300, 20); p++;
    PropInit::Set0(p, 4, 0, (s32)func_00183028); p++;
    PropInit::Set0(p, 2, 8194, 24); p++;
    PropInit::Set1(p, (s32)func_00100438, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001004F0, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 2, 6, 8); p++;
    PropInit::Set0(p, 4, 6, (s32)func_00183478); p++;
    PropInit::Set1(p, (s32)func_001005A0, 0, 0, 1, 1); p++;
    PropInit::Set1(p, 0, (s32)func_00100650, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00100720, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_001007F0, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_001008B8, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00100998, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00100A78, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00100B48, 18, 1024, 2); p++;
    PropInit::Set2(p, 2, 256, (s32)func_001290B8); p++;
    PropInit::Set2(p, 2, 256, (s32)func_001290E0); p++;
    PropInit::Set3(p, 6, 4224, 4, (s32)func_00129108); p++;
    PropInit::Set3(p, 1, 4224, 12, (s32)func_00129108); p++;
    PropInit::Set3(p, 1, 4224, 16, (s32)func_00129108); p++;
    PropInit::Set3(p, 4172, 4224, 8, (s32)func_00129108); p++;
    PropInit::Set1(p, (s32)func_00100C28, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)func_0015FBA0); p++;
    PropInit::Set4(p, 66, 2, 256, 132); p++;
    PropInit::Set4(p, 18, 2, 400, 400); p++;
    PropInit::Set0(p, 2, 2, 320); p++;
    PropInit::Set4(p, 66, 4, 208, 136); p++;
    PropInit::Set4(p, 18, 4, 416, 416); p++;
    PropInit::Set0(p, 2, 4, 272); p++;
    PropInit::Set5(p, 292, (s32)func_00129648, (s32)func_001295C8, 2, (s32)func_00129648); p++;
    PropInit::Set4(p, 36, 2, (s32)func_00127678, (s32)func_00127628); p++;
    PropInit::Set4(p, 66, 2, 352, 148); p++;
    PropInit::Set0(p, 2, 2, 368); p++;
    PropInit::Set0(p, 2, 2, 384); p++;
    PropInit::Set0(p, 2, 8194, 80); p++;
    PropInit::Set5(p, 292, (s32)func_00129170, (s32)func_00129188, 1, (s32)func_00129170); p++;
    PropInit::Set5(p, 292, (s32)func_001291A0, (s32)func_001291B8, 1, (s32)func_001291A0); p++;
    PropInit::Set5(p, 292, (s32)func_00129228, (s32)func_00129440, 0, (s32)func_00129228); p++;
    PropInit::Set5(p, 292, (s32)func_00129288, (s32)func_00129450, 6, (s32)func_00129288); p++;
    PropInit::Set5(p, 292, (s32)func_001292B8, (s32)func_00129480, 1, (s32)func_001292B8); p++;
    PropInit::Set5(p, 292, (s32)func_001292E8, (s32)func_001294B0, 1, (s32)func_001292E8); p++;
    PropInit::Set5(p, 292, (s32)func_00129318, (s32)func_001294E0, 1, (s32)func_00129318); p++;
    PropInit::Set5(p, 292, (s32)func_00129348, (s32)func_00129510, 1, (s32)func_00129348); p++;
    PropInit::Set5(p, 292, (s32)func_00129378, (s32)func_00129540, 1, (s32)func_00129378); p++;
    PropInit::Set5(p, 292, (s32)func_001293A8, (s32)func_00129598, 2, (s32)func_001293A8); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001293D8); p++;
    PropInit::Set6(p, (s32)func_0012A3C8, 0, 288, (s32)func_0012A3C8); p++;
    PropInit::Set5(p, 292, (s32)func_0012A3E8, (s32)func_0012A418, 4196, (s32)func_0012A3E8); p++;
    PropInit::Set2(p, 0, 256, (s32)func_0012A3A0); p++;
    PropInit::Set2(p, 4110, 256, (s32)func_0012A430); p++;
    PropInit::Set6(p, (s32)func_00129E10, 1, 288, (s32)func_00129E10); p++;
    PropInit::Set6(p, (s32)func_00129E88, 9, 288, (s32)func_00129E88); p++;
    PropInit::Set6(p, (s32)func_00129EE0, 1, 288, (s32)func_00129EE0); p++;
    PropInit::Set6(p, (s32)func_00129F58, 9, 288, (s32)func_00129F58); p++;
    PropInit::Set2(p, 0, 256, (s32)func_0012A478); p++;
    PropInit::Set2(p, 4110, 256, (s32)func_0012A4A0); p++;
    PropInit::Set6(p, (s32)func_0012A4E8, 5, 288, (s32)func_0012A4E8); p++;
    PropInit::Set6(p, (s32)func_00129FB0, 1, 288, (s32)func_00129FB0); p++;
    PropInit::Set6(p, (s32)func_0012A028, 9, 288, (s32)func_0012A028); p++;
    PropInit::Set6(p, (s32)func_0012A080, 1, 288, (s32)func_0012A080); p++;
    PropInit::Set6(p, (s32)func_0012A0F8, 9, 288, (s32)func_0012A0F8); p++;
    PropInit::Set6(p, (s32)func_0012A150, 1, 288, (s32)func_0012A150); p++;
    PropInit::Set6(p, (s32)func_0012A200, 12, 288, (s32)func_0012A200); p++;
    PropInit::Set6(p, (s32)func_0012A270, 1, 288, (s32)func_0012A270); p++;
    PropInit::Set6(p, (s32)func_0012A320, 12, 288, (s32)func_0012A320); p++;
    PropInit::Set6(p, (s32)func_0012A1A0, 1, 288, (s32)func_0012A1A0); p++;
    PropInit::Set6(p, (s32)func_0012A2C0, 1, 288, (s32)func_0012A2C0); p++;
    PropInit::Set2(p, 4110, 256, (s32)func_0012A390); p++;
    PropInit::Set2(p, 4110, 256, (s32)func_0012A398); p++;
    PropInit::Set7(p, 3, 0); p++;
    PropInit::Set2(p, 4110, 256, (s32)func_0012A528); p++;
    PropInit::Set5(p, 292, (s32)func_0012A580, (s32)func_0012A5B8, 1, (s32)func_0012A580); p++;
    PropInit::Set5(p, 292, (s32)func_0012A5D0, (s32)func_0012A610, 9, (s32)func_0012A5D0); p++;
    PropInit::Set5(p, 292, (s32)func_0012A630, (s32)func_0012A678, 10, (s32)func_0012A630); p++;
    PropInit::Set5(p, 292, (s32)func_0012A6A0, (s32)func_0012A6E0, 9, (s32)func_0012A6A0); p++;
    PropInit::Set5(p, 292, (s32)func_0012A700, (s32)func_0012A748, 10, (s32)func_0012A700); p++;
    PropInit::Set5(p, 292, (s32)func_0012A770, (s32)func_0012A7A8, 5, (s32)func_0012A770); p++;
    PropInit::Set5(p, 292, (s32)func_0012A7C0, (s32)func_0012A7F8, 5, (s32)func_0012A7C0); p++;
    PropInit::Set8(p, 6, 260, (s32)func_0012A848, (s32)func_0012A810); p++;
    PropInit::Set4(p, 36, 8194, (s32)func_0012A888, (s32)func_0012A860); p++;
    PropInit::Set1(p, (s32)func_00100CC8, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00100D68, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00100E08, (s32)func_00100E08, 18, 1025, 3); p++;
    PropInit::Set0(p, 4, -2147475455, (s32)func_001288F0); p++;
    PropInit::Set1(p, (s32)func_00100EE0, 0, 18, 1, 2); p++;
    PropInit::Set6(p, (s32)func_0012A9C8, 4127, 288, (s32)func_0012A9C8); p++;
    PropInit::Set6(p, (s32)func_0012AA00, 1, 288, (s32)func_0012AA00); p++;
    PropInit::Set6(p, (s32)func_0012AA28, 0, 288, (s32)func_0012AA28); p++;
    PropInit::Set1(p, (s32)func_00100FA8, 0, 18, 1, 1); p++;
    PropInit::Set6(p, (s32)func_00126AB0, 5, 288, (s32)func_00126AB0); p++;
    PropInit::Set9(p, 32, 5, (s32)func_00126A48); p++;
    PropInit::Set5(p, 292, (s32)func_0012B0B0, (s32)func_0012B128, 4160, (s32)func_0012B0B0); p++;
    PropInit::Set5(p, 292, (s32)func_0012B140, (s32)func_0012B180, 2, (s32)func_0012B140); p++;
    PropInit::Set5(p, 292, (s32)func_0012B1A0, (s32)func_0012B1E0, 2, (s32)func_0012B1A0); p++;
    PropInit::Set5(p, 292, (s32)func_0012B200, (s32)func_0012B238, 1, (s32)func_0012B200); p++;
    PropInit::Set5(p, 292, (s32)func_0012AC08, (s32)func_0012AC88, 14, (s32)func_0012ABD0); p++;
    PropInit::Set8(p, 1, 260, (s32)func_0012ACD8, (s32)func_0012ACA0); p++;
    PropInit::Set8(p, 1, 260, (s32)func_0012AD78, (s32)func_0012ACF8); p++;
    PropInit::Set5(p, 292, (s32)func_0012AE20, (s32)func_0012AE58, 1, (s32)func_0012AD98); p++;
    PropInit::Set5(p, 292, (s32)func_0012AEB0, (s32)func_0012AEE8, 1, (s32)func_0012AE78); p++;
    PropInit::Set8(p, 10, 260, (s32)func_0012AF00, (s32)func_0012AD30); p++;
    PropInit::Set1(p, (s32)func_00101058, 0, 18, 1, 5); p++;
    PropInit::Set1(p, (s32)func_00101168, 0, 18, 1, 0); p++;
    PropInit::Set8(p, 1, 260, (s32)func_0012AE08, (s32)func_0012ADD0); p++;
    PropInit::Set5(p, 292, (s32)func_0012B250, (s32)func_0012B260, 4163, (s32)func_0012B250); p++;
    PropInit::Set5(p, 292, (s32)func_0012B270, (s32)func_0012B278, 4163, (s32)func_0012B270); p++;
    PropInit::Set5(p, 292, (s32)func_0012B288, (s32)func_0012B290, 4163, (s32)func_0012B288); p++;
    PropInit::Set5(p, 292, (s32)func_0012B2A0, (s32)func_0012B2A8, 4163, (s32)func_0012B2A0); p++;
    PropInit::Set5(p, 292, (s32)func_0012B2B8, (s32)func_0012B2C0, 4163, (s32)func_0012B2B8); p++;
    PropInit::Set5(p, 292, (s32)func_0012B2D0, (s32)func_0012B2D8, 4163, (s32)func_0012B2D0); p++;
    PropInit::Set9(p, 32, 6, (s32)func_0012B2F8); p++;
    PropInit::Set1(p, (s32)func_00101208, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001012B8, 0, 18, 1, 1); p++;
    PropInit::Set8(p, 0, 258, 660, (s32)func_0012B4C8); p++;
    PropInit::Set1(p, (s32)func_00101368, 0, 8339, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00101418, 0, 8338, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001014C8, 0, 8338, 1, 0); p++;
    PropInit::Set6(p, (s32)func_0012B420, 0, 288, (s32)func_0012B420); p++;
    PropInit::Set1(p, (s32)func_00101568, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 292, (s32)func_0012B550, (s32)func_0012B590, 0, (s32)func_0012B550); p++;
    PropInit::Set1(p, (s32)func_00101620, 0, 18, 1, 2); p++;
    PropInit::Set4(p, 34, 1, 872, (s32)func_001B9418); p++;
    PropInit::Set6(p, (s32)func_001BB1D8, 4111, 288, (s32)func_001BB1D8); p++;
    PropInit::Set5(p, 146, 848, 848, 2, 848); p++;
    PropInit::Set2(p, 0, 256, (s32)func_001BB000); p++;
    PropInit::Set6(p, (s32)func_001BB058, 4096, 288, (s32)func_001BB058); p++;
    PropInit::Set6(p, (s32)func_001BB0C8, 4096, 288, (s32)func_001BB0C8); p++;
    PropInit::Set2(p, 1, 256, (s32)func_001BAFE0); p++;
    PropInit::Set10(p, 1, 2194, 864, 864, 864, 0.5f); p++;
    PropInit::Set10(p, 1, 2194, 868, 868, 868, 1.0f); p++;
    PropInit::Set6(p, (s32)func_001BB168, 0, 288, (s32)func_001BB168); p++;
    PropInit::Set2(p, 0, 256, (s32)func_001BB1A0); p++;
    PropInit::Set6(p, (s32)func_001BB378, 0, 288, (s32)func_001BB378); p++;
    PropInit::Set6(p, (s32)func_001BB3B0, 0, 288, (s32)func_001BB3B0); p++;
    PropInit::Set6(p, (s32)func_001BB400, 0, 288, (s32)func_001BB400); p++;
    PropInit::Set6(p, (s32)func_001BB450, 0, 288, (s32)func_001BB450); p++;
    PropInit::Set0(p, 4, -2147475453, (s32)func_001BB710); p++;
    PropInit::Set5(p, 146, 1248, 1248, 4129, 1248); p++;
    PropInit::Set0(p, 2, 1, 976); p++;
    PropInit::Set2(p, 4132, 256, (s32)func_001BB138); p++;
    PropInit::Set1(p, (s32)func_001016F0, (s32)func_001016F0, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_001017A0, 0, 0, 1, 1); p++;
    PropInit::Set5(p, 292, (s32)func_001BC710, (s32)func_001BC748, 0, (s32)func_001BC710); p++;
    PropInit::Set4(p, 18, 2, 64, 64); p++;
    PropInit::Set4(p, 18, 4, 80, 80); p++;
    PropInit::Set0(p, 4, 2, (s32)func_001F3BD8); p++;
    PropInit::Set0(p, 4, 4, (s32)func_001F3C08); p++;
    PropInit::Set4(p, 18, 2, 128, 128); p++;
    PropInit::Set5(p, 146, 128, 128, 1, 128); p++;
    PropInit::Set5(p, 146, 132, 132, 1, 132); p++;
    PropInit::Set5(p, 146, 136, 136, 1, 136); p++;
    PropInit::Set8m(p, 0, 144, 130); p++;
    PropInit::Set8m(p, 0, 148, 130); p++;
    PropInit::Set5(p, 146, 176, 176, 6, 176); p++;
    PropInit::Set5(p, 290, (s32)func_001F4308, 156, 1, (s32)func_001F4308); p++;
    PropInit::Set1(p, (s32)func_00101860, (s32)func_00101860, 18, 1025, 4); p++;
    PropInit::Set1(p, (s32)func_00101950, 0, 18, 1, 0); p++;
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
    PropInit::Set1(p, (s32)func_001019F0, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 34, 4200, 740, (s32)func_001F4760); p++;
    PropInit::Set4(p, 18, 2, 64, 64); p++;
    PropInit::Set0(p, 4, 2, (s32)func_001920B0); p++;
    PropInit::Set12(p, 2176, 68, 0, 4098); p++;
    PropInit::Set12(p, 2176, 72, 0, 0); p++;
    PropInit::Set12(p, 2176, 76, 0, 0); p++;
    PropInit::Set2(p, 5, 128, 120); p++;
    PropInit::Set10(p, 1, 2194, 124, 124, 124, 1.0f); p++;
    PropInit::Set2(p, 9, 128, 128); p++;
    PropInit::Set2(p, 10, 128, 144); p++;
    PropInit::Set1(p, (s32)func_00101A90, 0, 8338, 1, 4); p++;
    PropInit::Set1(p, (s32)func_00101B80, 0, 8338, 1, 5); p++;
    PropInit::Set1(p, (s32)func_00101C88, 0, 1, 1, 1); p++;
    PropInit::Set0(p, 2, 1, 52); p++;
    PropInit::Set8m(p, 0, 80, 130); p++;
    PropInit::Set0(p, 2, 8323, 8); p++;
    PropInit::Set0(p, 2, 8194, 12); p++;
    PropInit::Set0(p, 2, 1, 20); p++;
    PropInit::Set4(p, 34, 1, 24, (s32)func_0012F6B0); p++;
    PropInit::Set4(p, 34, 1, 28, (s32)func_0012F6D0); p++;
    PropInit::Set4(p, 34, 5, 232, (s32)func_0012F718); p++;
    PropInit::Set4(p, 34, 0, 36, (s32)func_0012D448); p++;
    PropInit::Set1(p, (s32)func_00101D38, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)func_00101E10, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00101EB0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00101F60, 0, 18, 1, 2); p++;
    PropInit::Set11(p, 1408, 1, 1408, 1408, 0, 2194); p++;
    PropInit::Set11(p, 1420, 1, 1420, 1420, 0, 2194); p++;
    PropInit::Set5(p, 146, 1392, 1392, 2, 1392); p++;
    PropInit::Set3(p, 6, 4352, (s32)func_001F5840, (s32)func_001EF828); p++;
    PropInit::Set13(p, (s32)func_001F5868, 4128, 8193, (s32)func_001EF828); p++;
    PropInit::Set13(p, (s32)func_001F5930, 4128, 8193, (s32)func_001EF828); p++;
    PropInit::Set1(p, (s32)func_00102030, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1432, 1432, 1, 1432); p++;
    PropInit::Set5(p, 146, 1436, 1436, 0, 1436); p++;
    PropInit::Set5(p, 146, 1412, 1412, 0, 1412); p++;
    PropInit::Set5(p, 146, 1416, 1416, 0, 1416); p++;
    PropInit::Set2(p, 6, 256, (s32)func_0013D868); p++;
    PropInit::Set2(p, 6, 256, (s32)func_0013D8B0); p++;
    PropInit::Set2(p, 6, 256, (s32)func_0013D900); p++;
    PropInit::Set2(p, 6, 256, (s32)func_0013D950); p++;
    PropInit::Set11(p, 1660, 0, 1660, 1660, 0, 2194); p++;
    PropInit::Set5(p, 146, 1572, 1572, 1, 1572); p++;
    PropInit::Set12(p, 2176, 1592, -1, 6); p++;
    PropInit::Set5(p, 146, 1576, 1576, 10, 1576); p++;
    PropInit::Set10(p, 1, 2194, 1584, 1584, 1584, 300.0f); p++;
    PropInit::Set10(p, 1, 2194, 1588, 1588, 1588, 3.0f); p++;
    PropInit::Set2(p, 6, 256, (s32)func_0013DA48); p++;
    PropInit::Set2(p, 7, 256, (s32)func_0013DA80); p++;
    PropInit::Set2(p, 7, 256, (s32)func_0013DAB8); p++;
    PropInit::Set5(p, 292, (s32)func_0013D9A0, (s32)func_0013D9E0, 0, (s32)func_0013D9A0); p++;
    PropInit::Set5(p, 292, (s32)func_0013D9F0, (s32)func_0013DA30, 0, (s32)func_0013D9F0); p++;
    PropInit::Set5(p, 146, 1676, 1676, 5, 1676); p++;
    PropInit::Set1(p, (s32)func_001020D0, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 34, 0, 1664, (s32)func_0013D820); p++;
    PropInit::Set5(p, 146, 1684, 1684, 0, 1684); p++;
    PropInit::Set11(p, 1564, 1, 1564, 1564, 4162, 2194); p++;
    PropInit::Set5(p, 146, 1568, 1568, 1, 1568); p++;
    PropInit::Set5(p, 146, 1688, 1688, 5, 1688); p++;
    PropInit::Set5(p, 146, 1696, 1696, 2, 1696); p++;
    PropInit::Set5(p, 146, 1712, 1712, 0, 1712); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)func_0013DAF0); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)func_0013DAF0); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)func_0013DAF0); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)func_0013DAF0); p++;
    PropInit::Set2(p, 6, 128, 1556); p++;
    PropInit::Set5(p, 146, 1668, 1668, 0, 1668); p++;
    PropInit::Set5(p, 146, 1728, 1728, 1, 1728); p++;
    PropInit::Set5(p, 146, 1732, 1732, 4096, 1732); p++;
    PropInit::Set5(p, 146, 1736, 1736, 4096, 1736); p++;
    PropInit::Set4(p, 18, 8195, 1740, 1740); p++;
    PropInit::Set5(p, 146, 1744, 1744, 4124, 1744); p++;
    PropInit::Set10(p, 1, 2194, 1372, 1372, 1372, 1.5f); p++;
    PropInit::Set10(p, 1, 2194, 1368, 1368, 1368, 10.0f); p++;
    PropInit::Set5(p, 290, (s32)func_0013DD78, 1360, 4146, (s32)func_0013DD78); p++;
    PropInit::Set5(p, 146, 1380, 1380, 0, 1380); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001405F0); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00140660); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001406B0); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001406D0); p++;
    PropInit::Set2(p, 7, 256, (s32)func_001406F0); p++;
    PropInit::Set2(p, 7, 256, (s32)func_00140710); p++;
    PropInit::Set10(p, 1, 2194, 1660, 1660, 1660, 1.0f); p++;
    PropInit::Set12(p, 2176, 1360, 0, 4105); p++;
    PropInit::Set15(p, 1644, 1.0f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 1672, 0, 0); p++;
    PropInit::Set12(p, 2176, 1676, 0, 0); p++;
    PropInit::Set12(p, 2176, 1680, 0, 0); p++;
    PropInit::Set12(p, 2176, 1648, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00102178, (s32)func_00102178, 18, 1025, 4); p++;
    PropInit::Set2(p, 6, 128, 1684); p++;
    PropInit::Set4(p, 34, 4187, 1664, (s32)func_0013F6F8); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00140618); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00140688); p++;
    PropInit::Set10(p, 1, 2194, 1768, 1768, 1768, 1.0f); p++;
    PropInit::Set15(p, 1752, 1.0f, 1, 2176); p++;
    PropInit::Set12(p, 2176, 1780, 1, 0); p++;
    PropInit::Set12(p, 2176, 1784, 0, 0); p++;
    PropInit::Set12(p, 2176, 1756, 0, 0); p++;
    PropInit::Set11(p, 1932, 1, 1932, 1932, 0, 2194); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00140730); p++;
    PropInit::Set1(p, (s32)func_00102268, (s32)func_00102268, 18, 1025, 4); p++;
    PropInit::Set11(p, 1936, 0, 1936, 1936, 0, 2194); p++;
    PropInit::Set0(p, 4, -2147475455, (s32)func_00140550); p++;
    PropInit::Set2(p, 6, 128, 1792); p++;
    PropInit::Set4(p, 34, 4187, 1772, (s32)func_00140238); p++;
    PropInit::Set5(p, 290, (s32)func_00192990, 1360, 0, (s32)func_00192990); p++;
    PropInit::Set1(p, (s32)func_00102358, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_001023F8, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 4, 4198, (s32)func_00192498); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00160050); p++;
    PropInit::Set15(p, 1360, 100.0f, 1, 2176); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00198ED8); p++;
    PropInit::Set5(p, 146, 1368, 1368, 0, 1368); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00123C90); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00123CB8); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00123CE0); p++;
    PropInit::Set11(p, 1576, 0, 1576, 1576, 0, 2194); p++;
    PropInit::Set11(p, 1376, 0, 1376, 1376, 1, 2194); p++;
    PropInit::Set0(p, 2, 4137, 1360); p++;
    PropInit::Set0(p, 4, -2147475408, (s32)func_00123D40); p++;
    PropInit::Set1(p, (s32)func_001024B0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00102560, (s32)func_00102560, 18, 1025, 4); p++;
    PropInit::Set0(p, 2, 8239, 1728); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001AF000); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001AF028); p++;
    PropInit::Set2(p, 7, 256, (s32)func_001AF050); p++;
    PropInit::Set2(p, 7, 256, (s32)func_001AF078); p++;
    PropInit::Set11(p, 1460, 0, 1460, 1460, 0, 2194); p++;
    PropInit::Set10(p, 1, 2194, 1464, 1464, 1464, 1.0f); p++;
    PropInit::Set10(p, 1, 2194, 1468, 1468, 1468, 1.0f); p++;
    PropInit::Set11(p, 1376, 1, 1376, 1376, 4140, 2194); p++;
    PropInit::Set0(p, 2, 8239, 1360); p++;
    PropInit::Set0(p, 2, 4140, 1368); p++;
    PropInit::Set0(p, 2, 4139, 1364); p++;
    PropInit::Set4(p, 18, 0, 1472, 1472); p++;
    PropInit::Set1(p, (s32)func_00102650, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00102710, 0, 18, 1, 0); p++;
    PropInit::Set11(p, 1488, 0, 1488, 1488, 4141, 2194); p++;
    PropInit::Set10(p, 1, 2194, 2796, 2796, 2796, 0.25f); p++;
    PropInit::Set1(p, (s32)func_001027C0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00102870, 0, 18, 1, 1); p++;
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
    PropInit::Set2(p, 6, 256, (s32)func_0012FCB0); p++;
    PropInit::Set2(p, 7, 256, (s32)func_0012FCD0); p++;
    PropInit::Set2(p, 0, 128, 1360); p++;
    PropInit::Set2(p, 6, 128, 1424); p++;
    PropInit::Set5(p, 290, (s32)func_00156108, 728, 5, (s32)func_00156108); p++;
    PropInit::Set5(p, 290, (s32)func_00156178, 776, 0, (s32)func_00156178); p++;
    PropInit::Set14(p, 4242, 4148, 724, 724, 724, (s32)func_001557B8); p++;
    PropInit::Set14(p, 4242, 10, 732, 732, 732, (s32)func_001557B8); p++;
    PropInit::Set14(p, 4242, 1, 756, 756, 756, (s32)func_001557B8); p++;
    PropInit::Set14(p, 4242, 1, 744, 744, 744, (s32)func_001557B8); p++;
    PropInit::Set14(p, 4242, 10, 748, 748, 748, (s32)func_001557B8); p++;
    PropInit::Set4(p, 36, 0, (s32)func_00156030, (s32)func_00156000); p++;
    PropInit::Set8m(p, 0, 740, 130); p++;
    PropInit::Set8m(p, 6, 760, 130); p++;
    PropInit::Set8m(p, 6, 764, 130); p++;
    PropInit::Set8m(p, 6, 768, 130); p++;
    PropInit::Set8m(p, 6, 772, 130); p++;
    PropInit::Set8m(p, 6, 784, 130); p++;
    PropInit::Set1(p, (s32)func_00102920, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001029D0, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00102A70, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)func_00156060); p++;
    PropInit::Set16(p, 4118, 16, 16, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 2, 32, 32, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 2, 32, 32, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 2, 48, 48, (s32)func_00155778, 4226); p++;
    PropInit::Set8m(p, 6, 780, 130); p++;
    PropInit::Set14(p, 4242, 4119, 80, 80, 80, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 112, 112, 112, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 4121, 128, 128, 128, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 160, 160, 160, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 168, 168, 168, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 2, 176, 176, 176, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 192, 192, 192, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 196, 196, 196, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 2, 208, 208, 208, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 4120, 224, 224, 224, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 228, 228, 228, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 5, 236, 236, 236, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 240, 240, 240, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 244, 244, 244, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 248, 248, 248, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 256, 256, 256, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 9, 272, 272, 272, (s32)func_00155778); p++;
    PropInit::Set16(p, 4117, 288, 288, (s32)func_00155778, 4226); p++;
    PropInit::Set2(p, 4115, 256, (s32)func_00156218); p++;
    PropInit::Set16(p, 4115, 436, 436, (s32)func_00155778, 4226); p++;
    PropInit::Set14(p, 4242, 10, 464, 464, 464, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 9, 448, 448, 448, (s32)func_00155778); p++;
    PropInit::Set16(p, 4116, 484, 484, (s32)func_00155778, 4226); p++;
    PropInit::Set14(p, 4242, 1, 488, 488, 488, (s32)func_00155778); p++;
    PropInit::Set16(p, 6, 308, 308, (s32)func_00155778, 4226); p++;
    PropInit::Set14(p, 4242, 9, 320, 320, 320, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 9, 336, 336, 336, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 9, 352, 352, 352, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 0, 368, 368, 368, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 372, 372, 372, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 0, 376, 376, 376, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 4149, 304, 304, 304, (s32)func_00155778); p++;
    PropInit::Set16(p, 6, 392, 392, (s32)func_00155778, 4226); p++;
    PropInit::Set14(p, 4242, 4150, 400, 400, 400, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 1, 404, 404, 404, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 4151, 408, 408, 408, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 10, 412, 412, 412, (s32)func_00155778); p++;
    PropInit::Set14(p, 4242, 0, 420, 420, 420, (s32)func_00155778); p++;
    PropInit::Set1(p, 0, (s32)func_00102B10, 18, 1024, 6); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 0, 500, 500, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 6, 496, 496, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 1, 496, 496, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 1, 504, 504, (s32)func_00155778, 4226); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)func_00155778, 4226); p++;
    PropInit::Set14(p, 4242, 4118, 16, 16, 16, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 48, 48, 48, (s32)func_00158DD8); p++;
    PropInit::Set8m(p, 6, 148, 130); p++;
    PropInit::Set8m(p, 6, 152, 130); p++;
    PropInit::Set14(p, 4242, 4119, 80, 80, 80, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 96, 96, 96, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 112, 112, 112, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 4121, 128, 128, 128, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 160, 160, 160, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 168, 168, 168, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 228, 228, 228, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 5, 236, 236, 236, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 240, 240, 240, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 248, 248, 248, (s32)func_00158DD8); p++;
    PropInit::Set1(p, 0, (s32)func_00102C28, 18, 1024, 6); p++;
    PropInit::Set5(p, 146, 164, 164, 10, 164); p++;
    PropInit::Set8m(p, 6, 172, 130); p++;
    PropInit::Set8m(p, 6, 180, 130); p++;
    PropInit::Set8m(p, 6, 176, 130); p++;
    PropInit::Set5(p, 146, 184, 184, 1, 184); p++;
    PropInit::Set5(p, 146, 188, 188, 0, 188); p++;
    PropInit::Set14(p, 4242, 2, 176, 176, 176, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 192, 192, 192, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 196, 196, 196, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 2, 208, 208, 208, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 4120, 224, 224, 224, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 244, 244, 244, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 256, 256, 256, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 9, 272, 272, 272, (s32)func_00158DD8); p++;
    PropInit::Set16(p, 4117, 288, 288, (s32)func_00158DD8, 4226); p++;
    PropInit::Set2(p, 4115, 256, (s32)func_00156250); p++;
    PropInit::Set16(p, 4115, 436, 436, (s32)func_00158DD8, 4226); p++;
    PropInit::Set14(p, 4242, 10, 464, 464, 464, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 9, 448, 448, 448, (s32)func_00158DD8); p++;
    PropInit::Set16(p, 4116, 484, 484, (s32)func_00158DD8, 4226); p++;
    PropInit::Set14(p, 4242, 1, 488, 488, 488, (s32)func_00158DD8); p++;
    PropInit::Set16(p, 6, 308, 308, (s32)func_00158DD8, 4226); p++;
    PropInit::Set14(p, 4242, 9, 320, 320, 320, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 9, 336, 336, 336, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 9, 352, 352, 352, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 0, 368, 368, 368, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 372, 372, 372, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 0, 376, 376, 376, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 4149, 304, 304, 304, (s32)func_00158DD8); p++;
    PropInit::Set16(p, 6, 392, 392, (s32)func_00158DD8, 4226); p++;
    PropInit::Set14(p, 4242, 4150, 400, 400, 400, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 1, 404, 404, 404, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 4151, 408, 408, 408, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 10, 412, 412, 412, (s32)func_00158DD8); p++;
    PropInit::Set14(p, 4242, 0, 420, 420, 420, (s32)func_00158DD8); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 0, 500, 500, (s32)func_00158DD8, 4226); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)func_00159068); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)func_00159068); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)func_00159068); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)func_00159068); p++;
    PropInit::Set1(p, (s32)func_00102D40, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00102DE0, 0, 18, 1, 6); p++;
    PropInit::Set16(p, 6, 496, 496, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 1, 496, 496, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 1, 500, 500, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 1, 504, 504, (s32)func_00158DD8, 4226); p++;
    PropInit::Set16(p, 0, 496, 496, (s32)func_00158DD8, 4226); p++;
    PropInit::Set1(p, (s32)func_00102F10, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00102FB0, 0, 18, 1, 6); p++;
    PropInit::Set5(p, 290, (s32)func_00184768, 720, 4122, (s32)func_00184768); p++;
    PropInit::Set5(p, 162, (s32)func_001847F0, 736, 2, 736); p++;
    PropInit::Set5(p, 162, (s32)func_00184818, 752, 1, 752); p++;
    PropInit::Set5(p, 162, (s32)func_00184838, 756, 1, 756); p++;
    PropInit::Set5(p, 162, (s32)func_00184858, 760, 1, 760); p++;
    PropInit::Set5(p, 162, (s32)func_00184878, 764, 1, 764); p++;
    PropInit::Set5(p, 162, (s32)func_00184898, 768, 1, 768); p++;
    PropInit::Set5(p, 290, (s32)func_001848B8, 784, 2, (s32)func_001848B8); p++;
    PropInit::Set5(p, 290, (s32)func_00184968, 772, 0, (s32)func_00184968); p++;
    PropInit::Set5(p, 290, (s32)func_00184968, 772, 0, (s32)func_00184968); p++;
    PropInit::Set5(p, 146, 776, 776, 0, 776); p++;
    PropInit::Set5(p, 162, (s32)func_00184990, 816, 10, 816); p++;
    PropInit::Set5(p, 162, (s32)func_001849D0, 824, 1, 824); p++;
    PropInit::Set5(p, 162, (s32)func_00184A08, 828, 1, 828); p++;
    PropInit::Set5(p, 162, (s32)func_00184A38, 832, 2, 832); p++;
    PropInit::Set5(p, 292, (s32)func_00184CD0, (s32)func_00184D10, 1, (s32)func_00184CD0); p++;
    PropInit::Set5(p, 292, (s32)func_00184D20, (s32)func_00184D58, 2, (s32)func_00184D20); p++;
    PropInit::Set7(p, 0, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set7(p, 1, 0); p++;
    PropInit::Set2(p, 0, 128, 68); p++;
    PropInit::Set1(p, (s32)func_001030E0, 0, 8339, 1, 3); p++;
    PropInit::Set0(p, 2, 8194, 28); p++;
    PropInit::Set4(p, 36, 6, (s32)func_001B6568, (s32)func_001B64D8); p++;
    PropInit::Set0(p, 4, 6, (s32)func_001B6598); p++;
    PropInit::Set0(p, 4, 6, (s32)func_001B65C8); p++;
    PropInit::Set4(p, 34, 1, 56, (s32)func_001B65F8); p++;
    PropInit::Set0(p, 2, 8338, 36); p++;
    PropInit::Set9(p, 32, 6, (s32)func_001B6628); p++;
    PropInit::Set1(p, (s32)func_001031C0, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 2, 8328, 24); p++;
    PropInit::Set12(p, 2176, 7544, 1, 0); p++;
    PropInit::Set15(p, 7548, 1.0f, 1, 2176); p++;
    PropInit::Set5(p, 162, (s32)func_001DD5F8, 7532, 1, 7532); p++;
    PropInit::Set5(p, 162, (s32)func_001DD610, 7528, 1, 7528); p++;
    PropInit::Set2(p, 13, 128, 7524); p++;
    PropInit::Set2(p, 1, 256, (s32)func_001437C0); p++;
    PropInit::Set2(p, 1, 256, (s32)func_001437E8); p++;
    PropInit::Set2(p, 1, 256, (s32)func_00143810); p++;
    PropInit::Set2(p, 1, 256, (s32)func_00143838); p++;
    PropInit::Set2(p, 1, 256, (s32)func_00143860); p++;
    PropInit::Set2(p, 1, 256, (s32)func_00143888); p++;
    PropInit::Set2(p, 13, 256, (s32)func_001438B0); p++;
    PropInit::Set2(p, 1, 256, (s32)func_001438D8); p++;
    PropInit::Set10(p, 1, 2194, 8968, 8968, 8968, 15.0f); p++;
    PropInit::Set10(p, 1, 2194, 8972, 8972, 8972, 180.0f); p++;
    PropInit::Set4(p, 34, 1, 8984, (s32)func_001DD628); p++;
    PropInit::Set4(p, 34, 1, 9036, (s32)func_001DDAB8); p++;
    PropInit::Set4(p, 34, 1, 9040, (s32)func_001DDAC8); p++;
    PropInit::Set14(p, 4242, 5, 4, 4, 4, (s32)func_00151A58); p++;
    PropInit::Set14(p, 4242, 5, 8, 8, 8, (s32)func_00151A58); p++;
    PropInit::Set14(p, 4242, 5, 12, 12, 12, (s32)func_00151A58); p++;
    PropInit::Set14(p, 4242, 5, 16, 16, 16, (s32)func_00151A58); p++;
    PropInit::Set1(p, (s32)func_00103260, 0, 18, 1, 3); p++;
    PropInit::Set4(p, 36, 1, (s32)func_001DD9C0, (s32)func_001DD9A0); p++;
    PropInit::Set4(p, 36, 1, (s32)func_001DDA08, (s32)func_001DD9D8); p++;
    PropInit::Set6(p, (s32)func_001C0A50, 14, 288, (s32)func_001C0A50); p++;
    PropInit::Set6(p, (s32)func_001C0AB8, 10, 288, (s32)func_001C0AB8); p++;
    PropInit::Set6(p, (s32)func_001C0B08, 10, 288, (s32)func_001C0B08); p++;
    PropInit::Set1(p, 0, (s32)func_00103350, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)func_00103420, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_001034F0, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00103590, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103640, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001036F0, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001037A0, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103850, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103900, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001039B0, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103A60, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)func_00103B40, 0, 5, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00103C10, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103CC0, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00103D70, 0, 5, 1, 0); p++;
    PropInit::Set0(p, 4, 0, (s32)func_001DDA90); p++;
    PropInit::Set1(p, (s32)func_00103E10, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00103EB0, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00103F80, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104020, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 9044, 9044, 0, 9044); p++;
    PropInit::Set1(p, (s32)func_001040C0, 0, 5, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00104170, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00104220, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_001042F0, 0, 5, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001043A0, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00104470, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104510, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_001045B0, (s32)func_001045B0, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00104660, (s32)func_00104660, 18, 1025, 1); p++;
    PropInit::Set0(p, 4, 5, (s32)func_001DDCB0); p++;
    PropInit::Set0(p, 4, 5, (s32)func_001DDCC8); p++;
    PropInit::Set4(p, 34, 2, 64, (s32)func_00143900); p++;
    PropInit::Set4(p, 34, 4, 128, (s32)func_00143920); p++;
    PropInit::Set4(p, 34, 1, 452, (s32)func_00143940); p++;
    PropInit::Set4(p, 18, 1, 456, 456); p++;
    PropInit::Set4(p, 18, 12, 464, 464); p++;
    PropInit::Set4(p, 34, 1, 484, (s32)func_00143968); p++;
    PropInit::Set4(p, 34, 1, 488, (s32)func_00143988); p++;
    PropInit::Set4(p, 34, 1, 504, (s32)func_001439A8); p++;
    PropInit::Set4(p, 34, 1, 508, (s32)func_001439C8); p++;
    PropInit::Set4(p, 34, 1, 512, (s32)func_001439E8); p++;
    PropInit::Set4(p, 34, 1, 448, (s32)func_00143A38); p++;
    PropInit::Set1(p, (s32)func_00104710, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001047C0, 0, 4177, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104860, 0, 4177, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104900, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)func_001049D8, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104A78, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104B18, 0, 0, 1, 3); p++;
    PropInit::Set2(p, 6, 128, 720); p++;
    PropInit::Set2(p, 2, 128, 736); p++;
    PropInit::Set2(p, 2, 128, 752); p++;
    PropInit::Set2(p, 2, 128, 768); p++;
    PropInit::Set1(p, (s32)func_00104C00, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00104CA0, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 720, 720, 0, 720); p++;
    PropInit::Set5(p, 146, 1364, 1364, 4124, 1364); p++;
    PropInit::Set3(p, 6, 4352, (s32)func_001F5840, (s32)func_001F5208); p++;
    PropInit::Set13(p, (s32)func_001F5868, 4128, 8193, (s32)func_001F5208); p++;
    PropInit::Set13(p, (s32)func_001F5930, 4128, 8193, (s32)func_001F5208); p++;
    PropInit::Set1(p, (s32)func_00104D40, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1368, 1368, 1, 1368); p++;
    PropInit::Set5(p, 146, 1372, 1372, 0, 1372); p++;
    PropInit::Set5(p, 146, 136, 136, 4127, 136); p++;
    PropInit::Set5(p, 146, 140, 140, 1, 140); p++;
    PropInit::Set5(p, 146, 144, 144, 0, 144); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001419A0); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001419C0); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001419E0); p++;
    PropInit::Set1(p, (s32)func_00104DE0, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1448, 1448, 1, 1448); p++;
    PropInit::Set0(p, 4, 0, (s32)func_00199C10); p++;
    PropInit::Set5(p, 290, (s32)func_00146240, 1360, 1, (s32)func_00146240); p++;
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
    PropInit::Set5(p, 162, (s32)func_001CA998, 2340, 6, 2340); p++;
    PropInit::Set5(p, 146, 1848, 1848, 10, 1848); p++;
    PropInit::Set5(p, 146, 1856, 1856, 10, 1856); p++;
    PropInit::Set5(p, 274, 1868, 1868, 1, (s32)func_001CAD28); p++;
    PropInit::Set1(p, 0, (s32)func_00104E80, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)func_00104F50, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00105020, 0, 8323, 1, 1); p++;
    PropInit::Set5(p, 146, 2672, 2672, 1, 2672); p++;
    PropInit::Set1(p, 0, (s32)func_001050D0, 18, 1024, 4); p++;
    PropInit::Set1(p, 0, (s32)func_001051C0, 18, 1024, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00105290, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)func_00105360, 0, 18, 1, 2); p++;
    PropInit::Set1(p, 0, (s32)func_00105430, 18, 1024, 2); p++;
    PropInit::Set5(p, 146, 2664, 2664, 5, 2664); p++;
    PropInit::Set5(p, 146, 2668, 2668, 0, 2668); p++;
    PropInit::Set1(p, (s32)func_00105500, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 2972, 2972, 10, 2972); p++;
    PropInit::Set5(p, 146, 2944, 2944, 0, 2944); p++;
    PropInit::Set5(p, 146, 2892, 2892, 6, 2892); p++;
    PropInit::Set4(p, 36, 8195, (s32)func_001CAAD0, (s32)func_001CAB00); p++;
    PropInit::Set5(p, 146, 2884, 2884, 0, 2884); p++;
    PropInit::Set5(p, 146, 2844, 2844, 0, 2844); p++;
    PropInit::Set5(p, 146, 2848, 2848, 1, 2848); p++;
    PropInit::Set5(p, 146, 2864, 2864, 9, 2864); p++;
    PropInit::Set5(p, 146, 2336, 2336, 4174, 2336); p++;
    PropInit::Set1(p, (s32)func_001055A8, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 2904, 2904, 5, 2904); p++;
    PropInit::Set5(p, 146, 2912, 2912, 2, 2912); p++;
    PropInit::Set5(p, 146, 2928, 2928, 0, 2928); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001CA878); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001CA888); p++;
    PropInit::Set2(p, 1, 128, 2840); p++;
    PropInit::Set5(p, 146, 3024, 3024, 1, 3024); p++;
    PropInit::Set5(p, 146, 3028, 3028, 0, 3028); p++;
    PropInit::Set0(p, 2, 4133, 1828); p++;
    PropInit::Set5(p, 146, 2752, 2752, 0, 2752); p++;
    PropInit::Set0(p, 4, 0, (s32)func_001C8D40); p++;
    PropInit::Set5(p, 146, 3040, 3040, 10, 3040); p++;
    PropInit::Set5(p, 146, 3036, 3036, 0, 3036); p++;
    PropInit::Set5(p, 146, 3048, 3048, 1, 3048); p++;
    PropInit::Set5(p, 146, 3032, 3032, 0, 3032); p++;
    PropInit::Set5(p, 146, 3080, 3080, 0, 3080); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001CB6A8); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001CB6D0); p++;
    PropInit::Set5(p, 146, 3096, 3096, 1, 3096); p++;
    PropInit::Set5(p, 146, 3100, 3100, 1, 3100); p++;
    PropInit::Set5(p, 146, 3104, 3104, 1, 3104); p++;
    PropInit::Set5(p, 146, 3108, 3108, 1, 3108); p++;
    PropInit::Set5(p, 146, 3112, 3112, 6, 3112); p++;
    PropInit::Set2(p, 6, 128, 3088); p++;
    PropInit::Set0(p, 2, 8288, 3092); p++;
    PropInit::Set1(p, 0, (s32)func_00105658, 18, 1024, 2); p++;
    PropInit::Set5(p, 146, 3272, 3272, 0, 3272); p++;
    PropInit::Set5(p, 146, 3276, 3276, 0, 3276); p++;
    PropInit::Set5(p, 146, 3280, 3280, 4197, 3280); p++;
    PropInit::Set5(p, 146, 3052, 3052, 6, 3052); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001B7100); p++;
    PropInit::Set15(p, 1740, 35.0f, 1, 2176); p++;
    PropInit::Set6(p, (s32)func_001C5E50, 1, 288, (s32)func_001C5E50); p++;
    PropInit::Set5(p, 290, (s32)func_001C5EA8, 1792, 1, (s32)func_001C5EA8); p++;
    PropInit::Set5(p, 146, 1372, 1372, 1, 1372); p++;
    PropInit::Set5(p, 146, 1376, 1376, 1, 1376); p++;
    PropInit::Set5(p, 146, 1360, 1360, 4135, 1360); p++;
    PropInit::Set5(p, 146, 1544, 1544, 4136, 1544); p++;
    PropInit::Set5(p, 146, 1380, 1380, 0, 1380); p++;
    PropInit::Set5(p, 146, 1384, 1384, 1, 1384); p++;
    PropInit::Set5(p, 146, 1396, 1396, 1, 1396); p++;
    PropInit::Set5(p, 146, 1388, 1388, 10, 1388); p++;
    PropInit::Set5(p, 146, 1472, 1472, 1, 1472); p++;
    PropInit::Set1(p, (s32)func_00105728, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001057D8, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1652, 1652, 0, 1652); p++;
    PropInit::Set5(p, 146, 1656, 1656, 0, 1656); p++;
    PropInit::Set5(p, 146, 1660, 1660, 4124, 1660); p++;
    PropInit::Set14(p, 4242, 14, 0, 0, 0, (s32)func_0013C950); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)func_0013C950); p++;
    PropInit::Set14(p, 4242, 1, 8, 8, 8, (s32)func_0013C950); p++;
    PropInit::Set14(p, 4242, 1, 12, 12, 12, (s32)func_0013C950); p++;
    PropInit::Set5(p, 146, 1368, 1368, 1, 1368); p++;
    PropInit::Set8m(p, 0, 1668, 130); p++;
    PropInit::Set1(p, (s32)func_00105878, 0, 18, 1, 3); p++;
    PropInit::Set1(p, (s32)func_00105960, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00105A00, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 8640, 8640, 0, 8640); p++;
    PropInit::Set4(p, 34, 4178, 10008, (s32)func_001D27C0); p++;
    PropInit::Set1(p, (s32)func_00105AB0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00105B60, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00105C10, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00105CC0, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 11220, 11220, 0, 11220); p++;
    PropInit::Set5(p, 162, (s32)func_00177828, 11224, 0, 11224); p++;
    PropInit::Set1(p, (s32)func_00105D60, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00105E10, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00105EC0, 0, 18, 1, 1); p++;
    PropInit::Set2(p, 4144, 128, 68); p++;
    PropInit::Set2(p, 6, 128, 52); p++;
    PropInit::Set2(p, 6, 128, 56); p++;
    PropInit::Set2(p, 4127, 128, 76); p++;
    PropInit::Set1(p, 0, (s32)func_00105F70, 18, 1024, 3); p++;
    PropInit::Set1(p, 0, (s32)func_00106048, 18, 1024, 3); p++;
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
    PropInit::Set2(p, 6, 256, (s32)func_001A4858); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001A4860); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001A4868); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001A4870); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001A4878); p++;
    PropInit::Set14(p, 4242, 1, 0, 0, 0, (s32)func_001A6480); p++;
    PropInit::Set16(p, 1, 4, 4, (s32)func_001A6480, 4226); p++;
    PropInit::Set14(p, 4242, 9, 16, 16, 16, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 1, 32, 32, 32, (s32)func_001A6480); p++;
    PropInit::Set16(p, 1, 36, 36, (s32)func_001A6480, 4226); p++;
    PropInit::Set14(p, 4242, 9, 48, 48, 48, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 10, 64, 64, 64, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 10, 72, 72, 72, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 9, 80, 80, 80, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 10, 96, 96, 96, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 10, 104, 104, 104, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 9, 112, 112, 112, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 1, 128, 128, 128, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 1, 132, 132, 132, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 9, 144, 144, 144, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 1, 160, 160, 160, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 1, 164, 164, 164, (s32)func_001A6480); p++;
    PropInit::Set14(p, 4242, 9, 176, 176, 176, (s32)func_001A6480); p++;
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
    PropInit::Set4(p, 34, 4145, 1360, (s32)func_0014F110); p++;
    PropInit::Set10(p, 1, 2194, 1368, 1368, 1368, 2500.0f); p++;
    PropInit::Set10(p, 1, 2194, 1372, 1372, 1372, 20.0f); p++;
    PropInit::Set10(p, 1, 2194, 1376, 1376, 1376, 30.0f); p++;
    PropInit::Set10(p, 1, 2194, 1380, 1380, 1380, 1.5f); p++;
    PropInit::Set10(p, 1, 2194, 1384, 1384, 1384, 10.0f); p++;
    PropInit::Set2(p, 6, 128, 1728); p++;
    PropInit::Set12(p, 2176, 1732, 5, 5); p++;
    PropInit::Set10(p, 1, 2194, 1744, 1744, 1744, 1.0f); p++;
    PropInit::Set10(p, 1, 2194, 1748, 1748, 1748, 20.0f); p++;
    PropInit::Set2(p, 6, 256, (s32)func_001503E0); p++;
    PropInit::Set1(p, (s32)func_00106120, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_001061C0, 0, 18, 1, 1); p++;
    PropInit::Set10(p, 1, 2194, 1680, 1680, 1680, 800.0f); p++;
    PropInit::Set4(p, 18, 8194, 1684, 1684); p++;
    PropInit::Set4(p, 18, 2, 1696, 1696); p++;
    PropInit::Set5(p, 146, 1720, 1720, 0, 1720); p++;
    PropInit::Set1(p, 0, (s32)func_00106270, 18, 1024, 1); p++;
    PropInit::Set1(p, 0, (s32)func_00106320, 18, 1024, 1); p++;
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
    PropInit::Set1(p, 0, (s32)func_001063D0, 18, 1024, 4); p++;
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
    PropInit::Set5(p, 290, (s32)func_001E29E8, 864, 1, (s32)func_001E29E8); p++;
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
    PropInit::Set5(p, 162, (s32)func_001E2840, 920, 4109, 920); p++;
    PropInit::Set5(p, 146, 880, 880, 1, 880); p++;
    PropInit::Set5(p, 146, 884, 884, 1, 884); p++;
    PropInit::Set6(p, (s32)func_0016D040, 6, 160, 1400); p++;
    PropInit::Set1(p, (s32)func_001064C0, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00106560, 0, 18, 1, 0); p++;
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
    PropInit::Set1(p, 0, (s32)func_00106600, 18, 1024, 4); p++;
    PropInit::Set16(p, 0, 4, 4, (s32)func_001A8110, 4226); p++;
    PropInit::Set5(p, 146, 64, 64, 4158, 64); p++;
    PropInit::Set4(p, 18, 5, 68, 68); p++;
    PropInit::Set1(p, (s32)func_001066F0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001067A0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00106850, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00106920, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_001069C0, 0, 0, 1, 1); p++;
    PropInit::Set0(p, 2, 8195, 72); p++;
    PropInit::Set1(p, (s32)func_00106A70, 0, 18, 1, 0); p++;
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
    PropInit::Set1(p, (s32)func_00106B10, 0, 18, 1, 0); p++;
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
    PropInit::Set1(p, (s32)func_00106BB0, 0, 18, 1, 0); p++;
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
    PropInit::Set4(p, 34, 4156, 1364, (s32)func_0015B7B8); p++;
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
    PropInit::Set4(p, 34, 4167, 724, (s32)func_00150790); p++;
    PropInit::Set2(p, 6, 128, 768); p++;
    PropInit::Set5(p, 146, 804, 804, 0, 804); p++;
    PropInit::Set5(p, 146, 808, 808, 0, 808); p++;
    PropInit::Set5(p, 146, 812, 812, 0, 812); p++;
    PropInit::Set1(p, 0, (s32)func_00106C50, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)func_00106CF0, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)func_00106D90, 18, 1024, 2); p++;
    PropInit::Set1(p, (s32)func_00106E60, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00106F00, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 780, 780, 6, 780); p++;
    PropInit::Set4(p, 36, 0, (s32)func_00150770, (s32)func_00150780); p++;
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
    PropInit::Set6(p, (s32)func_001C1030, 6, 160, 812); p++;
    PropInit::Set5(p, 146, 784, 784, 2, 784); p++;
    PropInit::Set5(p, 146, 808, 808, 1, 808); p++;
    PropInit::Set2(p, 6, 256, (s32)func_00199398); p++;
    PropInit::Set1(p, (s32)func_00106FA0, 0, 18, 1, 0); p++;
    PropInit::Set2(p, 5, 256, (s32)func_00199380); p++;
    PropInit::Set1(p, 0, (s32)func_00107040, 18, 1024, 0); p++;
    PropInit::Set1(p, 0, (s32)func_001070E0, 18, 1024, 0); p++;
    PropInit::Set14(p, 4242, 2, 16, 16, 16, (s32)func_001F3810); p++;
    PropInit::Set5(p, 292, (s32)func_001F3850, (s32)func_001F38A0, 1, (s32)func_001F3850); p++;
    PropInit::Set14(p, 4242, 1, 104, 104, 104, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 1, 108, 108, 108, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 2, 64, 64, 64, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 10, 48, 48, 48, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 10, 80, 80, 80, (s32)func_001F3810); p++;
    PropInit::Set14(p, 4242, 2, 16, 16, 16, (s32)func_001F3830); p++;
    PropInit::Set14(p, 4242, 10, 48, 48, 48, (s32)func_001F3830); p++;
    PropInit::Set14(p, 4242, 1, 56, 56, 56, (s32)func_001F3830); p++;
    PropInit::Set1(p, 0, (s32)func_00107180, 18, 1024, 4); p++;
    PropInit::Set14(p, 4242, 2, 32, 32, 32, (s32)func_001F3830); p++;
    PropInit::Set14(p, 4242, 10, 128, 128, 128, (s32)func_001F3830); p++;
    PropInit::Set14(p, 4242, 1, 136, 136, 136, (s32)func_001F3830); p++;
    PropInit::Set1(p, 0, (s32)func_00107268, 18, 1024, 4); p++;
    PropInit::Set0(p, 2, 5, 56); p++;
    PropInit::Set4(p, 18, 5, 1744, 1744); p++;
    PropInit::Set5(p, 146, 3088, 3088, 0, 3088); p++;
    PropInit::Set0(p, 2, 8339, 3600); p++;
    PropInit::Set5(p, 146, 3604, 3604, 8307, 3604); p++;
    PropInit::Set1(p, (s32)func_00107350, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 4, 1, (s32)func_0018B460); p++;
    PropInit::Set4(p, 34, 4175, 1824, (s32)func_001DFBE0); p++;
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
    PropInit::Set2(p, 6, 256, (s32)func_001E53F8); p++;
    PropInit::Set5(p, 146, 1616, 1616, 10, 1616); p++;
    PropInit::Set5(p, 146, 1624, 1624, 10, 1624); p++;
    PropInit::Set5(p, 146, 1600, 1600, 5, 1600); p++;
    PropInit::Set1(p, 0, (s32)func_001073F0, 18, 1024, 2); p++;
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
    PropInit::Set2(p, 6, 256, (s32)func_0014C838); p++;
    PropInit::Set14(p, 4242, 1, 0, 0, 0, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 4, 4, 4, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 9, 16, 16, 16, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 64, 64, 64, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 32, 32, 32, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 40, 40, 40, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 9, 48, 48, 48, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 68, 68, 68, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 76, 76, 76, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 9, 96, 96, 96, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 112, 112, 112, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 116, 116, 116, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 9, 128, 128, 128, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 144, 144, 144, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 1, 148, 148, 148, (s32)func_0014C820); p++;
    PropInit::Set14(p, 4242, 9, 160, 160, 160, (s32)func_0014C820); p++;
    PropInit::Set5(p, 146, 1680, 1680, 5, 1680); p++;
    PropInit::Set5(p, 146, 1136, 1136, 9, 1136); p++;
    PropInit::Set0(p, 2, 8339, 1068); p++;
    PropInit::Set5(p, 146, 3108, 3108, 5, 3108); p++;
    PropInit::Set5(p, 146, 1552, 1552, 1, 1552); p++;
    PropInit::Set5(p, 146, 1556, 1556, 1, 1556); p++;
    PropInit::Set5(p, 146, 1560, 1560, 1, 1560); p++;
    PropInit::Set5(p, 146, 1564, 1564, 1, 1564); p++;
    PropInit::Set4(p, 34, 8302, 2096, (s32)func_001DAFB8); p++;
    PropInit::Set4(p, 34, 8302, 2120, (s32)func_001DB0C8); p++;
    PropInit::Set5(p, 146, 2820, 2820, 5, 2820); p++;
    PropInit::Set1(p, (s32)func_001074C0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00107570, 0, 18, 1, 5); p++;
    PropInit::Set4(p, 18, 8330, 2876, 2876); p++;
    PropInit::Set5(p, 290, (s32)func_001DB238, 2868, 4183, (s32)func_001DB238); p++;
    PropInit::Set1(p, (s32)func_00107678, 0, 18, 1, 0); p++;
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
    PropInit::Set1(p, (s32)func_00107718, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_001077D8, 0, 0, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00107898, 0, 0, 1, 1); p++;
    PropInit::Set4(p, 34, 8307, 3112, (s32)func_001906E8); p++;
    PropInit::Set4(p, 34, 8307, 3108, (s32)func_001906F0); p++;
    PropInit::Set0(p, 4, 2, (s32)func_00191C78); p++;
    PropInit::Set5(p, 146, 1740, 1740, 1, 1740); p++;
    PropInit::Set5(p, 146, 1744, 1744, 1, 1744); p++;
    PropInit::Set5(p, 146, 1748, 1748, 1, 1748); p++;
    PropInit::Set5(p, 146, 1752, 1752, 1, 1752); p++;
    PropInit::Set1(p, (s32)func_00107948, 0, 18, 1, 2); p++;
    PropInit::Set4(p, 34, 4176, 2992, (s32)func_00181DA8); p++;
    PropInit::Set1(p, (s32)func_00107A10, (s32)func_00107A10, 18, 1025, 0); p++;
    PropInit::Set1(p, (s32)func_00107AB0, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00107B60, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00107C00, (s32)func_00107C00, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00107CB0, (s32)func_00107CB0, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00107D60, (s32)func_00107D60, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00107E10, (s32)func_00107E10, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00107EC0, (s32)func_00107EC0, 18, 1025, 1); p++;
    PropInit::Set1(p, (s32)func_00107F70, (s32)func_00107F70, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)func_00108038, (s32)func_00108038, 18, 1025, 4); p++;
    PropInit::Set1(p, (s32)func_00108128, (s32)func_00108128, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)func_00108208, (s32)func_00108208, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)func_001082E8, (s32)func_001082E8, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)func_001083C8, (s32)func_001083C8, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)func_00108498, (s32)func_00108498, 18, 1025, 1); p++;
    PropInit::Set5(p, 146, 104, 104, 0, 104); p++;
    PropInit::Set1(p, (s32)func_00108548, (s32)func_00108548, 18, 1025, 0); p++;
    PropInit::Set1(p, (s32)func_001085E8, (s32)func_001085E8, 18, 1025, 0); p++;
    PropInit::Set5(p, 146, 60, 60, 13, 60); p++;
    PropInit::Set5(p, 146, 64, 64, 13, 64); p++;
    PropInit::Set5(p, 146, 68, 68, 13, 68); p++;
    PropInit::Set5(p, 146, 72, 72, 1, 72); p++;
    PropInit::Set5(p, 146, 80, 80, 1, 80); p++;
    PropInit::Set5(p, 146, 76, 76, 1, 76); p++;
    PropInit::Set5(p, 146, 88, 88, 4188, 88); p++;
    PropInit::Set4(p, 18, 8195, 1544, 1544); p++;
    PropInit::Set4(p, 34, 4190, 1360, (s32)func_0017B410); p++;
    PropInit::Set9(p, 32, 0, (s32)func_0017B510); p++;
    PropInit::Set1(p, (s32)func_00108688, 0, 18, 1, 0); p++;
    PropInit::Set1(p, (s32)func_00108728, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 1788, 1788, 1, 1788); p++;
    PropInit::Set5(p, 146, 1792, 1792, 1, 1792); p++;
    PropInit::Set1(p, (s32)func_001087D8, 0, 18, 1, 0); p++;
    PropInit::Set5(p, 146, 1368, 1368, 5, 1368); p++;
    PropInit::Set5(p, 162, (s32)func_0017B8C0, 1360, 4191, 1360); p++;
    PropInit::Set5(p, 290, (s32)func_001ED050, 3164, 5, (s32)func_001ED050); p++;
    PropInit::Set5(p, 290, (s32)func_001ED070, 3168, 5, (s32)func_001ED070); p++;
    PropInit::Set1(p, (s32)func_00108878, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00108928, 0, 18, 1, 0); p++;
    PropInit::Set0(p, 2, 8339, 3156); p++;
    PropInit::Set4(p, 18, 8307, 3144, 3144); p++;
    PropInit::Set1(p, (s32)func_001089C8, 0, 18, 1, 2); p++;
    PropInit::Set1(p, (s32)func_00108A98, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00108B48, 0, 18, 1, 0); p++;
    PropInit::Set4(p, 18, 8307, 1660, 1660); p++;
    PropInit::Set4(p, 18, 8335, 1576, 1576); p++;
    PropInit::Set1(p, (s32)func_00108BE8, (s32)func_00108BE8, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)func_00108CC8, (s32)func_00108CC8, 18, 1025, 3); p++;
    PropInit::Set1(p, (s32)func_00108DA8, (s32)func_00108DA8, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)func_00108E70, (s32)func_00108E70, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)func_00108F38, (s32)func_00108F38, 18, 1025, 2); p++;
    PropInit::Set1(p, (s32)func_00109000, (s32)func_00109000, 18, 1025, 2); p++;
    PropInit::Set4(p, 18, 5, 3088, 3088); p++;
    PropInit::Set1(p, (s32)func_001090C8, 0, 18, 1, 3); p++;
    PropInit::Set4(p, 18, 0, 3108, 3108); p++;
    PropInit::Set4(p, 34, 4199, 1552, (s32)func_001C3FC8); p++;
    PropInit::Set1(p, (s32)func_001091A8, 0, 18, 1, 1); p++;
    PropInit::Set5(p, 146, 1680, 1680, 5, 1680); p++;
    PropInit::Set5(p, 146, 1684, 1684, 5, 1684); p++;
    PropInit::Set1(p, (s32)func_00109258, 0, 18, 1, 1); p++;
    PropInit::Set1(p, (s32)func_00109308, 0, 18, 1, 1); p++;
    PropInit::Set4(p, 18, 5, 1360, 1360); p++;
    PropInit::Set4(p, 18, 8311, 1368, 1368); p++;
    PropInit::Set1(p, (s32)func_001093B8, 0, 18, 1, 2);
}

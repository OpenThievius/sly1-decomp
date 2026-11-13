// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 219/260 (84.2%), checked 2026-11-13
// w44-fa (2026-11-12), 1 compile (the dumps): the per-arm stores alone do not hold the addiu either. Replayed by hand on ours' sched2 trace with insn 126 (the store through p) out of the join block: d's reload (224) is then ready at t=1, the two issues of each cycle go to 199 and 189, then 165 and 190, and at t=3 to 301 and the addiu (253), which is still two cycles before any weight is loaded. With or without 126 it lands after `sqc2 vf3,32(sp)` only if it becomes ready between t=5 and t=8, as w8 found (after 171, 205, 228, 251, 233, 298 or 301); cycles 6 to 8 are full (two issues each), so any of those puts it in cycle 9 behind 181. No source form found for such a dependence; nothing new tried in C.
// w25 (2026-11-11, w25-deps): the pending-list flush at a block's 33rd memory reference (docs/toolchain/sched1.md, "The 33rd memory reference of a block is a barrier") is not reached in this function (most pending: 10), so it is not the missing dependence.
// Wave 23 (w23-vuD, 2026-11-11): the sched2 trace (-dR -fsched-verbose-6) of the join block shows the addiu (insn 253, priority 5, no dependences) issued at t=3 beside addiu v0 because lw v1 is queued two cycles behind its lui. Retail cannot have it merely low in priority: from t=4 to t=9 the ready insns are mostly memory insns (one per cycle), so a free ALU slot would take it each cycle; it must depend on the MulXSum asm or the first weight's slot store (it issues right after sqc2 vf3,32(sp) at the cycle after the asm). An asm volatile MulXSum (a probe only) makes that dependence but also changes sched1 (registers and order): not the mechanism. The per-arm store hypothesis (cross-jumping after sched2) stands; arm A's qmtc2 v0,vf1 then needs the stored pseudo to be the VU-class result shared with DivX and canonical in CSE (make_regs_eqv: it lives past the CSE path), which no plain form tried gives.
// Re-scored 2026-11-10 (w15-14F168), about 15 compiles: only `addiu a1,sp,16` is out of place (ours beside addiu v0, retail between sqc2 vf3 and sqc2 vf1). Per-arm stores merged by jump2's cross-jumping are consistent with retail's head (probe: both arms' sqc2 vf1,0(v1) merge, reorg fills arm A's slot), but CSE makes `p = &d` the frame pointer in both arms (make_regs_eqv prefers the fixed register; arm A is in the test's extended block), so a plain per-arm form stores through sp, and arm A stores the fallback's GPR (sq v0); with the store kept out of the join by a probe, the first weight's %hi takes a0 and the addiu comes one slot late. p reassigned to &r for the store and the call (p then lives in a1 from the top), an NRV inline returning Vec02 (memcpy / a temporary), do { } while (0) around the normalize (loop-note barrier breaks the head), statement permutations: no closer. docs/toolchain/sched1.md, "Why the arms' stores cannot be written plainly".
// Still differs (2026-11-09, scalar-slot): with Scalar's slot a cast's copy (MEM_SCALAR_P; docs/TOOLCHAIN.md "The weight slot is a cast's copy") the method-table load (lw v1,0(s0)) and the weights are retail's, the delay slot holds the last weight store and the size is retail's 260; left: the address of r for the call (addiu a1,sp,16) issues first, where retail has it after the weight's store. Tried r written through *(u128*)&r and Vu0::Set, and the descriptor read after the sum or inside the call: unchanged.
// Mechanism research (2026-11-09, w8-14F168), 14 compiles: replaying sched2 puts the addiu where retail has it only if it is ready from cycle 5 to 9 (a dependence on the weights' loads or qmtc2s, unit Z's load, move a0,s0 or the MulXSum asm) or grouped with r's store; no plain form gives `$5 = sp+16` such a dependence (no insn in the block names a1 or sets sp, the address pseudo is merged by combine or deleted by reload). Pointers to r, p reused, an address-returning inline, an inline call wrapper, a local function pointer, a Vec copy, ScalarAtValue: all unchanged. docs/TOOLCHAIN.md, "An argument's frame address that sched2 holds back".
// Tried night-close8 after FromFloatAt's "rV" (2026-11-08), 8 compiles: the weights now load into the registers of their lui as retail's (lw v1,7380(v1), lw a0,7384(a0)), but the scheduling around them moved: 11 differing words became 29; the descriptor read into a local before the sum gives 26 (here). Set for the sum, Vec values, the descriptor read first in the function: no closer.
// NEAR: scheduling only: retail puts the vtable load (lw v1,0(s0)) right after move a0,s0, the addiu a1,sp,16 after the weight's sqc2 and the last weight store in the jalr's delay slot; here addiu a1 comes first, the vtable load after the sum's store and the jalr's slot is a nop (the C is 264 bytes, retail's 260).
// Before: NEAR: identical but for three details: the vtable load (lw v1,0(s0)) sits before the vmulax in retail and after the vmaddx here; the two weights load into v1 and a0 (the registers of their lui) where ours uses a1 and v1; retail issues the last weight store (sqc2 vf4) in the delay slot of the jalr. WeightAt is FromFloatAt in a 16-byte local, the lw-form of Vu0::Scalar, which include/vu0.h lacks. Tried loading the method or the descriptor first, naming the weights, and a pointer to r.
// w37-f2 (2026-11-12), no compile beyond the dumps: haifa-sched.c keeps same-block LOG_LINKS from sched1 into sched2 (it drops only links into other blocks), so a stale link could hold the addiu; replayed by hand on the sched2 trace, a link to a weight's qmtc2, unit Z's load, move a0,s0 or the MulXSum asm puts it after sqc2 vf3,32(sp), a link to the table load, d's reload or the slot store does not. But sched1 links `a1 = sp+16` only to insns naming hard register 5 or setting its address pseudo, and none of those five can; a loop-note barrier puts a slot store, r's store or move a0,s0 on the wrong side wherever it stands. So no dependence explains it: what sched2's block holds does (the per-arm stores). docs/toolchain/sched1.md, "Why the arms' stores cannot be written plainly", last item.
#include "common.h"
#include "placed_object.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_00261CD4;
extern f32 D_00261CD8;
s32 IsObjectOfKind(void* a, s32 b);
void SetPlayerState(PlacedObject* self, s32 a, s32 b);

// A float read from memory as a weight: stored in a slot of its own that the next weight shares.
static inline u128 WeightAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

void LaunchObjectFromPooledObject(PlacedObject* self, PlacedObject* other)
{
    Vec02 d = self->v150;
    d.z = 0.0f;
    Vec02* p = &d;
    Vec02 r;
    Vu0::Q(*p) = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector));
    const Desc02* desc = other->desc02();
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAt(D_00261CD4), Vu0::Q(g_unitZVector), Vu0::ScalarAt(D_00261CD8));
    desc->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

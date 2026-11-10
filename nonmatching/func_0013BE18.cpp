// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 282/332 (84.9%), checked 2026-11-10
// Re-scored 2026-11-10 (w15-14F168): unchanged. A reused u128 n (first set to the Sub result in the first else arm, then `n = x; *p = n;` / `n = DivX(..); *p = n;` in the normalize's arms) still stores the fallback's GPR in arm A (sq v0,0(sp)): CSE's path from block 0 follows the first if's arms, so n is not canonical; p set in the same block is replaced by the frame pointer. docs/toolchain/sched1.md, "Why the arms' stores cannot be written plainly".
// Still differs (2026-11-09, w10-13BE18): with Vu0::ScalarAt for the weights (the slot a cast's copy) every register is retail's (the weights in v1 and a0, the registers of their lui); left is sched2's order in the join block after NormalizeOr: ours issues addiu s0,sp,16 (&r) and the argument moves early, retail after the reload of d. Mechanism: NormalizeOr's store of *p (sqc2 vf1,0(v1)) heads that block in ours; with it in the block the memory unit is busy and free issue slots go to &r and the moves. Probes storing *p in each arm (e1, e4: the store leaves the join block) give retail's order of the tail (lqc2 vf1, addiu s0, vmulax, vmaddx, sqc2 vf3, move a3, sqc2 vf1 ...), so retail stored in each arm and jump2's cross-jumping, which runs after sched2 (toplev.c), merged the two identical stores into the join. Not found: the C that makes both arms store vf1 through p (arm A: qmtc2 v0,vf1 then sqc2 vf1,0(v1)); written plainly, CSE gives arm A sq v0,0(sp) and the arms do not merge (CSE folds the arm's copy `n = x` back to x, make_regs_eqv keeping x canonical; p declared before the first if keeps p a register in both arms but crosses the call into s2). Probe e5 (Vec values, *p stored in each arm): the tail is retail's but for the weights' lw order; the head differs (sq v0 in arm A). docs/TOOLCHAIN.md, "A store in each arm leaves the join block to sched2".
// Wave 4 (night-lever1, 4 compiles): D_00261364 defined in C (f32 [3] = {800, 0, 0}), Vu0::Set for r, the weights as named locals: unchanged or worse (the weights stay in a1/v1; the call-argument moves are scheduled ahead of the weights).
// NEAR: the same call tree as func_0014F168 and the same remainder: the two weights load into a1 and v1 (retail v1 and a0, the registers of their lui), the moves of the call arguments are scheduled before the vector work here and after it (and the last weight store) in retail. D_00261364 is INCLUDE_DATA in src (f32 D_00261364[3] = { 800, 0, 0 }); 
#include "common.h"
#include "child_group_object.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_00261360;
extern f32 D_00261364[];
s32 IsObjectOfKind(void* a, s32 b);
void SetPlayerState(PlacedObject* self, s32 a, s32 b);
void ConstrainVectorByParentAnchor(Collider* self, Vec02* anchor, Vec02* in, Vec02* out, Vec02* dir);

void func_0013BE18(ChildGroupObject* self, Collider* other)
{
    Vec02 d;
    Vec02 r;
    if (IsObjectOfKind(self, 0x3D) != 0) {
        d = *(Vec02*)((u8*)self + 0x700);
    } else {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
    }
    d.z = 0.0f;
    Vec02* p = &d;
    Vu0::Q(*p) = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector));
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAt(D_00261360), Vu0::Q(g_unitZVector), Vu0::ScalarAt(D_00261364[0]));
    ConstrainVectorByParentAnchor(other, &other->v440, &r, &r, 0);
    other->desc02()->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

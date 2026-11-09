// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 219/260 (84.2%), checked 2026-11-09
// Still differs (2026-11-09, scalar-slot): with Scalar's slot a cast's copy (MEM_SCALAR_P; docs/TOOLCHAIN.md "The weight slot is a cast's copy") the method-table load (lw v1,0(s0)) and the weights are retail's, the delay slot holds the last weight store and the size is retail's 260; left: the address of r for the call (addiu a1,sp,16) issues first, where retail has it after the weight's store. Tried r written through *(u128*)&r and Vu0::Set, and the descriptor read after the sum or inside the call: unchanged.
// Tried night-close8 after FromFloatAt's "rV" (2026-11-08), 8 compiles: the weights now load into the registers of their lui as retail's (lw v1,7380(v1), lw a0,7384(a0)), but the scheduling around them moved: 11 differing words became 29; the descriptor read into a local before the sum gives 26 (here). Set for the sum, Vec values, the descriptor read first in the function: no closer.
// NEAR: scheduling only: retail puts the vtable load (lw v1,0(s0)) right after move a0,s0, the addiu a1,sp,16 after the weight's sqc2 and the last weight store in the jalr's delay slot; here addiu a1 comes first, the vtable load after the sum's store and the jalr's slot is a nop (the C is 264 bytes, retail's 260).
// Before: NEAR: identical but for three details: the vtable load (lw v1,0(s0)) sits before the vmulax in retail and after the vmaddx here; the two weights load into v1 and a0 (the registers of their lui) where ours uses a1 and v1; retail issues the last weight store (sqc2 vf4) in the delay slot of the jalr. WeightAt is FromFloatAt in a 16-byte local, the lw-form of Vu0::Scalar, which include/vu0.h lacks. Tried loading the method or the descriptor first, naming the weights, and a pointer to r.
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

void func_0014F168(PlacedObject* self, PlacedObject* other)
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

// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 264/260, checked 2026-11-08
// NEAR: identical but for three details: the vtable load (lw v1,0(s0)) sits before the vmulax in retail and after the vmaddx here; the two weights load into v1 and a0 (the registers of their lui) where ours uses a1 and v1; retail issues the last weight store (sqc2 vf4) in the delay slot of the jalr. WeightAt is FromFloatAt in a 16-byte local, the lw-form of Vu0::Scalar, which include/vu0.h lacks. Tried loading the method or the descriptor first, naming the weights, and a pointer to r.
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
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), WeightAt(D_00261CD4), Vu0::Q(g_unitZVector), WeightAt(D_00261CD8));
    other->desc02()->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

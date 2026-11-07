// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 282/332 (84.9%), checked 2026-11-07
// NEAR: the same call tree as func_0014F168 and the same remainder: the two weights load into a1 and v1 (retail v1 and a0, the registers of their lui), the moves of the call arguments are scheduled before the vector work here and after it (and the last weight store) in retail. D_00261364 is INCLUDE_DATA in src (f32 D_00261364[3] = { 800, 0, 0 }); WeightAt is FromFloatAt in a 16-byte local.
#include "common.h"
#include "child_group_object.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_00261360;
extern f32 D_00261364[];
s32 IsObjectOfKind(void* a, s32 b);
void SetPlayerState(PlacedObject* self, s32 a, s32 b);
void ConstrainVectorByParentAnchor(Collider* self, Vec02* anchor, Vec02* in, Vec02* out, Vec02* dir);

// A float read from memory as a weight: stored in a slot of its own that the next weight shares.
static inline u128 WeightAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

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
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), WeightAt(D_00261360), Vu0::Q(g_unitZVector), WeightAt(D_00261364[0]));
    ConstrainVectorByParentAnchor(other, &other->v440, &r, &r, 0);
    other->desc02()->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 243/256 (94.9%), checked 2026-11-07
// NEAR: identical but for the register that holds the address of the direction vector: retail forms it (move a0,sp) right after the lq of the velocity and keeps it in a0, ours puts it in a2 or v1 and the high half of D_00275898 takes a0 (the sqc2 of the scaled direction then addresses 0(a2)). Tried p = &d, a reference to Q(d), Q(*p), the float read early.
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_00275894;
extern f32 D_00275898;
void TurnColliderTowardHeading(TintBlendCollider* self);
void SetPlayerState(TintBlendCollider* self, s32 a, s32 b);
f32 WrapAngle(f32 a);
f32 ArctangentOfRatio(f32 a, f32 b);

void func_001DF600(TintBlendCollider* self, TintBlendCollider* other)
{
    Vec02 d = self->v150;
    d.z = 0.0f;
    u128& q = Vu0::Q(d);
    Vec02 k;
    u128 n = Vu0::NormalizeOr(q, Vu0::Q(g_unitXVector));
    Vu0::Q(k) = Vu0::FromFloatAt(D_00275894);
    f32 z = D_00275898;
    q = Vu0::MulX(n, Vu0::Q(k));
    d.z = z;
    other->desc02()->m20(other, &d);
    other->f638 = WrapAngle(ArctangentOfRatio(d.y, d.x) + 3.1415927f);
    TurnColliderTowardHeading(other);
    SetPlayerState(other, 4, 0x2B);
}

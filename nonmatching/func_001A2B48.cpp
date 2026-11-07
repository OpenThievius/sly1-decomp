// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 488/484, checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "effect_spawner.h"
#include "collider.h"
#include "world.h"
#include "globals.h"
// NEAR (2026-11-08, worker vu0w4-e1): one instruction too many and one place: retail fills the nop
// after c.lt.s (the compare of the velocity's length with 0.0001) with `addiu v1,s2,160`, the address
// of the effect's vA0 that the normalized direction is stored through (and that BuildBasisFromX gets as
// s4 by a move), here the address is formed before the compare and the nop stays. Everything else is
// retail's. Tried: the value in a local before the store, Vu0::Set, a pointer variable for vA0
// (each changes the VU0 registers of the direction).

typedef int Quadword128 __attribute__((mode(TI)));
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
s32 IsEffectAimCandidate(Rec50* self, Collider* other);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), s32 p4, s32* n, Collider*** list);
Collider* FindNearestSpanObject(s32 flags, void* a1, void* a2, s32 count, Collider** list, ColliderSpan* out);
void BuildBasisFromX(void* x, void* out);
extern const Vec02 D_00248D20;

void func_001A2B48(Effect* self, Rec50* src)
{
    f32* poly = (f32*)((u8*)src + 0x1C0);
    f32 speed = self->m30[0];
    f32 peak = poly[0];
    f32 a = peak;
    f32 b = poly[1];
    f32 c = poly[2];
    peak = (a + b + c) >? peak;
    if (0.0001f < __builtin_fabsf(c)) {
        f32 t = -b / (c + c);
        peak = (a + t * (b + t * c)) >? peak;
    }
    Vec02 end;
    ColliderSpan span;
    s32 n;
    Collider** list;
    Quadword128 tq;
    Quadword128 uq;
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->qA0)));
    f32 reach = speed * peak;
    Vec02* from = (Vec02*)&self->q80;
    Vu0::Q(self->qA0) = Vu0::NormalizeOr(Vu0::Q(self->qA0), Vu0::Q(D_00248D20));
    Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(*from), Vu0::Q(self->qA0), Vu0::Scalar(reach * 100.0f));
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, from, &end, (s32 (*)(void*, Collider*))IsEffectAimCandidate, (s32)src, &n, &list);
    if (FindNearestSpanObject(1, from, &end, n, list, &span) != 0) {
        speed = speed * span.time[0];
    }
    PopBackMemoryMark();
    StoreFloatAsQuadword(&tq, speed);
    Quadword128 tv = tq;
    CopyQuadword(&uq, poly);
    StoreQuadword(&self->q30, ScaleQuadword(tv, uq));
    BuildBasisFromX(&self->qA0, self->rot50);
    Vu0::Q(self->qA0) = Vu0::Zero();
}

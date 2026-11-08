// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 888/904, checked 2026-11-07
// NEAR: the frame (0x100), the calls and both VU0 loops are retail's. Differences: the early
//       returns (retail jumps straight to the epilogue with the value in each delay slot; ours
//       shares a block), the corner count: retail keeps the 4 as a register it loads twice (`li v0, 4;
//       sll a0, v0, 4` and `blez v0`) where ours folds it, the flag test `(x & 1) == 0` (retail
//       andi, bnel; ours xori, beqz), the switch's range tests, and the registers ($s2 for the object
//       in retail, $s1 here). About 20 compiles.
#include "common.h"
#include "switched_collider.h"
#include "collider.h"
#include "placed_object.h"
#include "world.h"
#include "vu0.h"

extern f32 D_00274620[16];
extern f32 D_00274660[16];
s32 IsObjectOfKind(void* a, s32 b);
s32 GetAgentRosterState(CompanionAgent* self);
s32 IsCompanionAgentBlocker(CompanionAgent* self, Collider* ent);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
s32 IsPadSelectFlagHeld(World* world);
s32 TestPointAgainstObjectShape(s32 shape, Vec02* p);
void* PushSoundLevel(s32 kind);
void RemoveSoundLevelAndRecompute(void* p);
s32 func_0015AA50(void* shape, Vec02* p);
s32 func_001CB3D0(CompanionAgent* self);
void TransformPointBetweenFrames(void* from, s32 to, void* in, void* out);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(CompanionAgent*, Collider*), CompanionAgent* self, s32* n, Collider*** list);
s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);

#define F(T, o) (*(T*)((u8*)self + (o)))

s32 func_001B7280(CompanionAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0) return 0;
    if (F(s32, 0xCCC) != 0) return 0;
    if (F(s32, 0xCC8) != 0) return 1;
    PlacedObject* target = (PlacedObject*)self->desc08()->m62(self);
    if (target == 0) return 0;
    if (self->fC14 == 0) return 0;
    if (self->f724 == 0xB) return 0;
    if (self->f724 == 0x10) return 0;
    Vec02 a;
    if (IsObjectOfKind(target, 6) != 0) {
        if (F(s32, 0x690) != 0) {
            a = *(Vec02*)((u8*)target + 0x6A0);
        } else {
            a = target->v140;
            a.z -= 70.0f;
        }
    } else {
        a = target->v140;
    }
    Vec02 delta;
    Vu0::Q(delta) = Vu0::Sub(Vu0::Q(a), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(delta), Vu0::Q(delta))));
    s32 near;
    if (self->fC2C != 0) {
        near = TestPointAgainstObjectShape(self->fC2C, &a);
    } else {
        near = 0;
        if (dist < self->fC20) {
            if (__builtin_fabsf(delta.z) < self->fC24) near = 1;
        }
    }
    if (near != 0) {
        if (self->fCC0 == 0) self->fCC0 = PushSoundLevel(-0x14);
    } else {
        RemoveSoundLevelAndRecompute(self->fCC0);
        self->fCC0 = 0;
    }
    if (func_0015AA50(self->fC14, &a) == 0) {
        if (self->fC18 < dist) return 0;
        if (self->fC1C < __builtin_fabsf(delta.z)) return 0;
    }
    s32 v = GetAgentRosterState(self);
    if (!(F(s32, 0xCD0) & 1)) {
        if (v != 2) {
            if (func_001CB3D0(self) != 0) return 0;
        }
    }
    if (F(s32, 0xCD0) & 2) return 1;
    f32* table;
    switch (v) {
    case 0:
    case 1:
        table = D_00274660;
        break;
    case 2:
        table = D_00274620;
        break;
    }
    Vec02* pos = F(PlacedObject*, 0x734) != 0 ? &F(PlacedObject*, 0x734)->v140 : &self->v140;
    PushBackMemoryMark();
    Vec02 lo = *pos;
    Vec02 hi = *pos;
    s32 n = 4;
    Vec02* buf = (Vec02*)AllocateBackMemory(n << 4);
    Collider*** listp;
    s32 count;
    Collider** list;
    for (s32 i = 0; i < n; i++) {
        TransformPointBetweenFrames(target, 0, table + i * 4, &buf[i]);
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(buf[i]));
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(buf[i]));
    }
    GatherCollidersInBox(self->world, 0, &lo, &hi, IsCompanionAgentBlocker, self, &count, &list);
    s32 i = 0;
    while (i < 4) {
        if (FindNearestSpanObject(0, pos, &buf[i], count, list, 0) == 0) break;
        i++;
    }
    PopBackMemoryMark();
    return i < 4;
}

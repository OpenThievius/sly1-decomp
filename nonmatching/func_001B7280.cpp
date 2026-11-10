// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 896/904, checked 2026-11-10
// NEAR (2026-11-08, night-sizex2): 896 bytes for retail's 904 (was 888). The corner count set in
// each arm of the table's switch (n = 4 at a join is no constant to CSE, so the allocation and
// the loop take it from a register as retail does) and a third `case 3: break;` for the
// switch's tree (retail's compares are bltz, slti 2, then 2) gave 8 bytes and about half the
// differing words. Still differs: self in s3 and the table in s2 here (retail s2 and s1, with
// the table copied to s3 and the count put in s1 before the loop: `move s3, s1; li s1, 4`, and
// the count loaded again as `li v0, 4` for the allocation's size and the loop's first test),
// the return after func_001CB3D0 (retail bnez to the epilogue, ours beqzl) and the compare
// tree's order (default, the bltz, first in retail).
// Before (night-size4): the target's 0x690 flag is read from the target, the zero returns that
// retail sends straight to the epilogue are joined with || (bnez with move v0,zero in the slot),
// and the flag test is `(x & 1) == 0` (retail's andi, bnezl).
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
    if (IsPadSelectFlagHeld(self->world) != 0 || F(s32, 0xCCC) != 0) return 0;
    if (F(s32, 0xCC8) != 0) return 1;
    PlacedObject* target = (PlacedObject*)self->desc08()->m62(self);
    if (target == 0) return 0;
    if (self->fC14 == 0 || self->f724 == 0xB || self->f724 == 0x10) return 0;
    Vec02 a;
    if (IsObjectOfKind(target, 6) != 0) {
        if (*(s32*)((u8*)target + 0x690) != 0) {
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
    if ((F(s32, 0xCD0) & 1) == 0) {
        if (v != 2) {
            if (func_001CB3D0(self) != 0) return 0;
        }
    }
    if (F(s32, 0xCD0) & 2) return 1;
    f32* table;
    s32 n;
    switch (v) {
    case 0:
    case 1:
        table = D_00274660;
        n = 4;
        break;
    case 2:
        table = D_00274620;
        n = 4;
        break;
    case 3:
        break;
    }
    Vec02* pos = F(PlacedObject*, 0x734) != 0 ? &F(PlacedObject*, 0x734)->v140 : &self->v140;
    PushBackMemoryMark();
    Vec02 lo = *pos;
    Vec02 hi = *pos;
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

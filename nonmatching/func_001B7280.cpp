// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 591/904 (65.4%), checked 2026-11-11
// Wave 23 (w23-vuD, 2026-11-11): re-scored, unchanged (591/904); not worked on this wave (the replay tools address register and order differences; this one's are structural: the case tree, the third equal set and the branching return).
// NEAR (2026-11-10, worker w16-1B7280): retail's size now (was 896), 591 of 904 bytes. The
// count is a constant retail never keeps in a register: `li v0, 4; sll a0, v0, 4` for the
// allocation, `li v0, 4; blez v0` for the loop's first test and `li s1, 4` for its counter are
// reload putting back the REG_EQUIV constant of a pseudo global-alloc left without a register
// (all nine saved registers are taken over its life), and the arms' `n = 4` sets are the
// equivalence's init insns reload deletes. update_equiv_regs doubles n's live length once per
// equal constant set (2 sets: 130 x 4 = 520, priority 2*5/520 = 0.0192); the table's first set
// doubles it once and the second, another constant, ends the equivalence (127 x 2 = 254,
// 3/254 = 0.0118). n ranks first and takes s1, the table s3 and the loop's table pointer with
// it (no `move s3, s1`). A third equal set gives 0.0096: the table is placed first and takes s1,
// n finds no register, and the allocation, the test and the counter come out as retail's.
// `case 3: n = 4;` below is that third set; retail's compare tree has no node for 3 (bltz,
// slti 2, then 2, which cases {0-1} and {2} alone give: see b7 in the worker's folder), so the
// real third set is elsewhere. Ruled out: `default: n = 4` or `s32 n = 4;` anywhere before the
// switch (every path then sets n = 4, GCSE's cprop sees the set available at the uses, loop.c
// knows the trip count: `li s4, 3; bgez`), `case 3: n = 4` (the extra compare). Still differs:
// the tree; self in s3 here (retail s2: the case 3 insns lengthen its life past the loop
// pointer's priority, 0.679 against 0.700); i and the loop's `i < 4` swapped (s2/s1); and the
// return, which retail branches on (`bnez s2` to `li v0, 1`, else `move v0, zero`) where every
// form tried (`return i < 4`, `if (i < 4) return 1; return 0;`, `i == 4`, `i != 4`, a ?:) is a
// store-flag here; `if (i == 4) return 0; return 1;` is 4 bytes longer.
// Before (night-sizex2): the corner count set in each arm of the table's switch (n = 4 at a
// join is no constant to CSE) and the flag tests: the target's 0x690 flag is read from the
// target, the zero returns that retail sends straight to the epilogue are joined with ||
// (bnez with move v0,zero in the slot), and the flag test is `(x & 1) == 0` (retail's andi,
// bnezl).
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
s32 IsPointInsideObjectFaces(void* shape, Vec02* p);
s32 IsPlayerUntargetableByAgent(CompanionAgent* self);
void TransformPointBetweenFrames(void* from, s32 to, void* in, void* out);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(CompanionAgent*, Collider*), CompanionAgent* self, s32* n, Collider*** list);
s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);

#define F(T, o) (*(T*)((u8*)self + (o)))

s32 IsCompanionAgentTargetReachable(CompanionAgent* self)
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
    if (IsPointInsideObjectFaces(self->fC14, &a) == 0) {
        if (self->fC18 < dist) return 0;
        if (self->fC1C < __builtin_fabsf(delta.z)) return 0;
    }
    s32 v = GetAgentRosterState(self);
    if ((F(s32, 0xCD0) & 1) == 0) {
        if (v != 2) {
            if (IsPlayerUntargetableByAgent(self) != 0) return 0;
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
        n = 4;
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

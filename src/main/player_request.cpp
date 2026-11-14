// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "game_clock.h"
#include "aim_blend_grid.h"
#include "placed_object.h"
#include "vertex_batch.h"
#include "packet_writer.h"
#include "vu0.h"
#include "ring_params.h"
#include "deferred_request.h"
#include "object_finder.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/heap.h"
#include "functions/path_follower.h"
#include "functions/player.h"
#include "functions/player_request.h"
#include "functions/player_target.h"
#include "functions/pooled_object.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"

// Types other files define, named by the parameters of their functions declared here.
struct TargetArcSource;

s32 g_playerBlendDeltaIdsA[2] = {286, 287};
s32 g_playerBlendDeltaIdsB[2] = {288, 289};
s32 D_00274FB0[2] = {2, 2};
s32 D_00274FB8[2] = {48, 64};

struct PlayerTableEntry { s32 id; f32 v; BaseObject* object; };
PlayerTableEntry g_playerObjectTable[8] = {
    { 0x35, 30.0f, 0 }, { 0x36, 30.0f, 0 }, { 0x37, 30.0f, 0 }, { 0x3A, 30.0f, 0 },
    { 0x50, 60.0f, 0 }, { 0x58, 30.0f, 0 }, { 0x170, 30.0f, 0 }, { 0, 0.0f, 0 }
};
float D_00275020[4] = {0.0f, 10.0f, 0.00999999978f, 0.0f};
f32 D_00275030[4] = { 3.5f, 0.0f, 0.5f, 0.0f };
f32 D_00275040[4] = { 0.0f, 0.0f, -1000.0f, 0.0f };
f32 D_00275050[4] = { -0.5f, -0.0025f, 0.0f, 0.0f };
f32 D_00275060[2] = { 0.0f, 0.7f };
f32 D_00275068[1] = { 0 };
float D_0027506C = 0.25f;
float g_ringSevenPoints[14] = {0.0f, 1.0f, 0.781831503f, 0.623489797f, 0.974927902f, -0.222520933f, 0.433883727f, -0.90096885f, -0.433883727f, -0.90096885f, -0.974927902f, -0.222520933f, -0.781831503f, 0.623489797f};
float g_ringSeventeenPoints[34] = {1.0f, 0.0f, 0.932472229f, 0.361241668f, 0.739008904f, 0.673695624f, 0.445738345f, 0.895163298f, 0.0922683626f, 0.995734155f, -0.273662984f, 0.961825669f, -0.602634609f, 0.798017204f, -0.850217164f, 0.526432157f, -0.982973099f, 0.183749512f, -0.982973099f, -0.183749512f, -0.850217164f, -0.526432157f, -0.602634609f, -0.798017204f, -0.273662984f, -0.961825669f, 0.0922683626f, -0.995734155f, 0.445738345f, -0.895163298f, 0.739008904f, -0.673695624f, 0.932472229f, -0.361241668f};

// The eight blend slots func_001D4148 fills (0x20 bytes each), the weight of slot 6 first.
struct BlendSlotObject;
struct BlendSlot {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10: where the object's mover puts it
};

typedef void (*SlotMoveFn)(PoseSource* m, void* body, f32 x, f32 y, s32 z, Vec02* out, Vec02* out2);
struct SlotMover { SlotMoveFn* vtbl; };
struct SlotMoverHolder { u8 pad00[4]; SlotMover* mover; };
struct BlendSlotObject {
    u8 pad00[0x34];
    f32 duration;           // 0x34
    u8 pad38[0x9C - 0x38];
    SlotMoverHolder* holder; // 0x9C
};

struct BlendAnimation;
struct Collider;
BlendSourceEntry* FindEntryByObjectId(BlendAnimationView* self, BaseObject* key);

struct PlayerBlendItem {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    f32 timeAtFirstKey;     // 0x30
    u8 pad34[0x40 - 0x34];
    f32 timeAtSecondKey;    // 0x40
    u8 pad44[0x50 - 0x44];
};
struct PlayerBlendCurve { u8 pad00[0x10]; void* f10; };


void CreateSixEntryBlend(TurningCollider* self, PlayerBlendItem* items, BlendAnimationView** out)
{
    Vec02 a0;
    Vec02 a10;
    BlendAnimationView* blend;
    s32 i;

    if (items[0].object == 0) {
        *out = 0;
        return;
    }
    items[0].weight = 1.0f;
    ComputeWrappedDeltas(0x50, 6, (u8*)items, 0x30, 2, g_playerBlendDeltaIdsA);
    ComputeWrappedDeltas(0x50, 6, (u8*)items, 0x40, 2, g_playerBlendDeltaIdsB);
    for (i = 0; i < 6; i++) {
        PlayerBlendItem* it = &items[i];
        BlendSlotObject* o = it->object;
        if (o != 0) {
            f32 one = 1.0f;
            SlotMover* m = o->holder->mover;
            (*m->vtbl)((PoseSource*)m, self, 0.0f, one, 0, &a0, 0);
            m = o->holder->mover;
            (*m->vtbl)((PoseSource*)m, self, o->duration, one, 0, &a10, 0);
            *(Vu0::Vec*)&it->v10 = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(a0), Vu0::Vec::Of(a10)), Vu0::Vec::ScalarAt(o->duration));
            Vec02 a20;
            m = (SlotMover*)FindEntryByObjectId((BlendAnimationView*)it->object, (BaseObject*)self->f610)->mover;
            (*m->vtbl)((PoseSource*)m, self->f610, it->timeAtFirstKey, one, 0, &a20, 0);
            Vec02 a30;
            m = (SlotMover*)FindEntryByObjectId((BlendAnimationView*)it->object, (BaseObject*)self->f614)->mover;
            (*m->vtbl)((PoseSource*)m, self->f614, it->timeAtSecondKey, one, 0, &a30, 0);
            Vu0::Vec h = Vu0::Vec::Scalar(0.5f);
            *(Vu0::Vec*)&it->v20 = Vu0::MulXSum(Vu0::Vec::Of(a20), h, Vu0::Vec::Of(a30), h);
        }
    }
    BuildCombinedBlendAnimation((TurningCollider*)self, 0x50, 6, (u8*)items, 2, D_00274FB8, D_00274FB0, (BlendAnimation**)&blend);
    for (s32 j = 0; j < blend->f38; j++) {
        BlendSourceEntry* e = (BlendSourceEntry*)(blend->f3C + j * 0x1C);
        s32 k = e->key;
        if (k >= 0x37) {
            if (k < 0x3A) {
                continue;
            }
            if (k < 0x3D) {
                if (e->mover != 0) {
                    ((PlayerBlendCurve*)e->mover)->f10 = blend->pC0 + 1;
                }
                if (e->sub != 0) {
                    ((PlayerBlendCurve*)e->sub)->f10 = blend->pC0 + 1;
                }
                continue;
            }
        }
        if (e->mover != 0) {
            ((PlayerBlendCurve*)e->mover)->f10 = 0;
        }
        if (e->sub != 0) {
            ((PlayerBlendCurve*)e->sub)->f10 = 0;
        }
    }
    SetBlendItemWeights(blend, 0x50, 6, items);
    if (out != 0) {
        *out = blend;
    }
}

struct WeightedRow { f32 w; u8 pad0[0xC]; Vec02 v; u8 pad1[0x14]; f32 d; u8 pad2[0x18]; };

void SumBlendEntryVectors(s32 n, WeightedRow* rows, f32* scale, Vec02* out)
{
    Vec02 k;
    Vu0::Q(*out) = Vu0::Zero();
    if (n > 0) {
        do {
            f32 t = rows->w * (rows->d / scale[1]);
            Vu0::Q(k) = Vu0::FromFloat(t);
            Vu0::Q(*out) = Vu0::MulAddX(Vu0::Q(*out), Vu0::Q(rows->v), Vu0::Q(k));
            rows++;
        } while (--n);
    }
}
ASM_FUNC(func_001D3A38);
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);

s32 FindObjectAlongSegment(PlacedObject* self, Vec02* from, Vec02* to, f32* ratio)
{
    Vec02 a;
    Vec02 b;
    ColliderSpan hit;
    s32 count;
    Collider** list;
    a = *from;
    b = *to;
    PushBackMemoryMark();
    GatherCollidersInBox(self->world, (Collider*)self, &a, &b, 0, 0, &count, &list);
    s32 found = FindNearestSpanObject(0, &a, &b, count, list, &hit);
    *ratio = found != 0 ? Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(hit.q[0]), Vu0::Q(a)))) / Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(b)))) : 1.0f;
    PopBackMemoryMark();
    return found != 0;
}

extern "C" f32 ConvertDoubleToFloat(u64 bits);

s32 FillOuterProductTable(s32 stride, s32 n, s32 m, char* out, ...) {
    f32 rows[16];
    f32 cols[16];
    u64* ap = (u64*)((char*)__builtin_next_arg(out) - 32);
    f32 sum = 0.0f;
    s32 i;
    s32 j;
    s32 changed;
    for (i = 1; i < n; i++) {
        ap++;
        rows[i] = ConvertDoubleToFloat(ap[-1]);
        sum += rows[i];
    }
    rows[0] = 1.0f - sum;
    sum = 0.0f;
    for (j = 1; j < m; j++) {
        ap++;
        cols[j] = ConvertDoubleToFloat(ap[-1]);
        sum += cols[j];
    }
    cols[0] = 1.0f - sum;
    char* p = out;
    changed = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum = rows[i] * cols[j];
            if (sum != *(f32*)p) {
                *(f32*)p = sum;
                changed = 1;
            }
            p += stride;
        }
    }
    return changed;
}

extern "C" u64 ConvertFloatToDouble(f32 x);

struct BlendSpan { f32 t; u8 pad4[8]; f32 len; };
struct BlendSpans { u8 pad0[8]; BlendSpan* a; u8 padC[8]; BlendSpan* b; };

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))

void InterpolateBlendEntryPosition(void* p, void* e, f32 a, f32 b, s32 i, s32 j, void* out);

void UpdateSixEntryBlendWeights(TurningCollider* p, void* e, BlendAnimationView* g, void* a3)
{
    f32 t;
    f32 lo;
    f32 hi;
    Vec02 va;
    Vec02 vb;
    Vec02 vd;
    Vec02 vc;
    if (W(e, 0x54) == 0) {
        t = 0.0f;
    } else {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        f32 d0 = F(p, 0x640) - F(e, 0x10);
        f32 d1 = F(p, 0x640) - F(e, 0x60);
        f32 n = F(e, 0x34) * d0;
        t = n / (n - F(e, 0x84) * d1);
        if (t < zero) {
            t = zero;
        } else if (one < t) {
            t = one;
        }
    }
    if (W(e, 0xA4) == 0) {
        lo = 0.0f;
        hi = lo;
    } else {
        BlendSpans* sp = (BlendSpans*)g->pC0;
        f32 now = F(a3, 0x14);
        f32 x = sp->a->t - now;
        if (x <= 0.0f) {
            x += g->f34;
        }
        f32 q = x / sp->a->len;
        f32 y = sp->b->t - now;
        if (y <= 0.0f) {
            y += g->f34;
        }
        f32 r = y / sp->a->len;
        hi = q;
        lo = (r <? q);
        InterpolateBlendEntryPosition(p, e, lo, t, 2, 3, &va);
        InterpolateBlendEntryPosition(p, e, lo, t, 0, 1, &vb);
        if (FindObjectAlongSegment(p, &va, &vb, (f32*)&vc)) {
            lo = 0.0f;
            hi = 1.0f - vc.x;
        } else if (W(e, 0x144) != 0) {
            InterpolateBlendEntryPosition(p, e, lo, t, 4, 5, &vd);
            if (FindObjectAlongSegment(p, &vb, &vd, (f32*)&vc)) {
                lo = vc.x;
                hi = 0.0f;
            } else {
                lo = 1.0f;
                hi = 0.0f;
            }
        } else {
            lo = 0.0f;
            hi = lo;
        }
    }
    u64 hv = ConvertFloatToDouble(hi);
    u64 lv = ConvertFloatToDouble(lo);
    u64 tv = ConvertFloatToDouble(t);
    if (FillOuterProductTable(0x50, 3, 2, (char*)e, hv, lv, tv)) {
        SetBlendItemWeights(g, 0x50, 6, e);
        SumBlendEntryVectors(6, (WeightedRow*)e, (f32*)g->pC0->p8, &p->headingVelocity);
    }
}

#undef F
#undef W

// The six blend records func_001D40A0 hands to func_001399F8 (0x50 bytes each): the weight
// of each at its start; the second record's word at +4 says whether it blends at all.
struct TurnBlendRecords {
    f32 weight0;
    u8 pad4[0x4C];
    f32 weight1;
    s32 secondBlends;
    u8 pad58[0x48];
    s32 weight2;
    u8 padA4[0x4C];
    s32 weight3;
    u8 padF4[0x4C];
    s32 weight4;
    u8 pad144[0x4C];
    s32 weight5;
};


void SetPlayerBlendWeights(f32 f12, f32 f13, TurningCollider* a0, TurnBlendRecords* a1, BlendAnimationView* a2)
{
    a0->heading = f12;
    if (a1->secondBlends == 0) {
        a1->weight0 = 1.0f;
        a1->weight1 = 0.0f;
    } else {
        f32 one = 1.0f;
        a1->weight1 = f13;
        a1->weight0 = one - f13;
    }
    a1->weight2 = 0;
    a1->weight4 = 0;
    a1->weight3 = 0;
    a1->weight5 = 0;
    SetBlendItemWeights(a2, 0x50, 6, a1);
    SumBlendEntryVectors(6, (WeightedRow*)a1, (f32*)a2->pC0->p8, (Vec02*)&a0->f640);
}

void CreateEightEntryBlend(TurningCollider* self, BlendSlot* slots, BlendAnimationView** gr)
{
    Vec02 here;
    Vec02 there;
    Vec02 delta;
    Vec02 k;
    s32 i;
    slots[6].weight = 1.0f;
    for (i = 0; i < 8; i++) {
        BlendSlot* e = &slots[i];
        BlendSlotObject* o = e->object;
        if (o->holder && o->holder->mover) {
            SlotMover* m = o->holder->mover;
            (*m->vtbl)((PoseSource*)m, self, 0.0f, 1.0f, 0, &here, 0);
            m = o->holder->mover;
            (*m->vtbl)((PoseSource*)m, self, o->duration, 1.0f, 0, &there, 0);
            Vu0::Q(delta) = Vu0::Sub(Vu0::Q(there), Vu0::Q(here));
            Vu0::Q(k) = Vu0::FromFloat(-1.0f / o->duration);
            Vu0::Q(e->v10) = Vu0::MulX(Vu0::Q(delta), Vu0::Q(k));
        } else {
            switch (i) {
            case 0:
            case 2:
            case 4:
            case 6: {
                SlotMover* m = (SlotMover*)FindEntryByObjectId((BlendAnimationView*)e->object, (BaseObject*)self->f610)->mover;
                (*m->vtbl)((PoseSource*)m, self->f610, 0.0f, 1.0f, 0, 0, &e->v10);
                break;
            }
            case 1:
            case 3:
            case 5:
            case 7: {
                SlotMover* m = (SlotMover*)FindEntryByObjectId((BlendAnimationView*)e->object, (BaseObject*)self->f614)->mover;
                (*m->vtbl)((PoseSource*)m, self->f614, 0.0f, 1.0f, 0, 0, &e->v10);
                break;
            }
            }
        }
    }
    BuildCombinedBlendAnimation(self, 0x20, 8, (u8*)slots, 0, 0, 0, (BlendAnimation**)gr);
    SetBlendItemWeights(*gr, 0x20, 8, slots);
}
// The three weights of the slots base[0], base[2] and base[4] that follow self->v640: each is
// the part of v640 along the slot's vector over the squared length, scaled by `scale` and at
// least zero. They are made to add up to at most one; what is left goes to base[6].
static inline void SetSlotWeights(Player* self, BlendSlot* slots, s32 o, f32 scale)
{
    f32 zero;
    u128 v = Vu0::Q(slots[o + 0].v10);
    f32 length = scale * Vu0::ToFloatMoved(Vu0::Dot(v, v));
    f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->headingVelocity), v));
    f32 first = along / length;
    zero = 0.0f;
    u128 v2 = Vu0::Q(slots[o + 2].v10);
    f32 length2 = scale * Vu0::ToFloatMoved(Vu0::Dot(v2, v2));
    u128 v4 = Vu0::Q(slots[o + 4].v10);
    f32 length4 = scale * Vu0::ToFloatMoved(Vu0::Dot(v4, v4));
    f32 w0 = first >? zero;
    slots[o + 0].weight = w0;
    f32 second = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->headingVelocity), v2)) / length2;
    f32 w2 = second >? zero;
    slots[o + 2].weight = w2;
    f32 w4 = (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->headingVelocity), Vu0::Q(slots[o + 4].v10))) / length4) >? zero;
    slots[o + 4].weight = w4;
    f32 sum = w0 + w2 + w4;
    if (sum < 1.0f) {
        slots[o + 6].weight = 1.0f - sum;
    } else {
        slots[o + 0].weight = w0 / sum;
        slots[o + 2].weight = w2 / sum;
        slots[o + 4].weight = w4 / sum;
        slots[o + 6].weight = zero;
    }
}

void UpdateEightEntryBlendWeights(Player* self, BlendSlot* slots, BlendAnimationView* gr)
{
    Vec02 acc;
    f32 scale = *(f32*)((u8*)self->stateAnimPlayer + 0x18);
    s32 i;
    if (self->eightWayHalf == -1) {
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->headingVelocity), Vu0::Q(slots[0].v10))) < 0.0f)
            self->eightWayHalf = 1;
        else
            self->eightWayHalf = 0;
    }
    for (i = 0; i < 8; i++)
        slots[i].weight = 0.0f;
    switch (self->eightWayHalf) {
    case -1:
        break;
    case 0:
        SetSlotWeights(self, slots, 0, scale);
        break;
    case 1:
        SetSlotWeights(self, slots, 1, scale);
        break;
    }
    Vu0::Q(acc) = Vu0::Zero();
    BlendSlot* e = slots;
    for (i = 0; i < 8; i++) {
        Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(e->v10), Vu0::ScalarAt(e->weight));
        e++;
    }
    Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(acc), Vu0::Scalar(scale));
    SetBlendItemWeights(gr, 0x20, 8, slots);
}
static inline f32 MinF(f32 a, f32 b) { return b <? a; }
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

// The velocity of a heading and speed, from six axes of the basis: forward (y) by the
// heading's length ahead, and right or left by its side (x), the set picked by the walk mode.
void SetPlayerVelocityFromHeading(Player* self, const Vec02* basis, BlendAnimationView* blend, f32 heading, f32 speed)
{
    Vec02 h;
    ComputePolarOffset((Vec3*)&h, heading - self->heading, speed, 0.0f);
    f32 m;
    if (10.0f < h.y) {
        if (self->eightWayHalf == 0) {
            h.y = 0.0f;
            m = 0.0f;
        } else {
            m = 1.0f;
        }
    } else if (h.y < -10.0f) {
        if (self->eightWayHalf == 1) {
            h.y = 0.0f;
            m = 1.0f;
        } else {
            m = 0.0f;
        }
    } else if (self->eightWayHalf == -1) {
        m = 0.0f;
    } else {
        m = (f32)self->eightWayHalf;
    }
    if (m == 1.0f) {
        u128 s = Vu0::Scalar(h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->headingVelocity) = Vu0::MulXSum3(Vu0::Q(basis[3]), s, Vu0::Q(basis[7]), t, Vu0::Q(basis[11]), u);
    } else {
        u128 s = Vu0::Scalar(-h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->headingVelocity) = Vu0::MulXSum3(Vu0::Q(basis[1]), s, Vu0::Q(basis[5]), t, Vu0::Q(basis[9]), u);
    }
    self->headingVelocity.z = 0.0f;
    Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(self->headingVelocity), Vu0::ScalarAt(*(f32*)((u8*)self->stateAnimPlayer + 0x18)));
}




void ResolvePlayerTableObjects(Player* self)
{
    self->ringCount = 7;
    self->ringAnchors = CopyToFrontMemory(0x54, g_playerObjectTable);
    for (s32 i = 0; i < self->ringCount; i++) {
        PlayerTableEntry* it = (PlayerTableEntry*)self->ringAnchors + i;
        it->object = FindFirstObjectById(self->world, 1, it->id, self);
    }
}


void AddColliderForce(Collider* self, Vec02* force);

void StepPlayerRequestState(Player* self)
{
    Vec02 force;
    switch (self->subState) {
    case 0x25:
    case 0x26: {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(k));
        AddColliderForce(self, &force);
        SteerColliderTowardPosition(self, 0, 0, (Vec02*)&D_00248D30, D_00275020, g_gameClock.dt);
        break;
    }
    case 0x29:
    case 0x30: {
        Vec02 aim;
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(k));
        AddColliderForce(self, &force);
        f32 zero = 0.0f;
        aim = D_00248D30;
        if (self->headingVelocity.z != zero)
            aim.z = self->v150.z;
        SteerColliderTowardPosition(self, 0, 0, &aim, D_00275020, g_gameClock.dt);
        if (self->headingVelocity.z != zero) {
            force = D_00248D30;
            force.z = (-self->headingVelocity.z - aim.z) / g_gameClock.dt;
            AddColliderForce(self, &force);
        }
        break;
    }
    case 0x27: // the states that apply no force of their own
        break;
    case 0x2A:
        break;
    }
    TurnColliderTowardRotation(self, g_gameClock.dt, &self->headingMatrix, &self->turnGain);
}

struct TargetCand;
struct Chooser;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
s32 IsObjectOfKind(BaseObject* list, s32 key);

void UpdatePlayerRequestSubState(Player* self) {
    switch (self->subState) {
    case 0x2B: {
        f32 t = ArctangentOfRatio(self->v150.y, self->v150.x);
        self->heading = ApproachAngleWithRamp(self->heading, t + 3.1415927f, g_gameClock.dt, D_00275030, 0);
        if (0.25f < g_gameClock.time - self->subStateStartTime && self->groundContact != 0) {

            RunPlayerCallback(self);
        }
        break;
    }
    case 0x2C: {
        if (*(f32*)((u8*)self->selfPoseSource + 0x18) < g_gameClock.time) {
            RunPlayerCallback(self);
        } else if (self->touchedObject != 0 && *(f32*)((u8*)self->selfPoseSource + 0x18) < g_gameClock.time + 0.25f &&
                   (IsObjectOfKind((BaseObject*)self->touchedObject, 0x76) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x70) ||
                    IsObjectOfKind((BaseObject*)self->touchedObject, 0x71) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x81) ||
                    IsObjectOfKind((BaseObject*)self->touchedObject, 0x6F) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x7F))) {
            if (self->f26B0 != 0) {
                RunPlayerCallback(self);
            } else {
                void* o = self->touchedObject;
                SetPlayerState(self, 2, 2);
                s32 r = ChoosePlayerTargetByCost((Chooser*)self, (TargetCand*)o);
                SetPlayerState(self, 2, r);
            }
        } else {
            ComputeTargetArc(self, (TargetArcSource*)&self->touchedObject, *(f32*)((u8*)self->selfPoseSource + 0x18) - g_gameClock.time, 0, (Vec02*)((u8*)self->selfPoseSource + 0x20), 0);
        }
        break;
    }
    }
}

void SetPlayerCallback(Player* self, void (*value)(Player* self))
{
    self->cb26B0 = value;
}


void RunPlayerCallback(Player* self)
{
    s32 v = self->pendingFlags;
    void (*fn)(Player* self) = self->cb26B0;

    v &= -0x11;
    self->cb26B0 = 0;

    self->pendingFlags = v;
    if (fn != 0) {
        fn(self);
        return;
    }
    if ((u32)(self->subState - 0x2D) < 5) {
        EndPlayerRequestState(self);
    } else {
        SetPlayerState(self, 2, 2);
    }
}


typedef void (*PlayerRequestFn)(s32 data, Player* self);
struct PlayerRequestMessage { Player* self; s32 v; };

s32 MaskWorldBitsBySave(void);
s32 HasSpareCount(void);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern u32 g_buttonCodeFlags;
extern f32 g_gameTime[];

s32 AcceptPlayerRequest(Player* self, Ev07* msg)
{
    if (self->desc05()->m4B(self, msg->kind) != 0) {
        return 0;
    }
    if (self->state == 6 && self->targetMode == 2) {
        Ev07* tmp = msg;
        TriggerScriptEvent((BaseObject*)self->heldObject, 0x13, 1, &tmp);
        SetPlayerState(self, 2, 5);
        return 0;
    }
    self->lastMessage = *msg;
    if (self->state != 4 && self->state != 0xB && self->pulseActive == 0 && (g_buttonCodeFlags & 1) == 0 &&
        IsPadSelectFlagHeld(self->world) == 0) {
        s32 c;
        switch (self->lastMessage.kind) {
        case 3:
            c = MaskWorldBitsBySave() & 0x100;
            break;
        case 5:
            c = MaskWorldBitsBySave() & 0x4000;
            break;
        default:
            self->f2730 = 1;
            goto check;
        }
        if (c == 0) {
            self->f2730 = 1;
        }
    check:
        if (self->f2730 != 0) {
            if (HasSpareCount() != 0) {
                self->pulseActive = 1;
                self->pulseStartTime = g_gameTime[0];
            }
        }
    }
    SetPlayerCallback(self, 0);
    switch (msg->kind) {
    case 0:
        StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->lastMessage.fn;
            if (fn != 0) {
                self->lastMessage.fn = 0;
                fn(self->lastMessage.data, self);
            } else {
                SetPlayerState(self, 4, 0x2B);
            }
        }
        SetPlayerCallback(self, ContinuePlayerRequestKind0);
        break;
    case 6:
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->lastMessage.fn;
            if (fn != 0) {
                self->lastMessage.fn = 0;
                fn(self->lastMessage.data, self);
            } else {
                SetPlayerState(self, 4, 0x2B);
            }
        }
        if (400.0f < self->v150.z) {
            StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        SetPlayerCallback(self, ContinuePlayerRequestKind6);
        break;
    case 1:
    case 2: {
        s32 id;
        if (self->state == 0xD) {
            (*(Quad16*)&self->savedVelocity) = (*(Quad16*)&self->savedSpin) = *(const Quad16*)&D_00248D30;
        } else {
            (*(Quad16*)&self->savedVelocity) = (*(Quad16*)&self->v150);
            (*(Quad16*)&self->savedSpin) = (*(Quad16*)&self->v160);
        }
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        switch (msg->kind) {
        case 1:
            id = 0x25;
            break;
        case 2:
            id = 0x26;
            break;
        }
        SetPlayerState(self, 4, id);
        SetPlayerCallback(self, ContinuePlayerRequestKind1Or2);
        break;
    }
    case 3:
        if (self->f2730 == 0 || HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x27);
            SetPlayerCallback(self, FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x2F);
        }
        break;
    case 4:
        self->desc02()->m20(self, (Vec02*)D_00275040);
        if (HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x28);
            SetPlayerCallback(self, FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x31);
        }
        break;
    case 5:
        if (self->f2730 == 0 || HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x29);
            SetPlayerCallback(self, FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x30);
        }
        break;
    }
    if (self->f2730 != 0) {
        PlayerRequestMessage m;
        m.self = self;
        m.v = msg->arg;
        self->desc->m0E(self, 0x17, &m);
    }
    return self->f2730;
}

s32 HasSpareCount(void);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void ContinuePlayerRequestKind0(Player* self)
{
    if (self->subState == 0x2C && self->touchedObject != 0 &&
        (IsObjectOfKind((BaseObject*)self->touchedObject, 0x70) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x71) ||
         IsObjectOfKind((BaseObject*)self->touchedObject, 0x81) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x6F) ||
         IsObjectOfKind((BaseObject*)self->touchedObject, 0x7F) || IsObjectOfKind((BaseObject*)self->touchedObject, 0x76))) {
        if (HasSpareCount()) {
            FinishSwitchedCollider(self);
            void* p = self->touchedObject;
            SetPlayerState(self, 2, 2);
            SetPlayerState(self, 2, ChoosePlayerTargetByCost((Chooser*)self, (TargetCand*)p));
        } else {
            SetPlayerState(self, 4, 0x2D);
        }
    } else {
        if (HasSpareCount()) {
            SetPlayerState(self, 4, 0x24);
            SetPlayerCallback(self, FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x2D);
        }
    }
    if (self->state == 4) {
        f32 t = self->v150.z;
        f32 x = D_00275050[0] + t * (D_00275050[1] + t * D_00275050[2]);
        f32 lo = D_00275060[0];
        f32 hi = D_00275060[1];
        if (x < lo) {
            x = lo;
        } else if (hi < x) {
            x = hi;
        }
        f32 z = 0.0f;
        StartSoundEffect(0x49, 0, 0, 0, z, z, x, D_00275068[0], z, 0, 0);
    }
}

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void ContinuePlayerRequestKind6(Player* self)
{
    StartSoundEffect(0xA6, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    SetPlayerState(self, 4, 0x2A);
    SetPlayerCallback(self, ContinuePlayerSubState2A);
}

void ContinuePlayerSubState2A(Player* self)
{
    if (HasSpareCount()) {
        self->desc05()->m50(self);
    } else {
        SetPlayerState(self, 4, 0x2D);
    }
}

void ContinuePlayerRequestKind1Or2(Player* self)
{
    self->desc02()->m20(self, &self->savedVelocity);
    self->desc02()->m21(self, &self->savedSpin);
    if (HasSpareCount()) {
        self->desc05()->m50(self);
    } else {
        SetPlayerState(self, 4, 0x2D);
    }
}

struct PlayerWorld;
extern u32 g_buttonCodeFlags;

s32 IsPlayerRequestBlocked(Player* self, s32 n)
{
    s32 v;
    s32 k;
    if (n == 3 || n == 5) {
        switch (self->state) {
        case 4:
            switch (self->subState) {
            case 0x27:
            case 0x29:
            case 0x2C:
            case 0x2F:
            case 0x30:
                return 1;
            case 0x28:
            case 0x2A:
            case 0x2B:
            case 0x2D:
            case 0x2E:
            default:
                return 0;
            }
        case 6:
            k = self->targetMode;
            if (k != 3) { if (k != 6) return 1; }
            return 0;
        case 2:
            if (self->subState < 16) {
                if (!(self->subState < 9)) return 1;
            }
        case 5:
        default: {
            s32 r = 0;
            if (self->state == 11) goto set;
            if (IsPadSelectFlagHeld((World*)self->world) != 0) {
set:
                r = 1;
            }
            return r;
        }
        case 3:
        case 7:
        case 8:
            goto one;
        }
    }
    v = self->state;
    if (v == 4) goto one;
    if (v == 11) goto one;
    if (self->pulseActive != 0) goto one;
    if ((g_buttonCodeFlags & 1) != 0) goto one;
    if (IsPadSelectFlagHeld((World*)self->world) != 0) goto one;
    goto zero;
one:
    return 1;
zero:
    return 0;
}

void SetCrossfadeRatioDeep(PlacedObject* self, f32 value);
void SpendReserveUnit(void);

void EndPlayerRequestState(void* self)
{
    SetCrossfadeRatioDeep((PlacedObject*)self, 1.0f);
    SpendReserveUnit();
}

struct AnimRecord;
// A point of the ring in camera space and its angle about the centre.
struct __attribute__((aligned(16))) RingEntry {
    Vec02 pos;              // 0x00
    f32 angle;              // 0x10
    u8 pad14[0x20 - 0x14];
};

s32 CompareSortedTargets(RingEntry* a, RingEntry* b) { if (a->angle < b->angle) return -1; return 1; }


extern PacketWriter g_vifPacketWriter;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));
void* InitVertexBatch(VertexBatch* b);
void SetVertexBatchTransform(VertexBatch* batch, void* a1, void* a2);
void SetVertexBatchMode(VertexBatch* batch, u8* value);
void SetVertexTexCoord(VertexBatch* dst, U64P* src);
void SetVertexColor(VertexBatch* batch, void* src);
void SetVertexPosition(VertexBatch* body, Vec3* v);
void AddVertex(VertexBatch* b, s32 z);
void FlushVertexBatch(VertexBatch* b);
void DestroyVertexBatch(VertexBatch* b, s32 f);

// The ring around a set of anchors: the points projected into camera space, the lowest first,
// sorted by angle about it, the hull (a Graham scan against the z axis), the points where the
// hull crosses the centre's x, the angles about the centre, the gaps filled every D_0027506C
// radians, then the strip drawn once per texture with two rows of the three.
// `n - 1` is written at each use and never kept in a variable: the first sort's count and the
// gap loop's start are then two redundant occurrences of one expression, PRE gives them one
// reaching register, and its second life (beside n << 5 in s2) is what puts the first in s3.
// `base` is declared apart from its value: two more insns before GCSE, whose table then has
// retail's 323 buckets and numbers the four hoisted addresses in retail's spill-slot order
// (docs/toolchain/gcse.md, "One reaching register for every occurrence").
void DrawAngleSortedRing(Vec02* at, s32 nOffsets, Point2* offsets, s32 nAnchors, RingAnchor* anchors, RingParams* params, DeferredRequest* request)
{
    RingEntry entries[256];
    Vec02 pt;
    Vec02 center;
    f32 lowest = 3.4028235e+38f;
    RingEntry* low = 0;
    s32 n = 0;
    s32 i;
    s32 next;
    RingEntry* e;
    Vu0::Vec base;
    ProjectPointToCamera(g_camera, at, (f32*)&center);
    for (s32 j = 0; j < nAnchors; j++) {
        RingAnchor* anchor = &anchors[j];
        for (s32 k = 0; k < nOffsets; k++) {
            Point2* off = &offsets[k];
            f32 s = anchor->scale;
            u8* cam = (u8*)g_camera;
            base = Vu0::Vec::Of(anchor->obj->v140);
            Vu0::Vec sx = Vu0::Vec::Scalar(off->x * s);
            Vu0::Vec ax = Vu0::Vec::Of(*(Vec02*)(cam + 0x90));
            Vu0::Vec sy = Vu0::Vec::Scalar(off->y * s);
            Vu0::Vec ay = Vu0::Vec::Of(*(Vec02*)(cam + 0xA0));
            *(Vu0::Vec*)&pt = Vu0::MulAddX2(base, ax, sx, ay, sy);
            e = &entries[n];
            ProjectPointToCamera(g_camera, &pt, (f32*)e);
            n++;
            e->pos.z = center.z;
            if (e->pos.y < lowest) {
                lowest = e->pos.y;
                low = e;
            }
        }
    }
    {
        RingEntry t = *low;
        *low = entries[0];
        entries[0] = t;
    }
    for (s32 j = 1; j < n; j++) {
        Vec02 d;
        e = &entries[j];
        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(entries[0].pos));
        e->angle = ArctangentOfRatio(d.y, d.x);
    }
    SortElements(&entries[1], n - 1, 0x20, (s32 (*)(const void*, const void*))CompareSortedTargets);
    RingEntry* top = entries;
    for (i = 0; i < n;) {
        next = i + 1;
        e = &entries[i];
        while (top >= &entries[2]) {
            Vu0::Vec c = Vu0::Cross(Vu0::Sub(Vu0::Vec::Of(top[-1].pos), Vu0::Vec::Of(top[-2].pos)), Vu0::Vec::Of(g_unitZVector));
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(top[-2].pos)), c)) < 0.0f) {
                break;
            }
            top--;
        }
        *top = *e;
        top++;
        i = next;
    }
    n = top - entries;
    entries[n] = entries[0];
    Vec02 lo;
    Vec02 hi;
    lo = hi = center;
    for (i = n - 1; i >= 0; i--) {
        e = &entries[i];
        *(Vu0::Vec*)&lo = Vu0::Min(Vu0::Vec::Of(lo), Vu0::Vec::Of(e->pos));
        *(Vu0::Vec*)&hi = Vu0::Max(Vu0::Vec::Of(hi), Vu0::Vec::Of(e->pos));
    }
    *(Vu0::Vec*)&center = Vu0::MulXSum(Vu0::Vec::Of(lo), Vu0::Vec::Scalar(0.5f), Vu0::Vec::Of(hi), Vu0::Vec::Scalar(0.5f));
    for (i = n - 1; i >= 0; i--) {
        e = &entries[i];
        f32 x0 = e[0].pos.x;
        f32 x1 = e[1].pos.x;
        if ((x0 - center.x) * (x1 - center.x) < 0.0f) {
            f32 t = (center.x - x0) / (x1 - x0);
            Vu0::Vec s0 = Vu0::Vec::Scalar(1.0f - t);
            Vu0::Vec p0 = Vu0::Vec::Of(e[0].pos);
            Vu0::Vec s1 = Vu0::Vec::Scalar(t);
            Vu0::Vec p1 = Vu0::Vec::Of(e[1].pos);
            *(Vu0::Vec*)&entries[n++].pos = Vu0::MulXSum(p0, s0, p1, s1);
        }
    }
    for (i = n - 1; i >= 0; i--) {
        Vec02 d;
        e = &entries[i];
        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
        e->angle = WrapAngle(ArctangentOfRatio(d.y, d.x));
    }
    SortElements(entries, n, 0x20, (s32 (*)(const void*, const void*))CompareSortedTargets);
    entries[n] = entries[0];
    {
        Vu0::Vec prev = Vu0::Vec::Of(e[n].pos);
        f32 prevAngle = e[n].angle;
        for (i = n - 1; i >= 0;) {
            s32 down = i - 1;
            Vu0::Vec from;
            Vu0::Vec to;
            from = prev;
            to = Vu0::Vec::Of(entries[i].pos);
            prev = to;
            f32 a = prevAngle;
            prevAngle = entries[i].angle;
            s32 steps = (s32)(__builtin_fabsf(WrapAngle(a - prevAngle)) / D_0027506C);
            if (steps > 0) {
                for (i = 0; i < steps;) {
                    i++;
                    f32 t = (f32)i / (f32)(steps + 1);
                    Vec02 d;
                    e = &entries[n++];
                    *(Vu0::Vec*)&e->pos = Vu0::MulXSum(to, Vu0::Vec::Scalar(1.0f - t), from, Vu0::Vec::Scalar(t));
                    *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
                    e->angle = ArctangentOfRatio(d.y, d.x);
                }
            }
            i = down;
        }
    }
    SortElements(entries, n, 0x20, (s32 (*)(const void*, const void*))CompareSortedTargets);
    entries[n] = entries[0];
    VertexBatch batch;
    InitVertexBatch(&batch);
    BeginDmaTag(&g_vifPacketWriter);
    SetVertexBatchTransform(&batch, (u8*)&D_00248D30, (u8*)&g_identityMatrix);
    Vec02 rows[3];
    s32 r;
    for (r = 0; r < 3; r++) {
        rows[r] = *(Vec02*)&params->rows[r].shape;
        rows[r].x = rows[r].x / center.z;
        rows[r].z = rows[r].z * center.z;
    }
    for (s32 s = 0; s < 2; s++) {
        AnimRecord* tex = params->textures[s];
        if (tex == 0) {
            continue;
        }
        f32 prev = -3.1415927f;
        SetVertexBatchMode(&batch, (u8*)tex);
        f32 u0 = WrapModulo(g_gameClock.time * params->rate, 1.0f);
        for (i = 0; i <= n;) {
            Vec02 d;
            f32 uv[2];
            next = i + 1;
            e = &entries[i];
            *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(e->pos), Vu0::Vec::Of(center));
            f32 a = e->angle;
            while (a < prev) {
                a += 6.2831855f;
            }
            prev = a;
            switch (params->mode) {
            case 0:
            default:
                uv[0] = u0 + params->uScale * a * 0.15915494f;
                break;
            case 1:
                uv[0] = u0 + params->uScale * __builtin_fabsf(WrapAngle(a - 1.5707964f)) * 0.15915494f;
                break;
            }
            for (r = s; r <= s + 1; r++) {
                uv[1] = params->rows[r].v;
                f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(d)));
                Vu0::Vec w = Vu0::Vec::Scalar(((rows + r)->x + len * ((rows + r)->y + len * (rows + r)->z)) / len);
                *(Vu0::Vec*)&pt = Vu0::MulAddX2(Vu0::Vec::Of(center), Vu0::Vec::Of(d), w, Vu0::Vec::Of(g_unitZVector), Vu0::Vec::ScalarAtValue(params->rows[r].lift));
                UnprojectCameraPoint(g_camera, (f32*)&pt, &pt);
                SetVertexTexCoord(&batch, (U64P*)uv);
                Rgba4 c = *(Rgba4*)&params->rows[r].color;
                SetVertexColor(&batch, &c);
                SetVertexPosition(&batch, (Vec3*)&pt);
                AddVertex(&batch, 0);
            }
            i = next;
        }
        FlushVertexBatch(&batch);
    }
    CloseDmaTag(&g_vifPacketWriter);
    DestroyVertexBatch(&batch, 2);
}



// The three rings each keep their parameter block as a function-local static with a brace
// initialiser (include/ring_params.h); the textures are looked up at every call. Each is a
// deferred request's callback (QueuePlayerMarkerRingDraw), the player the request's argument.
void DrawPlayerMarkerRing1(DeferredRequest* request)
{
    Player* player = (Player*)request->arg;
    static RingParams params = {
        0, 5.0f, 1.0f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RingColor(0x00000000) },
            { { 0.0f, 1.0f, 0.0f }, 0.5f, -100.0f, RingColor(0xFFFFFFFF) },
            { { 75.0f, 1.0f, 0.0f }, 1.0f, 0.0f, RingColor(0xFFFFFFFF) },
        },
    };
    params.textures[0] = 0;
    params.textures[1] = FindAnimRecord(0x15C);
    DrawAngleSortedRing(&player->v140, 7, (Point2*)g_ringSevenPoints, player->ringCount, (RingAnchor*)player->ringAnchors, &params, request);
}

void DrawPlayerMarkerRing2(DeferredRequest* request)
{
    Player* player = (Player*)request->arg;
    static RingParams params = {
        1, 5.0f, 0.5f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 100.0f, RingColor(0x80FFFFFF) },
            { { 0.0f, 0.5f, 0.0f }, 0.0f, 50.0f, RingColor(0x80FFFFFF) },
            { { 75.0f, 1.0f, 0.0f }, 1.0f, -100.0f, RingColor(0x80FFFFFF) },
        },
    };
    AnimRecord* texture = FindAnimRecord(0x15D);
    params.textures[1] = texture;
    params.textures[0] = texture;
    DrawAngleSortedRing(&player->v140, 7, (Point2*)g_ringSevenPoints, player->ringCount, (RingAnchor*)player->ringAnchors, &params, request);
}

void DrawPlayerMarkerRing3(DeferredRequest* request)
{
    Player* player = (Player*)request->arg;
    static RingParams params = {
        0, 5.0f, 1.0f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RingColor(0x00000000) },
            { { 0.0f, 1.0f, 0.0f }, 0.5f, -100.0f, RingColor(0xFFFFFFFF) },
            { { 25.0f, 1.0f, 0.0f }, 1.0f, 0.0f, RingColor(0xFFFFFFFF) },
        },
    };
    RingAnchor anchor;
    params.textures[0] = 0;
    params.textures[1] = FindAnimRecord(0x15C);
    anchor.scale = 60.0f;
    anchor.obj = (PlacedObject*)player;
    DrawAngleSortedRing(&player->v140, 0x11, (Point2*)g_ringSeventeenPoints, 1, &anchor, &params, request);
}

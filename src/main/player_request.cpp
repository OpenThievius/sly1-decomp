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
#include "c8b.h"
#include "vu0.h"

s32 D_00274FA0[2] = {286, 287};
s32 D_00274FA8[2] = {288, 289};
s32 D_00274FB0[2] = {2, 2};
s32 D_00274FB8[2] = {48, 64};

struct PlayerTableEntry { s32 id; f32 v; s32 object; };
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
float D_00275070[14] = {0.0f, 1.0f, 0.781831503f, 0.623489797f, 0.974927902f, -0.222520933f, 0.433883727f, -0.90096885f, -0.433883727f, -0.90096885f, -0.974927902f, -0.222520933f, -0.781831503f, 0.623489797f};
float D_002750A8[34] = {1.0f, 0.0f, 0.932472229f, 0.361241668f, 0.739008904f, 0.673695624f, 0.445738345f, 0.895163298f, 0.0922683626f, 0.995734155f, -0.273662984f, 0.961825669f, -0.602634609f, 0.798017204f, -0.850217164f, 0.526432157f, -0.982973099f, 0.183749512f, -0.982973099f, -0.183749512f, -0.850217164f, -0.526432157f, -0.602634609f, -0.798017204f, -0.273662984f, -0.961825669f, 0.0922683626f, -0.995734155f, 0.445738345f, -0.895163298f, 0.739008904f, -0.673695624f, 0.932472229f, -0.361241668f};
s32 D_00275130 = 0;
s32 D_00275134 = 0;
s32 D_00275138 = 0;

// The eight blend slots func_001D4148 fills (0x20 bytes each), the weight of slot 6 first.
struct BlendSlotObject;
struct BlendSlot {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10: where the object's mover puts it
};

typedef void (*SlotMoveFn)(Mover8B* m, void* body, f32 x, f32 y, s32 z, Vec02* out, Vec02* out2);
struct SlotMover { SlotMoveFn* vtbl; };
struct SlotMoverHolder { u8 pad00[4]; SlotMover* mover; };
struct BlendSlotObject {
    u8 pad00[0x34];
    f32 f34;                // 0x34
    u8 pad38[0x9C - 0x38];
    SlotMoverHolder* holder; // 0x9C
};

Entry8B* FindEntryByObjectId(void* object, void* body);
void BuildCombinedBlendAnimation(TurningCollider* self, s32 stride, s32 count, BlendSlot* slots, s32 a, s32 b, s32 c, Gr8B** gr);

struct PlayerBlendItem {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    f32 f30;                // 0x30
    u8 pad34[0x40 - 0x34];
    f32 f40;                // 0x40
    u8 pad44[0x50 - 0x44];
};
struct PlayerBlendCurve { u8 pad00[0x10]; void* f10; };

void ComputeWrappedDeltas(s32 stride, s32 count, u8* base, s32 off, s32 count2, s32* vals);
void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);

void func_001D36F0(TurningCollider* self, PlayerBlendItem* items, Gr8B** out)
{
    Vec02 a0;
    Vec02 a10;
    Gr8B* blend;
    s32 i;

    if (items[0].object == 0) {
        *out = 0;
        return;
    }
    items[0].weight = 1.0f;
    ComputeWrappedDeltas(0x50, 6, (u8*)items, 0x30, 2, D_00274FA0);
    ComputeWrappedDeltas(0x50, 6, (u8*)items, 0x40, 2, D_00274FA8);
    for (i = 0; i < 6; i++) {
        PlayerBlendItem* it = &items[i];
        BlendSlotObject* o = it->object;
        if (o != 0) {
            f32 one = 1.0f;
            SlotMover* m = o->holder->mover;
            (*m->vtbl)((Mover8B*)m, self, 0.0f, one, 0, &a0, 0);
            m = o->holder->mover;
            (*m->vtbl)((Mover8B*)m, self, o->f34, one, 0, &a10, 0);
            *(Vu0::Vec*)&it->v10 = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(a0), Vu0::Vec::Of(a10)), Vu0::Vec::ScalarAt(o->f34));
            Vec02 a20;
            m = (SlotMover*)FindEntryByObjectId(it->object, self->f610)->mover;
            (*m->vtbl)((Mover8B*)m, self->f610, it->f30, one, 0, &a20, 0);
            Vec02 a30;
            m = (SlotMover*)FindEntryByObjectId(it->object, self->f614)->mover;
            (*m->vtbl)((Mover8B*)m, self->f614, it->f40, one, 0, &a30, 0);
            Vu0::Vec h = Vu0::Vec::Scalar(0.5f);
            *(Vu0::Vec*)&it->v20 = Vu0::MulXSum(Vu0::Vec::Of(a20), h, Vu0::Vec::Of(a30), h);
        }
    }
    BuildCombinedBlendAnimation((TurningCollider*)self, 0x50, 6, (BlendSlot*)items, 2, (s32)D_00274FB8, (s32)D_00274FB0, &blend);
    for (s32 j = 0; j < blend->f38; j++) {
        Entry8B* e = (Entry8B*)(blend->f3C + j * 0x1C);
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

void func_001D39E0(s32 n, WeightedRow* rows, f32* scale, Vec02* out)
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
s32 FindNearestSpanObject(void* a, Vec02* from, Vec02* to, s32 count, Collider** list, void* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, s32 c, s32 d, s32* count, Collider*** list);

s32 func_001D3B58(PlacedObject* self, Vec02* from, Vec02* to, f32* ratio)
{
    Vec02 a;
    Vec02 b;
    ColliderSpan hit;
    s32 count;
    Collider** list;
    a = *from;
    b = *to;
    PushBackMemoryMark();
    GatherCollidersInBox(self->world, self, &a, &b, 0, 0, &count, &list);
    s32 found = FindNearestSpanObject(0, &a, &b, count, list, &hit);
    *ratio = found != 0 ? Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(hit.q[0]), Vu0::Q(a)))) / Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(b)))) : 1.0f;
    PopBackMemoryMark();
    return found != 0;
}

f32 func_001FD578(u64 v);

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
        rows[i] = func_001FD578(ap[-1]);
        sum += rows[i];
    }
    rows[0] = 1.0f - sum;
    sum = 0.0f;
    for (j = 1; j < m; j++) {
        ap++;
        cols[j] = func_001FD578(ap[-1]);
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

u64 func_001FD868(f32 x);
s32 FindObjectAlongSegment(void* p, void* a, void* b, void* out);

struct BlendSpan { f32 t; u8 pad4[8]; f32 len; };
struct BlendSpans { u8 pad0[8]; BlendSpan* a; u8 padC[8]; BlendSpan* b; };

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))

void InterpolateBlendEntryPosition(void* p, void* e, f32 a, f32 b, s32 i, s32 j, void* out);
void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);
void SumBlendEntryVectors(s32 a0, void* a1, s32 a2, void* a3);

void func_001D3E00(TurningCollider* p, void* e, Gr8B* g, void* a3)
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
        if (FindObjectAlongSegment(p, &va, &vb, &vc)) {
            lo = 0.0f;
            hi = 1.0f - vc.x;
        } else if (W(e, 0x144) != 0) {
            InterpolateBlendEntryPosition(p, e, lo, t, 4, 5, &vd);
            if (FindObjectAlongSegment(p, &vb, &vd, &vc)) {
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
    u64 hv = func_001FD868(hi);
    u64 lv = func_001FD868(lo);
    u64 tv = func_001FD868(t);
    if (FillOuterProductTable(0x50, 3, 2, (char*)e, hv, lv, tv)) {
        SetBlendItemWeights(g, 0x50, 6, e);
        SumBlendEntryVectors(6, e, (s32)g->pC0->p8, (u8*)p + 0x640);
    }
}

#undef F
#undef W

// The six blend records func_001D40A0 hands to func_001399F8 (0x50 bytes each): the weight
// of each at its start; the second record's word at +4 says whether it blends at all.
struct TurnBlendRecords {
    f32 f0;
    u8 pad4[0x4C];
    f32 f50;
    s32 f54;
    u8 pad58[0x48];
    s32 fA0;
    u8 padA4[0x4C];
    s32 fF0;
    u8 padF4[0x4C];
    s32 f140;
    u8 pad144[0x4C];
    s32 f190;
};

void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);
void SumBlendEntryVectors(s32 a0, void* a1, s32 a2, void* a3);

void SetPlayerBlendWeights(TurningCollider* a0, TurnBlendRecords* a1, Gr8B* a2, f32 f12, f32 f13)
{
    a0->f638 = f12;
    if (a1->f54 == 0) {
        a1->f0 = 1.0f;
        a1->f50 = 0.0f;
    } else {
        f32 one = 1.0f;
        a1->f50 = f13;
        a1->f0 = one - f13;
    }
    a1->fA0 = 0;
    a1->f140 = 0;
    a1->fF0 = 0;
    a1->f190 = 0;
    SetBlendItemWeights(a2, 0x50, 6, a1);
    SumBlendEntryVectors(6, a1, (s32)a2->pC0->p8, &a0->f640);
}

void func_001D4148(TurningCollider* self, BlendSlot* slots, Gr8B** gr)
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
            (*m->vtbl)((Mover8B*)m, self, 0.0f, 1.0f, 0, &here, 0);
            m = o->holder->mover;
            (*m->vtbl)((Mover8B*)m, self, o->f34, 1.0f, 0, &there, 0);
            Vu0::Q(delta) = Vu0::Sub(Vu0::Q(there), Vu0::Q(here));
            Vu0::Q(k) = Vu0::FromFloat(-1.0f / o->f34);
            Vu0::Q(e->v10) = Vu0::MulX(Vu0::Q(delta), Vu0::Q(k));
        } else {
            switch (i) {
            case 0:
            case 2:
            case 4:
            case 6: {
                SlotMover* m = (SlotMover*)FindEntryByObjectId(e->object, self->f610)->mover;
                (*m->vtbl)((Mover8B*)m, self->f610, 0.0f, 1.0f, 0, 0, &e->v10);
                break;
            }
            case 1:
            case 3:
            case 5:
            case 7: {
                SlotMover* m = (SlotMover*)FindEntryByObjectId(e->object, self->f614)->mover;
                (*m->vtbl)((Mover8B*)m, self->f614, 0.0f, 1.0f, 0, 0, &e->v10);
                break;
            }
            }
        }
    }
    BuildCombinedBlendAnimation(self, 0x20, 8, slots, 0, 0, 0, gr);
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
    f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->v640), v));
    f32 first = along / length;
    zero = 0.0f;
    u128 v2 = Vu0::Q(slots[o + 2].v10);
    f32 length2 = scale * Vu0::ToFloatMoved(Vu0::Dot(v2, v2));
    u128 v4 = Vu0::Q(slots[o + 4].v10);
    f32 length4 = scale * Vu0::ToFloatMoved(Vu0::Dot(v4, v4));
    f32 w0 = first >? zero;
    slots[o + 0].weight = w0;
    f32 second = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), v2)) / length2;
    f32 w2 = second >? zero;
    slots[o + 2].weight = w2;
    f32 w4 = (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[o + 4].v10))) / length4) >? zero;
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

void func_001D4348(Player* self, BlendSlot* slots, Gr8B* gr)
{
    Vec02 acc;
    f32 scale = *(f32*)((u8*)self->watched2230 + 0x18);
    s32 i;
    if (self->fA14 == -1) {
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[0].v10))) < 0.0f)
            self->fA14 = 1;
        else
            self->fA14 = 0;
    }
    for (i = 0; i < 8; i++)
        slots[i].weight = 0.0f;
    switch (self->fA14) {
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
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(acc), Vu0::Scalar(scale));
    SetBlendItemWeights(gr, 0x20, 8, slots);
}
static inline f32 MinF(f32 a, f32 b) { return b <? a; }
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }
void ComputePolarOffset(Vec02* out, f32 angle, f32 radius, f32 z);

// The velocity of a heading and speed, from six axes of the basis: forward (y) by the
// heading's length ahead, and right or left by its side (x), the set picked by the walk mode.
void SetPlayerVelocityFromHeading(Player* self, const Vec02* basis, f32 heading, f32 speed)
{
    Vec02 h;
    ComputePolarOffset(&h, heading - self->f638, speed, 0.0f);
    f32 m;
    if (10.0f < h.y) {
        if (self->fA14 == 0) {
            h.y = 0.0f;
            m = 0.0f;
        } else {
            m = 1.0f;
        }
    } else if (h.y < -10.0f) {
        if (self->fA14 == 1) {
            h.y = 0.0f;
            m = 1.0f;
        } else {
            m = 0.0f;
        }
    } else if (self->fA14 == -1) {
        m = 0.0f;
    } else {
        m = (f32)self->fA14;
    }
    if (m == 1.0f) {
        u128 s = Vu0::Scalar(h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[3]), s, Vu0::Q(basis[7]), t, Vu0::Q(basis[11]), u);
    } else {
        u128 s = Vu0::Scalar(-h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[1]), s, Vu0::Q(basis[5]), t, Vu0::Q(basis[9]), u);
    }
    self->v640.z = 0.0f;
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(self->v640), Vu0::ScalarAt(*(f32*)((u8*)self->watched2230 + 0x18)));
}



u8* CopyToFrontMemory(s32 size, void* src);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

void ResolvePlayerTableObjects(Player* self)
{
    self->f26A8 = 7;
    self->f26AC = CopyToFrontMemory(0x54, g_playerObjectTable);
    for (s32 i = 0; i < self->f26A8; i++) {
        PlayerTableEntry* it = (PlayerTableEntry*)self->f26AC + i;
        it->object = FindFirstObjectById(self->world, 1, it->id, self);
    }
}


void AddColliderForce(Collider* self, Vec02* force);
void SteerColliderTowardPosition(Collider* self, void* a, void* b, const Vec02* target, const f32* ramp, f32 dt);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* from, f32* to);

void func_001D48E8(Player* self)
{
    Vec02 force;
    switch (self->f2228) {
    case 0x25:
    case 0x26: {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(k));
        AddColliderForce(self, &force);
        SteerColliderTowardPosition(self, 0, 0, &D_00248D30, D_00275020, g_gameClock.dt);
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
        if (self->v640.z != zero)
            aim.z = self->v150.z;
        SteerColliderTowardPosition(self, 0, 0, &aim, D_00275020, g_gameClock.dt);
        if (self->v640.z != zero) {
            force = D_00248D30;
            force.z = (-self->v640.z - aim.z) / g_gameClock.dt;
            AddColliderForce(self, &force);
        }
        break;
    }
    case 0x27: // the states that apply no force of their own
        break;
    case 0x2A:
        break;
    }
    TurnColliderTowardRotation(self, g_gameClock.dt, &self->m660, &self->f6E0);
}

f32 ArctangentOfRatio(f32 a, f32 b);
f32 ApproachAngleWithRamp(f32* p, s32 a, f32 b, f32 c, f32 d);
s32 IsObjectOfKind(void* e, s32 k);
void RunPlayerCallback(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);
s32 ChoosePlayerTargetByCost(Player* self, void* b);
void ComputeTargetArc(Player* self, void* s2, f32 f, void* a2, void* a3, void* a4);

void UpdatePlayerRequestSubState(Player* self) {
    switch (self->f2228) {
    case 0x2B: {
        f32 t = ArctangentOfRatio(self->v150.y, self->v150.x);
        self->f638 = ApproachAngleWithRamp(D_00275030, 0, self->f638, t + 3.1415927f, g_gameClock.dt);
        if (0.25f < g_gameClock.time - self->f222C && self->f690 != 0) {

            RunPlayerCallback(self);
        }
        break;
    }
    case 0x2C: {
        if (*(f32*)((u8*)self->f2514 + 0x18) < g_gameClock.time) {
            RunPlayerCallback(self);
        } else if (self->f2B70 != 0 && *(f32*)((u8*)self->f2514 + 0x18) < g_gameClock.time + 0.25f &&
                   (IsObjectOfKind(self->f2B70, 0x76) || IsObjectOfKind(self->f2B70, 0x70) ||
                    IsObjectOfKind(self->f2B70, 0x71) || IsObjectOfKind(self->f2B70, 0x81) ||
                    IsObjectOfKind(self->f2B70, 0x6F) || IsObjectOfKind(self->f2B70, 0x7F))) {
            if (self->f26B0 != 0) {
                RunPlayerCallback(self);
            } else {
                void* o = self->f2B70;
                SetPlayerState(self, 2, 2);
                s32 r = ChoosePlayerTargetByCost(self, o);
                SetPlayerState(self, 2, r);
            }
        } else {
            ComputeTargetArc(self, &self->f2B70, *(f32*)((u8*)self->f2514 + 0x18) - g_gameClock.time, 0, (u8*)self->f2514 + 0x20, 0);
        }
        break;
    }
    }
}

void SetPlayerCallback(Player* self, s32 value)
{
    self->f26B0 = value;
}

extern void EndPlayerRequestState(Player* self);
extern void SetPlayerState(Player* self, s32 mode, s32 count);

void RunPlayerCallback(Player* self)
{
    s32 v = self->f2254;
    void (*fn)(Player* self) = self->cb26B0;

    v &= -0x11;
    self->cb26B0 = 0;

    self->f2254 = v;
    if (fn != 0) {
        fn(self);
        return;
    }
    if ((u32)(self->f2228 - 0x2D) < 5) {
        EndPlayerRequestState(self);
    } else {
        SetPlayerState(self, 2, 2);
    }
}

void ContinuePlayerRequestKind0(Player* self);
void ContinuePlayerRequestKind6(Player* self);
void ContinuePlayerSubState2A(Player* self);
void ContinuePlayerRequestKind1Or2(Player* self);
void FinishPlayerRequest(void);

typedef void (*PlayerRequestFn)(s32 data, Player* self);
struct PlayerRequestMessage { Player* self; s32 v; };

void TriggerScriptEvent(s32 target, s32 a, s32 b, Ev07** c);
void SetPlayerState(Player* self, s32 a, s32 b);
void SetPlayerCallback(Player* self, s32 value);
s32 IsPadSelectFlagHeld(s32 p);
s32 MaskWorldBitsBySave(void);
s32 HasSpareCount(void);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u32 g_buttonCodeFlags;
extern f32 g_gameTime[];

s32 AcceptPlayerRequest(Player* self, Ev07* msg)
{
    if (self->desc05()->m4B(self, msg->kind) != 0) {
        return 0;
    }
    if (self->f2220 == 6 && self->f239C == 2) {
        Ev07* tmp = msg;
        TriggerScriptEvent((s32)self->heldObject, 0x13, 1, &tmp);
        SetPlayerState(self, 2, 5);
        return 0;
    }
    self->f26B4 = *msg;
    if (self->f2220 != 4 && self->f2220 != 0xB && self->f26C4 == 0 && (g_buttonCodeFlags & 1) == 0 &&
        IsPadSelectFlagHeld((s32)self->world) == 0) {
        s32 c;
        switch (self->f26B4.kind) {
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
                self->f26C4 = 1;
                self->f26C8 = g_gameTime[0];
            }
        }
    }
    SetPlayerCallback(self, 0);
    switch (msg->kind) {
    case 0:
        StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->f26B4.fn;
            if (fn != 0) {
                self->f26B4.fn = 0;
                fn(self->f26B4.data, self);
            } else {
                SetPlayerState(self, 4, 0x2B);
            }
        }
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind0);
        break;
    case 6:
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->f26B4.fn;
            if (fn != 0) {
                self->f26B4.fn = 0;
                fn(self->f26B4.data, self);
            } else {
                SetPlayerState(self, 4, 0x2B);
            }
        }
        if (400.0f < self->v150.z) {
            StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind6);
        break;
    case 1:
    case 2: {
        s32 id;
        if (self->f2220 == 0xD) {
            (*(Quad16*)&self->v2BB0) = (*(Quad16*)&self->v2BC0) = *(const Quad16*)&D_00248D30;
        } else {
            (*(Quad16*)&self->v2BB0) = (*(Quad16*)&self->v150);
            (*(Quad16*)&self->v2BC0) = (*(Quad16*)&self->v160);
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
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind1Or2);
        break;
    }
    case 3:
        if (self->f2730 == 0 || HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x27);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x2F);
        }
        break;
    case 4:
        self->desc02()->m20(self, (Vec02*)D_00275040);
        if (HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x28);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x31);
        }
        break;
    case 5:
        if (self->f2730 == 0 || HasSpareCount() != 0) {
            SetPlayerState(self, 4, 0x29);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
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
void FinishSwitchedCollider(Player* o);
void SetPlayerState(Player* o, s32 a, s32 b);
s32 ChoosePlayerTargetByCost(Player* o, void* p);
void SetPlayerCallback(Player* o, s32 value);
void FinishPlayerRequest(void);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void ContinuePlayerRequestKind0(Player* self)
{
    if (self->f2228 == 0x2C && self->f2B70 != 0 &&
        (IsObjectOfKind(self->f2B70, 0x70) || IsObjectOfKind(self->f2B70, 0x71) ||
         IsObjectOfKind(self->f2B70, 0x81) || IsObjectOfKind(self->f2B70, 0x6F) ||
         IsObjectOfKind(self->f2B70, 0x7F) || IsObjectOfKind(self->f2B70, 0x76))) {
        if (HasSpareCount()) {
            FinishSwitchedCollider(self);
            void* p = self->f2B70;
            SetPlayerState(self, 2, 2);
            SetPlayerState(self, 2, ChoosePlayerTargetByCost(self, p));
        } else {
            SetPlayerState(self, 4, 0x2D);
        }
    } else {
        if (HasSpareCount()) {
            SetPlayerState(self, 4, 0x24);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            SetPlayerState(self, 4, 0x2D);
        }
    }
    if (self->f2220 == 4) {
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

void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void ContinuePlayerRequestKind6(Player* self)
{
    StartSoundEffect(0xA6, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    SetPlayerState(self, 4, 0x2A);
    SetPlayerCallback(self, (s32)ContinuePlayerSubState2A);
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
    self->desc02()->m20(self, &self->v2BB0);
    self->desc02()->m21(self, &self->v2BC0);
    if (HasSpareCount()) {
        self->desc05()->m50(self);
    } else {
        SetPlayerState(self, 4, 0x2D);
    }
}

struct PlayerWorld;
s32 IsPadSelectFlagHeld(PlayerWorld* k);
extern u32 g_buttonCodeFlags;

s32 IsPlayerRequestBlocked(Player* self, s32 n)
{
    s32 v;
    s32 k;
    if (n == 3 || n == 5) {
        switch (self->f2220) {
        case 4:
            switch (self->f2228) {
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
            k = self->f239C;
            if (k != 3) { if (k != 6) return 1; }
            return 0;
        case 2:
            if (self->f2228 < 16) {
                if (!(self->f2228 < 9)) return 1;
            }
        case 5:
        default: {
            s32 r = 0;
            if (self->f2220 == 11) goto set;
            if (IsPadSelectFlagHeld((PlayerWorld*)self->world) != 0) {
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
    v = self->f2220;
    if (v == 4) goto one;
    if (v == 11) goto one;
    if (self->f26C4 != 0) goto one;
    if ((g_buttonCodeFlags & 1) != 0) goto one;
    if (IsPadSelectFlagHeld((PlayerWorld*)self->world) != 0) goto one;
    goto zero;
one:
    return 1;
zero:
    return 0;
}

void SetCrossfadeRatioDeep(void* self, f32 value);
void SpendReserveUnit(void);

void EndPlayerRequestState(void* self)
{
    SetCrossfadeRatioDeep(self, 1.0f);
    SpendReserveUnit();
}

struct SortedTarget { u8 pad[0x10]; f32 key; };
s32 CompareSortedTargets(SortedTarget* a, SortedTarget* b) { if (a->key < b->key) return -1; return 1; }


extern const f32 D_0024DC88 = 3.4028235e38f;
INCLUDE_ASM(func_001D5678);


INCLUDE_ASM(func_001D5FA8);
INCLUDE_ASM(func_001D60B0);
INCLUDE_ASM(func_001D61C8);

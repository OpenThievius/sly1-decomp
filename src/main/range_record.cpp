// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "path_curve_object.h"
#include "world.h"
#include "packet_writer.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "asm_func.h"

void InvalidateRangeRecordPacket(RangeRecord* o);
void FillMemory(void* p, s32 v, s32 n);
extern s32 g_meshQueueCount;
extern u8 D_0027DC20[];
void LinkRangeRecord(RangeRecord* self, s32 code);
s32 HasRangeRecordRanges(RangeRecord* self);
void StoreRangeRecordNear(RangeRecord* self, f32 v);
void StoreRangeRecordFar(RangeRecord* self, f32 v);
AnimRecord* FindAnimRecord(s32 key);
void UpdateRangeRecordBounds(RangeRecord* o);
s32 ReadBufferedU8(void* src);
PathCurve* CreatePathCurve(s32 kind);
void ReadPropertyRecords(void* self, void* obj);
void BuildRangeRecordPacket(void* o);
s32 RangeRecordReachesSphere(RangeRecord* node, void* a1, f32 f);
f32 Tangent(RangeRecord* o, f32 s);
extern u8 D_00248400[];
void BuildMatrixFromRotationAndTranslation(void* a, void* b, Mat4A* dst);
void ReparentObject(BaseObject* self, void* other);

// The file's .data, in retail's order.
f32 D_002744F0 = 50.0f;

ASM_FUNC(func_001B1AC8);

void PrepareRangeRecord(RangeRecord* self)
{
    if (self->link == 0) {
        LinkRangeRecord(self, 0x2C);
    }
    if (HasRangeRecordRanges(self) == 0) {
        StoreRangeRecordNear(self, 100.0f);
        StoreRangeRecordFar(self, 400.0f);
    }
    if ((self->link->maskC & 0x10000000) == 0) {
        s32 idx = g_meshQueueCount;
        if (idx < 0x4000) {
            u8* p = D_0027DC20 + idx * 16;
            self->f2D0 = p;
            g_meshQueueCount = idx + 1;
            FillMemory(p, 0, 16);
        }
    }
}

void InvalidateRangeRecordPacket(RangeRecord* self)
{
    self->fC0 = 0;
}

ASM_FUNC(func_001B1BF8);

void LinkRangeRecord(RangeRecord* self, s32 key)
{
    AnimRecord* found = FindAnimRecord(key != -1 ? key : 0x2C);
    self->link = found;
    if (found)
        InvalidateRangeRecordPacket(self);
}

s32 HasRangeRecordRanges(RangeRecord* p)
{
    s32 r = 0;
    if (0.0f <= p->f04 && 0.0f <= p->f08)
        r = 1;
    return r;
}

void StoreRangeRecordNear(RangeRecord* p, f32 v)
{
    p->f04 = v;
    if (p->f08 < 0.0f)
        p->f08 = v;
    InvalidateRangeRecordPacket(p);
}

void StoreRangeRecordFar(RangeRecord* o, f32 v)
{
    o->f08 = v;
    if (o->f04 < 0.0f) {
        o->f04 = v;
    }
    InvalidateRangeRecordPacket(o);
}

ASM_FUNC(func_001B1DE0);

ASM_FUNC(func_001B1EC8);

void StoreRangeRecordInner(RangeRecord* o, f32 v)
{
    o->f40 = v;
    UpdateRangeRecordBounds(o);
    InvalidateRangeRecordPacket(o);
}

void StoreRangeRecordOuter(RangeRecord* o, f32 v)
{
    o->f44 = v;
    UpdateRangeRecordBounds(o);
    InvalidateRangeRecordPacket(o);
}

void ScaleRangeRecordByAngle(RangeRecord* o, f32 s) {
    f32 t = Tangent(o, s * 0.00872664712f);
    o->f04 = t * o->f40;
    o->f08 = t * o->f44;
    InvalidateRangeRecordPacket(o);
}

void StoreRangeRecordVector(RangeRecord* self, Quad16* src)
{
    *(Quad16*)((u8*)self + 0x30) = *src;
    InvalidateRangeRecordPacket(self);
}

s32 RangeRecordMatchesKinds(RangeRecord* self, u32 bits)
{
    s32 r = 0;
    if (self->link != 0) {
        u32 flags = self->link->maskC;
        Camera* g = g_camera;
        u32 mask = g->f21C;
        s32 ok = 0;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            ok = 1;
        }
        if (ok != 0) {
            if (((bits & 1) != 0 && self->link->kind == 2) || ((bits & 2) != 0 && self->link->kind == 3)) {
                r = 1;
            }
        }
    }
    return r;
}

s32 IsRangeRecordBodyCandidate(void* unused, Collider* o)
{
    s32 r = 0;
    if ((o->flags538 & (1UL << 43)) == 0) {
        r = o->faceStarts != 0;
    }
    return r;
}

ASM_FUNC(func_001B2140);

// The literals func_001B2358 loads.
extern const f32 D_0024D164 = -3.40282347e+38f;
extern const f32 D_0024D168 = 3.40282347e+38f;

ASM_FUNC(func_001B2358);

void QueueRangeRecordPacket(RangeRecord* o)
{
    if (o->link != 0) {
        Camera* c = g_camera;
        s32 bits = o->link->maskC;
        s32 need = c->f21C;
        s32 a2 = 0;
        if ((bits & 0x10000000) != 0) {
            goto set;
        }
        if ((need & bits) != need) {
            goto skip;
        }
    set:
        a2 = 1;
    skip:
        if (a2 != 0) {
            if (o->fC0 == 0) {
                BuildRangeRecordPacket(o);
                if (o->fC0 == 0) {
                    goto done;
                }
            }
            PacketWriter* g = &g_vifPacketWriter;
            u64 hi = (u64)(u32)((u8*)o + 0xD0) << 32;
            u64 v = (u64)(s64)(o->fC0 | 0x40000000) | hi;
            *(u64*)g->cur = v;
            g->cur = g->cur + 0x10;
        }
    }
done:
    ;
}

ASM_FUNC(func_001B26F8);

void CollectRangeRecordsInReach(World* self, void* a1, s32 max, s32* outCount, RangeRecord** out, f32 f)
{
    ListFrame frame;
    s32 count = 0;
    RangeRecord* node;
    for (node = (RangeRecord*)self->list1C00.head; node != 0; node = node->next) {
        if (RangeRecordReachesSphere(node, a1, f) == 0) {
            continue;
        }
        if (count < max) {
            *out = node;
            out++;
            count++;
        } else {
            break;
        }
    }
    *outCount = count;
}

void LoadPathCurveObject(PathCurveObject* self, void* obj)
{
    PathCurve* p = CreatePathCurve(ReadBufferedU8(obj));
    self->curve = p;
    void (*fn)(PathCurve* self, void* stream) = p->vt->m00;
    if (fn != 0) {
        fn(p, obj);
    }
    ReadPropertyRecords(self, obj);
}

void ReparentPathCurveObject(PathCurveObject* self, BaseObject* other)
{
    Mat4A a;
    Mat4A b;
    PathCurve* h;
    if (self->parent) {
        BuildMatrixFromRotationAndTranslation((u8*)self->parent + 0x140, (u8*)self->parent + 0x110, &a);
    } else {
        a = *(Mat4A*)D_00248400;
    }
    if (other) {
        BuildMatrixFromRotationAndTranslation((u8*)other + 0x140, (u8*)other + 0x110, &b);
    } else {
        b = *(Mat4A*)D_00248400;
    }
    h = self->curve;
    if (h->vt->m04) {
        h->vt->m04(h, &a, &b);
    }
    ReparentObject(self, other);
}

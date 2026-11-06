// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c6e.h"
#include "world.h"
#include "v24a0.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "asm_func.h"

void func_001B1BF0(RangeRecord* o);
struct Obj_1B2118 {
    u8 pad_0[0x410];
    u32 f410;
    u8 pad_414[0x538 - 0x414];
    u64 f538;
};
void func_001F5C0C(void* p, s32 v, s32 n);
extern s32 D_002626D0;
extern u8 D_0027DC20[];
void func_001B1CF8(RangeRecord* self, s32 code);
s32 func_001B1D38(RangeRecord* self);
void func_001B1D70(RangeRecord* self, f32 v);
void func_001B1DA8(RangeRecord* self, f32 v);
struct Hdr_1B1B38 {
    u8 pad0[0xC];
    s32 f0C;
};
void* func_001B4688(s32 key);
void func_001B1BF8(RangeRecord* o);
s32 func_00137B90(void* src);
T2176* func_0014D9A8(s32 kind);
void func_0011EC40(void* self, void* obj);
struct Sub_1B2640 {
    u8 pad0[0xC];
    s32 f0C;
};
struct Obj_1B2640 {
    Sub_1B2640* f0;
    u8 pad4[0xBC];
    s32 fC0;
    u8 padC4[0xC];
};
void func_001B2358(void* o);
struct Node_1B2790;
struct Node_1B2790 { u8 pad[0xB8]; Node_1B2790* next; };
s32 func_001B26F8(Node_1B2790* node, void* a1, f32 f);
struct Obj_1B2090 {
    u8 kind_0;
    u8 pad_1[0xB];
    u32 flags_C;
};
f32 func_002054F0(RangeRecord* o, f32 s);
extern u8 D_00248400[];
void func_00188B08(void* a, void* b, Mat4A* dst);
void func_00182F78(BaseObject* self, void* other);

// The file's .data, in retail's order.
f32 D_002744F0 = 50.0f;

ASM_FUNC(func_001B1AC8);

void func_001B1B38(RangeRecord* self)
{
    if (self->link == 0) {
        func_001B1CF8(self, 0x2C);
    }
    if (func_001B1D38(self) == 0) {
        func_001B1D70(self, 100.0f);
        func_001B1DA8(self, 400.0f);
    }
    if ((((Hdr_1B1B38*)self->link)->f0C & 0x10000000) == 0) {
        s32 idx = g_meshQueueCount;
        if (idx < 0x4000) {
            u8* p = D_0027DC20 + idx * 16;
            self->f2D0 = p;
            g_meshQueueCount = idx + 1;
            func_001F5C0C(p, 0, 16);
        }
    }
}

void func_001B1BF0(RangeRecord* self)
{
    self->fC0 = 0;
}

ASM_FUNC(func_001B1BF8);

void func_001B1CF8(RangeRecord* self, s32 key)
{
    void* found = FindAnimRecord(key != -1 ? key : 0x2C);
    self->link = found;
    if (found)
        func_001B1BF0(self);
}

s32 func_001B1D38(RangeRecord* p)
{
    s32 r = 0;
    if (0.0f <= p->f04 && 0.0f <= p->f08)
        r = 1;
    return r;
}

void func_001B1D70(RangeRecord* p, f32 v)
{
    p->f04 = v;
    if (p->f08 < 0.0f)
        p->f08 = v;
    func_001B1BF0(p);
}

void func_001B1DA8(RangeRecord* o, f32 v)
{
    o->f08 = v;
    if (o->f04 < 0.0f) {
        o->f04 = v;
    }
    func_001B1BF0(o);
}

ASM_FUNC(func_001B1DE0);

ASM_FUNC(func_001B1EC8);

void func_001B1FB0(RangeRecord* o, f32 v)
{
    o->f40 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

void func_001B1FE0(RangeRecord* o, f32 v)
{
    o->f44 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

void func_001B2010(RangeRecord* o, f32 s) {
    f32 t = func_002054F0(o, s * 0.00872664712f);
    o->f04 = t * o->f40;
    o->f08 = t * o->f44;
    func_001B1BF0(o);
}

void func_001B2068(RangeRecord* self, Quad16* src)
{
    *(Quad16*)((u8*)self + 0x30) = *src;
    func_001B1BF0(self);
}

s32 func_001B2090(Obj_1B2090** self, u32 bits)
{
    s32 r = 0;
    if (*self != 0) {
        u32 flags = (*self)->flags_C;
        Camera* g = g_camera;
        u32 mask = g->f21C;
        s32 ok = 0;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            ok = 1;
        }
        if (ok != 0) {
            if (((bits & 1) != 0 && (*self)->kind_0 == 2) || ((bits & 2) != 0 && (*self)->kind_0 == 3)) {
                r = 1;
            }
        }
    }
    return r;
}

s32 func_001B2118(void* unused, Obj_1B2118* o)
{
    s32 r = 0;
    if ((o->f538 & (1UL << 43)) == 0) {
        r = o->f410 != 0;
    }
    return r;
}

ASM_FUNC(func_001B2140);

// The literals func_001B2358 loads.
extern const f32 D_0024D164 = -3.40282347e+38f;
extern const f32 D_0024D168 = 3.40282347e+38f;

ASM_FUNC(func_001B2358);

void func_001B2640(Obj_1B2640* o)
{
    if (o->f0 != 0) {
        Camera* c = g_camera;
        s32 bits = o->f0->f0C;
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
                func_001B2358(o);
                if (o->fC0 == 0) {
                    goto done;
                }
            }
            V24A0* g = &g_vifPacketWriter;
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

void func_001B2790(World* self, void* a1, s32 max, s32* outCount, Node_1B2790** out, f32 f)
{
    ListFrame frame;
    s32 count = 0;
    Node_1B2790* node;
    for (node = (Node_1B2790*)self->list1C00.head; node != 0; node = node->next) {
        if (func_001B26F8(node, a1, f) == 0) {
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

void func_001B2840(C6E* self, void* obj)
{
    T2176* p = CreatePathCurve(ReadBufferedU8(obj));
    self->curve = p;
    void (*fn)(T2176* self, void* stream) = p->vt->m00;
    if (fn != 0) {
        fn(p, obj);
    }
    ReadPropertyRecords(self, obj);
}

void func_001B28A8(C6E* self, BaseObject* other)
{
    Mat4A a;
    Mat4A b;
    T2176* h;
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

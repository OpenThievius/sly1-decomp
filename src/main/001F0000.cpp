// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "transform_object.h"
#include "c67.h"
#include "c8d.h"
#include "camera.h"
#include "list_iter.h"
#include "screen_element.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "pad_record.h"
#include "object_link.h"

struct Entry_1F3358 { f32 w; f32 x; f32 y; f32 z; };
struct Blob_1F3358 { f32 lo; f32 hi; f32 scale; s32 count; Entry_1F3358 items[1]; };

f32 func_001F3250(f32 a, f32 b, f32 c);
f32 func_001F3328(f32 a, f32 b);

f32 func_001F3358(Blob_1F3358* obj)
{
    f32 num = 0.0f;
    f32 den = 0.0f;
    for (s32 i = 0; i < obj->count; i++) {
        Entry_1F3358* e = &obj->items[i];
        f32 r = SampleSmoothNoise(e->x, e->y, e->z);
        num += e->w * r;
        den += e->w;
    }
    f32 t = ApplyBiasCurve(num / den, obj->scale);
    return obj->lo + t * (obj->hi - obj->lo);
}

struct Vec4_1F38F0 { f32 a; f32 b; f32 c; f32 d; };
struct Buf_1F38F0 { u8 pad[0xC]; u32 count; Vec4_1F38F0 items[4]; };

void func_001F38F0(Buf_1F38F0* buf, f32 x, f32 y, f32 z, f32 w)
{
    u32 n = buf->count;
    if (n < 4) {
        Vec4_1F38F0* e = &buf->items[n];
        buf->count = n + 1;
        e->a = x;
        e->b = y;
        e->c = z;
        e->d = w;
    }
}

void* func_001F37D8(void* self, s32 mode, s32 flag);

void* func_001F3830(void* self, s32 mode)
{
    return func_001F37D8(self, mode, 1);
}

struct Scaler_001F3850 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

void func_001F3850(void* self, f32 x)
{
    Scaler_001F3850* s = (Scaler_001F3850*)func_001F3810(self, 1);
    if (x == 0.0f) s->scale = 0.0f;
    else s->scale = 1.0f / x;
}

struct Scaler_001F38A0 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

void func_001F38A0(void* self, f32* out)
{
    Scaler_001F38A0* s = (Scaler_001F38A0*)func_001F3810(self, 1);
    f32 v = s->scale;
    if (v == 0.0f) *out = 0.0f;
    else *out = 1.0f / v;
}

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 a, f32 b, f32 c, f32 d);

void func_001F3928(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    AppendVector4ToBuffer(p + 0x30, a, b, c, d);
}

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 x, f32 y, f32 z, f32 w);

void func_001F3990(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    AppendVector4ToBuffer(p + 0x80, a, b, c, d);
}

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);

void func_001F3A40(TransformObject* self, void* stream)
{
    ReadBufferedRotation3(stream, &self->rot);
    ReadBufferedVector3(stream, &self->pos);
    ReadPropertyRecords(self, stream);
}

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_00182F78(void* self, void* value);

void func_001F3A90(TransformObject* self, BaseObject* other)
{
    func_00128018(self->parent, other, &self->pos, &self->pos);
    func_00128150(self->parent, other, &self->rot, &self->rot);
    ReparentObject(self, other);
}

void func_001F3AF0(TransformObject* self, BaseObject* other)
{
    func_00128018(other, 0, &self->pos, &self->pos);
    func_00128150(other, 0, &self->rot, &self->rot);
}

s32 func_00128018(void* a, s32 b, void* c, s32 d);

s32 func_001F3BD8(BaseObject* self, s32 arg)
{
    return func_00128018(self->parent, 0, (u8*)self + 0x40, arg);
}

s32 func_00128150(void* a, s32 b, void* c, s32 d);

s32 func_001F3C08(BaseObject* self, s32 arg)
{
    return func_00128150(self->parent, 0, (u8*)self + 0x50, arg);
}

void func_00182C18(void* self);

void func_001F2758(C8D* self)
{
    InitObject(self);
    self->index40 = -1;
    self->scale34 = -1.0f;
    self->index6D0 = -1;
}

struct Node_1F2798 { u8 pad0[0xC]; void* owner0C; u8 pad1[0x84 - 0x10]; Node_1F2798* next84; };
struct Item_1F2798 { s32 link; u8 pad0[0x3C]; };
struct Sub_1F2798 { u8 pad0[4]; void* listA[4]; void* listB[1]; };
struct Elem_1F2798 { u8 pad0[0x20]; Sub_1F2798* sub20; u8 pad1[0x2C]; };
struct Ctx_1F2798 { u8 pad0[0x54]; Node_1F2798* node54; s32 count58; Elem_1F2798* elems5C; };
struct Owner_1F2798 { u8 pad0[0x3C]; s32 count3C; u8 pad1[0x6E0 - 0x40]; Item_1F2798 items6E0[4]; Item_1F2798 items7E0[1]; u8 pad2[0x8E0 - 0x820]; Node_1F2798* head8E0; };

void func_001F2798(Owner_1F2798* self, s32 unused, Ctx_1F2798* ctx)
{
    Node_1F2798* node = ctx->node54;
    node->next84 = self->head8E0;
    self->head8E0 = node;
    node->owner0C = self;
    for (s32 i = 0; i < ctx->count58; i++) {
        Elem_1F2798* elem = ctx->elems5C + i;
        Sub_1F2798* sub = elem->sub20;
        for (s32 j = 0; j < self->count3C; j++) {
            if (sub->listA[j]) {
                *(void**)sub->listA[j] = &self->items6E0[j];
            }
            if (sub->listB[j]) {
                *(void**)sub->listB[j] = &self->items7E0[j];
            }
        }
    }
}

f32 func_001F3328(f32 value, f32 denominator)
{
    return value / (1.0f + (1.0f / denominator - 2.0f) * (1.0f - value));
}

void* func_001F37D8(C8D* obj, s32 value)
{
    if (obj->f38 == 0) {
        return 0;
    }
    if (value == 1) {
        obj->f8E4 = value;
    }
    return (u8*)obj + (obj->index6D0 * 0xD0 + 0x50);
}

typedef void (*VFn_1F3D80)(void* self, void* arg);
struct Item_1F3D80 { VFn_1F3D80* vtbl; };
struct Obj_1F3D80 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x40 - 0x18];
    u8 pad2[0x50 - 0x40];
    u8 pad3[0xA0 - 0x50];
    s32 count;
    Item_1F3D80** arr;
    s32 count2;
    void** arr2;
};

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);
s32 func_00137D10(void* p);
void* func_0018D500(int size);
void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);
void func_00138518(void* self);

void func_001F3D80(Obj_1F3D80* self, void* other)
{
    ReadBufferedRotation3(other, (u8*)self + 0x50);
    ReadBufferedVector3(other, (u8*)self + 0x40);
    ReadPropertyRecords(self, other);
    self->count = ReadBufferedS16(other);
    self->arr = (Item_1F3D80**)AllocateFrontMemory(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        s32 a = ReadBufferedS16(other);
        s32 b = ReadBufferedS16(other);
        s32 c = ReadBufferedS16(other);
        Item_1F3D80* it = (Item_1F3D80*)CreateTypedRecord(a, self->f14, 0, b, c);
        self->arr[i] = it;
        it->vtbl[14](it, other);
    }
    SkipBufferedBlock(other);
    self->count2 = ReadBufferedS16(other);
    self->arr2 = (void**)AllocateFrontMemory(self->count2 << 2);
    for (s32 i = 0; i < self->count2; i++) {
        self->arr2[i] = (void*)ReadBufferedS16(other);
    }
}

typedef void (*VFn_1F3F80)(void* self, void* arg);
struct Item_1F3F80 { VFn_1F3F80* vtbl; };
struct Obj_1F3F80 { u8 pad0[0x18]; void* f18; u8 pad1[0xA0 - 0x1C]; s32 count; void** arr; };

void func_00182C58(void* self);
void func_00182ED8(void* a);

void func_001F3F80(Obj_1F3F80* self)
{
    StartObject(self);
    for (s32 i = 0; i < self->count; i++) {
        Item_1F3F80* item = (Item_1F3F80*)self->arr[i];
        item->vtbl[25](item, self->f18);
        func_00182ED8(item);
    }
}

struct Obj_1F3810;

void* func_001F37D8(Obj_1F3810* self, s32 mode, s32 flag);

void* func_001F3810(Obj_1F3810* self, s32 mode)
{
    return func_001F37D8(self, mode, 0);
}

struct Mgr_1F18B0;
struct Loc_1F18B0;
struct Obj_1F18B0;
void func_00128018(Mgr_1F18B0* a0, Obj_1F18B0* a1, void* a2, Loc_1F18B0* a3);

struct Node_1F36E8 {
    s32 f0;
    s32 f4;
    u8 pad8[0x8];
    Quad16 q10;
    u8 pad20[0x40];
    s32 f60;
};

void func_001F36E8(C8D* o)
{
    s32 n = o->f38;
    s32 off;
    Node_1F36E8* node;

    o->f38 = n + 1;
    o->index6D0 = o->index6D0 + 1;
    off = n * 0xD0;
    off += 0x50;
    node = (Node_1F36E8*)((u8*)o + off);
    node->f0 = 0;
    node->q10 = *(Quad16*)&g_unitXVector;
    if (o->index40 >= 0) {
        node->f4 = o->index40;
        o->index40 = -1;
        node->f60 = 2;
    } else {
        s32 v = o->f3C;
        node->f4 = v;
        v++;
        o->f3C = v;
        o->index40 = node->f4;
        node->f60 = 0;
    }
}

void func_00182C18(BaseObject* self);

void func_001F39F8(TransformObject* self)
{
    InitObject(self);
    Mat3_73* dst = &self->rot;
    *dst = *(Mat3_73*)&g_identityMatrix;
}

// NEAR: the two counter increments (0x38 and 0x6D0) are computed in the reverse
// order of retail (addiu v0 before addiu v1); no statement order tried changed it.

struct Entry_001F3768 {
    s32 a;
    u8 pad0[0x0C];
    Quad16 q10;
    Quad16 q20;
    u8 pad1[0x08];
    f32 f38;
    u8 pad2[0x4C];
    f32 f88;
};

void func_001F3768(C8D* self)
{
    s32 n6 = self->index6D0;
    s32 idx = self->f38;
    Entry_001F3768* e = (Entry_001F3768*)((u8*)self + 0x50 + 0xD0 * idx);
    n6 = n6 + 1;
    idx = idx + 1;
    self->f38 = idx;
    self->index6D0 = n6;
    e->a = 1;
    e->q10 = *(Quad16*)&g_unitYVector;
    e->q20 = *(Quad16*)&g_unitZVector;
    e->f38 = 0.5f;
    e->f88 = 0.5f;
    self->f3C = self->f3C + 1;
}

f32 func_001F31F8(s32 a0)
{
    s32 n = a0;
    n ^= n << 13;
    n = n * (n * n * 0x3D73 + 0xC0AE5) + 0x5208DD0D & 0x7FFFFFFF;
    return (f32)n * 4.656612873077393e-10f;
}

struct Tbl_1F3EE0 { u8 pad0[0x14]; s32 f14; u8 pad1[0xA0 - 0x18]; s32 count; s32* arr; };

void func_001830D8(Tbl_1F3EE0* self, Tbl_1F3EE0* other);
s32 func_00183058(s32 a, s32 b, s32 c);

void func_001F3EE0(Tbl_1F3EE0* self, Tbl_1F3EE0* other)
{
    CopyObjectData(self, other);
    self->arr = (s32*)AllocateFrontMemory(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        self->arr[i] = CreateObjectCopy(other->arr[i], self->f14, 0);
    }
}

extern f32 D_0026185C;

f32 func_001F31F8(s32 i);

f32 func_001F3250(f32 x, f32 y, f32 z)
{
    f32 t = (x + x) * g_gameTime + y;
    s32 i = (s32)t;
    f32 a = HashToUnitFloat(i);
    f32 b = HashToUnitFloat(i + 1);
    if (i & 1) {
        a = a * z;
        b = z * (b - 1.0f) + 1.0f;
    } else {
        b = b * z;
        a = z * (a - 1.0f) + 1.0f;
    }
    f32 u = t - (f32)i;
    u = (u * u) * (3.0f - (u + u));
    return a + u * (b - a);
}

struct Node_1F0758;

void func_00182ED8(Node_1F0758* node);

C7A* func_0015A418(World* host, s32 kind, s32 id, C7A* ctx);
s32 func_0015A4F0(World* host, s32 kind, s32 a2, s32 a3, s32 max, C7A** out);

struct Min_1F3C38 {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

C7A* func_001F3C38(s32 id, s32 parent)
{
    C7A* found = 0;
    C7A* buf[64];
    C7A* other;
    C7A* any;
    s32 n;
    s32 i;

    if (id != -1) {
        found = FindFirstObjectById(g_currentWorld, 0x101, id, FindFirstObjectById(g_currentWorld, 0x101, parent, 0));
    }
    if (found == 0) {
        any = 0;
        other = 0;
        n = GatherObjectsById(g_currentWorld, 0x205, 0x74, 0, 0x100, buf);
        n = Min_1F3C38::Of(n, 0x40);
        for (i = 0; i < n; i++) {
            C7A* e = buf[i];
            if (id != -1 && id == e->idB0) {
                found = e;
                break;
            }
            if (g_screenFade.mode != 0 && g_screenFade.style == 2 && e->id94 != 0) {
                other = e;
            }
            if (e->rec != 0) {
                any = e;
            }
        }
        if (found == 0) {
            found = other;
        }
        if (found == 0) {
            found = any;
        }
    }
    return found;
}

extern s32 (*D_00276608[6])[4];

struct Ent_1F0908 { s32 a; s32 type; s32 id; s32 d; };
struct Tbl_1F0908 { u8 pad0[0x54]; s32 count; Ent_1F0908* ents; };
struct Slot_1F0908 { u8 pad0[0x34]; f32 f34; };
struct SlotRef_1F0908 { Slot_1F0908* s; u8 pad[0x30]; };
struct Obj_1F0908 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x2E8 - 0x18];
    Tbl_1F0908* tbl;
    u8 pad2EC[4];
    u8 f2F0[8];
    SlotRef_1F0908 slots[1];
};

BaseObject* func_0015A418(void* o, s32 a, s32 b, Obj_1F0908* c);


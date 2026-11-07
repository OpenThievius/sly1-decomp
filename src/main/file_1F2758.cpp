// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1F2758 to 0x1F59C4, built whole (config/us/files.tsv): it starts where
// file_1E88D0.cpp's _GLOBAL_$I$ ends and ends where the libraries begin (config/us/layout.tsv).
// Its .rodata is the two jump tables of its assembly at 0x24E840 and 0x24E860; it has no .data
// or .bss. Named after its first address until what it was is known.
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
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "asm_func.h"

#include "common.h"

struct Entry_1F3358 { f32 w; f32 x; f32 y; f32 z; };
struct Blob_1F3358 { f32 lo; f32 hi; f32 scale; s32 count; Entry_1F3358 items[1]; };

f32 func_001F3250(f32 a, f32 b, f32 c);
f32 func_001F3328(f32 a, f32 b);

struct Vec4_1F38F0 { f32 a; f32 b; f32 c; f32 d; };
struct Buf_1F38F0 { u8 pad[0xC]; u32 count; Vec4_1F38F0 items[4]; };

void* func_001F37D8(void* self, s32 mode, s32 flag);

struct Scaler_001F3850 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

struct Scaler_001F38A0 { u8 pad[0x64]; f32 scale; };

void* func_001F3810(void* self, s32 mode);

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 a, f32 b, f32 c, f32 d);

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 x, f32 y, f32 z, f32 w);

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_00182F78(void* self, void* value);

s32 func_00128018(void* a, s32 b, void* c, s32 d);

s32 func_00128150(void* a, s32 b, void* c, s32 d);

void func_00182C18(void* self);

struct Node_1F2798 { u8 pad0[0xC]; void* owner0C; u8 pad1[0x84 - 0x10]; Node_1F2798* next84; };
struct Item_1F2798 { s32 link; u8 pad0[0x3C]; };
struct Sub_1F2798 { u8 pad0[4]; void* listA[4]; void* listB[1]; };
struct Elem_1F2798 { u8 pad0[0x20]; Sub_1F2798* sub20; u8 pad1[0x2C]; };
struct Ctx_1F2798 { u8 pad0[0x54]; Node_1F2798* node54; s32 count58; Elem_1F2798* elems5C; };
struct Owner_1F2798 { u8 pad0[0x3C]; s32 count3C; u8 pad1[0x6E0 - 0x40]; Item_1F2798 items6E0[4]; Item_1F2798 items7E0[1]; u8 pad2[0x8E0 - 0x820]; Node_1F2798* head8E0; };

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

typedef void (*VFn_1F3F80)(void* self, void* arg);
struct Item_1F3F80 { VFn_1F3F80* vtbl; };
struct Obj_1F3F80 { u8 pad0[0x18]; void* f18; u8 pad1[0xA0 - 0x1C]; s32 count; void** arr; };

void func_00182C58(void* self);
void func_00182ED8(void* a);

struct Obj_1F3810;

void* func_001F37D8(Obj_1F3810* self, s32 mode, s32 flag);

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

void func_00182C18(BaseObject* self);

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

struct Tbl_1F3EE0 { u8 pad0[0x14]; s32 f14; u8 pad1[0xA0 - 0x18]; s32 count; s32* arr; };

void func_001830D8(Tbl_1F3EE0* self, Tbl_1F3EE0* other);
s32 func_00183058(s32 a, s32 b, s32 c);

extern f32 D_0026185C;

f32 func_001F31F8(s32 i);

struct Node_1F0758;

void func_00182ED8(Node_1F0758* node);

C7A* func_0015A418(World* host, s32 kind, s32 id, C7A* ctx);
s32 func_0015A4F0(World* host, s32 kind, s32 a2, s32 a3, s32 max, C7A** out);

struct Min_1F3C38 {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

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


#include "common.h"

void func_001451F0(u32, int, int, void*, int, void*);
void func_00125C90();
struct Obj_1F4308 { u8 pad[0x98]; s32 state; f32 value; };

void func_00123ED0(void*);

void func_001F57E0(void*);

void func_00145088(u32, int, void*, int, void*);

void func_001BA130(void*);

s32 func_0013EC00(void*, int, void*, void*, void*, void*, void*);

void func_00124A48(void*);
void func_001F55A8(Rec36*);

void func_001FA468();

s32 func_001F3C38(void* a, void* b);
s32 func_001F4008(void* x);
s32 func_001925F0(void);
s32 func_00192620(void);
s32 func_001929D0(void* v);

// NEAR: only the vtbl[19] load differs: retail loads it into $v1 (lw v1,76(v1)), we use $v0 for the test and the call.


void func_00124A48(void* self);

extern f32 D_0026185C;
void func_001DDA20(void* a);

struct Glob_1F4A30 { s32 flags; };
s32 func_001601A0(s32 a0);
s32 func_00160850(s32 a0);
void func_001EFFA0(ScreenFade* dst, FadeRequest* args, s32 count);

void func_00124A48(LookupObject* self);
BaseObject* func_0015A418(void* host, s32 a1, s32 a2, LookupObject* ctx);
s32 func_001300E8(BaseObject* n, s32 kind);

void func_001B7968(Collider* self);

void func_001B9AE0(C37* o, s32 a, s32 b, s32 c, s32 d);

struct Ev_1F5868;
s32 func_001300E8(Ev_1F5868* e, s32 kind);

struct Obj_1F4378 { u8 pad[0x2D0]; s32 f2D0; };


s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

struct Self_57E0 { void* f0; s32 f4; };
struct Out_57E0 { s32 f0; s32 f4; Self_57E0* f8; void* fC; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_0018D800(void* dst, void* src, s32 count);

extern u8 D_00247AD0[];

struct Ctx_1F4408 {
    u8 pad00[0x19D8];
    s32 f19D8;
    s32 f19DC;
};

struct Obj_1F4408 {
    u8 pad00[0x78];
    s32 f78;
};

struct Val_1F4408 { s32 unused; };
struct Key_1F4408 { s32 unused; };
Val_1F4408* func_00160180(Key_1F4408* k);
void func_001F0428(Val_1F4408* v, s32 m, s32 n);
void func_001F4808(ObjectSubGroup* x);
void func_001EFFA0(ScreenFade* dst, FadeRequest* args, s32 count);

struct Ctx_1F56D8;
struct Tab_1F56D8;
struct Ctx_1F56D8 {
    u8 pad00[0x0C];
    s32 cnt;            // 0x0C
    u8 pad10[0x84];
    s32 s94;            // 0x94
};
struct Frame_1F56D8 {
    s32 a[4];           // 0x00
    u8 pad10[0x10];
    s32 b[4];           // 0x20
    s32 c[4];           // 0x30
    u8 pad40[0x20];
    f32 f60;            // 0x60
};


void func_00178D98(Player* self, s32 a1, void* a2, void* a3, void* a4);
void func_001782C0(Player* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void func_00188850(Tab_1F56D8* t, void* out, f32 x);
void func_00175170(Player* self, s32 a, s32 b);
void func_00178598(Player* self, void* s2, f32 f);

void func_00138550(void* a, void* b);
void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void* a, void* b, void* c, void* d, void* e);
void func_0011EC40(void* a, void* b);
s32 func_00137D10(void* a);
void* func_0018D500(s32 size);
void* func_0011E580(s32 a, s32 b, s32 c, s32 d, s32 e);


struct Iter_1F55A8 { List01* list; u8* link; s32 offset; Iter_1F55A8* saved; };

struct Next_1F55A8 {
    static BaseObject* Of(Iter_1F55A8* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_1F55A8 {
    static void Of(Iter_1F55A8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_1F55A8*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

BaseObject* func_0015A418(World* a, s32 b, void* c, ContactTracker* d);
void func_001F5868(Rec36* self, BaseObject* n);

struct Obj_1F5008 {
    u8 pad0[0x550];
    s32 f550;
};

void func_001B93F8(Collider* self);
s32 func_00182F40(Obj_1F5008* o, ContactTracker* self);
s32 func_001300E8(Obj_1F5008* o, s32 kind);
s32 func_001F5C0C(void* p, s32 a, s32 b);
s32 func_00177838(void* t, s32 a, s32 b);

struct Tmp_1F5008 {
    ContactTracker* self;
    Obj_1F5008* obj;
    u8 pad[0x18];
    Vec02 q20;
    Vec02 q30;
};

struct Add_1F5008 {
    static void Of(ContactTracker* self, Obj_1F5008* p, Vec02* a, Vec02* b)
    {
        s32 c = self->count;
        if ((u32)c < 10) {
            if (p->f550 != 3) {
                Slot36* s = &self->slots[c];
                self->count = c + 1;
                s->obj = (Collider*)p;
                s->q10 = *a;
                s->q20 = *b;
            }
        }
    }
};

struct Glob_1F4808 { u8 pad[0x19DC]; s32 f19DC; };


s32 func_001601A0(s32 a);
void func_001E0828(T217D_1380* g);
void func_001F4760(ObjectSubGroup* self, s32 state);
void func_001E02C8(T217D_1380* g, s32 n);
void func_001F4408(s32 flag, s32 n);
s32 func_001300E8(BaseObject* key, s32 kind);
void func_001451F0(u8* a0, s32 a1, s32 a2, u8* a3, s32 a4, s32 a5);
s32 func_0012C7B0(Animation* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);
s32 func_0012C9A8(Animation* node);
void func_001837E0(ObjectSubGroup* self, s32 a, s32 b, s32 c);

void func_001F2758(C8D* self)
{
    InitObject(self);
    self->index40 = -1;
    self->scale34 = -1.0f;
    self->index6D0 = -1;
}

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

INCLUDE_RODATA(jtbl_0024E840);
ASM_FUNC(func_001F2840);

ASM_FUNC(func_001F2EF0);

ASM_FUNC(func_001F3140);

f32 func_001F31F8(s32 a0)
{
    s32 n = a0;
    n ^= n << 13;
    n = n * (n * n * 0x3D73 + 0xC0AE5) + 0x5208DD0D & 0x7FFFFFFF;
    return (f32)n * 4.656612873077393e-10f;
}

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

f32 func_001F3328(f32 value, f32 denominator)
{
    return value / (1.0f + (1.0f / denominator - 2.0f) * (1.0f - value));
}

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

ASM_FUNC(func_001F3408);

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

void* func_001F3810(Obj_1F3810* self, s32 mode)
{
    return func_001F37D8(self, mode, 0);
}

void* func_001F3830(void* self, s32 mode)
{
    return func_001F37D8(self, mode, 1);
}

void func_001F3850(void* self, f32 x)
{
    Scaler_001F3850* s = (Scaler_001F3850*)func_001F3810(self, 1);
    if (x == 0.0f) s->scale = 0.0f;
    else s->scale = 1.0f / x;
}

void func_001F38A0(void* self, f32* out)
{
    Scaler_001F38A0* s = (Scaler_001F38A0*)func_001F3810(self, 1);
    f32 v = s->scale;
    if (v == 0.0f) *out = 0.0f;
    else *out = 1.0f / v;
}

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

void func_001F3928(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    AppendVector4ToBuffer(p + 0x30, a, b, c, d);
}

void func_001F3990(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    AppendVector4ToBuffer(p + 0x80, a, b, c, d);
}

void func_001F39F8(TransformObject* self)
{
    InitObject(self);
    Mat3_73* dst = &self->rot;
    *dst = *(Mat3_73*)&g_identityMatrix;
}

void func_001F3A40(TransformObject* self, void* stream)
{
    ReadBufferedRotation3(stream, &self->rot);
    ReadBufferedVector3(stream, &self->pos);
    ReadPropertyRecords(self, stream);
}

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

ASM_FUNC(func_001F3B48);

s32 func_001F3BD8(BaseObject* self, s32 arg)
{
    return func_00128018(self->parent, 0, (u8*)self + 0x40, arg);
}

s32 func_001F3C08(BaseObject* self, s32 arg)
{
    return func_00128150(self->parent, 0, (u8*)self + 0x50, arg);
}

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

void func_001F3EE0(Tbl_1F3EE0* self, Tbl_1F3EE0* other)
{
    CopyObjectData(self, other);
    self->arr = (s32*)AllocateFrontMemory(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        self->arr[i] = CreateObjectCopy(other->arr[i], self->f14, 0);
    }
}

void func_001F3F80(Obj_1F3F80* self)
{
    StartObject(self);
    for (s32 i = 0; i < self->count; i++) {
        Item_1F3F80* item = (Item_1F3F80*)self->arr[i];
        item->vtbl[25](item, self->f18);
        ResolveAndStartObject(item);
    }
}

ASM_FUNC(func_001F4008);

void func_001F42D0(void* self, void* a1, void* a2, void* a3, void* a4) { UpsertKeyedEntry((u8*)self + 0xB8, 4, (u8*)self + 0xB4, a1, a2, a3, a4); }

void func_001F4308(Obj_1F4308* self, f32 value) { self->value = value; self->state = 1; }

s32 func_001F4318(void* unused, void* a, void* b)
{
    s32 r = func_001F3C38(a, b);
    if (r != 0) {
        r = func_001F4008((void*)r);
        goto done;
    }
    r = GetActiveSwitchedCollider();
    if (r == 0) {
        r = GetCurrentSwitchedCollider();
        if (r != 0) {
            r = ActivateSwitchedCollider((void*)r);
        }
    }
done:
    return r;
}

Obj_1F4378* func_001F4378(void)
{
    void* arr[64];
    Obj_1F4378* found = 0;
    s32 n = GatherObjectsById(g_currentWorld, 0x205, 0x7D, 0, 0x100, arr);
    s32 cap = 0x40;
    s32 lim = 0x3F;
    n = (lim < n) ? cap : n;
    for (s32 i = 0; i < n; i++) {
        Obj_1F4378* o = (Obj_1F4378*)arr[i];
        if (o->f2D0 != 0) {
            found = o;
            break;
        }
    }
    return found;
}

void func_001F4408(s32 flag, s32 n)
{
    Ctx_1F4408* ctx = (Ctx_1F4408*)g_saveData;
    Obj_1F4408* o;
    ObjectSubGroup* v;
    Val_1F4408* k;
    FadeRequest args;
    if (ctx->f19D8 == 5) {
        goto lm1;
    }
    if (ctx->f19DC != 0) {
        goto l4490;
    }
    o = (Obj_1F4408*)g_currentLevelRecord;
    if ((o->f78 & 1) != 0) {
        goto l4470;
    }
lm1:
    StartObjectFade((Val_1F4408*)D_00247AD0, -1, n);
    return;
l4470:
    k = LookupEntryById((Key_1F4408*)(u32)((ctx->f19D8 << 8) | 1));
    StartObjectFade(k, 0x1BD, n);
    return;
l4490:
    v = (ObjectSubGroup*)FindActiveObjectSubGroup();
    if (v == 0) {
        goto larg;
    }
    if (flag != 0) {
        v->count = 0;
    }
    func_001F4808(v);
    return;
larg:
    args.kind = 1;
    args.key = &D_00275B04;
    args.f08 = -1;
    args.f0C = -1;
    args.flags = 0;
    StartScreenFade(&g_screenFade, &args, n);
}

void func_001F4500(ObjectSubGroup* self, void* s3)
{
    ReadOptionalBufferedBlock(s3, (u8*)self + 0x2FC);
    ReadOptionalBufferedBlock(s3, (u8*)self + 0x308);
    ReadBufferedRotation3(s3, &self->rot);
    ReadBufferedVector3(s3, &self->pos);
    void (*f)(BaseObject* self) = self->desc->m12;
    if (f != 0) {
        f(self);
    }
    self->f2E4 = 0;
    ReadMeshTables(s3, &self->f2EC, &self->f2F0, &self->f2F4, &self->f2F8);
    s32 i = 0;
    ReadPropertyRecords(self, s3);
    s32 n = ReadBufferedS16(s3);
    self->count = n;
    self->items = (BaseObject**)AllocateFrontMemory(n * 4);
    while (i < self->count) {
        s32 a = ReadBufferedS16(s3);
        s32 b = ReadBufferedS16(s3);
        s32 c = ReadBufferedS16(s3);
        BaseObject* o = (BaseObject*)CreateTypedRecord(a, (s32)self->world, (s32)self->parent, b, c);
        self->items[i++] = o;
        o->desc->m0A(o, s3);
        o->desc->m03(o);
    }
}

void func_001F4660(ObjectSubGroup* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->count; i++) {
        BaseObject* e = self->items[i];
        const Desc01* vt = e->desc;
        if (vt->m0F != 0) {
            vt->m0F(e);
        }
        BaseObject* e2 = self->items[i];
        e2->desc->m10(e2);
    }
    if (self->f2D4 != 0) {
        s32* g = (s32*)(void*)g_currentEntry;
        if ((g[0] & 2) == 0) {
            BaseObject* a = self;
            while (a->parent != 0) {
                a = a->parent;
            }
            a->desc->m03(a);
        }
    }
}

void func_001F4760(ObjectSubGroup* self, s32 state)
{
    if (state != self->f2E4) {
        if (self->f2E4 == 4 && state != 5)
            D_0026F138.vt->m15(&D_0026F138);
        if (state == 5) {
            self->flags = (self->flags & ~0x30000000000ULL) | 0x10000000000ULL;
            AcquirePadSelectFlag(self->world);
            self->f2E4 = state;
        } else {
            self->f2E4 = state;
        }
        self->f2E8 = g_gameTime;
    }
}

void func_001F4808(ObjectSubGroup* self)
{
    BaseObject* key;
    s32 i;
    s32 found = 0;
    s32 next;
    Animation* it;

    key = (BaseObject*)GetActiveSwitchedCollider();
    if (g_timerCaption.state == 2
        && (self->f2E0 != 0 || self->f2D4 != 0
            || ((*(Glob_1F4808**)&g_saveData)->f19DC == 0 && (u8)GetEntryIdByKey(self->f2FC) == 1))) {
        func_001E0828(&g_timerCaption);
        SetObjectSubGroupState(self, 2);
        goto tail;
    }
    if (g_timerCaption.state >= 2) {
        SetBestTimeState(&g_timerCaption, 4);
    }
    if (self->f2D8 != 0) {
        func_001F4408(1, self->f318);
        SetObjectSubGroupState(self, 0);
        return;
    }
    if (key == 0 || IsObjectOfKind(key, 0x16) == 0) {
        RemoveCameraControllers((*(u8**)&g_camera), 2, 0, (*(u8**)&g_camera) + 0x460, 0, 0);
    }
    SetObjectSubGroupState(self, 5);
    for (i = 0; i < self->count; i++) {
        it = (Animation*)self->items[i];
        CreateAnimationPlayerWithoutPresetTargets(it, 0, 0, 0, 0.0f, 1.0f);
        next = 0;
        if (found != 0 || func_0012C9A8(it) != 0) {
            next = 1;
        }
        found = next;
    }
    if (found == 0) {
        if (self->f324 > 0.0f) {
            self->f31C = ((f32*)&g_gameTime)[0] + self->f324;
        } else if (self->count > 0) {
            self->f31C = ((f32*)&g_gameTime)[0] + ((Animation*)self->items[0])->length;
        } else {
            self->f31C = ((f32*)&g_gameTime)[0];
        }
    }
tail:
    TriggerScriptEvent(self, 2, 0, 0);
}

void func_001F4A30(ObjectSubGroup* self)
{
    FadeRequest m;
    s32 ok = 0;
    m.kind = 1;
    switch (self->f304) {
    case 0: ok = GetLevelEntryWord(GetEntryIdByKey(self->f2FC)) >> 1; goto fin;
    case 1: ok = ((Glob_1F4A30*)(void*)g_currentEntry)->flags >> 1;
    fin: ok &= 1;
    }
    if (ok) {
        m.text = (u8*)self->f308;
        m.f08 = self->f30C;
    } else {
        m.text = (u8*)self->f2FC;
        m.f08 = self->f300;
    }
    m.f0C = -1;
    m.flags = 0;
    StartScreenFade(&g_screenFade, &m, self->f318);
}

INCLUDE_RODATA(jtbl_0024E860);
ASM_FUNC(func_001F4AE0);

void func_001F4E18(LookupObject* self) { InitPlacedObject(self); self->id = -1; }

void func_001F4E48(LookupObject* self)
{
    StartPlacedObject(self);
    if (self->id != -1) {
        BaseObject* c = FindFirstObjectById(self->world, 0x104, self->id, self);
        if (c) {
            if (c->desc->flags & 1) {
                self->found2D8 = c;
            } else if (IsObjectOfKind(c, 0x7E)) {
                self->found2D4 = c;
            }
        }
    }
}

void func_001F4ED0(void* self) { if (!*(s32*)((u8*)self + 0x310)) { PushCameraController((u32)g_camera, 7, (u8*)g_camera + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 1; } }

void func_001F4F20(void* self) { if (*(s32*)((u8*)self + 0x310)) { RemoveCameraControllers((u32)g_camera, 0xB, 7, (u8*)g_camera + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 0; } }

void func_001F5590(Rec36* a, ContactTracker* b);

void func_001F4F70(ContactTracker* self)
{
    InitCollider(self);
    InitTrackedNodes(&self->rec, self);
    self->f4E0 = 1;
    self->flags538 = (self->flags538 & ~0xF000000000ULL) | 0x2000000000ULL;
}

void func_001F4FD8(ContactTracker* self) { StartPlacedObject(self); FillTrackedNodes(&self->rec); }

void func_001F5008(ContactTracker* self) {
    Tmp_1F5008 tmp;
    Obj_1F5008* p;
    UpdateCollider(self);
    self->count = 0;
    Collider* owner = self->root03();
    for (ContactRow03* g = owner->contacts->head; g; g = g->next) {
        for (Contact03* it = g->head; it; it = it->next) {
            s32 side = (owner != it->end[0].body);
            Obj_1F5008* near = (Obj_1F5008*)it->end[side].part;
            if (IsObjectDescendantOf(near, self)) {
                ContactEnd03* far = &it->end[1 - side];
                Obj_1F5008* o = (Obj_1F5008*)far->part;
                if (IsObjectOfKind(o, 0x41)) {
                    p = o; Add_1F5008::Of(self, p, &far->v10, &it->v80);
                }
            }
        }
    }
    func_001F5C0C(&tmp, 0, 0x40);
    for (s32 i = 0; i < self->count; i++) {
        Slot36* s = &self->slots[i];
        p = (Obj_1F5008*)s->obj;
        tmp.self = self;
        tmp.obj = p;
        tmp.q20 = *(Vec02*)((u8*)p + 0x140);
        tmp.q30 = *(Vec02*)((u8*)p + 0x150);
        FindNodeForQuery(&tmp, 0, 0);
    }
}

void func_001F51A0(ContactTracker* self) { CopyCollider(self); self->rec.owner = self; }

void func_001F51C8() { func_00125C90(); }

int func_001F51E8(ContactTracker* self) { func_001F57E0(&self->rec); return 1; }

void* func_001F5208(void* self) { return (u8*)self + 0x550; }

void func_001F5210(ContactTracker* self) { self->rec.found = 0; }

void func_001F5218(C37* o) {
    InitContactTracker(o);
    o->flags538 |= ((u64)0x8000 << 28);
    SetColliderAnchors(o, 3, 0, 3, 0);
}

ASM_FUNC(func_001F5268);

void func_001F5590(Rec36* a, ContactTracker* b) { a->owner = b; a->f04 = 0; a->f08 = 150.0f; }

void func_001F55A8(Rec36* self)
{
    Iter_1F55A8 it;
    BaseObject* n;
    s32 i;

    Begin_1F55A8::Of(&it, &self->owner->children);
    while ((n = Next_1F55A8::Of(&it)) != 0) {
        s32 t = n->desc->id;
        if (t == 0x7E || t == 0x6E) {
            if (self->found < 0x20) {
                self->nodes[self->found++] = n;
            }
        }
    }
    for (i = 0; i < self->count; i++) {
        n = FindFirstObjectById(self->owner->world, 0x104, self->keys[i], self->owner);
        if (n != 0) {
            AddTrackedNode(self, n);
        }
    }
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_001F56D8(Ctx_1F56D8* ctx, Player* self)
{
    Frame_1F56D8 f;
    ChooseBestTargetCandidate(self, ctx->s94, (u8*)ctx + 0x98, f.a, &f.f60);
    if (ctx->cnt != 0) {
        ComputeTargetArc(self, f.a, 0.0f, 0, f.b, 0);
        self->desc02()->m1D(self, (Vec02*)f.b);
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        BuildAxisAngleMatrix((Tab_1F56D8*)&g_unitZVector, f.c, self->f638);
        self->desc02()->m1E(self, (Mat02*)f.c);
        SetPlayerState(self, 2, 2);
    } else {
        LaunchPlayerAtTarget(self, f.a, f.f60);
    }
}

void func_001F57E0(Self_57E0* self, void* a1, Out_57E0* out)
{
    GetActiveSwitchedCollider();
    s32 v = self->f4;
    out->f8 = self;
    out->f0 = v;
    out->fC = (void*)func_001F56D8;
    TriggerScriptEvent(self->f0, 2, 0, 0);
}

void func_001F5840(Rec36* self, void* entry) { u32 n = self->count; if (n < 32) { self->keys[n] = entry; self->count = n + 1; } }

void func_001F5868(Rec36* self, Ev_1F5868* e) {
    if (self->found < 0x20) {
        if (IsObjectOfKind(e, 0x7E) || IsObjectOfKind(e, 0x6E) || IsObjectOfKind(e, 0x76) ||
            IsObjectOfKind(e, 0x70) || IsObjectOfKind(e, 0x71) || IsObjectOfKind(e, 0x81)) {
            self->nodes[self->found++] = e;
        }
    }
}

void func_001F5930(Rec36* self, s32 value)
{
    s32 i;
    for (i = 0; i < (s32)self->found; i++) {
        if ((s32)self->nodes[i] == value) {
            break;
        }
    }
    if (i < (s32)self->found) {
        s32* p = (s32*)&self->nodes[i];
        CopyMemory(p, p + 1, ((s32)self->found - i - 1) * 4);
        self->found = (s32)self->found - 1;
    }
}

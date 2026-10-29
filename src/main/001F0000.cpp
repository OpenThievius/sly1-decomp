// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1F0468 { u8 pad[0x19DC]; s32 value; };

extern s32 D_00275BF0;
extern void* D_002623C0;

s32 func_001F0468(void)
{
    if (D_00275BF0 != 2) {
        return ((Obj_1F0468*)D_002623C0)->value;
    }
    return 10;
}

struct Cam_1F0EB8 { u8 pad[0x1C4]; f32 a; f32 b; };

extern Cam_1F0EB8* D_00261990;

void func_00143940(void* p, f32 v);
void func_00125B70(void* obj, void* c, void* out);
void func_00188B08(void* a, void* b, void* out);
void func_00125C90(void* obj, void* s, void* out);

void func_001F0EB8(void* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Cam_1F0EB8* p = D_00261990;
    f32 keep1 = p->a;
    f32 keep2 = p->b;
    func_00143940(p, 1.0f);
    func_00125B70(obj, c, tmp);
    func_00188B08(s + 0x40, s + 0x80, tmp);
    func_00125C90(obj, s, tmp);
    func_00143940(D_00261990, keep1);
    D_00261990->b = keep2;
}

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
        f32 r = func_001F3250(e->x, e->y, e->z);
        num += e->w * r;
        den += e->w;
    }
    f32 t = func_001F3328(num / den, obj->scale);
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
    func_001F38F0(p + 0x30, a, b, c, d);
}

struct __attribute__((packed)) Pair16_1F00C0 {
    u64 lo;
    u64 hi;
};

struct Src_1F00C0 {
    Pair16_1F00C0 pair;
    s32 mid;
};

struct Dst_1F00C0 {
    u8 pad_000[0x28];
    Pair16_1F00C0 pair;
    s32 mid;
    s32 last;
};

void func_001F00C0(Dst_1F00C0* dst, Src_1F00C0* src, s32 last)
{
    s32 mid = src->mid;
    u64 lo = src->pair.lo;
    u64 hi = src->pair.hi;
    dst->pair.lo = lo;
    dst->pair.hi = hi;
    dst->last = last;
    dst->mid = mid;
}

void* func_001F3830(void* self, s32 mode);
void func_001F38F0(void* buf, f32 x, f32 y, f32 z, f32 w);

void func_001F3990(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)func_001F3830(self, 1);
    func_001F38F0(p + 0x80, a, b, c, d);
}

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);

void func_001F3A40(void* self, void* other)
{
    func_00137EB0(other, (u8*)self + 0x50);
    func_00137E70(other, (u8*)self + 0x40);
    func_0011EC40(self, other);
}

struct Obj_1F3A90 { u8 pad[0x18]; void* link; };

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_00182F78(void* self, void* value);

void func_001F3A90(void* self, void* other)
{
    Obj_1F3A90* s = (Obj_1F3A90*)self;
    func_00128018(s->link, other, (u8*)self + 0x40, (u8*)self + 0x40);
    func_00128150(s->link, other, (u8*)self + 0x50, (u8*)self + 0x50);
    func_00182F78(self, other);
}

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);

void func_001F3AF0(void* self, void* other)
{
    u8* p = (u8*)self;
    func_00128018(other, 0, p + 0x40, p + 0x40);
    p += 0x50;
    func_00128150(other, 0, p, p);
}

struct Holder_1F3BD8 {
    u8 pad[0x18];
    void* link;
};

s32 func_00128018(void* a, s32 b, void* c, s32 d);

s32 func_001F3BD8(Holder_1F3BD8* self, s32 arg)
{
    return func_00128018(self->link, 0, (u8*)self + 0x40, arg);
}

struct Holder_1F3C08 {
    u8 pad[0x18];
    void* link;
};

s32 func_00128150(void* a, s32 b, void* c, s32 d);

s32 func_001F3C08(Holder_1F3C08* self, s32 arg)
{
    return func_00128150(self->link, 0, (u8*)self + 0x50, arg);
}

struct Reset_1F2758 { u8 pad0[0x34]; f32 scale34; u8 pad1[0x40 - 0x38]; s32 index40; u8 pad2[0x6D0 - 0x44]; s32 index6D0; };

void func_00182C18(void* self);

void func_001F2758(Reset_1F2758* self)
{
    func_00182C18(self);
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

struct Obj_1F0878 { u8 pad[0x2F4]; s32 field2F4; };

extern u8 D_0026F138[];
void func_001AD0D0(void* list, s32 a, s32 b);
void func_001F18B0(void* self, s32 value);

void func_001F0878(Obj_1F0878* self, s32 value)
{
    if (value == 10) {
        func_001AD0D0(D_0026F138, 0, 4);
    } else {
        u8* base = D_0026F138;
        s32 t = value < 9;
        s32 idx = t ? value : -1;
        func_001AD0D0(base, self->field2F4, idx);
    }
    func_001F18B0(self, value);
}

extern s32 D_00276250;
extern s32 D_00276654;

void func_001F08F0(s32 unused, s32 a, s32 b)
{
    D_00276250 = a;
    D_00276654 = b;
}

f32 func_001F3328(f32 value, f32 denominator)
{
    return value / (1.0f + (1.0f / denominator - 2.0f) * (1.0f - value));
}

struct Object_1F37D8 { u8 pad1[0x38]; s32 state; u8 pad2[0x694]; s32 index; u8 pad3[0x210]; s32 cached; };

void* func_001F37D8(Object_1F37D8* obj, s32 value)
{
    if (obj->state == 0) {
        return 0;
    }
    if (value == 1) {
        obj->cached = value;
    }
    return (u8*)obj + (obj->index * 0xD0 + 0x50);
}

struct Msg_1F0428 { s32 kind; void* obj; void* value; u8 pad; s32 last; };

extern u8 D_00275F80[];

void func_001EFFA0(void* dst, void* args, s32 count);

void func_001F0428(void* obj, void* value, s32 count)
{
    Msg_1F0428 m;
    m.kind = 1;
    m.obj = obj;
    m.value = value;
    m.last = 0;
    func_001EFFA0(D_00275F80, &m, count);
}

extern u8 D_00275F80[];

void func_00127378(void* self, s32 kind, void* msg);
void func_001F0220(void* o, s32 mode);
void func_001F1050(void* self, s32 mode);

struct Obj_1F0F70 { u8 pad0[0x2D0]; s32 f2D0; u8 pad1[8]; s32 f2DC; s32 f2E0; u8 pad2[8]; s32 f2EC; };

void func_001F0F70(Obj_1F0F70* self, s32 kind, void* msg)
{
    func_00127378(self, kind, msg);
    if (kind != 5) return;
    s32 v = self->f2D0;
    if (v == 3) goto L_three;
    if (v >= 4) goto L_ge4;
    if (v == 1) goto L_one;
    return;
L_ge4:
    if (v == 4) goto L_four;
    return;
L_one:
    func_001F1050(self, self->f2E0);
    return;
L_three:
    func_001F0220(D_00275F80, 2);
    return;
L_four:
    if ((s32)msg != self->f2EC) return;
    u8* g = D_00275F80;
    if (*(s32*)(g + 4) == 3) {
        func_001F0220(g, 0);
    }
    func_001F1050(self, 0);
}

void func_001F1050(void* self, s32 mode);

struct Obj_1F1590 { u8 pad0[0x2D0]; s32 f2D0; u8 pad1[8]; s32 f2DC; s32 f2E0; u8 pad2[8]; s32 f2EC; };

void func_001F1590(Obj_1F1590* self, s32 a1, s32 a2)
{
    s32 v = self->f2D0;
    if (v == 2) goto L_two;
    if (v < 3) {
        if (v == 0) goto L_store;
    } else {
        if (v == 4) goto L_store;
    }
    return;
L_store:
    self->f2DC = a1;
    self->f2E0 = a2;
    func_001F1050(self, 1);
    return;
L_two:
    self->f2DC = a1;
    if (a2 == 3) {
        func_001F1050(self, 3);
    }
}

void func_001F1050(void* self, s32 mode);

struct Obj_1F1610 { u8 pad0[0x2D0]; s32 f2D0; };

void func_001F1610(Obj_1F1610* self)
{
    s32 v = self->f2D0;
    if (v < 3) {
        if (v > 0) {
            func_001F1050(self, 4);
        }
    }
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
    func_00137EB0(other, (u8*)self + 0x50);
    func_00137E70(other, (u8*)self + 0x40);
    func_0011EC40(self, other);
    self->count = func_00137D10(other);
    self->arr = (Item_1F3D80**)func_0018D500(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        s32 a = func_00137D10(other);
        s32 b = func_00137D10(other);
        s32 c = func_00137D10(other);
        Item_1F3D80* it = (Item_1F3D80*)func_0011E580(a, self->f14, 0, b, c);
        self->arr[i] = it;
        it->vtbl[14](it, other);
    }
    func_00138518(other);
    self->count2 = func_00137D10(other);
    self->arr2 = (void**)func_0018D500(self->count2 << 2);
    for (s32 i = 0; i < self->count2; i++) {
        self->arr2[i] = (void*)func_00137D10(other);
    }
}

typedef void (*VFn_1F3F80)(void* self, void* arg);
struct Item_1F3F80 { VFn_1F3F80* vtbl; };
struct Obj_1F3F80 { u8 pad0[0x18]; void* f18; u8 pad1[0xA0 - 0x1C]; s32 count; void** arr; };

void func_00182C58(void* self);
void func_00182ED8(void* a);

void func_001F3F80(Obj_1F3F80* self)
{
    func_00182C58(self);
    for (s32 i = 0; i < self->count; i++) {
        Item_1F3F80* item = (Item_1F3F80*)self->arr[i];
        item->vtbl[25](item, self->f18);
        func_00182ED8(item);
    }
}

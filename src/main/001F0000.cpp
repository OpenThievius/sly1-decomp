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

struct Sub_1F1A08 {
    u8 pad0[0x2D0];
    s32 f2D0;
    u8 pad1[0x2DC - 0x2D4];
    s32 f2DC;
    u8 pad2[0x560 - 0x2E0];
    s32 f560;
};

struct Obj_1F1A08 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x30 - 0x18];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad2[0xAA - 0x40];
    u16 fAA;
    u8 pad3[0x250 - 0xAC];
    s32 f250;
    u8 pad4[0x260 - 0x254];
    Sub_1F1A08* f260;
    u8 pad5[0x27C - 0x264];
    f32 f27C;
    f32 f280;
};

struct Pool_1F1A08;
struct Q_1F1A08;
struct Q3_1F1A08;
struct Val_1F1A08;
typedef s32 Key_1F1A08;
typedef s32 Id_1F1A08;

extern f32 D_00261858[];
extern u8 D_00262C70[];
extern u8 D_00275BC0[];
extern f32 D_00275FC0[];
extern u8 D_00276278[];

s32 func_001F0490(Sub_1F1A08* o, s32 n, s32* a, s32* b);
s32 func_0016EC98(Obj_1F1A08* t);
s32 func_0016EED0(Obj_1F1A08* t);
void func_001F1648(Sub_1F1A08* o, s32 n);
void func_0016EC20(Pool_1F1A08* p, s32 n);
s32 func_001F0468(void);
void func_001E9570(Q_1F1A08* q);
Val_1F1A08* func_00160180(Key_1F1A08 k);
void func_001F0428(Val_1F1A08* v, s32 m, s32 n);
void func_001BFCD8(Id_1F1A08 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 func_001EA4B8(Q3_1F1A08* p, s32 a1, f32 f12, f32 f13, f32 f14);

void func_001F1A08(Obj_1F1A08* self, Obj_1F1A08* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->f260 == 0) return;
    if (self->f260->f2D0 != 2) return;
    if (self->f260->f560 != 0) return;
    if ((t->fAA & 0x910) != 0 || t->f14 == 1) {
        func_001E9570((Q_1F1A08*)D_00275BC0);
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x910);
        return;
    }
    if (self->f250 != self->f260->f2D0) return;

    s3 = func_001F0490(self->f260, self->f260->f2DC, &loc[0], &loc[1]);
    s2 = func_0016EC98(t);
    v1 = func_0016EED0(t);
    t->f30 = D_00261858[4] + t->f34;
    t->f38 = D_00261858[4] + t->f3C;

    if (v1 < 0) {
        func_001F1648(self->f260, 0);
    } else if (v1 > 0) {
        func_001F1648(self->f260, 1);
    } else if (s2 < 0) {
        func_001F1648(self->f260, 2);
    } else if (s2 > 0) {
        func_001F1648(self->f260, 3);
    } else if ((t->fAA & 0x40) != 0) {
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x40);
        if (self->f260->f2DC != func_001F0468()) {
            if (s3 != 0) {
                Val_1F1A08* v = func_00160180((loc[0] << 8) | loc[1]);
                self->f260->f560 = 1;
                func_001E9570((Q_1F1A08*)D_00275BC0);
                func_001F0428(v, -1, 2);
            } else {
                func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        } else {
            func_001E9570((Q_1F1A08*)D_00275BC0);
        }
    }

    if (s3 != 0) {
        self->f280 = 1.0f;
    } else {
        self->f280 = D_00275FC0[0];
    }
    self->f27C = func_001EA4B8((Q3_1F1A08*)D_00276278, 0, self->f27C, self->f280, D_00261858[5]);
}

typedef void (*VFn_1F1C90)(void* self);
struct Anim_1F1C90 { u8 pad[0x34]; f32 f34; };
struct Sub_1F1C90 {
    u8 pad0[0x2E4];
    Anim_1F1C90* f2E4;
    Anim_1F1C90* f2E8;
    u8 pad1[0x560 - 0x2EC];
    s32 f560;
};
struct Obj_1F1C90 {
    VFn_1F1C90* vtbl;
    u8 pad0[0x25C - 4];
    s32 f25C;
    Sub_1F1C90* f260;
    u8 pad1[0x27C - 0x264];
    f32 f27C;
    f32 f280;
};
struct Glob_1F1C90 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; };


extern void* D_002623C0;
extern u8 D_00262C70[];
extern u8 D_00275BC0[];

void func_001AA060(void* self);
s32 func_001F0468(void);
s32 func_001F0490(void* o, s32 n, s32* a, s32* b);
void func_001F1590(void* self, s32 a1, s32 a2);
void func_001F1610(void* self);
void func_001AA8B0(void* self, f32 v);
void func_001AA8C0(void* self, f32 v);
void func_001BED48(void);
void func_001BED70(void);
void func_0016E0F0(s32 bits);
void func_0016E118(s32 n);
void func_0016EC88(void* p);
void func_001E96F8(void* obj, s32 mode);


void func_001F1C90(Obj_1F1C90* self, s32 a1)
{
    if ((a1 != 0) != (self->f25C == 0)) return;
    if (a1 != 0) {
        func_001AA060(self);
        s32 r = func_001F0468();
        if (r == 10) {
            r = (func_001F0490(self->f260, 1, 0, 0) != 0);
        }
        func_001F1590(self->f260, r, 2);
        self->f280 = 1.0f;
        self->f27C = 1.0f;
        Anim_1F1C90* an = self->f260->f2E4;
        if (an != 0) {
            func_001AA8B0(self, an->f34);
        }
        Glob_1F1C90* g = (Glob_1F1C90*)D_002623C0;
        if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
            func_001BED48();
        }
        self->vtbl[14](self);
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
        func_001E96F8(D_00275BC0, 7);
    } else {
        self->vtbl[15](self);
        if (self->f260->f560 == 0) {
            func_001F1610(self->f260);
            Anim_1F1C90* an = self->f260->f2E8;
            if (an != 0) {
                func_001AA8C0(self, an->f34);
            }
            func_0016E118(1);
            func_001E96F8(D_00275BC0, 3);
            Glob_1F1C90* g = (Glob_1F1C90*)D_002623C0;
            if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
                func_001BED70();
            }
        }
    }
    self->f25C = a1;
}

struct Obj_1F0580 { u8 pad[0x2F4]; s32 mode; };

s32 func_001F0490(void* self, s32 code, s32 a2, s32 a3);

s32 func_001F0580(void* self, s32 code)
{
    s32 r;
    if (code == 9) {
        return 0;
    }
    r = func_001F0490(self, code, 0, 0);
    if (r == 0) {
        switch (((Obj_1F0580*)self)->mode) {
        case 1:
            if (code >= 2) {
                if (code < 6) {
                    r = func_001F0490(self, 1, 0, 0);
                } else if (code < 8) {
                    r = func_001F0490(self, 9, 0, 0);
                }
            }
            break;
        case 2:
        case 3:
        case 4:
            if (code >= 2) {
                if (code < 5) {
                    r = func_001F0490(self, 1, 0, 0);
                } else if (code < 8) {
                    r = func_001F0490(self, 9, 0, 0);
                }
            }
            break;
        }
    }
    return r;
}

struct __attribute__((packed)) Pair16_1F00F0 {
    u64 lo;
    u64 hi;
};

struct Key_1F00F0 {
    u8 pad_000[8];
    s32 f8;
    u8 pad_00C[0xC];
    s32 f18;
    s32 Same(Key_1F00F0* o)
    {
        if (this == o) {
            return 1;
        }
        if (o == 0) {
            return 0;
        }
        return ((o->f8 ^ o->f18) ^ (f8 ^ f18)) == 0;
    }
};

struct Rec_1F00F0 {
    u8 pad_000[4];
    Key_1F00F0* key;
    u8 pad_008[8];
    s32 flags;
    s32 tail;
};

struct Self_1F00F0 {
    u8 pad_000[0x10];
    Pair16_1F00F0 pair;
    s32 flags;
    s32 tail;
    Pair16_1F00F0 spair;
    s32 mid;
    s32 last;
};

struct Blk20_1F00F0 {
    Pair16_1F00F0 p;
    s32 w;
};

struct Obj_1F00F0 {
    u8 pad_000[0xAA];
    u16 flags;
};

extern void* D_00275710;
extern Key_1F00F0 D_00275B04;

s32 func_001DDA80(void* p);
void func_0016EC20(Obj_1F00F0* o, s32 n);
s32 func_001F0220(Self_1F00F0* self, void* param);

s32 func_001F00F0(Self_1F00F0* self, Obj_1F00F0* o, void* param2)
{
    if (func_001DDA80(D_00275710) != 0 && *(s32*)((u8*)self + 0x28) != 0 && (o->flags & 0x800) != 0) {
        func_0016EC20(o, 0x800);
        *(Blk20_1F00F0*)&self->pair = *(Blk20_1F00F0*)&self->spair;
        self->tail = self->last;
        Rec_1F00F0* rr = (Rec_1F00F0*)&self->pair;
        Key_1F00F0* kk = rr->key;
        if (kk == 0 || kk->Same(&D_00275B04)) {
            rr->flags |= 8;
        } else {
            rr->flags &= ~8;
        }
        func_001F0220(self, param2);
        return 1;
    }
    return 0;
}

struct Obj_1F0220 {
    u8 pad0[0x4];
    s32 f4;
    f32 f8;
    union { s32 i; f32 f; } fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
};

struct Quint_1F0220 { s32 a; s32 b; s32 c; s32 d; s32 e; };
struct Tbl_1F0220 { u8 pad0[0x260]; void* f260; void* f264[1]; };
struct Sub_1F0220 { u8 pad0[0x2E0]; s32 f2E0; };

extern u8 D_00275AF0[];
extern u8 D_00275BC0[];
extern Tbl_1F0220 D_0026F808;
extern void* D_0026FA68;
extern void* D_00275710;
extern s32 D_00275BF0;
extern s32 D_002623CC;
extern f32 D_00261868;

void func_001E4E80(void* a, s32 b, s32 c, s32 d, s32 e);
void func_001E96F8(void* obj, s32 mode);
s32 func_001601A0(s32 a);
void func_001F1590(void* self, s32 a1, s32 a2);
void func_001F1050(void* self, s32 mode);
void func_001DDB58(void* a);
void func_00168B68(f32 t);

void func_001F0220(Obj_1F0220* self, s32 mode)
{
    if (self->f4 == mode) goto L0410;
    if (self->f4 == 2) {
        if (D_0026FA68 != 0) {
            func_001F1050(D_0026FA68, 0);
        }
    }
    if (mode == 1) goto L02E0;
    if (mode < 2) {
        if (mode == 0) {
            self->fC.i = 0;
            goto L0400;
        }
        self->f4 = mode;
        goto L0404;
    }
    if (mode == 2) goto L02A0;
    if (mode == 3) goto L0374;
    self->f4 = mode;
    goto L0404;

L02A0:
    if (self->f10 != 0) {
        Quint_1F0220* q = (Quint_1F0220*)((u8*)self + 0x10);
        func_001E4E80(D_00275AF0, q->b, q->c, q->d, q->e);
    }
    self->f10 = 0;
    self->fC.f = 1.0f;
    self->f28 = 0;
    goto L0400;

L02E0:
    {
        s32 v = self->f24;
        if (v == 2) goto L0300;
        if (v == 3) goto L0354;
        goto L0364;
    }

L0300:
    {
        s32 v = func_001601A0(self->f14);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (D_0026FA68 == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        func_001F1590(D_0026FA68, a1, 3);
        func_001DDB58(D_00275710);
        goto L0364;
    }

L034C:
    self->f24 = 0;
    goto L0364;

L0354:
    mode = 2;
    goto L02A0;

L0364:
    func_001E96F8(D_00275BC0, 8);
    self->f4 = mode;
    goto L0404;

L0374:
    {
        s32 a = self->f24;
        if (a == 2) goto L038C;
        if (a == mode) goto L03EC;
        self->f4 = mode;
        goto L0404;
    }

L038C:
    {
        if (self->f24 == D_00275BF0) {
            s32 idx = D_002623CC;
            if (idx != -1) {
                D_0026F808.f260 = D_0026F808.f264[idx];
            }
        }
        if (D_0026F808.f260 != 0) {
            ((Sub_1F0220*)D_0026F808.f260)->f2E0 = 3;
            func_001F1050(D_0026F808.f260, 4);
            self->f4 = mode;
            goto L0404;
        }
        self->f24 = 3;
        goto L0400;
    }

L03EC:
    func_00168B68(0.25f);
    self->f24 = 0;
    goto L0400;

L0400:
    self->f4 = mode;
L0404:
    self->f8 = D_00261868;
L0410:
    return;
}

// EXACT: callee declared s32, called as (void)

struct Cfg_1F2688 { u8 pad0[4]; u8 kind; u8 pad5[3]; f32 f8; f32 fC; f32 f10; f32 f14; s32 f18; };

extern u8 D_00276620[];
extern f32 D_00276648;
extern f32 D_00276650;

s32 func_001F5C0C(Cfg_1F2688* p, s32 zero, s32 size);

void func_001F2688(s32 a0, s32 a1)
{
    if (a1 != 0xFFFF) return;
    if (a0 == 0) return;
    Cfg_1F2688* c = (Cfg_1F2688*)D_00276620;
    (void)func_001F5C0C(c, 0, 0x1C);
    c->f18 = (s32)0xFF7D4B00;
    D_00276650 = D_00276648 * 0.75f;
    c->f8 = 2.0f;
    c->fC = 1.0f;
    c->f10 = 0.3f;
    c->f14 = 0.3f;
    c->kind = 0x3D;
}

struct Obj_1F3810;

void* func_001F37D8(Obj_1F3810* self, s32 mode, s32 flag);

void* func_001F3810(Obj_1F3810* self, s32 mode)
{
    return func_001F37D8(self, mode, 0);
}

extern u8 D_00248D30[];

struct __attribute__((aligned(16))) Quad_1F18B0 { s32 a, b, c, d; };
struct Mgr_1F18B0;
struct Loc_1F18B0;
struct Obj_1F18B0;
struct Rec_1F18B0 {
    u8 pad00[0x18];
    Mgr_1F18B0* f18;
    u8 pad1C[0x24];
};
void func_00128018(Mgr_1F18B0* a0, Obj_1F18B0* a1, void* a2, Loc_1F18B0* a3);

void func_001F18B0(Obj_1F18B0* self, s32 idx) {
    u8* base = (u8*)self;
    if (*(s32*)(base + 0x534) == idx) {
        return;
    }
    Rec_1F18B0* r = *(Rec_1F18B0**)(base + idx * 0x34 + 0x30C);
    if (r != 0) {
        func_00128018(r->f18, self, (u8*)r + 0x40, (Loc_1F18B0*)(base + 0x550));
    } else {
        *(Quad_1F18B0*)(base + 0x550) = *(Quad_1F18B0*)D_00248D30;
    }
    u8* arr = base + 0x320;
    u8* slot = arr + idx * 0x34;
    *(s32*)slot = 0;
    s32 old = *(s32*)(base + 0x534);
    if (old != -1) {
        *(f32*)(arr + old * 0x34) = 1.0f;
    }
    *(s32*)(base + 0x534) = idx;
}

extern u8 D_00276620[];
extern u8 D_0024E808[];

struct Clr_1F1960 { s32 a, b, c, d, e, f; };
struct Obj_1F1960;
typedef void (*VFn_1F1960)(Obj_1F1960* self, void* arg);
struct Obj_1F1960 {
    VFn_1F1960* vtbl;
    u8 pad004[0x204];
    u32 f208;
    u8 pad20C[0x4];
    u32* f210;
    u8 pad214[0x4C];
    u32 f260;
};

void func_001AA268(Obj_1F1960* self);
s32 func_0015C188(s32 n);
u32 func_0015C1C0(s32 n);
void func_001AA8B8(Obj_1F1960* self, f32 v);
void func_001AA788(Obj_1F1960* self, f32 v);
void func_001F5C0C(Clr_1F1960* p, s32 v, s32 size);

void func_001F1960(Obj_1F1960* self) {
    func_001AA268(self);
    if (func_0015C188(2) != 0) {
        self->f210 = (u32*)D_00276620;
        *self->f210 = func_0015C1C0(2);
    }
    func_001AA8B8(self, 0.0f);
    func_001AA788(self, 0.6f);
    self->f208 = 0xDF7F7F7F;
    self->vtbl[8](self, D_0024E808);
    self->f260 = 0;
    func_001F5C0C((Clr_1F1960*)((u8*)self + 0x264), 0, 0x18);
}

extern u8 D_00248D00[];

struct __attribute__((aligned(16))) Quad_1F36E8 { s32 a, b, c, d; };

struct Node_1F36E8 {
    s32 f0;
    s32 f4;
    u8 pad8[0x8];
    Quad_1F36E8 q10;
    u8 pad20[0x40];
    s32 f60;
};

struct Obj_1F36E8 {
    u8 pad0[0x38];
    s32 f38;
    s32 f3C;
    s32 f40;
    u8 pad44[0x6D0 - 0x44];
    s32 f6D0;
};

void func_001F36E8(Obj_1F36E8* o)
{
    s32 n = o->f38;
    s32 off;
    Node_1F36E8* node;

    o->f38 = n + 1;
    o->f6D0 = o->f6D0 + 1;
    off = n * 0xD0;
    off += 0x50;
    node = (Node_1F36E8*)((u8*)o + off);
    node->f0 = 0;
    node->q10 = *(Quad_1F36E8*)D_00248D00;
    if (o->f40 >= 0) {
        node->f4 = o->f40;
        o->f40 = -1;
        node->f60 = 2;
    } else {
        s32 v = o->f3C;
        node->f4 = v;
        v++;
        o->f3C = v;
        o->f40 = node->f4;
        node->f60 = 0;
    }
}

struct __attribute__((aligned(16))) Blk_1F39F8 { u8 b[48]; };
struct Self_1F39F8 { u8 pad[0x50]; };
extern u8 D_002483D0[];
void func_00182C18(Self_1F39F8* self);

void func_001F39F8(Self_1F39F8* self)
{
    func_00182C18(self);
    u8* dst = (u8*)self + 0x50;
    *(Blk_1F39F8*)dst = *(Blk_1F39F8*)D_002483D0;
}

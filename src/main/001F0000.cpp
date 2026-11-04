// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c73.h"
#include "c67.h"
#include "c8d.h"
#include "list_iter.h"
#include "t217d.h"

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

void func_001F0EB8(C67* obj, u8* s, void* c)
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

void func_001F3A40(C73* self, void* stream)
{
    func_00137EB0(stream, &self->rot);
    func_00137E70(stream, &self->pos);
    func_0011EC40(self, stream);
}

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_00182F78(void* self, void* value);

void func_001F3A90(C73* self, C01* other)
{
    func_00128018(self->parent, other, &self->pos, &self->pos);
    func_00128150(self->parent, other, &self->rot, &self->rot);
    func_00182F78(self, other);
}

void func_001F3AF0(C73* self, C01* other)
{
    func_00128018(other, 0, &self->pos, &self->pos);
    func_00128150(other, 0, &self->rot, &self->rot);
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

void func_00182C18(void* self);

void func_001F2758(C8D* self)
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

void func_001AD0D0(T217D_3D0* self, s32 a, s32 b);
void func_001F18B0(void* self, s32 value);

void func_001F0878(Obj_1F0878* self, s32 value)
{
    if (value == 10) {
        func_001AD0D0(&D_0026F138, 0, 4);
    } else {
        T217D_3D0* base = &D_0026F138;
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

void func_001F0F70(C67* self, s32 kind, void* msg)
{
    func_00127378(self, kind, msg);
    if (kind != 5) return;
    s32 v = self->mode;
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

// The pad (include/c73.h's neighbours): its buttons at +0xAA, its direction timers at +0x30 .. 0x3C.
struct Pad_1F1A08 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x30 - 0x18];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad2[0xAA - 0x40];
    u16 fAA;
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
f32 D_00275FC0 = 0.5f;
extern u8 D_00276278[];

s32 func_001F0490(Sub_1F1A08* o, s32 n, s32* a, s32* b);
s32 func_0016EC98(Pad_1F1A08* t);
s32 func_0016EED0(Pad_1F1A08* t);
void func_001F1648(Sub_1F1A08* o, s32 n);
void func_0016EC20(Pool_1F1A08* p, s32 n);
s32 func_001F0468(void);
void func_001E9570(Q_1F1A08* q);
Val_1F1A08* func_00160180(Key_1F1A08 k);
void func_001F0428(Val_1F1A08* v, s32 m, s32 n);
void func_001BFCD8(Id_1F1A08 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 func_001EA4B8(Q3_1F1A08* p, s32 a1, f32 f12, f32 f13, f32 f14);

void func_001F1A08(T217D_0F0* self, Pad_1F1A08* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->current == 0) return;
    if (((Sub_1F1A08*)self->current)->f2D0 != 2) return;
    if (((Sub_1F1A08*)self->current)->f560 != 0) return;
    if ((t->fAA & 0x910) != 0 || t->f14 == 1) {
        func_001E9570((Q_1F1A08*)D_00275BC0);
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x910);
        return;
    }
    if (self->mode != ((Sub_1F1A08*)self->current)->f2D0) return;

    s3 = func_001F0490((Sub_1F1A08*)self->current, ((Sub_1F1A08*)self->current)->f2DC, &loc[0], &loc[1]);
    s2 = func_0016EC98(t);
    v1 = func_0016EED0(t);
    t->f30 = D_00261858[4] + t->f34;
    t->f38 = D_00261858[4] + t->f3C;

    if (v1 < 0) {
        func_001F1648((Sub_1F1A08*)self->current, 0);
    } else if (v1 > 0) {
        func_001F1648((Sub_1F1A08*)self->current, 1);
    } else if (s2 < 0) {
        func_001F1648((Sub_1F1A08*)self->current, 2);
    } else if (s2 > 0) {
        func_001F1648((Sub_1F1A08*)self->current, 3);
    } else if ((t->fAA & 0x40) != 0) {
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x40);
        if (((Sub_1F1A08*)self->current)->f2DC != func_001F0468()) {
            if (s3 != 0) {
                Val_1F1A08* v = func_00160180((loc[0] << 8) | loc[1]);
                ((Sub_1F1A08*)self->current)->f560 = 1;
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
        self->scaleTarget = 1.0f;
    } else {
        self->scaleTarget = D_00275FC0;
    }
    self->scale = func_001EA4B8((Q3_1F1A08*)D_00276278, 0, self->scale, self->scaleTarget, D_00261858[5]);
}

struct Anim_1F1C90 { u8 pad[0x34]; f32 f34; };
struct Sub_1F1C90 {
    u8 pad0[0x2E4];
    Anim_1F1C90* f2E4;
    Anim_1F1C90* f2E8;
    u8 pad1[0x560 - 0x2EC];
    s32 f560;
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


void func_001F1C90(T217D_0F0* self, s32 a1)
{
    if ((a1 != 0) != (self->open == 0)) return;
    if (a1 != 0) {
        func_001AA060(self);
        s32 r = func_001F0468();
        if (r == 10) {
            r = (func_001F0490(((Sub_1F1C90*)self->current), 1, 0, 0) != 0);
        }
        func_001F1590(((Sub_1F1C90*)self->current), r, 2);
        self->scaleTarget = 1.0f;
        self->scale = 1.0f;
        Anim_1F1C90* an = ((Sub_1F1C90*)self->current)->f2E4;
        if (an != 0) {
            func_001AA8B0(self, an->f34);
        }
        Glob_1F1C90* g = (Glob_1F1C90*)D_002623C0;
        if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
            func_001BED48();
        }
        self->vt->m14(self);
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
        func_001E96F8(D_00275BC0, 7);
    } else {
        self->vt->m15(self);
        if (((Sub_1F1C90*)self->current)->f560 == 0) {
            func_001F1610(((Sub_1F1C90*)self->current));
            Anim_1F1C90* an = ((Sub_1F1C90*)self->current)->f2E8;
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
    self->open = a1;
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
struct Sub_1F0220 { u8 pad0[0x2E0]; s32 f2E0; };

extern u8 D_00275AF0[];
extern u8 D_00275BC0[];
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
                D_0026F808.current = D_0026F808.nodes[idx];
            }
        }
        if (D_0026F808.current != 0) {
            ((Sub_1F0220*)D_0026F808.current)->f2E0 = 3;
            func_001F1050(D_0026F808.current, 4);
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

extern Cfg_1F2688 D_00276620;
extern f32 D_00276648;
extern f32 D_00276650;

s32 func_001F5C0C(Cfg_1F2688* p, s32 zero, s32 size);

void func_001F2688(s32 a0, s32 a1)
{
    if (a1 != 0xFFFF) return;
    if (a0 == 0) return;
    Cfg_1F2688* c = &D_00276620;
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

extern Cfg_1F2688 D_00276620;
extern const char D_0024E808[40];

struct Clr_1F1960 { s32 a, b, c, d, e, f; };
s32 func_0015C188(s32 n);
V24A2* func_0015C1C0(s32 n);
void func_001F5C0C(Clr_1F1960* p, s32 v, s32 size);

void func_001F1960(T217D_0F0* self) {
    func_001AA268(self);
    if (func_0015C188(2) != 0) {
        self->frame = (V24A2**)&D_00276620;
        *self->frame = func_0015C1C0(2);
    }
    func_001AA8B8(self, 0.0f);
    func_001AA788(self, 0.6f);
    self->color = 0xDF7F7F7F;
    self->vt->m08(self, D_0024E808);
    self->current = 0;
    func_001F5C0C((Clr_1F1960*)self->nodes, 0, 0x18);
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

extern u8 D_002483D0[];
void func_00182C18(C01* self);

void func_001F39F8(C73* self)
{
    func_00182C18(self);
    Mat3_73* dst = &self->rot;
    *dst = *(Mat3_73*)D_002483D0;
}

// NEAR: the two counter increments (0x38 and 0x6D0) are computed in the reverse
// order of retail (addiu v0 before addiu v1); no statement order tried changed it.

struct __attribute__((aligned(16))) Quad_001F3768 { s32 w[4]; };
struct Entry_001F3768 {
    s32 a;
    u8 pad0[0x0C];
    Quad_001F3768 q10;
    Quad_001F3768 q20;
    u8 pad1[0x08];
    f32 f38;
    u8 pad2[0x4C];
    f32 f88;
};
struct Obj_001F3768 {
    u8 pad0[0x38];
    s32 n38;
    s32 n3C;
    u8 pad1[0x6D0 - 0x40];
    s32 n6D0;
};

extern Quad_001F3768 D_00248D10;
extern Quad_001F3768 D_00248D20;

void func_001F3768(Obj_001F3768* self)
{
    s32 n6 = self->n6D0;
    s32 idx = self->n38;
    Entry_001F3768* e = (Entry_001F3768*)((u8*)self + 0x50 + 0xD0 * idx);
    n6 = n6 + 1;
    idx = idx + 1;
    self->n38 = idx;
    self->n6D0 = n6;
    e->a = 1;
    e->q10 = D_00248D10;
    e->q20 = D_00248D20;
    e->f38 = 0.5f;
    e->f88 = 0.5f;
    self->n3C = self->n3C + 1;
}

f32 func_001F31F8(s32 a0)
{
    s32 n = a0;
    n ^= n << 13;
    n = n * (n * n * 0x3D73 + 0xC0AE5) + 0x5208DD0D & 0x7FFFFFFF;
    return (f32)n * 4.656612873077393e-10f;
}

struct Glob_1F0660 {
    u8 pad[0x19D8];
    s32 val;
};
struct __attribute__((packed)) Ptr_1F0660 { C67* p; };
extern void func_00124A48(C67* o);

void func_001F0660(C67* o) {
    func_00124A48(o);
    o->flags = (o->flags & ~(3UL << 40)) | (1UL << 40);
    if (((Glob_1F0660*)D_002623C0)->val) {
        u8* t = (u8*)&D_0026F808;
        ((Ptr_1F0660*)(t + 0x260))->p = o;
    }
    switch (o->id) {
    case 0x1C7: o->slot = 1; break;
    case 0x1C8: o->slot = 2; break;
    case 0x1C9: o->slot = 3; break;
    case 0x1C6: o->slot = 4; break;
    case 0x1CA: o->slot = 5; break;
    default: o->slot = ((Glob_1F0660*)D_002623C0)->val; break;
    }
    D_0026F808.nodes[o->slot] = o;
}

struct Rec_1F1050 { s32 f0; f32 f4; s32 f8; };
struct Sub_1F1050 {
    void (**vtbl)(Sub_1F1050*);
    u8 pad04[0x30];
    f32 f34;
    u8 pad38[0x298 - 0x38];
    Rec_1F1050* f298;
};
struct Slot_1F1050 {
    Sub_1F1050* f00;
    Sub_1F1050* f04;
    f32 f08;
    Sub_1F1050* f0C;
    f32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    s32 f30;
};
struct Quad_1F1050 { u64 a; u64 b; } __attribute__((aligned(16)));
struct Ptr_1F1050;
struct Obj_1F1050 {
    void (**vtbl)(Obj_1F1050*);
    u8 pad04[0x2CC];
    s32 f2D0;
    f32 f2D4;
    s32 f2D8;
    s32 f2DC;
    s32 f2E0;
    Sub_1F1050* f2E4;
    Sub_1F1050* f2E8;
    void* f2EC;
    void* f2F0;
    u8 pad2F4[4];
    Slot_1F1050 slot[11]; // 0x2F8
    s32 f534;
    u8 pad538[8];
    Quad_1F1050 f540;
    Quad_1F1050 f550;
    s32 f560;
    Ptr_1F1050* f564;
};

extern f32 D_00261858[];

s32 func_001F0468(void);
s32 func_001F0490(Obj_1F1050* o, s32 n, s32* a, s32* b);
s32 func_001F0580(Obj_1F1050* o, s32 n);
void func_001F0878(Obj_1F1050* o, s32 n);
void func_001F0908(Obj_1F1050* o);
void func_001F18B0(Obj_1F1050* o, s32 n);
void func_001BF788(Ptr_1F1050* p, s32 n);
void func_00159C28(Rec_1F1050* r);
void func_00126C58(Sub_1F1050* o);
void func_0012C918(Sub_1F1050* a, Obj_1F1050* b, s32 c, void* d, f32 e, f32 f);
void func_001BFCD8(s32 a0, Ptr_1F1050** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001F1050(Obj_1F1050* self, u32 next)
{
    s32 i;
    Sub_1F1050* t;
    s32 cur = self->f2D0;
    if (cur == (s32)next) {
        return;
    }
    switch (cur) {
    case 1:
    case 4:
        func_001BF788(self->f564, 0);
        break;
    case 2:
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
        }
        for (s32 k = 0; k < 11; k++) {
            self->slot[k].f28 = 0;
        }
        break;
    case 0: {
        f32 one = 1.0f;
        self->vtbl[6](self);
        for (s32 n = 0; n < 11; n++) {
            Slot_1F1050* s = &self->slot[n];
            if (func_001F0490(self, n, (s32*)0, (s32*)0)) {
                s->f08 = one;
                s32 want;
                if (self->f2E0 == 3) {
                    want = func_001F0468();
                } else {
                    want = self->f2DC;
                }
                if (n == want) {
                    s->f10 = one;
                } else {
                    s->f10 = 0;
                }
            } else {
                s->f10 = 0;
                s->f08 = 0;
            }
        }
        *(f32*)((u8*)self + 0x4DC) = *(f32*)((u8*)self + 0x33C);
        for (s32 j = 0; j <= 10; j++) {
            Slot_1F1050* s = &self->slot[j];
            Sub_1F1050* a = s->f04;
            Sub_1F1050* b = s->f0C;
            if (a) {
                a->vtbl[6](a);
                func_00126C58(a);
                a->f298->f8 = 0;
                a->f298->f4 = s->f08;
            }
            if (b) {
                b->vtbl[6](b);
                func_00126C58(b);
                b->f298->f8 = 0;
                b->f298->f4 = s->f10;
            }
        }
        break;
    }
    }
    switch (next) {
    case 1: {
        if (self->f2E0 == 3) {
            s32 ne = self->f2DC != 1;
            Sub_1F1050* a;
            s32 off;
            if (ne) {
                off = self->f2DC * 52;
            } else {
                off = func_001F0468() * 52;
            }
            a = *(Sub_1F1050**)((u8*)self + off + 0x2F8);
            if (a) {
                f32 fa = 0;
                if (ne) {
                    fa = a->f34;
                }
                func_0012C918(a, self, 0, &self->f2F0, fa, 0.0f);
            }
        } else {
            Sub_1F1050* a = self->slot[1].f00;
            if (a) {
                func_0012C918(a, self, 0, &self->f2F0, 0.0f, 0.0f);
            }
            f32 z = 0.0f;
            func_001F18B0(self, self->f2DC);
            self->f540 = self->f550;
            func_001F0878(self, self->f2DC);
            func_001AA8B8(&D_0026F138, z);
            D_0026F138.vt->m14(&D_0026F138);
            func_001BFCD8(0x8A, &self->f564, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
            for (i = 0; i < 11; i++) {
                Slot_1F1050* s = &self->slot[i];
                s32 r = func_001F0580(self, i);
                s->f1C = r;
                s32 v = 0;
                if (r != 0 && ((u32)(i - 2) < 6 || i == 0)) {
                    v = 1;
                }
                s->f20 = v;
                s->f24 = s->f28 = 0.0f;
            }
        }
        self->f2D8 = self->f2DC;
        t = self->f2E4;
        if (t != 0) {
            goto L146C;
        }
        goto Lz;
    }
    case 4: {
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
            if (self->f2E0 == 2) {
                func_001BFCD8(0x8B, &self->f564, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
        func_001F0908(self);
        t = self->f2E8;
        if (t == 0) {
            goto Lz;
        }
    L146C:
        func_0012C918(t, self, 0, &self->f2EC, 0.0f, 1.0f);
        self->f2D0 = next;
        goto L1550;
    }
    case 2:
        for (s32 m = 0; m < 11; m++) {
            if (m != self->f534) {
                self->slot[m].f28 = 1.0f;
            }
        }
        self->f2D0 = next;
        goto L1550;
    case 3:
        self->f2D8 = -1;
        break;
    case 0:
        for (i = 0; i < 11; i++) {
            Sub_1F1050* a = self->slot[i].f04;
            Sub_1F1050* b = self->slot[i].f0C;
            if (a) {
                if (a->f298) {
                    func_00159C28(a->f298);
                }
                a->vtbl[7](a);
            }
            if (b) {
                if (b->f298) {
                    func_00159C28(b->f298);
                }
                b->vtbl[7](b);
            }
        }
        break;
    default:
        break;
    }
L154C:
    self->f2D0 = next;
L1550:
    self->f2D4 = D_00261858[4];
    return;
Lz:
    next = 0;
    goto L154C;
}

struct Tbl_1F3EE0 { u8 pad0[0x14]; s32 f14; u8 pad1[0xA0 - 0x18]; s32 count; s32* arr; };

void func_001830D8(Tbl_1F3EE0* self, Tbl_1F3EE0* other);
s32 func_00183058(s32 a, s32 b, s32 c);

void func_001F3EE0(Tbl_1F3EE0* self, Tbl_1F3EE0* other)
{
    func_001830D8(self, other);
    self->arr = (s32*)func_0018D500(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        self->arr[i] = func_00183058(other->arr[i], self->f14, 0);
    }
}

extern f32 D_0026185C;

f32 func_001F31F8(s32 i);

f32 func_001F3250(f32 x, f32 y, f32 z)
{
    f32 t = (x + x) * D_0026185C + y;
    s32 i = (s32)t;
    f32 a = func_001F31F8(i);
    f32 b = func_001F31F8(i + 1);
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

struct Obj_1F0490 { u8 pad0[0x2F4]; s32 f2F4; };

extern s32 D_00275FC8[6];
extern void* D_002623C0;

s32 func_001F0490(Obj_1F0490* self, s32 kind, s32* outA, s32* outB)
{
    s32 flag = 0;
    s32 sel;
    s32 idx;
    if (kind == 10) {
        sel = 0;
        idx = 4;
        flag = 1;
    } else {
        s32 mode = self->f2F4;
        s32 allowed = 1;
        if (mode == 5 && (kind == 1 || kind == 7)) {
            allowed = 0;
        }
        if (kind == 9) {
            if (allowed != 0) {
                s32 m = mode * 0x44C;
                if (*(s32*)((u8*)D_002623C0 + m + 0x88) & 1) {
                    u8* p = (u8*)D_002623C0 + 0x458;
                    s32 q = *(s32*)(p + m);
                    flag = (q & D_00275FC8[mode]) != 0;
                }
            }
        } else {
            s32 c = kind < 9;
            idx = -1;
            if (c) {
                idx = kind;
            }
            sel = mode;
            flag = 0;
            if (allowed != 0) {
                flag = *(s32*)((u8*)D_002623C0 + (sel * 0x44C + idx * 0x78) + 0x10) & 1;
            }
        }
    }
    if (outA != 0) {
        *outA = sel;
    }
    if (outB != 0) {
        *outB = idx;
    }
    return flag;
}

struct Ent_275FE0 { s32 a, b, c; };
extern Ent_275FE0 D_00275FE0[52];

struct Node_1F0758;
struct Iter_1F0758 { List01* list; u8* link; s32 offset; Iter_1F0758* saved; };


void func_001249A8(C67* self);
void func_00124DF8(C67* self, s32 n, void* table);
void func_00182ED8(Node_1F0758* node);
f32 func_001EAAE0(f32 a, f32 b);

struct Next_1F0758 {
    static Node_1F0758* Of(Iter_1F0758* it)
    {
        Node_1F0758* obj = *(Node_1F0758**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_1F0758 {
    static void Of(Iter_1F0758* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_1F0758*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void func_001F0758(C67* self)
{
    Iter_1F0758 it;
    Node_1F0758* node;
    Elem67* el;
    s32 i;

    func_001249A8(self);
    func_00124DF8(self, 0x34, D_00275FE0);
    Begin_1F0758::Of(&it, &self->children);
    while ((node = Next_1F0758::Of(&it)) != 0) {
        func_00182ED8(node);
    }
    el = self->elems;
    for (i = 0; i < 11; i++) {
        f32 zero = 0.0f;
        el->f28 = zero;
        el->f24 = zero;
        el->f2C = func_001EAAE0(zero, 6.2831855f);
        el->f30 = func_001EAAE0(0.5f, 0.7f);
        el++;
    }
    self->f534 = -1;
    D_0027B314 = (ListFrame*)it.saved;
}

struct Ent_1F3C38 { u8 pad0[0x90]; s32 f90; s32 f94; u8 pad98[0xB0 - 0x98]; s32 fB0; };
struct Mode_1F3C38 { u8 pad0[4]; s32 f4; u8 pad8[0x24 - 8]; s32 f24; };
struct Host_1F3C38;


Ent_1F3C38* func_0015A418(Host_1F3C38* host, s32 kind, s32 id, Ent_1F3C38* ctx);
s32 func_0015A4F0(Host_1F3C38* host, s32 kind, s32 a2, s32 a3, s32 max, Ent_1F3C38** out);

struct Min_1F3C38 {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

Ent_1F3C38* func_001F3C38(s32 id, s32 parent)
{
    Ent_1F3C38* found = 0;
    Ent_1F3C38* buf[64];
    Ent_1F3C38* other;
    Ent_1F3C38* any;
    s32 n;
    s32 i;

    if (id != -1) {
        found = func_0015A418((*(Host_1F3C38**)&D_00275710), 0x101, id, func_0015A418((*(Host_1F3C38**)&D_00275710), 0x101, parent, 0));
    }
    if (found == 0) {
        any = 0;
        other = 0;
        n = func_0015A4F0((*(Host_1F3C38**)&D_00275710), 0x205, 0x74, 0, 0x100, buf);
        n = Min_1F3C38::Of(n, 0x40);
        for (i = 0; i < n; i++) {
            Ent_1F3C38* e = buf[i];
            if (id != -1 && id == e->fB0) {
                found = e;
                break;
            }
            if ((*(Mode_1F3C38*)&D_00275F80).f4 != 0 && (*(Mode_1F3C38*)&D_00275F80).f24 == 2 && e->f94 != 0) {
                other = e;
            }
            if (e->f90 != 0) {
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

struct Ent_1F1648 { s32 f0; u8 rest[0x30]; };
struct Obj_1F1648 { u8 pad0[0x2DC]; s32 f2DC; u8 pad1[0x2F4 - 0x2E0]; s32 f2F4; u8 pad2[0x314 - 0x2F8]; Ent_1F1648 ents[1]; };

extern u8 D_00276298[], D_00276348[], D_002763F8[], D_002764A8[], D_00276558[];
extern s32 (*D_00276608[6])[4];

void func_001F1590(Obj_1F1648* self, s32 e, s32 n);
enum Sound_1F1648 { SOUND_1F1648_OK = 0x79, SOUND_1F1648_FAIL = 0x7B };
void func_001BFCD8(Sound_1F1648 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001F1648(Obj_1F1648* self, s32 idx)
{
    s32 (*table)[4] = D_00276608[self->f2F4];
    if (table == 0) {
        func_001BFCD8(SOUND_1F1648_FAIL, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s32 e = table[self->f2DC][idx];
    while (e != -1 && self->ents[e].f0 == 0) {
        e = table[e][idx];
    }
    if (e != -1 && self->ents[e].f0 != 0) {
        func_001F1590(self, e, 2);
        func_001BFCD8(SOUND_1F1648_OK, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        func_001BFCD8(SOUND_1F1648_FAIL, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
}

struct Ent_1F0908 { s32 a; s32 type; s32 id; s32 d; };
struct Tbl_1F0908 { u8 pad0[0x54]; s32 count; Ent_1F0908* ents; };
struct Slot_1F0908 { u8 pad0[0x34]; f32 f34; };
struct Body_1F0908;
typedef void (*BodyFn_1F0908)(Body_1F0908* b);
struct BodyVt_1F0908 { u8 pad[0x18]; BodyFn_1F0908 fn; };
struct Body_1F0908 { BodyVt_1F0908* vt; };
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
struct Cfg_1F0908 { u8 pad[0x19D8]; s32 hi; s32 lo; };

extern s32 D_00276250;
extern s32 D_00276654;

void func_0012C918(Slot_1F0908* s, Obj_1F0908* o, s32 c, void* d, f32 a, f32 b);
Body_1F0908* func_0015A418(void* o, s32 a, s32 b, Obj_1F0908* c);

void func_001F0908(Obj_1F0908* self)
{
    if (D_00276250 == -1) return;
    func_001AA8B8(&D_002721D0, (((*(Cfg_1F0908**)&D_002623C0)->hi << 8) | (*(Cfg_1F0908**)&D_002623C0)->lo) == 4 ? 0.5f : 2.0f);
    D_002721D0.vt->m16(&D_002721D0, 2);
    T217D_3D0* e = &D_0026F138;
    e->pending = 0;
    e->vt->m16(e, 0);
    func_001AD0D0(e, (*(Cfg_1F0908**)&D_002623C0)->hi, (*(Cfg_1F0908**)&D_002623C0)->lo);
    e->announce = 1;
    func_001AA8B8(e, 0.0f);
    e->vt->m16(e, 2);
    Slot_1F0908* sl = self->slots[D_00276250].s;
    if (sl != 0) {
        f32 f = 0.0f;
        if (D_00276654 == 0) f = sl->f34;
        func_0012C918(sl, self, 0, self->f2F0, f, 0.0f);
    }
    if (self->tbl != 0) {
        for (s32 i = 0; i < self->tbl->count; i++) {
            Ent_1F0908* en = &self->tbl->ents[i];
            if (en->type == 10) {
                Body_1F0908* n = func_0015A418(self->f14, 0x104, en->id, self);
                if (n != 0) n->vt->fn(n);
            }
        }
    }
    D_00276250 = -1;
}

extern u8 D_00262280[];

struct Frame_1F1E38;
struct Stream_1F1E38;
struct Locals_1F1E38 { s32 k; s32 pad[3]; f32 x; f32 y; };

void func_001613C0(Frame_1F1E38* f, s32 a, s32 b, s32 c);
void func_00161708(Frame_1F1E38* f, u64 a, u64 b);
void func_00161458(Stream_1F1E38* self, u32 value);
void func_001615F0(Stream_1F1E38* self, u32 a1, u32 a2, u32 a3, u32 a4);
f32 func_001EA408(f32 a);
void func_001EAD88(f32 angle, f32* a, f32* b);

void func_001F1E38(f32 cx, f32 cy, f32 radius, f32 angle, s32 n, s32* c1, s32* c2, s32 flags)
{
    Locals_1F1E38 loc;
    s32 i;
    f32 step = 6.2831855f / (f32)n;
    func_001613C0((Frame_1F1E38*)D_00262280, 0, 1, 0xE);
    func_00161708((Frame_1F1E38*)D_00262280, 0x47, 0x31001);
    func_00161708((Frame_1F1E38*)D_00262280, 0x42, (flags & 1) ? 0x48 : 0x44);
    func_001613C0((Frame_1F1E38*)D_00262280, 0x4D, 2, 0x41);
    func_00161458((Stream_1F1E38*)D_00262280, *c1);
    func_001615F0((Stream_1F1E38*)D_00262280, (u32)(s32)((cx + 1728.0f) * 16.0f),
                  (u32)(s32)((cy * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    loc.k = 0;
    for (i = 0; i < n + 1; i++) {
        func_001EAD88(func_001EA408(angle), &loc.x, &loc.y);
        loc.x = loc.x * radius + cx;
        loc.y = loc.y * radius + cy;
        if ((i & 1) && (flags & 2)) {
            func_00161458((Stream_1F1E38*)D_00262280, loc.k);
        } else {
            func_00161458((Stream_1F1E38*)D_00262280, *c2);
        }
        angle += step;
        func_001615F0((Stream_1F1E38*)D_00262280, (u32)(s32)((loc.x + 1728.0f) * 16.0f),
                      (u32)(s32)((loc.y * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    }
}

// Globals defined from C.
s32 D_00275FC8[6] = { 0, 2, 4, 4, 4, 0 };
Ent_275FE0 D_00275FE0[52] = {
    { 0x2, 0x1CB, 0x2E4 },
    { 0x2, 0x1CC, 0x2E8 },
    { 0x2, 0x1CD, 0x2F8 },
    { 0x2, 0x1CE, 0x32C },
    { 0x2, 0x1CF, 0x360 },
    { 0x2, 0x1D0, 0x394 },
    { 0x2, 0x1D1, 0x3C8 },
    { 0x2, 0x1D2, 0x3FC },
    { 0x2, 0x1D3, 0x430 },
    { 0x2, 0x1D4, 0x464 },
    { 0x2, 0x1D5, 0x498 },
    { 0x2, 0x1D6, 0x500 },
    { 0x2, 0x1E2, 0x304 },
    { 0x2, 0x1E3, 0x338 },
    { 0x2, 0x1E4, 0x36C },
    { 0x2, 0x1E5, 0x3A0 },
    { 0x2, 0x1E6, 0x3D4 },
    { 0x2, 0x1E7, 0x408 },
    { 0x2, 0x1E8, 0x43C },
    { 0x2, 0x1E9, 0x470 },
    { 0x2, 0x1EA, 0x4A4 },
    { 0x2, 0x1EC, 0x50C },
    { 0x2, 0x1EB, 0x4D8 },
    { 0x2, 0x1D7, 0x2FC },
    { 0x2, 0x1D8, 0x330 },
    { 0x2, 0x1D9, 0x364 },
    { 0x2, 0x1DA, 0x398 },
    { 0x2, 0x1DB, 0x3CC },
    { 0x2, 0x1DC, 0x400 },
    { 0x2, 0x1DD, 0x434 },
    { 0x2, 0x1DE, 0x468 },
    { 0x2, 0x1DF, 0x49C },
    { 0x2, 0x1E1, 0x504 },
    { 0x2, 0x1E0, 0x4D0 },
    { 0x2, 0x1F8, 0x310 },
    { 0x2, 0x1F9, 0x378 },
    { 0x2, 0x1FA, 0x3AC },
    { 0x2, 0x1FB, 0x3E0 },
    { 0x2, 0x1FC, 0x414 },
    { 0x2, 0x1FD, 0x448 },
    { 0x2, 0x1FE, 0x47C },
    { 0x2, 0x1FF, 0x4B0 },
    { 0x2, 0x1ED, 0x30C },
    { 0x2, 0x1EE, 0x340 },
    { 0x2, 0x1EF, 0x374 },
    { 0x2, 0x1F0, 0x3A8 },
    { 0x2, 0x1F1, 0x3DC },
    { 0x2, 0x1F2, 0x410 },
    { 0x2, 0x1F3, 0x444 },
    { 0x2, 0x1F4, 0x478 },
    { 0x2, 0x1F5, 0x4AC },
    { 0x2, 0x1F7, 0x514 },
};
s32 D_00276250 = -1;
s32 (*D_00276608[6])[4] = { 0, (s32(*)[4])D_00276298, (s32(*)[4])D_00276348, (s32(*)[4])D_002763F8, (s32(*)[4])D_002764A8, (s32(*)[4])D_00276558 };
Cfg_1F2688 D_00276620;
extern const char D_0024E808[40] = "&2T&. : Back\n&2(&. : Move\n&2X&. : Warp";

// _GLOBAL_$I$ of the file, after the 16 bytes the linker left of two layout setters.
void func_001F2738(void)
{
    func_001F2688(1, 0xFFFF);
}

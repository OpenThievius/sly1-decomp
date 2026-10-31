// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_E8E08 { u8 pad[0xC58]; s32 f58; s32 f5C; };
void func_001C9AF8(void);

void func_001E8E08(Obj_E8E08* a0)
{
    if (a0->f58 != 0x2DA) {
        s32 v = a0->f5C - 1;
        if (!(0 < v)) v = 0;
        a0->f5C = v;
    }
    func_001C9AF8();
}

extern u8 D_00275BC0[];
void func_001E90A8(void* p);

void func_001E9088(void)
{
    func_001E90A8(D_00275BC0);
}

void func_001AA110(void);

void func_001E9668(void)
{
    func_001AA110();
}

void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

struct __attribute__((packed)) Entry8_1EBCD8 { u8 b[8]; };
struct List_1EBCD8 { u8 pad[0x630]; s32 count; Entry8_1EBCD8 items[1]; };

void func_001EBCD8(List_1EBCD8* list, const Entry8_1EBCD8* src)
{
    s32 n = list->count;
    list->count = n + 1;
    Entry8_1EBCD8* dst = (Entry8_1EBCD8*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}

struct Obj_1E86E0 {
    u8 pad0[0x268];
    s32 f268;
    u8 pad1[0x270 - 0x26C];
    s32 f270;
};

struct Mgr_1E86E0 {
    void** vtbl;
    u8 pad[0x260 - 4];
    s32 f260;
};

extern Mgr_1E86E0 D_002701F8;
void func_001E7460(void* self);
void func_001E7440(void* self, s32 v);
void func_001E7518(void* self, s32 mode);
void func_001E87F0(void* self, void* a1);

void func_001E86E0(Obj_1E86E0* self, s32 value)
{
    if (value == self->f270) return;
    if (self->f270 == 0) {
        void** vt = D_002701F8.vtbl;
        ((void (*)(void*, s32))vt[8])(&D_002701F8, 0);
    }
    self->f270 = value;
    if (D_002701F8.f260 == 4) {
        func_001E7460(self);
        if (self->f270 != 0) {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 2);
            func_001E7518(self, 1);
            func_001E7440(self, 0);
        } else {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 0);
            func_001E7518(self, 3);
            func_001E7440(self, 0);
            func_001E87F0(self, 0);
        }
    } else {
        s32 st = self->f268;
        if (st >= 2) return;
        if (st < 0) return;
        func_001E7518(self, 2);
    }
}

struct Obj_1E87F0 {
    u8 pad0[0x278];
    Obj_1E87F0* f278;
    u8 pad1[0x2C8 - 0x27C];
    u64 f2C8;
};

void func_001E87F0(Obj_1E87F0* self, Obj_1E87F0* a1)
{
    Obj_1E87F0* old = self->f278;
    if (old != 0) {
        old->f2C8 &= ~(1ULL << 32);
    }
    self->f278 = a1;
    if (a1 != 0) {
        a1->f2C8 |= (1ULL << 32);
    }
}

struct Obj_1E8840 {
    u8 pad0[0x268];
    s32 f268;
    s32 pad1;
    s32 f270;
    s32 f274;
    u8 pad2[0xC70 - 0x278];
    s32 fC70;
};

void func_001AA8C8(void* self);

void func_001E8840(Obj_1E8840* self)
{
    func_001AA8C8(self);
    self->fC70 = 0;
    self->f274 = 0;
    self->f270 = 0;
    self->f268 = 3;
}

s32 func_001E8878(s32 a0, s32 a1);

void func_001E88B0(void)
{
    func_001E8878(1, 0xFFFF);
}

struct Obj_1EB598 { u8 pad0[0x14]; void* f14; u8 pad1[0x610 - 0x18]; void* f610; void* f614; };

extern u8 D_00275CA0[];
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a, void* p);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void func_001DBCC8(void* a, void* cb, void* ctx, s32 b, s32 c);
void func_001EB550(Obj_1EB598* self);

void func_001EB598(Obj_1EB598* self)
{
    func_00124A48(self);
    func_00124DF8(self, 4, D_00275CA0);
    self->f614 = func_001B6290(self->f610, self, 0x4CA, 1);
    func_001DBCC8(self->f14, (void*)func_001EB550, self, 0, 0);
}

struct Inner_1EB608 { u8 pad[0xC3C]; void* c3C; };
struct Obj_1EB608 { u8 pad0[0x14]; void* f14; u8 pad1[0x614 - 0x18]; void* f614; u8 pad2[0x68C - 0x618]; void* f68C; };
struct Glob_1EB608 { u8 pad[0x26D0]; f32 f26D0; };

extern Glob_1EB608* D_00262E10;

void func_001922E8(void* self);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);

void func_001EB608(Obj_1EB608* self, void* p)
{
    func_001922E8(self);
    Inner_1EB608* r = (Inner_1EB608*)func_0015A838(self->f14, 5, 0x13, 0);
    if (p != 0) {
        func_001B64D8(self->f614, 0x4CB);
        r->c3C = self;
        self->f68C = r;
    } else {
        func_001B64D8(self->f614, 0x4CA);
        D_00262E10->f26D0 = 2.0f;
    }
}

struct Obj_1EBC88 { u8 pad0[0x14]; void* f14; u8 pad1[0x688 - 0x18]; s32 f688; };

extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001EBC88(Obj_1EBC88* self)
{
    if (D_00262C64 & 1) return 1;
    if (func_001DDA80(self->f14) == 0) return self->f688 != 0;
    return 1;
}

s32 func_001EBD08(void)
{
    return 0;
}

struct Table_001E9038 {
    u8 pad0[0xC64];
    s32 items[6];
};

struct Probe_001E9038 {
    u8 pad0[0x50];
    s32 key;
};

s32 func_001C7468(void* self, void* probe);

s32 func_001E9038(Table_001E9038* self, Probe_001E9038* probe)
{
    s32 key = probe->key;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->items[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = func_001C7468(self, probe);
done:
    return result;
}

struct Ctor_001E90A8 {
    u8 pad0[4];
    s32 a04;
    u8 pad1[4];
    s32 a0C;
    u8 pad2[0x1C];
    s32 a2C;
    s32 a30;
};

void func_001E96F8(void* self, s32 mode);

void func_001E90A8(Ctor_001E90A8* self)
{
    self->a30 = -1;
    self->a04 = -1;
    func_001E96F8(self, 3);
    self->a0C = 0;
    self->a2C = 1;
}

void func_001E96F8(void* self, s32 mode);

void func_001E90E8(void* self)
{
    func_001E96F8(self, 3);
}

typedef void (*VFn_001E9498)(void* self);
typedef void (*VFnFlag_001E9498)(void* self, s32 flag);

struct Node_001E9498 {
    VFn_001E9498* vtbl;
};

struct Set_001E9498 {
    u8 pad0[0xC];
    Node_001E9498* items[8];
    s32 count;
};

s32 func_001BE5E8(void);
void func_001BEA28(void);

void func_001E9498(Set_001E9498* self, Node_001E9498* node)
{
    if (func_001BE5E8() && self->count == 1) {
        func_001BEA28();
    }
    if (self->count >= 2) {
        Node_001E9498* last = self->items[self->count - 1];
        if (last->vtbl[3]) {
            ((VFnFlag_001E9498)last->vtbl[3])(last, 0);
        }
    }
    if (node->vtbl[3]) {
        ((VFnFlag_001E9498)node->vtbl[3])(node, 1);
    }
    s32 index = self->count;
    self->items[index] = node;
    self->count = index + 1;
    if (node->vtbl[6]) {
        node->vtbl[6](node);
    }
}

f32 func_002058A0(f32 v);

f32 func_001EAFE0(f32 x, f32 y)
{
    f32 r = func_002058A0(x);
    if (r < 0.0f) {
        r += y;
    }
    return r;
}

struct Span_001EB050 { f32 lo; f32 hi; };

s32 func_001EB050(Span_001EB050* span, f32 x)
{
    s32 inside = 0;
    if (span->lo < x) {
        if (x < span->hi) {
            inside = 1;
        }
    }
    return inside;
}

s32 func_001EB050(Span_001EB050* span, f32 x);

s32 func_001EB080(s32 count, Span_001EB050* spans, f32 x)
{
    for (s32 i = 0; i < count; i++) {
        if (func_001EB050(&spans[i], x)) {
            return 1;
        }
    }
    return 0;
}

struct Span_001EB0F8 { f32 lo; f32 hi; };

f32 func_001EB0F8(Span_001EB0F8* span, f32 x)
{
    if (x < span->lo) {
        return span->lo;
    }
    if (span->hi < x) {
        return span->hi;
    }
    return x;
}

typedef void (*VFn3_1E9570)(void* self, int arg);
typedef void (*VFn7_1E9570)(void* self);
struct VTable_1E9570 {
    u8 pad0[0xC];
    VFn3_1E9570 slot3;
    u8 pad1[0xC];
    VFn7_1E9570 slot7;
};
struct Item_1E9570 { VTable_1E9570* vt; };
struct Group_1E9570 {
    u8 pad0[0xC];
    Item_1E9570* items[8];
    s32 count;
};

int func_001BE5E8(void);
void func_001BEA50(void);

void func_001E9570(Group_1E9570* g)
{
    Item_1E9570* item = g->items[--g->count];
    if (item->vt->slot3) item->vt->slot3(item, 0);
    if (item->vt->slot7) item->vt->slot7(item);
    if (g->count >= 2) {
        Item_1E9570* other = g->items[g->count - 1];
        if (other->vt->slot3) other->vt->slot3(other, 1);
    }
    if (func_001BE5E8()) {
        if (g->count == 1) func_001BEA50();
    }
}

void func_001AA178(void);

void func_001E9648(void)
{
    func_001AA178();
}

extern float D_0026185C;

void func_001C06A0(int a, int b, float t);
void func_00142ED0(float x);

void func_001E98E8(float x)
{
    if (0.0f < D_0026185C) {
        float t = (1.0f - x) * 0.6f + x;
        func_001C06A0(4, 1, t);
        func_001C06A0(4, 0, t);
    }
    func_00142ED0(x);
}

s32 func_001EB128(f32* a, f32* b)
{
    f32 x = *a;
    f32 y = *b;
    if (y < x) return 1;
    if (x < y) return -1;
    return 0;
}

void func_001EB160(void)
{
}

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* data);
extern u8 D_00275C90[];

void func_001EB518(void* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_00275C90);
}

struct Gate_0026FF68 { u8 pad0[0x250]; s32 f250; u8 pad1[8]; s32 f25C; s32 f260; };
struct Gate_0026F808 { u8 pad0[0x250]; s32 f250; u8 pad1[8]; s32 f25C; };

extern s32 D_00275F84;
extern u8 D_0026FF68[];
extern u8 D_0026F808[];

s32 func_001E9A10(void)
{
    if (D_00275F84 != 0) goto fail;
    if (((Gate_0026FF68*)D_0026FF68)->f25C != 0) goto fail;
    if (((Gate_0026FF68*)D_0026FF68)->f250 != 0) goto fail;
    if (((Gate_0026F808*)D_0026F808)->f25C != 0) goto fail;
    if (((Gate_0026F808*)D_0026F808)->f250 == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

struct Obj_1E8DB0 { u8 pad[0xC40]; s32 f40; u8 pad2[0x18]; s32 f5C; };

s32 func_001E8DB0(Obj_1E8DB0* a0)
{
    if (a0->f40 != 0) return 0;
    return a0->f5C != 0;
}

struct Obj_1E8DD0 { u8 pad[0xC58]; s32 f58; s32 f5C; };

s32 func_001E8DD0(Obj_1E8DD0* a0)
{
    if (a0->f58 != 0x2DB) return 0;
    {
        s32 v = a0->f5C;
        if (v == 5 || v == 0) return 0;
        return 1;
    }
}

f32 func_001EAFE0(f32 x, f32 y);

f32 func_001EA408(f32 a)
{
    f32 r = a;
    if (a < -3.1415927f || a > 3.1415927f) {
        r = func_001EAFE0(a + 3.1415927f, 6.2831855f) - 3.1415927f;
    }
    return r;
}

f32 func_001EA480(f32 a, f32 b)
{
    f32 r = a;
    if (b < r) {
        r = b;
    } else {
        b = -b;
        if (r < b) {
            r = b;
        }
    }
    return r;
}

struct Vec3_1EAD30 { f32 x; f32 y; f32 z; };

void func_001EAD30(Vec3_1EAD30* in, Vec3_1EAD30* out, f32 s, f32 t)
{
    out->z = in->z * s * s;
    out->y = (in->z + in->z) * s * t + in->y * s;
    out->x = (in->z * t * t + in->y * t) + in->x;
}

struct Obj_1E8E48 { u8 pad0[0x724]; s32 f724; u8 pad1[0xC58 - 0x728]; s32 fC58; s32 fC5C; u8 pad2[0xC7C - 0xC60]; s32 fC7C; };

s32 func_001BB290(void* a, s32 b, s32 c);
s32 func_001E89F0(void* a, void* b);
void* func_00129C20(s32 a, s32 b);
void func_001B64D8(void* p, s32 n);
void func_001C9CF8(void* a);

void func_001E8E48(Obj_1E8E48* self)
{
    if (self->fC58 == 0x2DA && self->f724 == 0xC && func_001BB290(self, 0, 0) != 0) {
        s32 s = func_001E89F0(self, (u8*)self + 0x140);
        if (s != self->fC7C) {
            s32 n = self->fC5C - 1;
            if (!(0 < n)) n = 0;
            self->fC5C = n;
            if (n > 0) {
                void* p = func_00129C20(s, -1);
                if (p != 0) func_001B64D8(p, 0x2E0);
                self->fC7C = s;
            }
        }
    }
    func_001C9CF8(self);
}

typedef void* (*VFn_1E8EF8)(void* self);
struct Obj_1E8EF8 { VFn_1E8EF8* vtbl; u8 pad0[0x724 - 4]; s32 f724; u8 pad1[0xC40 - 0x728]; s32 fC40; u8 pad2[0xC60 - 0xC44]; void* fC60; };
struct Buf_1E8EF8 { s32 v[4]; };

void func_001C8418(Obj_1E8EF8* self, void* p);
void func_001C8C08(Obj_1E8EF8* self);
void func_001F3BD8(void* self, void* arg);

void func_001E8EF8(Obj_1E8EF8* self)
{
    Buf_1E8EF8 loc;
    switch (self->f724) {
    case 4:
        if (self->fC40 != 0) {
            func_001C8418(self, (u8*)self + 0x190);
        } else {
            func_001F3BD8(self->fC60, &loc);
            func_001C8418(self, &loc);
        }
        break;
    case 8: {
        void* r = self->vtbl[102](self);
        if (r != 0) func_001C8418(self, (u8*)r + 0x140);
        break;
    }
    default:
        func_001C8C08(self);
        break;
    }
}

extern u8 D_00275B50[];
void func_001E8878(s32 enabled, u32 value) { if (value == 0xFFFF && enabled) { D_00275B50[0] = 0x80; D_00275B50[1] = 0x80; D_00275B50[2] = 0x80; D_00275B50[3] = 0x80; } }

struct Obj_1E8FA8 { u8 pad0[0x724]; s32 f724; };

void func_001C8BC0(Obj_1E8FA8* self);
void func_001C8E28(Obj_1E8FA8* self);

void func_001E8FA8(Obj_1E8FA8* self)
{
    if (self->f724 == 8) {
        func_001C8BC0(self);
    } else {
        func_001C8E28(self);
    }
}

typedef void (*VFn_1E9E30)(void* self);
struct Node_1E9E30 {
    VFn_1E9E30* vtbl;
    u8 pad0[0x6C - 4];
    Node_1E9E30* f6C;
    u8 pad1[0x2D8 - 0x70];
    Node_1E9E30* f2D8;
    u8 pad2[0x2E4 - 0x2DC];
    Node_1E9E30* f2E4;
    u8 pad3[0x414 - 0x2E8];
    Node_1E9E30* f414;
    u8 pad4[0x538 - 0x418];
    u64 f538;
};

void func_001E9E30(void* self)
{
    s32 scratch[4];
    (void)scratch;
    Node_1E9E30* s1 = ((Node_1E9E30*)self)->f6C;
    if (s1 != 0) {
        do {
            Node_1E9E30* s0 = s1->f2D8;
            if (s0 != 0) {
                do {
                    u64 bit = (u64)1 << 53;
                    if ((s0->f538 & bit) == 0) {
                        s0->vtbl[72](s0);
                    }
                    s0->f538 &= ~bit;
                    s0 = s0->f2E4;
                } while (s0 != 0);
            }
            s1 = s1->f414;
        } while (s1 != 0);
    }
}

struct Obj_1E8948 {
    u8 pad0[0x14];
    void* f_14;
    u8 pad1[0xC50 - 0x18];
    void* f_C50;
    void* f_C54;
    u8 pad2[0xC80 - 0xC58];
    void* f_C80[4];
    s32 f_C90;
};

extern u8 D_00261420[];
extern u8 D_00275B60[];

void func_00124DF8(void* self, s32 a1, void* a2);
void func_001DDC38(void* sub, void* self);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void* func_00140FF8(void* p);
void func_00167E08(void* self);

void func_001E8948(Obj_1E8948* self)
{
    func_00124DF8(self, 8, D_00275B60);
    func_001DDC38(self->f_14, self);
    if (self->f_C50 != 0) {
        self->f_C54 = func_001B6290(self->f_C50, 0, 0x2D7, 0);
    }
    self->f_C90 = 4;
    for (u32 i = 0; i < 4; i++) {
        self->f_C80[i] = func_00140FF8(D_00261420);
    }
    func_00167E08(self);
}

extern u8 D_0026E248[];

typedef void (*VFn_1E8FE8)(void* self);
struct Obj_1E8FE8 {
    VFn_1E8FE8* vtbl;
};

s32 func_001E9970(void);

void func_001E8FE8(void)
{
    if (func_001E9970()) {
        ((Obj_1E8FE8*)D_0026E248)->vtbl[14](D_0026E248);
    } else {
        ((Obj_1E8FE8*)D_0026E248)->vtbl[15](D_0026E248);
    }
}

struct Gate_1E9A68 { u8 pad0[0x250]; s32 f250; u8 pad1[8]; s32 f25C; };

extern s32 D_00275F84;
extern u8 D_0026FF68[];
extern u8 D_0026F808[];
extern s32 D_00270458;

s32 func_001E9A68(void)
{
    s32 m;
    if (D_00275F84 != 0) goto fail;
    if (((Gate_1E9A68*)D_0026FF68)->f25C != 0) goto fail;
    if (((Gate_1E9A68*)D_0026FF68)->f250 != 0) goto fail;
    if (((Gate_1E9A68*)D_0026F808)->f25C != 0) goto fail;
    if (((Gate_1E9A68*)D_0026F808)->f250 != 0) goto fail;
    m = D_00270458;
    if (m == 4) goto fail;
    if (m != 1) goto ok;
fail:
    return 0;
ok:
    return 1;
}

struct Gate_1E9AD8 { u8 pad0[0x250]; s32 f250; u8 pad1[8]; s32 f25C; };

extern s32 D_00275F84;
extern u8 D_0026FF68[];
extern u8 D_0026F808[];

s32 func_001E9AD8(void)
{
    if (D_00275F84 != 0) goto fail;
    if (((Gate_1E9AD8*)D_0026FF68)->f25C != 0) goto fail;
    if (((Gate_1E9AD8*)D_0026FF68)->f250 != 0) goto fail;
    if (((Gate_1E9AD8*)D_0026F808)->f25C != 0) goto fail;
    if (((Gate_1E9AD8*)D_0026F808)->f250 == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

extern u8 D_00275DB8[];
extern u8 D_00275DBC[];
void func_001C6F48(void* self);
void* func_0018D500(s32 size);
void func_001BEA78(void);

void func_001EBEB0(u8* self)
{
    func_001C6F48(self);
    *(s32*)(self + 0xC5C) = 0x3C;
    *(f32*)(self + 0xC8C) = 1.0f;
    *(f32*)(self + 0xC64) = 8.0f;
    *(s32*)(self + 0xC70) = 0;
    *(s32*)(self + 0xC78) = -1;
    *(s32*)(self + 0xC74) = -1;
    *(s32*)(self + 0xC60) = 8;
    *(s32*)(self + 0xC6C) = (s32)func_0018D500(0x400);
    *(s32*)(*(u8**)(self + 0x14) + 0x2358) = 1;
    func_001BEA78();
    *(s32*)D_00275DB8 = 2;
    *(s32*)D_00275DBC = 0;
}

// NEAR: the li and lui registers differ (retail keeps 1 in v0 and the global base in a2)

extern u8 D_00262C70[];

struct Obj_1E9688 {
    u8 pad0[0xC];
    s32 f_0C;
    u8 pad1[0x2C - 0x10];
    s32 f_2C;
    s32 f_30;
};

void func_001E9570(void* g);
void func_001A7D98(void* self, s32 mode);
void func_001AA0C0(void);

void func_001E9688(Obj_1E9688* self)
{
    while (self->f_2C >= 2) {
        func_001E9570(self);
    }
    s32 one = 1;
    self->f_30 = -1;
    u8* base = D_00262C70;
    self->f_2C = one;
    self->f_0C = 0;
    func_001A7D98(*(void**)(base + 0xBC), 3);
    func_001AA0C0();
}

// NEAR: prologue copies: retail moves $f12 to $f22 before $a1 to $s1, and sets $f14 from $f20 before $a1 = sp; the compiler orders both differently (4 lines).

struct Obj_1EA620 { u8 pad[0xC]; f32 f0C; };

f32 func_001EA4B8(f32 a, f32 b, f32 c, void* p, f32* out);

f32 func_001EA620(f32 a, f32 b, f32 c, f32 d, void* self, f32* out)
{
    Obj_1EA620* o = (Obj_1EA620*)self;
    f32 tmp;
    f32 res = func_001EA4B8(a, c, d, self, &tmp);
    f32 k = o->f0C;
    if (0.0f < k) {
        f32 hi = b + k * d;
        f32 lo = b - k * d;
        if (hi < tmp) {
            tmp = hi;
            res = a + b * d + (k * (d * 0.5f)) * d;
        } else if (tmp < lo) {
            tmp = lo;
            res = a + b * d - (k * (d * 0.5f)) * d;
        }
    }
    if (out != 0) *out = tmp;
    return res;
}

// NEAR: ints are saved to s0/s1 the wrong way round (self in s1, a1 in s0) and mov.s f21,f15 lands in the delay slot; ordering of the callee-saved moves differs.

f32 func_001EA408(f32 a);
f32 func_001EA620(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1);

f32 func_001EA798(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1)
{
    f32 t = func_001EA408(f14 - f12);
    f32 r = func_001EA620(0.0f, f13, t, f15, self, a1);
    return func_001EA408(f12 + r);
}

f32 func_001EA408(f32 a);
f32 func_001EA4B8(f32 a, f32 b, f32 c, void* p, f32* out);

f32 func_001EA728(f32 a, f32 b, f32 c, void* self, f32* out)
{
    f32 t = func_001EA408(b - a);
    f32 r = func_001EA4B8(0.0f, t, c, self, out);
    return func_001EA408(a + r);
}

s32 func_001F6708(void);

f32 func_001EAAE0(f32 a, f32 b)
{
    f32 r;
    if (a != b) {
        s32 n = func_001F6708();
        r = a + (b - a) * (f32)n * 0.0000000004656613f;
    } else {
        r = a;
    }
    return r;
}

struct Coeffs_1EA4B8 { f32 p0; f32 p1; f32 p2; };

void func_001EACA0(f32* roots, f32 a, f32 b, f32 c);

f32 func_001EA4B8(Coeffs_1EA4B8* k, f32* out, f32 x, f32 y, f32 z)
{
    f32 roots[4];
    s32 flip = 0;
    f32 d = x - y;
    f32 c = z;
    f32 half;
    f32 t;
    f32 res;
    f32 r;
    if (d < 0.0f) {
        flip = 1;
        d = -d;
    }
    half = (k->p1 + k->p0) * k->p2 * 0.5f;
    if (half <= d) {
        f32 u = (d - half) / k->p0;
        if (c <= u) {
            res = d - k->p0 * c;
            t = -k->p0;
            goto tail;
        }
        c = c - u;
        d = half;
    }
    func_001EACA0(roots, (k->p0 - k->p1) / (k->p2 + k->p2), k->p1, -d);
    r = roots[0] - c;
    if (0.0f < r) {
        res = (k->p0 - k->p1) * r * r / (k->p2 + k->p2) + k->p1 * r;
        t = -(k->p1 + (k->p0 - k->p1) * r / k->p2);
    } else {
        t = -k->p1;
        res = 0.0f;
    }
tail:
    if (flip) {
        res = y - res;
        if (out) {
            *out = -t;
        }
    } else {
        res = res + y;
        if (out) {
            *out = t;
        }
    }
    return res;
}

struct Obj_1E88D0 {
    u8 pad0[0xC10];
    f32 fC10;
    f32 fC14;
    u8 pad1[0xC20 - 0xC18];
    f32 fC20;
    f32 fC24;
    s32 fC28;
    f32 fC2C;
    u8 pad2[0xC58 - 0xC30];
    s32 fC58;
};

void func_00167D68(void* self);

void func_001E88D0(Obj_1E88D0* self)
{
    func_00167D68(self);
    self->fC58 = 0x2D8;
    self->fC14 = 30000.0f;
    self->fC10 = 30000000.0f;
    self->fC20 = 3000000.0f;
    self->fC24 = 3000000.0f;
    self->fC28 = 0;
    self->fC2C = 6.2831855f;
}

f32 func_001EAF28(f32 x)
{
    f32 buf[2];
    u64* qp = (u64*)buf;
    buf[0] = x;
    u64 bits = *qp;
    u32 ex = (u32)((s64)(bits << 9) >> 32) & 0xFF;
    s32 e = (s32)ex - 0x7F;
    if (e < 0)
        return 0.0f;
    if (e < 0x17) {
        s32 mask = (s32)(((u64)1 << (0x17 - e)) - 1);
        s32 frac = *(s32*)buf & 0x7FFFFF;
        if ((frac & mask) == mask) {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
            buf[0] = buf[0] + 1.0f;
        } else {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
        }
    }
    return buf[0];
}

struct Entry_1EBFB0 { s32 a; s32 b; s32 c; };
struct Ctx_1EBFB0 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0xC50 - 0x18];
    void* pC50;
    void* pC54;
    u8 pad2[0xC98 - 0xC58];
    s32 countC98;
    void* tableC9C;
};

void func_001C72A0(void* self);
void func_001DDC38(void* a, void* self);
void func_00124DF8(void* self, s32 n, void* data);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6DF8(void* a, void* self);
void* func_0018D568(s32 size, void* name);
s32 func_0015A418(void* a, s32 b, s32 c, void* self);
extern u8 D_00275D08[];
extern u8 D_00275D48[];

void func_001EBFB0(Ctx_1EBFB0* self)
{
    func_001C72A0(self);
    func_001DDC38(self->p14, self);
    func_00124DF8(self, 5, D_00275D08);
    void* r = func_001B6290(self->pC50, 0, -1, 0);
    self->pC54 = r;
    func_001B6DF8(r, self);
    self->countC98 = 9;
    self->tableC9C = func_0018D568(0x6C, D_00275D48);
    s32 i = 0;
    if (self->countC98 > 0) {
        s32 off = 0;
        do {
            Entry_1EBFB0* e = (Entry_1EBFB0*)((u8*)self->tableC9C + off);
            e->c = func_0015A418(self->p14, 1, e->a, self);
            i++;
            off += 12;
        } while (i < self->countC98);
    }
}

struct Obj_1EA0A8 { u8 pad[0x234C]; f32 f234C; f32 f2350; };

extern u8 D_00275C18[];
extern u8 D_00275C28[];

f32 func_001EA4B8(void* p, void* out, f32 a, f32 b, f32 c);

void func_001EA0A8(void* self, f32 x)
{
    Obj_1EA0A8* o = (Obj_1EA0A8*)self;
    f32 a = o->f234C;
    f32 b = o->f2350;
    if (b < a) {
        o->f234C = func_001EA4B8(D_00275C18, 0, a, b, x);
    } else if (a < b) {
        o->f234C = func_001EA4B8(D_00275C28, 0, a, b, x);
    }
}

struct Self_1E8D58 { u8 p0[0x724]; s32 v724; u8 p1[0x7E0 - 0x728]; s32 v7E0; u8 p2[0xBFC - 0x7E4]; f32 fBFC; u8 p3[0xC5C - 0xC00]; s32 vC5C; };

extern f32 D_0024E66C;
s32 func_001C8010(Self_1E8D58* self);

s32 func_001E8D58(Self_1E8D58* self)
{
    s32 a1;
    if (self->vC5C <= 0) {
        self->fBFC = D_0024E66C;
    }
    a1 = self->v724;
    if (a1 == 10) {
        a1 = (self->v7E0 == 0) ? 8 : 10;
    } else {
        a1 = func_001C8010(self);
    }
    return a1;
}

struct __attribute__((aligned(16))) Chunk_1EB550 { u8 b[0x80]; };
struct Blk_1EB550 { u8 pad0[0x580]; Chunk_1EB550 c; u8 pad1[4]; s32 f604; };


void func_001EB550(Blk_1EB550* a0)
{
    a0->c = ((Blk_1EB550*)D_00262E10)->c;
    a0->f604 = ((Blk_1EB550*)D_00262E10)->f604;
}

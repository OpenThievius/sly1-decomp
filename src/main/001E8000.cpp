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

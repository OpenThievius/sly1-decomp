// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Item_14C838 { s32 value; s32 pad[4]; };
struct List_14C838 { u8 pad0[0x2DC]; s32 count; Item_14C838 items[1]; };

void func_0014C838(List_14C838* self, s32 value)
{
    s32 i = self->count;
    self->count = i + 1;
    self->items[i].value = value;
}

struct Obj_14DA68 { u8 pad0[0x8]; void* p8; s32 cnt; u8 pad1[4]; f32* p14; };

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014DA68(Obj_14DA68* self, f32* a1, f32* a2)
{
    return func_0014D1A0(self->cnt, self->p14, self->p8, a1, a2);
}

struct Obj_14DD28 { void** vtbl; u8 pad0[4]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };
typedef void (*Fn_14DD28)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

void func_0014DD28(Obj_14DD28* self, void* src)
{
    self->a8 = func_00137B90(src);
    s32 n = func_00137B90(src);
    self->cnt = n;
    self->p10 = (f32*)func_0018D500(n * 4);
    self->p14 = (f32*)func_0018D500(self->cnt * 4);
    self->p18 = func_0018D500(self->cnt * 16);
    for (s32 i = 0; i < self->cnt; i++) {
        self->p10[i] = func_00137DF8(src);
        func_00137E70(src, (u8*)self->p18 + i * 16);
    }
    Fn_14DD28 fn = (Fn_14DD28)self->vtbl[9];
    if (fn) fn(self);
}

struct Obj_14DF98 { u8 pad0[0x14]; f32* p14; };

s32 func_0014DA38(void* self, f32* a, f32* b);

f32 func_0014DF98(Obj_14DF98* self)
{
    f32 a, b;
    s32 i = func_0014DA38(self, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->p14[i] + t * self->p14[i + 1];
}

struct Obj_14E2A0 { u8 pad0[0x8]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };

void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_0014E2A0(Obj_14E2A0* self, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = func_0014D1A0(self->cnt, self->p14, (void*)self->a8, 0, 0);
    s32 ia;
    f32 fb;
    func_0014D680(a1, a2, self->cnt, self->p18, idx, self->a8, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->p14[ia] + fb * self->p14[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->p10[ia] + fb * self->p10[ia + 1];
}

struct Obj_14E910 { u8 pad0[0x14]; f32* p14; void* p18; void* p1C; void* p20; };
f32 func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);
f32 func_0014E910(Obj_14E910* self)
{
    f32 a, b;
    s32 i = func_0014DA38(self, &a, &b);
    u32 off = i * 16;
    f32 r = func_00130C20((u8*)self->p18 + off, (u8*)self->p20 + off,
                          (u8*)self->p18 + (off + 16), (u8*)self->p1C + (off + 16), b, a);
    return r + self->p14[i];
}

struct Obj_14EE70 { u8 pad0[0x14]; u8* p14; void* p18; u8 pad1[0x538 - 0x1C]; u64 bits538; };

void func_001B7A98(void* self);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);

void func_0014EE70(Obj_14EE70* self)
{
    func_001B7A98(self);
    if (func_001526D0(self->p14 + 0x1C78, self)) func_00152600(self->p14 + 0x1C78, self);
    if (self->p18 != 0 && func_001300E8(self->p18, 0x3A) != 0) {
        self->bits538 |= (u64)0x8000 << 28;
    } else {
        self->bits538 &= ~((u64)1 << 43);
    }
}

extern u8 D_00261CC8[];
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);

void func_0014F020(void* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_00261CC8);
}

extern u8* D_00262E10;

void func_0014F900(u8* self)
{
    if (D_00262E10 != 0) {
        *(s32*)(self + 0x6DC) = *(s32*)(D_00262E10 + 0x24F8);
    }
}

struct Mgr_14C668 {
    u8 pad_00[0x42C];
    void* dev;
};

extern Mgr_14C668* D_0027C00C;

void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0014C5E8(Mgr_14C668* self);

void func_0014C668(void* unused, s32 mode)
{
    if (mode == 1) {
        s32 t[2];
        func_001B6568(D_0027C00C->dev, &t[0]);
        func_001B6598(D_0027C00C->dev, &t[1]);
        if (t[0] != 0x3FE && t[1] != 0x3FE) {
            func_001B64D8(D_0027C00C->dev, 0x3FF);
            func_0014C5E8(D_0027C00C);
        }
    }
}

extern f32 D_00261858[];

void func_00124FC0(void* self);
void func_0014C858(void* self);
void func_0014CBA8(void* self);
void* func_001925F0(void);

typedef void (*VFn_14C6E0)(void* self);
struct Obj_14C6E0 { VFn_14C6E0* vtbl; };

struct Mgr_14C6E0 {
    u8 pad_00[0x42C];
    void* dev;
    u8 pad_430[0x45C - 0x430];
    f32 f45C;
    f32 f460;
};

void func_0014C6E0(Mgr_14C6E0* self)
{
    s32 tag;
    func_00124FC0(self);
    func_001B6598(self->dev, &tag);
    if (tag == 0x3FD) {
        if (self->f45C < D_00261858[1]) {
            func_0014C858(self);
        }
        if (self->f460 < D_00261858[1]) {
            func_0014CBA8(self);
        }
        void* p = func_001925F0();
        Obj_14C6E0* o = (Obj_14C6E0*)p;
        o->vtbl[81](p);
    }
}

extern u8 D_0026D348[];
extern u8 D_0026E760[];

struct Mgr_14C788 {
    u8 pad_00[0x42C];
    void* dev;
};

typedef void (*VFn_14C788)(void* self);
struct Obj_14C788 { VFn_14C788* vtbl; };

void* func_001E9970(void* zero);

void func_0014C788(Mgr_14C788* self)
{
    s32 tag;
    func_001B6598(self->dev, &tag);
    void* p = 0;
    if (tag == 0x3FD) {
        p = func_001E9970(p);
    }
    if (p) {
        ((Obj_14C788*)D_0026D348)->vtbl[14](D_0026D348);
        ((Obj_14C788*)D_0026E760)->vtbl[14](D_0026E760);
    } else {
        ((Obj_14C788*)D_0026D348)->vtbl[15](D_0026D348);
        ((Obj_14C788*)D_0026E760)->vtbl[15](D_0026E760);
    }
}

struct Table_14C820 {
    u8 pad_00[0x690];
    s32 f690;
};

void* func_0014C820(Table_14C820* self)
{
    return (u8*)self + (self->f690 * 0xB0 + 0x480);
}

extern f32 D_0026185C;

f32 func_001EAAE0(f32 a, f32 b);

struct Mgr_14CD70 {
    u8 pad_00[0x43C];
    f32 f43C;
    f32 f440;
    u8 pad_444[0x450 - 0x444];
    s32 f450;
    u8 pad_454[0x458 - 0x454];
    s32 f458;
    f32 f45C;
};

void func_0014CD70(Mgr_14CD70* self)
{
    if (self->f458 == self->f450) {
        self->f45C = D_0026185C + func_001EAAE0(self->f43C, self->f440);
    }
    self->f458 = self->f458 - 1;
}

struct Ctx_0014F850 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0x744 - 0x18];
    s32 count744;
    void* items748[8];
    s32 count768;
    void* items76C[8];
};

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);
s32 func_001300E8(void* obj, s32 kind);

void func_0014F850(Ctx_0014F850* self)
{
    s32 i = 0;
    func_001249A8(self);
    if (self->count744 > 0) {
        do {
            void* p = func_0015A448(self->p14, self->items748[i], self);
            if (p != 0) {
                if (func_001300E8(p, 0x41) != 0) {
                    s32 n = self->count768;
                    self->items76C[n] = p;
                    self->count768 = n + 1;
                }
            }
            i++;
        } while (i < self->count744);
    }
}

struct Obj_0014FBE0 {
    u8 pad0[0x588];
    void* f588;
};

s32 func_001B8A08(void* self, void* obj);

s32 func_0014FBE0(void* self, Obj_0014FBE0* obj)
{
    if (func_001300E8(obj, 0x46) != 0) {
        if (obj->f588 == self) {
            return 1;
        }
    }
    return func_001B8A08(self, obj);
}

struct VObj_0014FC38 {
    void** vtbl;
};

struct Sub_0014FC38 {
    u8 pad0[0x200];
    VObj_0014FC38* p200;
};

struct Ctx_0014FC38 {
    u8 pad0[0x6C8];
    VObj_0014FC38* p6C8;
    u8 pad1[0x734 - 0x6CC];
    Sub_0014FC38* p734;
    u8 pad2[0x740 - 0x738];
    void* p740;
};

typedef void (*VFn1_0014FC38)(void* self);
typedef void (*VFn2_0014FC38)(void* self, s32 arg);

void func_001B6628(void* h, s32 arg);
void func_001B6598(void* h, s32* out);
void func_001B6438(void* h);
void func_0013D278(void* self);

void func_0014FC38(Ctx_0014FC38* self)
{
    s32 status;

    if (self->p6C8 != 0) {
        ((VFn2_0014FC38)self->p6C8->vtbl[25])(self->p6C8, 0);
        ((VFn1_0014FC38)self->p6C8->vtbl[7])(self->p6C8);
    }
    if (self->p740 != 0) {
        func_001B6628(self->p740, 0x2B7);
        func_001B6598(self->p740, &status);
        if (status == 0x2B7) {
            func_001B6438(self->p740);
            self->p740 = 0;
        }
    }
    {
        VObj_0014FC38* o = self->p734->p200;
        ((VFn2_0014FC38)o->vtbl[2])(o, 7);
    }
    func_0013D278(self);
}

struct Leaf_0014FCE8 {
    u8 pad0[0x1C];
    s32 f1C;
    u8 pad1[0x4C - 0x20];
    s32 f4C;
};

struct Sub_0014FCE8 {
    u8 pad0[0x200];
    Leaf_0014FCE8* p200;
};

struct Ctx_0014FCE8 {
    u8 pad0[0x6D8];
    s32 f6D8;
    u8 pad1[0x734 - 0x6DC];
    Sub_0014FCE8* p734;
    u8 pad2[0x740 - 0x738];
    void* p740;
};

void func_001B6568(void* h, s32* out);
void func_001B64D8(void* h, s32 code);

void func_0014FCE8(Ctx_0014FCE8* self, s32 code)
{
    s32 r;

    func_001B6568(self->p740, &r);
    if (r == -1) {
        func_001B6598(self->p740, &r);
    }
    if (code == r) {
        return;
    }
    if (r == 0x2B7) {
        self->p734->p200->f4C = 0;
    }
    if (code < 0x2BA) {
        if (code >= 0x2B8) {
            self->p734->p200->f1C = (code == 0x2B9);
            if (!((u32)(r - 0x2BA) < 2)) {
                self->f6D8 = 0;
            }
        }
    }
    func_001B64D8(self->p740, code);
}

struct Span_0014DD00 { u8 pad0[0x10]; f32* p; };

f32 func_0014DD00(Span_0014DD00* self)
{
    f32* p = self->p;
    f32 b = p[1]; f32 a = p[0]; return (b - a) * 0.1f;
}

struct Frame_0014DE08 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_0014DE08(Frame_0014DE08* self, s32 a1, s32 a2)
{
    func_0014D280(self->f0C, self->f18, self->f10, self->f08, a1, a2);
}

struct Frame_0014DE40 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_0014DE40(Frame_0014DE40* self, s32 a1, s32 a2)
{
    func_0014D280(self->f0C, self->f18, self->f14, self->f08, a1, a2);
}

struct __attribute__((aligned(16))) Quad_0014DE78 { s32 v[4]; };
struct __attribute__((packed)) Pack4_0014DE78 { s32 v; };
struct Table_0014DE78 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };

void func_00188700(void* a, void* b, void* c, f32 w);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);

void func_0014DE78(Table_0014DE78* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5)
{
    Quad_0014DE78 A;
    Quad_0014DE78 B;
    Pack4_0014DE78 C;
    s32 next;

    if (idx == self->f0C - 1) {
        next = 0;
        if (self->f08 == 0) {
            return;
        }
    } else {
        next = idx + 1;
    }
    func_00188700(a2, (u8*)self->f18 + (idx << 4), &A, 1.0f);
    func_00188700(a2, (u8*)self->f18 + (next << 4), &B, 1.0f);
    C = *(Pack4_0014DE78*)a4;
    func_001DD3E0(&A, &B, &C, a3, a5);
}

struct Obj_14E510 {
    u8 pad0[0x10];
    f32* p10;
    u8 pad1[4];
    u8* p18;
    u8* p1C;
    u8* p20;
    u8 pad2[0xC];
    u8 buf30[0x140];
    u8 pad3[0x1C0 - 0x170];
    s32 idx1C0;
};

void func_00130B48(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
f32 func_0014D0A8(s32 n, void* buf, void* other);

void func_0014E510(Obj_14E510* self, s32 i)
{
    if (i != self->idx1C0) {
        f32 d = self->p10[i + 1] - self->p10[i];
        s32 off = i * 16;
        func_00130B48(self->p18 + off, self->p20 + off, self->p18 + (off + 16),
                      self->p1C + (off + 16), d, 0.0f, d, 20, self->buf30);
        func_0014D0A8(20, self->buf30, self->pad3);
        self->idx1C0 = i;
    }
}

struct Obj_14E6A8 { void** vtbl; };
typedef f32 (*Fn_14E6A8)(void* self);
typedef void (*Fn2_14E6A8)(void* self, f32 t, s32 a1, void* a2);

void func_0014E6A8(Obj_14E6A8* self, s32 a1, void* a2)
{
    f32 t = ((Fn_14E6A8)self->vtbl[6])(self);
    Fn2_14E6A8 fn = (Fn2_14E6A8)self->vtbl[1];
    if (fn) {
        fn(self, t, a1, a2);
    }
}

struct Obj_14EA48 {
    u8 pad0[0xC];
    s32 n;
    f32* p10;
    f32* p14;
    u8* p18;
    u8* p1C;
    u8* p20;
};


void func_0014EA48(Obj_14EA48* self)
{
    *(s32*)self->p14 = 0;
    s32 m = self->n - 1;
    for (s32 i = 0; i < m; i++) {
        f32 d = self->p10[i + 1] - self->p10[i];
        s32 off = i * 16;
        f32 r = func_00130C20(self->p18 + off, self->p20 + off,
                              self->p18 + (off + 16), self->p1C + (off + 16), d, d);
        self->p14[i + 1] = self->p14[i] + r;
    }
}

f32 func_0014D138(s32 count, f32* table, s32 wrap, f32 x)
{
    if (wrap == 0) {
        return x;
    }
    f32 lo = table[0];
    f32 hi = table[count - 1];
    f32 span = hi - lo;
    if (x < lo) {
        do {
            x += span;
        } while (x < lo);
    }
    if (hi < x) {
        do {
            x -= span;
        } while (hi < x);
    }
    return x;
}

struct Obj_14EE40;

void func_001B7968(Obj_14EE40* self);
void func_0014F110(Obj_14EE40* self, s32 value);

void func_0014EE40(Obj_14EE40* self)
{
    func_001B7968(self);
    func_0014F110(self, -1);
}

struct __attribute__((aligned(16))) Quad_14D938 { s32 w[4]; };

void func_001891C0(void* self, void* arg, Quad_14D938* out);
void func_00188700(void* a, void* b, void* c, f32 w);

void func_0014D938(s32 count, Quad_14D938* dst, void* arg, void* self)
{
    Quad_14D938 mat[4];
    Quad_14D938 tmp;

    func_001891C0(self, arg, mat);
    if (count > 0) {
        do {
            func_00188700(mat, dst, &tmp, 1.0f);
            *dst = tmp;
            dst++;
            count--;
        } while (count != 0);
    }
}

f32 func_0014DA18(void)
{
    return 0.0f;
}

struct Obj_14E068 { u8 pad0[0xC]; s32 f0C; u8 pad1[4]; void* f14; void* f18; };


f32 func_0014E068(Obj_14E068* self)
{
    return func_0014D0A8(self->f0C, self->f18, self->f14);
}

struct Obj_14E090 { u8 pad0[0xC]; s32 f0C; f32* f10; f32* f14; void* f18; };
struct Frac_14E090 { s32 idx; f32 t; };

void func_0014D3A8(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);

void func_0014E090(Obj_14E090* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1)
{
    Frac_14E090 f;
    func_0014D3A8(a1, a2, self->f0C, self->f18, a3, a4, &f.idx, &f.t);
    if (out1) {
        *out1 = (1.0f - f.t) * self->f14[f.idx] + f.t * self->f14[f.idx + 1];
    }
    if (out0) {
        *out0 = (1.0f - f.t) * self->f10[f.idx] + f.t * self->f10[f.idx + 1];
    }
}

struct Ctx_0014F740 {
    u8 pad0[0x6C0];
    s32 f6C0;
};

void func_0013DDB8(void* self);

void func_0014F740(Ctx_0014F740* self)
{
    func_0013DDB8(self);
    self->f6C0 = -1;
}

f32 func_0014DA28(void)
{
    return 0.0f;
}

struct Obj_14DA38 { u8 pad0[0x8]; void* p8; s32 cnt; f32* p10; };

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014DA38(void* self, f32* a, f32* b)
{
    Obj_14DA38* o = (Obj_14DA38*)self;
    return func_0014D1A0(o->cnt, o->p10, o->p8, a, b);
}

struct Obj_14E170 { u8 pad0[0x8]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_0014E170(Obj_14E170* self, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = func_0014D1A0(self->cnt, self->p10, (void*)self->a8, 0, 0);
    s32 ia;
    f32 fb;
    func_0014D680(a1, a2, self->cnt, self->p18, idx, self->a8, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->p14[ia] + fb * self->p14[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->p10[ia] + fb * self->p10[ia + 1];
}

struct Obj_14E3D0 { void** vtbl; u8 pad0[4]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; void* p1C; void* p20; };
typedef void (*Fn_14E3D0)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);
void func_0014E500(void* self);

void func_0014E3D0(Obj_14E3D0* self, void* src)
{
    self->a8 = func_00137B90(src);
    s32 n = func_00137B90(src);
    self->cnt = n;
    self->p10 = (f32*)func_0018D500(n * 4);
    self->p14 = (f32*)func_0018D500(self->cnt * 4);
    self->p18 = func_0018D500(self->cnt * 16);
    self->p1C = func_0018D500(self->cnt * 16);
    self->p20 = func_0018D500(self->cnt * 16);
    for (s32 i = 0; i < self->cnt; i++) {
        self->p10[i] = func_00137DF8(src);
        func_00137E70(src, (u8*)self->p18 + i * 16);
        func_00137E70(src, (u8*)self->p1C + i * 16);
        func_00137E70(src, (u8*)self->p20 + i * 16);
    }
    Fn_14E3D0 fn = (Fn_14E3D0)self->vtbl[9];
    if (fn) fn(self);
    func_0014E500(self);
}

struct Obj_14DB40 { u8 pad[0xC]; u32 index; u32 base; };
f32 func_0014DB40(Obj_14DB40* obj) { u32 address = obj->index * 4 + obj->base; return *(f32*)(address - 4); }

struct Obj_14DB58 { u8 pad[0xC]; u32 index; u32 pad10; u32 base; };
f32 func_0014DB58(Obj_14DB58* obj) { u32 address = obj->index * 4 + obj->base; return *(f32*)(address - 4); }

struct Obj_14E500 { u8 pad[0x1C0]; s32 value; };
void func_0014E500(Obj_14E500* obj) { obj->value = -1; }

void func_0014DF68(u8* self,void* a,void* b) { func_0014D938(*(s32*)(self+0xC),*(Quad_14D938**)(self+0x18),a,b); }

void func_00182D50(void*);
void func_00152470(void*,void*);
void func_0014EF00(u8* self) { func_00182D50(self); func_00152470(*(u8**)(self+0x14)+0x1C78,self); func_0014F110((Obj_14EE40*)self,0); }

struct __attribute__((packed)) Pack_0014EF40 { u64 value; };
struct Obj_0014EF40 { u8 pad[0x56C]; Pack_0014EF40 value; };
void func_001BA130(void*, void*);
void func_0014EF40(Obj_0014EF40* self, void* other) { Pack_0014EF40 save=self->value; func_001BA130(self,other); self->value=save; }

void func_001BAC30(void*);
void func_00159478(void*,void*);
void func_0014EF88(u8* self) { func_001BAC30(self); func_00159478(self+0x58C,self); }

struct Obj_14EFB8 {
    u8 pad0[0x578];
    void* field_578;
};

void func_00127378(void* self, s32 kind, void* msg);
void func_0014F110(Obj_14EFB8* self, s32 value);

void func_0014EFB8(Obj_14EFB8* self, s32 kind, void* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 6) {
        if (msg == self->field_578) {
            self->field_578 = 0;
            func_0014F110(self, 4);
        }
    }
}

typedef void (*VFn_14F770)(void* self, void* arg);
struct Sub_14F770 { u8 pad0[0x1C]; s32 f1C; u8 pad1[0x2C]; s32 f4C; };
struct Child_14F770 { VFn_14F770* vtbl; u8 pad0[0x1FC]; Sub_14F770* f200; };
struct Obj_14F770 { u8 pad0[0x680]; s32 f680; u8 pad1[0xB0]; Child_14F770* f734; Child_14F770* f738; u8 pad2[4]; void* f740; };

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6568(void* dev, s32* out);
void func_001B6438(void* h);

void func_0014F770(Obj_14F770* self, s32 kind, void* msg)
{
    s32 result;

    func_00127378(self, kind, msg);
    if (kind == 0x14) {
        if (msg == self->f740) {
            func_001B6568(msg, &result);
            if (result == 0x2B7) {
                if (self->f680 != 0) {
                    func_001B6438(self->f740);
                    self->f740 = 0;
                } else {
                    self->f734->f200->f4C = 1;
                    self->f734->f200->f1C = 0;
                    self->f734->vtbl[0x84 / 4](self->f734, (u8*)self->f734 + 0x190);
                    self->f734->vtbl[0x88 / 4](self->f734, (u8*)self->f734 + 0x1A0);
                    self->f738->vtbl[0x88 / 4](self->f738, (u8*)self->f738 + 0x1A0);
                }
            }
        }
    }
}

struct Obj_14E000 { u8 pad0[0x10]; f32* p10; };

s32 func_0014DA68(Obj_14E000* self, f32* a1, f32* a2);

f32 func_0014E000(Obj_14E000* self)
{
    f32 lo, hi;
    s32 idx = func_0014DA68(self, &lo, &hi);
    f32 t = lo / hi;
    return (1.0f - t) * self->p10[idx] + t * self->p10[idx + 1];
}

struct Obj_14E990 { u8 pad0[0x10]; f32* p10; u8 pad1[0x170 - 0x14]; f32 buf170[4]; };

s32 func_0014DA68(Obj_14E990* self, f32* a1, f32* a2);
void func_0014E510(Obj_14E990* self, s32 i);
s32 func_0014D1A0(f32 x, s32 n, f32* arr, void* p2, f32* lo, f32* hi);

f32 func_0014E990(Obj_14E990* self)
{
    f32 lo, a, b;
    s32 idx = func_0014DA68(self, &lo, 0);
    func_0014E510(self, idx);
    s32 n = func_0014D1A0(lo, 20, self->buf170, 0, &a, &b);
    f32 t = a / b;
    f32 u = ((f32)n + t) * 0.0526315793f;
    return (1.0f - u) * self->p10[idx] + u * self->p10[idx + 1];
}

struct __attribute__((aligned(16))) Quad_14F920 { s32 a, b, c, d; };
struct Sub_14F920 { u8 pad0[0x4C]; s32 f4C; };
struct Obj734_14F920 { u8 pad0[0x200]; Sub_14F920* p200; };
struct Elem_14F920 { void** vtbl; };
struct Src_14F920 { void** vtbl; u8 pad0[0x14 - 4]; void* p14; s32 f18; u8 pad1[0x190 - 0x1C]; Quad_14F920 q190[4]; };
struct Self_14F920 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0x6C0 - 0x18];
    s32 f6C0;
    s32 cnt;
    u8 pad2[0x6F0 - 0x6C8];
    Quad_14F920 q6F0[4];
    s32 f730;
    Obj734_14F920* p734;
    u8 pad3[0x73C - 0x738];
    void* p73C;
    void* f740;
};

typedef void (*VFn_14F920)(void* self);
typedef void (*VFn_14F920Arg)(void* self, s32 x);

extern u8 D_00261CE0[];

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 n, void* table);
Src_14F920* func_0015A480(void* a, s32 kind, void* arg);
void* func_00183058(void* item, void* x, void* self);
void func_0014F900(void* self);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void* func_001B6290(void* a, void* b, s32 c, s32 d);

void func_0014F920(Self_14F920* self)
{
    func_0013CE40(self);
    func_00124DF8(self, 3, D_00261CE0);
    self->p734->p200->f4C = 1;
    Src_14F920* s2 = func_0015A480(self->p14, self->f6C0, self);
    self->q6F0[0] = s2->q190[0];
    self->q6F0[1] = s2->q190[1];
    self->q6F0[2] = s2->q190[2];
    self->q6F0[3] = s2->q190[3];
    self->f730 = s2->f18;
    s32 i = 1;
    if (i < self->cnt) {
        do {
            Elem_14F920* e = (Elem_14F920*)func_00183058(s2, s2->p14, 0);
            if (e->vtbl[19] != 0) {
                ((VFn_14F920)e->vtbl[19])(e);
            }
            i++;
            ((VFn_14F920)e->vtbl[20])(e);
            ((VFn_14F920)e->vtbl[7])(e);
        } while (i < self->cnt);
    }
    ((VFn_14F920Arg)s2->vtbl[25])(s2, 0);
    ((VFn_14F920)s2->vtbl[7])(s2);
    func_001DBCC8(self->p14, (void*)(void (*)(void*))func_0014F900, self, 0, 0);
    self->f740 = func_001B6290(self->p73C, self, 0x2B7, 1);
}

struct Step_14C138 {
    u8 pad0[0xC];
    f32 dt;
};

struct Slot_14C138 {
    void* obj;
    void* f4;
    void* f8;
    u8 padC[8];
};

struct Node_14C138 {
    u8 pad[0x14];
    void* f14;
};

struct Obj_14C138 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x2DC - 0x18];
    s32 n2DC;
    Slot_14C138 slots[1];
    u8 pad2F4[0x428 - 0x2F4];
    void* f428;
    void* f42C;
    u8 f430[0x1C];
    s32 f44C;
    u8 pad450[0x470 - 0x450];
    f32 poly[3];
    u8 pad47C[4];
    f32 a480[44];
    f32 b530[44];
    f32 o5E0[44];
};

extern Step_14C138* D_002623C8;
extern f32 D_00275C60[];
extern u8 D_00261CA0[];

void func_00124A48(Obj_14C138* self);
void func_00124DF8(Obj_14C138* self, s32 n, void* table);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6598(void* a, void* b);
void func_001B6DF8(void* a, void* b);
void func_0014C2F0(Obj_14C138* self);

void func_0014C138(Obj_14C138* self)
{
    s32 i = 0;
    func_00124A48(self);
    func_00124DF8(self, 3, D_00261CA0);
    self->f42C = func_001B6290(self->f428, 0, 0x3FB, 0);
    func_001B6598(self->f42C, self->f430);
    func_001B6DF8(self->f42C, self);
    for (; i < self->n2DC; i++) {
        Slot_14C138* s = &self->slots[i];
        Node_14C138* n = (Node_14C138*)func_0015A448(self->f14, s->obj, self);
        s->obj = n;
        s->f8 = func_0015A480(n->f14, 0x3F7, n);
        s->f4 = func_0015A480(n->f14, 0x3F6, n);
    }
    f32* p = self->poly;
    f32 g = D_002623C8->dt;
    f32 v = self->poly[0] + g * (p[1] + g * p[2]);
    f32 lo = D_00275C60[0];
    f32 hi = D_00275C60[1];
    f32 t;
    if (v < lo) {
        t = lo;
    } else if (hi < v) {
        t = hi;
    } else {
        t = v;
    }
    f32 u = 1.0f - t;
    f32* pa = self->a480;
    f32* pb = self->b530;
    f32* po = self->o5E0;
    for (u32 k = 0; k < 44; k++) {
        *po++ = u * *pa++ + t * *pb++;
    }
    self->f44C = (s32)self->o5E0[0];
    func_0014C2F0(self);
}

struct Self_14F110 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
    u8 pad1[0xC];
    f32 f564;
    u8 pad2[0x14];
    s32 f57C;
    s32 f580;
    s32 f584;
    s32 f588;
};

struct Sub_14F110;

extern f32 D_0026185C;

s32 func_00126D60(Sub_14F110* sub, f32 value);

void func_0014F110(Self_14F110* self, s32 state)
{
    if (self->f550 != state) {
        if (self->f550 != 2) {
            self->f550 = state;
        } else {
            self->f57C = 0;
            self->f580 = 0;
            self->f584 = 0;
            self->f588 = 0;
            self->f550 = state;
        }
        self->f554 = D_0026185C;
        if (state == 5) {
            (void)func_00126D60((Sub_14F110*)self, self->f564);
        }
    }
}

struct Cfg_14C5E8 { u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; };
extern u8 D_00261EF0[];
void func_00151E20(Cfg_14C5E8* self, f32 amount);

void func_0014C5E8(Cfg_14C5E8* self)
{
    f32 one = 1.0f;
    f32 ratio = (f32)self->f2D0 / (f32)self->f2D4;
    f32 c;
    if (ratio < 0.0f) {
        c = 0.0f;
    } else if (one < ratio) {
        c = 1.0f;
    } else {
        c = ratio;
    }
    func_00151E20((Cfg_14C5E8*)D_00261EF0, 1.0f - c * 0.8f);
}

struct Obj_14D9A8 { void* vt; s32 kind; };

extern u8 D_002176D0[];
extern u8 D_00217708[];

void* func_0018D5C0(u32 n);

Obj_14D9A8* func_0014D9A8(s32 kind)
{
    Obj_14D9A8* p;
    switch (kind) {
    case 0:
        p = (Obj_14D9A8*)func_0018D5C0(0x1C);
        p->vt = (void*)D_002176D0;
        break;
    case 1:
        p = (Obj_14D9A8*)func_0018D5C0(0x1D0);
        p->vt = (void*)D_00217708;
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

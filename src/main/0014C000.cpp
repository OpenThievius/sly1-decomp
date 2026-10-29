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

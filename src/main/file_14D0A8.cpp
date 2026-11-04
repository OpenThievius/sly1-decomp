// SPDX-License-Identifier: AGPL-3.0-or-later
// Curves: piecewise-linear and spline tracks of keyed values (two kinds, made by func_0014D9A8,
// with the method tables D_002176D0 and D_00217708), and the segment-length and lookup helpers.
#include "common.h"
#include "asm_func.h"

struct __attribute__((aligned(16))) Quad_14D938 { s32 w[4]; };

struct Obj_14D9A8 { void* vt; s32 kind; };

struct Obj_14DA38 { u8 pad0[0x8]; s32 wrap; s32 cnt; f32* p10; };
struct Obj_14DA68 { u8 pad0[0x8]; s32 wrap; s32 cnt; u8 pad1[4]; f32* p14; };

struct Obj_14DB40 { u8 pad[0xC]; u32 index; u32 base; };
struct Obj_14DB58 { u8 pad[0xC]; u32 index; u32 pad10; u32 base; };

struct __attribute__((aligned(16))) Vec_14DB78 { f32 v[4]; };
struct Src_14DB78;
struct VT_14DB78 {
    void* slot0;
    void (*f4)(Src_14DB78* self, Vec_14DB78* out, s32 flag);
};
struct Src_14DB78 { VT_14DB78* vt; };
struct Obj_14DB78 {
    Src_14DB78* src;
    Vec_14DB78* a;
    Vec_14DB78* b;
};

struct Obj_14DBD0 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };
struct Ctx_14DBD0 { Obj_14DBD0* self; s32 a1; s32 a2; s32 pad; };
struct Out_14DBD0 { f32 f; s32 p1; s32 p2; s32 p3; };

struct Span_0014DD00 { u8 pad0[0x10]; f32* p; };

struct Obj_14DD28 { void** vtbl; u8 pad0[4]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };
typedef void (*Fn_14DD28)(void* self);

struct Frame_0014DE08 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };
struct Frame_0014DE40 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };

struct __attribute__((aligned(16))) Quad_0014DE78 { s32 v[4]; };
struct __attribute__((packed)) Pack4_0014DE78 { s32 v; };
struct Table_0014DE78 { u8 pad0[8]; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; };

struct Obj_14DF98 { u8 pad0[0x14]; f32* p14; };
struct Obj_14E000 { u8 pad0[0x10]; f32* p10; };
struct Obj_14E068 { u8 pad0[0xC]; s32 f0C; u8 pad1[4]; void* f14; void* f18; };
struct Obj_14E090 { u8 pad0[0xC]; s32 f0C; f32* f10; f32* f14; void* f18; };
struct Frac_14E090 { s32 idx; f32 t; };
struct Obj_14E170 { u8 pad0[0x8]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };
struct Obj_14E2A0 { u8 pad0[0x8]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };

struct Obj_14E3D0 { void** vtbl; u8 pad0[4]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; void* p1C; void* p20; };
typedef void (*Fn_14E3D0)(void* self);

struct Obj_14E500 { u8 pad[0x1C0]; s32 value; };

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

struct Obj_14E6A8 { void** vtbl; };
typedef f32 (*Fn_14E6A8)(void* self);
typedef void (*Fn2_14E6A8)(void* self, f32 t, s32 a1, void* a2);

struct Obj_14E910 { u8 pad0[0x14]; f32* p14; void* p18; void* p1C; void* p20; };
struct Obj_14E990 { u8 pad0[0x10]; f32* p10; u8 pad1[0x170 - 0x14]; f32 buf170[4]; };

struct Obj_14EA48 {
    u8 pad0[0xC];
    s32 n;
    f32* p10;
    f32* p14;
    u8* p18;
    u8* p1C;
    u8* p20;
};

struct Obj_14EC70 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };
struct Ctx_14EC70 { Obj_14EC70* self; s32 a1; s32 a2; s32 pad; };
struct Out_14EC70 { f32 f; s32 p1; s32 p2; s32 p3; };

struct Obj_14ED98 { void** vtbl; };
typedef f32 (*Slot6_14ED98)(void* self);
typedef void (*Slot11_14ED98)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

// An entry of a table of functions.
typedef void (*Fn_Table)();
extern const Fn_Table D_002176D0[];
extern const Fn_Table D_00217708[];

f32 func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);
void func_00130B48(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void func_00186320(Vec_14DB78* p, Vec_14DB78* a, Vec_14DB78* b, f32* o1, f32* o2);
void func_00188700(void* a, void* b, void* c, f32 w);
void func_001891C0(void* self, void* arg, Quad_14D938* out);
void* func_0018D500(s32 size);
void* func_0018D5C0(u32 n);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);
void func_001EB168(void* fn, f32 f12, f32 f13, f32 f14, f32 f15, void* ctx, void* out, s32 a3);

f32 func_0014D0A8(s32 n, void* buf, void* other);
f32 func_0014D138(s32 count, f32* table, s32 wrap, f32 x);
s32 func_0014D1A0(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi);
void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void func_0014D3A8(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);
void func_0014D938(s32 count, Quad_14D938* dst, void* arg, void* self);
Obj_14D9A8* func_0014D9A8(s32 kind);
f32 func_0014DA18(void);
f32 func_0014DA28(void);
s32 func_0014DA38(void* self, f32 t, f32* a, f32* b);
s32 func_0014DA68(void* self, f32 t, f32* a1, f32* a2);
void func_0014DA98(void);
f32 func_0014DB40(Obj_14DB40* obj);
f32 func_0014DB58(Obj_14DB58* obj);
void func_0014DB70(void);
f32 func_0014DB78(Obj_14DB78* self);
void func_0014DBD0(Obj_14DBD0* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
f32 func_0014DD00(Span_0014DD00* self);
void func_0014DD28(Obj_14DD28* self, void* src);
void func_0014DE08(Frame_0014DE08* self, s32 a1, s32 a2);
void func_0014DE40(Frame_0014DE40* self, s32 a1, s32 a2);
void func_0014DE78(Table_0014DE78* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);
void func_0014DF68(u8* self, void* a, void* b);
f32 func_0014DF98(Obj_14DF98* self, f32 t);
f32 func_0014E000(Obj_14E000* self, f32 t);
f32 func_0014E068(Obj_14E068* self);
void func_0014E090(Obj_14E090* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
void func_0014E170(Obj_14E170* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void func_0014E2A0(Obj_14E2A0* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void func_0014E3D0(Obj_14E3D0* self, void* src);
void func_0014E500(Obj_14E500* obj);
void func_0014E510(Obj_14E510* self, s32 i);
void func_0014E6A8(Obj_14E6A8* self, s32 a1, void* a2);
f32 func_0014E910(Obj_14E910* self, f32 t);
f32 func_0014E990(Obj_14E990* self, f32 t);
void func_0014EA48(Obj_14EA48* self);
void func_0014EC70(Obj_14EC70* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
void func_0014ED98(Obj_14ED98* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

ASM_FUNC(func_0014D0A8);

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

s32 func_0014D1A0(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi)
{
    f32 r = func_0014D138(n, arr, wrap, x);
    s32 i = 1;
    while (i < n && !(r < arr[i])) i++;
    if (i >= n) i--;
    i--;
    if (lo) *lo = r - arr[i];
    if (hi) *hi = arr[i + 1] - arr[i];
    return i;
}

ASM_FUNC(func_0014D280);

INCLUDE_RODATA(D_00249FBC);
ASM_FUNC(func_0014D3A8);

ASM_FUNC(func_0014D680);

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

Obj_14D9A8* func_0014D9A8(s32 kind)
{
    Obj_14D9A8* p;
    switch (kind) {
    case 0:
        p = (Obj_14D9A8*)func_0018D5C0(0x1C);
        p->vt = (void*)((u8*)D_002176D0);
        break;
    case 1:
        p = (Obj_14D9A8*)func_0018D5C0(0x1D0);
        p->vt = (void*)((u8*)D_00217708);
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

f32 func_0014DA18(void)
{
    return 0.0f;
}

f32 func_0014DA28(void)
{
    return 0.0f;
}

s32 func_0014DA38(void* self, f32 t, f32* a, f32* b)
{
    Obj_14DA38* o = (Obj_14DA38*)self;
    return func_0014D1A0(t, o->cnt, o->p10, o->wrap, a, b);
}

s32 func_0014DA68(void* self, f32 t, f32* a1, f32* a2)
{
    Obj_14DA68* o = (Obj_14DA68*)self;
    return func_0014D1A0(t, o->cnt, o->p14, o->wrap, a1, a2);
}

ASM_FUNC(func_0014DA98);

f32 func_0014DB40(Obj_14DB40* obj) { u32 address = obj->index * 4 + obj->base; return *(f32*)(address - 4); }

f32 func_0014DB58(Obj_14DB58* obj) { u32 address = obj->index * 4 + obj->base; return *(f32*)(address - 4); }

LINKER_REMNANT(func_0014DB70);

f32 func_0014DB78(Obj_14DB78* self)
{
    Vec_14DB78 p;
    f32 o1;
    f32 o2;
    if (self->src->vt->f4)
        self->src->vt->f4(self->src, &p, 0);
    func_00186320(&p, self->a, self->b, &o1, &o2);
    return o2;
}

void func_0014DBD0(Obj_14DBD0* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    Ctx_14DBD0 ctx;
    Out_14DBD0 out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.self = self;
    ctx.a1 = a1;
    ctx.a2 = a2;
    f14 = self->f10[0];
    f13 = (self->f10[1] - f14) * 0.1f;
    func_001EB168((void*)func_0014DB78, f12, f13, self->f8 ? -3.4028235e+38f : f14, self->f8 ? 3.4028235e+38f : self->f10[self->fC - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = self->vt[1];
        if (fn != 0) {
            ((void (*)(Obj_14DBD0*, s32, s32, f32))fn)(self, a3, a4, out.f);
        }
    }
    if (a5 != 0) {
        *a5 = out.f;
    }
    if (a6 != 0) {
        *a6 = ((f32 (*)(Obj_14DBD0*, f32))self->vt[5])(self, out.f);
    }
}

LINKER_REMNANT(func_0014DCF8);

f32 func_0014DD00(Span_0014DD00* self)
{
    f32* p = self->p;
    f32 b = p[1]; f32 a = p[0]; return (b - a) * 0.1f;
}

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

void func_0014DE08(Frame_0014DE08* self, s32 a1, s32 a2)
{
    func_0014D280(self->f0C, self->f18, self->f10, self->f08, a1, a2);
}

void func_0014DE40(Frame_0014DE40* self, s32 a1, s32 a2)
{
    func_0014D280(self->f0C, self->f18, self->f14, self->f08, a1, a2);
}

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

void func_0014DF68(u8* self,void* a,void* b) { func_0014D938(*(s32*)(self+0xC),*(Quad_14D938**)(self+0x18),a,b); }

f32 func_0014DF98(Obj_14DF98* self, f32 t0)
{
    f32 a, b;
    s32 i = func_0014DA38(self, t0, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->p14[i] + t * self->p14[i + 1];
}

f32 func_0014E000(Obj_14E000* self, f32 t0)
{
    f32 lo, hi;
    s32 idx = func_0014DA68(self, t0, &lo, &hi);
    f32 t = lo / hi;
    return (1.0f - t) * self->p10[idx] + t * self->p10[idx + 1];
}

f32 func_0014E068(Obj_14E068* self)
{
    return func_0014D0A8(self->f0C, self->f18, self->f14);
}

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

void func_0014E170(Obj_14E170* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = func_0014D1A0(t, self->cnt, self->p10, self->a8, 0, 0);
    s32 ia;
    f32 fb;
    func_0014D680(a1, a2, self->cnt, self->p18, idx, self->a8, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->p14[ia] + fb * self->p14[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->p10[ia] + fb * self->p10[ia + 1];
}

void func_0014E2A0(Obj_14E2A0* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = func_0014D1A0(t, self->cnt, self->p14, self->a8, 0, 0);
    s32 ia;
    f32 fb;
    func_0014D680(a1, a2, self->cnt, self->p18, idx, self->a8, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->p14[ia] + fb * self->p14[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->p10[ia] + fb * self->p10[ia + 1];
}

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
    func_0014E500((Obj_14E500*)self);
}

void func_0014E500(Obj_14E500* obj) { obj->value = -1; }

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

ASM_FUNC(func_0014E5B8);

void func_0014E6A8(Obj_14E6A8* self, s32 a1, void* a2)
{
    f32 t = ((Fn_14E6A8)self->vtbl[6])(self);
    Fn2_14E6A8 fn = (Fn2_14E6A8)self->vtbl[1];
    if (fn) {
        fn(self, t, a1, a2);
    }
}

ASM_FUNC(func_0014E710);

ASM_FUNC(func_0014E828);

f32 func_0014E910(Obj_14E910* self, f32 t0)
{
    f32 a, b;
    s32 i = func_0014DA38(self, t0, &a, &b);
    u32 off = i * 16;
    f32 r = func_00130C20((u8*)self->p18 + off, (u8*)self->p20 + off,
                          (u8*)self->p18 + (off + 16), (u8*)self->p1C + (off + 16), b, a);
    return r + self->p14[i];
}

f32 func_0014E990(Obj_14E990* self, f32 t0)
{
    f32 lo, a, b;
    s32 idx = func_0014DA68(self, t0, &lo, 0);
    func_0014E510((Obj_14E510*)self, idx);
    s32 n = func_0014D1A0(lo, 20, self->buf170, 0, &a, &b);
    f32 t = a / b;
    f32 u = ((f32)n + t) * 0.0526315793f;
    return (1.0f - u) * self->p10[idx] + u * self->p10[idx + 1];
}

// Read only by the assembly func_0014EB10. Defined in C, ahead of func_0014EA48 (which reads no
// .rodata) so the compiler leaves .rodata before that function: an include would align the label
// to 8, as its address is, but this file's .rodata starts 4 bytes past a 16-byte boundary.
extern const f32 D_00249FC8 = 3.4028235e+38f;

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

ASM_FUNC(func_0014EB10);

void func_0014EC70(Obj_14EC70* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    Ctx_14EC70 ctx;
    Out_14EC70 out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.self = self;
    ctx.a1 = a1;
    ctx.a2 = a2;
    f14 = self->f10[0];
    f13 = (self->f10[1] - f14) * 0.1f;
    func_001EB168((void*)func_0014DA98, f12, f13, self->f8 ? -3.4028235e+38f : f14, self->f8 ? 3.4028235e+38f : self->f10[self->fC - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = self->vt[1];
        if (fn != 0) {
            ((void (*)(Obj_14EC70*, s32, s32, f32))fn)(self, a3, a4, out.f);
        }
    }
    if (a5 != 0) {
        *a5 = out.f;
    }
    if (a6 != 0) {
        *a6 = ((f32 (*)(Obj_14EC70*, f32))self->vt[5])(self, out.f);
    }
}

void func_0014ED98(Obj_14ED98* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    s32 q4 = p4;
    s32 q3 = p3;
    s32 q2 = p2;
    s32 q1 = p1;
    s32 q6 = p6;
    s32 q5 = p5;
    f32 r = ((Slot6_14ED98)self->vtbl[6])(self);
    Slot11_14ED98 fn = (Slot11_14ED98)self->vtbl[11];
    if (fn != 0) {
        fn(self, q1, r, q2, q3, q4, q5, q6);
    }
}

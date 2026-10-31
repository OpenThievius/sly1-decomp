// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1300D8 { u8 pad[0x20]; s32 f20; };

void func_001300D8(Obj_1300D8* a0, s32 a1)
{
    a0->f20 += a1;
}

void func_00130B48(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, s32 n, void* buf);
void func_0014D0A8(s32 n, void* buf, s32 zero);

void func_00130C20(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y)
{
    u8 buf[0x140];
    func_00130B48(a, b, c, d, x, 0.0f, y, 20, buf);
    func_0014D0A8(20, buf, 0);
}

struct Quad_130F48 {
    f32 c0, c1, c2, c3;
} __attribute__((aligned(16)));

struct Span_130F48 {
    Quad_130F48 head;
    f32 len;
    f32 halfw;
    s32 lo;
    s32 mid;
    s32 hi;
    f32 p;
    f32 q;
};

void func_00130F48(Span_130F48* d, const Quad_130F48* src, s32 n, f32 x, f32 y)
{
    f32 fn = (f32)n;
    f32 inv = 1.0f / fn;
    s32 half = n / 2;
    s32 t;
    s32 lo;
    f32 u;

    d->head = *src;
    d->len = fn;
    d->mid = half;
    t = (s32)(x / inv) >> 1;
    d->hi = half + t;
    d->halfw = (f32)t;
    lo = half - t;
    d->lo = lo;
    u = (f32)lo / fn;
    d->p = src->c0 + u * (src->c1 + u * src->c2);
    d->q = src->c0 + 0.5f * (src->c1 + 0.5f * src->c2) + y;
}



f32 func_00131000(const Span_130F48* s, s32 x)
{
    if (x < s->lo || s->hi < x) {
        f32 u = (f32)x / s->len;
        return s->head.c0 + u * (s->head.c1 + u * s->head.c2);
    }
    if (x == s->lo || x == s->hi) {
        return s->p;
    }
    if (x < s->mid) {
        f32 t = (f32)(x - s->lo) / s->halfw;
        return (1.0f - t) * s->p + t * s->q;
    }
    if (s->mid < x) {
        f32 t = (f32)(x - s->mid) / s->halfw;
        return (1.0f - t) * s->q + t * s->p;
    }
    return s->q;
}

typedef void (*VFn_131140)(void* self, s32 arg);

struct Obj_131140 {
    VFn_131140* vtbl;
    u8 pad0[0x300 - 4];
    s32 f300;
    s32 f304;
    s32 f308;
    u8 pad1[8];
    f32 f314;
};

void func_001365A0(void* self, s32 arg);

void func_00131140(Obj_131140* self)
{
    self->vtbl[8](self, 0);
    func_001365A0(self, 0);
    self->f300 = 0;
    self->f304 = 0;
    self->f308 = 0;
    self->f314 = 0.4f;
}

struct Obj_130070 { s32 state; };

void func_0012FE70(void* self);
void func_0012FFE8(void* self);

void func_00130070(Obj_130070* self)
{
    switch (self->state) {
    case 0:
        func_0012FE70(self);
        func_0012FFE8(self);
        break;
    case 1:
        func_0012FFE8(self);
        func_0012FE70(self);
        break;
    }
}

struct Node_1300E8 { Node_1300E8* next; s32 key; };
struct List_1300E8 { Node_1300E8* head; };

s32 func_001300E8(List_1300E8* list, s32 key)
{
    Node_1300E8* node = list->head;
    while (node != 0) {
        if (node->key == key) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

struct Obj_130110 { s32 pad0; s32 field4; };

extern u8 D_00259F38[];
s32 func_0011BF30(void);
void func_0011A708(void* dst, s32 value);

void func_00130110(Obj_130110* self)
{
    if (self->field4 == 0) {
        s32 v = func_0011BF30();
        self->field4 = v;
        func_0011A708(D_00259F38, v);
    }
}

struct Inner_130158 { s32 pad0; s32 value; };
struct Holder_130158 { Inner_130158* inner; };

void func_00130158(Holder_130158* holder, s32* out)
{
    *out = holder->inner->value;
}

void func_001303F0(f32* p0, f32* p1, f32* p2, f32 dur, f32 t, f32 e, f32 a, f32 b, f32 c, f32 dd)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    f32 span = c - a;
    if (p0 != 0) {
        f32 uv = u * v;
        f32 vv = v * v;
        f32 uu = u * u;
        f32 uvv = uv * v;
        f32 vvv = vv * v;
        f32 uuv = uu * v;
        f32 t5 = uvv * 3.0f;
        f32 uvd = uvv * dur;
        f32 t4 = uuv * 3.0f;
        f32 t0 = vvv + t5;
        f32 uuu = uu * u;
        f32 p2b = uvd * b;
        f32 p1a = t0 * a;
        f32 q = uuv * dur;
        f32 t3 = uuu + t4;
        f32 s = p1a + p2b;
        f32 qd = q * dd;
        f32 t3c = t3 * c;
        f32 r = s - qd;
        *p0 = r + t3c;
    }
    if (p1 != 0) {
        f32 t1 = (u * (6.0f * v)) / dur * span;
        f32 t2 = (1.0f - (u * (4.0f - 3.0f * u))) * b;
        f32 w2 = 3.0f * u + -2.0f;
        f32 t3 = (u * w2) * dd;
        *p1 = ((t1 + t2) + t3) * e;
    }
    if (p2 != 0) {
        f32 dd2 = dur * dur;
        f32 ee = e * e;
        f32 s1 = (6.0f - 12.0f * u) / dd2 * span;
        f32 s2 = (6.0f * u - 4.0f) / dur * b;
        f32 s3 = (6.0f * u - 2.0f) / dur * dd;
        *p2 = ((s1 + s2) + s3) * ee;
    }
}

struct Rgba_133B58
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    Rgba_133B58() {}
    Rgba_133B58(const Rgba_133B58& o) { *this = o; }
};
struct Gs_133B58;
struct Span_133B58;
struct Self_133B58
{
    u8 pad000[0x30C];
    f32 phase;
};

extern Rgba_133B58 D_002610E0;
extern Rgba_133B58 D_002610D8;
extern Span_133B58 D_00261280;
extern Span_133B58 D_002612B0;

f32 func_00205210(f32 x);
f32 func_00131000(Span_133B58* s, s32 x);
void func_001613C0(Gs_133B58* gs, s32 a, s32 b, s32 c);
void func_00161458(Gs_133B58* gs, u32 c);
void func_00161670(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);
void func_001615F0(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);

struct Lerp_133B58
{
    static s32 Channel(s32 a, s32 b, f32 t)
    {
        if (a == b)
        {
            return b;
        }
        if (a < b)
        {
            return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        }
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }

    static Rgba_133B58 Mix(Rgba_133B58 a, Rgba_133B58 b, f32 t)
    {
        Rgba_133B58 c;
        c.r = Channel(a.r, b.r, t);
        c.g = Channel(a.g, b.g, t);
        c.b = Channel(a.b, b.b, t);
        c.a = Channel(a.a, b.a, t);
        return c;
    }
};

void func_00133B58(Self_133B58* self, Gs_133B58* gs)
{
    Rgba_133B58 c0;
    Rgba_133B58 c1;
    Rgba_133B58 c2;
    f32 step = 1.0f / 24.0f;
    f32 t;
    t = 0.5f - func_00205210(self->phase) * 0.5f;
    c0 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->phase + 1.5707964f) * 0.5f;
    c1 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->phase + 3.1415927f) * 0.5f;
    c2 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    s32 i;
    f32 x;

    func_001613C0(gs, 0x8C, 2, 0x41);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x7B45, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7B62, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x7B45, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7B62, 0, 0);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x80FA, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80DD, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x80FA, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80DD, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7B62, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x7B80, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v = r + 4.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7B62, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x7B80, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80DD, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x80C0, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v = r - 4.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80DD, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x80C0, 0, 0);
}

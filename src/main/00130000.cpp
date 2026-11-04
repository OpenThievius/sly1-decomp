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



struct Obj_1310F0 {
    u8 pad0[0x234];
    f32 f234;
    f32 f238;
    u8 pad1[0x2F0 - 0x23C];
    f32 f2F0;
    u32 f2F4;
};
void func_001AA1F0(Obj_1310F0* self, s32 a1);


struct Self_130B48;
struct Out_130B48 { u8 pad0[16]; };

void func_00130540(f32 f12, Self_130B48* a, u8* b, u8* c, u8* d, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

void func_00130B48(f32 k, Self_130B48* self, u8* a1, u8* a2, u8* a3, s32 count, Out_130B48* out, f32 start, f32 end)
{
    f32 step = (end - start) / (f32)(count - 1);
    f32 cur = start;
    s32 i;
    for (i = 0; i < count; i++) {
        func_00130540(k, self, a1, a2, a3, cur, 1.0f, (s32)(out + i), 0, 0);
        cur += step;
    }
}

void func_00130168(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero)
{
    f32 c[4];
    if (diff < 0.0001f) {
        diff = 0.0f;
    } else if (delta - diff < 0.0001f) {
        diff = 1.0f;
    } else {
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        s32 k = 0;
        c[2] = g3;
        c[3] = -diff;
        f32 a = g3 - d3;
        f32 b = d3 - g3;
        b = b - g3;
        a = a + delta;
        c[1] = b;
        c[0] = a;
        do {
            f32 m = lo + 1.0f / (f32)(1 << (k + 1));
            f32 v = m * (m * (m * c[0] + c[1]) + c[2]) + c[3];
            if (v < 0.0f) {
                lo = m;
            } else if (0.0f < v) {
                hi = m;
            } else {
                break;
            }
        } while (++k < 16);
        diff = (lo + hi) * 0.5f;
    }
    if (outF != 0) {
        f32 a3 = p1C * 3.0f;
        f32 b3 = p30 * 3.0f;
        c[3] = p4;
        c[0] = a3 - p4 - b3 + p24;
        c[1] = p4 * 3.0f - p1C * 6.0f + b3;
        c[2] = p4 * -3.0f + a3;
        *outF = diff * (diff * (diff * c[0] + c[1]) + c[2]) + p4;
    }
    if (outI != 0) {
        c[0] = p4 * -3.0f + p1C * 9.0f - p30 * 9.0f + p24 * 3.0f;
        c[1] = p4 * 6.0f - p1C * 12.0f + p30 * 6.0f;
        c[2] = p4 * -3.0f + p1C * 3.0f;
        f32 num = diff * (diff * c[0] + c[1]) + c[2];
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        c[2] = g3;
        c[0] = g3 * 3.0f - d3 * 3.0f + delta * 3.0f;
        c[1] = g3 * -4.0f + (d3 + d3);
        f32 den = diff * (diff * c[0] + c[1]) + c[2];
        *outI = num * scale / den;
    }
}

struct Rgba_132500
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    Rgba_132500() {}
    Rgba_132500(const Rgba_132500& o) { *this = o; }
};
struct Gs_132500;
struct Span_132500;

struct Pad_132500 { u8 pad[0x78]; f32 f78; };
struct Clock_132500 { u8 pad[0x478]; f32 f478; };

struct Obj_132500 {
    u8 pad0[0x260];
    s32 f260;
    u8 pad1[0x30C - 0x264];
    f32 f30C;
    u8 pad2[0x320 - 0x310];
    s32 f320;
};

extern s32 D_00262C68;
extern Pad_132500 D_00262C70;
extern Pad_132500 D_00262D38;
extern f32 D_00261860;
extern Clock_132500* D_00261990;
extern Rgba_132500 D_002610E8;
extern Rgba_132500 D_002610F0;
extern Rgba_132500 D_002610F8;
extern Rgba_132500 D_00261100;
extern Rgba_132500 D_00261108;
extern Rgba_132500 D_00261110;
extern Span_132500 D_002612E0;

void func_001613C0(Gs_132500* gs, s32 a, s32 b, u64 c);
void func_00161708(Gs_132500* gs, s32 reg, u64 value);
void func_00161458(Gs_132500* gs, u32 color);
void func_00161670(Gs_132500* gs, s32 x, s32 y, s32 z, s32 f);
void func_001615F0(Gs_132500* gs, s32 x, s32 y, s32 z, s32 f);
f32 func_001EA408(f32 a);
f32 func_00205210(f32 a);
void func_00136EC8(Obj_132500* self, f32* x, f32* y);
f32 func_00131000(const Span_132500* s, s32 i);

struct Gfx_132500 {
    static s32 LerpU8(s32 a, s32 b, f32 t)
    {
        if (a == b) {
            return b;
        }
        if (a < b) {
            return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        }
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }

    static Rgba_132500 Lerp(Rgba_132500 a, Rgba_132500 b, f32 t)
    {
        Rgba_132500 r;
        r.r = LerpU8(a.r, b.r, t);
        r.g = LerpU8(a.g, b.g, t);
        r.b = LerpU8(a.b, b.b, t);
        r.a = LerpU8(a.a, b.a, t);
        return r;
    }

    static f32 Wave(f32 x, f32 period, f32 phase)
    {
        return func_00205210(phase + (x / period) * 2.0f * 3.1415927f);
    }

    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
    }
};



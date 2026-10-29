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

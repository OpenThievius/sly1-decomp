// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Data_1B4BC8 { u8 pad0[0x20]; s32 count; };
struct Node_1B4BC8 {
    u8 pad0[0x10]; s32 flags; Data_1B4BC8* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4AD0(void* p);
f32 func_001EAAE0(f32 a, f32 b);

void func_001B4BC8(Node_1B4BC8* p)
{
    func_001B4AD0(p);
    if (p->data != 0) {
        f32 a = func_001EAAE0(p->f2C, p->f30);
        p->f3C = (f32)p->data->count / a;
        f32 b = func_001EAAE0(p->f34, p->f38);
        p->f44 = b;
        p->f48 = b;
    }
}

struct Data_1B4D18 { u8 pad0[0x20]; s32 count; };
struct Node_1B4D18 {
    u8 pad0[0x10]; s32 flags; Data_1B4D18* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

f32 func_001B4D18(Node_1B4D18* p)
{
    return (p->f40 / p->f3C) / ((f32)p->data->count / p->f3C + p->f44);
}

struct Data_1B4D48 { u8 pad0[0x20]; s32 count; };
struct Node_1B4D48 {
    u8 pad0[0x10]; s32 flags; Data_1B4D48* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Src_1B4D48 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; u16 u14; };

void func_001B4AA0(void* a, void* b);

void func_001B4D48(Node_1B4D48* p, Src_1B4D48* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4;
    p->f30 = s->f8;
    p->f34 = s->fC;
    p->f38 = s->f10;
    p->f40 = (f32)s->u14;
}

struct Data_1B4F18 { u8 pad0[0x20]; s32 count; };
struct Node_1B4F18 {
    u8 pad0[0x10]; s32 flags; Data_1B4F18* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

f32 func_001B4F18(Node_1B4F18* p)
{
    f32 x = p->f3C;
    f32 a;
    if (x < 0.0f) {
        x = -x;
        a = (f32)(p->data->count << 1) - p->f40;
    } else {
        a = p->f40;
    }
    return (a / x) / ((f32)(p->data->count << 1) / x + p->f44);
}

struct Data_1B4F80 { u8 pad0[0x20]; s32 count; };
struct Node_1B4F80 {
    u8 pad0[0x10]; s32 flags; Data_1B4F80* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Src_1B4F80 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; u16 u14; };

void func_001B4AA0(void* a, void* b);

void func_001B4F80(Node_1B4F80* p, Src_1B4F80* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4;
    p->f30 = s->f8;
}

struct Data_1B5108 { u8 pad0[0x20]; s32 count; };
struct Node_1B5108 {
    u8 pad0[0x10]; s32 flags; Data_1B5108* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4AD0(void* p);

void func_001B5108(Node_1B5108* p)
{
    func_001B4AD0(p);
    if (p->data != 0) {
        s32 n = p->data->count;
        if (n >= 2) {
            p->f34 = p->f30 / (f32)n;
        }
    }
}

struct Data_1B5160 { u8 pad0[0x20]; s32 count; };
struct Node_1B5160 {
    u8 pad0[0x10]; s32 flags; Data_1B5160* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};

extern u8 func_00166690[];
extern u8* D_00261990;
void func_001B4AD0(void* p);
f32 func_00205778(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);
void func_001B46E0(void* p, s32 k);

void func_001B5160(Node_1B5160* p, void* unused, Other_1B5160* q)
{
    if (p->data == 0) {
        return;
    }
    if (p->data->count < 2) {
        return;
    }
    if (*(void**)q != (void*)func_00166690) {
        return;
    }
    Vec2_1B5160* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (Vec2_1B5160*)(D_00261990 + 0x80);
    }
    f32 t = func_00205778(vv->y, vv->x);
    f32 r = func_001EAFE0(p->f2C - t, p->f30);
    s32 k = (s32)(r / p->f34);
    func_001B46E0((u8*)p + 0x10, k);
}

struct Data_1B5278 { u8 pad0[0x20]; s32 count; };
struct Node_1B5278 {
    u8 pad0[0x10]; s32 flags; Data_1B5278* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4750(void* p, f32 a, f32 b);
f32 func_002058A0(f32 a, f32 b);

void func_001B5278(Node_1B5278* p, f32 t)
{
    if (p->data != 0) {
        f32 r1 = func_002058A0(p->f1C + p->f2C * p->f3C * t, p->f34);
        f32 r2 = func_002058A0(p->f20 + p->f30 * p->f40 * t, p->f38);
        func_001B4750((u8*)p + 0x10, r1, r2);
    }
}

struct Data_1B5388 { u8 pad0[0x20]; s32 count; };
struct Node_1B5388 {
    u8 pad0[0x10]; s32 flags; Data_1B5388* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B5388(Node_1B5388* p, f32 a, f32 b)
{
    p->f3C = a;
    p->f40 = b;
}

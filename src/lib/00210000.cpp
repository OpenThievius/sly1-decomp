// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Object_2107B8 { u8 pad1[8]; s32 mode; u8 pad2[0xA0]; s32 fieldAC; u8 pad3[0x68]; s32 field118; u8 pad4[0x704]; s32 field820; };

s32 func_002107B8(Object_2107B8* obj)
{
    s32 value;
    s32 result = 1;
    if (obj->mode == 2) {
        goto done;
    }
    value = obj->field118;
    obj->mode = 2;
    obj->fieldAC = value;
done:
    obj->field820 = result;
    return result;
}

struct Stream_2117A0 { u8 pad[8]; u32 position; u8 pad2[0x18]; u32 limit; u32 span; };

u32 func_002117A0(Stream_2117A0* stream, s32 amount)
{
    u32 position = stream->position + (amount >> 3);
    if (position >= stream->limit) {
        position -= stream->span;
    }
    return position;
}

// NEAR: retail saves s0 and ra with 8-byte sd/ld, the default compiler with 16-byte sq/lq. Otherwise identical

struct Node_210160 {
    u8 pad000[0xF8];
    s32 f0F8;
    u8 pad0FC[0x54];
    s32 f150;
    u8 pad154[0x20];
    s32 f174;
    u8 pad178[0x40];
    s32 f1B8;
    u8 pad1BC[0x8];
    s32 f1C4;
    s32 f1C8;
    u8 pad1CC[0x8];
    s32 f1D4;
    s32 f1D8;
    u8 pad1DC[0x8];
    s32 f1E4;
};

void func_00210970(struct Node_210160* a, s32 b, s32 c);
void func_00210A80(struct Node_210160* a, s32 b, s32 c, s32 d);

void func_00210160(struct Node_210160* self, s32 count, s32 flag)
{
    s32 n = count;
    if (flag != 0) {
        if (self->f174 == 3) {
            s32 x;
            if (self->f150 == 3) {
                x = self->f1C4;
            } else {
                x = self->f1B8;
            }
            func_00210970(self, x, n - 1);
        } else {
            s32 x;
            s32 y;
            if (self->f150 == 3) {
                x = self->f1D4;
                y = self->f1E4;
            } else {
                x = self->f1C8;
                y = self->f1D8;
            }
            n = n - 1;
            func_00210A80(self, x, y, n);
        }
    }
    if (self->f0F8 == 1) {
        self->f0F8 = 2;
    }
}

// NEAR: body matches; the only difference is the prologue and epilogue, where retail saves s0, s1 and ra with sd/ld (8 bytes) as Sony's library code does, and SN GCC emits sq/lq.

struct Self_211700 { s64 bits; u8 pad0[0x8]; s32 f10; };
struct Peek_211700 { s64 bits; };
struct Bits_211700 { s64 bits; };

s64 func_002115F8(Peek_211700* p, s32 n);
void func_00211618(Bits_211700* p, s32 n);

s64 func_00211700(Self_211700* self)
{
    s64 r = func_002115F8((Peek_211700*)self, 1);
    func_00211618((Bits_211700*)self, 1);
    return r;
}

struct Ctx_211988 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};
struct Arg_211988 { u32 v; };

extern void func_002117D0(Arg_211988* a);
extern void func_00211838(Arg_211988* a);

void func_00211988(Ctx_211988* s0)
{
    u32 v = (u32)s0->f1C;
    u32 s3 = v & 0x7Fu;
    u32 t = ((v >> 16) & 3u) + ((v >> 8) & 0xFu);
    s32 s1 = s0->f0 - (s32)(t << 4);
    s32 s2 = s0->f8 + (s32)t;

    if (s0->f10 != 0) {
        if (s0->f14 != 0) {
            *(volatile u32*)0x1000B010 = s0->f10;
            *(volatile u32*)0x1000B020 = s0->f14;
            func_002117D0((Arg_211988*)(u32)(s0->f18 | 0x100));
        }
    }
    while (*(volatile s32*)0x10002010 < 0) {
        ;
    }
    *(volatile u32*)0x10002000 = s3;
    while (*(volatile s32*)0x10002010 < 0) {
        ;
    }
    if (s1 == 0) {
        return;
    }
    if (s2 == 0) {
        return;
    }
    *(volatile u32*)0x1000B410 = s1;
    *(volatile u32*)0x1000B430 = s0->f4;
    *(volatile u32*)0x1000B420 = s2;
    func_00211838((Arg_211988*)(u32)(s0->fC | 0x100));
}

extern u8 D_002504B8[];
extern u8 D_002504D8[];

struct Sub_210090 { u8 pad[0x28]; s32 f28; };
struct Obj_210090 {
    u8 pad0[0x120];
    s32 f120;
    u8 pad1[0x50];
    s32 f174;
    u8 pad2[0x48];
    Sub_210090* f1C0;
    u8 pad3[0xC];
    Sub_210090* f1D0;
    u8 pad4[0xC];
    Sub_210090* f1E0;
};

void func_0020B978(Obj_210090* self, void* a1);
s32 func_0020E3B8(Obj_210090* self);

s32 func_00210090(Obj_210090* self)
{
    Sub_210090* s1;
    s32 v;
    s32 mode = self->f174;
    if (mode == 3 && self->f120 != 0) {
        func_0020B978(self, D_002504B8);
        self->f120 = 0;
        mode = self->f174;
    }
    switch (mode) {
    case 3:
        s1 = self->f1C0;
        break;
    case 1:
        s1 = self->f1D0;
        break;
    case 2:
        s1 = self->f1E0;
        break;
    default:
        s1 = self->f1C0;
        func_0020B978(self, D_002504D8);
        break;
    }
    v = func_0020E3B8(self);
    if (v != 0) {
        s1->f28 = 1;
    }
    return v;
}

// EXACT: hardware registers read through volatile u32 pointers (lui/ori into a register, lw 0).

struct Out_002118A0 { u32 w00; u32 w04; u32 w08; u32 w0C; u32 w10; u32 w14; u32 w18; u32 w1C; u32 w20; };
struct Q_002118A0;
void func_00211838(Q_002118A0* q);
void func_002117D0(Q_002118A0* q);

void func_002118A0(Out_002118A0* out)
{
    func_00211838((Q_002118A0*)1);
    volatile u32* a = (volatile u32*)0x1000B410;
    out->w00 = *a;
    out->w04 = *(volatile u32*)0x1000B430;
    out->w08 = *(volatile u32*)0x1000B420;
    out->w0C = *(volatile u32*)0x1000B400;
    while ((*(volatile u32*)0x10002010 & 0xF0) != 0) {
    }
    func_002117D0((Q_002118A0*)0);
    out->w10 = *(volatile u32*)0x1000B010;
    out->w14 = *(volatile u32*)0x1000B020;
    out->w18 = *(volatile u32*)0x1000B000;
    out->w1C = *(volatile u32*)0x10002020;
    out->w20 = *(volatile u32*)0x10002010;
}

struct Node_2104A8 {
    u8 pad0[0xDC];
    s32 fDC;
    s32 fE0;
    s32 fE4;
};

struct Rec_2104A8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
};

s32 func_001E1FD0(char *dst, const char *fmt, ...);
void func_0020B978(struct Node_2104A8 *self, char *buf);

s32 func_002104A8(struct Node_2104A8 *self, struct Rec_2104A8 *rec) {
    char buf[0x100];
    s32 flag;
    if (self->fE0 != 0)
        flag = self->fDC >= rec->f4 && self->fE0 >= rec->f8;
    else
        flag = self->fE4 >= rec->fC * rec->f10;
    if (flag == 0) {
        func_001E1FD0(buf, "Too small buffer size for %dx%d picture\n", rec->f4, rec->f8);
        func_0020B978(self, buf);
    }
    return flag;
}

struct Bits_210000;
u32 func_0020F5B8(Bits_210000* self, u32 n);

void func_00210000(Bits_210000* self)
{
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 8);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 7);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 0x14);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 0x16);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 0x16);
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_00210D90(u32 a, s32 b)
{
    func_001F9D60();
    *(volatile u32*)0x1000B010 = (a & 0xFFFFFFF) | 0x80000000;
    *(volatile u32*)0x1000B020 = b >> 4;
    *(volatile u32*)0x1000B000 = 0x100;
    func_001F9DA8();
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_002117D0(u32 value)
{
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_00211838(u32 value)
{
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B400 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_00211B40(u32 value)
{
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B400 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
}

extern u8 D_0027B198[];
extern u8 D_0062C540[];
void func_001FFBE0(u8* a, u8* b);

void func_00211DE0(void)
{
    func_001FFBE0(D_0027B198, D_0062C540);
}

extern u8 D_0027B198[];
void func_001FFC08(u8* a);

void func_00211DF8(void)
{
    func_001FFC08(D_0027B198);
}

struct Str_2115C0 { u64 w0; u32 f8; u32 fC; u32 f10; u32 pad14; u64 w18; u32 f20; u32 f24; u32 f28; };
void func_00211618(Str_2115C0* self, s32 n);

void func_002115C0(Str_2115C0* self, u32 buf, u32 a, u32 b)
{
    self->f8 = buf;
    self->fC = buf;
    self->w0 = 0;
    self->f10 = 0;
    self->w18 = 0;
    self->f20 = a;
    self->f24 = a + b;
    self->f28 = b;
    func_00211618(self, 0);
}

struct Str_211748 { u64 w0; u32 f8; u32 fC; u32 f10; u32 pad14; u64 w18; u32 f20; u32 f24; u32 f28; };
void func_00211618(Str_211748* self, s32 n);

void func_00211748(Str_211748* self, s32 bytes)
{
    self->w0 = 0;
    self->f10 = 0;
    self->w18 += bytes << 3;
    self->fC = self->f8 + (s32)(self->w18 >> 3);
    if (self->fC >= self->f24) {
        self->fC -= self->f28;
    }
    func_00211618(self, 0);
}

struct Bits_2116B0 { u64 bits; };

s64 func_002115F8(Bits_2116B0* self, s32 n);
void func_00211618(Bits_2116B0* self, s32 n);

s64 func_002116B0(Bits_2116B0* self, s32 n)
{
    s64 r = func_002115F8(self, n);
    func_00211618(self, n);
    return r;
}

u32 func_00211AD8(s32 mode)
{
    u32 result = 0;
    switch (mode) {
    case 0:
        while (*(volatile s32*)0x10002010 < 0) {
        }
        result = 0;
        break;
    case 1:
        result = *(volatile u32*)0x10002010 >> 31;
        break;
    }
    return result;
}

struct Blk_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0xC]; u64 f20; s32 f28; u8 p2C[0xC]; u64 f38; };
struct Src_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0x14]; s32 f28; u8 p2C[0x18]; s32 f44; s32 f48; u8 p4C[4]; s32 f50; s32 f54; u8 p58[4]; s32 f5C; s32 f60; };
struct Ctx_210A80 {
    u8 p0[0x80]; s32 f80; u8 p84[4]; union { u64 d; u32 w[2]; } f88; u8 p90[0x20]; s32 fB0; s32 fB4; s32 fB8; u8 pBC[4]; s32 fC0; s32 fC4; u8 pC8[4]; s32 fCC; s32 fD0;
    u8 pD4[0x174 - 0xD4]; s32 f174; u8 p178[0x858 - 0x178]; Blk_210A80* f858;
};

s32 func_002107E0(Ctx_210A80* c, Src_210A80* s, void* a, void* b, void* d);
s32 func_002104A8(Ctx_210A80* c, Src_210A80* s);
s32 func_00211348(Ctx_210A80* c, Src_210A80* s);
s32 func_00210548(Ctx_210A80* c, Src_210A80* s);
s32 func_002107B8(Ctx_210A80* c);

void func_00210A80(Ctx_210A80* c, Src_210A80* a, Src_210A80* b)
{
    Src_210A80* s3;
    Src_210A80* s4;
    s32 s6 = 0;
    if (c->f174 == 2) {
        s3 = a;
        s4 = b;
        s6 = 0x40;
    } else {
        s3 = b;
        s4 = a;
    }
    (void)func_002107E0(c, s3, (u8*)c->f858 + 0x10, (u8*)c->f858 + 0x18, (u8*)c->f858 + 0x20);
    c->f80 = c->f858->f10;
    c->f88.d = 1;
    (void)func_002107E0(c, s4, (u8*)c->f858 + 0x28, (u8*)c->f858 + 0x30, (u8*)c->f858 + 0x38);
    c->f80 = c->f858->f28;
    c->f88.d = 1;
    Blk_210A80* p = c->f858;
    u64 v0 = p->f20 | (s64)s6;
    s32 a2 = s3->f5C;
    u64 v1 = p->f38 | (s64)s6;
    c->fCC = a2;
    p->f20 = v0;
    s32 a2b = s3->f60;
    p->f38 = v1;
    c->fD0 = a2b;
    c->fB4 = s3->f44;
    c->fB8 = s4->f48;
    c->fC0 = s3->f50;
    c->fC4 = s4->f54;
    if (func_002104A8(c, a)) {
        if (a->f28 == 1 && b->f28 == 1) {
            a->f10 <<= 1;
            if (c->fB0) {
                func_00211348(c, a);
            } else {
                func_00210548(c, a);
            }
            a->f10 >>= 1;
            func_002107B8(c);
        }
    }

}

struct Node_2107E0 {
    u8 pad0[0x18];
    s64 f18;
    s64 f20;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
};

struct Obj_2107E0 {
    u8 pad0[0x70];
    s32 f70;
    u8 pad1[0x4];
    s64 f78;
    s32 f80;
    u8 pad2[0x4];
    s64 f88;
    s32 f90;
    u8 pad3[0x5C];
    s64 fF0;
    s32 fF8;
};

s64 func_001FE890(s64 a, s64 b);

void func_002107E0(Obj_2107E0* self, Node_2107E0* node, s64* out1, s64* out3, s64* out4)
{
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s6;
    s32 s7;
    s64 v;
    s64 t88;

    if (self->f70 != 0) {
        v = node->f18;
        if (v >= 0) {
            *out1 = v;
        } else {
            s7 = self->f80;
            if (s7 < 0) {
                *out1 = v;
            } else {
                t88 = self->f88;
                s0 = (s32)t88;
                s2 = s0 & 1;
                v = func_001FE890(s2, self->f78 & 1);
                s6 = self->f90;
                v = func_001FE890(v, s6 & 1);
                s1 = (s32)v;
                *out1 = (s64)(s7 + ((s32)(func_001FE890(self->f78, s0) >> 1) + s1));
                if (func_001FE890(s2, self->f78 & 1)) {
                    self->f90 = s6 + 1;
                }
            }
        }
    } else {
        *out1 = node->f18;
    }
    if (self->fF8 == 2) {
        if (self->fF0 >= 0) {
            *out1 = self->fF0;
            self->fF8 = 0;
            self->fF0 = -1;
        }
    }
    *out3 = node->f20;
    *out4 = ((s64)node->f34 << 8) | (node->f2C | ((s64)node->f38 << 7) | ((s64)node->f3C << 6) | ((s64)node->f40 << 5) | ((s64)node->f30 << 3));
}

typedef u64 Quad_211BA8 __attribute__((mode(TI)));
extern volatile Quad_211BA8 D_0027B0C0[];
extern Quad_211BA8 D_0027B110[];
void func_00211B40(u32 value);

void func_00211BA8(void)
{
    func_00211B40(1);
    *(volatile u32*)0x10002010 = 0x40000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[0];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[1];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[2];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[3];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[4];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[4];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[4];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B0C0[4];
    *(volatile u32*)0x10002000 = 0x50000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0x58000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile Quad_211BA8*)0x10007010 = D_0027B110[0];
    *(volatile Quad_211BA8*)0x10007010 = D_0027B110[1];
    *(volatile u32*)0x10002000 = 0x60000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0x90000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002010 = 0x40000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0;
    while (*(volatile s32*)0x10002010 < 0) {
    }
}

struct Sub_2101F0 {
    u8 pad00[0x18];
    u64 f18;
    u64 f20;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
};

struct Obj_2101F0 {
    u8 pad000[0xA0];
    s32 fA0;
    s32 fA4;
    u8 pad0A8[0xE8 - 0xA8];
    s32 fE8;
    u8 pad0EC[0x13C - 0xEC];
    s32 f13C;
    u8 pad140[0x148 - 0x140];
    s32 f148;
    s32 f14C;
    s32 f150;
    u8 pad154[0x174 - 0x154];
    s32 f174;
    s32 f178;
    u8 pad17C[0x184 - 0x17C];
    s32 f184;
    s32 f188;
    s32 f18C;
    s32 f190;
    s32 f194;
    s32 f198;
    s32 f19C;
    s32 f1A0;
    s32 f1A4;
    s32 f1A8;
    u8 pad1AC[0x1B8 - 0x1AC];
    Sub_2101F0* f1B8;
    Sub_2101F0* f1BC;
    Sub_2101F0* f1C0;
    Sub_2101F0* f1C4;
    Sub_2101F0* f1C8;
    Sub_2101F0* f1CC;
    Sub_2101F0* f1D0;
    Sub_2101F0* f1D4;
    Sub_2101F0* f1D8;
    Sub_2101F0* f1DC;
    Sub_2101F0* f1E0;
    Sub_2101F0* f1E4;
    u8 pad1E8[0x828 - 0x1E8];
    u64 f828;
    u64 f830;
};

s32 func_002101F0(Obj_2101F0* p, s32 flag)
{
    Sub_2101F0* o = 0;
    s32 ok = 0;
    s32 lim = p->f174 == 3 ? 2 : 4;

    if (p->f150 == 3) {
        p->f1C0 = p->f1C4;
        p->f1D0 = p->f1D4;
        p->f1E0 = p->f1E4;
        if (p->fA0 + p->fA4 >= lim) {
            p->fE8 = 0;
            p->f1A8 = 0;
            p->f1A4 = 0;
        }
        if ((p->fE8 || p->f1A8) && !p->f1A4) {
            p->f1B8->f28 = 0;
            p->f1C8->f28 = 0;
            p->f1D8->f28 = 0;
        }
        p->fE8 = 0;
        p->f1A8 = 0;
        if (p->f174 == 3) {
            if ((p->f1B8->f28 == 1 || p->f1A4) && p->f1BC->f28 == 1) ok = 1;
        } else {
            if (((p->f1C8->f28 == 1 && p->f1D8->f28 == 1) || p->f1A4) && p->f1CC->f28 == 1 && p->f1DC->f28 == 1) ok = 1;
        }
    } else {
        if (flag == 0) {
            Sub_2101F0* t;
            t = p->f1B8; p->f1B8 = p->f1BC; p->f1BC = t;
            t = p->f1C8; p->f1C8 = p->f1CC; p->f1CC = t;
            t = p->f1D8; p->f1D8 = p->f1DC; p->f1DC = t;
        }
        p->f1C0 = p->f1BC;
        p->f1D0 = p->f1CC;
        p->f1E0 = p->f1DC;
        if (p->f174 == 3) {
            if (p->f150 != 2 || p->f1B8->f28 == 1) ok = 1;
        } else {
            Sub_2101F0* x = p->f174 == 1 ? p->f1DC : p->f1CC;
            if (p->f150 != 2) ok = 1;
            else if ((flag && x->f28 == 1) || (p->f1C8->f28 == 1 && p->f1D8->f28 == 1)) ok = 1;
        }
    }

    switch (p->f174) {
    case 2: o = p->f1E0; break;
    case 1: o = p->f1D0; break;
    case 3: o = p->f1C0; break;
    }
    o->f28 = 0;
    o->f18 = p->f828;
    o->f2C = p->f150;
    o->f20 = p->f830;
    o->f30 = p->f174;
    o->f34 = p->f13C;
    o->f38 = p->f188;
    o->f3C = p->f178;
    o->f40 = p->f184;
    o->f44 = p->f18C;
    o->f48 = p->f190;
    o->f4C = p->f194;
    o->f50 = p->f198;
    o->f54 = p->f19C;
    o->f58 = p->f1A0;
    o->f5C = p->f148;
    o->f60 = p->f14C;
    return ok;
}

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

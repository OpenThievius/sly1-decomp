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

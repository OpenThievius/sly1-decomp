// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 498/520 (95.8%), checked 2026-11-02
#include "common.h"
// NEAR: prologue save/move order (s0/s1), v0/v1 choice for the 0x1B8..0x1E4 pointer setup and the order of the final 0x84C/0x854 stores differ

struct Outer_20AE40 {
    s32 f0; s32 f4; s32 f8; s32 pad0C;
    s64 f10; s64 f18; s64 f20; s64 f28; s64 f30; s64 f38;
    s32 f40;
};
struct Inner_20AE40 {
    s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C;
    s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; s32 f34; s32 f38; s32 f3C;
    s32 f40; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58; s32 f5C;
    s32 f60; s32 f64; s32 f68; s32 f6C; s32 f70; s32 pad74; s64 f78; s32 f80; s32 pad84;
    s64 f88; s32 f90; s32 f94; s32 f98; s32 f9C; s32 fA0; s32 fA4; s32 fA8; s32 fAC;
    s32 fB0; s32 fB4; s32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8; s32 fCC;
    s32 fD0; s32 fD4; s32 fD8; s32 fDC; s32 fE0; s32 fE4; s32 fE8; s32 fEC;
    s64 fF0; s32 fF8; s32 fFC; s32 f100; s32 f104;
};
extern u8 D_00250070[];

s32 func_001F5C0C(s32 a, s32 b);
void func_0020B978(Inner_20AE40* a, u8* b);
void func_0020B240(Inner_20AE40* a, Inner_20AE40* b, s32 c);
s32 func_0020B278(Inner_20AE40* a, Inner_20AE40* b, s32 c, s32 d);
void func_0020B810(Inner_20AE40* a);
void func_0020B0C0(Outer_20AE40* a);
void func_0020B110(Outer_20AE40* a);
void func_0020B258(Inner_20AE40* a);
void func_0020C178(void);
void func_0020C188(void);

s32 func_0020AE40(Outer_20AE40* out, s32 mem, u32 size)
{
    (void)func_001F5C0C(mem, 0);
    Inner_20AE40* in = (Inner_20AE40*)(((u32)(mem + 3) >> 2) << 2);
    s32 diff = (s32)in - mem;
    u32 rest = size - diff;
    if (rest < 0x10C0) {
        func_0020B978(in, D_00250070);
        return 0;
    }
    Inner_20AE40* cur = (Inner_20AE40*)((u8*)in + 0x108);
    out->f40 = (s32)in;
    rest -= 0x10C0;
    s32 neg;
    func_0020B240(cur, (Inner_20AE40*)((u8*)in + 0x10C0), rest);
    neg = -1;
    out->f0 = 0;
    out->f4 = 0;
    out->f8 = 0;
    out->f10 = -1;
    out->f18 = -1;
    out->f20 = 0;
    out->f28 = -1;
    out->f30 = -1;
    out->f38 = 0;
    in->fB4 = 0;
    in->fB8 = 0;
    in->fBC = 0;
    in->fC0 = 0;
    in->fC4 = 0;
    in->fC8 = 0;
    in->fCC = 0;
    in->fD0 = 0;
    in->fD4 = 0;
    in->fD8 = 0;
    in->fDC = 0;
    in->fE0 = 0;
    in->fE4 = 0;
    in->fE8 = 0;
    in->fF8 = 0;
    in->f0C = 0;
    in->f14 = 0;
    in->f2C = 0;
    in->f34 = 0;
    in->f3C = 0;
    in->fF0 = -1;
    in->f1C = (s32)func_0020C178;
    in->f24 = (s32)func_0020C188;
    s32 r278 = func_0020B278(in, cur, 0x600, 8);
    in->f48 = 0;
    in->fFC = 0;
    in->f100 = 0;
    in->f104 = 0;
    in->f70 = 0;
    in->f78 = 0;
    in->f80 = neg;
    in->f88 = 0;
    in->f90 = 0;
    in->fAC = 0;
    in->f94 = neg;
    in->f98 = neg;
    in->f9C = neg;
    *(s32*)((u8*)in + 0x858) = (s32)out;
    in->f44 = r278;
    in->fB0 = 1;
    func_0020B810(in);
    func_0020B0C0(out);
    func_0020B110(out);
    *(s32*)((u8*)in + 0x1B8) = (s32)((u8*)in + 0x1E8);
    *(s32*)((u8*)in + 0x1BC) = (s32)((u8*)in + 0x250);
    *(s32*)((u8*)in + 0x1C4) = (s32)((u8*)in + 0x2B8);
    *(s32*)((u8*)in + 0x1C8) = (s32)((u8*)in + 0x320);
    *(s32*)((u8*)in + 0x1CC) = (s32)((u8*)in + 0x388);
    *(s32*)((u8*)in + 0x1D4) = (s32)((u8*)in + 0x3F0);
    *(s32*)((u8*)in + 0x1D8) = (s32)((u8*)in + 0x458);
    *(s32*)((u8*)in + 0x1DC) = (s32)((u8*)in + 0x4C0);
    *(s32*)((u8*)in + 0x1E4) = (s32)((u8*)in + 0x528);
    func_0020B258(cur);
    *(s32*)((u8*)in + 0x850) = neg;
    *(s32*)((u8*)in + 0x854) = 0;
    *(s32*)((u8*)in + 0x84C) = 0;
    *(s32*)((u8*)in + 0x81C) = 0x70003600;
}

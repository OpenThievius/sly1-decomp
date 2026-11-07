// SPDX-License-Identifier: AGPL-3.0-or-later
// The IPU library's transfers, from 0x2117D0 to 0x211B40, built whole (config/us/files.tsv): the
// start of a transfer from the IPU (func_002117D0, DMA channel 3) and to it (func_00211838,
// channel 4), each with the DMA suspended while its control register is written, the saving of
// both channels' state (func_002118A0) and its restoring (func_00211988), which the MPEG library
// calls around a picture, and the wait for the IPU (func_00211AD8). No data. Its end is chosen:
// src/lib/ipu_reset.cpp has its own copy of func_00211838, so the boundary is at 0x211AD8 or
// 0x211B40; this file ends at the second, with each file's helpers first. Its start is chosen
// too: the MPEG library's bit reader before it (func_002115C0 to func_002117A0) is called only
// by the MPEG library and uses no IPU register, so its own file ends here; the data can't
// decide. Written for this project from retail's code.
#include "common.h"

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_002117D0(u32 value)
{
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
}

void func_00211838(u32 value)
{
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B400 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
}

struct Out_002118A0 { u32 w00; u32 w04; u32 w08; u32 w0C; u32 w10; u32 w14; u32 w18; u32 w1C; u32 w20; };

void func_002118A0(Out_002118A0* out)
{
    func_00211838(1);
    volatile u32* a = (volatile u32*)0x1000B410;
    out->w00 = *a;
    out->w04 = *(volatile u32*)0x1000B430;
    out->w08 = *(volatile u32*)0x1000B420;
    out->w0C = *(volatile u32*)0x1000B400;
    while ((*(volatile u32*)0x10002010 & 0xF0) != 0) {
    }
    func_002117D0(0);
    out->w10 = *(volatile u32*)0x1000B010;
    out->w14 = *(volatile u32*)0x1000B020;
    out->w18 = *(volatile u32*)0x1000B000;
    out->w1C = *(volatile u32*)0x10002020;
    out->w20 = *(volatile u32*)0x10002010;
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
            func_002117D0(s0->f18 | 0x100);
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
    func_00211838(s0->fC | 0x100);
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

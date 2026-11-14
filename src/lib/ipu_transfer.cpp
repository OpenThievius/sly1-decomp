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
#include "mpeg_decoder.h"

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

void StartIpuOutputTransfer(u32 value)
{
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
}

void StartIpuInputTransfer(u32 value)
{
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B400 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
}


void SaveIpuDmaChannels(IpuDmaState* out)
{
    StartIpuInputTransfer(1);
    volatile u32* a = (volatile u32*)0x1000B410;
    out->inAddress = *a;
    out->inTagAddress = *(volatile u32*)0x1000B430;
    out->inCount = *(volatile u32*)0x1000B420;
    out->inControl = *(volatile u32*)0x1000B400;
    while ((*(volatile u32*)0x10002010 & 0xF0) != 0) {
    }
    StartIpuOutputTransfer(0);
    out->outAddress = *(volatile u32*)0x1000B010;
    out->outCount = *(volatile u32*)0x1000B020;
    out->outControl = *(volatile u32*)0x1000B000;
    out->bitPosition = *(volatile u32*)0x10002020;
    out->control = *(volatile u32*)0x10002010;
}

void RestoreIpuDmaChannels(IpuDmaState* s0)
{
    u32 v = (u32)s0->bitPosition;
    u32 s3 = v & 0x7Fu;
    u32 t = ((v >> 16) & 3u) + ((v >> 8) & 0xFu);
    s32 s1 = s0->inAddress - (s32)(t << 4);
    s32 s2 = s0->inCount + (s32)t;

    if (s0->outAddress != 0) {
        if (s0->outCount != 0) {
            *(volatile u32*)0x1000B010 = s0->outAddress;
            *(volatile u32*)0x1000B020 = s0->outCount;
            StartIpuOutputTransfer(s0->outControl | 0x100);
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
    *(volatile u32*)0x1000B430 = s0->inTagAddress;
    *(volatile u32*)0x1000B420 = s2;
    StartIpuInputTransfer(s0->inControl | 0x100);
}

u32 SyncIpu(s32 mode, s32 unused1)
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

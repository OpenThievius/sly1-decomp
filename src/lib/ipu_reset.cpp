// SPDX-License-Identifier: AGPL-3.0-or-later
// The IPU library's initialisation, from 0x211B40 to 0x211DE0, built whole (config/us/files.tsv):
// the start of the transfer to the IPU (func_00211B40, a copy of src/lib/ipu_transfer.cpp's
// func_00211838 for channel 4, so a helper each file has of its own) and the reset of the IPU
// with its default quantiser matrices and colour table (func_00211BA8, which the MPEG library's
// initialisation calls). Its .data is the library's identification string, the matrices and the
// table. Its start is chosen: the two copies of the helper put a boundary at 0x211AD8 or here, and
// the helper opening the file, as func_002117D0 opens the file before, puts it here. Its end is
// the frame-information object at 0x211DE0. Written for this
// project from retail's code.
#include "common.h"

// The library's identification string, 16 characters without a terminator.
char g_ipuLibraryVersion[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'i', 'p', 'u', ' ', ' ', '2', '4', '0', '0' };

typedef u64 Quad_211BA8 __attribute__((mode(TI)));
struct Quad_27B0C0 { u64 lo; u64 hi; } __attribute__((aligned(16)));

// The default quantiser matrices: intra, then one row of the non-intra (all 16), sent four times.
volatile Quad_27B0C0 g_ipuQuantiserMatrices[5] = {
    { 0x1616131013101008ULL, 0x1B1A181A16161616ULL },
    { 0x1B1B1A1A1A1A1B1BULL, 0x1D2222221D1D1D1BULL },
    { 0x20201D1D1B1B1D1DULL, 0x2223232526252222ULL },
    { 0x3030282828262623ULL, 0x5345453A38382E2EULL },
    { 0x1010101010101010ULL, 0x1010101010101010ULL },
};
// The colour table the reset loads.
Quad_27B0C0 g_ipuColourTable[2] = {
    { 0x03E0084204210000ULL, 0x1CE718C614A51084ULL },
    { 0x7C00294A2529001FULL, 0x39CE7FFF35AD318CULL },
};

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

void StartIpuInputForReset(u32 value)
{
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B400 = value;
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
}

void ResetIpu(void)
{
    StartIpuInputForReset(1);
    *(volatile u32*)0x10002010 = 0x40000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[0];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[1];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[2];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[3];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[4];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[4];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[4];
    *(volatile Quad_211BA8*)0x10007010 = *(volatile Quad_211BA8*)&g_ipuQuantiserMatrices[4];
    *(volatile u32*)0x10002000 = 0x50000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile u32*)0x10002000 = 0x58000000;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    *(volatile Quad_211BA8*)0x10007010 = *(Quad_211BA8*)&g_ipuColourTable[0];
    *(volatile Quad_211BA8*)0x10007010 = *(Quad_211BA8*)&g_ipuColourTable[1];
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

// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's TLB set-up, its own object from 0x1FA9B0 to 0x1FAC00, built whole
// (config/us/files.tsv): a file-local copy of the system call stub 0x56 (func_001FA9B0, which
// only func_001FAA00 calls; the public one is func_001F6BD0), the entry func_001FA9C0, which
// sets the TLB up through func_001FAA00 when func_001F6D20 reports 0x2000000 and calls
// func_001F6D30 otherwise, and func_001FAA00 itself, which reports the entry counts and writes
// the three tables of entries D_00277FE0 points to (original assembly, compiled with inline
// assembly: config/us/original_asm.tsv). Its .rodata (the four messages) and .data (the three
// tables and the record pointing to them) are this object's.
#include "common.h"
#include "asm_func.h"

ASM_FUNC(func_001FA9B0);

s32 func_001F6D20(void);
s32 func_001F6D30(void);
s32 func_001FAA00(void);

s32 func_001FA9C0(void)
{
    if (QueryMemorySize() == 0x2000000) {
        return func_001FAA00();
    }
    return func_001F6D30();
}

ASM_FUNC(func_001FAA00);

extern const char D_0024EC30[56] = "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n";
extern const char D_0024EC68[24] = "# TLB over flow (1)";
extern const char D_0024EC80[24] = "# TLB over flow (2)";
extern const char D_0024EC98[24] = "# TLB over flow (3)";

INCLUDE_DATA(D_00277D70);
INCLUDE_DATA(D_00277E40);
INCLUDE_DATA(D_00277F60);

extern u8 D_00277D70[], D_00277E40[], D_00277F60[], D_0027B184[];
void* D_00277FE0[8] = { (void*)0xD, (void*)0x12, (void*)8, 0, D_00277D70, D_00277E40, D_00277F60, D_0027B184 };

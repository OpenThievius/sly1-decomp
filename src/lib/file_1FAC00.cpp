// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1FAC00 to 0x1FAE38, built whole (config/us/files.tsv):
// func_001FAC00, original assembly (config/us/original_asm.tsv), which calls through the word at
// address 0 on a stack at 0x1000, returns from an exception with the registers saved in
// D_0062A540 and the special registers after it, and holds a second entry, func_001FAD68, which
// calls the functions of the constructor list D_0027B130 from the last to the first; and
// func_001FAE18, which calls func_001FAD68 once. Its .bss, 0x62A540 to 0x62A770, is the saved
// registers and the flag of func_001FAE18.
#include "common.h"
#include "asm_func.h"

static u8 D_0062A540[0x200];
static u64 D_0062A740;
static u64 D_0062A748;
static u64 D_0062A750;
static u64 D_0062A758;
static u64 D_0062A760;
static s32 D_0062A768;
static s32 D_0062A76C;

ASM_FUNC(func_001FAC00);

void func_001FAD68(void);

void RunConstructorsOnce(void)
{
    if (D_0062A76C == 0) {
        D_0062A76C = 1;
        func_001FAD68();
    }
}

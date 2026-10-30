// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the function body matches in behavior, but the candidate is 192 bytes versus retail 188 and uses sq/lq instead of sd/ld.
// NEAR: all body instructions match; SN emits sq/lq saves where retail uses sd/ld (and reports 192 vs 188 bytes).
#include "common.h"

void* func_00201BA8(void*);

void func_00201BB8(void* self)
{
    s16 kind = *(s16*)((u8*)func_00201BA8(self) + 6);
    if (kind == 1) {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000070 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x12000080 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000C0 = *(u64*)((u8*)self + 0x20);
    } else {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000020 = *(u64*)((u8*)self + 8);
        *(volatile u64*)0x12000090 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x120000A0 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000E0 = *(u64*)((u8*)self + 0x20);
    }
}

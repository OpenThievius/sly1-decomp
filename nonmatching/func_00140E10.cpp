// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: plain C models the aligned and unaligned copies, but GCC does
// not reproduce retail's four loads followed by four stores per iteration,
// the two copy loops' branch layout, or the final field-store schedule.
#include "common.h"
struct __attribute__((packed)) CopyQuad_140E10 { u64 a, b, c, d; };
void func_00140E10(void* self, s32 arg1, s32 arg2)
{
    u8* src = (u8*)self + 8;
    u8* dst = (u8*)self + 0x220;
    u8* end = (u8*)self + 0x208;
    *(s32*)((u8*)self + 0x20C) = 0;
    if ((((u32)src | (u32)dst) & 7) != 0) {
        do {
            *(CopyQuad_140E10*)dst = *(CopyQuad_140E10*)src;
            src += 32;
            dst += 32;
        } while (src != end);
    } else {
        do {
            *(CopyQuad_140E10*)dst = *(CopyQuad_140E10*)src;
            src += 32;
            dst += 32;
        } while (src != end);
    }
    *(s32*)dst = *(s32*)src;
    *(s32*)((u8*)self + 0x42C) = 1;
    *(s32*)((u8*)self + 0x424) = arg1;
    *(s32*)((u8*)self + 0x428) = arg2;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: this copy constructor is modelled with aligned and unaligned
// 32-byte copies, but the compiler emits different branch layout, register
// scheduling, and field stores than retail.
#include "common.h"
struct __attribute__((packed)) CopyQuad_140F48 { u64 a, b, c, d; };
void func_00140F48(void* self)
{
    u8* src = (u8*)self + 0x220;
    u8* dst = (u8*)self + 8;
    u8* end = (u8*)self + 0x420;
    *(s32*)((u8*)self + 4) = 0;
    if ((((u32)src | (u32)dst) & 7) != 0) {
        do {
            *(CopyQuad_140F48*)dst = *(CopyQuad_140F48*)src;
            src += 32;
            dst += 32;
        } while (src != end);
    } else {
        do {
            *(CopyQuad_140F48*)dst = *(CopyQuad_140F48*)src;
            src += 32;
            dst += 32;
        } while (src != end);
    }
    *(s32*)dst = *(s32*)src;
    *(s32*)((u8*)self + 0x20C) = 0;
}

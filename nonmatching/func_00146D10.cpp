// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: mask and MMIO behavior are modeled, but register ordering and conditional branch layout differ.
#include "common.h"

struct Context_146D10 {
    u8 pad00[0x50];
    void* state;
    u8 pad58[0x4E0];
    u64 flags;
};
s32 func_001300E8(void* state, s32 id);
s32 func_00146D10(void* unused, Context_146D10* context)
{
    if (context->flags & 0x80000000000ULL) goto failure;
    if (func_001300E8(context->state, 5)) goto failure;
    if (func_001300E8(context->state, 0x27)) goto failure;
    if (func_001300E8(context->state, 0x3B)) goto failure;
    if (func_001300E8(context->state, 0x40)) goto failure;
    if (!func_001300E8(context->state, 0x2E)) return 1;
failure:
    return 0;
}

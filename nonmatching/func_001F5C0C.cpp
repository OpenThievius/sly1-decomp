// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 44/192, checked 2026-11-01
// NEAR: check.py reports DIFFER; byte fill is modeled, but retail uses MMI fill blocks and aligned wide stores.
#include "common.h"

void* func_001F5C0C(void* destination, s32 value, u32 count)
{
    u8* bytes = (u8*)destination;
    for (u32 i = 0; i < count; i++) bytes[i] = (u8)value;
    return destination;
}

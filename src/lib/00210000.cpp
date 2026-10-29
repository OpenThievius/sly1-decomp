// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Object_2107B8 { u8 pad1[8]; s32 mode; u8 pad2[0xA0]; s32 fieldAC; u8 pad3[0x68]; s32 field118; u8 pad4[0x704]; s32 field820; };

s32 func_002107B8(Object_2107B8* obj)
{
    s32 value;
    s32 result = 1;
    if (obj->mode == 2) {
        goto done;
    }
    value = obj->field118;
    obj->mode = 2;
    obj->fieldAC = value;
done:
    obj->field820 = result;
    return result;
}

struct Stream_2117A0 { u8 pad[8]; u32 position; u8 pad2[0x18]; u32 limit; u32 span; };

u32 func_002117A0(Stream_2117A0* stream, s32 amount)
{
    u32 position = stream->position + (amount >> 3);
    if (position >= stream->limit) {
        position -= stream->span;
    }
    return position;
}

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

void func_001FD988() {}

s16 func_001FDDC8(void* object)
{
	return *(s16*)((u8*)object + 6);
}

s16 func_001FDDD0(void* object)
{
	return *(s16*)((u8*)object + 4);
}

void func_001FE190() {}

u8* func_001FF048(u8* input, u32* output)
{
	u8 byte = *input;
	u32 shift = 0;
	input++;
	u32 value = byte & 0x7F;
	if (byte & 0x80) {
		do {
			byte = *input;
			shift += 7;
			input++;
			value |= (byte & 0x7F) << shift;
		} while (byte & 0x80);
	}
	*output = value;
	return input;
}

void* func_001FFFE0(void* a0, void* a1) { return a1; }

void* func_001FFFE8(void* a0, void* a1) { return a1; }

u8* func_001FF090(u8* input, s32* output)
{
    u32 shift = 0;
    u32 value = 0;
    u8 byte;

    do {
        byte = *input++;
        value |= (u32)(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    if (shift < 32) {
        s32 signMask = -1;
        if (byte & 0x40) {
            value |= signMask << shift;
        }
    }
    *output = (s32)value;
    return input;
}

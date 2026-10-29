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

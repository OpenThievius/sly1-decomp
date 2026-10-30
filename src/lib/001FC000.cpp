// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

extern s32 D_00278640;

s32 func_001FE928(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

struct Node_1FFBE0 { s32 first; s32 second; s32 value; s32 link; s32 flag; s32 previous; };
extern Node_1FFBE0* D_0062A7B8;

void func_001FFBE0(s32 value, Node_1FFBE0* item)
{
    item->link = value;
    item->previous = (s32)D_0062A7B8;
    D_0062A7B8 = item;
    item->value = value;
    item->second = 0;
    item->flag = 0;
    item->first = 0;
    item->flag = 0;
    item->second = 0;
}

extern s32 D_002789D8;

s32 func_001FFFD0(s32 value)
{
    s32 previous = D_002789D8;
    D_002789D8 = value;
    return previous;
}

struct Cur_1FF490 { s32 off; s32 f4; s32 f8; s32 fC; };
struct List_1FF490 { Cur_1FF490** items; s32 count; };

void func_001FF490(Cur_1FF490* cur, List_1FF490* list, s32* lo, s32* hi)
{
    s32 mn = *lo;
    s32 mx = *hi;
    if (cur->off != 0) {
        do {
            if (cur->f4 == 0) goto next;
            if (cur->f8 == 0) goto next;
            {
                s32 n = list->count;
                list->items[n] = cur;
                list->count = n + 1;
                {
                    s32 x = cur->f8;
                    s32 e = x + cur->fC;
                    if ((u32)x < (u32)mn) mn = x;
                    if ((u32)mx < (u32)e) mx = e;
                }
            }
        next:
            cur = (Cur_1FF490*)((u8*)cur + cur->off + 4);
        } while (cur->off != 0);
    }
    *lo = mn;
    *hi = mx;
}

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

s32 func_0020B048(void) {
	return 1;
}

struct Device_20B0B0 {
	u8 padding[0x40];
	void* state;
};

s32 func_0020B0B0(Device_20B0B0* device) {
	return *(s32*)device->state;
}

struct Device_20B110 {
	u8 padding[0x40];
	u8* state;
};

struct DeviceState_20B110 {
	u8 padding[0x1B8];
	void* a;
	void* d;
	u8 padding2[8];
	void* b;
	void* e;
	u8 padding3[8];
	void* c;
	void* f;
};

s32 func_0020B110(Device_20B110* device) {
	DeviceState_20B110* state = (DeviceState_20B110*)device->state;
	if (state->a) *(s32*)((char*)state->a + 0x28) = 0;
	if (state->b) *(s32*)((char*)state->b + 0x28) = 0;
	if (state->c) *(s32*)((char*)state->c + 0x28) = 0;
	if (state->d) *(s32*)((char*)state->d + 0x28) = 0;
	if (state->e) *(s32*)((char*)state->e + 0x28) = 0;
	if (state->f) *(s32*)((char*)state->f + 0x28) = 0;
	return 1;
}

struct Field_20B258 {
	u8 padding[8];
	s32 f8;
	s32 fc;
};

s32 func_0020B258(Field_20B258* field) {
	return field->fc = field->f8;
}

extern u32* D_0062AD68;
extern u32* D_0062AD6C;
extern u32* D_0062AD70;
void func_00209C60(u32 base) {
    volatile u32* regs = (volatile u32*)(base | 0x20000000);
    if (D_0062AD68) *D_0062AD68 = regs[0];
    if (D_0062AD6C) *D_0062AD6C = regs[1];
    if (D_0062AD70) *D_0062AD70 = regs[0x24];
}

struct Obj_20B168 { u8 pad[0x40]; u32* values; };

s32 func_0020B168(Obj_20B168* obj, s32 index, s32 value, s32 second)
{
    u32* array = obj->values;
    u32* current = array + 3;
    u32 offset = index * 2;
    current += offset;
    array += offset;
    array[4] = second;
    s32 old = *current;
    *current = value;
    return old;
}

struct Item_20B240 { s32 a; s32 b; s32 c; s32 d; };
void func_0020B240(Item_20B240* item, s32 value, s32 field)
{
    item->a = value;
    item->b = field;
    item->c = value;
    item->d = value;
}

s32 func_0020B268(s32* item)
{
    s32 value = item[3];
    item[2] = value;
    return value;
}

struct Item_20B9D0 { u8 pad[4]; s32 x; s32 y; s32 left; s32 top; };
s32 func_0020B9D0(Item_20B9D0* item, s32 x, s32 y)
{
    item->x = x;
    item->y = y;
    item->left = x >> 4;
    item->top = y >> 4;
    return 1;
}

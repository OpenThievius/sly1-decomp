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


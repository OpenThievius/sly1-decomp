// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

int func_0013CCE8() {
	return 0;
}

struct InitialState {
	s32 field_00;
	s32 field_04;
	s32 field_08;
	s32 field_0C;
	s32 field_10;
	s32 field_14;
	s32 field_18;
	s32 field_1C;
};

extern void func_0013C9B0(InitialState* state);

void func_0013C988(InitialState* state, s32 initialValue, s32 secondaryValue) {
	state->field_04 = initialValue;
	state->field_00 = secondaryValue;
	func_0013C9B0(state);
}

struct FlagState {
	char padding[0x63C];
	s32 flags;
};

void func_0013D9E0(FlagState* state, s32* result) {
	*result = state->flags & 1;
}

void func_0013DA30(FlagState* state, s32* result) {
	*result = (state->flags >> 2) & 1;
}

struct QueueWithPrefix {
	char padding[0x44];
	s32 count;
	s32 values[16];
};

bool func_0013E8D8(QueueWithPrefix* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

struct Queue {
	s32 count;
	s32 values[16];
};

bool func_0013E8F8(Queue* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

extern void func_0013EB68(void* state);

void func_0013F6F8(void* state) {
	func_0013EB68((char*)state + 0x554);
}

void func_0013C9B0(InitialState* state)
{
    state->field_1C = 0;
    state->field_18 = 0;
    state->field_14 = 0;
    state->field_0C = 0;
    state->field_08 = 0;
    state->field_10 = state->field_04;
}

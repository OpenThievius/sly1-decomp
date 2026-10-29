// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern void* func_00113888(void* state, void* value, s32 mode);
extern void* func_00113B60(void* state, void* value, void* rangeEnd);

void* func_001139E8(void* state, void* arg1, void* value) {
	func_00113888(state, value, 0);
	return state;
}

void* func_00113A18(void* state, void* arg1, void* value) {
	func_00113888(state, value, 1);
	return state;
}

void* func_00113A78(void* state, void* arg1, void* value) {
	func_00113888(state, value, 3);
	return state;
}

void* func_00113E48(void* state, void* arg1, void* value) {
	func_00113B60(state, value, (char*)value + 8);
	return state;
}

extern void func_0011B008(void* state);
extern void func_0011B5F0(void* state, bool condition);
extern void func_0011B018(void* state, void* value);
extern void func_0011B060(void* state, s32 mode);

void* func_00113E78(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x1B);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113EE0(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] >= 0x14 && value[0] < 0x16);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113F48(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x15);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113FB0(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x14);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

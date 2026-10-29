// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

struct Quad_001891C0 { s32 a, b, c, d; } __attribute__((aligned(16)));

extern void func_001C7CB8(void);
extern void func_001C6F48(void*);
extern void func_001C7140(void*);
extern void func_00124DF8(void*, s32, void*);
extern void* func_00189438(s32, void*, void*);
extern void func_001EA480(f32, f32);
extern void func_001884C0(void*);
extern void func_00188B48(Quad_001891C0*, Quad_001891C0*, void*);
extern void func_00188668(void*, void*, void*);
extern s32 func_001B6598(s32, s32*);
extern s32 func_001C96B8(void*);
extern s32 func_001C8010(void*);
extern s32 func_00209B80(s32, s32*, s32*);
extern s32 func_0018B930(s32);
extern s32 func_0018B988(s32, s32);
extern void func_002093F0(void);
extern void func_0018B5C0(void*);
extern void func_0018BD58(void*, s32, s32);
extern void func_001F6A50(s32, s32);
extern void func_001F6B60(s32);
extern void func_001F6B40(s32);
extern s32 func_0018B770(void*);
extern u8 D_00264910[];
extern u8 D_00269990[];
extern u8 D_00264A40[];

struct Quad_001884E0 { s32 a, b, c, d; } __attribute__((aligned(16)));

void* func_001884E0(Quad_001884E0* destination, const Quad_001884E0* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	func_001884C0(destination);
	return destination;
}

void func_00188810(f32* a, f32* b, f32* out)
{
	s32 count = 15;
	do {
		*out++ = *a++ + *b++;
	} while (--count >= 0);
}

void func_00188CE0(f32* p)
{
	func_001EA480((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
}

void func_001891C0(Quad_001891C0* source, void* input, Quad_001891C0* output)
{
	Quad_001891C0 local[8];
	func_00188B48(source + 3, source, local);
	func_00188668(local + 4, input, local);
	output[0] = local[4];
	output[1] = local[5];
	output[2] = local[6];
	output[3] = local[7];
}

void* func_00189AF0(void* a0, void* a1)
{
	return func_00189438(4, a0, a1);
}

void func_0018A388(void* self)
{
	func_001C6F48(self);
	*(s32*)((char*)self + 0xE3C) = -1;
}

void func_0018A3B8(void* self)
{
	func_001C7140(self);
	func_00124DF8(self, 2, D_00264910);
}

struct State_0018ABF0 { u8 pad[0x724]; s32 type; u8 rest[0x6e8]; s32 handle; };

s32 func_0018ABF0(State_0018ABF0* state)
{
	if (state->type == 4) {
		s32 event;
		func_001B6598(state->handle, &event);
		if (event == 0x438 && func_001C96B8(state) == 0) return 2;
	}
	return func_001C8010(state);
}

void func_0018ACD0(void)
{
	func_001C7CB8();
}

void func_0018B580(void)
{
	func_002093F0();
	func_0018B5C0(D_00269990);
	func_0018BD58(D_00264A40, 0, 0);
}

struct State_0018B720 { s32 first; s32 second; };

void func_0018B720(State_0018B720* state)
{
	if (func_0018B770(D_00269990))
		func_001F6A50(state->second, 1);
	func_001F6B60(state->first);
	func_001F6B40(state->first);
}

s32 func_0018B770(void* p)
{
	return *(s32*)((char*)p + 4) != -1;
}

s32 func_0018B910(s32 value)
{
	if (value == 0) return 29;
	if (value > 0) return 30;
	return 31;
}

s32 func_0018BC90(s32 value, s32 mode, s32* output)
{
	s32 local[2];
	s32 result = func_0018B930(func_00209B80(value, &local[0], &local[1]));
	if (output) *output = local[1];
	if (result == 33) result = func_0018B988(mode, local[1]);
	return result;
}

s32 func_0018BD00(s32 value, void* first, s32 second)
{
	s32 result = func_0018B910(value);
	if (result == 29)
		result = func_0018BC90(0, (s32)first, (s32*)second);
	return result;
}

s32 func_0018BFA8(void* lhs, void* rhs)
{
	s32 difference = *(u16*)((char*)lhs + 0x54) - *(u16*)((char*)rhs + 0x54);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x52) - *(u8*)((char*)rhs + 0x52);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x53) - *(u8*)((char*)rhs + 0x53);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x56) - *(u8*)((char*)rhs + 0x56);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x57) - *(u8*)((char*)rhs + 0x57);
	if (difference) return difference;
	return *(u8*)((char*)lhs + 0x58) - *(u8*)((char*)rhs + 0x58);
}

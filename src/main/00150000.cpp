// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

struct State_001503E0 { u8 pad[0x744]; u32 count; u32 items[8]; };

struct Object_00150338 { u8 pad[0x550]; s32 status; };
struct State_00150338 { u8 pad[0x78C]; s32 count; Object_00150338* items[8]; };
extern Object_00150338* func_00182FC8(Object_00150338*);

Object_00150338* func_00150338(State_00150338* state)
{
	for (s32 i = 0; i < state->count; ++i) {
		Object_00150338* item = state->items[i];
		if (func_00182FC8(item) == 0) continue;
		if (item->status == 3) continue;
		if (item->status == 4) continue;
		return item;
	}
	return 0;
}

void func_001503E0(State_001503E0* state, u32 value)
{
	u32 count = state->count;
	if (count < 8) {
		state->items[count] = value;
		state->count = count + 1;
	}
}

struct State_00150408 { u8 pad[0x78C]; u32 field_78C; u8 gap[0x20]; u32 field_7B0; };

void func_00150408(State_00150408* state)
{
	state->field_78C = 0;
	state->field_7B0 = 0;
}

extern void func_00123ED0();
struct State_001504E0 { u8 pad0[0x2C8]; u64 flags; u8 pad1[0x30]; s32 second; u8 pad2[8]; s32 first; };

void func_001504E0(State_001504E0* state)
{
	func_00123ED0();
	state->flags |= ((u64)0x8000u << 17);
	state->second = -1;
	state->first = -1;
}

extern void func_001289C0();
extern void func_00150570(void*, u32, void*, void*);

void func_00150528(void* state, u32 arg)
{
	func_001289C0();
	func_00150570(state, arg, (u8*)state + 0x2DC, (u8*)state + 0x2E0);
}

struct State_00150780 { u8 pad[0x304]; u32* value; };

void func_00150780(State_00150780* state, u32 value)
{
	*state->value = value;
}

extern void func_00127378(void*, u32, u32);
struct State_001512A8 { u8 pad[0x2F8]; u32 value; };

void func_001512A8(State_001512A8* state, u32 mode, u32 value)
{
	func_00127378(state, mode, value);
	if (mode == 6 && value == state->value)
		state->value = 0;
}

extern void func_00150790(void*, u32);
struct State_001519A8 { u8 pad[0x2D4]; u32 mode; };

void func_001519A8(State_001519A8* state)
{
	if (state->mode != 1 && state->mode != 3)
		func_00150790(state, 0);
}

extern void* func_00160810(const char*);
extern void* func_00160CA0(void*, u32);
struct Collection_001519E0 { u8 pad[0x310]; u32 count; void* items[4]; };

void func_001519E0(Collection_001519E0* collection, const char* name, u32 kind)
{
	if (collection->count >= 4) return;
	void* item = func_00160810(name);
	if (!item) return;
	void* value = func_00160CA0(item, kind);
	if (!value) return;
	u32 count = collection->count;
	collection->items[count] = value;
	collection->count = count + 1;
}

extern void func_001F5C0C(void*, u32, u32);

void func_00151A68(void* state)
{
	func_001F5C0C(state, 0, 0x24);
}

void func_00151E18() {}

extern void func_00152410(void*, f32);
extern u8* D_002623C8;

void func_00151FC8(void* object)
{
	func_00152410(object, 0.0f);
	u8* manager = D_002623C8;
	*(f32*)(manager + 0x10) = 0.0f;
	*(u32*)(manager + 0x70) = 0;
	func_001F5C0C(manager + 0x74, 0, 1);
}

extern f32 func_001EB0F8(void*);
struct Object_00152410 { u8 pad[0x1C]; void* field_1C; };

void func_00152410(Object_00152410* object, f32 unused)
{
	f32 value = func_001EB0F8(object->field_1C);
	*(f32*)(D_002623C8 + 0xC) = value;
}

struct Pair_00152438 { u32 first, second, value; };

void func_00152438(Pair_00152438* p, u32 value)
{
	p->value = value;
}

struct Pair_00152440 { u32 first, second; };

void func_00152440(Pair_00152440* p)
{
	p->second = 0;
	p->first = 0;
}

struct Pair_00152450 { u32 first, second; };

void func_00152450(Pair_00152450* p)
{
	p->second = 0;
	p->first = 0;
}

struct Pair_00152460 { u32 first, second, value; };

u32 func_00152460(Pair_00152460* p, u32 value)
{
	return value + p->value;
}

struct Count_00152720 { u32 count; };

u32 func_00152720(Count_00152720* p)
{
	return p->count == 0;
}

extern u32 func_002027C8(u32);
extern void func_002018E8();
extern u32 func_002027A0(u32);
extern u32 D_00261F14, D_00261F18, D_00261F1C, D_00261F20, D_00261F24;

void func_00152810()
{
	func_002027C8(1);
	func_002018E8();
	D_00261F14 = func_002027A0(0);
	D_00261F18 = func_002027A0(1);
	D_00261F1C = func_002027A0(2);
	D_00261F20 = func_002027A0(8);
	D_00261F24 = func_002027A0(9);
}

struct Four_001528C8 { u32 a, b, d, c; };

void func_001528C8(Four_001528C8* p)
{
	p->a = 0;
	p->b = 0;
	p->d = 0;
	p->c = 0;
}

struct Four_001528E0 { u32 a, b, c, d; };

void func_001528E0(Four_001528E0* p)
{
	u32 b = p->b;
	p->c = 0;
	p->d = b;
}

extern u8* func_0018D4B0(u32);
struct Buffer_001528F0 { u8* end; u8* current; u8 pad[4]; u8* allocated; };

void func_001528F0(Buffer_001528F0* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = func_0018D4B0(bytes);
	buffer->allocated = memory;
	buffer->end = memory + bytes;
	buffer->current = memory;
}

extern u8* func_0018D500(u32);
struct Buffer_00152938 { u8* end; u8* current; u8 pad[4]; u8* allocated; };

void func_00152938(Buffer_00152938* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = func_0018D500(bytes);
	buffer->allocated = memory;
	buffer->end = memory + bytes;
	buffer->current = memory;
}

extern u8* func_0018D658(u32);
struct Buffer_00152980 { u8* end; u8* current; u8 pad[4]; u8* allocated; };

void func_00152980(Buffer_00152980* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = func_0018D658(bytes);
	buffer->allocated = memory;
	buffer->end = memory + bytes;
	buffer->current = memory;
}

struct Ranges_001529C8 { u32 start, current, spare, limit; };

void func_001529C8(Ranges_001529C8* p, u32 count, u32 start)
{
	p->current = start;
	p->limit = start;
	p->start = start + (count << 4);
}

extern void func_00152D70(void*);
extern void func_001528C8(void*);
struct Buffer_001529E0 { u8* start; u8* current; u8* spare; u8* end; };

void func_001529E0(Buffer_001529E0* buffer, u32* count, u8** current)
{
	func_00152D70(buffer);
	if (count) *count = ((u32)buffer->end - (u32)buffer->current) >> 4;
	if (current) *current = buffer->current;
	func_001528C8(buffer);
}

void func_00152E18() {}

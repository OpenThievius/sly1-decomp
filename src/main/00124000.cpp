// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

struct Flags_00126AB0 { u8 pad[0x264]; u32 flags; u32 value; };

extern void* func_00159BB0();
extern s32 func_00182FC8(void*);
struct State_00126C58 { u8 pad[0x298]; void* resource; };
struct Resource_00126C58 { s32 unknown; f32 value; };

struct Callback_00125108 { u8 pad[0x5C]; void (*function)(); };
struct Root_00125108 { Callback_00125108* callback; };

struct Quad_00124540 { s32 a, b, c, d; } __attribute__((aligned(16)));
typedef void (*Callback_00124540)(void*, void*);
struct Object_00124540 {
	Callback_00124540* vtable;
	u8 pad004[0xCC];
	Quad_00124540 sourceD0;
	Quad_00124540 sourceE0;
	Quad_00124540 sourceF0;
	Quad_00124540 source100;
	u8 pad110[0x80];
	Quad_00124540 destination190;
	Quad_00124540 destination1A0;
	Quad_00124540 destination1B0;
	Quad_00124540 destination1C0;
};
extern void func_00188FD8(void*, void*);

void func_00124540(Object_00124540* object)
{
	object->destination190 = object->source100;
	object->destination1A0 = object->sourceD0;
	object->destination1B0 = object->sourceE0;
	object->destination1C0 = object->sourceF0;
	object->vtable[46](object, (u8*)object + 0x1A0);
	func_00188FD8((u8*)object + 0x1A0, (u8*)object + 0x1D0);
}

void func_00125108(Root_00125108* root)
{
	if (root->callback->function)
		root->callback->function();
}

void func_00125438()
{
}

void func_00126AB0(Flags_00126AB0* state, u32 value)
{
	state->value = value;
	state->flags |= 2;
}

void func_00126C58(State_00126C58* state)
{
	if (state->resource)
		return;
	state->resource = func_00159BB0();
	if (func_00182FC8(state))
		((Resource_00126C58*)state->resource)->value = 1.0f;
	else
		((Resource_00126C58*)state->resource)->value = 0.0f;
}

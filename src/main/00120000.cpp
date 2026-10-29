// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

extern void func_0011F850(void*);

void func_00120110(void* object)
{
	func_0011F850((u8*)object + 0x20);
}

struct Arguments_001201D0 { u8 pad[0xC]; void* first; void* second; };
extern void func_0011F9F8(void*, void*);
extern void func_0011FB98(void*, void*, void*, void*);

void func_001201D0(Arguments_001201D0* args)
{
	func_0011F9F8(args->first, args->second);
}

struct Arguments_001202C0 { u8 pad[0xC]; void* first; void* second; };

void func_001202C0(Arguments_001202C0* args, void* value1, void* value2)
{
	func_0011FB98(args->first, args->second, value1, value2);
}

extern void func_0011F798(void*, void*, void*);

void func_00120360(void* object, void* value)
{
	func_0011F798((u8*)object + 0x20, (u8*)object + 0x10, value);
}

void func_00120388(void* object)
{
	func_0011F850((u8*)object + 0x20);
}

extern void func_0011FA88(void*, void*, void*);

void func_00120418(void* object, void* value)
{
	func_0011FA88((u8*)object + 8, (u8*)object + 0xC, value);
}

struct Arguments_00120440 { u8 pad[8]; void* first; void* second; };

void func_00120440(Arguments_00120440* args, void* value1, void* value2)
{
	func_0011FB98(args->first, args->second, value1, value2);
}

struct Root_00121228 { u8 pad[0x1B20]; };
struct CallbackObject_00121228 { void* callback; };
typedef void (*Callback_00121228)(void*, void*);
extern void* func_001B5EE0(void*);

void* func_00121228(Root_00121228* root, void* value, CallbackObject_00121228* callbackObject)
{
	void* node = func_001B5EE0((u8*)root + 0x1B20);
	*(void**)node = callbackObject;
	((Callback_00121228)callbackObject->callback)(node, value);
	return node;
}

struct Parent_00121568 { u8 pad[4]; void* child; };
struct Child_00121568 { u8 pad[0x224]; void* values; };
struct Value_00121568 { u8 pad[0x8C]; f32 value; };

void func_00121568(Parent_00121568* parent, f32* output, s32* clear)
{
	Value_00121568* value = (Value_00121568*)((u8*)((Child_00121568*)parent->child)->values);
	*output = value->value;
	*clear = 0;
}

struct Parent_001215A8 { u8 pad[4]; u8* data; };
struct Child_001215A8 { u8 pad[0x274]; f32* values; };

f32 func_001215A8(Parent_001215A8* parent, s32 index)
{
	return ((Child_001215A8*)parent->data)->values[index];
}

struct Pair_00122840 { u8 pad[0x80]; f32 first; f32 second; };

void func_00122840(Pair_00122840* pair, f32* first, f32* second)
{
	*first = pair->first;
	*second = pair->second;
}

struct Quad_00122858 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Vectors_00122858 {
	u8 pad[0x90];
	Quad_00122858 first;
	Quad_00122858 second;
	Quad_00122858 third;
} __attribute__((aligned(16)));

void func_00122858(Vectors_00122858* vectors, Quad_00122858* output)
{
	output[0] = vectors->first;
	output[1] = vectors->second;
	output[2] = vectors->third;
}

struct Values_00122878 { u8 pad[0xC4]; f32* values; };

f32 func_00122878(Values_00122878* values, s32 index)
{
	return values->values[index];
}

struct Quad_00122920 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Interface_00122920 { void** vtable; };
struct Root_00122920 {
	u8 pad0[4];
	Interface_00122920* interface;
	u8 pad8[0x14];
	Quad_00122920* first;
	Quad_00122920* second;
};
typedef void (*Callback_00122920)(Interface_00122920*);

void func_00122920(Root_00122920* root, Quad_00122920* first, Quad_00122920* second)
{
	*first = *root->first;
	*second = *root->second;
	Callback_00122920 callback = (Callback_00122920)root->interface->vtable[44];
	if (callback)
		callback(root->interface);
}

struct Object_001233C0 {
	u8 pad0[0x680];
	s32 state;
	u8 pad684[0x3C];
	void* counter;
};
struct Counter_00123B18;
void func_00123B18(Counter_00123B18*);
extern void func_0013D278(void*);

void func_001233C0(Object_001233C0* object)
{
	if (!object->state)
		func_00123B18((Counter_00123B18*)object->counter);
	func_0013D278(object);
}

struct Value_00123400 { u8 pad[0x6C0]; s32 value; };

void func_00123400(Value_00123400* state, s32 value)
{
	state->value = value;
}

extern void func_001B7968();
extern void* func_00140FF8(const char*);
extern const char D_00261420[];
struct State_00123408 { u8 pad0[0x550]; s32 value; u8 pad[0x15C]; void* object; };

void func_00123408(State_00123408* state)
{
	func_001B7968();
	state->value = -1;
	state->object = func_00140FF8(D_00261420);
}

extern void func_001BA130(void*);
struct Object_00123540 { u8 pad[0x6B0]; s32 value; };

void func_00123540(Object_00123540* object)
{
	s32 value = object->value;
	func_001BA130(object);
	object->value = value;
}

struct Counter_00123B18 { u8 pad[0x61C]; s32 value; };

void func_00123B18(Counter_00123B18* counter)
{
	counter->value++;
}

extern void func_0013EC00(void*, s32, void*, void*, void*, void*, void*);

void func_00123D08(void* object, void* a1, void* a2, void* a3, void* a4)
{
	func_0013EC00((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

struct Owner_00120130 {
    u8 pad0[0xC];
    void* first;
    void* second;
};
struct Interface_00120130 { void** vtable; };
struct Buffer_00120130 { u8 bytes[0x20]; };
typedef void (*Finish_00120130)(void* self, void* output, void* state);
extern void func_0011F9F8(void*, void*, s32, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_001EDE38(void*, void*, void*);

void func_00120130(Owner_00120130* self, Interface_00120130* parent, s32 mode,
                   void* output, void* state)
{
    Buffer_00120130 buffer;
    func_0011F9F8(self->first, self->second, mode,
                  output ? &buffer.bytes[0] : 0,
                  state ? &buffer.bytes[0x10] : 0);
    if (output) {
        func_00188A20(&buffer.bytes[0], output);
    }
    if (state) {
        func_001EDE38(&buffer.bytes[0], &buffer.bytes[0x10], state);
    }
    if (parent) {
        ((Finish_00120130)parent->vtable[0xB4 / 4])(parent, output, state);
    }
}


struct Result_001202F0 { f32 x; f32 y; f32 z; };
struct Output_001202F0 { f32 x; u8 pad4[0x10]; f32 y; u8 pad18[0x10]; f32 z; };
extern void func_0011F6B0(void*, void*, void*, void*, void*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_001202F0(void* first, void* second, void* third,
                   Output_001202F0* output, f32 factor)
{
    Result_001202F0 result;
    func_0011F6B0((u8*)first + 0x20, second, third, (u8*)first + 0x10,
                  output ? &result : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->x = result.x;
        output->y = result.y;
        output->z = result.z;
    }
}


struct Owner_001203A8 {
    u8 pad0[8];
    void* first;
    void* second;
};
struct Result_001203A8 {
    f32 first;
    f32 second;
    f32 third;
};
struct Output_001203A8 {
    f32 first;
    u8 pad4[0x10];
    f32 second;
    u8 pad18[0x10];
    f32 third;
};
extern void func_0011F9F8(void*, void*, void*, f32*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_001203A8(Owner_001203A8* self, void* unused, void* mode,
                   Output_001203A8* output, f32 factor)
{
    Result_001203A8 result;
    func_0011F9F8(self->first, self->second, mode,
                  output ? &result.first : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->first = result.first;
        output->second = result.second;
        output->third = result.third;
    }
}


typedef void (*GetValue_00123358)(void* self, void* owner, s32 zero1,
                                  f32* output, s32 zero2, f32 a, f32 b);
struct Object_00123358 { GetValue_00123358* vtable; };
struct Table_00123358 { u8 pad0[0x3C]; u8* base; };
struct Track_00123358 {
    u8 pad0[8];
    Table_00123358* table;
    u8 pad0C[8];
    f32 f14;
    f32 f18;
};
struct Owner_00123358 {
    u8 pad0[4];
    void* p4;
    u8 pad8[0x14];
    Track_00123358* track;
    u8 pad20[8];
    s32 row;
};

f32 func_00123358(Owner_00123358* self, s32 index)
{
    Track_00123358* track = self->track;
    u8* row = track->table->base + self->row * 0x1C;
    u8* values = *(u8**)(row + 0x18);
    Object_00123358* object = *(Object_00123358**)(values + index * 4);
    f32 result;
    object->vtable[0](object, self->p4, 0, &result, 0, track->f14, track->f18);
    return result;
}

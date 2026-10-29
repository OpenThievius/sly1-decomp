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

struct Ctx_001503E0 {
    u8 pad0[0x744];
    s32 count744;
    void* items748[8];
};

void func_001503E0(Ctx_001503E0* self, void* item)
{
    u32 n = (u32)self->count744;
    if (n < 8) {
        self->items748[n] = item;
        self->count744 = n + 1;
    }
}

struct Ctx_00150408 {
    u8 pad0[0x78C];
    s32 f78C;
    u8 pad1[0x7B0 - 0x790];
    s32 f7B0;
};

void func_00150408(Ctx_00150408* self)
{
    self->f78C = 0;
    self->f7B0 = 0;
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

void func_001289C0(void* self, void* arg);
void func_00150570(void* self, void* arg, void* a, void* b);

void func_00150528(void* self, void* arg)
{
    func_001289C0(self, arg);
    func_00150570(self, arg, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
}

extern void* D_002623C8;
void func_00124A48(void* self);
void* func_00160CA0(void* base, s32 index);

struct Slot_1506F0 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x2F8];
    void* f304;
    u8 f308[4];
    s32 f30C;
};

void func_001506F0(Slot_1506F0* self)
{
    func_00124A48(self);
    if (self->f30C == -1) {
        self->f30C = self->f8;
    }
    void* v = func_00160CA0(D_002623C8, self->f30C);
    self->f304 = v;
    if (!v) {
        self->f304 = self->f308;
    }
}

struct State_150750 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

void func_00150750(State_150750* self)
{
    self->f2D0 = 1;
}

struct State_150760 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

void func_00150760(State_150760* self)
{
    self->f2D0 = 2;
}

struct Value_150770 {
    s32 value;
};

struct Holder_150770 {
    u8 pad0[0x304];
    Value_150770* f304;
};

void func_00150770(Holder_150770* self, s32* out)
{
    *out = self->f304->value;
}

struct Obj_150780 { u8 pad[0x304]; s32* target; };

void func_00150780(Obj_150780* self, s32 value)
{
    *self->target = value;
}

extern void func_00127378(void*, u32, u32);
struct State_001512A8 { u8 pad[0x2F8]; u32 value; };

void func_001512A8(State_001512A8* state, u32 mode, u32 value)
{
	func_00127378(state, mode, value);
	if (mode == 6 && value == state->value)
		state->value = 0;
}

struct Obj_1519A8 { u8 pad[0x2D4]; s32 state; };

void func_00150790(void* self, s32 arg);

void func_001519A8(Obj_1519A8* self)
{
    if (self->state != 1 && self->state != 3) {
        func_00150790(self, 0);
    }
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

void func_00151E18(void* self)
{
}

extern void func_00152410(void*, f32);

void func_00151FC8(void* object)
{
	func_00152410(object, 0.0f);
	u8* manager = (u8*)D_002623C8;
	*(f32*)(manager + 0x10) = 0.0f;
	*(u32*)(manager + 0x70) = 0;
	func_001F5C0C(manager + 0x74, 0, 1);
}

extern f32 func_001EB0F8(void*);
struct Object_00152410 { u8 pad[0x1C]; void* field_1C; };

void func_00152410(Object_00152410* object, f32 unused)
{
	f32 value = func_001EB0F8(object->field_1C);
	*(f32*)((u8*)D_002623C8 + 0xC) = value;
}

struct Obj_152438 { u8 pad[8]; void* link; };

void func_00152438(Obj_152438* self, void* value)
{
    self->link = value;
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

u8* func_0018D4B0(s32 size);

struct Span_1528F0 { u8* end; u8* begin; u8* unused8; u8* cur; };

void func_001528F0(Span_1528F0* self, s32 count)
{
    s32 size = count << 4;
    u8* base = func_0018D4B0(size);
    self->cur = base;
    self->end = base + size;
    self->begin = base;
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

struct PktList_1529C8 {
    u8* end;
    u8* begin;
    u8* chunk;
    u8* write;
};

void func_001529C8(PktList_1529C8* self, s32 count, u8* base)
{
    self->begin = base;
    self->write = base;
    self->end = base + count * 16;
}

void func_00152D70(PktList_1529C8* self);
void func_001528C8(PktList_1529C8* self);

void func_001529E0(PktList_1529C8* self, u32* outCount, u8** outBegin)
{
    func_00152D70(self);
    if (outCount != 0) {
        *outCount = ((u32)self->write - (u32)self->begin) >> 4;
    }
    if (outBegin != 0) {
        *outBegin = self->begin;
    }
    func_001528C8(self);
}

void func_00152D70(void* self);
void func_001528C8(void* self);
u32 func_0018D568(u32 size, u32 src);

struct Span_152A50 { u32 end; u32 begin; u32 pad8; u32 cur; };

void func_00152A50(Span_152A50* self, u32* count, u32* begin, u32* out)
{
    func_00152D70(self);
    u32 n = (self->cur - self->begin) >> 4;
    if (count != 0) {
        *count = n;
    }
    if (begin != 0) {
        *begin = self->begin;
    }
    if (out != 0) {
        *out = func_0018D568(n << 4, self->begin);
    }
    func_001528C8(self);
}

void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);

void func_00152AE0(PktList_1529C8* self, void* dma)
{
    func_00152D70(self);
    func_001F6C20(0);
    func_00202A80(dma, self->begin);
    self->write = self->begin;
}

void func_00152B38(PktList_1529C8* self)
{
    func_00152D70(self);
    u8* q = self->write;
    self->chunk = q;
    self->write = q + 16;
    *(u64*)q = 0x10000000;
    *(u64*)(self->chunk + 8) = 0;
}

void func_00152B80(PktList_1529C8* self, s32 lo, s32 hi)
{
    s32 flag = 0;
    if (self->chunk != 0) {
        func_00152D70(self);
        flag = 1;
    }
    u8* p = self->write;
    self->write = p + 16;
    *(u64*)p = (u64)lo | 0x40000000 | ((u64)hi << 32);
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->write;
        self->chunk = q;
        self->write = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)(self->chunk + 8) = 0;
    }
}

void func_00152C18(PktList_1529C8* self, s32 hi)
{
    s32 flag = 0;
    if (self->chunk != 0) {
        func_00152D70(self);
        flag = 1;
    }
    u8* p = self->write;
    self->write = p + 16;
    *(u64*)p = ((u64)hi << 32) | 0x50000000;
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->write;
        self->chunk = q;
        self->write = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)(self->chunk + 8) = 0;
    }
}

struct Buf_152CA0 { u8 pad[0xC]; u8* cur; };

void func_00152CA0(Buf_152CA0* self)
{
    func_00152D70(self);
    u64* p = (u64*)self->cur;
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
}

void func_00152E18() {}

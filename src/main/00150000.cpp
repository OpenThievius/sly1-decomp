// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Node_150298 { u8 pad[0x554]; f32 value554; u8 pad2[0x558 - 0x558]; Node_150298* next; };
struct State_150298 { u8 pad[0x6CC]; Node_150298* selected; };
extern Node_150298* D_00262708;
extern f32 D_0024A014;
Node_150298* func_0016A820(Node_150298*);
void func_0014F110(Node_150298*, s32);
void func_00150298(State_150298* self)
{
	s32 scratch[4];
	(void)scratch;
	if (self->selected != 0) return;
	Node_150298* current = D_00262708;
	Node_150298* best = 0;
	f32 minimum = D_0024A014;
	while (current != 0) {
		Node_150298* candidate = func_0016A820(current);
		current = current->next;
		if (candidate != 0 && candidate->value554 < minimum) { best = candidate; minimum = candidate->value554; }
	}
	if (best != 0) { func_0014F110(best, 5); self->selected = best; }
}

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

struct Events_150418 {
    u8 pad0[0x768];
    s32 eventCount;
    void* events[8];
    s32 candidateCount;
    void* candidates[8];
    s32 state;
};

s32 func_001300E8(void* event, s32 kind);

void func_00150418(Events_150418* self, void* event)
{
    if (func_001300E8(event, 7)) {
        self->state = 1;
        return;
    }
    if (!func_001300E8(event, 0x41)) {
        return;
    }
    s32 found = 0;
    for (s32 i = 0; i < self->eventCount; i++) {
        if (self->events[i] == event) {
            found = 1;
            break;
        }
    }
    if (found) {
        u32 count = self->candidateCount;
        if (count < 8) {
            self->candidates[count] = event;
            self->candidateCount = count + 1;
        }
    }
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

extern u8 D_00275BC0[];
struct Global_2701F8 { u8 pad[0x324]; void* value; };
extern Global_2701F8 D_002701F8;
void func_001E9498(void* a, void* b);

typedef void (*Callback_151860)(void* self, void* value);
struct VTable_151860 {
    u8 pad[0x158];
    Callback_151860 callback;
};
struct Object_151860 {
    VTable_151860* vtable;
};

void func_00151860(void* value, Object_151860* object)
{
    if (object != 0) {
        object->vtable->callback(object, value);
    } else {
        D_002701F8.value = value;
        func_001E9498(D_00275BC0, &D_002701F8);
    }
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

extern u8 D_00261EF0[];

void* func_00151A58(void)
{
    return D_00261EF0;
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
extern void* D_002623C8;
extern void* D_002623C0;
extern u8 D_00275C60[];
struct Object_151E20 { u8 pad[0x1C]; void* field_1C; };
void func_00152410(void*, f32);
f32 func_001EB0F8(void*, f32);
void func_00151E20(void* self, f32 amount)
{
    f32 x = *(f32*)((u8*)*(void**)&D_002623C8 + 0xC) + amount * *(f32*)((u8*)*(void**)((u8*)self + 0x1C) + 0x10);
    func_00152410(self, x);
    s32 index = *(s32*)((u8*)*(void**)&D_002623C0 + 0x19E0);
    f32 y;
    if (index < 0) {
        y = *(f32*)((u8*)*(void**)((u8*)self + 0x1C) + 0x40);
    } else {
        y = *(f32*)((u8*)*(void**)((u8*)self + 0x1C) + 0x3C);
        if (index <= *(s32*)((u8*)*(void**)((u8*)self + 0x1C) + 0x4C)) {
            y += *(f32*)((u8*)*(void**)((u8*)self + 0x1C) + 0x50);
        }
    }
    f32 result = ((f32 (*)(void*, f32))func_001EB0F8)(D_00275C60, *(f32*)((u8*)*(void**)&D_002623C8 + 0x10) + amount * y);
    *(f32*)((u8*)*(void**)&D_002623C8 + 0x10) = result;
}

void func_00151FC8(void* object)
{
	func_00152410(object, 0.0f);
	u8* manager = (u8*)D_002623C8;
	*(f32*)(manager + 0x10) = 0.0f;
	*(u32*)(manager + 0x70) = 0;
	func_001F5C0C(manager + 0x74, 0, 1);
}

extern f32 func_001EB0F8(void*, f32);
struct Object_00152410 { u8 pad[0x1C]; void* field_1C; };

void func_00152410(Object_00152410* object, f32 unused)
{
	f32 value = ((f32 (*)(void*))func_001EB0F8)(object->field_1C);
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

struct Pair_152470 { u32 first, second; };
void func_00152470(Pair_152470* self, u32 value)
{
    u32* slot = (u32*)func_00152460((Pair_00152460*)self, value);
    if (self->second == 0) {
        self->first = value;
    } else {
        u32* oldTail = (u32*)func_00152460((Pair_00152460*)self, self->second);
        slot[1] = self->second;
        oldTail[0] = value;
    }
    self->second = value;
}

struct Pair_152540 { u32 first, second, base; };
void func_00152470(Pair_152540*, u32);
void func_001524D8(Pair_152540*, u32);
void func_00152540(Pair_152540* self, u32 before, u32 value)
{
    if (before == 0) {
        func_00152470(self, value);
        return;
    }
    if (before == self->first) {
        func_001524D8(self, value);
        return;
    }
    u32* next = (u32*)func_00152460((Pair_00152460*)self, value);
    u32* previous = (u32*)func_00152460((Pair_00152460*)self, before);
    u32 after = previous[1];
    u32* afterSlot = (u32*)func_00152460((Pair_00152460*)self, after);
    next[0] = before;
    next[1] = after;
    previous[1] = value;
    afterSlot[0] = value;
}

s32 func_001526D0(void* self, u8* item)
{
    u8* slot = (u8*)func_00152460((Pair_00152460*)self, (u32)item);
    s32 result = 0;
    if (*(void**)slot != 0) {
        goto matched;
    }
    if (*(void**)((u8*)self + 4) != item) {
        goto done;
    }
matched:
    result = 1;
done:
    return result;
}

struct Count_00152720 { u32 count; };

u32 func_00152720(Count_00152720* p)
{
	return p->count == 0;
}

struct LinkCounter_1527D8 {
    void* head;
    u32 pad4;
    s32 stride;
};

s32 func_001527D8(LinkCounter_1527D8* list)
{
    s32 count = 0;
    u8* node = (u8*)list->head;
    if (node != 0) {
        s32 stride = list->stride;
        do {
            node = *(u8**)(node + stride);
            count++;
        } while (node != 0);
    }
    return count;
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

void func_0018D780(void* cursor, s32 count, s32 index);

void func_00152CE0(void* self, s32 index, s32 count)
{
    func_0018D780(*(void**)((u8*)self + 0xC), count, index);
    *(u8**)((u8*)self + 0xC) += index * 16;
}

void func_00152D70(void* self);

void func_00152D30(void* self)
{
    func_00152D70(self);
    u8* cursor = *(u8**)((u8*)self + 0xC);
    *(u8**)((u8*)self + 0xC) = cursor + 0x10;
    *(u64*)cursor = 0x70000000;
    *(u64*)(cursor + 8) = 0;
}

void func_00152E18() {}

struct Ctl_001517C0 { u8 pad0[0x2DC]; s32 count; u8* base; s32 index; u8 pad2E8[0x10]; void* p2F8; };
void func_00150DC0(Ctl_001517C0* self, u8* item);
s32 func_00151300(Ctl_001517C0* self);
void func_0012E760(void* obj);
void func_001516C0(Ctl_001517C0* self);

void func_001517C0(Ctl_001517C0* self)
{
    s32 index;

    if (self->index < self->count) {
        for (;;) {
            if (func_00151300(self) != 0) {
                return;
            }
            if (self->p2F8 != 0) {
                func_0012E760(self->p2F8);
                self->p2F8 = 0;
            }
            index = self->index + 1;
            self->index = index;
            if (!(index < self->count)) {
                break;
            }
            func_00150DC0(self, self->base + index * 0x28);
        }
        func_001516C0(self);
    }
}

typedef void (*VFn_153328)(void* self, void* arg);

struct Self_153328 {
    VFn_153328* vtbl;
    u8 pad0[0x2D0 - 4];
    void* f2D0;
};

struct Frame_153328 {
    void* fn;
    s32 f04;
    s32 f08;
    u8 pad0[4];
    u8 out[0x50];
    void* self;
    u8 pad1[0x1C];
};

extern u8 func_001533A8[];
s32 func_001F5C0C(void* p, s32 zero, s32 size);
void func_00125B70(void* obj, void* c, void* out);
void func_0019D410(void* p);

void func_00153328(Self_153328* self, s32 unused, void* a2)
{
    (void)unused;
    if (self->f2D0 != 0) {
        self->vtbl[43](self, a2);
        Frame_153328 f;
        (void)func_001F5C0C(&f, 0, 0x80);
        f.fn = (void*)func_001533A8;
        f.f08 = 0;
        func_00125B70(self, a2, f.out);
        f.self = self;
        func_0019D410(&f);
    }
}

struct Part_151ED8 { u8 pad0[0x14]; f32 f14; f32 f18; };
struct Obj_151ED8 { u8 pad0[0x1C]; Part_151ED8* p1C; };
struct Node_151ED8 { u8 pad0[0x5B4]; s32 f5B4; };
struct Mgr_151ED8 { u8 pad0[0xC]; f32 fC; u8 pad1[0x70 - 0x10]; s32 count70; u8 bits74[1]; };

void func_00152410(void*, f32);

void func_00151ED8(Obj_151ED8* obj, Node_151ED8* node)
{
    f32 value;
    if (node != 0) {
        s32 idx = node->f5B4;
        s32 bit = 1 << (idx & 7);
        if (((Mgr_151ED8*)D_002623C8)->bits74[idx / 8] & bit) {
            value = obj->p1C->f18;
            goto have;
        }
    }
    value = obj->p1C->f14;
have:
    func_00152410(obj, ((Mgr_151ED8*)D_002623C8)->fC + value);
    if (node != 0) {
        Mgr_151ED8* m = (Mgr_151ED8*)D_002623C8;
        s32 idx = node->f5B4;
        s32 bit = 1 << (idx & 7);
        u8 cur = m->bits74[idx / 8];
        if (cur & bit) return;
        m->bits74[idx / 8] = cur | bit;
        m->count70 = m->count70 + 1;
    }
}

struct Link_00152600 { s32 f0; s32 f4; };
struct Entry_00152600 { u8 pad0[4]; s32 f4; u8 pad1[4]; Entry_00152600* next; };
extern Entry_00152600* D_0027B314;
void* func_00152460(void* a, void* b);

void func_00152600(u8* a, void* b)
{
    Link_00152600* link = (Link_00152600*)func_00152460(a, b);
    Entry_00152600* e = D_0027B314;
    while (e != 0) {
        if (e->f4 != (s32)link) {
            e = e->next;
            continue;
        }
        if (link->f4 != 0) e->f4 = (s32)func_00152460(a, (void*)link->f4);
        else e->f4 = (s32)a;
        e = e->next;
    }
    if (link->f4 != 0) {
        *(s32*)func_00152460(a, (void*)link->f4) = link->f0;
    } else {
        *(s32*)a = link->f0;
    }
    if (link->f0 != 0) {
        *(s32*)((u8*)func_00152460(a, (void*)link->f0) + 4) = link->f4;
    } else {
        *(s32*)(a + 4) = link->f4;
    }
    link->f0 = 0;
    link->f4 = 0;
}

struct Target_00152D70 { u8 pad0[8]; s16 off8; u8 pad1[2]; void (*fnC)(void* self, s32 arg); };
struct Obj_00152D70 { u8 pad0[8]; s32* f8; s32 fC; s32 f10; s32 f14; Target_00152D70* f18; };

void func_00152D70(Obj_00152D70* self)
{
    if (self->f10 != 0) {
        s32 p = self->fC;
        if ((p & 0xF) != 0) {
            *(s32*)p = 0;
            p += 4;
            while ((p & 0xF) != 0) { *(s32*)p = 0; p += 4; }
        }
        self->fC = p;
    } else if (self->f14 != 0) {
        Target_00152D70* t = self->f18;
        t->fnC((u8*)self + t->off8, 0);
    }
    s32* q = self->f8;
    if (q != 0) {
        *q = *q | (((self->fC - (s32)q) >> 4) - 1);
        self->f8 = 0;
    }
}

struct Self_153528 { s32 f00; u8 pad04[4]; void* f08; u8 pad0C[0x40 - 0x0C]; void* f40; void* f44; void* f48; void* f4C; };

s32 func_001F5C0C(void* p, s32 zero, s32 size);
void func_00152438(Obj_152438* self, void* value);

void func_00153528(Self_153528* self, s32 count)
{
	(void)func_001F5C0C(self, 0, 0x50);
	s32 n = count << 1;
	self->f00 = n;
	s32 size = 0x60 * n;
	self->f08 = func_0018D658(size);
	(void)func_001F5C0C(self->f08, 0, size);
	func_00152438((Obj_152438*)((u8*)self + 0xC), (void*)0x4C);
	func_00152438((Obj_152438*)((u8*)self + 0x18), (void*)0x4C);
	func_00152438((Obj_152438*)((u8*)self + 0x24), (void*)0x4C);
	func_00152438((Obj_152438*)((u8*)self + 0x30), (void*)0x4C);
	s32 sq = (n * n) << 2;
	self->f40 = func_0018D658(sq);
	self->f44 = func_0018D658(sq);
	self->f48 = func_0018D658(count << 3);
	self->f4C = func_0018D658(count << 3);
}

struct Gl_0026E9F8 { u8 pad0[0x260]; s32 f260; u8 pad1[0x8]; s32 f26C; };
struct Obj_001518B8 { u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; u8 pad1[0x2C]; s32* p304; u8 pad2[0x8]; s32 count310; s32 items314[1]; };

extern u8 D_0026E9F8[];
extern s32 D_00275F84;
extern void* D_0027051C;
s32 func_001BE5E8(void);
void func_00150790(void* self, s32 mode);

void func_001518B8(Obj_001518B8* self)
{
    Gl_0026E9F8* g = (Gl_0026E9F8*)D_0026E9F8;
    if (g->f260 >= 2 || g->f26C != 0)
        return;
    if (func_001BE5E8() != 0)
        return;
    if (D_00275F84 == 1)
        return;
    if (self == D_0027051C)
        return;
    s32 mode = 1;
    if (*self->p304 != 0) {
        mode = (self->f2D0 == 2) ? self->f2D4 : 5;
    } else {
        s32 n = self->count310;
        if (n > 0) {
            for (s32 i = 0; i < n; i++) {
                if (*(s32*)self->items314[i] != 0) {
                    mode = 5;
                    break;
                }
            }
        }
    }
    func_00150790(self, mode);
}

struct Node_152730 { u32 a; u32 b; u32 c; };
struct __attribute__((packed)) Wide_152730 { u64 v; u32 w __attribute__((aligned(4))); };

u32 func_00152460(Node_152730* node, u32 value);
void func_00152440(Node_152730* node);

void func_00152730(Node_152730* dst, Node_152730* src)
{
    if (src->a != 0) {
        if (dst->a == 0) {
            *(Wide_152730*)dst = *(Wide_152730*)src;
            func_00152440(src);
        } else {
            u32 p1 = func_00152460(dst, dst->b);
            u32 p2 = func_00152460(src, src->a);
            *(u32*)p1 = src->a;
            *(u32*)(p2 + 4) = dst->b;
            dst->b = src->b;
            func_00152440(src);
        }
    }
}

struct Pair_1524D8 { u32 first, second; };
void func_001524D8(Pair_1524D8* self, u32 value)
{
    u32* slot = (u32*)func_00152460((Pair_00152460*)self, value);
    if (self->first == 0) {
        *(u32*)((u8*)self + 4) = value;
        *(u32*)self = value;
        return;
    }
    {
        u32* oldHead = (u32*)func_00152460((Pair_00152460*)self, self->first);
        slot[0] = self->first;
        oldHead[1] = value;
        self->first = value;
    }
}

struct Obj_151D28 { u8 pad0[0x2C]; f32 f2C; s32 f30; f32 f34; s32 f38; };
struct Mgr_151D28 { u8 pad0[0xC]; f32 fC; };
struct Glob_151D28 { u8 pad0[0x19E4]; s32 f19E4; };
struct Self_151D28 { u8 pad0[0x1C]; Obj_151D28* field_1C; s32 field_20; };

extern s32 D_00275B00;
extern void* D_00275710;
void func_00160C48(s32 value);
f32 func_001EB0F8(void*, f32);
void func_00152410(void*, f32);
void func_00148CE0(void*);

void func_00151D28(Self_151D28* self)
{
    if (D_00275B00 & 8) {
                if (self->field_1C->f2C <= ((Mgr_151D28*)D_002623C8)->fC && ((Mgr_151D28*)D_002623C8)->fC < self->field_1C->f34) {
            if (((Glob_151D28*)D_002623C0)->f19E4 < self->field_1C->f30) {
                func_00160C48(self->field_1C->f30);
                self->field_20 = 1;
            }
        } else if (self->field_1C->f34 <= ((Mgr_151D28*)D_002623C8)->fC) {
            if (((Glob_151D28*)D_002623C0)->f19E4 < self->field_1C->f38) {
                func_00160C48(self->field_1C->f38);
                self->field_20 = 1;
            }
        }
    } else {
        f32 v = func_001EB0F8((u8*)self->field_1C + 8, ((Mgr_151D28*)D_002623C8)->fC);
        func_00152410(self, v);
    }
    func_00148CE0(D_00275710);
}

struct Self_152888 { u8 pad0[0x10]; s32 f10; s32 f14; u8* f18; };

extern u8 D_0024A0E0[];
void func_001528C8(Self_152888* p);

Self_152888* func_00152888(Self_152888* self)
{
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = D_0024A0E0;
    func_001528C8(self);
    return self;
}

struct Mgr_150790 { u8 pad0[0x460]; u8 f460[0x5C]; s32 f4BC; };
struct Self_150790;
struct Glob_150790 { u8 pad0[0x260]; Self_150790* f260; };
struct __attribute__((packed)) Blk_150790 { u8 pad0[0x324]; s32 f324; };
struct Ptr_150790 { s32 f0; };
struct Self_150790 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x2D0 - 0x18];
    s32 f2D0;
    s32 f2D4;
    f32 f2D8;
    u8 pad2DC[0x2E4 - 0x2DC];
    s32 f2E4;
    s32 f2E8;
    u8 pad2EC[0x2F8 - 0x2EC];
    void* f2F8;
    u8 pad2FC[4];
    s32 f300;
    Ptr_150790* f304;
    u8 pad308[0x330 - 0x308];
    s32 f330;
};

extern Mgr_150790* D_00261990;
extern Glob_150790 D_0026F5A0;
extern u8 D_002708E0[];
extern u8 D_00271558[];
extern s32 D_00261D38;
extern f32 D_0026185C;
extern void* D_00275710;

void func_001BE998(void);
void func_001837E0(Self_150790* self, s32 a, s32 b, s32 c);
void func_001451F0(Mgr_150790* m, s32 a, s32 b, void* c, s32 d, s32 e);
void func_001DDA50(void* a);
void func_001DDA20(void* a);
s32 func_00149610(void* a);
void func_001495E8(void* a, s32 b);
void func_00145088(Mgr_150790* m, s32 a, void* b, s32 c, s32 d);
void func_0012E760(void* a);
void func_001C06A0(s32 a, s32 b, f32 f);
void func_001356C0(Blk_150790* a, s32 b);
void func_001365A0(Blk_150790* a, s32 b);
void* func_0015A448(void* a, s32 b, s32 c);
void func_001E86E0(void* a, s32 b);
void func_001E87F0(void* a, s32 b);

void func_00150790(Self_150790* self, s32 next)
{
    s32 cur = self->f2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (D_0026F5A0.f260 == self) {
            D_0026F5A0.f260 = 0;
        }
        break;
    case 1:
        if (self->f2D0 != cur) {
            D_00261D38 = D_00261D38 - 1;
        }
        break;
    case 3:
        self->f304->f0 = 1;
        func_001BE998();
        func_001837E0(self, 0x15, 0, 0);
        if (self->f2D0 == 2) {
            func_001451F0(D_00261990, 0xF, 6, D_00261990->f460, 0, 0);
            func_001DDA50(D_00275710);
        }
        (void)func_00149610(D_00261990->f460);
        if ((self->f2E8 & 0x10) != 0 && self->f2F8 != 0) {
            func_0012E760(self->f2F8);
        }
        if (self->f2D0 == 2 && self->f330 != 0) {
            f32 f = 1.0f;
            func_001C06A0(9, 0, f);
            func_001C06A0(9, 1, f);
        }
        break;
    case 4:
        ((Blk_150790*)&D_002701F8)->f324 = 0;
        func_001356C0((Blk_150790*)&D_002701F8, 0);
        break;
    }
    switch (next) {
    case 5:
        if (D_0026F5A0.f260 != 0) {
            func_00150790(D_0026F5A0.f260, 0);
        }
        D_0026F5A0.f260 = self;
        self->f2D4 = next;
        break;
    case 1:
        if (self->f2D0 != next) {
            D_00261D38 = D_00261D38 + 1;
        }
        self->f2D4 = next;
        break;
    case 3:
        self->f2E4 = -1;
        self->f2E8 = 0;
        if (self->f2D0 == 2) {
            func_001495E8(D_00261990->f460, 4);
            func_00145088(D_00261990, 6, D_00261990->f460, 0, 0);
            func_001DDA20(D_00275710);
            func_001365A0((Blk_150790*)&D_002701F8, 0);
            if (self->f330 != 0) {
                f32 f = 0.6f;
                func_001C06A0(9, 0, f);
                func_001C06A0(9, 1, f);
            }
        } else {
            func_001495E8(D_00261990->f460, 3);
            if (self->f2D0 == 0) {
                if (self->f300 != -1) {
                    D_00261990->f4BC = (s32)func_0015A448(self->f14, self->f300, 0);
                } else {
                    D_00261990->f4BC = 0;
                }
            }
        }
        self->f2D4 = next;
        break;
    case 4:
        func_001E86E0(D_002708E0, 0);
        func_001E87F0(D_002708E0, 0);
        func_001E86E0(D_00271558, 0);
        func_001E87F0(D_00271558, 0);
        self->f2D4 = next;
        break;
    default:
        self->f2D4 = next;
        break;
    }
    self->f2D8 = D_0026185C;
}

struct Node_153EC0 {
    u8 pad_00[0x28];
    s32 f28;
    u8 pad_2C[0x38 - 0x2C];
    f32 f38;
    u8 pad_3C[0x44 - 0x3C];
    s32 f44;
    u8 pad_48[4];
    Node_153EC0* next;
};
struct Obj_153EC0 {
    u8 pad_00[0xC];
    s32 listA;
    u8 pad_10[0x30 - 0x10];
    Node_153EC0* head;
    u8 pad_34[8];
    s32 f3C;
};
struct Frame_153EC0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00153780(Obj_153EC0* self, s32 a1, Node_153EC0* n, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00152600(void* list, Node_153EC0* n);
void func_00152470(void* list, Node_153EC0* n);
void func_00153A50(Obj_153EC0* self, Node_153EC0* n);
extern f32 D_BC23D70A;

void func_00153EC0(Obj_153EC0* self, s32 a1, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    Frame_153EC0 fr;
    s32 scratch[4];
    (void)scratch;
    s32 e = (s32)&self->head;
    fr.cursor = e;
    fr.list = e;
    s32 old = *(s32*)&D_0027B314;
    s32 link = *(s32*)(e + 8);
    *(s32*)&D_0027B314 = (s32)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    Node_153EC0* node = (Node_153EC0*)h;
    while (node != 0) {
        if (node->f28 == 2) {
            if (node->f44 == 0) {
                func_00153780(self, a1, node, a3, a4, a5, a6);
            }
            func_00152600(&self->head, node);
            func_00152470(&self->listA, node);
            self->f3C++;
        }
        Node_153EC0* nx = *(Node_153EC0**)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = (s32)nx + lk;
        node = nx;
    }
    func_00153A50(self, 0);
    *(s32*)&D_0027B314 = fr.prev;
    for (;;) {
        f32 best = -0.01f;
        Node_153EC0* sel = 0;
        for (Node_153EC0* p = self->head; p != 0; p = p->next) {
            if (p->f38 < best) {
                best = p->f38;
                sel = p;
            }
        }
        if (!sel) break;
        if (sel->f44 == 0) {
            func_00153780(self, a1, sel, a3, a4, a5, a6);
        }
        func_00153A50(self, sel);
    }
}

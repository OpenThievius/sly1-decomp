// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001289C0(void* self, void* arg);
void func_00150570(void* self, void* arg, void* a, void* b);

void func_00150528(void* self, void* arg)
{
    func_001289C0(self, arg);
    func_00150570(self, arg, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
}

struct Obj_150780 { u8 pad[0x304]; s32* target; };

void func_00150780(Obj_150780* self, s32 value)
{
    *self->target = value;
}

struct Obj_1519A8 { u8 pad[0x2D4]; s32 state; };

void func_00150790(void* self, s32 arg);

void func_001519A8(Obj_1519A8* self)
{
    if (self->state != 1 && self->state != 3) {
        func_00150790(self, 0);
    }
}

void func_00151E18(void* self)
{
}

struct Obj_152438 { u8 pad[8]; void* link; };

void func_00152438(Obj_152438* self, void* value)
{
    self->link = value;
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

struct Buf_152CA0 { u8 pad[0xC]; u8* cur; };

void func_00152CA0(Buf_152CA0* self)
{
    func_00152D70(self);
    u64* p = (u64*)self->cur;
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
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

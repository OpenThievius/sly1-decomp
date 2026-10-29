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

void func_00152D70(void* self);

struct Buf_152CA0 { u8 pad[0xC]; u8* cur; };

void func_00152CA0(Buf_152CA0* self)
{
    func_00152D70(self);
    u64* p = (u64*)self->cur;
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
}

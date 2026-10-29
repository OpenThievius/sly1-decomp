// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1AC638 {
    u8 pad0[4];
    s32 handle;
    s8 flag;
    u8 pad1[0x20C - 9];
    f32 scale;
};

struct Loc_1AC638 {
    u8 data[0xB0];
    f32 x;
    f32 y;
};

s32 func_001E2100(void* p);
void func_001E2138(void* dst, void* p);
void func_0015C8B8(s32 handle, f32 a, f32 b);
void func_0015DB28(void* out, void* p, s32 handle);
void func_0015E290(void* out, f32 t, f32* a, f32* b);
void func_001AAB20(Obj_1AC638* self, f32 x, f32 y);
void func_0015C900(s32 handle);

void func_001AC638(Obj_1AC638* self, void* p)
{
    Loc_1AC638 loc;

    if (p != 0 && func_001E2100(p)) {
        func_001E2138(&self->flag, p);
    } else {
        self->flag = 0;
    }
    f32 v = self->scale;
    func_0015C8B8(self->handle, v, v);
    func_0015DB28(&loc, &self->flag, self->handle);
    f32 zero = 0.0f;
    func_0015E290(&loc, zero, &loc.x, &loc.y);
    f32 x = loc.x;
    func_001AAB20(self, x, (self->flag != 0) ? loc.y : 0.0f);
    func_0015C900(self->handle);
}

void func_001AA8F0(void* self);

struct Obj_1ACA30 { u8 pad[0x250]; s32 mode; u8 pad2[0x260 - 0x254]; s32 flag; };

void func_001ACA30(Obj_1ACA30* self)
{
    if (self->mode != 3 || self->flag == 0) {
        func_001AA8F0(self);
    }
}

void func_001AA958(void* self);

struct Obj_1AD3B0 { u8 pad[0x250]; s32 mode; u8 pad2[0x260 - 0x254]; s32 flag; };

void func_001AD3B0(Obj_1AD3B0* self)
{
    if (self->mode == 3 && self->flag != 0) {
        self->flag = 0;
    } else {
        func_001AA958(self);
    }
}

void func_001ADFF0(void* self);
void func_001AA998(void* self, s32 flag);

struct Obj_1AE130 { u8 pad[0x268]; s32 pending; };

void func_001AE130(Obj_1AE130* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        func_001ADFF0(self);
        force = 1;
    }
    func_001AA998(self, force);
}

struct Queue_1AF078 {
    u8 pad_0[0x5A0];
    u32 count;
    u32 items[4];
};

void func_001AF078(Queue_1AF078* q, u32 value)
{
    u32 n = q->count;
    if (n < 4) {
        q->items[n] = value;
        q->count = n + 1;
    }
}

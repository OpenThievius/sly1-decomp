// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_00182ED0(void* self);
void func_001A93C8(void* self);

void func_001A80E0(void* self)
{
    func_00182ED0(self);
    func_001A93C8(self);
}

void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);

void func_001A97C8(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        func_001F3C08(*(void**)(self + 0x10), v);
        func_00128150(0, x, v, v);
        *out = func_00205778(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        func_00128150(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = func_00205778(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void func_001C7CB8(void* self);
void func_0012E760(void* obj);

void func_001A9A40(void* self)
{
    u8* s = (u8*)self;
    func_001C7CB8(self);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            func_0012E760(p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

struct Obj_1AA788 { u8 pad[0x20C]; f32 value; };

void func_001AA788(Obj_1AA788* self, f32 v)
{
    self->value = v;
}

struct Obj_1AA8B8 { u8 pad[0x244]; f32 value; };

void func_001AA8B8(Obj_1AA8B8* self, f32 v)
{
    self->value = v;
}

extern f32 D_0026185C;
extern f32 D_00261860;

typedef void (*VFn_1AB660)(void* self);

void func_001AA298(void* self);
void func_001AB980(void* self, f32 value);

struct Obj_1AB660 {
    VFn_1AB660* vtbl;
    u8 pad[0x250 - 4];
    s32 mode;
    u8 pad2[0x260 - 0x254];
    s32 flag;
    f32 timer;
    u8 pad3[0x290 - 0x268];
    s32 extra;
};

void func_001AB660(Obj_1AB660* self)
{
    func_001AA298(self);
    if (self->mode == 0) {
        return;
    }
    if (self->flag == 0) {
        s32 close = (1.0f <= D_0026185C - self->timer);
        if ((u32)(self->mode - 1) < 2) {
            if (self->extra != 0 || close) {
                self->vtbl[15](self);
            }
        }
    } else {
        func_001AB980(self, D_00261860);
    }
}

extern f32 D_0026185C;

struct Obj_1ABE20 { u8 pad[0x260]; s32 state; f32 timer; };

void func_001ABE20(Obj_1ABE20* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->timer = D_0026185C;
    }
}

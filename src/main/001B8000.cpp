// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_1B89B8)(void* self);

struct Sub_1B89B8 {
    VFn_1B89B8* vtbl;
};

struct Obj_1B89B8 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x38];
    Sub_1B89B8* f50;
};

void func_00125108(Obj_1B89B8* self);
void func_00138BE0(void* a, void* b, s32 c);
void func_001389C8(void* a);

void func_001B89B8(Obj_1B89B8* self)
{
    func_00125108(self);
    self->f50->vtbl[54](self->f50);
    func_00138BE0(self->f14, self, 7);
    func_001389C8(self->f14);
}

struct Obj_1B9418 {
    u8 pad0[0x368];
    f32 f368;
};

void func_001B9448(Obj_1B9418* self);

void func_001B9418(Obj_1B9418* self, f32 v)
{
    f32 a = self->f368;
    f32 q = v / a;
    self->f368 = a * q;
    func_001B9448(self);
}

void func_001BAC28(void)
{
}

struct Obj_1BB1A0 {
    u8 pad0[0x538];
    u64 f538;
};

void func_001BB1A0(Obj_1BB1A0* self, s32 flag)
{
    self->f538 = (self->f538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

struct Obj_1BB400 { u8 pad[0x538]; u64 flags; };

void func_001B94F0(Obj_1BB400* self, s32 value);

void func_001BB400(Obj_1BB400* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags = (self->flags & ~(1ULL << 43)) | bit;
    func_001B94F0(self, value != 0 ? 2 : 0);
}

struct Node_1BB9A0 { s32 value; Node_1BB9A0* next; };

s32 func_001BB9A0(Node_1BB9A0* node, s32 value)
{
    while (node != 0) {
        if (node->value == value) return 1;
        node = node->next;
    }
    return 0;
}

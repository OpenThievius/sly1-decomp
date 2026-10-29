// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_5E08 {
    u8 pad0[0x624];
    void* f624;
};

struct Vtbl_5E08 {
    void* slots[0x148 / 4];
};

typedef void (*VFn_5E08)(void* self);

void func_001924C8(void* self);

void func_001E5E08(void* self)
{
    Obj_5E08* o = (Obj_5E08*)self;

    if (o->f624 != 0) {
        VFn_5E08 fn = *(VFn_5E08*)(*(u8**)o->f624 + 0x148);
        fn(o->f624);
    } else {
        func_001924C8(self);
    }
}

struct Obj_E7440 { u8 pad[0x260]; s32 f260; f32 f264; };
extern f32 D_00261868;

void func_001E7440(Obj_E7440* a0, s32 a1)
{
    if (a1 != a0->f260) {
        a0->f260 = a1;
        a0->f264 = D_00261868;
    }
}

struct Ptr_1E76E0 {
    s32 f0;
    union {
        s32 i4;
        f32 f4;
    };
};

struct Obj_1E76E0 {
    u8 pad0[0x218];
    Ptr_1E76E0* f218;
    u8 pad1[0x250 - 0x21C];
    s32 f250;
    u8 pad2[0x268 - 0x254];
    s32 f268;
};

extern s32 D_00270458;
void func_001AA998(void* self, s32 flag);
void func_001AAB20(void* self, f32 x, f32 y);
void func_001E7518(void* self, s32 mode);

void func_001E76E0(Obj_1E76E0* self, s32 value)
{
    s32 old = self->f250;
    func_001AA998(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->f218->i4 = 0;
        func_001AAB20(self, 640.0f, 360.0f);
    } else {
        self->f218->f4 = -20.0f;
        func_001AAB20(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->f268 = -1;
    func_001E7518(self, 3);
}

struct Ret_1E4880 { u8 pad[0x20]; f32 value; };

f32 func_001E4880(void* a0, void* a1, void* a2, Ret_1E4880* a3)
{
    return a3->value;
}

void func_001F5C0C(void* p, s32 v, s32 n);

struct Ctor_1E4E38 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 body[0x20]; };

Ctor_1E4E38* func_001E4E38(Ctor_1E4E38* self)
{
    self->f4 = 0;
    self->f10 = 0;
    self->fC = self->f8 = -1;
    func_001F5C0C(self->body, 0, 0x20);
    return self;
}

struct Blk_1E4E80 { s32 state; s32 a; s32 b; s32 c; s32 d; };

void func_001E4E80(Blk_1E4E80* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->state == 0) {
        self->state = 1;
        self->a = a1;
        self->b = a2;
        self->c = a3;
        self->d = a4;
    }
}

extern u8 D_00275AF0[];

void func_001E4E38(void* item);

void func_001E5328(void* owner, s32 code)
{
    if (code == 0xFFFF && owner != 0) {
        func_001E4E38(D_00275AF0);
    }
}

void func_001E5328(void* owner, s32 code);

void func_001E5358(void)
{
    func_001E5328((void*)1, 0xFFFF);
}

struct Table_1E5378 {
    u8 pad0[0x63C];
    void* p63C;
    void* p640;
    s32 f644;
    u8 pad1[0x650 - 0x648];
    f32 f650;
    f32 f654;
    f32 f658;
    f32 f65C;
};

void func_001921A8(void* self);
void* func_0018D500(s32 size);

void func_001E5378(Table_1E5378* self)
{
    func_001921A8(self);
    self->f644 = 1;
    self->p63C = func_0018D500(0x40);
    self->p640 = func_0018D500(0x40);
    self->f658 = -1.5f;
    self->f65C = 1.5f;
    self->f650 = -0.7f;
    self->f654 = 0.7f;
}

struct Table_1E53F8 {
    u8 pad0[0x638];
    s32 count;
    u8 pad1[4];
    void** items;
};

void func_001E53F8(Table_1E53F8* self, void* value)
{
    s32 n = self->count;
    if (n < 0x11) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

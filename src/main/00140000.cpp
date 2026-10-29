// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

s32 func_001C1A28(void* a, void* b);

struct Self_140550 {
    u8 pad0[0x598];
    s32 f598;
    void* f59C[32];
};

s32 func_00140550(Self_140550* self, void* arg)
{
    for (s32 i = 0; i < self->f598; i++) {
        if (func_001C1A28(arg, &self->f59C[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void func_0013EB30(void* p);
void func_00140640(void* a, void* b, void* c);

void func_00140688(void* self, void* b)
{
    func_00140640((u8*)self + 0x5C0, self, b);
}

void func_0013EB30(void* p);

void func_00140750(void* self)
{
    func_0013EB30((u8*)self + 0x554);
}

void func_001409D8(void) {}

s32 func_00141008(u8* bits, s32 index)
{
    s32 mask = 1 << (index & 7);
    bits += index / 8;
    return (bits[0xC] & mask) != 0;
}

struct Obj_1419C0 {
    u8 pad[0x550];
    s32 count;
    void* items[1];
};

void func_001419C0(Obj_1419C0* obj, void* item)
{
    s32 n = obj->count;
    obj->items[n] = item;
    obj->count = n + 1;
}

void func_001430C0(void** dst, void* value)
{
    *dst = value;
}

extern void* D_00261990;
void func_00143968(void* arg);

void func_001437E8(void)
{
    func_00143968(D_00261990);
}

extern void* D_00261990;
void func_00143A38(void* arg);

void func_001438D8(void)
{
    func_00143A38(D_00261990);
}

struct Obj_1439A8 {
    u8 pad[0x1F8];
    f32 value;
};
void func_00143560(void* self);

void func_001439A8(Obj_1439A8* self, f32 value)
{
    self->value = value;
    func_00143560(self);
}

struct Obj_143AF0 {
    u8 pad[0x340];
    s32 field;
};

void func_00143AF0(Obj_143AF0* obj)
{
    obj->field = 0;
}

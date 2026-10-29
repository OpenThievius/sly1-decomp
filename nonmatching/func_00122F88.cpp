// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The packed 64-bit spill differs: C emits aligned sd/ld while retail
//        uses sdl/sdr, and save order differs.
#include "common.h"

extern void func_001212D8(void*);
struct __attribute__((packed)) Object_122F88 {
    u8 pad[0x1C];
    s32 value;
    u64 data;
};

void func_00122F88(Object_122F88* object)
{
    s32 value = object->value;
    volatile struct __attribute__((packed)) Data { u64 value; } data;
    data.value = object->data;
    func_001212D8(object);
    object->data = data.value;
    object->value = value;
}

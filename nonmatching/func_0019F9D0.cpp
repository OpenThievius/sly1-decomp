// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: frame size is reproduced, but callback invocation and object initialization paths still differ substantially.
#include "common.h"
struct Entity_19F9D0 { u8 pad[0x24]; void* data; u8 pad28[0x6C]; u8 quad[16]; };
struct Alloc_19F9D0 { void** vtbl; };
extern s32 func_0013DFD8(void*, void*, void*, s32, void*);
extern void* func_0019EA78(s32, void*);
extern void func_0019EBE8(void*);
s32 func_0019F9D0(Entity_19F9D0* self, void* arg)
{
    u8 local[0x710];
    if (arg) {
        func_0013DFD8(*(void**)((u8*)self->data + 0x3F8), (u8*)self + 0x90,
                      (u8*)self + 0x80, 0x10, local);
    }
    void* obj = func_0019EA78(4, 0);
    if (obj) func_0019EBE8(obj);
    return 0;
}

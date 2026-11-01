// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 184/168, checked 2026-11-01
// NEAR: This candidate is 184 bytes versus retail 168; constant
//        materialization and save order differ.
#include "common.h"

struct Vtable_00124338 { u8 pad0[0x24]; void (*begin)(void*); u8 pad28[0x20]; void (*finish)(void*, s32, void*); };
struct Object_00124338 { Vtable_00124338* vtable; };
struct Frame_00124338 { u32 first; u32 current; u32 offset; u32 saved; };
extern u32 D_0027B314;

void func_00124338(Object_00124338* self)
{
    Frame_00124338 frame;
    u8* base = (u8*)self + 0x34;
    frame.first = (u32)base;
    frame.current = (u32)base;
    frame.offset = *(u32*)(base + 8);
    frame.saved = D_0027B314;
    D_0027B314 = (u32)&frame;
    self->vtable->begin(self);
    do {
        u32 next = *(u32*)frame.current;
        frame.offset += next;
        frame.current = frame.offset;
        if (next) ((Object_00124338*)next)->vtable->begin((void*)next);
    } while (frame.current);
    self->vtable->finish(self, 2, self);
    D_0027B314 = frame.saved;
}

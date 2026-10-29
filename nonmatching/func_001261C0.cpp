// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The candidate is 216 bytes versus retail 176; field-load registers
//        and branch layout remain different.
#include "common.h"

struct Vtable_001261C0 { u8 pad0[0xA8]; void (*finish)(void*, void*, void*); u8 padAC[0x14]; void (*start)(void*); };
struct Manager_001261C0 { u8 pad0[0xB0]; u32 flags; };
struct Object_001261C0 { Vtable_001261C0* vtable; u8 pad4[0x220]; Manager_001261C0* manager; };
struct Quad_001261C0 { u64 low; u64 high; };
extern void func_001261C0(Object_001261C0*, void*, void*);

void func_001261C0(Object_001261C0* self, void* context, Quad_001261C0* source)
{
    self->vtable->start(self);
    Manager_001261C0* manager = self->manager;
    if (manager && (manager->flags & 0x80)) {
        if (source) {
            *(s32*)((u8*)self->vtable + 0xA4) = 1;
            Quad_001261C0* target = (Quad_001261C0*)((u8*)manager + 0x60);
            target[0] = source[0];
            target[1] = source[1];
            target[2] = source[2];
            target[3] = source[3];
        } else {
            *(s32*)((u8*)self->vtable + 0xA4) = 0;
        }
    }
    self->vtable->finish(self, context, source);
}

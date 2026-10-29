// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The candidate frame is 32 bytes versus retail 48; saved-register
//        offsets and order differ.
#include "common.h"

struct Vtable_001249A8 { u8 pad0[0x4C]; void (*update)(void*); };
struct Node_001249A8 { Vtable_001249A8* vtable; u8 pad4[0x18]; Node_001249A8* next; };
struct Component_001249A8 { u8 pad0[0x20]; s32 state; };
struct Object_001249A8 {
    Vtable_001249A8* vtable;
    u8 pad4[0x10];
    void* resource;
    u8 pad18[0x1C];
    Node_001249A8* child;
    u8 pad38[0x1C8];
    Component_001249A8* component;
    u8 pad204[0x130];
};
extern void func_00128DB8(void*);
extern void func_00124540(void*);
extern void* func_0015A448(void*, s32, void*);
extern void func_0012A860(void*, void*);
extern void func_00165828(void*, void*);

void func_001249A8(Object_001249A8* self)
{
    func_00128DB8(self);
    func_00124540(self);
    if (self->component && self->component->state != -1) {
        void* item = func_0015A448(self->resource, self->component->state, self);
        if (item) func_0012A860(self, item);
    }
    func_00165828((u8*)self + 0x22C, self);
    for (Node_001249A8* node = self->child; node; node = node->next) {
        if (node->vtable->update) node->vtable->update(node);
    }
}

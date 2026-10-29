// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The frame and body are close, but retail passes callback arguments on
//        the stack while this candidate uses a3.
#include "common.h"
struct VTable_153328 { u8 pad[0xAC]; void* callback; };
struct Object_153328 { VTable_153328* vtable; u8 pad[0x2CC]; void* field_2D0; };
void func_001F5C0C(void*, s32, s32);
void func_00125B70(void*, void*, void*, void*, s32);
void func_0019D410(void*);
void func_001533A8();
void func_00153328(Object_153328* self, void* ignored, void* value)
{
    if (self->field_2D0 == 0) return;
    ((void (*)(Object_153328*, void*))self->vtable->callback)(self, value);
    u8 work[0x80];
    func_001F5C0C(work, 0, 0x80);
    func_00125B70(self, value, work + 0x10, (void*)func_001533A8, 0);
    *(void**)(work + 0x60) = self;
    func_0019D410(work);
}

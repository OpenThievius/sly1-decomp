// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 148/176, checked 2026-11-01
// NEAR: the candidate uses a 0x30-byte frame versus retail's 0x40-byte frame; entry and return branch layout differ.
#include "common.h"
struct Object_18AD88 { u8 pad000[0x724]; s32 state; u8 pad728[0x6E8]; void* alternate; u8 padE14[4]; void* primary; };
extern void* D_00262E10;
void func_001F3BD8(void*, void*);
void func_001C8418(void*, void*);
void func_001B6598(void*, s32*);
void func_001C8C08(void*);
void func_0018AD88(Object_18AD88* self)
{
    s32 scratch[4];
    if (self->state != 4) { func_001C8C08(self); return; }
    if (self->primary) {
        func_001F3BD8(self->primary, scratch);
        func_001C8418(self, scratch);
        return;
    }
    func_001B6598(self->alternate, &scratch[0]);
    s32 value = scratch[0];
    void* target = (value >= 0x438 && value < 0x43A) ? (u8*)self + 0x140 : (u8*)D_00262E10 + 0x140;
    func_001C8418(self, target);
}

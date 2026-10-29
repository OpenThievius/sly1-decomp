// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: Field offsets are corrected, but constant register choice and store
//        order still differ.
#include "common.h"

extern void func_001F5C0C(void*, s32, s32);
extern void func_0018C178(void*, s32);

struct State_0018BD58 { u8 pad0[4]; s32 first; s32 second; s32 handle; u8 pad1[4]; s32 state; };

void func_0018BD58(State_0018BD58* self, s32 first, s32 second)
{
    func_001F5C0C(self, 0, 20304);
    self->state = 0;
    self->handle = -1;
    func_0018C178(self, 0);
    self->first = first;
    self->second = second;
    *(volatile s32*)((char*)self + 0x4f44) = 0;
    *(volatile s32*)((char*)self + 0x4f48) = 0;
}

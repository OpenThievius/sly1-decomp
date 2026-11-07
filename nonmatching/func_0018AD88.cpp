// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 148/176, checked 2026-11-07
// NEAR: the candidate uses a 0x30-byte frame versus retail's 0x40-byte frame; entry and return branch layout differ.
#include "common.h"
struct Object_18AD88 { u8 pad000[0x724]; s32 state; u8 pad728[0x6E8]; void* alternate; u8 padE14[4]; void* primary; };
extern void* g_player;
void GetObjectWorldPosition(void*, void*);
void func_001C8418(void*, void*);
void GetStateWalkerCurrentKey(void*, s32*);
void UpdateAgentGoal(void*);
void UpdateGaugeAgentGoal(Object_18AD88* self)
{
    s32 scratch[4];
    if (self->state != 4) { UpdateAgentGoal(self); return; }
    if (self->primary) {
        GetObjectWorldPosition(self->primary, scratch);
        func_001C8418(self, scratch);
        return;
    }
    GetStateWalkerCurrentKey(self->alternate, &scratch[0]);
    s32 value = scratch[0];
    void* target = (value >= 0x438 && value < 0x43A) ? (u8*)self + 0x140 : (u8*)g_player + 0x140;
    func_001C8418(self, target);
}

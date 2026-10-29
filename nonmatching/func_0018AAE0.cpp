// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 192 bytes versus retail 168; branch and register
//        allocation differ.
#include "common.h"

extern s32 func_001DDA80(s32);
extern s32 func_001B6598(s32, s32*);

struct State_0018AAE0 {
    u8 pad0[0x14]; s32 first;
    u8 pad1[0x724 - 0x18]; s32 type;
    u8 pad2[0xC10 - 0x728]; s32 pending;
    u8 pad3[0xE10 - 0xC14]; s32 eventHandle;
};

s32 func_0018AAE0(State_0018AAE0* self)
{
    if (func_001DDA80(self->first) != 0) return 0;
    if (self->pending != 0) return 0;
    if (self->type == 16) return 1;
    if (self->type == 11) return 0;
    s32 (*callback)(State_0018AAE0*) = *(s32 (**)(State_0018AAE0*))(*(s32*)self + 0x198);
    if (callback(self) == 0) return 0;
    s32 event;
    func_001B6598(self->eventHandle, &event);
    return event == 1084 || (event >= 1085 && event != 1086) || event == 1082;
}

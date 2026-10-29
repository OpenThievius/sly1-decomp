// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the behavior is modelled, but retail keeps the input in $s1,
// uses a 48-byte frame, and has distinct branch-likely control flow. The
// current C forms did not reproduce that allocation or branch layout.
#include "common.h"
void func_001F6B50(s32 value);
struct Obj_1F7E58 { u8 pad[0x10]; u32 flags; u8 pad2[4]; s32 field_18; };
void func_001F7E58(Obj_1F7E58* self);
void func_001F7EA8(void* self)
{
    s32 type = *(s32*)((u8*)self + 0x20);
    u8* child;
    if (type == (s32)0x8000000A) {
        child = *(u8**)((u8*)self + 0x1C);
        void (*callback)(s32) = *(void (**)(s32))(child + 0x1C);
        if (callback) callback(*(s32*)(child + 0x20));
    } else if (type == (s32)0x80000009) {
        child = *(u8**)((u8*)self + 0x1C);
        *(s32*)(child + 0x24) = *(s32*)((u8*)self + 0x24);
        *(s32*)(child + 0x14) = *(s32*)((u8*)self + 0x28);
        *(s32*)(child + 0x18) = *(s32*)((u8*)self + 0x2C);
    } else {
        child = *(u8**)((u8*)self + 0x1C);
    }
    s32 value = *(s32*)(child + 8);
    if (value >= 0) func_001F6B50(value);
    func_001F7E58((Obj_1F7E58*)child);
    *(s32*)child = 0;
}

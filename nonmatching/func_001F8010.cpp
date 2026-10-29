// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: retail uses 64-bit saves, a likely branch, and a tail jump.
#include "common.h"

struct Obj_F8010 { u8 pad[0x14]; s32 f14; u8 pad18[4]; s32 f1C; s32 f20; };
struct Obj_F8010Result { u8 pad[0x14]; s32 f14; u8 pad18[4]; s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; };
void* func_001F7E78(void* input);
void* func_001F7FC0(s32 input, void* original);
void func_001FA670(void* source, void* destination, s32 size, s32 a3, s32 a4, s32 a5);

void func_001F8010(Obj_F8010* input, void* original)
{
    Obj_F8010Result* result = (Obj_F8010Result*)func_001F7E78(original);
    result->f1C = input->f1C;
    result->f14 = input->f14;
    result->f20 = (s32)0x80000009;
    void* found = func_001F7FC0(input->f20, original);
    result->f24 = (s32)found;
    if (found) {
        result->f28 = *(s32*)((u8*)found + 8);
        result->f2C = *(s32*)((u8*)found + 0x14);
    } else {
        result->f28 = 0;
        result->f2C = 0;
    }
    func_001FA670((void*)0x80000008, result, 0x40, 0, 0, 0);
}

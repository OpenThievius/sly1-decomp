// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 84/96, checked 2026-11-01
// Near miss: register allocation and conditional state-update sequence differ.
#include "common.h"
extern s32 func_001F8DB8(void*, s32, s32);
struct Obj_1377C0 { u8 pad0[8]; s32 f8; s32 fC; u8 pad10[4]; s32 f14; u8 pad18[8]; s32 f20; s32 f24; u8 pad28[0xC]; void* f34; };
void func_001377C0(Obj_1377C0* self)
{
    s32 size = self->fC;
    s32 start = self->f8;
    s32 limit = self->f14;
    self->f20 = start;
    if (size > 0x8000) size = 0x8000;
    if (size >= limit) size = limit;
    self->f24 = func_001F8DB8(self->f34, start, size);
}

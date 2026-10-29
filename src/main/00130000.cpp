// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1300D8 { u8 pad[0x20]; s32 f20; };

void func_001300D8(Obj_1300D8* a0, s32 a1)
{
    a0->f20 += a1;
}

void func_00130B48(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, s32 n, void* buf);
void func_0014D0A8(s32 n, void* buf, s32 zero);

void func_00130C20(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y)
{
    u8 buf[0x140];
    func_00130B48(a, b, c, d, x, 0.0f, y, 20, buf);
    func_0014D0A8(20, buf, 0);
}

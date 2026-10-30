// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the mode, null, global-float, and state checks match retail.
// The compiler delays saving the context pointer and schedules the callback
// argument setup differently from the target.
#include "common.h"

extern f32 D_0026185C;
void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

struct Info_00127378 { s32 kind; f32 f4; f32 f8; f32 fC; f32 f10; u8 pad14[8]; s32 flag1C; f32 value20; };
struct Self_00127378 { u8 pad0[0x2AC]; Info_00127378* info; };

void func_00127378(Self_00127378* self, s32 mode)
{
    if (mode != 1) {
        return;
    }
    Info_00127378* info = self->info;
    if (info != 0 && D_0026185C != 0.0f && info->flag1C == 0) {
        func_001BFCD8(info->kind, &info->flag1C, self, 0, &info->pad14[0], 0,
                     info->f4, info->f8, info->fC, info->f10, info->value20);
    }
}

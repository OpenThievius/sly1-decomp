// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 188/180, checked 2026-11-01
// NEAR: This candidate is 188 bytes versus retail 180; nested-loop pointer
//        and control-flow layout differ.
#include "common.h"

void func_00188C10(f32* a0, f32* a1, f32* a2, f32* out)
{
    f32* row = a1;
    for (s32 i = 0; i < 3; i++) {
        f32* src = row;
        f32* factor = a2;
        f32* dst = out;
        for (s32 j = 0; j < 3; j++) {
            *dst++ = *src++ * *factor++;
        }
        row += 4;
        out += 4;
    }
    f32* dst = a0;
    f32* target = out;
    for (s32 i = 0; i < 3; i++) *target++ = *dst++;
    for (f32* p = target + 8; p >= target; p -= 4) *p = 0.0f;
    out[3] = 1.0f;
}

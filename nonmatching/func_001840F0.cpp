// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 208/188, checked 2026-11-01
// Near match: corrected argument flow gives retail's 0x60 frame, but the
// attempt remains 20 bytes longer and differs in constant materialization,
// floating-register allocation, and arithmetic scheduling.
#include "common.h"

f32 func_00205210(f32 value);
void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d);
void func_001840F0(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d)
{
    f32 scale = 0.008729999f;
    a *= scale;
    f32 x = func_00205210(a);
    x = x + x * x * x;
    b *= scale;
    f32 y = func_00205210(b);
    f32 y2 = y * y;
    f32 y3 = y2 * y;
    y = y + y3;
    f32 z = x * x * y;
    z = z + y;
    f32 factor = 0.003921569f;
    func_00183F40(out0, out1, x, c, y, d * factor + z);
}

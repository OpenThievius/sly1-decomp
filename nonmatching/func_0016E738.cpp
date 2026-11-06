// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 497/520 (95.6%), checked 2026-11-06
#include "common.h"
// NEAR: 15 lines, FP register numbers only (instruction order and the sqrt.s tail now match retail
// with Fpu::Sqrt). Retail: d $f4, rt $f2, best $f6, zero copy $f7, nx*nx $f9, ny*ny $f8; ours: d and rt $f1,
// best $f2, zero $f4, squares $f7/$f6. Tried: pointer walk, m then one divide, d = d / m, inline Norm/Dot
// helpers, best declared first, sum of squares in one variable, nx = ny = 0.0f, ptr to range[i],
// permute.py --auto (no gain). Not run: decomp-permuter (its setup writes outside build/swarm/t67a/).
#include "fpu.h"

struct Pad_16E738 { u8 pad[0x20]; f32 mag; };
struct Axis_16E738 { f32 x, y; };
struct Range_16E738 { f32 lo, hi; };
extern Axis_16E738 D_00262A30[];

static inline f32 Clamp_16E738(f32 v, f32 lo, f32 hi)
{
    if (v < lo) return lo;
    if (hi < v) return hi;
    return v;
}

void func_0016E738(Pad_16E738* p, u8 x, u8 y, f32* outX, f32* outY, f32* outMag,
                   u8* prevX, u8* prevY, s32* flag, Range_16E738* range)
{
    f32 nx, ny;
    if (*flag == 0) {
        s32 r = 0;
        if (p->mag != 0.0f
            && (x != *prevX || y != *prevY || x < 0x60 || x > 0xA0 || y < 0x60 || y > 0xA0)) {
            r = 1;
        }
        *flag = r;
    }
    if (*flag != 0) {
        nx = ((f32)(s32)x + (f32)(s32)x) * 0.003921569f + -1.0f;
        ny = 1.0f - ((f32)(s32)y + (f32)(s32)y) * 0.003921569f;
    } else {
        nx = 0.0f;
        ny = 0.0f;
    }
    f32 sx = nx * nx;
    f32 sy = ny * ny;
    f32 best = 0.0f;
    for (u32 i = 0; i < 4; i++) {
        f32 d = nx * D_00262A30[i].x + ny * D_00262A30[i].y;
        f32 rt;
        if (0.0f <= d) {
            if (range[i].hi < d) range[i].hi = d;
            rt = d / range[i].hi;
        } else {
            if (d < range[i].lo) range[i].lo = d;
            rt = d / range[i].lo;
        }
        if (best < rt) best = rt;
    }
    f32 t = best - 0.35f;
    t = t + t;
    f32 c = Clamp_16E738(t, 0.0f, 1.0f);
    *outMag = c;
    f32 mag = Fpu::Sqrt(sx + sy);
    if (0.0001f < mag) {
        *outX = c * nx / mag;
        *outY = c * ny / mag;
    } else {
        *outX = *outY = 0.0f;
    }
    *prevX = x;
    *prevY = y;
}

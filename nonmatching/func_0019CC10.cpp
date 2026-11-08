// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 196/380 (51.6%), checked 2026-11-07
// NEAR: order: the logic is retail's; the float registers are allocated differently (about 70
//       lines).
// Tried (order-class pass 2): the products re-associated four ways (z*(ny*xa), xa*ny*z, ny*xa*z, z*xa*ny): 94 to 98 words, worse than 70.
#include "common.h"

void ComputeGridBlendWeights(void* self, f32* out, f32 x, f32 y, f32 z)
{
    f32 xa, xb;
    f32 z1, z2, z3;
    f32 ny = 1.0f - y;
    if (x < 0.0f) {
        xb = x + 1.0f;
        xa = -x;
        x = 0.0f;
    } else {
        xb = 1.0f - x;
        xa = 0.0f;
    }
    if (z < 1.0f) {
        z3 = 1.0f - z;
        z2 = 0.0f;
        z1 = 0.0f;
    } else if (z < 2.0f) {
        z = 2.0f - z;
        z2 = 0.0f;
        z1 = 1.0f - z;
        z3 = 0.0f;
    } else {
        z1 = 3.0f - z;
        z = 0.0f;
        z2 = 1.0f - z1;
        z3 = 0.0f;
    }
    out[0] = z3 * ny * xa;
    out[1] = z * ny * xa;
    out[2] = z1 * ny * xa;
    out[3] = z2 * ny * xa;
    out[4] = z3 * y * xa;
    out[5] = z * y * xa;
    out[6] = z1 * y * xa;
    out[7] = z2 * y * xa;
    out[8] = z3 * ny * xb;
    out[9] = z * ny * xb;
    out[10] = z1 * ny * xb;
    out[11] = z2 * ny * xb;
    out[12] = z3 * y * xb;
    out[13] = z * y * xb;
    out[14] = z1 * y * xb;
    out[15] = z2 * y * xb;
    out[16] = z3 * ny * x;
    out[17] = z * ny * x;
    out[18] = z1 * ny * x;
    out[19] = z2 * ny * x;
    out[20] = z3 * y * x;
    out[21] = z * y * x;
    out[22] = z1 * y * x;
    out[23] = z2 * y * x;
}

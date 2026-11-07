/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked arctangent of y / x for floats: the kernel's result, or a domain error for two
 * zeros reported through the error hook. One of the math library's files, each its own object
 * in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_00206A68(f32 y, f32 x);

f32 func_00205778(f32 y, f32 x)
{
    MathError e;
    f32 z = func_00206A68(y, x);

    if (D_0024FF78 == -1 || func_00209238(x) || func_00209238(y)) {
        return z;
    }
    if (x == 0.0f && y == 0.0f) {
        e.arg1 = (double)y;
        e.arg2 = (double)x;
        e.type = 1;
        e.name = "atan2f";
        e.result = 0.0;
        e.err = 0;
        if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
            *func_002014F0() = 0x21;
        }
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return (f32)e.result;
    }
    return z;
}

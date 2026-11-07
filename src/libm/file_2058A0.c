/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked remainder of x / y for floats: the kernel's result, or a domain error for a zero
 * divisor reported through the error hook. One of the math library's files, each its own object
 * in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_00206D50(f32 x, f32 y);

f32 func_002058A0(f32 x, f32 y)
{
    MathError e;
    f32 z = func_00206D50(x, y);

    if (D_0024FF78 == -1 || func_00209238(y) || func_00209238(x)) {
        return z;
    }
    if (y == 0.0f) {
        e.type = 1;
        e.name = "fmodf";
        e.err = 0;
        e.arg1 = (double)x;
        e.arg2 = (double)y;
        if (D_0024FF78 == 0) {
            e.result = (double)x;
        } else {
            e.result = 0.0 / 0.0;
        }
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

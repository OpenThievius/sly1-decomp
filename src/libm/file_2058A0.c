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
    f32 value = func_00206D50(x, y);

    if (D_0024FF78 == -1 || func_00209238(y) || func_00209238(x)) {
        return value;
    }
    if (y == 0.0f) {
        e.kind = 1;
        e.function = "fmodf";
        e.error_code = 0;
        e.first_arg = (double)x;
        e.second_arg = (double)y;
        if (D_0024FF78 == 0) {
            e.result = (double)x;
        } else {
            e.result = 0.0 / 0.0;
        }
        if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
            *func_002014F0() = 0x21;
        }
        if (e.error_code != 0) {
            *func_002014F0() = e.error_code;
        }
        return (f32)e.result;
    }
    return value;
}

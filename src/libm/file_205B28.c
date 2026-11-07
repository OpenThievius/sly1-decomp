/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked base-10 logarithm of a float: the kernel's result, or a singularity at zero or a
 * domain error below it reported through the error hook. One of the math library's files, each
 * its own object in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_002072C8(f32 x);

f32 func_00205B28(f32 x)
{
    MathError e;
    f32 z = func_002072C8(x);

    if (D_0024FF78 == -1 || func_00209238(x)) {
        return z;
    }
    if (x <= 0.0f) {
        e.err = 0;
        e.name = "log10f";
        e.arg1 = e.arg2 = (double)x;
        if (D_0024FF78 == 0) {
            e.result = -3.40282346638528859812e+38;
        } else {
            e.result = -D_0024FF70;
        }
        if (x == 0.0f) {
            e.type = 2;
            if (D_0024FF78 == 2) {
                *func_002014F0() = 0x22;
            } else if (!func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
        } else {
            e.type = 1;
            if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
        }
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return (f32)e.result;
    }
    return z;
}

/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked arccosine of a float: the kernel's result, or a domain error reported through
 * the error hook. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_00206298(f32 x);
f32 func_002052F8(f32 x);

f32 func_00205578(f32 x)
{
    MathError e;
    f32 value = func_00206298(x);

    if (D_0024FF78 == -1 || func_00209238(x)) {
        return value;
    }
    if (func_002052F8(x) > 1.0f) {
        e.kind = 1;
        e.function = "acosf";
        e.errorCode = 0;
        e.firstArg = e.secondArg = (double)x;
        e.result = 0.0;
        if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
            *func_002014F0() = 0x21;
        }
        if (e.errorCode != 0) {
            *func_002014F0() = e.errorCode;
        }
        return (f32)e.result;
    }
    return value;
}

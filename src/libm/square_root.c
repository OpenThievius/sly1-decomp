/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked square root of a float: the kernel's result, or a domain error below zero
 * reported through the error hook. One of the math library's files, each its own object in
 * retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 SquareRootKernel(f32 x);

f32 SquareRoot(f32 x)
{
    MathError e;
    f32 value = SquareRootKernel(x);

    if (g_mathErrorMode == -1 || IsNotANumber(x)) {
        return value;
    }
    if (x < 0.0f) {
        e.kind = 1;
        e.function = "sqrtf";
        e.errorCode = 0;
        e.firstArg = e.secondArg = (double)x;
        if (g_mathErrorMode == 0) {
            e.result = 0.0;
        } else {
            e.result = 0.0 / 0.0;
        }
        if (g_mathErrorMode == 2 || !HandleMathError(&e)) {
            *GetErrorNumberAddress() = 0x21;
        }
        if (e.errorCode != 0) {
            *GetErrorNumberAddress() = e.errorCode;
        }
        return (f32)e.result;
    }
    return value;
}

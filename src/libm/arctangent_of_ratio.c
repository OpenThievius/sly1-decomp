/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked arctangent of y / x for floats: the kernel's result, or a domain error for two
 * zeros reported through the error hook. One of the math library's files, each its own object
 * in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 ArctangentOfRatioKernel(f32 y, f32 x);

f32 ArctangentOfRatio(f32 y, f32 x)
{
    MathError e;
    f32 value = ArctangentOfRatioKernel(y, x);

    if (g_mathErrorMode == -1 || IsNotANumber(x) || IsNotANumber(y)) {
        return value;
    }
    if (x == 0.0f && y == 0.0f) {
        e.firstArg = (double)y;
        e.secondArg = (double)x;
        e.kind = 1;
        e.function = "atan2f";
        e.result = 0.0;
        e.errorCode = 0;
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

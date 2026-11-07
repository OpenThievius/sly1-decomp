/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked remainder of x / y for floats: the kernel's result, or a domain error for a zero
 * divisor reported through the error hook. One of the math library's files, each its own object
 * in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 FloatRemainderKernel(f32 x, f32 y);

f32 FloatRemainder(f32 x, f32 y)
{
    MathError e;
    f32 value = FloatRemainderKernel(x, y);

    if (g_mathErrorMode == -1 || IsNotANumber(y) || IsNotANumber(x)) {
        return value;
    }
    if (y == 0.0f) {
        e.kind = 1;
        e.function = "fmodf";
        e.errorCode = 0;
        e.firstArg = (double)x;
        e.secondArg = (double)y;
        if (g_mathErrorMode == 0) {
            e.result = (double)x;
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

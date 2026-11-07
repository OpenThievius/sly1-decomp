/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked base-10 logarithm of a float: the kernel's result, or a singularity at zero or a
 * domain error below it reported through the error hook. One of the math library's files, each
 * its own object in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 LogarithmBase10Kernel(f32 x);

f32 LogarithmBase10(f32 x)
{
    MathError e;
    f32 value = LogarithmBase10Kernel(x);

    if (g_mathErrorMode == -1 || IsNotANumber(x)) {
        return value;
    }
    if (x <= 0.0f) {
        e.errorCode = 0;
        e.function = "log10f";
        e.firstArg = e.secondArg = (double)x;
        if (g_mathErrorMode == 0) {
            e.result = -3.40282346638528859812e+38;
        } else {
            e.result = -g_mathInfinity;
        }
        if (x == 0.0f) {
            e.kind = 2;
            if (g_mathErrorMode == 2) {
                *GetErrorNumberAddress() = 0x22;
            } else if (!HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x21;
            }
        } else {
            e.kind = 1;
            if (g_mathErrorMode == 2 || !HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x21;
            }
        }
        if (e.errorCode != 0) {
            *GetErrorNumberAddress() = e.errorCode;
        }
        return (f32)e.result;
    }
    return value;
}

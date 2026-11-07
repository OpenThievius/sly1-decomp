/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked power x ** y of floats: the kernel's result, or a domain, singularity, overflow
 * or underflow error reported through the error hook. One of the math library's files, each its
 * own object in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 PowerKernel(f32 x, f32 y);

f32 Power(f32 x, f32 y)
{
    f32 value = PowerKernel(x, y);
    MathError e;

    if (g_mathErrorMode == -1 || IsNotANumber(y)) {
        return value;
    }
    if (IsNotANumber(x)) {
        if (y == 0.0f) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            e.result = (double)x;
            if (g_mathErrorMode == 2) {
                e.result = 1.0;
            } else if (!HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x21;
            }
            if (e.errorCode != 0) {
                *GetErrorNumberAddress() = e.errorCode;
            }
            return (f32)e.result;
        }
        return value;
    }
    if (x == 0.0f) {
        if (y == 0.0f) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            e.result = 0.0;
            if (g_mathErrorMode != 0) {
                e.result = 1.0;
            } else if (!HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x21;
            }
            if (e.errorCode != 0) {
                *GetErrorNumberAddress() = e.errorCode;
            }
            return (f32)e.result;
        }
        if (IsFinite(y) && y < 0.0f) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (g_mathErrorMode == 0) {
                e.result = 0.0;
            } else {
                e.result = -g_mathInfinity;
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
    if (!IsFinite(value) && IsFinite(x) && IsFinite(y)) {
        if (IsNotANumber(value)) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (g_mathErrorMode == 0) {
                e.result = 0.0;
            } else {
                e.result = 0.0 / 0.0;
            }
            if (g_mathErrorMode == 2 || !HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x21;
            }
        } else {
            e.kind = 3;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (g_mathErrorMode == 0) {
                e.result = 3.40282346638528859812e+38;
                y *= 0.5;
                if ((double)x < 0.0 && RoundToInteger((double)y) != (double)y) {
                    e.result = -3.40282346638528859812e+38;
                }
            } else {
                e.result = g_mathInfinity;
                y *= 0.5;
                if ((double)x < 0.0 && RoundToInteger((double)y) != (double)y) {
                    e.result = -g_mathInfinity;
                }
            }
            if (g_mathErrorMode == 2 || !HandleMathError(&e)) {
                *GetErrorNumberAddress() = 0x22;
            }
        }
        if (e.errorCode != 0) {
            *GetErrorNumberAddress() = e.errorCode;
        }
        return (f32)e.result;
    }
    if (value == 0.0f && IsFinite(x) && IsFinite(y)) {
        e.kind = 4;
        e.function = "powf";
        e.errorCode = 0;
        e.firstArg = (double)x;
        e.secondArg = (double)y;
        e.result = 0.0;
        if (g_mathErrorMode == 2 || !HandleMathError(&e)) {
            *GetErrorNumberAddress() = 0x22;
        }
        if (e.errorCode != 0) {
            *GetErrorNumberAddress() = e.errorCode;
        }
        return (f32)e.result;
    }
    return value;
}

/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked power x ** y of floats: the kernel's result, or a domain, singularity, overflow
 * or underflow error reported through the error hook. One of the math library's files, each its
 * own object in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_002073F8(f32 x, f32 y);

f32 func_00205C78(f32 x, f32 y)
{
    f32 value = func_002073F8(x, y);
    MathError e;

    if (D_0024FF78 == -1 || func_00209238(y)) {
        return value;
    }
    if (func_00209238(x)) {
        if (y == 0.0f) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            e.result = (double)x;
            if (D_0024FF78 == 2) {
                e.result = 1.0;
            } else if (!func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
            if (e.errorCode != 0) {
                *func_002014F0() = e.errorCode;
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
            if (D_0024FF78 != 0) {
                e.result = 1.0;
            } else if (!func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
            if (e.errorCode != 0) {
                *func_002014F0() = e.errorCode;
            }
            return (f32)e.result;
        }
        if (func_00209210(y) && y < 0.0f) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (D_0024FF78 == 0) {
                e.result = 0.0;
            } else {
                e.result = -D_0024FF70;
            }
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
    if (!func_00209210(value) && func_00209210(x) && func_00209210(y)) {
        if (func_00209238(value)) {
            e.kind = 1;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (D_0024FF78 == 0) {
                e.result = 0.0;
            } else {
                e.result = 0.0 / 0.0;
            }
            if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
        } else {
            e.kind = 3;
            e.function = "powf";
            e.errorCode = 0;
            e.firstArg = (double)x;
            e.secondArg = (double)y;
            if (D_0024FF78 == 0) {
                e.result = 3.40282346638528859812e+38;
                y *= 0.5;
                if ((double)x < 0.0 && func_00209010((double)y) != (double)y) {
                    e.result = -3.40282346638528859812e+38;
                }
            } else {
                e.result = D_0024FF70;
                y *= 0.5;
                if ((double)x < 0.0 && func_00209010((double)y) != (double)y) {
                    e.result = -D_0024FF70;
                }
            }
            if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
                *func_002014F0() = 0x22;
            }
        }
        if (e.errorCode != 0) {
            *func_002014F0() = e.errorCode;
        }
        return (f32)e.result;
    }
    if (value == 0.0f && func_00209210(x) && func_00209210(y)) {
        e.kind = 4;
        e.function = "powf";
        e.errorCode = 0;
        e.firstArg = (double)x;
        e.secondArg = (double)y;
        e.result = 0.0;
        if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
            *func_002014F0() = 0x22;
        }
        if (e.errorCode != 0) {
            *func_002014F0() = e.errorCode;
        }
        return (f32)e.result;
    }
    return value;
}

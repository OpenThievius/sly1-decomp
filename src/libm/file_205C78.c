/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The checked power x ** y of floats: the kernel's result, or a domain, singularity, overflow
 * or underflow error reported through the error hook. One of the math library's files, each its
 * own object in retail (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"

f32 func_002073F8(f32 x, f32 y);

f32 func_00205C78(f32 x, f32 y)
{
    f32 z = func_002073F8(x, y);
    MathError e;

    if (D_0024FF78 == -1 || func_00209238(y)) {
        return z;
    }
    if (func_00209238(x)) {
        if (y == 0.0f) {
            e.type = 1;
            e.name = "powf";
            e.err = 0;
            e.arg1 = (double)x;
            e.arg2 = (double)y;
            e.result = (double)x;
            if (D_0024FF78 == 2) {
                e.result = 1.0;
            } else if (!func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
            if (e.err != 0) {
                *func_002014F0() = e.err;
            }
            return (f32)e.result;
        }
        return z;
    }
    if (x == 0.0f) {
        if (y == 0.0f) {
            e.type = 1;
            e.name = "powf";
            e.err = 0;
            e.arg1 = (double)x;
            e.arg2 = (double)y;
            e.result = 0.0;
            if (D_0024FF78 != 0) {
                e.result = 1.0;
            } else if (!func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
            if (e.err != 0) {
                *func_002014F0() = e.err;
            }
            return (f32)e.result;
        }
        if (func_00209210(y) && y < 0.0f) {
            e.type = 1;
            e.name = "powf";
            e.err = 0;
            e.arg1 = (double)x;
            e.arg2 = (double)y;
            if (D_0024FF78 == 0) {
                e.result = 0.0;
            } else {
                e.result = -D_0024FF70;
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
    if (!func_00209210(z) && func_00209210(x) && func_00209210(y)) {
        if (func_00209238(z)) {
            e.type = 1;
            e.name = "powf";
            e.err = 0;
            e.arg1 = (double)x;
            e.arg2 = (double)y;
            if (D_0024FF78 == 0) {
                e.result = 0.0;
            } else {
                e.result = 0.0 / 0.0;
            }
            if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
                *func_002014F0() = 0x21;
            }
        } else {
            e.type = 3;
            e.name = "powf";
            e.err = 0;
            e.arg1 = (double)x;
            e.arg2 = (double)y;
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
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return (f32)e.result;
    }
    if (z == 0.0f && func_00209210(x) && func_00209210(y)) {
        e.type = 4;
        e.name = "powf";
        e.err = 0;
        e.arg1 = (double)x;
        e.arg2 = (double)y;
        e.result = 0.0;
        if (D_0024FF78 == 2 || !func_00208FE8(&e)) {
            *func_002014F0() = 0x22;
        }
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return (f32)e.result;
    }
    return z;
}

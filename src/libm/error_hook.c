/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The error hook the checked functions call: it handles nothing and returns 0. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "libm.h"
/* The math library's error hook, which the checked functions call with a MathError record; the
 * library has no handler, so it always returns 0 (the caller then sets the error number itself). */
s32 HandleMathError(MathError* e)
{
    s32 n = 0;

    if (e->firstArg != e->firstArg) {
        return 0;
    }
    return n;
}

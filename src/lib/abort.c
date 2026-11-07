/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C library's abort: raise signal 6 and leave with status 1, its own object in retail, the
 * first of the C library's after the C++ runtime. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

s32 func_00201668(s32 sig);
void func_001000B8(s32 status);

void func_002014D0(void)
{
    for (;;) {
        RaiseSignal(6);
        func_001000B8(1);
    }
}

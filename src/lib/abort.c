/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C library's abort: raise signal 6 and leave with status 1, its own object in retail, the
 * first of the C library's after the C++ runtime. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

s32 RaiseSignal(s32 sig);
void ExitProgram(s32 status);

void AbortProgram(void)
{
    for (;;) {
        RaiseSignal(6);
        ExitProgram(1);
    }
}

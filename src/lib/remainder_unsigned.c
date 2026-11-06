/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The unsigned remainder (__umoddi3). One of the toolchain runtime's division files, each its
 * own object in retail with its own table (include/divide.h). C, built by the Linux cc1 of
 * 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "divide.h"

u64 func_001FC3D0(u64 num, u64 den)
{
    u64 rem;

    divide(num, den, &rem);
    return rem;
}

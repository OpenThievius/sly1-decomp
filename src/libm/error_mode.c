/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The math library's error mode, which the checked functions read (libm.h): 1 here. One of the
 * math library's files, each its own object in retail (config/us/files.tsv): this one has no
 * code, only its constant, between the infinity's and the rounding function's in .rodata. C,
 * built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv, docs/TOOLCHAIN.md). Written
 * for this project from retail's data. */
#include "libm.h"

const s32 g_mathErrorMode = 1;

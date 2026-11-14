/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* Where the C library's error number is: the first word of its state record, which
 * D_0027696C points to. Its own object in retail, after abort. C, built by the Linux cc1 of
 * 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "common.h"

extern s32* g_libraryState;

/* The address of the C library's error number: the first word of the state record that
 * g_libraryState points to. The math library stores 0x21 (domain) or 0x22 (range) through it. */
s32* GetErrorNumberAddress(void)
{
    return g_libraryState;
}

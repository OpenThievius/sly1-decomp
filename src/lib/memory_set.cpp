// SPDX-License-Identifier: AGPL-3.0-or-later
// The C library's memory fill (memset in config/us/libcalls.tsv), its own object from 0x1F5C0C
// to 0x1F5CCC, padded to 0x1F5CD0 where the next object starts on 8 (config/us/files.tsv): one
// original assembly function (config/us/original_asm.tsv), word for word a member of the
// toolchain's libc.a assembled from a .S source. No data of its own.
#include "asm_func.h"

ASM_FUNC(func_001F5C0C);

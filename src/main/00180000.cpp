// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// Read-only data at 0x244EC0, far before the .rodata of this window's files (file_180EB0.cpp,
// file_182C18.cpp, whose func_001837E0 reads it); defined here until the file it belongs to is found.
extern const s32 D_00244EC0[32] = { 0, 1, 3, 4, 5, 6, 7, 9, 11, 12, 14, 17, 19, 20, 22, 26, 29, 31, 33, 34, 36, 38, 39, 40, 41, 43, 44, 45, 47, 48, 50, 0 };

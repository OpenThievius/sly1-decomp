// SPDX-License-Identifier: AGPL-3.0-or-later
// A range of two floats: func_001EB050 says whether a value is inside it, func_001EB080 asks
// it of each range of an array, func_001EB0F8 clamps a value to it (Range_1C30E8 inlines the
// same clamp). Written for this project from what retail's code does.
//
// Ranges sit at C08+0x738, in D_002754C8, D_00275C60 (the clamp of the D_002623C8 record's
// word 0x10, 00150000.cpp) and eight times in G262C70 (g262c70.h). 00128000.cpp copies
// D_00275C60 as one unaligned doubleword (U64_12A678, U64_12A748): that view stays the file's.
#ifndef S1EB050_H
#define S1EB050_H

#include "common.h"

struct S1EB050 {
    f32 lo;                 // 0x00
    f32 hi;                 // 0x04
};

typedef char check_S1EB050[sizeof(S1EB050) == 8 ? 1 : -1];

extern S1EB050 D_002754C8;      // 001D8000.cpp, 001E8000.cpp
extern S1EB050 D_00275C60;      // 001E4000.cpp defines it; 00128000.cpp, 00150000.cpp, 001E8000.cpp, file_1C29E8.cpp

#endif

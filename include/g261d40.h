// SPDX-License-Identifier: AGPL-3.0-or-later
// The four entries of D_00261D40 (001E4000.cpp defines them: { 0.8, 2, 5 } ... { 0, 50, 100 }):
// a threshold and two counts, which func_00151A88 (00150000.cpp) takes by the first that the
// value reaches. Written for this project from what retail's code does (globals.tsv). The
// label runs 0x30 bytes: four entries.
#ifndef G261D40_H
#define G261D40_H

#include "common.h"

struct G261D40 {
    f32 key;                // 0x00
    s32 a;                  // 0x04
    s32 b;                  // 0x08
};

typedef char check_G261D40[sizeof(G261D40) == 0xC ? 1 : -1];

extern G261D40 D_00261D40[4];   // 001E4000.cpp

#endif

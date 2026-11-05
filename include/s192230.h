// SPDX-License-Identifier: AGPL-3.0-or-later
// What a message carries to class 0x05's slot 13 (func_00192230, c05.h) and its overrides
// (func_0017AB58, func_00181D28, func_001DFB08, func_001E5CE8): three words, built on the
// senders' stacks. Written for this project from what retail's code does (g2027).
// func_001DAF08 also receives an object there (Rec_1DAF08: a kind at 0x08 and a link at
// 0x6CC), which is a class's object, not this record.
#ifndef S192230_H
#define S192230_H

#include "common.h"

struct S192230 {
    s32 f0;                 // 0x00
    s32 f4;                 // 0x04: func_0017AB58, func_001DFB08, func_001E5CE8
    s32 f8;                 // 0x08
};

#endif

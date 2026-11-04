// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x39 (descriptor D_0021E458, 0x560 bytes): a collision object with a scale and two
// factors that set the position of one of its children's tag-6 entry (func_00146298). Written
// for this project from what retail's code does (config/us/classes.tsv).
#ifndef C39_H
#define C39_H

#include "c03.h"

struct C39 : C03 {
    f32 scale;              // 0x550: 100.0 at set-up (slot 0); func_00146240 changes it
    f32 factorX;            // 0x554: read after the collision prefix (slot 10)
    f32 factorY;            // 0x558: read after factorX
    u8 pad55C[0x560 - 0x55C];
};

typedef char check_C39[sizeof(C39) == 0x560 ? 1 : -1];

void func_00146100(C39* self);                  // slot 0
void func_00146130(C39* self, void* stream);    // slot 10
void func_00146178(C39* self);                  // slot 16

#endif

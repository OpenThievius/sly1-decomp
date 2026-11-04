// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6D (descriptor D_00221520, 0x590 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Only the span func_00143648
// sets up is declared; its other users (file_143140.cpp) still reach the rest by offset.
#ifndef C6D_H
#define C6D_H

#include "c01.h"

// func_00143648 (slot 0) fills the identity frame at 0x80 and the settings at 0x1C0..0x208,
// then five sub-objects at 0x454, 0x460, 0x4C0, 0x510 and 0x520.
struct C6D : C01 {
    u8 pad34[0x590 - 0x34];
};

typedef char check_C6D[sizeof(C6D) == 0x590 ? 1 : -1];

void func_00143648(C6D* self);   // slot 0

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5C (descriptor D_0021D038, 0x2E0 bytes), a placed object (under 0x02) whose own
// methods only set it up (func_00199170 loads the common block and registers one table,
// D_0026A918; func_001991A8 does the same after loading). Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// It declares no field of its own yet: after the common block it is padding up to the
// descriptor's size.
#ifndef C5C_H
#define C5C_H

#include "placed_object.h"

struct C5C : PlacedObject {
    u8 pad2D0[0x2E0 - 0x2D0];
};

typedef char check_C5C[sizeof(C5C) == 0x2E0 ? 1 : -1];

void func_00199170(C5C* self);  // 0x5C slot 10 (load)
void func_001991A8(C5C* self);  // 0x5C slot 16 (after loading)

#endif

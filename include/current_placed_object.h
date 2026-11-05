// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x69 (descriptor D_00221210, 0x350 bytes), a placed object (class 0x02) that makes
// itself the current one (D_0026FCF0) after loading. Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x2D0 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef CURRENT_PLACED_OBJECT_H
#define CURRENT_PLACED_OBJECT_H

#include "c02.h"

// 0x69: after loading (slot 16) it sets two bits of the parent's doubleword at 0x2C8, sets
// 0x2D0 to -1 and has its level call func_0016AB38 on it (func_001DBCC8).
struct CurrentPlacedObject : C02 {
    s32 f2D0;               // 0x2D0: -1 after loading
    u8 pad2D4[0x350 - 0x2D4];
};

typedef char check_CurrentPlacedObject[sizeof(CurrentPlacedObject) == 0x350 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0016AED8(CurrentPlacedObject* self);                       // 0x69 slot 16

#endif

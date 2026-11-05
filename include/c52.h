// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x52 (descriptor D_00219A20, 0x2D0 bytes), a placed object that adds no fields of its
// own to class 0x02. Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef C52_H
#define C52_H

#include "placed_object.h"

struct C52 : PlacedObject {
};

typedef char check_C52[sizeof(C52) == 0x2D0 ? 1 : -1];

// The methods (config/us/classes.tsv). Slot 37 only calls the shared func_001261C0 and uses
// no argument.
void func_0016C508(void);                            // 0x52 slot 37

#endif

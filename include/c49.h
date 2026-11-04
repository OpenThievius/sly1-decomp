// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x49 (descriptor D_0021FD58, 0x570 bytes): a collision object that adds nothing of its
// own that the matched code reads (slot 0, func_0018F988, sets a flag of C03's doubleword).
// Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef C49_H
#define C49_H

#include "c03.h"

struct C49 : C03 {
    u8 pad550[0x570 - 0x550];
};

typedef char check_C49[sizeof(C49) == 0x570 ? 1 : -1];

#endif

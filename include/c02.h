// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x02 (descriptor D_00217498, 0x2D0 bytes), the parent of every placed object: what its
// load method 0x1289C0 reads is the common block of docs/DISC.md ("Objects"). Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// Its fields are declared as its own methods are consolidated; until then the class is padding
// after the root's, so the families under it can derive from it and keep their own fields at
// their retail offsets.
#ifndef C02_H
#define C02_H

#include "c01.h"

struct C02 : C01 {
    u8 pad34[0x2D0 - 0x34];
};

typedef char check_C02[sizeof(C02) == 0x2D0 ? 1 : -1];

#endif

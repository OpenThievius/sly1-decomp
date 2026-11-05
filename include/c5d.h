// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5D (descriptor D_0021D108, 0x330 bytes), a placed object (under 0x02) like 0x5C with
// its own table (D_0026A938): func_001991E0 loads the common block and registers it,
// func_00199218 does the same after loading. Written for this project from what retail's code
// does (config/us/classes.tsv).
//
// func_00199218 reads the ids of the objects it works on from a list and collects them with the
// ones found in the level (class 0x5C), then gives each a handle and the whole object one.
#ifndef C5D_H
#define C5D_H

#include "placed_object.h"

struct C5D : PlacedObject {
    s32 mask2D0;            // 0x2D0: tested against the global's flags (0x448) to choose 0x22F or 0x22E
    void* f2D4;             // 0x2D4: what the handle at 0x2D8 is made from
    void* f2D8;             // 0x2D8: the object's own handle
    s32 count2DC;           // 0x2DC: ids in the list below
    s32 ids2E0[8];          // 0x2E0: ids of the objects to collect
    s32 count300;           // 0x300: objects collected
    void* objs304[8];       // 0x304: the objects (found by kind 0x5C, then by id)
    u8 pad324[0x330 - 0x324];
};

typedef char check_C5D[sizeof(C5D) == 0x330 ? 1 : -1];

void func_001991E0(C5D* self);  // 0x5D slot 10 (load)
void func_00199218(C5D* self);  // 0x5D slot 16 (after loading)

#endif

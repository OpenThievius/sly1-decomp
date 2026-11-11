// SPDX-License-Identifier: AGPL-3.0-or-later
// Role: an object that owns a state walker, made from a state graph its link table resolves; a StateWalkerGroup finds it by kind and drives its walker.
// Class 0x5C (descriptor D_0021D038, 0x2E0 bytes), a placed object (under 0x02) whose own
// methods only set it up (func_00199170 loads the common block and registers one table,
// D_0026A918; func_001991A8 does the same after loading). Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// It declares no field of its own yet: after the common block it is padding up to the
// descriptor's size.
#ifndef STATE_WALKER_OBJECT_H
#define STATE_WALKER_OBJECT_H

#include "placed_object.h"

struct StateWalkerObject : PlacedObject {
    void* f2D0;             // 0x2D0: what its state walker is made from (func_00199218)
    void* f2D4;             // 0x2D4: its state walker (func_00199218)
    u8 pad2D8[0x2E0 - 0x2D8];
};

typedef char check_StateWalkerObject[sizeof(StateWalkerObject) == 0x2E0 ? 1 : -1];

void LoadStateWalkerObject(StateWalkerObject* self);  // 0x5C slot 10 (load)
void StartStateWalkerObject(StateWalkerObject* self);  // 0x5C slot 16 (after loading)

#endif

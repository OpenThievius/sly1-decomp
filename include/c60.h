// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x60 (descriptor 0x300 bytes, parent 0x02), an object with a three-float value at
// +0x2E0 and two floats after it that slots 17 and 37 read. Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C60_H
#define C60_H

#include "placed_object.h"

struct C60 : PlacedObject {
    s32 out2D0;             // 0x2D0: written by func_001E4C48 (slot 10)
    s32 out2D4;             // 0x2D4
    s32 out2D8;             // 0x2D8
    s32 out2DC;             // 0x2DC
    f32 v[3];               // 0x2E0: 1.0, 0.2, 0.1 at setup
    f32 f2EC;               // 0x2EC: 1.0 at setup; read by slots 17 and 37
    f32 f2F0;               // 0x2F0: 1.0 at setup; read by slot 17
    u8 pad2F4[0x300 - 0x2F4];
};

typedef char check_C60[sizeof(C60) == 0x300 ? 1 : -1];

void InitC60Object(C60* self);                       // slot 0
void LoadC60Object(C60* self, void* other);          // slot 10
void UpdateC60Object(C60* self);                       // slot 17
void DrawC60Object(C60* self, void* arg1, void* arg2); // slot 37

#endif

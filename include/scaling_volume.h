// SPDX-License-Identifier: AGPL-3.0-or-later
// Role: a volume of face meshes (ReadMeshTables) whose uniform scale eases toward a target (UpdateScalingVolume); it draws with that scale and tests whether a point is inside its face tree (IsPointInsideObjectFaces).
// Class 0x60 (descriptor 0x300 bytes, parent 0x02), an object with a three-float value at
// +0x2E0 and two floats after it that slots 17 and 37 read. Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef SCALING_VOLUME_H
#define SCALING_VOLUME_H

#include "placed_object.h"

struct ScalingVolume : PlacedObject {
    s32 out2D0;             // 0x2D0: written by func_001E4C48 (slot 10)
    s32 out2D4;             // 0x2D4
    s32 out2D8;             // 0x2D8
    s32 out2DC;             // 0x2DC
    f32 v[3];               // 0x2E0: 1.0, 0.2, 0.1 at setup
    f32 f2EC;               // 0x2EC: 1.0 at setup; read by slots 17 and 37
    f32 f2F0;               // 0x2F0: 1.0 at setup; read by slot 17
    u8 pad2F4[0x300 - 0x2F4];
};

typedef char check_ScalingVolume[sizeof(ScalingVolume) == 0x300 ? 1 : -1];

void InitScalingVolume(ScalingVolume* self);                       // slot 0
void LoadScalingVolume(ScalingVolume* self, void* other);          // slot 10
void UpdateScalingVolume(ScalingVolume* self);                       // slot 17
void DrawScalingVolume(ScalingVolume* self, void* arg1, void* arg2); // slot 37

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x54 (descriptor D_0021C4C8, 0x2E0 bytes), a camera-positioned object: a placed object
// that each update moves itself to the camera's position (MoveObjectToCamera), keeping its own
// height unless its one field of its own, at 0x2D0, is set. Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef CAMERA_POSITIONED_OBJECT_H
#define CAMERA_POSITIONED_OBJECT_H

#include "placed_object.h"

struct CameraPositionedObject : PlacedObject {
    s32 followHeight;       // 0x2D0: nonzero takes the camera's height too (MoveObjectToCamera)
    u8 pad2D4[0x2E0 - 0x2D4];
};

typedef char check_CameraPositionedObject[sizeof(CameraPositionedObject) == 0x2E0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001B5CD8(CameraPositionedObject* self);   // 0x54 slot 16
void func_001B5D28(CameraPositionedObject* self);   // 0x54 slot 17

#endif

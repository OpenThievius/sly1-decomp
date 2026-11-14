// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6D (descriptor D_00221520, 0x590 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Only the span func_00143648
// sets up is declared; its other users (camera.cpp) still reach the rest by offset.
#ifndef CAMERA_H
#define CAMERA_H

#include "base_object.h"
#include "camera_controller.h"
#include "placed_object.h"   // Vec02

// func_00143648 (slot 0) fills the identity frame at 0x80 and the settings at 0x1C0..0x208,
// then five sub-objects at 0x454, 0x460, 0x4C0, 0x510 and 0x520.
//
// The controllers are the kind t2173 (include/camera_controller.h). The camera keeps the ones in action in
// a stack ordered by key: func_00145088 pushes, func_001451F0 removes, func_00143E40 runs the
// first. The stack's size is the span up to the first controller (no code checks a limit).
struct Camera : BaseObject {
    u8 pad34[0x40 - 0x34];
    s32 position[4];        // 0x40: the camera's position
    f32 planes[3][4];       // 0x50: the rows of a 3x4 matrix whose columns are the normals of
                            //       four planes through f40 (func_00146038)
    union {
        s32 rotation[4];    // 0x80: the camera's rotation rows
        f32 g80[4];         // 0x80: func_00144FF8 reads the first two as floats
    };
    s32 f90[4];             // 0x90
    s32 fA0[4];             // 0xA0
    f32 fB0;                // 0xB0: scales a spawner's range (func_00155AB0)
    u8 padB4[0xC0 - 0xB4];
    f32 fC0;                // 0xC0: sent to VU1 with a listed object's draw (func_0013AD80)
    u8 padC4[0xD4 - 0xC4];
    f32 fD4;                // 0xD4: and this
    u8 padD8[0x100 - 0xD8];
    Vec02 f100; // 0x100
    u8 pad110[0x140 - 0x110];
    Vec02 f140; // 0x140
    Vec02 f150; // 0x150
    u8 pad160[0x1C0 - 0x160];
    f32 distanceScale;      // 0x1C0: scales the spawner range and the VU1 draw distance
    f32 zoom;               // 0x1C4: the current zoom
    f32 zoomGoal;           // 0x1C8: the zoom UpdateCamera approaches
    union {
        s32 i1CC;           // 0x1CC
        f32 zoomSpeed;      // 0x1CC: the speed of the zoom approach
    };
    f32 zoomProfile;        // 0x1D0: the ramp profile of the zoom approach
    u8 pad1D4[0x1E0 - 0x1D4];
    f32 aspectScale;        // 0x1E0: scales the yaw offset with f1C4 (func_00144BE8)
    f32 nearDistance;       // 0x1E4: the near clip distance
    f32 farDistance;        // 0x1E8: the far clip distance
    f32 f1EC; // 0x1EC
    f32 projectionScaleX;   // 0x1F0: ProjectPointToCamera divides the screen x by it
    f32 projectionScaleY;   // 0x1F4: and the screen y
    f32 fogNear;            // 0x1F8: the distance fog starts
    f32 fogFar;             // 0x1FC: the distance the fog is full
    f32 fogStrength;        // 0x200: how strong the fog is at fogFar
    u32 fogColor;           // 0x204: the word func_001B3510 writes to GIF register 0x3D (FOGCOL)
    u8 pad208[0x218 - 0x208];
    f32 swingStartTime;     // 0x218: the game time the view swing started
    s32 f21C;               // 0x21C
    s32 snapQueued;         // 0x220: set to ask for a snap on the next update
    s32 snapping;           // 0x224: a snap is in progress this frame
    s32 hasSnapValue;       // 0x228: set when the snap carries a value
    f32 snapValue;          // 0x22C: the value a snap with a source carries
    Vec02 v230;             // 0x230: from p to the screen point's place on the view ray (func_00145610)
    Vec02 v240;             // 0x240: D_00248D30 at func_00145610
    u8 pad250[0x270 - 0x250];
    Vec02 v270;             // 0x270: the offset the on-off controllers spring (func_001E3380)
    Vec02 v280;             // 0x280: its goal
    u8 pad290[0x2B0 - 0x290];
    f32 f2B0;               // 0x2B0
    f32 f2B4;               // 0x2B4
    f32 f2B8;               // 0x2B8
    f32 f2BC;               // 0x2BC
    f32 f2C0;               // 0x2C0
    u8 pad2C4[0x2D0 - 0x2C4];
    s32 f2D0[4];            // 0x2D0
    void* currentTarget;    // 0x2E0: the target object the camera last tracked
    void* f2E4; // 0x2E4
    void* f2E8; // 0x2E8
    BaseObject* f2EC; // 0x2EC
    Vec02 f2F0; // 0x2F0
    Vec02 f300; // 0x300
    Vec02 f310; // 0x310
    u8 pad320[0x334 - 0x320];
    s32 f334; // 0x334
    s32 f338; // 0x338
    u8 pad33C[0x340 - 0x33C];
    s32 objectCount;        // 0x340: how many objects are in the list at f344
    void* objects[8];       // 0x344: up to eight objects the camera keeps in view
    f32 controllerSwitchTime; // 0x364: the game time the first controller last started
    u8 pad368[0x370 - 0x368];
    s32 f370; // 0x370
    u8 pad374[0x3A0 - 0x374];
    Mat02 rot3A0;           // 0x3A0: a rotation DrawPhasedEffect turns each piece of its strip by
    s32 stackCount;         // 0x3D0: how many entries are in use
    CameraControllerEntry stack[8];    // 0x3D4: the first is in action
    CameraController ctl454;           // 0x454: D_00217398
    TargetCameraController ctl460;       // 0x460: D_002173B0
    FrameCameraController ctl4C0;       // 0x4C0: D_002173C8
    ValueCameraController ctl510;       // 0x510: D_002173E0
    OnOffCameraController ctl520;       // 0x520: D_002173F8
};

typedef char check_Camera[sizeof(Camera) == 0x590 ? 1 : -1];

void InitCamera(Camera* self);   // slot 0

#endif

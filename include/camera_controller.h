// SPDX-License-Identifier: AGPL-3.0-or-later
// The camera controllers (CameraController), five sub-objects embedded in class 0x6D (include/c6d.h)
// at +0x454, +0x460, +0x4C0, +0x510 and +0x520, and the stack of the ones in action. Written for
// this project from what retail's code does (config/us/tables.tsv, src/main/state_notifier.cpp,
// camera.cpp, on_off_object.cpp).
//
// func_00143648 (0x6D slot 0) stores each table and calls the base set-up func_00149398 (it
// keeps the owner) or a derived one. The camera keeps its controllers in a stack ordered by a
// key (func_00145088 pushes, func_001451F0 removes; count at +0x3D0, entries from +0x3D4): the
// first entry is in action, and func_00143E40 gives it the frame (slot 4).
//
// The tables are D_00217398, D_002173B0, D_002173C8, D_002173E0 and D_002173F8, defined in
// src/main/class_descriptors.cpp as arrays of function pointers; CameraControllerVt gives their slots types, and
// every object's first field points to its table (cast from the array where it is stored).
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "common.h"

struct Camera;     // the camera, class 0x6D (include/c6d.h), the owner of its controllers
struct CameraController;

typedef void (*CameraControllerFn)(CameraController* self, void* arg);

// The slots of a controller's table (6 slots, slot 5 empty in all five).
struct CameraControllerVt {
    CameraControllerFn m00;                  // 0x00: it has become the top
    CameraControllerFn m01;                  // 0x04: it has stopped being the top
    CameraControllerFn m02;                  // 0x08: it was pushed (func_00145088)
    CameraControllerFn m03;                  // 0x0C: it was removed (func_001451F0)
    void (*m04)(CameraController* self, u8* eye, u8* tail, f32 dt);    // 0x10: every frame, the top one
    void* m05;                                          // 0x14: unused
};

// The base: the table, the camera, and a word that func_0014AA90 sets (D_002173E0) and a
// controller of D_002173F8 uses as a pointer (its target, a class 0x63 object).
struct CameraController {
    const CameraControllerVt* vt;       // 0x00
    Camera* owner;             // 0x04: func_00149398 sets it; func_001493A0 asks whether it is the top
    union {
        s32 value;          // 0x08: func_001493B8, func_0014AA90 set it, func_0014AA98 clears it
        f32 g08;            // 0x08 as a float: a TargetCameraController's yaw (func_00149760
                            // stores it as a member: the alias rule, docs/TOOLCHAIN.md)
        void* ptr;          // 0x08: D_002173F8's target (func_001E30A0 clears it)
    };
};

// D_002173E0's: the base with a word of padding to the next object.
struct ValueCameraController : CameraController {
    u8 pad0C[0x10 - 0x0C];  // 0x0C
};

// D_002173B0's, 0x60 bytes: a mover with a stack of four numbers (func_001495E8 pushes,
// func_00149610 pops, func_00149638 reads the top). func_001496C0 (slot 0) sets it up from the
// camera at +0x80 and +0x1C8, func_0014A7B8 (slot 1) hands the camera its place back.
struct TargetCameraController : CameraController {
    union {
        s32 f0C;            // 0x0C: 0
        f32 yawSpeed;       // 0x0C as a float: the yaw speed (func_00149760)
    };
    f32 pitch;              // 0x10: D_00261BF0
    union {
        s32 f14;            // 0x14
        f32 pitchSpeed;     // 0x14 as a float: the pitch speed (func_00149760)
    };
    union {
        s32 f18;            // 0x18
        f32 zoomFraction;   // 0x18 as a float: func_00151300 compares it with the typed caption's
                            // value, func_00132500 scales text by it (the camera's +0x478)
    };
    union {
        s32 f1C;            // 0x1C
        f32 zoomSpeed;      // 0x1C as a float: g18's speed (func_00149760)
    };
    f32 f20;                // 0x20: 10.0, the divisor func_001496C0 takes the rate by
    f32 zoomMin;            // 0x24: the camera's f1C8 divided by f20
    f32 zoomMax;            // 0x28: the camera's f1C8; func_0014A7B8 gives it back
    f32 savedNearDistance;  // 0x2C: the camera's f1E4; func_0014A7B8 gives it back
    s32 items[4];           // 0x30: the stack of numbers
    s32 count;              // 0x40: how many
    s32 soundPaused;        // 0x44: set while p48's voice is paused (func_00149760)
    void* zoomSound;        // 0x48: func_001BF788 (n = 0) in func_0014A7B8
    void* p4C;              // 0x4C: func_001BF788 (n = 500) in func_0014A7B8
    union {
        s32 f50;            // 0x50
        u8* keptObject;     // 0x50: an object kept in view, its position at +0x140 (func_00149760)
    };
    f32 f54;                // 0x54: 0.5
    f32 sizeOverride;       // 0x58: -1.0
    void* anchorObject;     // 0x5C: the object whose place func_001493C8 reads, or 0
};

// A 3 by 4 block of the identity (D_002483D0) the controller keeps.
struct __attribute__((aligned(16))) CameraFrameBlock { u8 b[48]; };

// D_002173C8's, 0x50 bytes: func_0014A888 copies D_002483D0 to +0x20.
struct FrameCameraController : CameraController {
    u8 pad0C[0x20 - 0x0C];  // 0x0C
    CameraFrameBlock frame20;        // 0x20
};

// D_002173F8's, 0x70 bytes (up to the end of class 0x6D): +0x08 is a pointer (CameraController::ptr).
struct OnOffCameraController : CameraController {
    u8 pad0C[0x20 - 0x0C];  // 0x0C
    s32 f20;                // 0x20: set to 4 when no free span is found
    s32 active24;           // 0x24: func_001E2E68 sets it to 1
    u8 pad28[0x60 - 0x28];  // 0x28
    f32 lastMoveTime;       // 0x60: the game time the camera last moved or was held
    u8 pad64[0x70 - 0x64];  // 0x64
};

// One entry of the camera's stack (Camera::stack), sorted by key.
struct CameraControllerEntry {
    s32 key;                // 0x00: the entries are ordered by it (func_00145088)
    CameraController* ctl;             // 0x04: the controller
    void* target;           // 0x08: an object it works on (func_00143E40 calls its slot 73)
    void* arg;              // 0x0C: passed to the controller's slots
};

typedef char check_CameraController[sizeof(CameraController) == 0xC ? 1 : -1];
typedef char check_ValueCameraController[sizeof(ValueCameraController) == 0x10 ? 1 : -1];
typedef char check_TargetCameraController[sizeof(TargetCameraController) == 0x60 ? 1 : -1];
typedef char check_FrameCameraController[sizeof(FrameCameraController) == 0x50 ? 1 : -1];
typedef char check_OnOffCameraController[sizeof(OnOffCameraController) == 0x70 ? 1 : -1];
typedef char check_CameraControllerEntry[sizeof(CameraControllerEntry) == 0x10 ? 1 : -1];

#endif

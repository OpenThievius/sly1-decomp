// SPDX-License-Identifier: AGPL-3.0-or-later
// A part of a placed object's model (drawParts, 0x70 bytes each) and its state (partStates, 0x28
// bytes each), which the object's draw (placed_object.cpp) and the point graph's batch of them
// (point_graph.cpp) read.
#ifndef MODEL_PART_H
#define MODEL_PART_H

#include "common.h"
#include "placed_object.h"

struct FadeCubic {
    f32 c[4];
    f32 Eval(f32 t) const { return c[0] + t * (c[1] + t * (c[2] + t * c[3])); }
};
struct ModelPartFade {
    Vec02 axis;             // 0x00: the part's facing, turned by the object's transform
    FadeCubic cubic;        // 0x10: its weight by how squarely the camera sees it
};
struct ModelPartHook;
struct ModelPartHookVt {
    u8 pad00[0x10];
    void (*m04)(ModelPartHook* self, PlacedObject* obj, void* req); // 0x10
};
struct ModelPartHook {
    const ModelPartHookVt* vt;
};
struct ModelPart {
    Vec02 pos;              // 0x00: the part's point in the object
    f32 radius;             // 0x10
    s32 kind;               // 0x14
    u8 pad18[0x1C - 0x18];
    f32 nearFade;           // 0x1C
    f32 farFade;            // 0x20
    f32 dist;               // 0x24: FLT_MAX for the distance to the camera
    u8 pad28[0x30 - 0x28];
    ModelPartFade* fade;    // 0x30
    void* cameraFacing;     // 0x34: a camera-facing matrix source
    ModelPartHook* hook;    // 0x38
    u8 pad3C[0x60 - 0x3C];
    s32 f60;                // 0x60
    u8 pad64[0x68 - 0x64];
    void* matrix;           // 0x68: a matrix the transform is multiplied by
    u8 pad6C[0x70 - 0x6C];
};
// A part's state (partStates, 0x28 bytes each).
struct ModelPartState {
    u32 mask;               // 0x00: the camera's f21C bits it is drawn under
    u8 pad04[0x10 - 0x04];
    f32 fade;               // 0x10: eased to 1, or 0.5 until `until`
    f32 until;              // 0x14
    u8 pad18[0x28 - 0x18];
};

#endif

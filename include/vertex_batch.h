// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x1850-byte builder func_001C30E8 (trail_ribbon.cpp) keeps on its stack and hands to
// func_001619C0, func_00161A88, func_00161AB0, func_00161B10, func_00161BB0, func_00162508,
// func_00162680, func_001626A8, func_001626C0 and func_001626D8 (game_progress.cpp). Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g4664). Only a few of its
// words are known; the frame gives the size, no code checks it.
#ifndef VERTEX_BATCH_H
#define VERTEX_BATCH_H

#include "shapes.h"

struct LightObject;

// Sixteen bytes of the camera (InitVertexBatch copies them in), moved as bytes.
struct CameraBlock16 { u8 b[16]; };

struct VertexBatch {
    u8 pad000[0x40];        // 0x00: the transform SetVertexBatchTransform builds
    u8 inverse040[0x40];    // 0x40: its rigid inverse
    CameraBlock16 camera080; // 0x80: a copy of 16 bytes of the camera at +0x208
    f32 scale;              // 0x90: 1.0 at set-up
    s32 f94;                // 0x94: -1 at set-up; 4 once lights were selected (SelectVertexBatchLights)
    s32 f98;                // 0x98: func_001C30E8
    s32 strongestLight;     // 0x9C: what CollectLightsForSphere gives
    u8 pad0A0[0xAC - 0xA0];
    f32 f0AC;               // 0xAC: 1.0 at set-up
    s32 flaggedLightCount;  // 0xB0
    s32 lightCount;         // 0xB4
    LightObject* lights[16]; // 0xB8: the lights CollectLightsForSphere gives
    u8* mode;               // 0xF8: the batch's mode (SetVertexBatchMode); 0 for none
    f32 x;                  // 0xFC: func_00162680
    f32 y;                  // 0x100
    f32 z;                  // 0x104
    u8 pad108[0x114 - 0x108];
    U32P color;             // 0x114: the colour of the vertices that follow (SetVertexColor)
    U64P texCoord;          // 0x118: func_001626C0 (ldl/ldr; the pair of floats the caller copies in)
    u8 pad120[0x124 - 0x120];
    s32 vertexCount;        // 0x124: the vertices in the area below
    u8 vertices[0x1850 - 0x128]; // 0x128: the vertex area (0x1720 bytes) ResetVertexBatch clears
};

#endif

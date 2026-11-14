// SPDX-License-Identifier: AGPL-3.0-or-later
// The two 0x48-byte records at D_00262320 (render_frame.cpp defines both as zeros) and the
// pointer D_002622D8 to the one in use: three lists and the words func_0015E810,
// func_0015E9F0, func_0015ED50, func_0015EE80 and func_0015EFE8 (render_frame.cpp) keep. Written
// for this project from what retail's code does (build/swarm/st3/groups.tsv, g1808).
//
// The size: D_00262320 runs 0x90 bytes to the next label, two records.
//
// A frame is built in one record while a thread (func_0015EE80) draws the other one:
// func_0015E9F0 takes the next record and points the two buffer writers at its buffers,
// func_0015EC68 hands the lists over and wakes the thread.
#ifndef RENDER_FRAME_H
#define RENDER_FRAME_H

#include "base_object.h"

struct RenderFrame {
    u8 pad00[0x04];
    u8* bufA;               // 0x04: render_frame.cpp (g_renderFrames), func_0015E810, func_0015EE80
    u8 pad08[0x0C - 0x08];
    u8* bufB;               // 0x0C: render_frame.cpp, func_0015E810, func_0015EE80
    union {
        u8* frameData;      // 0x10: render_frame.cpp, func_0015E810
        s32 frameDataWord;  // 0x10: func_0015ED50
    };
    u8 pad14[0x18 - 0x14];
    u32 flags;              // 0x18: func_0015E9F0
    s32 hasMaskedImages;    // 0x1C: func_0015ED50
    List01 releasedObjects; // 0x20: func_0015E810, func_0015EFE8
    List01 detachedRecords; // 0x2C
    List01 deferredReleases; // 0x38
    s32 imageMask;          // 0x44: func_0015E9F0, func_0015ED50
};

typedef char check_RenderFrame[sizeof(RenderFrame) == 0x48 ? 1 : -1];

extern RenderFrame g_renderFrames[2];   // render_frame.cpp
extern RenderFrame* g_buildFrame;     // render_frame.cpp

#endif

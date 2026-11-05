// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x60-byte record func_00159CA0 and func_00159D00 (00158000.cpp) take as the first
// parameter (func_00152600 takes it out of its list): an object at +0, three colours and the
// times to go from the first to the second, hold the second and go to the third, then the
// start time. Written for this project from what retail's code does (build/swarm/st3/groups.tsv,
// g1786). The views end at 0x60; no code shows the size.
#ifndef COLOR_FADE_H
#define COLOR_FADE_H

#include "shapes.h"

struct ColorFade {
    void* obj;              // 0x00: an object (func_0019D6C0 calls its table)
    u8 pad04[0x3C - 0x04];
    Rgba4 startColor;       // 0x3C: func_00159D00
    Rgba4 holdColor;        // 0x40
    Rgba4 endColor;         // 0x44
    f32 fadeInTime;         // 0x48: startColor to holdColor
    f32 holdTime;           // 0x4C
    f32 fadeOutTime;        // 0x50: holdColor to endColor
    f32 startTime;          // 0x54: func_00159D00 subtracts it from the clock; func_00159ED0 sets it
    s32 mode;               // 0x58: 0 or 1; picks the request's mode (1 or 0x10)
    s32 running;            // 0x5C: func_00159ED0 sets 1, func_00159D00 clears it at the end
};

#endif

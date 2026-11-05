// SPDX-License-Identifier: AGPL-3.0-or-later
// The game clock at D_00261858 (.data): 59 declarations read it as a float array. Written for
// this project from what retail's code does (globals.tsv): func_00142F10 runs it (the tick
// count at 0x18, the accumulators), func_00143030 and func_001430B8 read parts of it, and the
// other readers take the time at 0x04, the step at 0x08 and the times at 0x10 and 0x14.
// No code shows its size: the views end at 0x20.
#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include "common.h"

struct GameClock {
    s32 running;            // 0x00: func_00142F10, func_001AB980
    f32 time;               // 0x04: func_00142F10, func_001430B8, func_001AB980 (D_0026185C)
    f32 dt;                 // 0x08: func_00142F10, func_001AB980, func_001EA118, file_184D78.cpp
    f32 previousDt;         // 0x0C: the last step's dt (func_00142F10 copies dt here; func_001EA118)
    f32 elapsed;            // 0x10: the sum of every step (func_00142F10, func_00143030 add to it); func_00143030, func_0016F238, func_001EA118, 0018C000.cpp
    f32 step;               // 0x14: func_00142F10, func_00143030 (step), func_001EA118 (real)
    s64 lastTick;           // 0x18: the tick count of the last step (func_00142F10, func_00143030)
};

extern GameClock D_00261858;

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// The scatter controller, the 0x24-byte record at D_00261EF0 (g_scatterController; file_14EE40.cpp
// defines it as zeros): ResetScatterController (func_00151A88) sets its count ranges and picks
// its table of level bands, ScatterObjectsAtPoint (func_00152010) counts its two countdowns down
// and scatters objects of kind 0x58 (and 0x57) when they run out, RaiseScatterLevelForObject
// (func_00151ED8) and SetScatterLevel (func_00152410) move the level through the table.
// Written for this project from what retail's code does (globals.tsv). The size is the label's
// (0x24).
#ifndef SCATTER_CONTROLLER_H
#define SCATTER_CONTROLLER_H

#include "common.h"

struct ThresholdRange;      // threshold_range.h

// A table ScatterController::table points at (D_00261D70[2], D_00261E30, D_00261E90; 0x60
// bytes): func_00151A88 picks one by the save's progress and draws the counts from it.
struct ScatterTable {
    s32 f00;                // 0x00
    f32 f04;                // 0x04: 1.0, or 0.5 in the second table
    f32 levelRange[2];      // 0x08: the level's bounds (func_00151D28 clamps to them)
    f32 f10;                // 0x10
    f32 raiseNew;           // 0x14: added to the level for an object not seen before (func_00151ED8)
    f32 raiseSeen;          // 0x18: the same for one already seen
    s32 countLoStart;       // 0x1C: the countdown's range at level 0 (func_00151A88, func_00152010)
    s32 countHiStart;       // 0x20
    s32 countLoEnd;         // 0x24: its range at level 1
    s32 countHiEnd;         // 0x28
    f32 bandStart1;         // 0x2C: from this level the spare count is at least spareCount1 (func_00151D28)
    s32 spareCount1;        // 0x30
    f32 bandStart2;         // 0x34: from this level, at least spareCount2
    s32 spareCount2;        // 0x38
    f32 f3C;                // 0x3C
    f32 f40;                // 0x40
    f32 f44;                // 0x44: added to the level by func_00152010
    f32 f48;                // 0x48: the same, in its other branch
    s32 f4C;                // 0x4C
    f32 f50;                // 0x50
    s32 count;              // 0x54: the entries of ranges
    ThresholdRange* ranges; // 0x58: the bands of the level (func_00151A88)
    s32 f5C;                // 0x5C
};

typedef char check_ScatterTable[sizeof(ScatterTable) == 0x60 ? 1 : -1];

struct ScatterController {
    u8 pad00[0x04];
    s32 refillLo;           // 0x04: func_00151A88 (4); the range of a scatter when countdown runs out
    s32 refillHi;           // 0x08: func_00151A88 (6)
    s32 countLo;            // 0x0C: func_00151A88 (1); the range of a scatter otherwise
    s32 countHi;            // 0x10: func_00151A88 (3)
    s32 countdown;          // 0x14: func_00151A88 draws it, func_00152010 counts it down
    s32 bandCountdown;      // 0x18: drawn from the level band (func_00151A88, func_00152010)
    void* table;            // 0x1C: func_00151A88, func_00151ED8, func_00152010, func_00152410
    s32 f20;                // 0x20: func_00151A88
};

typedef char check_ScatterController[sizeof(ScatterController) == 0x24 ? 1 : -1];

extern ScatterController g_scatterController;      // file_14EE40.cpp

#endif

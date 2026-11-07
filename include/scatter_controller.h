// SPDX-License-Identifier: AGPL-3.0-or-later
// The scatter controller, the 0x24-byte record at D_00261EF0 (g_scatterController; 001E4000.cpp
// defines it as zeros): ResetScatterController (func_00151A88) sets its count ranges and picks
// its table of level bands, ScatterObjectsAtPoint (func_00152010) counts its two countdowns down
// and scatters objects of kind 0x58 (and 0x57) when they run out, RaiseScatterLevelForObject
// (func_00151ED8) and SetScatterLevel (func_00152410) move the level through the table.
// Written for this project from what retail's code does (globals.tsv). The size is the label's
// (0x24).
#ifndef SCATTER_CONTROLLER_H
#define SCATTER_CONTROLLER_H

#include "common.h"

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

extern ScatterController D_00261EF0;      // 001E4000.cpp

#endif

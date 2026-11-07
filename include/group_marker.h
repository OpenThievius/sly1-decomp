// SPDX-License-Identifier: AGPL-3.0-or-later
// The 18 rows of 0x80 bytes at D_0026AC30 (group_marker.cpp defines them): a function, a word
// and the rest, which func_0019D4B0 and func_0019DF48 fill and call.
// Written for this project from what retail's code does (globals.tsv). The label runs 0x900
// bytes to D_0026B530.
//
// One row per group of the deferred requests: func_0019D4B0 puts a group's row in front of its
// requests in the sorted list when the row has a handler.
#ifndef GROUP_MARKER_H
#define GROUP_MARKER_H

#include "common.h"

struct GroupMarker {
    union {
        void (*handler)(void);  // 0x00: func_0019DF48 sets it per group
        s32 handlerWord;        // 0x00: func_0019D4B0 tests it for zero
    };
    s32 f04;                // 0x04: func_0019D4B0
    s32 f08;                // 0x08: func_0019D4B0, func_0019DF48
    u8 pad0C[0x80 - 0x0C];
};

typedef char check_GroupMarker[sizeof(GroupMarker) == 0x80 ? 1 : -1];

// The globals of group_marker.cpp's .data that have no initialiser, declared in their order
// (GCC writes such globals in the order they are first declared): the next free deferred
// request (D_005E4700), a GIF tag, the markers.
extern u8 D_0026AC10[16];
extern s32 D_0026AC20[4];
extern GroupMarker D_0026AC30[18];

#endif

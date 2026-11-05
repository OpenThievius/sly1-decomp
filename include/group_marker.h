// SPDX-License-Identifier: AGPL-3.0-or-later
// The 18 rows of 0x80 bytes at D_0026AC30 (001E4000.cpp defines them as zeros): a function, a
// word and the rest, which func_0019D4B0 and func_0019DF48 (0019C000.cpp) fill and call.
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

extern GroupMarker D_0026AC30[18];  // 001E4000.cpp

#endif

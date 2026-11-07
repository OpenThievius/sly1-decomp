// SPDX-License-Identifier: AGPL-3.0-or-later
// The loading progress record: InitLoadProgress (func_00193210(rec, a, b, c, d)) fills it, and
// RunPendingWorldLoad (func_001E4EA8) keeps one in a 0x28-byte local and gives it to the
// buffered stream it loads the world from as the stream's owner. The record func_00193210 fills and returns (pause_menu.cpp): five words, then
// four words it stores one by one with swl/swr (its arguments 1 to 4 are such words too).
// func_001E4EA8 keeps one in a 0x28-byte local. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g4869 and g4870).
#ifndef LOAD_PROGRESS_H
#define LOAD_PROGRESS_H

#include "shapes.h"

// A colour of the bar, read as four bytes at an unaligned place.
struct __attribute__((packed)) BarColor { u8 r, g, b, a; };

// UpdateLoadProgress (func_00193288) takes the first value it is given as the whole and counts
// the updates that bring no change; DrawLoadProgressBar (func_00193318) draws the part done in
// the bar colour and the rest in one of three colours chosen by that count.
struct LoadProgress {
    s32 active;             // 0x00: nonzero while the bar is shown
    s32 scale;              // 0x04: twice the first value
    s32 total;              // 0x08: the first value
    s32 current;            // 0x0C: the last value
    s32 stalls;             // 0x10: the updates in a row that kept the value
    union {
        U32P f14;           // 0x14
        BarColor barColor;  // 0x14: the part done
    };
    union {
        U32P f18;           // 0x18
        BarColor color0;    // 0x18: the rest, no stall
    };
    union {
        U32P f1C;           // 0x1C
        BarColor color1;    // 0x1C: the rest, one stall
    };
    union {
        U32P f20;           // 0x20
        BarColor color2;    // 0x20: the rest, more
    };
};

typedef char check_LoadProgress[sizeof(LoadProgress) == 0x24 ? 1 : -1];

#endif

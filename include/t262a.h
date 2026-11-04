// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t262a: the nine static button-code records in .data (D_00262A80 .. D_00262C48). Written
// for this project from what retail's code does (config/us/tables.tsv, src/main/0016C000.cpp).
//
// Each record holds a sequence of pad button masks (its data block precedes it in .data), the
// callback to run when the player has pressed them in order, and the record's place in the list
// D_00262DFC. func_0016F588 registers all nine through func_0016F188, func_0016F238 advances
// every record's position on a button change (a match moves it on, a miss back to 0), and
// func_0016F2E0 runs the callback of the completed record with the longest sequence.
//
// The records are 0x1C bytes; in .data they are 4 bytes apart from their neighbours (the next
// data block starts 8-aligned), which T262A_Slot adds for the eight that are followed by one.
#ifndef T262A_H
#define T262A_H

#include "common.h"

typedef void (*Fn262A)(s32 arg);

struct T262A {
    const u16* buttons;     // 0x00: the sequence
    s32 length;             // 0x04: how many masks (11 or 13)
    Fn262A fn;              // 0x08: run when the whole sequence has been pressed
    s32 arg;                // 0x0C: its argument
    s32 pos;                // 0x10: how many masks of the sequence matched so far
    s32 drop;               // 0x14: set to have func_0016F2E0 unlink the record
    T262A* next;            // 0x18: the next record in D_00262DFC
};

// A record followed by the 4 bytes that keep the next data block 8-aligned.
struct T262A_Slot {
    T262A rec;              // 0x00
    u8 pad1C[4];            // 0x1C
};

typedef char check_T262A[sizeof(T262A) == 0x1C ? 1 : -1];
typedef char check_T262A_Slot[sizeof(T262A_Slot) == 0x20 ? 1 : -1];

#endif

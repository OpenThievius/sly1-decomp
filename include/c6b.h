// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6B (descriptor D_002213D0, 0x6E0 bytes), an object that checks the game's own code
// with a CRC-32: func_0012B6B8 builds the table and sets the range to check, func_0012B760
// folds up to 64 words of the range into the sum each time it runs. Written for this project
// from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C6B_H
#define C6B_H

#include "c02.h"

struct C6B : C02 {
    u32 crc;                // 0x2D0: the running sum, 0xFFFFFFFF at the start
    union {
        s32 start;          // 0x2D4: where the range starts (func_0012B6B8 sets it)
        u32* cursor;        // 0x2D4: the next word to fold in (func_0012B760)
    };
    union {
        void* end;          // 0x2D8: the range's end (func_0012B6B8 sets it)
        s32 remaining;      // 0x2D8: the bytes left (func_0012B760)
    };
    u32 table[256];         // 0x2DC: the CRC-32 table (polynomial 0xEDB88320)
    u8 pad6DC[0x6E0 - 0x6DC];
};

typedef char check_C6B[sizeof(C6B) == 0x6E0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0012B6B8(C6B* self);                       // 0x6B slot 0
void func_0012B760(C6B* self);                       // 0x6B slot 17

#endif

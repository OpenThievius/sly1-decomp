// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x41 (descriptor D_0021D3B8, 0x670 bytes), an object with collision that gathers the
// objects of ids 0x269..0x287 around it when it is loaded (func_0019B0A0) and keeps a record
// for one of them (func_00159478) at 0x5F8. Written for this project from what retail's code
// does (config/us/classes.tsv; src/main/00198000.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C41_H
#define C41_H

#include "c03.h"

// The eight bytes func_0019B250 (slot 9) keeps across the copy, read as one unaligned
// doubleword.
struct __attribute__((packed)) Pk8_41 {
    s64 v;
};

struct C41 : C03 {
    s32 mode550;            // 0x550: -1 at set-up (func_0019B188, slot 16); func_0019BE08 (slot 45) tests it for 3
    u8 pad554[0x55C - 0x554];
    f32 f55C;               // 0x55C: slot 0 (func_0019B038) stores func_001EAB48 of the clock
    u8 pad560[0x564 - 0x560];
    s32 n564;               // 0x564: how many of f568 are filled (slot 10, func_0019B0A0)
    void* f568[16];         // 0x568: the found objects of ids 0x269..0x278
    s32 n5A8;               // 0x5A8: how many of f5AC are filled
    void* f5AC[19];         // 0x5AC: those of ids 0x279..0x287
    void* f5F8;             // 0x5F8: the record func_00159478 sets up (slot 10); its first word is the
                            //        object func_0019BE08 sends a message to
    u8 pad5FC[0x600 - 0x5FC];
    Pk8_41 q600;            // 0x600: kept by slot 9 (func_0019B250)
    f32 f608;               // 0x608: 0.5 at set-up
    f32 f60C;               // 0x60C: 1.0 at set-up
    u8 pad610[0x650 - 0x610];
    Vec02 v650;             // 0x650: v140, copied by slot 16
    u8 pad660[0x664 - 0x660];
    s32 f664;               // 0x664: -1 at set-up
    u8 pad668[0x670 - 0x668];
};

typedef char check_C41[sizeof(C41) == 0x670 ? 1 : -1];

#endif

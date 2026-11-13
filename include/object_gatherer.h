// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x41 (descriptor D_0021D3B8, 0x670 bytes), an object with collision that gathers the
// objects of ids 0x269..0x287 around it when it is loaded (func_0019B0A0) and keeps a record
// for one of them (func_00159478) at 0x5F8. Written for this project from what retail's code
// does (config/us/classes.tsv; src/main/object_gatherer.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef OBJECT_GATHERER_H
#define OBJECT_GATHERER_H

#include "collider.h"

// The eight bytes func_0019B250 (slot 9) keeps across the copy, read as one unaligned
// doubleword.
struct __attribute__((packed)) PackedS64 {
    s64 v;
};

struct ObjectGatherer : Collider {
    s32 state;            // 0x550: -1 at set-up (func_0019B188, slot 16); func_0019BE08 (slot 45) tests it for 3
    f32 f554;               // 0x554: g_gameClock[1] when the mode last changed (func_0019C1C0)
    f32 f558;               // 0x558: when the mode next changes
    f32 f55C;               // 0x55C: slot 0 (func_0019B038) stores func_001EAB48 of the clock
    s32 ring;               // 0x560: which of the found objects the ring is on (func_0019BC40)
    s32 lowCount;               // 0x564: how many of lowObjects are filled (slot 10, func_0019B0A0)
    void* lowObjects[16];         // 0x568: the found objects of ids 0x269..0x278
    s32 highCount;               // 0x5A8: how many of highObjects are filled
    void* highObjects[16];         // 0x5AC: those of ids 0x279..0x287
    void* base5EC;          // 0x5EC: the object of id 0x268 (g_objectGathererLoadLinks)
    f32 near5F0;            // 0x5F0: how far the point moves before the ring advances in state 1
    f32 near5F4;            // 0x5F4: the same in state 2
    void* group;             // 0x5F8: the record func_00159478 sets up (slot 10); its first word is the
                            //        object func_0019BE08 sends a message to
    void* f5FC;             // 0x5FC
    PackedS64 q600;            // 0x600: kept by slot 9 (func_0019B250)
    f32 f608;               // 0x608: 0.5 at set-up
    f32 f60C;               // 0x60C: 1.0 at set-up
    f32 f610;               // 0x610
    f32 f614;               // 0x614: the speed of state 1 (UpdateObjectGatherer)
    f32 f618;               // 0x618: the speed of state 2
    f32 f61C;               // 0x61C: the speed set each update
    f32 f620;               // 0x620: the weight of the upward push
    f32 f624;               // 0x624: how near another gatherer is sent to state 2
    u8 pad628[0x630 - 0x628];
    Vec02 v630;             // 0x630: the direction it heads in
    Vec02 v640;             // 0x640: the point mode 1 picks
    Vec02 v650;             // 0x650: v140, copied by slot 16
    void* f660;             // 0x660
    s32 f664;               // 0x664: -1 at set-up
    s32 f668;               // 0x668
    u8 pad66C[0x670 - 0x66C];
};

typedef char check_ObjectGatherer[sizeof(ObjectGatherer) == 0x670 ? 1 : -1];

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x40 (descriptor D_0021C598, 0x6A0 bytes), a part with collision that moves between
// states (slot 20 and 45 set one, slot 17 steps it) and shows one of up to sixteen objects (or one
// of eight, in mode 1) at a time. Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/00158000.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C40_H
#define C40_H

#include "c73.h"
#include "c03.h"

// Two floats the level data keeps as one doubleword (a range, a pair of times): func_0015AAE0
// sets them from tables of doublewords, func_0015B128 and func_0015AEB0 read each float.
struct __attribute__((packed)) Pk40 {
    u64 v;
};
union Pair40 {
    Pk40 pk;
    struct {
        f32 a;
        f32 b;
    };
};

// 0x40: mode 0 shows one object and keeps a handle at 0x5E4 (func_001BFCD8 makes it), mode 1
// steps through its objects with the timers below. State -1 at set-up; 0, 1, 3, 5 and 6 are
// the ones func_0015B128 and func_0015B4D0 distinguish.
struct C40 : C03 {
    s32 mode;               // 0x550: 0 or 1
    s32 state;              // 0x554: -1 at set-up
    f32 f558;               // 0x558: the time the state started
    f32 f55C;               // 0x55C: the time it ends
    s32 f560;               // 0x560: the state slot 16 starts in
    s32 count;              // 0x564: how many objects in objs
    s32 index;              // 0x568: the one shown
    C02* objs[16];          // 0x56C: found by kind 0x23C + i (func_0015AC08)
    s32 count5AC;           // 0x5AC: how many in objs5B0
    C02* objs5B0[8];        // 0x5B0: mode 1 only: found by kind 0x24D + i
    C02* obj5D0;            // 0x5D0
    C77* group;             // 0x5D4: a 0x77 or 0x78 found by func_00159478 (kept by slot 10)
    u8 pad5D8[0x5DC - 0x5D8];
    Pk40 f5DC;              // 0x5DC: kept across the copy by slot 9
    void* handle;           // 0x5E4: made by func_001BFCD8 in mode 0, given back with func_001BF788
    u8 pad5E8[0x5F0 - 0x5E8];
    Vec02 v5F0;             // 0x5F0
    u8 pad600[0x610 - 0x600];
    Pair40 p610;            // 0x610: set up from D_00262180
    Pair40 p618;            // 0x618: D_00262188
    Pair40 p620;            // 0x620: D_00262190
    Pair40 p628;            // 0x628: D_00262198
    s32 f630;               // 0x630: a kind, or -1
    s32 f634;               // 0x634
    f32 f638;               // 0x638
    Pair40 p63C;            // 0x63C: D_002621A0; a range for func_001EAAE0
    f32 f644;               // 0x644
    f32 f648;               // 0x648
    f32 f64C;               // 0x64C: twice radius3CC
    Pair40 p650;            // 0x650: D_002621A8
    Pair40 p658;            // 0x658: D_002621B0
    Pair40 p660;            // 0x660: D_002621B8
    f32 f668;               // 0x668
    u8 pad66C[0x670 - 0x66C];
    Pair40 p670;            // 0x670: D_002621C0
    u8 pad678[0x680 - 0x678];
    f32 f680;               // 0x680
    u8 pad684[0x688 - 0x684];
    f32 f688;               // 0x688
    s32 f68C;               // 0x68C: 1 at set-up, steps the index by 1 or -1
    s32 f690;               // 0x690: -1 at set-up
    u8 pad694[0x6A0 - 0x694];
};

typedef char check_C40[sizeof(C40) == 0x6A0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
// (Slot 45, func_0015B720, takes a message record only that file knows.)
void func_0015AAE0(C40* self);                       // 0x40 slot 0
void func_0015AD80(C40* self);                       // 0x40 slot 9
void func_0015AC08(C40* self, void* stream);         // 0x40 slot 10
void func_0015AEB0(C40* self);                       // 0x40 slot 16
void func_0015B128(C40* self);                       // 0x40 slot 17
void func_0015AE38(C40* self, s32 flag);             // 0x40 slot 20
void func_0015B4D0(C40* self, void* a1, void* a2);   // 0x40 slot 37

#endif

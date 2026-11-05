// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x46 (descriptor D_0021DBD8, 0x590 bytes): a collision object with a state of its own
// (func_0014F110 sets it; slot 17, func_0014F058, runs it), kept in the world's list at +0x1C78.
// Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef C46_H
#define C46_H

#include "c03.h"

// Eight bytes at an odd word offset, which slot 9 keeps across the copy (func_0014EF40).
struct __attribute__((packed)) Keep46 {
    u64 value;
};

struct C46 : C03 {
    s32 state;              // 0x550: func_0014F110 (-1 at set-up, 0 on entering the world)
    f32 stateTime;          // 0x554: the clock when the state changed (D_0026185C)
    C46* next;              // 0x558: the next in the list at D_00262708 (func_00150298)
    u8 pad55C[0x564 - 0x55C];
    f32 f564;               // 0x564: handed to func_00126D60 when the state becomes 5
    f32 delay;              // 0x568: slot 17 waits this long in state 4
    Keep46 keep56C;         // 0x56C: kept by slot 9
    void* f574;             // 0x574: not read here
    void* watched;        // 0x578: the object whose message (kind 6) clears it (slot 13)
    s32 f57C;               // 0x57C: zeroed when the state leaves 2
    s32 f580;               // 0x580
    s32 f584;               // 0x584
    void* taker;          // 0x588: the class 0x23 object that took it (func_0014FEC0; func_0014FBE0)
    void* member58C;        // 0x58C: the group or member func_00159478 finds (slot 10)
};

typedef char check_C46[sizeof(C46) == 0x590 ? 1 : -1];

void func_0014EE40(C46* self);                          // slot 0
void func_0014EF00(C46* self);                          // slot 3
void func_0014EE70(C46* self);                          // slot 6
void func_0014EF40(C46* self, C03* other);              // slot 9
void func_0014EF88(C46* self);                          // slot 10
void func_0014EFB8(C46* self, s32 kind, void* msg);     // slot 13
void func_0014F020(C46* self);                          // slot 16
void func_0014F058(C46* self, f32 dt);                  // slot 17
void func_0014F110(C46* self, s32 state);               // sets the state

#endif

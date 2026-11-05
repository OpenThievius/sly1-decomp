// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x43 (descriptor D_0021D848, 0x5B0 bytes), a direct child of class 0x03: a state
// (0x550) that counts up through eight steps (0x568) as it is hit, then is done at 9. Written
// for this project from what retail's code does (config/us/classes.tsv); one struct.
// Its descriptor has class 0x03's slots (desc03()).
#ifndef HIT_TARGET_H
#define HIT_TARGET_H

#include "c03.h"

// Three floats func_001A7128 reads as a polynomial in time: x + t * (y + t * z).
struct TimePolynomial {
    f32 x, y, z;
};

struct HitTarget : C03 {
    s32 state;  // 0x550: -1 at set-up (func_001A6F88); func_001A7480 sets it
    f32 stateTime;  // 0x554: the time of the last state change
    void* controller;  // 0x558: told when the state leaves 9 (func_001A7480)
    void* partner;  // 0x55C
    void* soundId;  // 0x560: the sound's id (slot 16 starts it with func_001B6290)
    void* soundHandle;  // 0x564: its handle; func_001A7480 changes the sound by state
    s32 hitLimit;  // 0x568: 8 at set-up: the hits the object takes (func_001A72B0)
    f32 recoverDelay;  // 0x56C: 1.0 at set-up (func_001A7420)
    f32 hitInterval;  // 0x570: 0.2 at set-up (the time between two hits)
    void* notifyRecord;  // 0x574: a record set up by slot 10 (func_00159478); its first word
                            //        is the object func_001A72B0 sends a message to
    void* scaledObject;  // 0x578: the object func_001A7128 scales (its 0x2DC and 0x2E0)
    f32 f57C;  // 0x57C: the two floats slot 16 copies from scaledObject's 0x2DC
    f32 f580;  // 0x580
    u8 pad584[0x590 - 0x584];
    TimePolynomial scalePoly;  // 0x590: 1, 0, 0 at set-up
    u8 pad59C[0x5A0 - 0x59C];
    u8 blob5A0[8];  // 0x5A0: kept across slot 9 (func_001A7050)
    u8 pad5A8[0x5B0 - 0x5A8];
};

typedef char check_HitTarget[sizeof(HitTarget) == 0x5B0 ? 1 : -1];

#endif

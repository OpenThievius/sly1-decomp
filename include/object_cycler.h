// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x40 (descriptor D_0021C598, 0x6A0 bytes), a part with collision that moves between
// states (slot 20 and 45 set one, slot 17 steps it) and shows one of up to sixteen objects (or one
// of eight, in mode 1) at a time. Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/file_1549C8.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef OBJECT_CYCLER_H
#define OBJECT_CYCLER_H

#include "transform_object.h"
#include "collider.h"

// Two floats the level data keeps as one doubleword (a range, a pair of times): func_0015AAE0
// sets them from tables of doublewords, func_0015B128 and func_0015AEB0 read each float.
struct __attribute__((packed)) PackedFloatPair {
    u64 v;
};
union FloatRange {
    PackedFloatPair pk;
    struct {
        f32 a;
        f32 b;
    };
};

// 0x40: mode 0 shows one object and keeps a handle at 0x5E4 (func_001BFCD8 makes it), mode 1
// steps through its objects with the timers below. State -1 at set-up; 0, 1, 3, 5 and 6 are
// the ones func_0015B128 and func_0015B4D0 distinguish.
struct ObjectCycler : Collider {
    s32 mode;               // 0x550: 0 or 1
    s32 state;              // 0x554: -1 at set-up
    f32 stateStart;               // 0x558: the time the state started
    f32 stateEnd;               // 0x55C: the time it ends
    s32 startState;               // 0x560: the state slot 16 starts in
    s32 count;              // 0x564: how many objects in objs
    s32 index;              // 0x568: the one shown
    PlacedObject* objs[16];          // 0x56C: found by kind 0x23C + i (func_0015AC08)
    s32 altCount;           // 0x5AC: how many in altObjects
    PlacedObject* altObjects[8];        // 0x5B0: mode 1 only: found by kind 0x24D + i
    PlacedObject* obj5D0;            // 0x5D0
    MemberObject* group;             // 0x5D4: a 0x77 or 0x78 found by func_00159478 (kept by slot 10)
    u8 pad5D8[0x5DC - 0x5D8];
    PackedFloatPair f5DC;              // 0x5DC: kept across the copy by slot 9
    void* handle;           // 0x5E4: made by func_001BFCD8 in mode 0, given back with func_001BF788
    u8 pad5E8[0x5F0 - 0x5E8];
    Vec02 v5F0;             // 0x5F0
    u8 pad600[0x610 - 0x600];
    FloatRange p610;            // 0x610: set up from D_00262180
    FloatRange p618;            // 0x618: D_00262188
    FloatRange p620;            // 0x620: D_00262190
    FloatRange p628;            // 0x628: D_00262198
    s32 swapKind;               // 0x630: the kind (or -1) whose object the shown one is swapped for near the end of a state (mode 1)
    s32 swapIndex;               // 0x634: the index of that object in objs
    f32 swapTail;               // 0x638: the last fraction of a state in which the swapped object is shown
    FloatRange checkDelay;            // 0x63C: D_002621A0; the range func_001EAAE0 picks the delay between checks from
    f32 stepInterval;               // 0x644: seconds between steps of the index (mode 1)
    f32 nextStepTime;               // 0x648: the clock value at which the index steps next
    f32 f64C;               // 0x64C: twice radius3CC
    FloatRange p650;            // 0x650: D_002621A8
    FloatRange p658;            // 0x658: D_002621B0
    FloatRange p660;            // 0x660: D_002621B8
    f32 nextAdvanceTime;               // 0x668: state 6: the clock value at which the index advances next
    f32 f66C;               // 0x66C: the clock when func_0015C0A0 last looked
    FloatRange p670;            // 0x670: D_002621C0
    u8 pad678[0x680 - 0x678];
    f32 f680;               // 0x680
    u8 pad684[0x688 - 0x684];
    f32 nextCheckTime;               // 0x688: mode 1: the clock value of the next func_0015BD48 check
    s32 indexStep;               // 0x68C: 1 at set-up, then 1 or -1: how far each step moves the index
    s32 f690;               // 0x690: -1 at set-up
    u8 pad694[0x6A0 - 0x694];
};

typedef char check_ObjectCycler[sizeof(ObjectCycler) == 0x6A0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
// (Slot 45, func_0015B720, takes a message record only that file knows.)
void InitObjectCycler(ObjectCycler* self);                       // 0x40 slot 0
void CopyObjectCycler(ObjectCycler* self);                       // 0x40 slot 9
void LoadObjectCycler(ObjectCycler* self, void* stream);         // 0x40 slot 10
void StartObjectCycler(ObjectCycler* self);                       // 0x40 slot 16
void UpdateObjectCycler(ObjectCycler* self);                       // 0x40 slot 17
void SetObjectCyclerHandle(ObjectCycler* self, s32 flag);             // 0x40 slot 20
void DrawObjectCycler(ObjectCycler* self, void* a1, void* a2);   // 0x40 slot 37

#endif

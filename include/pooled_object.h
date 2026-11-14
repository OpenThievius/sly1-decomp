// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x46 (descriptor D_0021DBD8, 0x590 bytes): a collision object with a state of its own
// (func_0014F110 sets it; slot 17, func_0014F058, runs it), kept in the world's list at +0x1C78.
// Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef POOLED_OBJECT_H
#define POOLED_OBJECT_H

#include "collider.h"
struct BufferedStream;

// Eight bytes at an odd word offset, which slot 9 keeps across the copy (func_0014EF40).
struct __attribute__((packed)) Keep46 {
    u64 value;
};

struct PooledObject : Collider {
    s32 state;              // 0x550: func_0014F110 (-1 at set-up, 0 on entering the world)
    f32 stateTime;          // 0x554: the clock when the state changed (D_0026185C)
    union {
        PooledObject* next;          // 0x558: the next in the list at D_00262708 (func_00150298)
        f32 holdSpeed;               // 0x558: held, the speed it follows its holder at (func_0014F270)
    };
    u8 pad55C[0x560 - 0x55C];
    f32 f560;               // 0x560: handed to SendPointEventToWorldListener when it lands (func_0014F270)
    f32 f564;               // 0x564: handed to func_00126D60 when the state becomes 5
    f32 delay;              // 0x568: slot 17 waits this long in state 4
    Keep46 keep56C;         // 0x56C: kept by slot 9
    void* f574;             // 0x574: not read here
    void* watched;        // 0x578: the object whose message (kind 6) clears it (slot 13)
    union {
        s32 f57C;           // 0x57C: zeroed when the state leaves 2
        Collider* holder;   // 0x57C: in state 2, the object it follows (func_0014F270)
    };
    s32 f580;               // 0x580
    union {
        s32 f584;           // 0x584
        f32 holdHeight;     // 0x584: in state 2, its height above the holder (func_0014F270)
    };
    void* taker;          // 0x588: the class 0x23 object that took it (func_0014FEC0; func_0014FBE0)
    void* member58C;        // 0x58C: the group or member func_00159478 finds (slot 10)
};

typedef char check_PooledObject[sizeof(PooledObject) == 0x590 ? 1 : -1];

void InitPooledObject(PooledObject* self);                          // slot 0
void AddToWorldQueue(PooledObject* self);                          // slot 3
void RemoveFromWorldQueue(PooledObject* self);                          // slot 6
void CopyPooledObject(PooledObject* self, Collider* other);              // slot 9
void LoadPooledObject(PooledObject* self, BufferedStream* stream);                          // slot 10
void HandlePooledObjectNotification(PooledObject* self, s32 kind, void* msg);     // slot 13
void StartPooledObject(PooledObject* self);                          // slot 16
void UpdatePooledObject(PooledObject* self, f32 dt);                  // slot 17
void SetPooledObjectState(PooledObject* self, s32 state);               // sets the state

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Role: an object with a three-state value (0, 1, 2) that returns to 0 on a message for its id or when state 2 times out (UpdateItemTimeouts), and keeps its keyed entries while in state 2.
// Class 0x62 (descriptor D_0021E658, 0x330 bytes), a placed object that watches for one object
// id. Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef STATE_RESET_OBJECT_H
#define STATE_RESET_OBJECT_H

#include "placed_object.h"

// What func_001EF9C8 reads of the message it is told about (kind 5): the id at 0x08.
struct StateResetMsg {
    s32 f0;
    s32 f4;
    s32 id;                 // 0x08
};

// 0x62: func_001EF838 sets both ids to -1 (none); func_001EF9C8 resets the object when the
// message names the id at 0x2DC.
struct StateResetObject : PlacedObject {
    s32 id2D0;              // 0x2D0: -1 for none
    f32 f2D4;               // 0x2D4
    f32 f2D8;               // 0x2D8: how long state 2 lasts (UpdateItemTimeouts)
    s32 id2DC;              // 0x2DC
    s32 id2E0;              // 0x2E0: -1 for none
    s32 f2E4;               // 0x2E4
    u8 f2E8[1];             // 0x2E8
    u8 pad2E9[0x328 - 0x2E9];
    void* group;            // 0x328: the record of the ones sharing id2E0 (func_001CB8B8), whose timeouts an agent schedules
    u8 pad32C[0x330 - 0x32C];
};

typedef char check_StateResetObject[sizeof(StateResetObject) == 0x330 ? 1 : -1];

struct ItemKeeper;          // include/item_keeper.h

// The 48-byte record of the class 0x62 objects that share an id (StateResetObject::group): CreateRecord2505C0
// makes it, AppendToSmallList and RemoveFromSmallList keep its objects, ScheduleItemTimeouts
// queues UpdateItemTimeouts on it.
struct StateResetGroup {
    void* vtbl;             // 0x00: D_002505C0
    s32 count;              // 0x04
    StateResetObject* items[8];          // 0x08
    s32 scheduled;          // 0x28: UpdateItemTimeouts is queued
    ItemKeeper* owner;      // 0x2C: the keeper that made it (func_001CB8B8)
};

typedef char check_StateResetGroup[sizeof(StateResetGroup) == 0x30 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitStateResetObject(StateResetObject* self);                       // 0x62 slot 0
void HandleStateResetNotification(StateResetObject* self, s32 kind, StateResetMsg* msg); // 0x62 slot 13
void StartStateResetObject(StateResetObject* self);                       // 0x62 slot 16
void UpdateStateResetObject(void);                            // 0x62 slot 17 (empty)

#endif

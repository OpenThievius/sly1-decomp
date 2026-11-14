// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x2F (descriptor D_0021AB08, 0x6C0 bytes): a collision object with three states (0, 1, 2)
// that watches lists of other objects: the ones it keeps (items1), the ones it asks for in
// state 2 (items2), the ones it found and tells (outItems) and a last list of ids (items3).
// Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef STATE_TRIGGER_H
#define STATE_TRIGGER_H

#include "collider.h"

struct TimedObject;     // class 0x30 (timed_object.h)
struct PlayingSound;
struct SoundLevelEntry;
struct StateWalker;     // a handle func_001B6290 makes (s1b6290.h)

struct StateTrigger : Collider {
    s32 state;              // 0x550: func_00123888 (-1 at set-up)
    f32 stateTime;          // 0x554: the clock when the state changed (D_0026185C)
    void* found558;         // 0x558: the first child of kind 0x88 (func_00123448)
    StateWalker* walker;        // 0x55C: a handle func_001B6290 makes for found558
    f32 timeout;            // 0x560: in state 2, how long before the state falls to 0
    s32 count1;             // 0x564: the ids at items1 whose objects (kind 0x22) it keeps
    s32 items1[4];          // 0x568: func_00123C90 appends
    s32 count2;             // 0x578
    s32 items2[16];         // 0x57C: func_00123CB8 appends; objects of kind 0x30 are put in outItems
    s32 outCount;           // 0x5BC
    TimedObject* outItems[16];   // 0x5C0: the objects found (kind 0x30); the state changes tell them
    s32 count3;             // 0x600
    s32 items3[6];          // 0x604: func_00123CE0 appends; objects of kind 8 are told func_001CAD40
    s32 done;               // 0x61C: counted up by func_00123B18; state 1 follows when it equals count1
    PlayingSound* sound;    // 0x620: handed to func_001BF788 when state 2 ends
    SoundLevelEntry* soundLevel; // 0x624: handed to func_001BF048 when state 2 ends
    s32 f628;               // 0x628
    s32 count62C;           // 0x62C: the entries of table630 (func_0013EC00)
    u8 table630[0x6B0 - 0x630];  // 0x630: func_0013ECB0 and func_0013EC00 work on it
    s32 id6B0;              // 0x6B0: an id of the table at D_00261420 (func_00140FF8)
    u8 pad6B4[0x6C0 - 0x6B4];
};

typedef char check_StateTrigger[sizeof(StateTrigger) == 0x6C0 ? 1 : -1];

void InitStateTrigger(StateTrigger* self);                  // slot 0
void CopyStateTrigger(StateTrigger* self, StateTrigger* src);                  // slot 9
void StartStateTrigger(StateTrigger* self);                  // slot 16
void UpdateStateTrigger(StateTrigger* self, f32 dt);                  // slot 17
void ResolveStateTriggerObjects(StateTrigger* self);                  // the callback func_00123448 queues
void SetStateTriggerState(StateTrigger* self, s32 mode);        // sets the state
void SetStateTriggerStateFromMessage(StateTrigger* self, s32 mode);        // sets the state from a message's mode
void CountStateTriggerDone(StateTrigger* self);                  // one more object done
void ResetStateTriggerOutputModes(StateTrigger* self);
void EndStateTriggerOutputs(StateTrigger* self);
void FinishStateTriggerOutputs(StateTrigger* self);
void AddStateTriggerCountedId(StateTrigger* self, s32 value);
void AddStateTriggerItemId(StateTrigger* self, s32 value);
void AddStateTriggerAgentId(StateTrigger* self, s32 value);
s32 TestStateTriggerItemsAccepted(StateTrigger* self, void* arg);

#endif

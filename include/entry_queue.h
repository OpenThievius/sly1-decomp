// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8F (descriptor D_0021B608, 0x6C bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef ENTRY_QUEUE_H
#define ENTRY_QUEUE_H

#include "base_object.h"

struct OnOffObject;     // class 0x63 (on_off_object.h)

// A 0x14-byte entry of the queue's buffer (0x80 of them, AddQueueEntry): its kind, an id, a
// state the queue waits on (0 not done, AdvanceEntryQueue) and one or two values.
struct QueueEntry {
    s32 kind;               // 0x00: 0 .. 0xC (the adders, func_0017CFC8 .. func_0017D220)
    s32 id;                 // 0x04
    s32 state;              // 0x08
    union {
        s32 value;          // 0x0C: kinds 2, 5, 8
        f32 valueF;         // 0x0C: kinds 4, 6, 7, 11
    };
    s32 value10;            // 0x10: kind 5
};

typedef char check_QueueEntry[sizeof(QueueEntry) == 0x14 ? 1 : -1];

// 0x8F: func_0017B998 (slot 0) allocates a 0xA00-byte buffer and sets a flag.
struct EntryQueue : BaseObject {
    s32 entryCount;         // 0x34: the entries in the queue's buffer
    void* buffer;           // 0x38
    void* player;           // 0x3C: the player it drives (func_0017CE20 binds it)
    s32 entryIndex;         // 0x40: the index of the entry being run
    f32 entryStartTime;     // 0x44: a kind 4 entry is done once its value is below minus this
    void* pendingEntry;     // 0x48: a queued entry (func_0017C660 hands it to func_0017C428)
    BaseObject* lastFoundObject; // 0x4C: the object the last entry found, where the next looks from
    void* animationPlayer;  // 0x50: the animation player a queue entry started
    void* aimTarget;        // 0x54: the object func_0017BB78 aims the player at
    OnOffObject* forcedOnOffObject; // 0x58: the on-off object it forces on (ReplaceQueueOnOffObject)
    s32 f5C;                // 0x5C: f58 was not attached, so it was put in its parent's list
    f32 f60;                // 0x60: a kind 6 entry turns the player round when its place is behind this
    f32 f64;                // 0x64: a kind 7 entry waits for the player's f2410 to come within 15 of this
    s32 flag68;             // 0x68
};

typedef char check_EntryQueue[sizeof(EntryQueue) == 0x6C ? 1 : -1];

void InitEntryQueue(EntryQueue* self);   // slot 0

#endif

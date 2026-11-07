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
    s32 f34;                // 0x34
    void* buffer;           // 0x38
    void* f3C;              // 0x3C: the player it drives (func_0017CE20 binds it)
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    void* f48;              // 0x48: a queued entry (func_0017C660 hands it to func_0017C428)
    s32 f4C;                // 0x4C
    void* f50;              // 0x50
    u8 pad54[0x58 - 0x54];
    OnOffObject* f58;       // 0x58: the on-off object it forces on (ReplaceQueueOnOffObject)
    s32 f5C;                // 0x5C: f58 was not attached, so it was put in its parent's list
    u8 pad60[0x68 - 0x60];
    s32 flag68;             // 0x68
};

typedef char check_EntryQueue[sizeof(EntryQueue) == 0x6C ? 1 : -1];

void func_0017B998(EntryQueue* self);   // slot 0

#endif

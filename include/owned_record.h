// SPDX-License-Identifier: AGPL-3.0-or-later
// A record an owner object (WorldListedObject, list at +0x624) keeps: the 0x10C0-byte record AcquireOwnedRecord (func_00139C70) takes from the world's pool at World+0x1B40
// (func_001B5EA0) and clears (func_001F5C0C, 0x10C0 bytes): it keeps a 0x580-byte record from the
// pool at +0x1B4C and its owner. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g1340; Rec_158F80 there is another pool's 0x70-byte record).
#ifndef OWNED_RECORD_H
#define OWNED_RECORD_H

#include "common.h"

struct OwnedRecord {
    u8 pad0000[0x1088];
    void* extraRecord;      // 0x1088: the 0x580-byte record (pool World+0x1B4C), cleared too
    void* owner;            // 0x108C: the object that keeps the record (func_00139C70's first argument)
    u8 pad1090[0x10C0 - 0x1090];
};

typedef char check_OwnedRecord[sizeof(OwnedRecord) == 0x10C0 ? 1 : -1];

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x28 (descriptor D_002190B0, 0x890 bytes): a collision trigger. A zone record at +0x554
// (Zone28: the objects that set it off, a mode, a clock) and four lists of ids and kinds that
// say which objects count (func_0013F718); mode 4 is the last, then the state follows
// (slot 17, func_0013FD20). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef TRIGGER_ZONE_H
#define TRIGGER_ZONE_H

#include "collider.h"
struct BufferedStream;

// Up to sixteen values, counted (func_0013E8F8 appends).
struct Queue28 {
    s32 count;              // 0x00
    s32 values[16];         // 0x04
};

// The objects queued for one side of the zone (func_0013E8D8 appends, func_0013EDC8 runs them).
struct ObjectQueue28 {
    s32 count;              // 0x00
    BaseObject* values[16]; // 0x04
};

// The ids one side of the zone has seen and the objects queued for it.
struct Pair28 {
    Queue28 seen;           // 0x00: func_0013E868 looks an object up in it
    ObjectQueue28 queued;   // 0x44: func_0013E8D8 appends
};

// The zone record (0x1CC bytes) the zone classes embed, at +0x554 in 0x28 (and +0x5C0 in the
// class that func_00140100 loads): its helpers take the record's address.
struct Zone28 {
    u8 pad00[4];
    Collider* owner;             // 0x04: the object it is in (func_0013E950)
    Pair28 pairs[2];        // 0x08, 0x90
    f32 seekTime;           // 0x118: the time handed to func_0012C8F8 (func_0013ED90)
    s32 persistent;         // 0x11C
    s32 id120;              // 0x120: an index of the table at D_00261420 (func_00140FF8)
    f32 stamp;              // 0x124: the clock when the mode changed (D_0026185C)
    f32 duration;           // 0x128
    s32 mode;               // 0x12C: func_0013EB68 changes it
    u8 pad130[4];
    s32 silent;             // 0x134
    s32 reversed;           // 0x138: non-zero reverses the direction (func_0013ED90)
    s32 staysActive;        // 0x13C
    s32 sequenceId;         // 0x140: -1 at set-up
    u8 pad144[4];
    s32 count148;           // 0x148: the entries of table14C (func_0013EC00)
    u8 table14C[0x80];      // 0x14C
};

struct __attribute__((aligned(16))) Quad28 {
    s32 a, b, c, d;
};

// A 0x30-byte entry the second kind of hit uses (func_0013F940 measures it).
struct Entry28 {
    u8 pad0[0x30];
};

struct TriggerZone : Collider {
    s32 state;              // 0x550: 0 and 1 test the hit, 2 and 4 end it, 3 waits (func_0013FD20)
    Zone28 zone;            // 0x554
    s32 countIdsIn;         // 0x720: ids an object must have, if any (func_0013F718); func_001406B0 appends
    s32 idsIn[8];           // 0x724
    s32 countIdsOut;        // 0x744: ids it must not have; func_001406D0 appends
    s32 idsOut[8];          // 0x748
    s32 countKindsIn;       // 0x768: kinds it must be, if any; func_001406F0 appends
    s32 kindsIn[8];         // 0x76C
    s32 countKindsOut;      // 0x78C: kinds it must not be; func_00140710 appends
    s32 kindsOut[8];        // 0x790
    s32 chosenIndex;        // 0x7B0: the entry chosen
    s32 quadCount;          // 0x7B4: the number of quads
    u8 pad7B8[0x7C0 - 0x7B8];
    union {
        Quad28 quads[8];    // 0x7C0: state 0's records (func_0013F140 inserts)
        struct {
            u8 pad7C0[0x7E0 - 0x7C0];
            s32 count7E0;   // 0x7E0: state 1's entries
            u8 pad7E4[0x7F0 - 0x7E4];
            Entry28 entries[2];     // 0x7F0: rotations (func_0013F290 reads the last one's rows)
        };
    };
    Vec02 v850;             // 0x850: state 1: the up axis picked by the zone's facing, times 100 (func_0013F290)
    Vec02 v860;             // 0x860: state 0: the unit line through the quads; state 1: a row of the last
                            //        rotation (func_0013F290); negated so that it faces away from v870
    Vec02 v870;             // 0x870: state 0: -v860; state 1: the next row (func_0013F290)
    s32 markerNode;         // 0x880: compared with the world's object at +0x2204 (func_0013FD20)
    u8 pad884[0x890 - 0x884];
};

typedef char check_Zone28[sizeof(Zone28) == 0x1CC ? 1 : -1];
typedef char check_TriggerZone[sizeof(TriggerZone) == 0x890 ? 1 : -1];

void InitTriggerZone(TriggerZone* self);                          // slot 0
void CopyTriggerZone(TriggerZone* self, TriggerZone* src);                          // slot 9
void LoadTriggerZone(TriggerZone* self, BufferedStream* stream);                          // slot 10
void StepTriggerZone(TriggerZone* self, f32 t);                   // slot 28
void UpdateTriggerZone(TriggerZone* self, f32 dt);                          // slot 17
s32 HandleTriggerZoneEvent(TriggerZone* self, void* event);              // slot 48 (m30)

#endif

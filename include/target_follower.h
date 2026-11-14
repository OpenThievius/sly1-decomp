// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x47 (descriptor D_0021F188, 0x5E0 bytes): a collision object that keeps a path of
// records it loads at +0x550, a list of the class 0x2A objects (include/c29.h) at +0x55C, and a
// few tuning values (+0x5B0). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef TARGET_FOLLOWER_H
#define TARGET_FOLLOWER_H

#include "collider.h"
#include "sound_level.h"
struct BufferedStream;

struct FollowableObject;

// The 0x14-byte entries of the records at +0x550 (func_0016CE80 looks for the one whose two
// ends have the ids 0x2EF and 0x2F0 and reads a float at +0x34 of the object its first word
// points to).
struct Ref47 {
    u8 pad00[0x34];
    f32 f34;                // 0x34
};

struct Entry47 {
    Ref47* ref;             // 0x00
    s32 a;                  // 0x04
    s32 b;                  // 0x08
    u8 pad0C[0x14 - 0x0C];
};

struct List47 {
    u8 pad0[0x38];
    u32 f38;                // 0x38
    s32 count;              // 0x3C
    Entry47* items;         // 0x40
};

// A record func_0015A838 finds; a field of it is passed to the player's code (+0x44).
struct Sub47 {
    u8 pad00[0x44];
    s32 f44;                // 0x44
};

// A message (type 0x13) carries a code: 0x2FD, 0x2FE, 0x2FF and 0x300 start the player's steps.
struct Packet47 {
    u8 pad00[8];
    s32 code;               // 0x08
};

// The three values slot 0 sets (25.0, 0, 0.25).
struct Tune47 {
    f32 a;                  // 0x00
    s32 b;                  // 0x04
    f32 c;                  // 0x08
};

struct TargetFollower : Collider {
    List47* list550;        // 0x550: loaded (table D_002629D0, id 0x2EE)
    void* stateWalker;      // 0x554: func_001B6290(list550, self, -1, 1)
    FollowableObject* followedObject;    // 0x558: the class 0x2A object it follows (func_0016D3F0)
    List01 list55C;         // 0x55C: the 0x2A objects, linked at their +0x7B0 (slot 0, func_0016DFE0)
    void* f568;             // 0x568: loaded (id 0x2F7)
    f32 heightOffset;       // 0x56C: the object's z less that of f568
    Sub47* launchPool;      // 0x570: the kind-0x8C child (slot 16)
    f32 nextLaunchTime;     // 0x574: a time (func_0016DAC0, mode 1)
    s32 followedObjectId;   // 0x578: -1 at set-up
    s32 f57C;               // 0x57C: loaded (id 0x2F8)
    s32 f580;               // 0x580: loaded (id 0x2F9)
    s32 f584;               // 0x584: loaded (id 0x2FA)
    s32 f588;               // 0x588: loaded (id 0x2FB)
    s32 f58C;               // 0x58C: loaded (id 0x2FC)
    void* lookTarget;       // 0x590: the object it looks at (func_0016DAC0, mode 3)
    void* trailObject;      // 0x594: func_0011E580(0x73, ...)
    s32 mode;               // 0x598: -1 at set-up
    f32 modeStartTime;      // 0x59C: the clock's time when the mode changed (func_0016DAC0)
    f32 heading;            // 0x5A0: read by slot 28 (func_00188850)
    f32 leadTime;           // 0x5A4: slot 10 reads it from f550's entry
    f32 phaseOneEndTime;    // 0x5A8: FLT_MAX in mode 0
    f32 arrivalTime;        // 0x5AC
    union {
        u8 sub5B0[0x28];    // 0x5B0: handed whole to func_001B9D10 by slot 28
        struct {
            Tune47 tune5B0; // 0x5B0
            SoundLevelEntry* soundLevel; // 0x5BC
            s32 voiceEnabled; // 0x5C0
            f32 f5C4;       // 0x5C4: 3000.0 at set-up
            f32 f5C8;       // 0x5C8: 1000.0 at set-up
            s32 voicePending; // 0x5CC
            void* lastTune; // 0x5D0
            s32 trailCountdown; // 0x5D4
        };
    };
    s32 stepHalted;         // 0x5D8: slot 28 does nothing more when it is set
    u8 pad5DC[0x5E0 - 0x5DC];
};

typedef char check_TargetFollower[sizeof(TargetFollower) == 0x5E0 ? 1 : -1];

void InitTargetFollower(TargetFollower* self);                          // slot 0
void LoadTargetFollowerRecords(TargetFollower* self, BufferedStream* stream);                          // slot 10
void HandleTargetFollowerNotification(TargetFollower* self, s32 type, Packet47* packet);  // slot 13
void ResolveTargetFollowerLinks(TargetFollower* self);                          // slot 16
void StepTargetFollower(TargetFollower* self, f32 t);                   // slot 28

#endif

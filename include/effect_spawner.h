// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x50 (descriptor 0x350 bytes, parent 0x02), an object that owns a 0x200-byte record
// (+0x2D0) shared with its copies and resolves the objects its ids name after loading. Written
// for this project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. Class 0x4D's slot 23 also copies class 0x02's float at 0x80
// (include/c02.h) from it.
#ifndef EFFECT_SPAWNER_H
#define EFFECT_SPAWNER_H

#include "placed_object.h"
#include "path_curve.h"
#include "transform_object.h"
#include "shapes.h"   // Quad16
struct BufferedStream;

// Two floats a random value is taken between (func_001EAAE0), copied as one unaligned doubleword.
struct ParticleRange {
    f32 lo;
    f32 hi;
};

struct RecordMember;   // transform_object.h

// The record the object points to (func_00154F98 makes it, func_00155778 makes it the object's
// own before a change, func_001550E8 fills it from the ids).
struct __attribute__((aligned(16))) EffectSpawnerRecord {
    s32 uses;               // 0x00: objects sharing it
    u8 pad04[0x10 - 0x04];
    s32 kind;               // 0x10: 3, 4 seen
    u8 pad14[0x20 - 0x14];
    union {
        struct {
            union {
                PathCurve* curve20;     // 0x20: the key-frame curve found by index (func_00154F98)
                s32 value20;        // 0x20: a value taken from another object (func_001550E8)
            };
            void* links;            // 0x24: the kind 3 link records
            u8 pad28[0x40 - 0x28];
        };
        Vec4 point20;      // 0x20: a point (PlaceEffectAtSource)
        f32 box20[8];       // 0x20: kind 1's box: two corners (WrapSpawnerParticlesIntoBox)
    };
    u8 pad40[0x78 - 0x40];
    void* frame;            // 0x78: a frame the record's points are placed in (GenerateSpawnSetupPair)
    void* target;           // 0x7C
    s32 secondVelocityMode; // 0x80: how the second end of a setup pair takes its velocity (1, 2 or 3)
    u8 pad84[0x110 - 0x84];
    Quad16 q110;            // 0x110: copied to the start of each effect it makes (SpawnRecordEffects)
    s32 effectMode;         // 0x120: 1 when the record spawns individual effects
    u8 pad124[0x130 - 0x124];
    union {
        struct {
            s32 f130;               // 0x130
            u8 pad134[0x178 - 0x134];
            s32 randomSecondFrame;  // 0x178: set, each particle gets a random second frame
            u8 pad17C[0x188 - 0x17C];
            s32 f188;               // 0x188
        };
        CappedWordList words130;    // 0x130: the ids the record reads from the stream
    };
    RecordMember* member;   // 0x18C: the member object the record belongs to (its rec at 0x90 is this record)
    u8 pad190[0x198 - 0x190];
    s32 skipCameraFacing;   // 0x198: clear, a particle's second frame turns toward the camera (EmitParticleChunk)
    ParticleRange range19C;       // 0x19C: the range of a particle's second frame
    s32 randomTurn;         // 0x1A4: set, each particle gets a random turn
    u8 pad1A8[0x1B0 - 0x1A8];
    s32 effectKind;         // 0x1B0: -1 or a value; set, starting the spawner sets f120 (func_00155270)
    u8 pad1B4[0x1C0 - 0x1B4];
    f32 poly1C0[3];         // 0x1C0: a quadratic (AimEffectAtNearestObject)
    u8 pad1CC[0x1D8 - 0x1CC];
    void* found[3];         // 0x1D8: objects named by the ids
    u8 pad1E4[0x1E8 - 0x1E4];
    f32 boundsMargin;       // 0x1E8
    u8 pad1EC[0x1F0 - 0x1EC];
    union {
        f32 f1F0f;          // 0x1F0: kind 24's first parameter
        s32 f1F0;           // 0x1F0: an effect's i124 takes it (func_001A22C8, func_001A2D30), an object id (func_001A39C8)
    };
    union {
        s32 i1F4;           // 0x1F4: an effect's i120 (func_001A2D30)
        f32 f1F4;           // 0x1F4: an effect's rate (func_001A39C8)
    };
    f32 f1F8;               // 0x1F8: kind 24's third parameter
    u8 pad1FC[0x200 - 0x1FC];
};

typedef char check_Rec50[sizeof(EffectSpawnerRecord) == 0x200 ? 1 : -1];

struct EffectSpawner : PlacedObject {
    EffectSpawnerRecord* rec;             // 0x2D0
    s32 mode;               // 0x2D4: -1 at setup; the mode, 0 to 3, chosen when it starts (func_00155270)
    s32 remaining;          // 0x2D8: -1 at setup
    union {
        struct {
            f32 delayMin;   // 0x2DC: 10.0 at setup
            f32 delayMax;   // 0x2E0: 10.0 at setup
        };
        ParticleRange delay;      // 0x2DC: where the first delay is taken from
    };
    s32 scaleByVolume;      // 0x2E4: set, the volume of the record's box scales the rate
    f32 chance;             // 0x2E8: the chance it starts active
    ParticleRange active;         // 0x2EC: how long it then stays active
    f32 targetCount;        // 0x2F4
    union {
        s64 key2F8;         // 0x2F8: the two ids, tested together against -1
        s32 id2F8[2];       // 0x2F8, 0x2FC
    };
    s32 id300;              // 0x300
    s32 id304;              // 0x304
    s32 continuous;         // 0x308: set, the spawner stays active forever
    s32 id30C;              // 0x30C
    s32 sharedId;           // 0x310: -1 at setup
    u8 list314[0x10];       // 0x314: initialised with func_00152438
    u8 pad324[0x328 - 0x324];
    f32 rate;               // 0x328: a random delay (func_00155270)
    f32 rateInterval;       // 0x32C
    f32 nextRateTime;       // 0x330
    f32 volumeScale;        // 0x334: 1.0, or the volume of the record's box scaled
    f32 margin;             // 0x338: half the side of the box around the target its points wrap in (func_00155868)
    f32 spawnRemainder;     // 0x33C: the fraction of a spawn carried to the next frame (func_00155AB0)
    f32 activeUntil;        // 0x340: -1.0 at setup
    BaseObject* held344;           // 0x344: objects it must let go of when told (slot 13)
    BaseObject* held348;           // 0x348
    s32 changed;            // 0x34C
};

typedef char check_EffectSpawner[sizeof(EffectSpawner) == 0x350 ? 1 : -1];

void InitEffectSpawner(EffectSpawner* self);                       // slot 0
void CopyEffectSpawner(EffectSpawner* self, EffectSpawner* src);                       // slot 9
void LoadEffectSpawner(EffectSpawner* self, BufferedStream* stream);            // slot 10
void ReleaseEffectSpawnerHeld(EffectSpawner* self, s32 mode, BaseObject* p);     // slot 13
void ResolveEffectSpawnerLinks(EffectSpawner* self);                       // slot 15

#endif

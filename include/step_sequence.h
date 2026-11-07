// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x65 (descriptor D_0021A490, 0x340 bytes), a placed object (under 0x02) that runs a
// list of steps (docs/DISC.md, "Events"): func_00150528 loads the common block, then the step
// list (func_00150570 reads the count and the steps into 0x2DC and 0x2E0). A small state
// machine (func_00150AE8, every frame) moves it between idle, waiting, playing and finished.
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its methods also use the base classes' fields (include/c01.h, include/c02.h): the id at
// 0x08 and the flags word at 0x2C8.
#ifndef STEP_SEQUENCE_H
#define STEP_SEQUENCE_H

#include "placed_object.h"

struct StepSequence;
struct AnimationPlayer;  // an animation's player (t2195.h)

// The entry func_001925F0 returns; its slot at 0x154 gives the state of the controls.
struct Ent65;
struct VtEnt65 {
    u8 pad[0x154];
    void (*f154)(void* o, StepSequence* self, s32* q);
    void (*f158)(Ent65* o, void* value);    // 0x158: shows a step's text (func_00151860)
};
struct Ent65 { VtEnt65* vt; };

// A step (0x28 bytes): func_00150570 reads `type` and then, by type, the words after it
// (0 and 7: an optional block at +4; 1, 2: two shorts; 3: two floats, two bytes, a string at
// +0x14 and four shorts; 4: a short). func_001516C0 plays them; func_00151300 looks ahead.
struct SequenceStep {
    s32 type;               // 0x00
    s32 w4;                 // 0x04
    s32 w8;                 // 0x08
    s32 wC;                 // 0x0C
    s32 w10;                // 0x10
    s32 w14[1];             // 0x14
    s32 w18;                // 0x18
    s32 w1C;                // 0x1C
    s32 w20;                // 0x20
    s32 w24;                // 0x24
};

typedef char check_SequenceStep[sizeof(SequenceStep) == 0x28 ? 1 : -1];

struct StepSequence : PlacedObject {
    s32 mode2D0;            // 0x2D0: 1 and 2 are set by func_00150750 and func_00150760
    s32 state2D4;           // 0x2D4: the state machine's state (0 to 6)
    f32 time2D8;            // 0x2D8: when the state was entered
    s32 count2DC;           // 0x2DC: number of steps (written by func_00150570)
    void* steps2E0;         // 0x2E0: the steps (written by func_00150570)
    s32 step2E4;            // 0x2E4: the step being played
    s32 f2E8;               // 0x2E8
    s32 f2EC;               // 0x2EC
    union {
        s32 f2F0;           // 0x2F0: compared with D_002708E0's +0x270 (func_00151300)
        void* p2F0;         // 0x2F0: an object found by id (func_00150DC0)
    };
    union {
        s32 f2F4;           // 0x2F4: compared with D_00271558's +0x270 (func_00151300)
        void* p2F4;         // 0x2F4: another (func_00150DC0)
    };
    union {
        u32 value2F8;       // 0x2F8: cleared when message 6 brings it back (func_001512A8)
        AnimationPlayer* player2F8;  // 0x2F8: the player func_0012E760 ends (func_00150DC0 reads its animation)
    };
    f32 f2FC;               // 0x2FC
    s32 second300;          // 0x300: -1 at load
    void* target304;        // 0x304: object found for id 30C, else the default at 0x308
    u8 fallback308[4];      // 0x308
    s32 first30C;           // 0x30C: -1 at load; then set from the id at +0x08
    s32 f310;               // 0x310
    void* f314[4];          // 0x314
    s32 f324;               // 0x324
    s32 f328;               // 0x328
    s32 f32C;               // 0x32C
    s32 f330;               // 0x330
    u8 pad334[0x340 - 0x334];
};

typedef char check_StepSequence[sizeof(StepSequence) == 0x340 ? 1 : -1];

void func_001504E0(StepSequence* self);                          // 0x65 slot 0
void func_00150528(StepSequence* self, void* arg);               // 0x65 slot 10
void func_001512A8(StepSequence* self, u32 mode, u32 value);     // 0x65 slot 13
void func_001506F0(StepSequence* self);                          // 0x65 slot 16
void func_00150AE8(StepSequence* self);                          // 0x65 slot 17

#endif

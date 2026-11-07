// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x83 (descriptor D_00219738, 0xB0 bytes), an animation, and class 0x84 (0xD0) under it.
// Written for this project from what retail's code does (config/us/classes.tsv, docs/DISC.md
// "Animations").
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the
// pads keep every field at its retail offset. Fields are named for what the code does with
// them; step 6 of the roadmap may rename them.
#ifndef ANIMATION_H
#define ANIMATION_H

#include "base_object.h"
#include "anim_curve.h"

struct Stream83;  // the level stream an animation is read from (func_00137D10 and friends)

// A track (28 bytes, func_0012B8C8): the target and one curve for each property the flags
// select (position 0x1, rotation 0x2, scale 0x4, weight 0x8), and the morph channels (0x10).
// The curves are kind t2196 (anim_curve.h); slot 1 (slot 2 of the rotation curves) reads each from
// the stream.
struct Track83 {
    s32 target;             // 0x00
    PositionCurve* pos;         // 0x04
    RotationCurve* rot;         // 0x08
    ScaleCurve* scale;     // 0x0C
    WeightCurve* weight;   // 0x10
    s32 morphCount;         // 0x14
    WeightCurve** morph;   // 0x18
};

// A value that moves with a speed and an acceleration (func_0012C160 steps it by the frame time).
struct Kin83 {
    f32 pos;                // 0x00
    f32 vel;                // 0x04
    f32 acc;                // 0x08
};

// 0x83: an animation. func_0012B8C8 reads it: the object id, the length in seconds, the target
// ids, the tracks and the three event lists (counts and records at 0x54..0x68).
struct Animation : BaseObject {
    f32 length;             // 0x34: seconds (the stream's 1/60 s count times 1/60)
    s32 trackCount;         // 0x38
    Track83* tracks;        // 0x3C
    s32 id;                 // 0x40
    s32 f44;                // 0x44
    s32 enabled;            // 0x48: func_0012C160 queues its callback while set
    s32 f4C;                // 0x4C
    s32 f50;                // 0x50
    s32 startCount;         // 0x54: the list that runs when it starts
    s32 startList;          // 0x58
    s32 timedCount;         // 0x5C: the timed list
    s32 timedList;          // 0x60
    s32 endCount;           // 0x64: the list that runs when it ends
    s32 endList;            // 0x68
    u8 props6C[0x80 - 0x6C]; // 0x6C: the property list (func_00152438 sets its element size 0x3C)
    Kin83 kin;              // 0x80
    u8 pad8C[0x90 - 0x8C];
    f32 lo;                 // 0x90
    f32 hi;                 // 0x94
    f32 out;                // 0x98
    Track83* f9C;           // 0x9C: the track func_0012D2A8 moved to the end (func_0012D398 tests it)
    s32 targetCount;        // 0xA0
    s32* targets;           // 0xA4
    u8 padA8[0xB0 - 0xA8];
};

// 0x84: no field of its own is read.
struct C84 : Animation {
    u8 padB0[0xD0 - 0xB0];
};

typedef char check_Animation[sizeof(Animation) == 0xB0 ? 1 : -1];
typedef char check_C84[sizeof(C84) == 0xD0 ? 1 : -1];
typedef char check_Track83[sizeof(Track83) == 0x1C ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0012B870(Animation* self);                      // 0x83 slot 0
void func_0012C140(void);                           // 0x83 slot 9 (the base class's copy)
void func_0012B8C8(Animation* self, Stream83* stream);    // 0x83 slot 10
void func_0012C160(Animation* self);                      // 0x83 slot 16
void func_0012D3F0();                               // 0x84 slot 9 (empty)
void func_0012D3E0();                               // 0x84 slot 10 (empty)
void func_0012D3E8();                               // 0x84 slot 16 (empty)

#endif

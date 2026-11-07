// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5F (descriptor D_0021D4E8, 0x660 bytes), a placed object with a blended pose and a
// small state machine (func_001A4DC0 picks the state, func_001A4C48 acts on it, func_001A4B30
// blends two poses). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset. Fields are named for what the code does with them; the naming
// step may rename them.
#ifndef PAIR_CONTROLLER_H
#define PAIR_CONTROLLER_H

#include "placed_object.h"

struct ObjectCreator;  // the object at 0x358 (object_creator.h; func_001A4C48 reads its state at 0x550)
struct LinkedObject;  // the object at 0x658 (func_001A4C48 reads a state at 0x2D4)

struct __attribute__((aligned(16))) AlignedQuad { f32 a, b, c, d; };

// A value that moves with a speed and an acceleration (func_001A4B30 steps it by the frame time).
struct BlendMotion {
    f32 pos;  // 0x00
    f32 vel;  // 0x04
    f32 acc;  // 0x08
};

// 0x5F: func_001A4718 sets it up (the lists, the ids, the tuning values and two copies of the
// pose table); func_001A4B30 blends the pose at 0x3E0 with the one at 0x4A0 into 0x560.
struct PairController : PlacedObject {
    s32 id2D0;  // 0x2D0: -1 for none
    s32 id2D4;  // 0x2D4
    s32 id2D8;  // 0x2D8
    s32 id2DC;  // 0x2DC
    s32 idCount;  // 0x2E0
    s32 ids[1];  // 0x2E4
    u8 pad2E8[0x340 - 0x2E8];
    s32 mode340;  // 0x340
    f32 tune344;  // 0x344
    f32 tune348;  // 0x348
    f32 tune34C;  // 0x34C
    f32 tune350;  // 0x350
    void* f354;  // 0x354
    ObjectCreator* target;  // 0x358
    u8 list35C[0x368 - 0x35C];  // lists (func_00152438 sets their element size)
    u8 list368[0x374 - 0x368];
    u8 list374[0x380 - 0x374];
    s32 count380;  // 0x380: paired objects out; at limit624 a removal schedules the next start (f62C to f630 later, at f634)
    u8 list384[0x390 - 0x384];
    u8 list390[0x39C - 0x390];
    s32 count39C;  // 0x39C: attachments out; at f628 a removal schedules the next (f638 to f63C later, at f640)
    u8 list3A0[0x3AC - 0x3A0];
    u8 list3AC[0x3B8 - 0x3AC];
    s32 limit3B8;  // 0x3B8: 0x28 after setup
    s32 count3BC;  // 0x3BC
    s32 f3C0;  // 0x3C0
    s32 f3C4;  // 0x3C4
    u8 pad3C8[0x3D0 - 0x3C8];
    union {
        AlignedQuad q3D0;  // 0x3D0: set from D_00275C50
        BlendMotion kin;  // 0x3D0: the blend's weight, speed and acceleration
    };
    f32 poseA[48];  // 0x3E0
    f32 poseB[48];  // 0x4A0
    f32 poseOut[48];  // 0x560
    s32 poseIndex;  // 0x620
    s32 limit624;  // 0x624: the most paired objects out at once
    s32 f628;  // 0x628
    f32 f62C;  // 0x62C: the shortest wait before the next start
    f32 f630;  // 0x630: the longest
    f32 f634;  // 0x634
    f32 f638;  // 0x638
    f32 f63C;  // 0x63C
    f32 f640;  // 0x640
    f32 f644;  // 0x644
    f32 f648;  // 0x648
    s32 id64C;  // 0x64C: -1 for none; the state func_001A4B30 compares
    s32 state;  // 0x650: -1 for none; the state machine's state
    f32 f654;  // 0x654
    LinkedObject* link;  // 0x658
    u8 pad65C[0x660 - 0x65C];
};

typedef char check_PairController[sizeof(PairController) == 0x660 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitPairController(PairController* self);                       // 0x5F slot 0
void BlendPairControllerPose(PairController* self);                       // 0x5F slot 16
void UpdatePairController(PairController* self);                       // 0x5F slot 17
void ShowPairControllerElement(PairController* self);                       // 0x5F slot 46

#endif

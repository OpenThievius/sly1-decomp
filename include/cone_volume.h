// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x51 (ConeVolume) (descriptor 0x620 bytes, parent 0x02), an object with two camera-style tuning
// vectors (+0x320, +0x340) and a state value at +0x304 that slot 9 compares and keeps through
// a copy. Written for this project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. Its set-up also uses class 0x02's flags word at 0x2C8
// (include/c02.h).
#ifndef CONE_VOLUME_H
#define CONE_VOLUME_H

#include "placed_object.h"

#include "shapes.h"   // Quad16

// Eight bytes that slot 9 keeps through the parent's copy; retail moves them unaligned.
struct __attribute__((packed)) ConeVolumeSaved { s32 a; s32 b; };

struct ConeVolume : PlacedObject {
    s32 mode;               // 0x2D0: 0 at setup
    u8 pad2D4[0x2E0 - 0x2D4];
    u32 f2E0[4];            // 0x2E0
    f32 f2F0;               // 0x2F0
    f32 f2F4;               // 0x2F4
    f32 f2f8;               // 0x2F8: 180.0 at setup
    f32 f2fc;               // 0x2FC: 240.0 at setup
    f32 f300;               // 0x300: 180.0 at setup
    s32 value;              // 0x304: compared by slot 9
    u8 pad308[0x320 - 0x308];
    Quad16 q320;            // 0x320: D_00248D20 at setup
    f32 rangeMin;           // 0x330: 200.0 at setup
    f32 rangeMax;           // 0x334: 2000.0 at setup
    f32 outerAngle;         // 0x338: 60.0 at setup
    f32 innerAngle;         // 0x33C
    Quad16 q340;            // 0x340: D_00248D10 at setup
    f32 f350;               // 0x350
    f32 f354;               // 0x354
    f32 f358;               // 0x358
    f32 f35C;               // 0x35C
    f32 f360;               // 0x360
    f32 f364;               // 0x364
    f32 f368;               // 0x368
    f32 f36C;               // 0x36C
    u8 pad370[0x410 - 0x370];
    ConeVolumeSaved saved;  // 0x410: kept through a copy
    u8 pad418[0x620 - 0x418];
};

typedef char check_ConeVolume[sizeof(ConeVolume) == 0x620 ? 1 : -1];

void func_00183CC8(ConeVolume* self);                       // slot 0
void func_00183E40(ConeVolume* self);                       // slot 6
void func_00183E70(ConeVolume* self);                       // slot 7
void func_00183EA0(ConeVolume* self, ConeVolume* other);           // slot 9
void func_00183D88(ConeVolume* self);                       // slot 19

#endif

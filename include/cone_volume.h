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
    s32 shape;              // 0x2D4: 2 with a first level and angle, 1 with a second, else 0 (RefreshConeVolumeShape)
    u8 pad2D8[0x2E0 - 0x2D8];
    union {
        u32 color[4];       // 0x2E0: as words (SetConeVolumeColor)
        Vec02 hsv;          // 0x2E0: hue, saturation and value, 0 to 255 (ConvertHsv255ToRgb255); the value is the first level
    };
    f32 secondLevel;        // 0x2F0: paired with secondAngle
    f32 thirdLevel;         // 0x2F4: paired with 360 less thirdAngle
    f32 firstAngle;         // 0x2F8: 180.0 at setup
    f32 secondAngle;        // 0x2FC: 240.0 at setup
    f32 thirdAngle;         // 0x300: 180.0 at setup
    s32 value;              // 0x304: compared by slot 9
    u8 pad308[0x310 - 0x308];
    Quad16 q310;            // 0x310: the direction SetConeVolumeDirection stores; q320 is its negated unit vector
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
    Vec02 planes[6];        // 0x370: the four sides (func_001443C8), the far and the near plane, each with its distance in w
    s32 mask;               // 0x3D0: the value lists' mask where it is (QueryValueListMask; all 28 bits in mode 0)
    u8 pad3D4[0x3E0 - 0x3D4];
    union {
        Quad16 axis;        // 0x3E0: the cone's axis, scaled by half the range to its middle (func_00184B58)
        Mat02 basis;        // 0x3E0: the frame RefreshConeVolumeShape builds from the direction and the up hint
    };
    ConeVolumeSaved saved;  // 0x410: kept through a copy
    u32 packetSize;         // 0x418: DetachPacketBuffer's count for the packet below
    u8 pad41C[0x420 - 0x41C];
    Quad16 packet[0x20];    // 0x420: the VIF packet RefreshConeVolumeShape writes
};

typedef char check_ConeVolume[sizeof(ConeVolume) == 0x620 ? 1 : -1];

void InitConeVolume(ConeVolume* self);                       // slot 0
void RegisterConeVolume(ConeVolume* self);                       // slot 6
void UnregisterConeVolume(ConeVolume* self);                       // slot 7
void CopyConeVolume(ConeVolume* self, ConeVolume* other);           // slot 9
void RefreshConeVolume(ConeVolume* self);                       // slot 19

#endif

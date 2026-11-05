// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x68 (descriptor 0x6A0 bytes, parent 0x02), the manager of a menu-like screen: a count
// and a table of 0x14-byte slots (+0x2E0), a device object (+0x42C), a timer, two parameter
// sets and their blend. Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef GAUGE_MANAGER_H
#define GAUGE_MANAGER_H

#include "c02.h"

struct GaugePair {
    f32 a;
    f32 b;
    void Set(f32 x, f32 y)
    {
        a = x;
        b = y;
    }
};

// One set of 44 words (0xB0 bytes); the constructor copies D_00249F00 into both.
struct __attribute__((aligned(16))) GaugeParams {
    s32 w[0x11];
    GaugePair p44;
    GaugePair p4C;
    s32 rest[0x17];
};

struct Timer68 {
    s32 state;
    f32 scale;
    s32 count;
    void Init()
    {
        state = 0;
        scale = 1.0f;
        count = 0;
    }
};

// The table at +0x2E0: an object, two things found from it, a key (func_0014CF30 clears the
// key of a slot whose object goes away).
struct GaugeSlot {
    void* obj;              // 0x00
    void* f4;               // 0x04
    void* f8;               // 0x08
    void* key;              // 0x0C
    u8 pad10[4];
};

struct GaugeManager : C02 {
    s32 amount;             // 0x2D0
    s32 maxAmount;          // 0x2D4: 50 at setup
    f32 f2D8;               // 0x2D8: 90.0 at setup
    s32 slotCount;          // 0x2DC: slots in use
    GaugeSlot slots[16];       // 0x2E0
    u8 pad420[0x424 - 0x420];
    void* f424;             // 0x424
    void* f428;             // 0x428
    void* device;           // 0x42C: the device object (func_001B6290 makes it)
    union {
        s32 tag430;         // 0x430: what func_001B6598 reads from the device
        u8 buf430[0x1C];
    };
    s32 f44C;               // 0x44C
    s32 f450;               // 0x450: 2 at setup
    s32 f454;               // 0x454
    u8 pad458[0x45C - 0x458];
    f32 f45C;               // 0x45C: the largest float at setup (D_00249FB0)
    f32 f460;               // 0x460
    s32 f464;               // 0x464: 0 at setup
    u8 pad468[0x470 - 0x468];
    union {
        Timer68 timer;      // 0x470
        f32 poly[3];        // 0x470: coefficients (func_0014C138)
    };
    u8 pad47C[0x480 - 0x47C];
    GaugeParams params0;       // 0x480
    GaugeParams params1;       // 0x530
    f32 o5E0[44];           // 0x5E0: the blend of the two sets (func_0014C138)
    s32 setIndex;           // 0x690
    u8 pad694[0x6A0 - 0x694];
};

typedef char check_GaugeManager[sizeof(GaugeManager) == 0x6A0 ? 1 : -1];

void func_0014C018(GaugeManager* self);                       // slot 0
void func_0014CF30(GaugeManager* self, s32 kind, void* key);  // slot 13
void func_0014C138(GaugeManager* self);                       // slot 16
void func_0014C6E0(GaugeManager* self);                       // slot 17
void func_0014C788(GaugeManager* self);                       // slot 46

#endif

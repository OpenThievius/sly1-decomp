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

#include "placed_object.h"

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
// key of a slot whose object goes away; func_0014CBA8 starts an animation player into it).
// func_0014CBA8 hands a free slot to the pool's chosen agent (NumberedAgent::slot), which
// clears `taken` when it is done with it (func_0014BD38, func_0014BF88 through ContactAgent::slot).
struct GaugeSlot {
    union {
        s32 id;             // 0x00: the object's id, until PostLoad finds it
        BaseObject* obj;    // 0x00
    };
    void* anchor;           // 0x04: the object whose position and rotation the agent takes
    void* animation;        // 0x08
    void* key;              // 0x0C
    s32 taken;              // 0x10: an agent holds the slot
};

struct GaugeManager : PlacedObject {
    s32 amount;             // 0x2D0
    s32 maxAmount;          // 0x2D4: 50 at setup
    f32 timerSeconds;       // 0x2D8: 90.0 at setup
    s32 slotCount;          // 0x2DC: slots in use
    GaugeSlot slots[16];       // 0x2E0
    void* contactPool;      // 0x420: a pool of agents (func_0014C858 takes the next one)
    void* slotPool;         // 0x424
    void* deviceGraph;      // 0x428
    void* device;           // 0x42C: the device object (func_001B6290 makes it)
    union {
        s32 tag430;         // 0x430: what func_001B6598 reads from the device
        u8 buf430[0x1C];
        struct {
            u8 pad430[0xC];
            f32 waitMin;    // 0x43C: func_0014CD70 waits a random time between this
            f32 waitMax;    // 0x440  and this
            u8 pad444[0x448 - 0x444];
            f32 speed448;   // 0x448: the animation speed class 0x11 sets (func_0014BD38)
        };
    };
    s32 maxSlotAgents;      // 0x44C
    s32 maxContactAgents;   // 0x450: 2 at setup
    s32 slotAgents;         // 0x454
    s32 contactAgents;      // 0x458: lowered by each contact (func_0014CD70)
    f32 nextContactTime;    // 0x45C: the largest float at setup (D_00249FB0)
    f32 nextSlotTime;       // 0x460
    s32 contactsStarted;    // 0x464: 0 at setup
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

void InitGaugeManager(GaugeManager* self);                       // slot 0
void HandleGaugeManagerNotification(GaugeManager* self, s32 kind, void* key);  // slot 13
void BlendParamSets(GaugeManager* self);                       // slot 16
void UpdateGaugeManager(GaugeManager* self, f32 dt);                       // slot 17
void ShowGaugeManagerDisplays(GaugeManager* self);                       // slot 46

#endif

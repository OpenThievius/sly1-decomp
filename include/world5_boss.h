// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4A (descriptor D_002206F8, 0x620 bytes), a gauge mode object: an object with collision
// that switches between modes (SetWorld5BossMode sets the mode, takes or gives up the
// world's gauge object and starts the handle it keeps for modes 0 and 1), shows or hides the
// gauge bar by its mode (ShowWorld5BossBar) and hands out three handles it makes when it
// starts (StartWorld5Boss). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/world5_boss.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef WORLD5_BOSS_H
#define WORLD5_BOSS_H

#include "collider.h"

// One weight of a group func_00139038 combines: 12 bytes each.
struct BlendWeight3 {
    f32 w;                  // 0x00
    u8 pad04[8];
};

struct World5Boss : Collider {
    s32 mode;               // 0x550: -1 at set-up; SetWorld5BossMode sets it
    f32 modeTime;           // 0x554: the clock when the mode was set
    u8 modePlayer[4];       // 0x558: the mode's player (ReplaceAnimationPlayer)
    union {
        struct {
            u8 grpA[0x24];  // 0x55C: the first group of func_00139038 (StartWorld5Boss)
            f32 fA;         // 0x580: 1.0
            u8 pad584[0x58C - 0x584];
        };
        BlendWeight3 wA[4]; // 0x55C: its four weights (func_0017AF38)
    };
    void* mode0Handle;      // 0x58C: the handle mode 0 starts
    union {
        struct {
            f32 fB;         // 0x590: 1.0, the second group
            u8 padB[0x5C0 - 0x594];
        };
        BlendWeight3 wB[4]; // 0x590: its four weights
    };
    void* mode1Handle;      // 0x5C0: the handle mode 1 starts
    union {
        struct {
            f32 fC;         // 0x5C4: 1.0, the third group
            u8 padC[0x600 - 0x5C8];
        };
        BlendWeight3 wC[5]; // 0x5C4: its five weights
    };
    void* loopHandle;       // 0x600: the handle PlayWorld5BossLoop starts
    u8 loopPlayer[4];       // 0x604: its player (ReplaceAnimationPlayer)
    s32 f608;               // 0x608: compared with a message's id by HandleWorld5BossEvent
    void* target;           // 0x60C: the object SetWorld5BossTarget finds
    u8 targetPlayer[0x620 - 0x610]; // 0x610: its player (PlayWorld5BossTarget)
};

typedef char check_World5Boss[sizeof(World5Boss) == 0x620 ? 1 : -1];

#endif

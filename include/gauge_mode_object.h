// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4A (descriptor D_002206F8, 0x620 bytes), a gauge mode object: an object with collision
// that switches between modes (SetGaugeModeObjectMode sets the mode, takes or gives up the
// world's gauge object and starts the handle it keeps for modes 0 and 1), shows or hides the
// gauge bar by its mode (ShowGaugeModeObjectBar) and hands out three handles it makes when it
// starts (StartGaugeModeObject). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/file_1793C0.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef GAUGE_MODE_OBJECT_H
#define GAUGE_MODE_OBJECT_H

#include "collider.h"

struct GaugeModeObject : Collider {
    s32 mode;               // 0x550: -1 at set-up; SetGaugeModeObjectMode sets it
    f32 modeTime;           // 0x554: the clock when the mode was set
    u8 modePlayer[4];       // 0x558: the mode's player (ReplaceAnimationPlayer)
    u8 grpA[0x24];          // 0x55C: the first group of func_00139038 (StartGaugeModeObject)
    f32 fA;                 // 0x580: 1.0
    u8 pad584[0x58C - 0x584];
    void* mode0Handle;      // 0x58C: the handle mode 0 starts
    f32 fB;                 // 0x590: 1.0, the second group
    u8 padB[0x5C0 - 0x594];
    void* mode1Handle;      // 0x5C0: the handle mode 1 starts
    f32 fC;                 // 0x5C4: 1.0, the third group
    u8 padC[0x600 - 0x5C8];
    void* loopHandle;       // 0x600: the handle PlayGaugeModeObjectLoop starts
    u8 loopPlayer[4];       // 0x604: its player (ReplaceAnimationPlayer)
    s32 f608;               // 0x608: compared with a message's id by HandleGaugeModeObjectEvent
    void* target;           // 0x60C: the object SetGaugeModeObjectTarget finds
    u8 targetPlayer[0x620 - 0x610]; // 0x610: its player (PlayGaugeModeObjectTarget)
};

typedef char check_GaugeModeObject[sizeof(GaugeModeObject) == 0x620 ? 1 : -1];

#endif

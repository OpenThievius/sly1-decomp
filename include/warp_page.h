// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x67 (descriptor D_00221020, 0x570 bytes), a placed object: a warp page, a screen of
// eleven entries with a cursor moved between them (MoveWarpCursor) and a mode that opens,
// shows and closes it (SetWarpPageMode). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef WARP_PAGE_H
#define WARP_PAGE_H

#include "placed_object.h"
#include "shapes.h"

// One of the page's eleven entries; PostLoadWarpPage clears two values and draws a phase and a
// speed at random from a range.
struct WarpEntry {
    void* f00;              // 0x00
    void* f04;              // 0x04: an object func_001F1050 starts with weight f08
    f32 f08;                // 0x08
    void* f0C;              // 0x0C: another, with weight f10
    f32 f10;                // 0x10
    s32 f14;                // 0x14
    s32 f18;                // 0x18
    s32 reachable;          // 0x1C: IsWarpEntryReachable's answer; MoveWarpCursor skips the entry while it is 0
    s32 f20;                // 0x20
    f32 f24;                // 0x24
    f32 f28;                // 0x28
    f32 phase;              // 0x2C: 0 to 2 pi at random
    f32 speed;              // 0x30: 0.5 to 0.7 at random
};

// 0x67: HandleWarpPageNotification reacts to a message by mode (1, 3 or 4), StartWarpPage enters
// the page in the table of the pages (slot by id), PostLoadWarpPage sets up the entries.
struct WarpPage : PlacedObject {
    s32 mode;               // 0x2D0
    f32 modeTime;           // 0x2D4: the clock when SetWarpPageMode last entered a mode
    s32 f2D8;               // 0x2D8: SetWarpPageMode (cursor, or -1)
    s32 cursor;             // 0x2DC: the entry under the cursor
    s32 f2E0;               // 0x2E0
    void* f2E4;             // 0x2E4
    void* f2E8;             // 0x2E8
    s32 f2EC;               // 0x2EC
    void* f2F0;             // 0x2F0: its address goes to func_0012C918 (func_001F1050)
    s32 slot;               // 0x2F4: 1..5 by id, else the value in the global block at +0x19D8
    WarpEntry entries[11];  // 0x2F8
    s32 selected;           // 0x534: the selected entry (-1 for none, SetWarpPageSelectedEntry)
    u8 pad538[0x540 - 0x538];
    Quad16 q540;            // 0x540: q550 copied whole by SetWarpPageMode
    Quad16 q550;            // 0x550
    s32 f560;               // 0x560
    void* sound;            // 0x564: the page's sound (StartSoundEffect, StopSoundRecord)
    u8 pad568[0x570 - 0x568];
};

typedef char check_WarpPage[sizeof(WarpPage) == 0x570 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F0F70(WarpPage* self, s32 kind, void* msg);  // 0x67 slot 13
void func_001F0758(WarpPage* self);                       // 0x67 slot 15
void func_001F0660(WarpPage* self);                       // 0x67 slot 16
void func_001F0EB8(WarpPage* self, u8* s, void* c);       // 0x67 slot 36

#endif

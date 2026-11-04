// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x65 (descriptor D_0021A490, 0x340 bytes), a placed object (under 0x02) that runs a
// list of steps (docs/DISC.md, "Events"): func_00150528 loads the common block, then the step
// list (func_00150570 reads the count and the steps into 0x2DC and 0x2E0). A small state
// machine (func_00150AE8, every frame) moves it between idle, waiting, playing and finished.
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Fields in the base classes that its methods read are reached through the object's address,
// as before (NOTES.md proposes them for include/c01.h and include/c02.h): the flags word
// at 0x2C8 and the id at 0x08.
#ifndef C65_H
#define C65_H

#include "c02.h"

struct C65;

// The entry func_001925F0 returns; its slot at 0x154 gives the state of the controls.
struct Ent65;
struct VtEnt65 {
    u8 pad[0x154];
    void (*f154)(void* o, C65* self, s32* q);
};
struct Ent65 { VtEnt65* vt; };

struct C65 : C02 {
    s32 mode2D0;            // 0x2D0: 1 and 2 are set by func_00150750 and func_00150760
    s32 state2D4;           // 0x2D4: the state machine's state (0 to 6)
    f32 time2D8;            // 0x2D8: when the state was entered
    s32 count2DC;           // 0x2DC: number of steps (written by func_00150570)
    void* steps2E0;         // 0x2E0: the steps (written by func_00150570)
    s32 step2E4;            // 0x2E4: the step being played
    u8 pad2E8[0x2F8 - 0x2E8];
    u32 value2F8;           // 0x2F8: cleared when message 6 brings it back (func_001512A8)
    u8 pad2FC[0x300 - 0x2FC];
    s32 second300;          // 0x300: -1 at load
    void* target304;        // 0x304: object found for id 30C, else the default at 0x308
    u8 fallback308[4];      // 0x308
    s32 first30C;           // 0x30C: -1 at load; then set from the id at +0x08
    u8 pad310[0x324 - 0x310];
    s32 f324;               // 0x324
    s32 f328;               // 0x328
    u8 pad32C[0x340 - 0x32C];
};

typedef char check_C65[sizeof(C65) == 0x340 ? 1 : -1];

void func_001504E0(C65* self);                          // 0x65 slot 0
void func_00150528(C65* self, void* arg);               // 0x65 slot 10
void func_001512A8(C65* self, u32 mode, u32 value);     // 0x65 slot 13
void func_001506F0(C65* self);                          // 0x65 slot 16
void func_00150AE8(C65* self);                          // 0x65 slot 17

#endif

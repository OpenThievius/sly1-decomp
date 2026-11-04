// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x63 (descriptor D_002188A0, 0x470 bytes), a placed object (under 0x02) that is either
// on or off (a state at 0x394, set by func_001E2778) and draws a shape from a stream-loaded
// record. Written for this project from what retail's code does (config/us/classes.tsv).
//
// Fields in the base classes that its methods read are reached through the object's address,
// as before (NOTES.md proposes them for include/c02.h): the flags word at 0x2C8, and the two
// vectors the loader reads at 0xD0 and 0x100.
#ifndef C63_H
#define C63_H

#include "c02.h"

// The 0x90 bytes at 0x2F0, copied from the table at D_00275980 at construction.
struct __attribute__((aligned(16))) Block63 {
    u8 d[0x90];
};

struct __attribute__((aligned(16))) Quad63 {
    u8 d[0x10];
};

struct __attribute__((packed)) Pack63 {
    u64 v;
};

// A list of floats the loader finds by index (func_0014D9A8): its count and its values.
struct Arr63 { u8 pad0[0xC]; s32 count; u8 pad1[4]; f32* data; };

struct C63 : C02 {
    void* f2D0;             // 0x2D0
    u8 pad2D4[0x2E4 - 0x2D4];
    Arr63* obj;             // 0x2E4: the list the stream names, or 0
    u8 pad2E8[0x2F0 - 0x2E8];
    Block63 block2F0;       // 0x2F0
    u8 pad380[0x398 - 0x380];
    s32 f398;               // 0x398: -1 at construction
    u8 pad39C[0x3F0 - 0x39C];
    f32 f3F0;               // 0x3F0: the list's last value, or 0
    u8 pad3F4[0x414 - 0x3F4];
    s32 i414;               // 0x414: 7 with a list, 5 without
    u8 pad418[0x420 - 0x418];
    f32 f420;               // 0x420
    f32 f424;               // 0x424
    f32 f428;               // 0x428
    f32 f42C;               // 0x42C
    s32 f430;               // 0x430: -1 at construction
    u8 pad434[0x450 - 0x434];
    Quad63 quad450;         // 0x450
    Pack63 pack460;         // 0x460
    u8 pad468[0x470 - 0x468];
};

typedef char check_C63[sizeof(C63) == 0x470 ? 1 : -1];

void func_001E2520(C63* self);                  // 0x63 slot 0
void func_001E25F8(C63* self);                  // 0x63 slot 7
void func_001E2648(C63* self, void* stream);    // 0x63 slot 10
void func_001E2758(C63* self);                  // 0x63 slot 16
void func_001E2940(C63* self);                  // 0x63 slot 17
void func_001E29A8(C63* self, void* p);         // 0x63 slot 20
void func_001E2988(void);                       // 0x63 slot 37 (calls the common slot)

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x47 (descriptor D_0021F188, 0x5E0 bytes): a collision object that keeps a path of
// records it loads at +0x550, a list of the class 0x2A objects (include/c29.h) at +0x55C, and a
// few tuning values (+0x5B0). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef C47_H
#define C47_H

#include "c03.h"

struct C2A;
struct Obj_1BF0D8;

// The 0x14-byte entries of the records at +0x550 (func_0016CE80 looks for the one whose two
// ends have the ids 0x2EF and 0x2F0 and reads a float at +0x34 of the object its first word
// points to).
struct Ref47 {
    u8 pad00[0x34];
    f32 f34;                // 0x34
};

struct Entry47 {
    Ref47* ref;             // 0x00
    s32 a;                  // 0x04
    s32 b;                  // 0x08
    u8 pad0C[0x14 - 0x0C];
};

struct List47 {
    u8 pad0[0x38];
    u32 f38;                // 0x38
    s32 count;              // 0x3C
    Entry47* items;         // 0x40
};

// A record func_0015A838 finds; a field of it is passed to the player's code (+0x44).
struct Sub47 {
    u8 pad00[0x44];
    s32 f44;                // 0x44
};

// A message (type 0x13) carries a code: 0x2FD, 0x2FE, 0x2FF and 0x300 start the player's steps.
struct Packet47 {
    u8 pad00[8];
    s32 code;               // 0x08
};

// The three values slot 0 sets (25.0, 0, 0.25).
struct Tune47 {
    f32 a;                  // 0x00
    s32 b;                  // 0x04
    f32 c;                  // 0x08
};

struct C47 : C03 {
    List47* list550;        // 0x550: loaded (table D_002629D0, id 0x2EE)
    void* f554;             // 0x554: func_001B6290(list550, self, -1, 1)
    C2A* f558;              // 0x558: the class 0x2A object it follows (func_0016D3F0)
    List01 list55C;         // 0x55C: the 0x2A objects, linked at their +0x7B0 (slot 0, func_0016DFE0)
    void* f568;             // 0x568: loaded (id 0x2F7)
    f32 f56C;               // 0x56C: the object's z less that of f568
    Sub47* f570;            // 0x570: the kind-0x8C child (slot 16)
    u8 pad574[0x578 - 0x574];
    s32 f578;               // 0x578: -1 at set-up
    s32 f57C;               // 0x57C: loaded (id 0x2F8)
    s32 f580;               // 0x580: loaded (id 0x2F9)
    s32 f584;               // 0x584: loaded (id 0x2FA)
    s32 f588;               // 0x588: loaded (id 0x2FB)
    s32 f58C;               // 0x58C: loaded (id 0x2FC)
    u8 pad590[0x594 - 0x590];
    void* f594;             // 0x594: func_0011E580(0x73, ...)
    s32 f598;               // 0x598: -1 at set-up
    u8 pad59C[0x5A0 - 0x59C];
    f32 f5A0;               // 0x5A0: read by slot 28 (func_00188850)
    f32 f5A4;               // 0x5A4: slot 10 reads it from f550's entry
    u8 pad5A8[0x5B0 - 0x5A8];
    union {
        u8 sub5B0[0x28];    // 0x5B0: handed whole to func_001B9D10 by slot 28
        struct {
            Tune47 tune5B0; // 0x5B0
            Obj_1BF0D8* f5BC;   // 0x5BC
            s32 f5C0;       // 0x5C0
            f32 f5C4;       // 0x5C4: 3000.0 at set-up
            f32 f5C8;       // 0x5C8: 1000.0 at set-up
            s32 f5CC;       // 0x5CC
            void* f5D0;     // 0x5D0
            s32 f5D4;       // 0x5D4
        };
    };
    s32 w5D8;               // 0x5D8: slot 28 does nothing more when it is set
    u8 pad5DC[0x5E0 - 0x5DC];
};

typedef char check_C47[sizeof(C47) == 0x5E0 ? 1 : -1];

void func_0016CE00(C47* self);                          // slot 0
void func_0016CE80(C47* self);                          // slot 10
void func_0016DA00(C47* self, s32 type, Packet47* packet);  // slot 13
void func_0016CF70(C47* self);                          // slot 16
void func_0016D0C0(C47* self, f32 t);                   // slot 28

#endif

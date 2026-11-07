// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8B (descriptor D_0021A7B8, 0x3F0 bytes), a child of the root: an object read from a
// level stream (func_0019C470) that is made of a grid of positions, a list of points on it, and
// triangles linked to their neighbours; after loading (func_0019C728) it finds its
// objects, fills a table of 24 slots, and measures it. Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// The slots are 0x20 bytes each from 0xE4; the stream's 24 ids land in their last word
// (0xF0, stride 0x20), so the loader's own fields (0xA0..0xE0) end where the first slot starts.
#ifndef C8B_H
#define C8B_H

#include "base_object.h"

#include "shapes.h"   // Quad16

struct Node8B;
typedef void (*VFn8B)(Node8B* n);
struct Node8B { VFn8B* vtbl; };

struct Tri8B { u8* a; u8* b; u8* c; };
struct Edge8B { u8* a; u8* b; };
struct Rec8B { s32 id; u8 pos[96]; };

// An entry of a Gr8B's table at +0x3C (0x1C bytes each, f38 of them), found by object id
// (FindEntryByObjectId, func_0012CCE8): the id, an object whose first method moves a body
// (func_001C8C08), and a record whose flag at 0x18 func_00139B38 sets.
struct Mover8B;
typedef void (*MoveFn8B)(Mover8B* m, void* body, f32 x, f32 y, s32 z, void* out, s32 w);
struct Mover8B { MoveFn8B* vtbl; };
struct Flagged8B { u8 pad[0x18]; s32 flag; };
struct Entry8B {
    s32 key;                // 0x00: the object id func_0012CCE8 matches
    Mover8B* mover;         // 0x04
    Flagged8B* sub;         // 0x08
    u8 pad0C[0x1C - 0x0C];
};

struct Fl8B { u8 pad[8]; f32 f8; };
struct In8B { u8 pad[8]; Fl8B* p8; };
struct Gr8B {
    u8 pad0[0x34];
    f32 f34;                // 0x34
    s32 f38;                // 0x38
    u8* f3C;                // 0x3C
    u8 pad40[0x6C - 0x40];
    void* f6C;              // 0x6C
    u8 pad70[0x78 - 0x70];
    s32 f78;                // 0x78
    u8 pad7C[0xB8 - 0x7C];
    void* fB8;              // 0xB8
    s32 fBC;                // 0xBC
    In8B* pC0;              // 0xC0
};

struct Slot8B {
    u8 pad0[4];
    Node8B* n4;             // 0x04: the object named by the id
    u8 pad8[4];
    s32 fC;                 // 0x0C: the id read from the stream
    u8 pad10[0x10];
};

struct C8B : BaseObject {
    s32 first34;            // 0x34: -1 at construction
    s32 second38;           // 0x38: -1 at construction
    void* f3C;              // 0x3C
    void* f40;              // 0x40
    u8 pad44[0x48 - 0x44];
    s32 f48;                // 0x48: grid size, read from the stream
    u8 pad4C[0x50 - 0x4C];
    s32 f50;                // 0x50
    f32 f54;                // 0x54
    f32 f58;                // 0x58
    f32 f5C;                // 0x5C
    f32 f60;                // 0x60
    u8 pad64[0x70 - 0x64];
    Quad16 q70;             // 0x70
    s32 f80;                // 0x80
    f32 f84;                // 0x84
    f32 f88;                // 0x88
    f32 f8C;                // 0x8C
    Quad16 q90;             // 0x90
    u8 fA0[4];              // 0xA0: read by func_00137FB0 (the field after it, fA4, is a count)
    s32 fA4;                // 0xA4
    u8 padA8[8];
    u8* fB0;                // 0xB0
    u8 padB4[0xC4 - 0xB4];
    Rec8B* fC4;             // 0xC4: fA4 records of 100 bytes
    s32 fC8;                // 0xC8
    u8* fCC;                // 0xCC: fC8 records of 16 bytes
    s32 fD0;                // 0xD0
    s32 fD4;                // 0xD4
    Tri8B* fD8;             // 0xD8
    Edge8B* fDC;            // 0xDC
    f32 fE0;                // 0xE0
    Slot8B slots[24];       // 0xE4
    Gr8B* f3E4;             // 0x3E4
    u8 pad3E8[0x3F0 - 0x3E8];
};

typedef char check_C8B[sizeof(C8B) == 0x3F0 ? 1 : -1];

void func_0019C440(C8B* self);                  // 0x8B slot 0
// func_0019C470 (slot 10) takes the level stream the source file declares.
void func_0019C728(C8B* self);                  // 0x8B slot 16

#endif

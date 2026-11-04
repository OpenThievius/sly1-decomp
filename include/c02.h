// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x02 (descriptor D_00217498, 0x2D0 bytes), the parent of every placed object: what its
// load method 0x1289C0 reads is the common block of docs/DISC.md ("Objects"). Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// The fields are the ones the class's own methods (src/main/00120000.cpp, 00124000.cpp,
// 00128000.cpp, file_15F678.cpp) and the families under it read. Records only the class points
// to, which its readers see in different shapes, stay `void*` until their own types exist.
#ifndef C02_H
#define C02_H

#include "c01.h"

struct C02;

// A 16-byte vector (a position, a velocity, a matrix row), 16-aligned as the code moves it.
struct __attribute__((aligned(16))) Vec02 {
    f32 x, y, z, w;
};

// Three rows: the placement matrix of the common block (+0xD0) and the two like it.
struct Mat02 {
    Vec02 r[3];
};

// A link (next, previous) kept as one unaligned doubleword by slot 9 (func_00127048).
struct __attribute__((packed)) Link02 {
    u32 next;
    u32 prev;
};

// An entry of the list at +0x2C4: an object id slot 16 (func_00124A48) resolves and starts.
struct Key02 {
    s32 key;        // 0x00
    Key02* next;    // 0x04
};

// An element of the list at +0x280 (func_00146298, func_0012AA50, func_001B11A0): its kind,
// then the values those readers take of kinds 1 and 6.
struct Elem02 {
    u8 pad00[0x08];
    s32 kind;               // 0x08: func_0012AA50 takes kind 6, func_0012AAE8 kind 5, func_001B11A0 kind 1
    u8 pad0C[0x14 - 0x0C];
    s32 f14;                // 0x14: func_001B11A0 takes the first kind 1 with it set
    u8 pad18[0x2C - 0x18];
    f32 x;                  // 0x2C: func_00146298 (kind 6)
    f32 y;                  // 0x30
};

// Class 0x02's descriptor: the root's slots, then twenty more (slot n at 0x10 + 4n).
struct Desc02 : Desc01 {
    void (*m1C)(C02* self);                         // 0x80: func_00125438
    void (*m1D)(C02* self, Vec02* pos);             // 0x84: set the position (func_001273F0)
    void (*m1E)(C02* self, Mat02* rot);             // 0x88: set the matrix (func_00127478)
    void (*m1F)(C02* self, C02* other);             // 0x8C: take other's frame (func_001276C0)
    void (*m20)(C02* self, Vec02* v);               // 0x90: func_001274F8
    void (*m21)(C02* self, Vec02* v);               // 0x94: func_00127590
    void* m22;                                      // 0x98: func_00122550
    void* m23;                                      // 0x9C: func_001225D0
    void (*m24)(C02* self, void* a, void* b);       // 0xA0: func_00125C90
    void (*m25)(C02* self, void* a, void* m);       // 0xA4: func_001261C0
    void (*m26)(C02* self, void* a, void* m);       // 0xA8: func_00126270
    void (*m27)(C02* self, void* frame);            // 0xAC: func_001660E8
    void* m28;                                      // 0xB0
    void* m29;                                      // 0xB4: func_00128E88
    void (*m2A)(C02* self, void* out);              // 0xB8: func_00128FD0
    void (*m2B)(C02* self);                         // 0xBC: func_00129780
    void (*m2C)(C02* self);                         // 0xC0: func_001660A0
    s32 (*m2D)(C02* self, void* other);             // 0xC4: func_0012B2E8
    void* m2E;                                      // 0xC8
    void (*m2F)(C02* self, s32 state);              // 0xCC: set the state (class 0x55: func_00147AB0)
};

struct C02 : C01 {
    List01 children;        // 0x34: the child objects, linked at C01::next (offset 0x1C)
    Link02 link40;          // 0x40
    Link02 link48;          // 0x48
    C02* root;              // 0x50: the topmost object above it (itself at the top)
    void* f54;              // 0x54: given back with func_0015F710 by slot 7
    Link02 link58;          // 0x58: the link in list60
    List01 list60;          // 0x60: offset 0x58
    s32 count6C;            // 0x6C
    C02* items70[4];        // 0x70: count6C of them
    f32 f80;                // 0x80: FLT_MAX at set-up
    f32 f84;                // 0x84: FLT_MAX at set-up
    s32 f88;                // 0x88: 0x0FFFFFFF at set-up
    u8 pad8C[0x90 - 0x8C];
    s32 save90;             // 0x90: C03::mode450 kept by func_001BD790
    s32 save94;             // 0x94: C03::mode470 kept by func_001BD790
    u8 pad98[0xA0 - 0x98];
    Vec02 vA0;              // 0xA0: v150 kept by slot 20
    Vec02 vB0;              // 0xB0: v160 kept by slot 20
    u64 savedC0;            // 0xC0: bits 0, 1: C03::flags538 bits 54, 55 kept by func_001BD790
    u8 padC8[0xD0 - 0xC8];
    Mat02 rot;              // 0xD0: the placement matrix (the common block)
    Vec02 pos;              // 0x100: the position (the common block; slot 29)
    Mat02 m110;             // 0x110
    Vec02 v140;             // 0x140
    Vec02 v150;             // 0x150: slot 32
    Vec02 v160;             // 0x160: slot 33
    u8 pad170[0x190 - 0x170];
    Vec02 v190;             // 0x190
    Mat02 m1A0;             // 0x1A0
    Vec02 v1D0;             // 0x1D0
    List01 list1E0;         // 0x1E0: offset 8
    void* f1EC;             // 0x1EC
    void* f1F0;             // 0x1F0
    void* f1F4;             // 0x1F4
    void** f1F8;            // 0x1F8: f26C entries
    void* f1FC;             // 0x1FC
    void* f200;             // 0x200
    void* f204;             // 0x204
    u8 pad208[0x20C - 0x208];
    u8* p20C;               // 0x20C: D_00260E70 until slot 9 copies it
    u8* p210;               // 0x210: D_00260E80
    u8* p214;               // 0x214: D_00260E90
    u8* p218;               // 0x218: D_00260EA0
    u8* p21C;               // 0x21C: D_00260EB0
    u8* p220;               // 0x220: D_00260EC0
    void* f224;             // 0x224: a 0xC0-byte record
    s32 tries;              // 0x228: as Actor6C::tries; func_0013DC38 tests it, func_00129DF8 clears the root's
    u8 sub22C[0x26C - 0x22C];   // 0x22C: a record func_00165728/165828/165920/165FE0 work on
    s32 f26C;               // 0x26C: the number of f1F8 entries
    u8 pad270[0x278 - 0x270];
    s32 f278;               // 0x278: func_001EECE0 calls slot 50 while it is set
    s32 elemCount;          // 0x27C
    Elem02** elems;         // 0x280: elemCount of them
    void* f284;             // 0x284: a 0x2E0-byte record in the world's list at 0x1C00
    void* f288;             // 0x288: a 0x40-byte record
    u8 pad28C[0x294 - 0x28C];
    s32 f294;               // 0x294: in the world's list at 0x78 instead of 0x54
    void* f298;             // 0x298
    s32 f29C;               // 0x29C
    void* f2A0;             // 0x2A0
    u8 pad2A4[0x2A8 - 0x2A4];
    f32 f2A8;               // 0x2A8
    void* f2AC;             // 0x2AC: a 0x24-byte record
    u8 tint[4];             // 0x2B0: four bytes, set to 0x10 by func_00146340
    u8 pad2B4[0x2C4 - 0x2B4];
    Key02* keys;            // 0x2C4: slot 16 resolves each and empties the list
    union {
        u64 flags;          // 0x2C8
        struct {
            u8 b2C8;        // 0x2C8
            s8 b2C9;        // 0x2C9: -1 at set-up
            s8 b2CA;        // 0x2CA: -1 at set-up
            u64 bits24 : 2; // set-up: 1 with a parent, 2 without
            u64 bits26 : 2; // set-up: 0 with a parent, 2 without
            u64 bits28 : 2; // func_00196410
        };
        struct {
            u32 flagsLo;    // 0x2C8
            u32 flagsHi;    // 0x2CC: bits 32 up, read as a word (func_001AFAF8, func_001B0BE0)
        };
    };

    const Desc02* desc02() const { return (const Desc02*)desc; }
};

typedef char check_C02[sizeof(C02) == 0x2D0 ? 1 : -1];
typedef char check_Desc02[sizeof(Desc02) == 0xD0 ? 1 : -1];

#endif

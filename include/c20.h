// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x20 (descriptor D_00218970, 0x6C0 bytes) and the classes under it: 0x21 (0x22, 0x23,
// 0x24) and 0x25 (0x26). A collision object with a queue of commands (+0x550), a mask of the
// objects it reacts to (+0x63C, with the lists it names) and a flag it sets while it is busy
// (+0x678). Written for this project from what retail's code does (config/us/classes.tsv); one
// struct per class, named by class id until the naming step, each derived from its parent's.
#ifndef C20_H
#define C20_H

#include "c03.h"

// The object at the 0x200 field of what C23 keeps at 0x734: a flag at 0x1C and one at 0x4C.
struct Held23 {
    void** vtbl;            // 0x00
    u8 pad04[0x1C - 4];
    s32 f1C;                // 0x1C
    u8 pad20[0x4C - 0x20];
    s32 f4C;                // 0x4C
};

struct C20;
struct C2F;
struct C05;
struct C46;

// An entry of the queue at 0x554 (func_0013D868 and its siblings append {kind, value}; the
// callback func_0013CE80 fills `node` with the object it found for `key`).
struct Slot20 {
    s32 kind;               // 0x00: 0 to 4
    s32 key;                // 0x04
    s32 node;               // 0x08
};

// Class 0x20's descriptor: 0x03's slots, then two more (slot n at 0x10 + 4n).
struct Desc20 : Desc03 {
    void (*m48)(C20* self);                         // 0x130: slot 72 (func_0013D278)
    void* m49;                                      // 0x134: slot 73
};

struct C20 : C03 {
    s32 count550;           // 0x550: entries of slots
    Slot20 slots[16];       // 0x554: func_0013D868, 0013D8B0, 0013D900, 0013D950 append (kind 0, 1, 2, 3)
    s32 f614;               // 0x614: a key for func_0015A418, -1 at set-up
    s32 f618;               // 0x618: the object it found (slot 10, func_00159478 when f614 is -1)
    u8 pad61C[0x624 - 0x61C];
    f32 f624;               // 0x624: 1.0 at set-up
    f32 f628;               // 0x628: 0.8 at set-up
    f32 f62C;               // 0x62C: 1.2 at set-up
    u8 pad630[0x63C - 0x630];
    s32 mask;               // 0x63C: which objects func_0013DB28 accepts: 0 any, bit 0 the player, bit 1 those in the lists, bit 2 those flagged 0x20
    s32 count640;           // 0x640
    void* list644[4];       // 0x644: func_0013DA48 appends (sets bit 1 of mask)
    s32 count654;           // 0x654
    void* list658[4];       // 0x658: func_0013DA80 appends
    s32 count668;           // 0x668
    void* list66C[3];       // 0x66C: func_0013DAB8 appends
    s32 f678;               // 0x678: busy; slot 17 clears it and calls slot 72
    u8 pad67C[0x680 - 0x67C];
    s32 hold;               // 0x680: func_0013D820 (an id of the table at D_00261420 is kept at 0x688)
    u8 pad684[0x688 - 0x684];
    s32 id688;              // 0x688: func_00140FF8 at set-up; slot 9 keeps it
    s32 f68C;               // 0x68C: 1 at set-up
    u8 pad690[0x698 - 0x690];
    s32 f698;               // 0x698: -1 in class 0x21
    u8 pad69C[0x6B4 - 0x69C];
    void* f6B4;             // 0x6B4: a block of 0x24 bytes (slot 9 copies it; func_0013DAF0 makes it)
    u8 pad6B8[0x6C0 - 0x6B8];

    const Desc20* desc20() const { return (const Desc20*)desc; }
};

typedef char check_C20[sizeof(C20) == 0x6C0 ? 1 : -1];
typedef char check_Desc20[sizeof(Desc20) == 0x138 ? 1 : -1];

struct C21 : C20 {
};

typedef char check_C21[sizeof(C21) == 0x6C0 ? 1 : -1];

struct C22 : C21 {
    C2F* counter;           // 0x6C0: told when the object is done (func_00123B18)
    u8 pad6C4[0x6D0 - 0x6C4];
};

typedef char check_C22[sizeof(C22) == 0x6D0 ? 1 : -1];

struct C23 : C21 {
    s32 f6C0;               // 0x6C0: -1 at set-up; the kind of object slot 16 looks up
    s32 cnt;                // 0x6C4
    C01* p6C8;              // 0x6C8: slot 72 lets go of it
    C46* p6CC;              // 0x6CC: the object of class 0x46 it holds while its state is 5 (func_0014FEC0)
    f32 f6D0;               // 0x6D0: how long before func_0014FEC0 is tried again
    u8 pad6D4[0x6D8 - 0x6D4];
    f32 f6D8;               // 0x6D8: the clock when func_0014FEC0 took the object
    s32 f6DC;               // 0x6DC
    C46* p6E0;              // 0x6E0
    u8 pad6E4[0x6F0 - 0x6E4];
    Vec02 q6F0[4];          // 0x6F0
    C01* f730;              // 0x730
    C02* p734;              // 0x734
    C02* p738;              // 0x738
    void* p73C;             // 0x73C
    void* p740;             // 0x740
    s32 count744;           // 0x744
    void* items748[8];      // 0x748
    s32 count768;           // 0x768
    void* items76C[8];      // 0x76C
    s32 f78C;               // 0x78C
    u8 pad790[0x7B0 - 0x790];
    s32 f7B0;               // 0x7B0
    u8 pad7B4[0x7C0 - 0x7B4];
};

typedef char check_C23[sizeof(C23) == 0x7C0 ? 1 : -1];

struct Alloc24 {
    u8 pad0[8];
    s32 field8;             // 0x08
    void* field_c;          // 0x0C
};

struct C24 : C21 {
    u8 pad6C0[4];
    void* x6C4;             // 0x6C4: loaded (D_00264230)
    void* x6C8;             // 0x6C8
    f32 f6CC;               // 0x6CC
    s32 f6D0;               // 0x6D0
    f32 f6D4;               // 0x6D4
    f32 f6D8;               // 0x6D8
    f32 f6DC;               // 0x6DC
    f32 f6E0;               // 0x6E0
    u8 pad6E4[0x6E8 - 0x6E4];
    Alloc24* x6E8;          // 0x6E8
    void* x6EC;             // 0x6EC: loaded (D_00264230)
};

typedef char check_C24[sizeof(C24) == 0x6F0 ? 1 : -1];

struct C25 : C20 {
    f32 scale;              // 0x6C0
    s32 sel6C4;             // 0x6C4: -1 at set-up
    s32 sel6C8;             // 0x6C8: -1 at set-up
    s32 cur;                // 0x6CC
};

typedef char check_C25[sizeof(C25) == 0x6D0 ? 1 : -1];

struct C26 : C25 {
    void* f6D0;             // 0x6D0
    C05* sel6D4;            // 0x6D4
    u8 pad6D8[0x6E0 - 0x6D8];
};

typedef char check_C26[sizeof(C26) == 0x6E0 ? 1 : -1];

#endif

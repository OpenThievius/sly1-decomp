// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x05 (descriptor D_00217C30, 0x610 bytes) and the 24 classes under it: 0x06 (0x07,
// 0x08 with 0x09..0x13, 0x14), 0x15, 0x16, 0x17, 0x18, 0x19 (0x1A), 0x1B, 0x1C, 0x1D. Written
// for this project from what retail's code does (config/us/classes.tsv); one struct per class,
// named by class id until the naming step, each derived from its parent's with its fields at
// their retail offsets. Fields are named by offset where no reader shows more.
#ifndef SWITCHED_COLLIDER_H
#define SWITCHED_COLLIDER_H

#include "collider.h"

struct SwitchedCollider;
struct TurningCollider;
struct Player;
struct Agent;
struct OnOffObject;     // an object of class 0x63 (c63.h)
struct StateWalker; // a handle func_001B6290 makes (s1b6290.h)
struct AnimationPlayer;  // an animation's player (t2195.h)

// 0x80 bytes at 0x580 of class 0x05, which class 0x17's slot 72 copies as one block.
struct Blk05 {
    Vec02 q[8];
};

// Records of class 0x08: the targets at 0x758 and 0x870 (an id and the object it resolves
// to), the id groups at 0x7E8, the entries at 0xA7C.
struct Slot08 {
    s32 id;                 // 0x00
    void* obj;              // 0x04
};

struct Group08 {
    s32 ids[4];             // 0x00
};

struct Elem08 {
    s32 key;                // 0x00
    void* obj;              // 0x04
    s32 f08;                // 0x08
};

// An entry of class 0x1C's list at 0x634: a direction (0..3) and the time it is due.
struct Ent1C {
    s32 dir;                // 0x00
    f32 t;                  // 0x04
};

// A 0x100-byte record class 0x07 keeps twice (0x1190, 0x1290), one per object it holds.
struct Part07 {
    u8 pad00[0x50];
    s32 f50;                // 0x50: cleared by func_00172530 when the object is missing
    u8 pad54[0x100 - 0x54];
};

// One of class 0x17's six groups at 0x658: count keys, the n objects they resolve to (slot 16),
// and the one picked at random.
struct Ent17 {
    s32 count;              // 0x00
    s32 keys[4];            // 0x04
    s32 n;                  // 0x14
    void* list[4];          // 0x18
    s32 pick;               // 0x28
};

// A message class 0x07's slot 75 keeps (+0x26B4): its kind, an argument, and a callback with
// its data that slot 75 calls once.
struct Ev07 {
    s32 kind;               // 0x00
    s32 arg;                // 0x04
    s32 data;               // 0x08
    s32 fn;                 // 0x0C
};

// One of class 0x19's four slots at 0x6B0: an object and a position.
struct Slot19 {
    void* obj;              // 0x00
    u8 pad04[0x10 - 0x04];
    Vec02 v10;              // 0x10
    u8 pad20[0x50 - 0x20];
    f32 f50;                // 0x50: f698 over f610 (slots 0, 1) or f614 (func_001D8D90)
    u8 pad54[0x60 - 0x54];
};

// An entry of class 0x08's second queue at 0xAC8 (func_001CA720 adds one, func_001CA7C0
// resolves its id into obj).
struct Pend08 {
    s32 f00;                // 0x00
    s32 id;                 // 0x04: -1 once resolved
    void* obj;              // 0x08
};

// Class 0x10's doubleword at 0xC10, which its slot 9 keeps across the copy as an unaligned
// doubleword.
struct __attribute__((packed)) Pack10 {
    u64 value;              // 0x00
};

// Class 0x05's descriptor: 0x03's slots, then twelve more (slot n at 0x10 + 4n).
struct Desc05 : Desc03 {
    void (*m48)(SwitchedCollider* self, s32 mode);               // 0x130: slot 72 (func_001922E8)
    void* m49;                                      // 0x134: slot 73
    s32 (*m4A)(SwitchedCollider* self);                          // 0x138: slot 74 (func_00192410)
    s32 (*m4B)(SwitchedCollider* self, s32 a);                   // 0x13C: slot 75 (func_00192450, class 0x08: func_001C9A48)
    s32 (*m4C)(SwitchedCollider* self, void* arg);               // 0x140: slot 76 (func_00192488, class 0x08: func_001C9990)
    s32 (*m4D)(SwitchedCollider* self);                          // 0x144: slot 77 (func_00192490)
    void (*m4E)(SwitchedCollider* self, s32 mode, PlacedObject* other);   // 0x148: slot 78 (func_001924C8)
    void (*m4F)(SwitchedCollider* self, s32 state);              // 0x14C: slot 79 (func_001925C0)
    void (*m50)(SwitchedCollider* self);                         // 0x150: slot 80 (func_00192C58)
    void* m51;                                      // 0x154: slot 81 (func_00192A28)
    void* m52;                                      // 0x158: slot 82 (func_00192A38)
    void* m53;                                      // 0x15C: slot 83 (func_001930B0)
};

// Class 0x06's descriptor (also 0x07's and 0x14's): four more slots.
struct Desc06 : Desc05 {
    void* m54;                                      // 0x160: slot 84 (class 0x06: func_001C53B0)
    s32 (*m55)(TurningCollider* self);                          // 0x164: slot 85 (class 0x06: func_001C4F00)
    void* m56;                                      // 0x168: slot 86 (class 0x06: func_001C5248)
    void* m57;                                      // 0x16C: slot 87 (class 0x08: func_001CB3C8)
};

// Class 0x08's descriptor (and its subclasses'): twelve more slots.
struct Desc08 : Desc06 {
    void* m58;                                      // 0x170: slot 88 (class 0x08: func_001CA460)
    void* m59;                                      // 0x174: slot 89 (class 0x08: func_001C8010)
    void* m5A;                                      // 0x178: slot 90 (class 0x08: func_001C8E28)
    void* m5B;                                      // 0x17C: slot 91 (class 0x08: func_001C9008)
    void* m5C;                                      // 0x180: slot 92 (class 0x08: func_001C91C8)
    s32 (*m5D)(Agent* self);                          // 0x184: slot 93 (class 0x08: func_001CA468)
    void (*m5E)(Agent* self, s32 on);                 // 0x188: slot 94 (class 0x08: func_001C8C08)
    void* m5F;                                      // 0x18C: slot 95 (class 0x08: func_001C8590)
    void* m60;                                      // 0x190: slot 96 (class 0x08: func_001C9CF8)
    void* m61;                                      // 0x194: slot 97 (class 0x08: func_001C9AF8)
    void* (*m62)(Agent* self);                        // 0x198: slot 98 (class 0x08: func_001CAA08)
    void* m63;                                      // 0x19C: slot 99
};

struct SwitchedCollider : Collider {
    s32 f550;               // 0x550: on (func_00192990 calls func_001926D0, off func_00192780); set by slots 0 and 9
    s32 f554;               // 0x554: slot 69 keeps v560 while it is set
    u8 pad558[0x560 - 0x558];
    Vec02 v560;             // 0x560: v140 kept by slot 72; slot 69 reads its z
    u8 pad570[0x574 - 0x570];
    void* f574;             // 0x574: given to func_001BF788 by slot 13 (kind 0xB)
    union {
        Blk05 blk580;       // 0x580: copied whole by class 0x17 (func_0019A520)
        struct {
            s32 f580;       // 0x580: 1 at set-up
            void* f584;     // 0x584: an object (class 0x16: func_0015A418 0x160)
            void* f588[3];  // 0x588: objects (class 0x16: 0x161..0x163); slot 17 starts one
            f32 f594;       // 0x594: 300.0 in class 0x16
            void* f598;     // 0x598: itself at set-up
            s32 f59C;       // 0x59C: given to the node slot 78 makes
            u8 pad5A0[0x5AC - 0x5A0];
            void* f5AC[9];  // 0x5AC: f5D0 of them (slot 78 makes the first; slot 13 forgets one)
            s32 f5D0;       // 0x5D0
            u8 pad5D4[0x5F0 - 0x5D4];
            void* f5F0;     // 0x5F0: an object slot 78 reads (func_0012CCC0)
            u8 pad5F4[0x600 - 0x5F4];
        };
    };
    s32 f600;               // 0x600: slot 17 calls func_00192DD0 in 1 and 3
    PlacedObject* f604;              // 0x604: an object slot 80 moves into place
    u8 pad608[0x610 - 0x608];

    const Desc05* desc05() const { return (const Desc05*)desc; }
};

struct TurningCollider : SwitchedCollider {
    void* f610;             // 0x610
    void* f614;             // 0x614
    void* f618;             // 0x618
    void* f61C;             // 0x61C
    void* f620;             // 0x620
    void* f624;             // 0x624
    void* f628;             // 0x628
    void* f62C;             // 0x62C
    f32 f630;               // 0x630
    f32 f634;               // 0x634
    f32 f638;               // 0x638
    f32 f63C;               // 0x63C
    union {
        void* f640;         // 0x640
        Vec02 v640;         // 0x640: class 0x14 sets it from D_00248D30 (func_001DFBE0)
    };
    u8 pad650[0x660 - 0x650];
    Mat02 m660;             // 0x660: the identity at set-up (slot 16); slot 84 hands it on

    s32 f690;               // 0x690
    f32 f694;               // 0x694
    f32 f698;               // 0x698
    u8 pad69C[0x6A0 - 0x69C];
    Vec02 v6A0;             // 0x6A0
    Vec02 v6B0;             // 0x6B0
    void* f6C0;             // 0x6C0
    f32 f6C4;               // 0x6C4
    f32 f6C8;               // 0x6C8
    u8 pad6CC[0x6D4 - 0x6CC];
    s32 f6D4;               // 0x6D4
    u8 pad6D8[0x6DC - 0x6D8];
    void* f6DC;             // 0x6DC
    f32 f6E0;               // 0x6E0
    f32 f6E4;               // 0x6E4
    f32 f6E8;               // 0x6E8
    u8 pad6EC[0x6F0 - 0x6EC];
    Vec02 v6F0;             // 0x6F0
    f32 f700;               // 0x700
    s32 f704[3];            // 0x704
    s32 f710[3];            // 0x710
    u8 pad71C[0x720 - 0x71C];

    const Desc06* desc06() const { return (const Desc06*)desc; }
};

struct Player : TurningCollider {
    u8 pad720[0x900 - 0x720];
    s32 f900;               // 0x900
    u8 pad904[0xA10 - 0x904];
    s32 fA10;               // 0xA10
    u8 padA14[0x103C - 0xA14];
    u8 f103C[0x20];         // 0x103C
    u8 f105C[4];            // 0x105C
    u8 pad1060[0x1064 - 0x1060];
    void* f1064;            // 0x1064
    u8 pad1068[0x1188 - 0x1068];
    void* f1188;            // 0x1188
    s32 f118C;              // 0x118C
    Part07 f1190;           // 0x1190: given to func_001C4848/func_001C4618 with f610 (slot 37)
    Part07 f1290;           // 0x1290: the same with f614
    u8 pad1390[0x1504 - 0x1390];
    void* f1504;            // 0x1504
    void* f1508[4];         // 0x1508
    void* f1518;            // 0x1518
    u8 f151C[4];            // 0x151C: given to func_001BC4D8
    u8 f1520[0x21C0 - 0x1520];  // 0x1520: a record func_001C29E8 and func_001C3028 work on
    s32 f21C0;              // 0x21C0
    s32 f21C4;              // 0x21C4
    f32 f21C8;              // 0x21C8
    s32 f21CC;              // 0x21CC
    Vec02 v21D0[3];         // 0x21D0
    void* f2200;            // 0x2200
    s32 f2204;              // 0x2204
    s32 f2208;              // 0x2208
    u8 pad220C[0x2220 - 0x220C];
    s32 f2220;              // 0x2220
    s32 f2224;              // 0x2224
    s32 f2228;              // 0x2228
    f32 f222C;              // 0x222C
    u8 pad2230[0x2234 - 0x2230];
    void* f2234;            // 0x2234
    u8 pad2238[0x223C - 0x2238];
    s32 f223C;              // 0x223C
    u8 pad2240[0x2248 - 0x2240];
    s32 f2248;              // 0x2248
    s32 f224C;              // 0x224C
    s32 f2250;              // 0x2250
    s32 f2254;              // 0x2254
    s32 f2258;              // 0x2258
    s32 f225C;              // 0x225C
    s32 f2260;              // 0x2260
    s32 f2264;              // 0x2264
    u8 pad2268[0x226C - 0x2268];
    f32 f226C;              // 0x226C
    u8 pad2270[0x2284 - 0x2270];
    f32 f2284;              // 0x2284
    u8 pad2288[0x22AC - 0x2288];
    void* f22AC;            // 0x22AC
    u8 pad22B0[0x239C - 0x22B0];
    s32 f239C;              // 0x239C
    u8 pad23A0[0x23B0 - 0x23A0];
    void* f23B0;            // 0x23B0
    u8 pad23B4[0x23BC - 0x23B4];
    void* f23BC;            // 0x23BC
    u8 pad23C0[0x23CC - 0x23C0];
    void* f23CC;            // 0x23CC: the class 0x17 object that set state 7 (func_0019AB78)
    u8 pad23D0[0x23D4 - 0x23D0];
    void* f23D4;            // 0x23D4
    u8 pad23D8[0x23E0 - 0x23D8];
    f32 f23E0;              // 0x23E0
    f32 f23E4;              // 0x23E4
    u8 pad23E8[0x23F0 - 0x23E8];
    f32 f23F0;              // 0x23F0
    f32 f23F4;              // 0x23F4
    u8 pad23F8[0x2420 - 0x23F8];
    f32 f2420;              // 0x2420
    f32 f2424;              // 0x2424
    u8 pad2428[0x242C - 0x2428];
    f32 f242C;              // 0x242C
    f32 f2430;              // 0x2430
    f32 f2434;              // 0x2434
    u8 pad2438[0x2498 - 0x2438];
    s32 f2498;              // 0x2498
    u8 pad249C[0x24A0 - 0x249C];
    void* f24A0;            // 0x24A0
    u8 pad24A4[0x24B0 - 0x24A4];
    u8 f24B0[0x10];         // 0x24B0: filled by func_00128018 (func_00172898)
    u8 pad24C0[0x250C - 0x24C0];
    s32 f250C;              // 0x250C
    s32 f2510;              // 0x2510
    void* f2514;            // 0x2514
    u8 pad2518[0x2590 - 0x2518];
    s32 f2590;              // 0x2590
    u8 pad2594[0x25AC - 0x2594];
    s32 f25AC;              // 0x25AC
    u8 pad25B0[0x25D8 - 0x25B0];
    void* f25D8[5];         // 0x25D8
    u8 pad25EC[0x2674 - 0x25EC];
    s32 f2674;              // 0x2674: func_001D1200 compares it with f2678
    OnOffObject* f2678;             // 0x2678: the record func_001D1260 fills
    u8 pad267C[0x2684 - 0x267C];
    s32 f2684;              // 0x2684
    f32 f2688;              // 0x2688
    s32 f268C;              // 0x268C
    u8 pad2690[0x26A0 - 0x2690];
    s32 f26A0;              // 0x26A0
    u8 pad26A4[0x26A8 - 0x26A4];
    s32 f26A8;              // 0x26A8
    void* f26AC;            // 0x26AC
    union {
        s32 f26B0;          // 0x26B0: set by func_001D4C90 (a function's address, or 0)
        void (*cb26B0)(Player* self);  // 0x26B0: called once by func_001D4C98
    };
    Ev07 f26B4;             // 0x26B4: the last message slot 75 took (func_001D4D08)
    s32 f26C4;              // 0x26C4
    f32 f26C8;              // 0x26C8
    u8 pad26CC[0x2718 - 0x26CC];
    s32 f2718;              // 0x2718: -1, or a mode that holds the pad-select flag (func_001D27C0)
    u8 pad271C[0x2730 - 0x271C];
    s32 f2730;              // 0x2730
    u8 pad2734[0x2750 - 0x2734];
    void* f2750;            // 0x2750
    u8 pad2754[0x2758 - 0x2754];
    f32 f2758;              // 0x2758
    s32 f275C;              // 0x275C
    u8 pad2760[0x2768 - 0x2760];
    s32 f2768;              // 0x2768
    u8 pad276C[0x2770 - 0x276C];
    u8 f2770[0x20];         // 0x2770
    u8 pad2790[0x2B70 - 0x2790];
    union {
        Vec02 q2B70[2];     // 0x2B70: the two quads func_00178598 copies from what func_001782C0 takes
        struct {
            void* f2B70;    // 0x2B70: the object it touches (func_001D4A98, func_001D51A0)
            s32 f2B74;      // 0x2B74
            s32 f2B78;      // 0x2B78
            s32 f2B7C;      // 0x2B7C
            s32 f2B80;      // 0x2B80
            s32 f2B84;      // 0x2B84
            s32 f2B88;      // 0x2B88
            s32 f2B8C;      // 0x2B8C
        };
    };
    u8 pad2B90[0x2BB0 - 0x2B90];
    Vec02 v2BB0;            // 0x2BB0
    Vec02 v2BC0;            // 0x2BC0
    void* f2BD0;            // 0x2BD0
    u8 pad2BD4[0x2BD8 - 0x2BD4];
    s32 f2BD8;              // 0x2BD8
    u8 pad2BDC[0x2BE4 - 0x2BDC];
    void* f2BE4;            // 0x2BE4
    void* f2BE8;            // 0x2BE8
    u8 pad2BEC[0x2BF0 - 0x2BEC];
};

struct Agent : TurningCollider {
    void* f720;             // 0x720
    s32 f724;               // 0x724
    f32 f728;               // 0x728
    s32 f72C;               // 0x72C
    void* f730;             // 0x730: what func_001C9A58 hands to func_001C8F20 (0 from func_001CB328)
    u8 pad734[0x738 - 0x734];
    s32 f738;               // 0x738
    f32 f73C;               // 0x73C
    f32 f740;               // 0x740
    f32 f744;               // 0x744
    f32 f748;               // 0x748
    f32 f74C;               // 0x74C
    void* f750;             // 0x750
    AnimationPlayer* f754;       // 0x754: an animation's player (func_0012C288 makes it, func_0012E760 ends it)
    Slot08 f758[17];        // 0x758: ids -1 at set-up (slot 0)
    AnimationPlayer* f7E0;       // 0x7E0: another (func_0012F0A0, func_0012F6B0)
    s32 f7E4;               // 0x7E4
    Group08 f7E8[8];        // 0x7E8
    void* f868;             // 0x868
    f32 f86C;               // 0x86C
    Slot08 f870[17];        // 0x870: ids -1 at set-up (slot 0)
    void* f8F8;             // 0x8F8
    u8 pad8FC[0x910 - 0x8FC];
    f32 f910;               // 0x910
    f32 f914;               // 0x914
    f32 f918;               // 0x918
    f32 f91C;               // 0x91C
    s32 f920;               // 0x920
    s32 f924;               // 0x924
    s32 f928;               // 0x928
    s32 f92C;               // 0x92C: func_001C84C0 compares it with f930
    s32 f930;               // 0x930
    u8 pad934[0xA60 - 0x934];
    s32 fA60;               // 0xA60
    u8 padA64[0xA68 - 0xA64];
    s32 fA68;               // 0xA68
    s32 fA6C;               // 0xA6C
    f32 fA70;               // 0xA70
    void* fA74;             // 0xA74
    s32 fA78;               // 0xA78: the number of fA7C entries (func_001CA960)
    Elem08 fA7C[4];         // 0xA7C
    u8 padAAC[0xAC4 - 0xAAC];
    s32 fAC4;               // 0xAC4: the number of fAC8 entries (func_001CA720)
    Pend08 fAC8[4];         // 0xAC8
    s32 fAF8;               // 0xAF8
    s32 fAFC;               // 0xAFC
    s32 fB00;               // 0xB00
    s32 fB04;               // 0xB04: a flag (1 from func_001CA888, tested by func_001C72A0)
    s32 fB08;               // 0xB08
    void* fB0C;             // 0xB0C
    s32 fB10;               // 0xB10
    s32 fB14;               // 0xB14
    f32 fB18;               // 0xB18
    s32 fB1C;               // 0xB1C
    u8 fB20[4];             // 0xB20
    f32 fB24;               // 0xB24
    u8 padB28[0xB40 - 0xB28];
    s32 fB40;               // 0xB40: set to 1 with fB48 (func_001CAB00)
    u8 padB44[0xB48 - 0xB44];
    void* fB48;             // 0xB48
    s32 fB4C;               // 0xB4C
    void* fB50;             // 0xB50
    void* fB54;             // 0xB54
    s32 fB58;               // 0xB58
    s32 fB5C;               // 0xB5C
    u8 fB60[0x10];          // 0xB60
    s32 fB70;               // 0xB70
    s32 fB74;               // 0xB74
    s32 fB78;               // 0xB78
    s32 fB7C;               // 0xB7C
    s32 fB80;               // 0xB80
    s32 fB84;               // 0xB84
    s32 fB88;               // 0xB88
    s32 fB8C;               // 0xB8C
    u8 padB90[0xBA4 - 0xB90];
    s32 fBA4;               // 0xBA4
    u8 padBA8[0xBD0 - 0xBA8];
    s32 fBD0;               // 0xBD0
    s32 fBD4;               // 0xBD4
    u32 fBD8;               // 0xBD8
    u8 padBDC[0xBE8 - 0xBDC];
    f32 fBE8;               // 0xBE8
    s32 fBEC;               // 0xBEC
    s32 fBF0;               // 0xBF0
    f32 fBF4;               // 0xBF4
    f32 fBF8;               // 0xBF8
    f32 fBFC;               // 0xBFC
    f32 fC00;               // 0xC00
    s32 fC04;               // 0xC04
    u8 padC08[0xC10 - 0xC08];

    const Desc08* desc08() const { return (const Desc08*)desc; }
};

struct C09 : Agent {
    s32 fC10;               // 0xC10
    void* fC14;             // 0xC14
    f32 fC18;               // 0xC18
    f32 fC1C;               // 0xC1C
    f32 fC20;               // 0xC20
    f32 fC24;               // 0xC24
    s32 fC28;               // 0xC28
    s32 fC2C;               // 0xC2C
    s32 fC30;               // 0xC30
    void* fC34;             // 0xC34
    u8 fC38[0x88];          // 0xC38
    void* fCC0;             // 0xCC0
    s32 fCC4;               // 0xCC4
    u8 padCC8[0xCD4 - 0xCC8];
    s32 fCD4;               // 0xCD4
    Slot08 fCD8[5];         // 0xCD8: fCD4 of them, resolved by slot 16 (func_001B7128)
};

struct C0A : Agent {
    f32 fC10;               // 0xC10
    f32 fC14;               // 0xC14
    s32 fC18;               // 0xC18
    s32 fC1C;               // 0xC1C
    f32 fC20;               // 0xC20
    f32 fC24;               // 0xC24
    f32 fC28;               // 0xC28
    f32 fC2C;               // 0xC2C
    s32 fC30;               // 0xC30
    s32 fC34;               // 0xC34
    u8 padC38[0xC40 - 0xC38];
    s32 fC40;               // 0xC40
    u8 padC44[0xC50 - 0xC44];
};

struct C0B : C0A {
    void* fC50;             // 0xC50
    void* fC54;             // 0xC54
    s32 fC58;               // 0xC58
    s32 fC5C;               // 0xC5C
    void* fC60;             // 0xC60
    s32 fC64[6];            // 0xC64: keys slot 56 answers for itself (func_001E9038)
    s32 fC7C;               // 0xC7C
    void* fC80[4];          // 0xC80
    s32 fC90;               // 0xC90
    u8 padC94[0xCA0 - 0xC94];
};

struct C0C : Agent {
    s32 fC10;               // 0xC10
    u8 padC14[0xE00 - 0xC14];
    s32 fE00;               // 0xE00
    u8 padE04[0xE0C - 0xE04];
    void* fE0C;             // 0xE0C
    void* fE10;             // 0xE10
    void* fE14;             // 0xE14
    void* fE18;             // 0xE18
    void* fE1C;             // 0xE1C
    s32 fE20;               // 0xE20
    void* fE24;             // 0xE24
    s32 fE28;               // 0xE28
    s32 fE2C;               // 0xE2C
    s32 fE30[3];            // 0xE30
    s32 fE3C;               // 0xE3C
    Vec02 vE40;             // 0xE40
};

struct C0D : Agent {
    u8 padC10[0xC14 - 0xC10];
    s32 fC14;               // 0xC14
    s32 fC18;               // 0xC18
    s32 fC1C;               // 0xC1C
    u8 padC20[0xC24 - 0xC20];
    s32 fC24;               // 0xC24
    u8 padC28[0xC30 - 0xC28];
};

struct C0E : Agent {
    s32 fC10;               // 0xC10: the number of fC14
    void* fC14[4];          // 0xC14: objects
    void* fC24;             // 0xC24: an object whose position slot 89 takes (func_001F3BD8)
    void* fC28;             // 0xC28: the same in states 12 and 13; slot 71 clears it
    void* fC2C;             // 0xC2C: an object (slot 91 calls its slot 80)
    s32 fC30;               // 0xC30
    s32 fC34;               // 0xC34
    s32 fC38;               // 0xC38
    s32 fC3C;               // 0xC3C
    s32 fC40;               // 0xC40
    s32 fC44;               // 0xC44
    u8 padC48[0xC50 - 0xC48];
};

struct C0F : Agent {
    s32 fC10;               // 0xC10
    void* fC14;             // 0xC14
    u8 padC18[0xC20 - 0xC18];
};

struct C10 : Agent {
    Pack10 fC10;            // 0xC10
    u8 padC18[0xC20 - 0xC18];
};

struct C11 : C10 {
    s32 fC20;               // 0xC20
    s32 fC24;               // 0xC24
    void* fC28;             // 0xC28
    s32 fC2C;               // 0xC2C
};

struct C12 : C10 {
    void* fC20;             // 0xC20
    f32 fC24;               // 0xC24
    u8 padC28[0xC30 - 0xC28];
};

struct C13 : Agent {
    u8 padC10[0xC20 - 0xC10];
    s32 fC20;               // 0xC20
    u8 padC24[0xC34 - 0xC24];
    void* fC34;             // 0xC34
    void* fC38;             // 0xC38
    u8 padC3C[0xC48 - 0xC3C];
    void* fC48;             // 0xC48
    u8 padC4C[0xC50 - 0xC4C];
    void* fC50;             // 0xC50
    void* fC54;             // 0xC54
    u8 padC58[0xC5C - 0xC58];
    s32 fC5C;               // 0xC5C
    s32 fC60;               // 0xC60
    f32 fC64;               // 0xC64
    s32 fC68;               // 0xC68: the number of fC6C entries (func_001ED090)
    void* fC6C;             // 0xC6C: a 0x400-byte table (slot 0)
    s32 fC70;               // 0xC70
    s32 fC74;               // 0xC74
    s32 fC78;               // 0xC78
    f32 fC7C;               // 0xC7C
    f32 fC80;               // 0xC80
    f32 fC84;               // 0xC84
    f32 fC88;               // 0xC88
    f32 fC8C;               // 0xC8C
    u8 padC90[0xC94 - 0xC90];
    s32 fC94;               // 0xC94
    s32 fC98;               // 0xC98
    void* fC9C;             // 0xC9C
};

struct C14 : TurningCollider {
    s32 f720;               // 0x720: the mode func_001DFBE0 sets
    f32 f724;               // 0x724: the clock when it last changed (func_001DFBE0)
    s32 f728;               // 0x728
    f32 f72C;               // 0x72C
    f32 f730;               // 0x730
    u8 pad734[0x738 - 0x734];
    s32 f738;               // 0x738
    s32 f73C;               // 0x73C
    void* f740;             // 0x740
    void* f744;             // 0x744
    void* f748;             // 0x748
    void* f74C;             // 0x74C
    void* f750;             // 0x750
    void* f754;             // 0x754
    void* f758;             // 0x758
    StateWalker* f75C;          // 0x75C: a handle (func_001B64D8, func_001B6628 take it)
};

struct C15 : SwitchedCollider {
    s32 f610;               // 0x610
    s32 f614;               // 0x614
    f32 f618;               // 0x618
    f32 f61C;               // 0x61C
    f32 f620;               // 0x620
    f32 f624;               // 0x624
    f32 f628;               // 0x628
    u8 pad62C[0x640 - 0x62C];
    void* f640;             // 0x640
    void* f644;             // 0x644
    s32* f648;              // 0x648
    void* f64C;             // 0x64C
    void* f650;             // 0x650
    void* f654;             // 0x654
    void* f658;             // 0x658
    void* f65C;             // 0x65C
    void* f660;             // 0x660
    void* f664;             // 0x664
    s32 f668;               // 0x668
    u8 f66C[0xC];           // 0x66C
    s32 f678;               // 0x678
    void* f67C;             // 0x67C
    void* f680;             // 0x680
    void* f684;             // 0x684
    s32 f688;               // 0x688
    u8 pad68C[0x690 - 0x68C];
};

struct C16 : SwitchedCollider {
    void* f610;             // 0x610
    void* f614;             // 0x614
    void* f618;             // 0x618
    s32 f61C;               // 0x61C
    void* f620;             // 0x620
    void* f624;             // 0x624
    s32 f628;               // 0x628
    u8 pad62C[0x630 - 0x62C];
    s32 f630;               // 0x630
    u8 pad634[0x638 - 0x634];
    s32 f638;               // 0x638
    void* f63C;             // 0x63C
    void* f640;             // 0x640
    s32 f644;               // 0x644
    u8 pad648[0x650 - 0x648];
    f32 f650;               // 0x650
    f32 f654;               // 0x654
    f32 f658;               // 0x658
    f32 f65C;               // 0x65C
};

struct C17 : SwitchedCollider {
    s32 f610;               // 0x610
    StateWalker* f614;          // 0x614: a handle (func_001B6290)
    u8 pad618[0x61C - 0x618];
    u8 f61C[0x28];          // 0x61C: three 12-byte records func_0019A178 sets up (slot 16)
    s32 f644;               // 0x644
    void* f648;             // 0x648
    s32 f64C;               // 0x64C
    void* f650;             // 0x650
    s32 f654;               // 0x654
    Ent17 f658[6];          // 0x658
    s32 f760;               // 0x760
    s32 f764;               // 0x764
    void* f768[28];         // 0x768
    s32 f7D8;               // 0x7D8
    void* f7DC[1];          // 0x7DC
    u8 pad7E0[0x800 - 0x7E0];
};

struct C18 : SwitchedCollider {
    void* f610;             // 0x610
    StateWalker* f614;          // 0x614: a handle (func_001B6290)
    f32 f618;               // 0x618
    f32 f61C;               // 0x61C
    u8 pad620[0x624 - 0x620];
    f32 f624;               // 0x624
    f32 f628;               // 0x628
    u8 pad62C[0x630 - 0x62C];
    Vec02 v630;             // 0x630
    void* f640;             // 0x640: an object func_00198760 tests and hands on
    s32 f644;               // 0x644
    u8 pad648[0x65C - 0x648];
    void* f65C;             // 0x65C
    void* f660;             // 0x660
    void* f664;             // 0x664
    u8 pad668[0x67C - 0x668];
    s32 f67C;               // 0x67C: counted up by func_00198760, at most D_0026A720
    s32 f680;               // 0x680: the count g_gaugeAmountCaption shows (func_00197F10)
    s32 f684;               // 0x684: its limit, one per class 0x48 object (func_00198920)
    f32 f688;               // 0x688
    u8 pad68C[0x690 - 0x68C];
    s32 f690;               // 0x690
    void* f694;             // 0x694: f690 entries
    f32 f698;               // 0x698: the time of the next transfer (func_00197848, func_00198760)
    List01 f69C;            // 0x69C: link offset 0x568 (slot 0); filled by slot 16
    List01 f6A8;            // 0x6A8: link offset 0x568 (slot 0)
    void* f6B4;             // 0x6B4
    void* f6B8;             // 0x6B8
    u8 pad6BC[0x6C0 - 0x6BC];
};

struct C19 : SwitchedCollider {
    f32 f610;               // 0x610
    f32 f614;               // 0x614
    f32 f618;               // 0x618
    f32 f61C;               // 0x61C
    Vec02 v620;             // 0x620
    u8 f630[0x40];          // 0x630: 0x40 bytes slot 0 copies from D_00275250
    f32 f670;               // 0x670
    f32 f674;               // 0x674
    f32 f678;               // 0x678
    u8 pad67C[0x680 - 0x67C];
    f32 f680;               // 0x680
    f32 f684;               // 0x684
    u8 pad688[0x694 - 0x688];
    f32 f694;               // 0x694
    f32 f698;               // 0x698: divided by f610 or f614 into the slots (func_001D8D90); 0 in func_001D9C98
    f32 f69C;               // 0x69C: eased by func_001D8D90
    s32 f6A0;               // 0x6A0
    u8 pad6A4[0x6B0 - 0x6A4];
    Slot19 f6B0[4];         // 0x6B0
    void* f830;             // 0x830
    f32 f834;               // 0x834
    u8 pad838[0x83C - 0x838];
    f32 f83C;               // 0x83C
    f32 f840;               // 0x840
    f32 f844;               // 0x844
    u8 pad848[0x850 - 0x848];
    f32 f850;               // 0x850
    f32 f854;               // 0x854
    s32 f858;               // 0x858
    f32 f85C;               // 0x85C
    f32 f860;               // 0x860
    f32 f864;               // 0x864
    f32 f868;               // 0x868
    u8 pad86C[0x870 - 0x86C];
    s32 f870;               // 0x870
    u8 f874[0x280];         // 0x874
    void* fAF4;             // 0xAF4
    void* fAF8;             // 0xAF8
    u8 padAFC[0xB00 - 0xAFC];
    s32 fB00;               // 0xB00
    s32 fB04;               // 0xB04
    s32 fB08;               // 0xB08
    s32 fB0C;               // 0xB0C
    u8 padB10[0xB14 - 0xB10];
    void* fB14;             // 0xB14
    u8 padB18[0xB30 - 0xB18];
    s32 fB30;               // 0xB30
    s32 fB34;               // 0xB34
    f32 fB38;               // 0xB38
    u8 padB3C[0xB44 - 0xB3C];
    void* fB44;             // 0xB44
    void* fB48;             // 0xB48
    u8 padB4C[0xB78 - 0xB4C];
    void* fB78;             // 0xB78
    u8 fB7C[0x4];           // 0xB7C
    u8 fB80[0x4];           // 0xB80
    u8 fB84[0x4];           // 0xB84
    u8 padB88[0xB8C - 0xB88];
    f32 fB8C;               // 0xB8C
    f32 fB90;               // 0xB90
    f32 fB94;               // 0xB94
    f32 fB98;               // 0xB98
    u8 padB9C[0xBB0 - 0xB9C];
};

struct C1A : C19 {
    s32 fBB0;               // 0xBB0
    f32 fBB4;               // 0xBB4
    void* fBB8;             // 0xBB8
    StateWalker* fBBC;          // 0xBBC: a handle (func_001B6290)
    void* fBC0;             // 0xBC0
    u8 padBC4[0xBC8 - 0xBC4];
    void* fBC8;             // 0xBC8
    void* fBCC;             // 0xBCC
    void* fBD0;             // 0xBD0
    u8 padBD4[0xBF0 - 0xBD4];
    s32 fBF0;               // 0xBF0
    f32 fBF4;               // 0xBF4
    f32 fBF8;               // 0xBF8
    u8 padBFC[0xC00 - 0xBFC];
    s32 fC00;               // 0xC00
    void* fC04;             // 0xC04
    u8 padC08[0xC10 - 0xC08];
};

struct C1B : SwitchedCollider {
    s32 f610;               // 0x610
    u8 pad614[0x618 - 0x614];
    s32 f618;               // 0x618
    u8 pad61C[0x650 - 0x61C];
    void* f650;             // 0x650
    void* f654;             // 0x654
    void* f658;             // 0x658
    u8 pad65C[0x660 - 0x65C];
    void* f660;             // 0x660
    u8 pad664[0x668 - 0x664];
    void* f668;             // 0x668
    u8 pad66C[0x680 - 0x66C];
    s32 f680;               // 0x680
    f32 f684;               // 0x684
    u8 pad688[0x6C0 - 0x688];
    void* f6C0;             // 0x6C0
    u8 pad6C4[0x6D0 - 0x6C4];
    s32 f6D0;               // 0x6D0
    f32 f6D4;               // 0x6D4
    f32 f6D8;               // 0x6D8
    u8 pad6DC[0x6E0 - 0x6DC];
    s32 f6E0;               // 0x6E0
    u8 pad6E4[0x6E8 - 0x6E4];
    void* f6E8;             // 0x6E8
    u8 pad6EC[0x704 - 0x6EC];
    s32 f704;               // 0x704
    f32 f708;               // 0x708
    s32 f70C;               // 0x70C
};

struct C1C : SwitchedCollider {
    void* f610;             // 0x610
    void* f614;             // 0x614
    u8 pad618[0x628 - 0x618];
    void* f628;             // 0x628
    s32 f62C;               // 0x62C
    s32 f630;               // 0x630
    Ent1C f634[8];          // 0x634: f630 of them, f62C the next (slot 77)
    f32 f674;               // 0x674
    s32 f678;               // 0x678
    void* f67C;             // 0x67C
    s32 f680;               // 0x680
    f32 f684;               // 0x684
    s32 f688;               // 0x688
    void* f68C;             // 0x68C
};

struct C1D : SwitchedCollider {
    s32 f610;               // 0x610
    f32 f614;               // 0x614
    u8 pad618[0x62C - 0x618];
    void* f62C;             // 0x62C
    f32 f630;               // 0x630
    f32 f634;               // 0x634
    s32 f638;               // 0x638
    f32 f63C;               // 0x63C
    f32 f640;               // 0x640
    f32 f644;               // 0x644
    f32 f648;               // 0x648
    u8 pad64C[0x660 - 0x64C];
    void* f660;             // 0x660
    void* f664;             // 0x664
    void* f668;             // 0x668
    u8 pad66C[0x670 - 0x66C];
    f32 f670;               // 0x670
    u8 pad674[0x678 - 0x674];
    void* f678;             // 0x678
    void* f67C;             // 0x67C
    s32 f680;               // 0x680
    s32 f684;               // 0x684
    void* f688;             // 0x688
    f32 f68C;               // 0x68C
    s32 f690;               // 0x690
    s32 f694;               // 0x694
    s32 f698;               // 0x698
    s32 f69C[1];            // 0x69C
    u8 pad6A0[0x71C - 0x6A0];
    s32 f71C;               // 0x71C
    void* f720[16];         // 0x720
};

typedef char check_Ent17[sizeof(Ent17) == 0x2C ? 1 : -1];
typedef char check_Slot19[sizeof(Slot19) == 0x60 ? 1 : -1];
typedef char check_SwitchedCollider[sizeof(SwitchedCollider) == 0x610 ? 1 : -1];
typedef char check_TurningCollider[sizeof(TurningCollider) == 0x720 ? 1 : -1];
typedef char check_Player[sizeof(Player) == 0x2BF0 ? 1 : -1];
typedef char check_Agent[sizeof(Agent) == 0xC10 ? 1 : -1];
typedef char check_C09[sizeof(C09) == 0xD00 ? 1 : -1];
typedef char check_C0A[sizeof(C0A) == 0xC50 ? 1 : -1];
typedef char check_C0B[sizeof(C0B) == 0xCA0 ? 1 : -1];
typedef char check_C0C[sizeof(C0C) == 0xE50 ? 1 : -1];
typedef char check_C0D[sizeof(C0D) == 0xC30 ? 1 : -1];
typedef char check_C0E[sizeof(C0E) == 0xC50 ? 1 : -1];
typedef char check_C0F[sizeof(C0F) == 0xC20 ? 1 : -1];
typedef char check_C10[sizeof(C10) == 0xC20 ? 1 : -1];
typedef char check_C11[sizeof(C11) == 0xC30 ? 1 : -1];
typedef char check_C12[sizeof(C12) == 0xC30 ? 1 : -1];
typedef char check_C13[sizeof(C13) == 0xCA0 ? 1 : -1];
typedef char check_C14[sizeof(C14) == 0x760 ? 1 : -1];
typedef char check_C15[sizeof(C15) == 0x690 ? 1 : -1];
typedef char check_C16[sizeof(C16) == 0x660 ? 1 : -1];
typedef char check_C17[sizeof(C17) == 0x800 ? 1 : -1];
typedef char check_C18[sizeof(C18) == 0x6C0 ? 1 : -1];
typedef char check_C19[sizeof(C19) == 0xBB0 ? 1 : -1];
typedef char check_C1A[sizeof(C1A) == 0xC10 ? 1 : -1];
typedef char check_C1B[sizeof(C1B) == 0x710 ? 1 : -1];
typedef char check_C1C[sizeof(C1C) == 0x690 ? 1 : -1];
typedef char check_C1D[sizeof(C1D) == 0x760 ? 1 : -1];
typedef char check_Desc05[sizeof(Desc05) == 0x160 ? 1 : -1];
typedef char check_Desc06[sizeof(Desc06) == 0x170 ? 1 : -1];
typedef char check_Desc08[sizeof(Desc08) == 0x1A0 ? 1 : -1];

#endif

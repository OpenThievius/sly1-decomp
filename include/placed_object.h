// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x02 (descriptor D_00217498, 0x2D0 bytes), the parent of every placed object: what its
// load method 0x1289C0 reads is the common block of docs/DISC.md ("Objects"). Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// The fields are the ones the class's own methods (src/main/pose_source.cpp,
// placed_object.cpp, game_progress.cpp) and the families under it read. Records only the class points
// to, which its readers see in different shapes, stay `void*` until their own types exist.
#ifndef PLACED_OBJECT_H
#define PLACED_OBJECT_H

#include "base_object.h"

struct PlacedObject;
struct Attachment;   // an attachment (t2195.h): a record of the world's pool at World::pool1B20
struct Rec2195_224;     // the 0xC0-byte record at +0x224 (t2195.h)
struct T2195_790;       // the aim attachment at +0x200 (attachment.h)
struct T2195_600;       // the own-value attachment at +0x204 (attachment.h)
struct T2195_5B0;       // the value-pointer attachment at +0x2C0 (attachment.h)
struct RangeRecord;         // the 0x2E0-byte record at +0x284 (s1291d0.h)
struct SoundRecord;         // the 0x24-byte record at +0x2AC (s1be4d8.h)
struct Animation;           // class 0x83 (animation.h)

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

// The 0x14-byte record at +0x2A0 (func_00129108 makes it): the animation the object starts when
// it starts (func_00124A48 queues func_00124CC0 while anim or key is set), and from where.
struct AnimationStart {
    Animation* anim;        // 0x00: the animation, or 0 to find it by key
    s32 key;                // 0x04: -1 at set-up; the animation's id
    s32 mode;               // 0x08: 0: value is a time, 1: a fraction of the length, 2: the time at the position
    f32 value;              // 0x0C
    f32 speedScale;         // 0x10: 1.0 at set-up; the player's scale of its speed (func_0012C288)
};

// A node of the world's pool at +0x1C18, in its list at +0x1C30 or +0x1C24 by the owner's
// +0x294 (AddObjectNodeToWorld): the object and a level its rate moves (StepObjectLevelRamp).
struct WorldObjectNode {
    PlacedObject* owner;    // 0x00
    f32 level;              // 0x04
    f32 rate;               // 0x08
};

// The 0x40-byte colour record at +0x288 (func_0012B040 makes it from D_00261000[0]); the presets
// D_00260F00 are records of this shape, given as words.
struct __attribute__((aligned(16))) ColorRecord {
    union {
        s32 w[16];          // 0x00: the record as its presets give it
        struct {
            s32 preset;     // 0x00: the preset's index, -1 when none (func_0012B0B0)
            u8 pad04[0x10 - 0x04];
            Vec02 c10;      // 0x10: a colour (func_0012B140)
            Vec02 c20;      // 0x20: a second one (func_0012B1A0)
            f32 factor;     // 0x30: 2.0 in the presets (func_0012B200)
        };
    };
};

// Class 0x02's descriptor: the root's slots, then twenty more (slot n at 0x10 + 4n).
struct Desc02 : Desc01 {
    void (*m1C)(PlacedObject* self);                         // 0x80: func_00125438
    void (*m1D)(PlacedObject* self, Vec02* pos);             // 0x84: set the position (func_001273F0)
    void (*m1E)(PlacedObject* self, Mat02* rot);             // 0x88: set the matrix (func_00127478)
    void (*m1F)(PlacedObject* self, PlacedObject* other);             // 0x8C: take other's frame (func_001276C0)
    void (*m20)(PlacedObject* self, Vec02* v);               // 0x90: func_001274F8
    void (*m21)(PlacedObject* self, Vec02* v);               // 0x94: func_00127590
    void* m22;                                      // 0x98: func_00122550
    void* m23;                                      // 0x9C: func_001225D0
    void (*m24)(PlacedObject* self, void* a, void* b);       // 0xA0: func_00125C90
    void (*m25)(PlacedObject* self, void* a, void* m);       // 0xA4: func_001261C0
    void (*m26)(PlacedObject* self, void* a, void* m);       // 0xA8: func_00126270
    void (*m27)(PlacedObject* self, void* frame);            // 0xAC: func_001660E8
    void (*m28)(PlacedObject* self, Vec02* pos, Vec02* vec); // 0xB0: told the position an attachment gave (func_001227B0)
    void (*m29)(PlacedObject* self, Mat02* rot, Vec02* v);   // 0xB4: told the orientation (func_00122968, func_00129648; func_00128E88)
    void (*m2A)(PlacedObject* self, void* out);              // 0xB8: func_00128FD0
    void (*m2B)(PlacedObject* self);                         // 0xBC: func_00129780
    void (*m2C)(PlacedObject* self);                         // 0xC0: func_001660A0
    s32 (*m2D)(PlacedObject* self, void* other);             // 0xC4: func_0012B2E8
    void* m2E;                                      // 0xC8
    void (*m2F)(PlacedObject* self, s32 state);              // 0xCC: set the state (class 0x55: func_00147AB0)
};

struct FoundList;

struct PlacedObject : BaseObject {
    List01 children;        // 0x34: the child objects, linked at BaseObject::next (offset 0x1C)
    Link02 link40;          // 0x40
    Link02 link48;          // 0x48
    PlacedObject* root;              // 0x50: the topmost object above it (itself at the top)
    PlacedObject* f54;      // 0x54: the owner of its link list (func_0015F6C0); given back with func_0015F710 by slot 7
    Link02 link58;          // 0x58: the link in list60
    List01 list60;          // 0x60: offset 0x58
    s32 count6C;            // 0x6C
    FoundList* items70[4];  // 0x70: count6C of the groups it is in (func_0015F8B0)
    f32 fadeDistanceFar;    // 0x80: FLT_MAX at set-up
    f32 fadeDistanceNear;   // 0x84: FLT_MAX at set-up
    s32 visibilityMask;     // 0x88: 0x0FFFFFFF at set-up
    void* f8C;              // 0x8C
    s32 save90;             // 0x90: Collider::mode450 kept by func_001BD790
    s32 save94;             // 0x94: Collider::mode470 kept by func_001BD790
    s32 f98[1];             // 0x98
    u8 pad9C[0xA0 - 0x9C];
    Vec02 vA0;              // 0xA0: v150 kept by slot 20
    Vec02 vB0;              // 0xB0: v160 kept by slot 20
    u64 savedC0;            // 0xC0: bits 0, 1: Collider::flags538 bits 54, 55 kept by func_001BD790
    u8 padC8[0xD0 - 0xC8];
    Mat02 rot;              // 0xD0: the placement matrix (the common block)
    Vec02 pos;              // 0x100: the position (the common block; slot 29)
    Mat02 m110;             // 0x110
    Vec02 v140;             // 0x140
    Vec02 v150;             // 0x150: slot 32
    Vec02 v160;             // 0x160: slot 33
    Vec02 v170;             // 0x170: added to the spin through the frames (func_001278A8)
    Vec02 v180;             // 0x180: crossed with the arm to the pivot (func_001C5148)
    Vec02 v190;             // 0x190
    Mat02 m1A0;             // 0x1A0
    Vec02 v1D0;             // 0x1D0
    List01 list1E0;         // 0x1E0: the attachments (Attachment records), linked at Attachment::link (offset 8)
    Attachment* positionAttachment; // 0x1EC: the attachment that gives the position (slot 4)
    Attachment* orientationAttachment; // 0x1F0: the one that gives the orientation (slot 5)
    void* matrixAttachment; // 0x1F4
    void** indexedAttachments; // 0x1F8: f26C entries
    Attachment* baseAttachment; // 0x1FC: the base attachment (func_001296E0, table D_00219560)
    T2195_790* aimAttachment; // 0x200: the aim attachment (func_00129730)
    T2195_600* ownValueAttachment; // 0x204: the own-value attachment (func_0012A8D8)
    u8 pad208[0x20C - 0x208];
    u8* p20C;               // 0x20C: D_00260E70 until slot 9 copies it
    u8* p210;               // 0x210: D_00260E80
    u8* p214;               // 0x214: D_00260E90
    u8* p218;               // 0x218: D_00260EA0
    u8* p21C;               // 0x21C: D_00260EB0
    u8* p220;               // 0x220: D_00260EC0
    Rec2195_224* linkRecord; // 0x224: a 0xC0-byte record (t2195.h)
    s32 tries;              // 0x228: as Actor6C::tries; func_0013DC38 tests it, func_00129DF8 clears the root's
    union {
        u8 sub22C[0x26C - 0x22C];   // 0x22C: a record func_00165728/165828/165920/165FE0 work on
        struct {
            u8 pad22C[0x238 - 0x22C];
            s32 drawPartCount;      // 0x238: the parts func_001533A8 draws
            void* drawParts;        // 0x23C: drawPartCount parts of 0x70 bytes
            void* partStates;       // 0x240: drawPartCount entries of 0x28 bytes (func_001250C8 clears their +8 to -1)
        };
    };
    s32 valueCount;         // 0x26C: the number of f1F8 entries
    f32* f270;              // 0x270
    f32* f274; // 0x274
    s32 f278;               // 0x278: func_001EECE0 calls slot 50 while it is set
    s32 elemCount;          // 0x27C
    Elem02** elems;         // 0x280: elemCount of them
    RangeRecord* rangeRecord;   // 0x284: a 0x2E0-byte record in the world's list at 0x1C00
    ColorRecord* colorRecord; // 0x288: a 0x40-byte record
    f32 xyScale;            // 0x28C
    f32 zScale;             // 0x290
    s32 frameStepClock;     // 0x294: in the world's list at 0x78 instead of 0x54
    WorldObjectNode* rampNode; // 0x298: its node in the world's list (func_00126C58)
    union {
        s32 f29C;           // 0x29C: cleared by func_0015FBB8 (slot 20)
        f32 eventTimer;     // 0x29C: a timer SuppressScriptEvent (func_00183668) drops events by;
                            // the script builtin func_00117880 sets it
    };
    AnimationStart* animationStart; // 0x2A0
    f32 f2A4;               // 0x2A4: a radius (func_0019E220 sets it with radius3CC, radius3D0 and f2A8)
    f32 boundRadius;        // 0x2A8: the radius for culling and ranges
    SoundRecord* soundRecord;   // 0x2AC: a 0x24-byte record
    u8 tint[4];             // 0x2B0: four bytes, set to 0x10 by func_00146340
    u8 tintByte4;           // 0x2B4
    u8 pad2B5[0x2B8 - 0x2B5];
    s32 keyedValueCount;    // 0x2B8
    void* keyedValues;      // 0x2BC
    T2195_5B0* keyedValueAttachment; // 0x2C0: the attachment func_0012B2F8 points at the values of a key of f2BC
    Key02* keys;            // 0x2C4: slot 16 resolves each and empties the list
    union {
        u64 flags;          // 0x2C8
        struct {
            u8 b2C8;        // 0x2C8
            s8 b2C9;        // 0x2C9: -1 at set-up
            s8 b2CA;        // 0x2CA: -1 at set-up
            u32 bits24 : 2; // set-up: 1 with a parent, 2 without (an int field: func_00125138 reads it as
                            // ld, then dsll 8, dsra32 and andi 3, the 32-bit extraction)
            u64 bits26 : 2; // set-up: 0 with a parent, 2 without
            u64 bits28 : 2; // func_00196410
            u32 bits30 : 2; // a pose follow state (func_00128598): 1 once the object is close and slow
                            // (an int field as bits24: read as ld, dsll 2, dsra32, andi 3; stored as
                            // the doubleword's ld, and, or, sd)
        };
        struct {
            u64 : 42;
            u64 mark : 4;   // bits 42..45: a level func_00159F48 compares, a mark func_0015A4F0 numbers
        };
        struct {
            u64 : 35;
            u64 onSet : 1;  // bit 35: Collider::flags538 bit 60, copied when it changes (func_001EEF90)
        };
        struct {
            u32 flagsLo;    // 0x2C8
            u32 flagsHi;    // 0x2CC: bits 32 up, read as a word (func_001AFAF8, func_001B0BE0)
        };
    };

    const Desc02* desc02() const { return (const Desc02*)desc; }
};

typedef char check_PlacedObject[sizeof(PlacedObject) == 0x2D0 ? 1 : -1];
typedef char check_ColorRecord[sizeof(ColorRecord) == 0x40 ? 1 : -1];
typedef char check_Desc02[sizeof(Desc02) == 0xD0 ? 1 : -1];

#endif

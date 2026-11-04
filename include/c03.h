// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x03 (descriptor D_00217568, 0x550 bytes), the parent of every object with collision:
// what its load method 0x1BAC30 reads before the common block is the collision prefix of
// docs/DISC.md ("Collision"). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// The fields are the ones the class's own methods (src/main/001B4000.cpp, 001B8000.cpp,
// 001BC000.cpp) and the families under it read. A 0x03 object is a part of a body: the
// topmost 0x03 object above it (C02::root, root03()) is the body, which keeps the list of its
// parts, the contacts between bodies and the flags that sum up its parts.
#ifndef C03_H
#define C03_H

#include "c02.h"

struct C03;

// A collision mesh as the loader keeps it (func_00137FB0 reads it, func_00160EA0 copies it,
// func_00160E80 clears it): the radius of its bounding sphere, its vertices and its faces
// (0x20 bytes each). The rest is the edge records and what the loader builds from them.
struct Mesh03 {
    f32 radius;             // 0x00
    s32 vertCount;          // 0x04
    void* verts;            // 0x08
    s32 faceCount;          // 0x0C
    void* faces;            // 0x10
    u8 pad14[0x24 - 0x14];
};

// A node of a mesh's BSP tree (func_00138278): its face, then its back and front children.
struct TreeNode03 {
    void* face;             // 0x00
    TreeNode03* back;       // 0x04
    TreeNode03* front;      // 0x08
};

// A mesh's BSP tree (func_00138278 reads it, func_0013E6C8 copies it).
struct Tree03 {
    s32 count;              // 0x00
    s32 count2;             // 0x04: the same count in the stream
    TreeNode03* nodes;      // 0x08
};

// A pair of values read with the collision prefix: a group (s16, u16 geometry entry) or a
// face reference (s16 geometry entry, s16 mesh).
struct Pair03 {
    s32 a;                  // 0x00
    s32 b;                  // 0x04
};

// One end of a contact: the body and the part of it that touches.
struct ContactEnd03 {
    C03* body;              // 0x00
    C03* part;              // 0x04
    u8 pad08[0x40 - 0x08];
};

// A contact between two bodies (0xD4 bytes, from the world's pool; func_001861E8 gives a
// chain of them back). Each body's table lists the contacts it is an end of.
struct Contact03 {
    ContactEnd03 end[2];    // 0x00
    u8 pad80[0x9C - 0x80];
    s32 kind;               // 0x9C: 8 and 9 are dropped when a part stops colliding (func_001B94F0)
    u8 padA0[0xC4 - 0xA0];
    f32 timer;              // 0xC4: slot 67 tells both ends' slot 65 while it is positive
    u8 padC8[0xD0 - 0xC8];
    Contact03* next;        // 0xD0
};

// A row of a body's contact table: its contacts with one other body (func_001BD558,
// func_001BD678) and where its last link is kept.
struct ContactRow03 {
    Contact03* head;        // 0x00
    ContactRow03* next;     // 0x04
    Contact03** link;       // 0x08
    C03* other;             // 0x0C: the other body
};

// A body's contact table (+0x480): the world gives one to every body (func_001DC7D0) and
// takes it back (func_001DC828); the rest of the record is the world's links.
struct Contacts03 {
    ContactRow03* head;     // 0x00
    C03* owner;             // 0x04
};

// A link between an object and a 0x03 object it is attached to (+0x4B0; func_001BA528 adds
// one, func_001BA550 removes it): slot 28 calls each owner's slot 51, slot 14 tells each
// owner's slot 13. The owner keeps its links in a list of its own (class 0x1F: +0x550).
struct Attach03 {
    C03* owner;             // 0x00
    C03* target;            // 0x04: the object whose list it is in
    Attach03* next;         // 0x08: in the target's list
    Attach03* nextOwn;      // 0x0C: in the owner's list
};

// An object a part touched (+0x540; func_001BB9D0 builds the list from the contacts, the
// world's pool takes it back with func_001DC108).
struct Touch03 {
    C03* obj;               // 0x00
    Touch03* next;          // 0x04
};

// Class 0x03's descriptor: 0x02's slots, then twenty-four more (slot n at 0x10 + 4n). Slots
// 60 to 66 are empty in 0x03; func_001BB4A0 looks for the nearest object with slot 60, 61,
// 62 or 65 set.
struct Desc03 : Desc02 {
    void* m30;                                      // 0xD0: func_001B7F78
    void* m31;                                      // 0xD4: func_001B8148
    void (*m32)(C03* self);                         // 0xD8: a body's parts changed (func_001B8540)
    void (*m33)(C03* self, Attach03* node, f32 dt); // 0xDC: called by what it is attached to (func_001BAC28)
    void* m34;                                      // 0xE0: func_001BC368
    void (*m35)(C03* self, s32* index, C03** list); // 0xE4: number the parts (func_001BC760)
    void* m36;                                      // 0xE8: func_001BC828
    void* m37;                                      // 0xEC: func_001BC978
    s32 (*m38)(C03* self, C03* other);              // 0xF0: func_001B8A08
    void* m39;                                      // 0xF4: func_00187F40
    void* m3A;                                      // 0xF8
    void* m3B;                                      // 0xFC: func_001B8B90
    void* m3C;                                      // 0x100
    void* m3D;                                      // 0x104
    void* m3E;                                      // 0x108
    void* m3F;                                      // 0x10C
    void* m40;                                      // 0x110
    void (*m41)(C03* self, Contact03* c, s32 end);  // 0x114: told of a contact (func_001B8A48)
    void* m42;                                      // 0x118
    void (*m43)(C03* self);                         // 0x11C: tell the contacts (func_001B8A48)
    void (*m44)(C03* self);                         // 0x120: keep v140 in v370 (func_001B9680)
    void (*m45)(C03* self, void* out);              // 0x124: func_001B9F30
    void* m46;                                      // 0x128: func_001BA5B0
    s32 (*m47)(C03* self);                          // 0x12C: func_001BBC30
};

struct C03 : C02 {
    Link02 link2D0;         // 0x2D0: kept by slot 9
    List01 parts;           // 0x2D8: (a body) its parts, linked at link2E4 (func_001B7C40)
    Link02 link2E4;         // 0x2E4: the link in the body's parts
    u8 pad2EC[0x2F0 - 0x2EC];
    Mat02 inertia;          // 0x2F0: the inertia tensor (the prefix; func_001B9448 scales it)
    Mat02 invInertia;       // 0x320: its inverse (func_001B9448)
    Vec02 gravity;          // 0x350: the world's (+0x1EE0) at set-up
    f32 f360;               // 0x360: 1.0 in class 0x1F
    f32 f364;               // 0x364: 1.0 in class 0x1F
    f32 mass;               // 0x368: the prefix's mass
    u8 pad36C[0x370 - 0x36C];
    Vec02 v370;             // 0x370: v140 kept by slot 68
    Mesh03 mesh;            // 0x380: the collision mesh as loaded
    Mesh03 meshCopy;        // 0x3A4: the object's own (the same, or a copy of mesh)
    void* hook;             // 0x3C8: slot 27 calls func_001BBEB8 while it is set
    f32 radius3CC;          // 0x3CC: mesh.radius at load
    f32 radius3D0;          // 0x3D0: mesh.radius at load
    u8 pad3D4[0x3F0 - 0x3D4];
    Tree03 tree;            // 0x3F0: meshCopy's tree
    s32 groupCount;         // 0x3FC
    Pair03* groups;         // 0x400: groupCount of them
    s32* nodeGroups;        // 0x404
    s32 refCount;           // 0x408
    Pair03* refs;           // 0x40C: the face references
    s32* faceStarts;        // 0x410: meshCopy.faceCount + 1 of them, with refs
    Link02 link414;         // 0x414: kept by slot 9
    u8 pad41C[0x440 - 0x41C];
    Vec02 v440;             // 0x440: in the parent's frame (slot 21 carries it over)
    s32 mode450;            // 0x450: a body sums up 3 and 3 in flag bit 54 (func_001B9AE0)
    u8 pad454[0x460 - 0x454];
    Vec02 v460;             // 0x460: in the parent's frame (slot 21 carries it over)
    s32 mode470;            // 0x470
    u8 pad474[0x480 - 0x474];
    Contacts03* contacts;   // 0x480: a body's contact table (slots 6, 7)
    u8 pad484[0x4B0 - 0x484];
    Attach03* attached;     // 0x4B0
    Contact03* contacts4B4; // 0x4B4: a body's contacts outside its table's rows (func_001BD558)
    s32 f4B8;               // 0x4B8: cleared by func_001B94F0 (on the body) and slot 9
    s32 f4BC;               // 0x4BC: -1 at set-up
    s32 index;              // 0x4C0: -1 at set-up; the part's number (slot 53)
    u8 pad4C4[0x4D0 - 0x4C4];
    Vec02 offset;           // 0x4D0: the prefix's offset (3 f32)
    s32 f4E0;               // 0x4E0: 1 in class 0x36; func_001BC4D8 walks up the parents to the first set
    C03* handler;           // 0x4E4: the nearest object (itself or above) with slot 60, 61, 62 or 65 (func_001BB4A0)
    Mesh03 mesh2;           // 0x4E8: the second mesh as loaded
    Mesh03 mesh2Copy;       // 0x50C: the object's own
    union {
        Tree03 tree2;       // 0x530: mesh2Copy's tree
        struct {
            u8 pad530[0x538 - 0x530];
            // 0x538: flags from bit 32 up (retail reaches them as one doubleword, whose low
            // word is tree2.nodes): 32-35, 36-39, 40, 41, 42, 43, 44, 47, 48, 50 (in the
            // body's parts), 51, 52, 54 (the body: v440 and v460 in mode 3), 55, 56, 63
            u64 flags538;
        };
    };
    Touch03* touching;      // 0x540: the objects it touched (func_001BB9D0)
    u8 pad544[0x550 - 0x544];

    const Desc03* desc03() const { return (const Desc03*)desc; }
    C03* root03() const { return (C03*)root; }
};

typedef char check_C03[sizeof(C03) == 0x550 ? 1 : -1];
typedef char check_Desc03[sizeof(Desc03) == 0x130 ? 1 : -1];
typedef char check_Mesh03[sizeof(Mesh03) == 0x24 ? 1 : -1];
typedef char check_Contact03[sizeof(Contact03) == 0xD4 ? 1 : -1];

#endif

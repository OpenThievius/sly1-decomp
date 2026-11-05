// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x01, the root of every object class (descriptor D_00217418, 0x34 bytes), and the
// class descriptor every object points to. Written for this project from what retail's code
// does (config/us/classes.tsv, docs/DISC.md "Objects").
//
// The fields are the ones the class's own methods (src/main/00180000.cpp, 0011C000.cpp) and its
// subclasses read; 0x0C, 0x10 and 0x24 stay padding until a reader names them.
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "common.h"

struct BaseObject;
struct World;     // the world, class 0x6C (include/c6c.h): the level every object lives in

// A list (func_00152438 sets the offset, func_00152470 appends, func_00152600 removes): the
// first and the last element, and the offset inside an element of its link, the element's
// next and previous ones.
struct List01 {
    void* head;     // 0x00
    void* tail;     // 0x04
    s32 offset;     // 0x08
};

// An entry of an object's callback list (+0x28): slot 23 (func_001832F0) adds one that calls
// the listener's slot 13 with the listener as context; slot 14 (func_00183350) calls each.
struct Callback01 {
    void (*fn)(void* ctx, s32 kind, void* arg);    // 0x00
    void* ctx;                                      // 0x04
    u8 pad08[0x10 - 0x08];
    Callback01* next;                               // 0x10
};

// The record at +0x30: another id the object answers to (func_001833F0, func_00183458).
struct Alias01 {
    u8 pad00[4];
    s32 id;         // 0x04
};

// A class descriptor (tools/classes.py): parent, id, flags, object size, then the method slots.
// Slot n is at 0x10 + 4n; the members are named by slot number until step 6 names them. The
// types are those of class 0x01's own methods (and 0x02's where 0x01 has none); a slot no
// matched method fixes stays `void*`.
struct Desc01 {
    const void* parent;                     // 0x00: the parent class's descriptor
    s32 id;                                 // 0x04
    u32 flags;                              // 0x08: 0x100 a group of objects (class 0x53)
    s32 size;                               // 0x0C
    void (*m00)(BaseObject* self);                 // 0x10: set up a new object (func_00182C18)
    void (*m01)(BaseObject* self);                 // 0x14: func_0011EDA8
    void (*m02)(BaseObject* self);                 // 0x18: into the parent's list (func_00182C80)
    void (*m03)(BaseObject* self);                 // 0x1C: out of the parent's list (func_00182D50)
    void (*m04)(BaseObject* self);                 // 0x20: func_00182D00
    void (*m05)(BaseObject* self);                 // 0x24: func_00182E88
    void (*m06)(BaseObject* self);                 // 0x28: func_00182D48 (0x02: func_001240F8)
    void (*m07)(BaseObject* self);                 // 0x2C: func_00182ED0 (0x02: func_001243E0)
    void (*m08)(BaseObject* self, BaseObject* src);       // 0x30: clone src (func_001830B0)
    void (*m09)(BaseObject* self, BaseObject* src);       // 0x34: copy from src (func_001830D8)
    void (*m0A)(BaseObject* self, void* stream);   // 0x38: load from the level stream
    void* m0B;
    void* m0C;
    void (*m0D)(BaseObject* self, s32 kind, void* arg);   // 0x44: told something (0x02: func_00127378)
    void (*m0E)(BaseObject* self, s32 kind, void* arg);   // 0x48: tell slot 13 and the callbacks (func_00183350)
    void (*m0F)(BaseObject* self);                 // 0x4C: after loading
    void (*m10)(BaseObject* self);                 // 0x50
    void (*m11)(BaseObject* self, f32 dt);         // 0x54: every frame (0x02: func_00124FC0)
    void (*m12)(BaseObject* self);                 // 0x58: 0x02: func_00125108
    void (*m13)(BaseObject* self);                 // 0x5C: 0x02: func_00125138
    void (*m14)(BaseObject* self, s32 on);         // 0x60: 0x02: func_0015FBB8
    void (*m15)(BaseObject* self, BaseObject* other);     // 0x64: make other the parent (func_00182F78)
    void (*m16)(BaseObject* self, BaseObject* other);     // 0x68: 0x02: func_00124868
    void (*m17)(BaseObject* self, BaseObject* other);     // 0x6C: listen to other (func_001832F0)
    void (*m18)(BaseObject* self, BaseObject* other);     // 0x70: let go of other (func_00183320)
    void (*m19)(BaseObject* self, void* fn, s32 ctx);     // 0x74: add a callback (func_00183290)
    void (*m1A)(BaseObject* self, s32 fn, s32 ctx);       // 0x78: remove a callback (func_001832C0)
    void (*m1B)(BaseObject* self, void* message);  // 0x7C: receive a message
};

struct BaseObject {
    const Desc01* desc;     // 0x00
    void* f04;              // 0x04: a 4-byte block func_0011BF30 makes (func_00130110); copied through func_0011BEE0 by slot 9
    s32 id;                 // 0x08: the object's id (func_001833F0)
    u8 pad0C[0x14 - 0x0C];
    World* world;             // 0x14
    BaseObject* parent;            // 0x18
    BaseObject* next;              // 0x1C: the link in the parent's list of children (PlacedObject::children)
    BaseObject* prev;              // 0x20
    BaseObject* nextById;          // 0x24: the next in its bucket of World::f1884 (func_0015A4F0 walks them)
    Callback01* callbacks;  // 0x28: slot 14 calls each
    void* f2C;              // 0x2C: looked up by func_001837E0, copied through func_0011A5B0
    Alias01* alias;         // 0x30
};

typedef char check_BaseObject[sizeof(BaseObject) == 0x34 ? 1 : -1];
typedef char check_Desc01[sizeof(Desc01) == 0x80 ? 1 : -1];

#endif

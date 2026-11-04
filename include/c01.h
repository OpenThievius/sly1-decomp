// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x01, the root of every object class (descriptor D_00217418, 0x34 bytes), and the
// class descriptor every object points to. Written for this project from what retail's code
// does (config/us/classes.tsv, docs/DISC.md "Objects").
//
// Only the fields its consolidated subclasses read are declared so far (include/c73.h); the rest of the
// 0x34 bytes stays padding until the class's own methods are consolidated.
#ifndef C01_H
#define C01_H

#include "common.h"

struct C01;
struct World;  // the level an object lives in (+0x14); its own header comes later

// A class descriptor (tools/classes.py): parent, id, flags, object size, then the method slots.
// Slot n is at 0x10 + 4n; the members are named by slot number until step 6 names them.
struct Desc01 {
    const void* parent;                     // 0x00: the parent class's descriptor
    s32 id;                                 // 0x04
    u32 flags;                              // 0x08: 0x100 a group of objects (class 0x53)
    s32 size;                               // 0x0C
    void (*m00)(C01* self);                 // 0x10: set up a new object (func_0011E580)
    void* m01;                              // 0x14
    void* m02;                              // 0x18
    void (*m03)(C01* self);                 // 0x1C
    void* m04;
    void* m05;
    void* m06;
    void* m07;
    void* m08;
    void (*m09)(C01* self, C01* src);       // 0x34: copy from src (func_001830D8)
    void (*m0A)(C01* self, void* stream);   // 0x38: load from the level stream
    void* m0B;
    void* m0C;
    void (*m0D)(C01* self, s32 kind, C01* other);  // 0x44: told about another object
    void* m0E;
    void (*m0F)(C01* self);                 // 0x4C: after loading
    void (*m10)(C01* self);                 // 0x50
    void* m11;
    void* m12;
    void* m13;
    void* m14;
    void (*m15)(C01* self, C01* other);     // 0x64: into another object's frame
    void (*m16)(C01* self, C01* other);     // 0x68: out of another object's frame
    void* m17;
    void (*m18)(C01* self, C01* other);     // 0x70: let go of other
    void* m19;
    void* m1A;
    void (*m1B)(C01* self, void* message);  // 0x7C: receive a message
};

struct C01 {
    const Desc01* desc;     // 0x00
    u8 pad04[0x14 - 0x04];
    World* world;           // 0x14
    C01* parent;            // 0x18
    u8 pad1C[0x34 - 0x1C];
};

typedef char check_C01[sizeof(C01) == 0x34 ? 1 : -1];
typedef char check_Desc01[sizeof(Desc01) == 0x80 ? 1 : -1];

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x73 (descriptor D_002178C0, 0x80 bytes), an object with a place of its own, and the
// classes under it that form groups: 0x77 (a member, 0x90), 0x78 (a group of up to eight
// members, 0xC0), 0x79 (a member with a shared record, 0xA0) and 0x7A (0xD0). Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the
// pads keep every field at its retail offset. Fields are named for what the code does with
// them; step 6 of the roadmap may rename them.
#ifndef TRANSFORM_OBJECT_H
#define TRANSFORM_OBJECT_H

#include "base_object.h"
#include "path_curve.h"

struct __attribute__((aligned(16))) Vec4_73 { f32 x, y, z, w; };
struct __attribute__((aligned(16))) Mat3_73 { Vec4_73 row[3]; };

// 0x73: position and orientation; func_001F39F8 sets the orientation to identity
// (D_002483D0), func_001F3A90/func_001F3AF0 move both into and out of the parent's frame.
struct TransformObject : BaseObject {
    u8 pad34[0x40 - 0x34];
    Vec4_73 pos;            // 0x40
    Mat3_73 rot;            // 0x50
};

// 0x74 (0x100 bytes): a set of objects of its own. Loading (slot 10, func_001F3D80) makes each
// object from the stream and has it load itself, then reads a list of ids; copying (slot 9,
// func_001F3EE0) copies the objects; starting (slot 16, func_001F3F80) gives each its parent
// and starts it.
struct TransformSet : TransformObject {
    u8 pad80[0xA0 - 0x80];
    s32 count;              // 0xA0
    BaseObject** objects;   // 0xA4
    s32 idCount;            // 0xA8
    s32* ids;               // 0xAC
    u8 padB0[0x100 - 0xB0];
};

struct MemberGroup;

// 0x77: a member of a group (class 0x78, func_001587C8 and func_00159478 fill it).
struct MemberObject : TransformObject {
    MemberGroup* group;             // 0x80
    u8 pad84[0x90 - 0x84];
};

// 0x78: a group of up to eight members; copying it copies them (func_00158980), messages
// go to every member (func_00158A80).
struct MemberGroup : MemberObject {
    s32 count;              // 0x90
    MemberObject* members[8];        // 0x94
    u8 padB4[0xC0 - 0xB4];
};

// The 0x200-byte record a 0x79 shares with its copies (func_00158C28 counts them;
// func_00158DD8 makes the object's own before a change).
struct Rec79 {
    s32 uses;               // 0x00
    u8 pad04[0x10 - 0x04];
    s32 kind;               // 0x10: 3, 4 seen
    u8 pad14[0x20 - 0x14];
    union {
        PathCurve* curve20;     // 0x20: the key-frame curve found by index (func_00158B30)
        s32 value20;        // 0x20: a value taken from another object (func_00158C60)
    };
    u8 pad24[0x7C - 0x24];
    void* target;           // 0x7C
    u8 pad80[0x120 - 0x80];
    void* link120;          // 0x120
    u8 pad124[0x188 - 0x124];
    s32 link188;            // 0x188
    u8 pad18C[0x1D8 - 0x18C];
    void* found[3];         // 0x1D8: objects named by a 0x7A's ids
    u8 pad1E4[0x200 - 0x1E4];
};

// 0x79: a member with a shared record and two object ids (-1 for none).
struct RecordMember : MemberObject {
    Rec79* rec;             // 0x90
    s32 id94;               // 0x94
    s32 id98;               // 0x98
    u8 pad9C[0xA0 - 0x9C];
};

// 0x7A: three more ids, a delay for messages, and two objects it holds.
struct HoldingMember : RecordMember {
    s32 fA0;                // 0xA0
    u8 padA4[0xAC - 0xA4];
    s32 idAC;               // 0xAC
    s32 idB0;               // 0xB0
    s32 idB4;               // 0xB4
    f32 delay;              // 0xB8
    u8 padBC[0xC0 - 0xBC];
    BaseObject* heldC0;            // 0xC0
    BaseObject* heldC4;            // 0xC4
    u8 padC8[0xD0 - 0xC8];
};

// Each class ends at its descriptor's size.
typedef char check_TransformObject[sizeof(TransformObject) == 0x80 ? 1 : -1];
typedef char check_TransformSet[sizeof(TransformSet) == 0x100 ? 1 : -1];
typedef char check_MemberObject[sizeof(MemberObject) == 0x90 ? 1 : -1];
typedef char check_MemberGroup[sizeof(MemberGroup) == 0xC0 ? 1 : -1];
typedef char check_RecordMember[sizeof(RecordMember) == 0xA0 ? 1 : -1];
typedef char check_HoldingMember[sizeof(HoldingMember) == 0xD0 ? 1 : -1];
typedef char check_Rec79[sizeof(Rec79) == 0x200 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F39F8(TransformObject* self);                       // 0x73 slot 0
void func_001F3A40(TransformObject* self, void* stream);         // 0x73 slot 10
void func_001F3A90(TransformObject* self, BaseObject* other);          // 0x73 slot 21
void func_001F3AF0(TransformObject* self, BaseObject* other);          // 0x73 slot 22
void func_001585F8(MemberObject* self);                       // 0x77 slot 16
void func_001587C0();                                // 0x77 slot 27 (empty)
void func_00158980(MemberGroup* self);                       // 0x78 slot 9
void func_001587C8(MemberGroup* self, void* stream);         // 0x78 slot 10
void func_00158A10(MemberGroup* self);                       // 0x78 slot 15
void func_00158A80(MemberGroup* self, void* message);        // 0x78 slot 27
void func_00158B00(RecordMember* self);                       // 0x79 slot 0
void func_00158C28(RecordMember* self);                       // 0x79 slot 9
void func_00158B30(RecordMember* self, void* stream);         // 0x79 slot 10
void func_00158C60(RecordMember* self);                       // 0x79 slot 15
void func_00158D38(void);                            // 0x79 slot 27 (empty)
void func_00158E10(HoldingMember* self);                       // 0x7A slot 0
void func_00158F10(HoldingMember* self, s32 kind, BaseObject* other); // 0x7A slot 13
void func_00158E48(HoldingMember* self);                       // 0x7A slot 15
void func_00158F80(HoldingMember* self, void* message);        // 0x7A slot 27
Rec79* func_00158DD8(RecordMember* self, s32 own);            // the record, made the object's own first

#endif

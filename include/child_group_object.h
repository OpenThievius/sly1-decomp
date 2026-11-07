// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x3B (descriptor D_0021B4D8, 0x690 bytes) and its children 0x3C (D_0021DF10, 0x6F0 bytes, the
// movie player's object, movie_player.cpp) and 0x3F (0x6A0 bytes, file_1D62E0.cpp). A 0x3B object
// waits until a time (+0x554), collects up to sixteen of its children of kind 0x27 (slot 16) and
// keeps a table of animation entries it starts by key (slot 58). Written for this project from
// what retail's code does (config/us/classes.tsv).
#ifndef CHILD_GROUP_OBJECT_H
#define CHILD_GROUP_OBJECT_H

#include "collider.h"

struct __attribute__((aligned(16))) Quad3B {
    s32 a, b, c, d;
};

struct Pair3B {
    s32 a, b;
};

// A 0x30-byte entry of the table at +0x68C (func_0013B9D8 finds the one with the key).
struct Entry3B {
    u8 pad00[0x10];
    void* data;             // 0x10
    u8 pad14[0x0C];
    f32 value;              // 0x20
    s32 key;                // 0x24
    u8 pad28[8];
};

struct ChildGroupObject : Collider {
    s32 f550;               // 0x550: 0 at set-up; a message of kind 10 starts the clock while it is 0
    f32 f554;               // 0x554: FLT_MAX at set-up; the clock plus a delay (func_0013BE00)
    u8 pad558[0x55C - 0x558];
    f32 f55C;               // 0x55C: 200.0
    f32 f560;               // 0x560: 200.0
    u8 pad564[0x568 - 0x564];
    f32 f568;               // 0x568: 800.0
    Pair3B f56C;            // 0x56C: 50.0, 5000.0
    f32 f574;               // 0x574: 5000.0
    s32 count;              // 0x578: the objects of arr (at most 16)
    s32 arr[16];            // 0x57C: children of kind 0x27 that slot 16 found
    void* member5BC;        // 0x5BC: func_00159478 finds it (slot 10)
    u8 pad5C0[0x5D0 - 0x5C0];
    Quad3B f5D0;            // 0x5D0
    Pair3B f5E0;            // 0x5E0
    u8 pad5E8[0x5F0 - 0x5E8];
    Quad3B f5F0;            // 0x5F0
    Pair3B f600;            // 0x600
    u8 pad608[0x674 - 0x608];
    s32 f674;               // 0x674: 1 at set-up
    s32 f678;               // 0x678: 1 at set-up
    s32 f67C;               // 0x67C: 0 at set-up
    void* slot;             // 0x680: a copy of the other's (func_0018D568, 0x24 bytes; slot 9)
    void* active;           // 0x684
    s32 entryCount;         // 0x688
    Entry3B* entries;       // 0x68C: entryCount of them (0xC0 bytes allocated when active)
};

// The movie player's object (movie_player.cpp): the lists of objects it asks about (slot 56),
// the movie's data (+0x6B4) and a flag.
struct ContactListObject : ChildGroupObject {
    u8 pad690[0x6B4 - 0x690];
    void* f6B4;             // 0x6B4: given back by slot 7 (func_0012E760)
    s32 ready;              // 0x6B8: 1 at set-up (slot 0); slot 27 tests it
    s32 count6BC;           // 0x6BC: the objects of items6C0
    void* items6C0[4];      // 0x6C0
    s32 count6D0;           // 0x6D0: the ids of items6D4
    void* items6D4[4];      // 0x6D4
    void* f6E4;             // 0x6E4
    u8 pad6E8[0x6F0 - 0x6E8];
};

// 0x3F, the player's stand-in: SwapInPlayerStandIn puts it in the place of an attached object.
struct StandIn : ChildGroupObject {
    f32 f690;               // 0x690: the clock when SwapInPlayerStandIn started it
    s32 f694;               // 0x694: 1 while it runs
    u8 pad698[0x6A0 - 0x698];
};

typedef char check_ChildGroupObject[sizeof(ChildGroupObject) == 0x690 ? 1 : -1];
typedef char check_ContactListObject[sizeof(ContactListObject) == 0x6F0 ? 1 : -1];
typedef char check_StandIn[sizeof(StandIn) == 0x6A0 ? 1 : -1];

void InitChildGroupObject(ChildGroupObject* self);                          // slot 0
void CopyChildGroupObject(ChildGroupObject* self, ChildGroupObject* other);              // slot 9
void LoadChildGroupObject(ChildGroupObject* self);                          // slot 10
void StartChildGroupObject(ChildGroupObject* self);                          // slot 16
void RunKeyedChildGroupEntry(ChildGroupObject* self, s32 key, s32 a2, s32 a3, s32 a4, void* arg5);   // slot 58
void HandleChildGroupObjectContact(ChildGroupObject* self);                          // slot 60
void InitContactListObject(ContactListObject* self);                          // slot 0
void LoadContactListObject(ContactListObject* self);                          // slot 10
void UnregisterContactListObject(ContactListObject* self);                          // slot 7
void MoveContactListObject(ContactListObject* self, void* b, f32 x);          // slot 27
void ApplyContactListAttachments(ContactListObject* self, void* in1, void* in2);    // slot 36
s32 TestContactListMayContact(ContactListObject* self, void* key);                // slot 56
s32 TestStandInMayContact(StandIn* self, s32 value);                // slot 56
void StopStandIn(StandIn* self);                          // slot 60

#endif

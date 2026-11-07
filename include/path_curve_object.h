// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6E (descriptor D_00217740, 0x38 bytes), a path curve object: an object that keeps a
// key-frame curve (include/path_curve.h) read from the level stream and moves it with its frame,
// and the four classes under it: 0x6F (0x60), 0x70 (0x70), 0x71 (0x5C) and 0x72 (0x40).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the
// pads keep every field at its retail offset. Fields are named for what the code does with
// them.
#ifndef PATH_CURVE_OBJECT_H
#define PATH_CURVE_OBJECT_H

#include "base_object.h"
#include "path_curve.h"

// Eight bytes that each subclass keeps through a copy (slot 9: saved, the parent's copy,
// restored); retail moves them as one unaligned doubleword.
struct __attribute__((packed)) PathCurveKeptBits { u64 bits; };

// 0x6E: LoadPathCurveObject makes the curve of the kind the stream names and lets it read
// itself (slot 0 of its table); ReparentPathCurveObject tells it (slot 4) the frames of the
// old parent and of the new one.
struct PathCurveObject : BaseObject {
    PathCurve* curve;           // 0x34
};

// 0x6F, a target curve: registers itself in the list D_002626E8 (g_targetCurveList, slots 6
// and 7); an object id (-1 for none) resolved after loading (slot 15) into an object whose
// 0x398 it clears.
struct TargetCurve : PathCurveObject {
    PathCurveKeptBits keep; // 0x38
    u8 pad40[0x44 - 0x40];
    s32 targetId;           // 0x44: -1 for none
    void* target;           // 0x48: the object targetId names
    s32 f4C;                // 0x4C: 1 at setup
    s32 f50;                // 0x50: 3 at setup
    u8 pad54[0x58 - 0x54];
    f32 f58;                // 0x58: the largest float at setup (D_0024A794)
    u8 pad5C[0x60 - 0x5C];
};

struct __attribute__((aligned(16))) TargetVectorQuad { u8 b[16]; };

// 0x70, a target vector: registers itself in the list D_00269BA8 (g_targetVectors, slots 6
// and 7); a 16-byte value set from D_00248D00 (the unit X vector), three integers, a float
// and an object id resolved when it starts.
struct TargetVector : PathCurveObject {
    PathCurveKeptBits keep; // 0x38
    TargetVectorQuad q40;   // 0x40
    s32 f50;                // 0x50: 8 at setup
    s32 f54;                // 0x54: 9 at setup
    s32 f58;                // 0x58: -1 at setup
    f32 f5C;                // 0x5C: D_0024B650 at setup
    u8 pad60[0x64 - 0x60];
    s32 targetId;           // 0x64: -1 for none
    s32 target;             // 0x68: what func_0015A418 returns for targetId
    u8 pad6C[0x70 - 0x6C];
};

// 0x71: registers itself in the world's list at +0x1C90 (slots 6 and 7); a float and an object
// id resolved when it starts. Its role is not known yet, so it keeps its id.
struct C71 : PathCurveObject {
    PathCurveKeptBits keep; // 0x38
    u8 pad40[0x4C - 0x40];
    f32 f4C;                // 0x4C: D_0024C8C4 at setup
    u8 pad50[0x54 - 0x50];
    s32 targetId;           // 0x54: -1 for none
    s32 target;             // 0x58: what func_0015A418 returns for targetId
};

// 0x72: registers itself in the world's list at +0x1C9C (slots 6 and 7, RegisterListedKeepObject)
// and has only the eight bytes it keeps.
struct ListedKeepObject : PathCurveObject {
    PathCurveKeptBits keep; // 0x38
};

// Each class ends at its descriptor's size.
typedef char check_PathCurveObject[sizeof(PathCurveObject) == 0x38 ? 1 : -1];
typedef char check_TargetCurve[sizeof(TargetCurve) == 0x60 ? 1 : -1];
typedef char check_TargetVector[sizeof(TargetVector) == 0x70 ? 1 : -1];
typedef char check_C71[sizeof(C71) == 0x5C ? 1 : -1];
typedef char check_ListedKeepObject[sizeof(ListedKeepObject) == 0x40 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001B2840(PathCurveObject* self, void* stream);        // 0x6E slot 10
void func_001B28A8(PathCurveObject* self, BaseObject* other);   // 0x6E slot 21
void func_00169CD8(TargetCurve* self);                          // 0x6F slot 0
void func_00169D20(TargetCurve* self);                          // 0x6F slot 6
void func_00169D58(TargetCurve* self);                          // 0x6F slot 7
void func_00169DD8(TargetCurve* self);                          // 0x6F slot 9
void func_00169D90(TargetCurve* self);                          // 0x6F slot 15
void func_00191F08(TargetVector* self);                         // 0x70 slot 0
void func_00191F68(TargetVector* self);                         // 0x70 slot 6
void func_00191FA0(TargetVector* self);                         // 0x70 slot 7
void func_00192020(TargetVector* self);                         // 0x70 slot 9
void func_00191FD8(TargetVector* self);                         // 0x70 slot 16
void func_0019AF00(C71* self);                                  // 0x71 slot 0
void func_0019AF38(C71* self);                                  // 0x71 slot 6
void func_0019AF70(C71* self);                                  // 0x71 slot 7
void func_0019AFF0(C71* self);                                  // 0x71 slot 9
void func_0019AFA8(C71* self);                                  // 0x71 slot 16
void func_00180EB0(ListedKeepObject* self);                     // 0x72 slot 6
void func_00180EE8(ListedKeepObject* self);                     // 0x72 slot 7
void func_00180F20(ListedKeepObject* self);                     // 0x72 slot 9

#endif

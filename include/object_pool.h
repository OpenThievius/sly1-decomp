// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8C (descriptor D_0021E2B8, 0x170 bytes), a direct child of the root class 0x01, and
// no class under it. Written for this project from what retail's code does
// (config/us/classes.tsv). Its own methods are func_001A7FE8 (slot 0), func_001A80E0 (7),
// func_001A84C8 (9), func_001A8590 (16) and func_001A86F8 (20); the functions
// func_001B4AA0..func_001B4B48 that the table lists after slot 27 take other objects (records
// and nodes of other classes) and are not this class's.
//
// Fields follow the root's and end at the descriptor's size; pads keep each at its retail offset.
#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "base_object.h"

// 0x3C: a record shared with the object this one was copied from (func_001A84C8).
struct Sub8C {
    s32 f0;                 // 0x0
    s32 f4;                 // 0x04: nonzero while the record is lent out
    s32 f8;                 // 0x08
    s32 fC;                 // 0xC
    s32 f10;                // 0x10
    void* f14;              // 0x14: the object it was lent to
};

// 0x110: three values func_001A7FE8 resets (0, 1.0f, 0).
struct V8C {
    s32 a;
    f32 b;
    s32 c;
};

struct ObjectPool : BaseObject {
    s32 count;              // 0x34: number of 0x14-byte items (func_001A84C8)
    void* items;            // 0x38
    Sub8C* sub;             // 0x3C
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    s32 f48;                // 0x48: the item chosen (func_001A8AF8); func_001A8C50 tests it, func_001A93C8 clears it
    s32 id4C;               // 0x4C: object ids, -1 for none (set by func_001A7FE8,
    s32 id50;               // 0x50  looked up by func_001A8590)
    s32 id54;               // 0x54
    s32 id58;               // 0x58
    void* f5C;              // 0x5C: objects found from the ids
    void* f60;              // 0x60
    void* f64;              // 0x64
    void* f68;              // 0x68
    u8 pad6C[0xD8 - 0x6C];
    f32 fD8;                // 0xD8
    u8 padDC[0xE0 - 0xDC];
    void* fE0;              // 0xE0
    void* fE4;              // 0xE4
    u8 padE8[0x110 - 0xE8];
    V8C v110;               // 0x110
    u8 pad11C[0x120 - 0x11C];
    s32 f120;               // 0x120
    f32 f124;               // 0x124
    u8 pad128[0x144 - 0x128];
    f32 f144;               // 0x144
    u8 pad148[0x160 - 0x148];
    void* f160;             // 0x160
    void* f164;             // 0x164
    s32 f168;               // 0x168: set once the ids are looked up
    u8 pad16C[0x170 - 0x16C];
};

typedef char check_ObjectPool[sizeof(ObjectPool) == 0x170 ? 1 : -1];

void func_001A7FE8(ObjectPool* self);                  // slot 0
void func_001A80E0(ObjectPool* self);                  // slot 7
void func_001A84C8(ObjectPool* self, ObjectPool* other);      // slot 9
void func_001A8590(ObjectPool* self);                  // slot 16
void func_001A86F8(ObjectPool* self, s32 flag);        // slot 20

#endif

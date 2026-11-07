// SPDX-License-Identifier: AGPL-3.0-or-later
// A property descriptor: one 0x20-byte record of D_002505D8, which func_00109488 fills at
// startup (src/main/object_host_functions.cpp). ApplyPropertyRecord (func_0011E680) reads a
// value of the record's type from a stream and stores it in the object at the record's offset,
// or hands it to the record's setter; ApplyObjectClassDefaults (func_0011EDA8) applies the
// records flagged 0x800 from the four bytes at +8. Written for this project from what retail's
// code does.
#ifndef PROPERTY_DESCRIPTOR_H
#define PROPERTY_DESCRIPTOR_H

#include "common.h"

struct ScriptValue;

struct PropertyDescriptor {
    s32 type;               // 0x00: the kind of value (func_0011E680 switches on it)
    u32 flags;              // 0x04: 0x800 a class default, read from value (func_0011EDA8)
    u8 value[4];            // 0x08: the default value
    void (*setter)(ScriptValue* ret, void* obj, s32 n, ScriptValue* args); // 0x0C: given the values read
    u8 pad10[4];
    s32 argCount;           // 0x14: how many values the setter takes
    s32 offset;             // 0x18: of the field (or of the method slot) in the target
    void* (*target)(void* obj, s32 one); // 0x1C: the object holding the field, when set
};

typedef char check_PropertyDescriptor[sizeof(PropertyDescriptor) == 0x20 ? 1 : -1];

#endif

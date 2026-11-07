// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x86 (descriptor D_00219460, 0x44 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef VALUE_LIST_OBJECT_H
#define VALUE_LIST_OBJECT_H

#include "base_object.h"

// 0x86: registers itself in its level (func_001EE900) and loads a list of values
// (func_001EE930).
struct ValueListObject : BaseObject {
    s32 count34;            // 0x34: filled by func_00138398 with f38
    void* data38;           // 0x38
    s32 valueCount;         // 0x3C: number of values
    s32* values;            // 0x40
};

typedef char check_ValueListObject[sizeof(ValueListObject) == 0x44 ? 1 : -1];

void InitValueListObject(ValueListObject* self);                 // slot 0
void LoadValueList(ValueListObject* self, void* stream);   // slot 10

#endif

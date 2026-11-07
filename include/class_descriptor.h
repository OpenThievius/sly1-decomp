// SPDX-License-Identifier: AGPL-3.0-or-later
// A class descriptor (tools/classes.py, config/us/classes.tsv): the parent's descriptor, the class
// id, its flags, the size of its objects, then its N method slots, each its own method, one it
// inherits, or zero. The descriptors are in src/main/class_descriptors.cpp; D_00247448
// (src/main/global_tables.cpp) lists them by class id.
#ifndef CLASS_DESCRIPTOR_H
#define CLASS_DESCRIPTOR_H

#include "common.h"

typedef void (*Fn_Table)();

template <int N> struct ClassDescriptor {
    const void* parent;     // 0x00
    s32 id;                 // 0x04
    s32 flags;              // 0x08
    s32 size;               // 0x0C
    Fn_Table methods[N];    // 0x10
};

#endif

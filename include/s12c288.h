// SPDX-License-Identifier: AGPL-3.0-or-later
// A key and an object, the fourth parameter of func_0012C288 (0012C000.cpp): func_00124CC0
// builds one at the start of its frame (Frame_124CC0), and one sits at C08+0xBEC. Written for
// this project from what retail's code does (build/swarm/st3/groups.tsv, g915).
#ifndef S12C288_H
#define S12C288_H

#include "common.h"

struct S12C288 {
    s32 key;                // 0x00
    void* val;              // 0x04: an object (Host_12C288 in func_0012C288, the caller's self in func_00124CC0)
};


#endif

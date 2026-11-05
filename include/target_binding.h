// SPDX-License-Identifier: AGPL-3.0-or-later
// A target key bound to an object: the fourth parameter of func_0012C288 (0012C000.cpp): func_00124CC0
// builds one at the start of its frame (Frame_124CC0), and one sits at Agent+0xBEC. Written for
// this project from what retail's code does (build/swarm/st3/groups.tsv, g915).
#ifndef TARGET_BINDING_H
#define TARGET_BINDING_H

#include "common.h"

struct TargetBinding {
    s32 key;                // 0x00
    void* object;           // 0x04: the object a track with that key acts on, an object (Host_12C288 in func_0012C288, the caller's self in func_00124CC0)
};


#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// A value range, two floats: func_001EB050 says whether a value is inside it, func_001EB080 asks
// it of each range of an array, func_001EB0F8 clamps a value to it (Clamp is the same clamp
// inlined, as trail_ribbon.cpp has it). Written for this project from what retail's code does.
//
// Ranges sit at Agent+0x738, in D_002754C8, D_00275C60 (the clamp of the D_002623C8 record's
// word 0x10, pooled_object.cpp) and eight times in PadRecord (g262c70.h). placed_object.cpp copies
// D_00275C60 as one unaligned doubleword (U64_12A678, U64_12A748): that view stays the file's.
#ifndef VALUE_RANGE_H
#define VALUE_RANGE_H

#include "common.h"

f32 RandomFloatInRange(f32 lo, f32 hi);

struct ValueRange {
    f32 lo;                 // 0x00
    f32 hi;                 // 0x04

    f32 Clamp(f32 v)
    {
        f32 l = lo;
        f32 h = hi;
        if (v < l)
            v = l;
        else if (h < v)
            v = h;
        return v;
    }

    // The same clamp with its result in a variable of its own and both ends loaded before the
    // compare (func_00196B78, func_001A2830): a different code from Clamp's, which changes v.
    f32 Limit(f32 v) const
    {
        f32 l = lo;
        f32 h = hi;
        f32 r;
        if (v < l)
            r = l;
        else if (h < v)
            r = h;
        else
            r = v;
        return r;
    }

    // A random value in the range (func_001EAAE0). Inlined, it reads hi through its own
    // this pointer, an address CSE and GCSE do not see as the caller's: a test of hi just before
    // keeps its value to its block (local-alloc's lowest free register), and reload's cse makes
    // the call's load a copy of it (func_001A8C90's spin: lwc1 $f1, then mov.s $f13,$f1).
    f32 Random() const { return RandomFloatInRange(lo, hi); }
};

typedef char check_ValueRange[sizeof(ValueRange) == 8 ? 1 : -1];

extern ValueRange D_002754C8;      // path_follower.cpp defines it; file_1E88D0.cpp
extern ValueRange g_unitRange;      // file_1E88D0.cpp defines it (and D_00275C68 after it); placed_object.cpp, pooled_object.cpp, trail_ribbon.cpp

#endif

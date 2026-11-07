// SPDX-License-Identifier: AGPL-3.0-or-later
// The four entries of D_00261D40 (file_14EE40.cpp defines them: { 0.8, 2, 5 } ... { 0, 50, 100 }):
// a threshold and the two ends of a range of counts, which func_00151A88 (file_14EE40.cpp) takes by the first that the
// value reaches. Written for this project from what retail's code does (globals.tsv). The
// label runs 0x30 bytes: four entries.
#ifndef THRESHOLD_RANGE_H
#define THRESHOLD_RANGE_H

#include "common.h"

struct ThresholdRange {
    f32 threshold;         // 0x00: the first entry whose threshold is <= the value is taken
    s32 low;               // 0x04: the lower bound of the count range
    s32 high;              // 0x08: the upper bound
};

typedef char check_ThresholdRange[sizeof(ThresholdRange) == 0xC ? 1 : -1];

extern ThresholdRange D_00261D40[4];   // file_14EE40.cpp

#endif

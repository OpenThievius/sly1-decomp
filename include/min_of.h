// SPDX-License-Identifier: AGPL-3.0-or-later
// The min of record.
#ifndef MIN_OF_H
#define MIN_OF_H

#include "common.h"

struct MinOf {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

#endif

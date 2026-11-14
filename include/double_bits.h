// SPDX-License-Identifier: AGPL-3.0-or-later
// The double bits record.
#ifndef DOUBLE_BITS_H
#define DOUBLE_BITS_H

#include "common.h"

union DoubleBits {
    double d;
    u64 u;
};

#endif

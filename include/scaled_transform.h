// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x50-byte transform BuildPlacedObjectTransform makes (func_0016A178's callers scale it before
// ApplyPlacedObjectTransform draws with it): its two scale factors are at 0x40 and 0x44. Written for
// this project from what retail's code does.
#ifndef SCALED_TRANSFORM_H
#define SCALED_TRANSFORM_H

#include "common.h"

struct __attribute__((aligned(16))) ScaledTransform {
    u8 pad00[0x40];
    f32 scaleA;             // 0x40
    f32 scaleB;             // 0x44
    u8 pad48[0x50 - 0x48];
};

#endif

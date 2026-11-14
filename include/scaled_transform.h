// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x50-byte transform BuildPlacedObjectTransform makes (func_0016A178's callers scale it before
// ApplyPlacedObjectTransform and DrawCollider draw with it): a matrix of four quads, then the two
// fades a part is drawn with at 0x40 and 0x44 (the outer one is also the fade a beam is drawn
// with). Written for this project from what retail's code does.
#ifndef SCALED_TRANSFORM_H
#define SCALED_TRANSFORM_H

#include "common.h"
#include "shapes.h"

struct __attribute__((aligned(16))) ScaledTransform {
    Quad16 q[4];
    f32 outerFade;          // 0x40
    f32 innerFade;          // 0x44
    f32 f48;
    f32 f4c;
};

#endif

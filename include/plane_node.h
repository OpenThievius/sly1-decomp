// SPDX-License-Identifier: AGPL-3.0-or-later
// One plane of a plane tree (the point graph's triangle tree, the value list's mask tree): a
// normal and an offset, and the two children, below and above the plane. A child is a node's
// address, or a leaf (a triangle, or a mask with bit 31 set).
#ifndef PLANE_NODE_H
#define PLANE_NODE_H

#include "common.h"
#include "placed_object.h"

struct PlaneNode {
    Vec4 normal;           // 0x00
    f32 offset;             // 0x10
    sptr below;             // 0x14: the child on the plane's near side
    sptr above;             // 0x18
};

#endif

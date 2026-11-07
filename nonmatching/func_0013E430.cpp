// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 520/544 (95.6%), checked 2026-11-07
// NEAR: right control flow and the switches (cases in ascending order); only two scheduling differences remain: retail loads the plane offset (lwc1) after the dot product's four VU0 instructions where ours hoists it before them, and then the first call's mov.s/move arguments swap. Tried the dot and the offset in six statement orders.
#include "common.h"
#include "zone_collider.h"
#include "trigger_zone.h"
#include "vu0.h"
extern f32* D_002613D0[4];
extern f32* D_002613E0[3];

// A node of a plane tree: its plane and the two sides (the boxes D_002613D0 and D_002613E0 are
// such nodes, with a box for a plane); func_0013E430 appends the nodes of the pieces it cuts.
struct PlaneTreePlane {
    Vec02 normal;           // 0x00
    f32 offset;             // 0x10
};

struct PlaneTreeNode {
    PlaneTreePlane* plane;  // 0x00
    PlaneTreeNode* below;   // 0x04
    PlaneTreeNode* above;   // 0x08
};

struct PlaneTreeOutput {
    PlaneTreeNode* cur;     // 0x00: the next node to write
};

s32 func_0013E430(PlaneTreeNode* node, Vec02* p, PlaneTreeOutput* out, f32 eps)
{
    f32 d;
    s32 result;
    while (node != 0) {
        PlaneTreePlane* pl = node->plane;
        f32 dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*p), Vu0::Q(pl->normal)));
        d = dot - pl->offset;
        if (eps < d) {
            node = node->above;
            continue;
        }
        if (d < -eps) {
            node = node->below;
            continue;
        }
        s32 lo;
        s32 hi;
        PlaneTreeNode* loNode;
        PlaneTreeNode* hiNode;
        if (node->below != 0) {
            lo = func_0013E430(node->below, p, out, eps);
            loNode = out->cur - 1;
        } else {
            lo = 0;
        }
        if (node->above != 0) {
            hi = func_0013E430(node->above, p, out, eps);
            hiNode = out->cur - 1;
        } else {
            hi = 1;
        }
        if (lo == hi && hi != 2) {
            result = hi;
            goto done;
        }
        out->cur->plane = node->plane;
        switch (lo) {
        case 0:
            out->cur->below = 0;
            break;
        case 1:
            out->cur->below = (PlaneTreeNode*)D_002613D0;
            break;
        case 2:
            out->cur->below = loNode;
            break;
        }
        switch (hi) {
        case 0:
            out->cur->above = (PlaneTreeNode*)D_002613E0;
            break;
        case 1:
            out->cur->above = 0;
            break;
        case 2:
            out->cur->above = hiNode;
            break;
        }
        result = 2;
        out->cur++;
        goto done;
    }
    result = eps < d;
done:
    return result;
}


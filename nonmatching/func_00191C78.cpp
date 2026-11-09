// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 495/500 (99.0%), checked 2026-11-09
// NEAR (w10, 2026-11-09): the triangle as a record of three corner pointers (GraphTri) makes the corner loads struct members (MEM_IN_STRUCT_P), which no longer wait for the Scalar slot stores (fixed_scalar_and_varying_struct_p): the whole weighted sum and its registers now match (26 differing words to 3). Still differs: the second walk loads the count straight into a2, where retail loads it into v0 for the pretest and copies it (move a2,v0) in the preheader. Ours: cse_around_loop (cse.c) replaces the bottom test's load with the pretest's register and gcse cprop folds the copy; retail's shape is the load left in the loop, hoisted by loop.c and turned into a copy by cse2, so something in retail's second walk stops cse_around_loop (a label or call in the body, a jump CSE altered, a second use of the loop-top label, or a store between the pretest and the loop). Tried: while form (same), continue/break (worse), an inline area helper (frame shrinks), PointGraph& g (worse).
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "point_graph_object.h"

f32 RandomFloatInRange(f32 lo, f32 hi);

// A triangle of the graph (12 bytes): its three corners.
struct GraphTri { GraphPoint* corner[3]; };

// A random point on the graph's triangles: one picked by its area, then a point inside it.
void func_00191C78(PointGraphObject* self, Vec02* out)
{
    Vec02 e1;
    Vec02 e2;
    GraphTri* t;
    f32 total = 0.0f;
    s32 i;
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphTri*)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(*t->corner[1]), Vu0::Q(*t->corner[0]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(*t->corner[2]), Vu0::Q(*t->corner[0]));
        total += e1.x * e2.y - e1.y * e2.x;
    }
    f32 r = RandomFloatInRange(0.0f, total);
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphTri*)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(*t->corner[1]), Vu0::Q(*t->corner[0]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(*t->corner[2]), Vu0::Q(*t->corner[0]));
        r -= e1.x * e2.y - e1.y * e2.x;
        if (r < 0.0f) {
            break;
        }
    }
    f32 u = RandomFloatInRange(0.0f, 1.0f);
    f32 v = RandomFloatInRange(0.0f, 1.0f);
    if (1.0f < u + v) {
        u = 1.0f - u;
        v = 1.0f - v;
    }
    u128 su = Vu0::Scalar(u);
    u128 a = Vu0::Q(*t->corner[0]);
    u128 sv = Vu0::Scalar(v);
    u128 b = Vu0::Q(*t->corner[1]);
    u128 sw = Vu0::Scalar(1.0f - u - v);
    u128 c = Vu0::Q(*t->corner[2]);
    Vu0::Q(*out) = Vu0::MulXSum3(a, su, b, sv, c, sw);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 425/500 (85.0%), checked 2026-11-08
// NEAR (night-low1, 2026-11-08): one index variable for both area walks gives retail's first walk (the triangle pointer in a0, the count in a1): 32 differing words to 26. Still differs: the second walk loads the count straight into a2 (retail into v0, then move a2,v0 in the preheader), and at the end retail gives the second weight vf5 and the first corner vf6 (here vf6 and vf5), with the corners' pointer loads earlier. Tried (this pass): Vec values inline (the corner and weight registers right, the third weight vf3 and the pointer load hoisted over the branch: 28), Vec locals (26), the weights first (30, 37), the count in a local (same). Before: the weights and corners as locals in the order u, a, v, b, w, c is the closest; the call with everything inline, the three weights first, and the weights before the corners are further.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "point_graph_object.h"

f32 RandomFloatInRange(f32 lo, f32 hi);

// A random point on the graph's triangles: one picked by its area, then a point inside it.
void func_00191C78(PointGraphObject* self, Vec02* out)
{
    Vec02 e1;
    Vec02 e2;
    GraphPoint** t;
    f32 total = 0.0f;
    s32 i;
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphPoint**)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(*t[1]), Vu0::Q(*t[0]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(*t[2]), Vu0::Q(*t[0]));
        total += e1.x * e2.y - e1.y * e2.x;
    }
    f32 r = RandomFloatInRange(0.0f, total);
    for (i = 0; i < self->graph.triCount; i++) {
        t = (GraphPoint**)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(*t[1]), Vu0::Q(*t[0]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(*t[2]), Vu0::Q(*t[0]));
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
    u128 a = Vu0::Q(*t[0]);
    u128 sv = Vu0::Scalar(v);
    u128 b = Vu0::Q(*t[1]);
    u128 sw = Vu0::Scalar(1.0f - u - v);
    u128 c = Vu0::Q(*t[2]);
    Vu0::Q(*out) = Vu0::MulXSum3(a, su, b, sv, c, sw);
}

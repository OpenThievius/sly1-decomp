// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 419/500 (83.8%), checked 2026-11-07
// NEAR: the two area walks, the random picks and the MulXSum3 of the corners are retail's. Still differs in registers: in the first walk retail keeps the triangle pointer in a0 and the count in a1 (here the other way), and at the end retail gives the second weight vf5 and the first corner vf6 (here vf6 and vf5), with the corners' loads interleaved differently. The weights and corners as locals in the order u, a, v, b, w, c is the closest; the call with everything inline, the three weights first, and the weights before the corners are further.
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
    for (s32 i = 0; i < self->graph.triCount; i++) {
        t = (GraphPoint**)(self->graph.tris + i * 12);
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(*t[1]), Vu0::Q(*t[0]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(*t[2]), Vu0::Q(*t[0]));
        total += e1.x * e2.y - e1.y * e2.x;
    }
    f32 r = RandomFloatInRange(0.0f, total);
    for (s32 i = 0; i < self->graph.triCount; i++) {
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

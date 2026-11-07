// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 340/348 (97.7%), checked 2026-11-07
#include "common.h"
#include "point_graph_object.h"
#include "placed_object.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-b): all but four instructions. Retail loads the link's two point
// pointers [0] then [1] into v0 and v1 before the weights; here [1] is loaded first (or, with
// the locals the other way round, into the other registers), and the second weight's store
// comes before the first row's lqc2.

s32 FindPointGraphTriangleWithin(GraphFace* faces, Vec02* p);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);

// p, when it is outside every face, moved to the nearest point of the nearest link (each link
// taken at p's height); otherwise p itself.
void SnapPointToPointGraph(PointGraph* self, Vec02* p, Vec02* out)
{
    if (FindPointGraphTriangleWithin(self->faces, p) != 0) {
        *out = *p;
        return;
    }
    f32 best = 3.4028235e38f;
    f32 bestT = -1.0f;
    GraphPoint** nearest = 0;
    for (s32 i = 0; i < self->nA; i++) {
        GraphPoint** link = (GraphPoint**)(self->links + i * 12);
        Vec02 a = *(Vec02*)link[0];
        Vec02 b = *(Vec02*)link[1];
        f32 t;
        f32 d;
        a.z = p->z;
        b.z = p->z;
        MeasurePointToSegment(p, &a, &b, &t, &d);
        if (d < best) {
            bestT = t;
            nearest = link;
            best = d;
        }
    }
    Vec02* a = (Vec02*)nearest[0];
    Vec02* b = (Vec02*)nearest[1];
    Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(*a), Vu0::Scalar(1.0f - bestT), Vu0::Q(*b), Vu0::Scalar(bestT));
}

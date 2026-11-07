// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 356/372 (95.7%), checked 2026-11-07
// NEAR: right instructions and registers; the lwc1 of the plane's distance (16(v0)) is scheduled right after the plane's lqc2, ahead of the dot product's four VU0 instructions, where retail has it after them (just before the qmfc2). Tried the distance read as a separate statement, a temp, a struct field and a reordered expression.
#include "common.h"
#include "c8b.h"
#include "placed_object.h"
#include "vu0.h"

struct TreePlane {
    Vec02 normal;
    f32 dist;
};

u8* func_0019CF68(C8B* self, Tri8B* node, Vec02* pt)
{
    if (node == 0) {
        node = self->fD8;
    }
    for (;;) {
        TreePlane* plane = (TreePlane*)node->a;
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*pt), Vu0::Q(plane->normal))) - plane->dist;
        if (d < -0.0001f) {
            if (node->b == 0) {
                return self->fDC[node - self->fD8].a;
            }
            node = (Tri8B*)node->b;
        } else if (d > 0.0001f) {
            if (node->c == 0) {
                return self->fDC[node - self->fD8].b;
            }
            node = (Tri8B*)node->c;
        } else {
            u8* r;
            if (node->c == 0) {
                r = self->fDC[node - self->fD8].b;
            } else {
                r = func_0019CF68(self, (Tri8B*)node->c, pt);
            }
            if (r != 0) {
                return r;
            }
            if (node->b == 0) {
                return self->fDC[node - self->fD8].a;
            }
            node = (Tri8B*)node->b;
        }
    }
}

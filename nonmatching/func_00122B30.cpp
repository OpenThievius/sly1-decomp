// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 194/280 (69.3%), checked 2026-11-07
// NEAR: GetIdentityPoseRotation. The matrix product (a, the identity pose's matrix, as values; b, the rotation just given, in place) and the rotated spin are retail's, but retail allocates the registers differently (the product takes vf5, vf2, vf1 and vf7, vf8, vf3, the spin vf3, vf4, vf6, vf1, vf2; ours 1, 4, 2 and 3, 5, 6) and stores the three dead rows of the product (0x30 to 0x50 of the frame) late, between and after the spin's sequence, where ours stores them with the rows of the result. Putting the spin first, storing x, y, z after the three sequences, and the product written out inline did not change it.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "anim_curve.h"
#include "globals.h"
#include "buffered_stream.h"
#include "script_value.h"

void GetOwnerRotation(Attachment* self, Mat02* out1, Vec02* out2);

// The product a b of two rotations into out: b's rows each rotated by a, the rows of a read once.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

void GetIdentityPoseRotation(T2195_588* self, f32 t, Mat02* rot, Vec02* vec)
{
    Attachment* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode1;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getRot(p, t, rot, vec);
    } else {
        GetOwnerRotation(self, rot, vec);
    }
    MulRotation(rot, self->rot, *rot);
    Vu0::Q(*vec) = Vu0::Add(Vu0::Rotate(self->rot, Vu0::Q(*vec)), Vu0::Q(self->v70));
}

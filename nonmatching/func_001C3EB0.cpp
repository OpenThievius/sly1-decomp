// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 132/180 (73.3%), checked 2026-11-08
#include "common.h"
#include "placed_object.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 3 retry): FromFloatAt for the scale, kept in a u128 across the test,
// and Set for the result's store (it is addressed from sp, not formed before the test): the
// scale's lw, qmtc2 and sqc2, the result's sqc2 16(sp) and the call are retail's (184 bytes
// against 180). Left: retail loads the fallback (lq) after the vaddq of the square root and
// into v0, so the receiver stays in a1; here the lq comes before the square root, into a1, and
// the receiver is moved to a2.
extern f32 D_00274AB4;

void func_001C3EB0(s32 c, void* receiver)
{
    PlacedObject* from = (PlacedObject*)c;
    PlacedObject* to = (PlacedObject*)receiver;
    Vec02 d;
    Vec02 v;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloatAt(D_00274AB4);
    u128 s = Vu0::Q(k);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(from->v140));
    d.z = 0.0f;
    Vu0::Set(v, Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), s));
    to->desc02()->m20(to, &v);
}

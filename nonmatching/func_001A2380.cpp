// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 588/624 (94.2%), checked 2026-11-08
// NEAR (2026-11-08, vu0w3-e1): same size, frame and registers; only the scheduling of the stores into the new effect (i20, life, m30[2], p120) and of the address of the unit-Z vector (lui/addiu) differs by one slot (all 24 orders of the four stores give the same 10 differing words). The rotation product is MulRotation written out with the three row copies assigned one by one (a block copy of the 48 bytes makes the compiler form the destination address in a register); the 0.0 is one f32 local, kept in $f21.
// permute.py --auto (2026-11-08, night-orders): 3 runs of 7/7/3 lines (10086 orders): best 36 bytes differ, as it stands.
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "globals.h"

extern f32 g_gameTime;
Effect* CreateEffect(s32 kind, EffectOwner* sys);
f32 RandomFloatInRange(f32 a, f32 b);
void TransformPointBetweenFrames(void* from, void* to, void* in, void* out);
void BuildPerpendicularPair(Vec02* dir, Vec02* a, const Vec02* b, const Vec02* c);
void BuildEulerRotationMatrix(Vec02* angles, Mat02* out);
void BuildShortestArcRotation(Vec02* from, Vec02* to, Mat02* out);

void AttachHitMarkEffect(Effect* self, s32 target, void* other, Vec02* point, Vec02* normal, Effect** out)
{
    Effect* e = 0;
    if (target != 0) {
        e = CreateEffect(0x14, 0);
        if (e != 0) {
            Vec02 local;
            Mat02 basis;
            Vec02 angles;
            Mat02 turn;
            TransformPointBetweenFrames(0, other, point, &local);
            f32 zero = 0.0f;
            f32 t = (g_gameTime - self->start) / self->life;
            f32* m = self->m30;
            f32 size = self->m30[0] + t * (m[1] + t * m[2]);
            size *= RandomFloatInRange(0.8f, 1.4f);
            e->vt->m00(e, &local, size, 0);
            size = -size;
            e->i20 = target;
            e->life = 5.0f;
            e->m30[2] = size;
            e->p120 = other;
            basis.r[2] = *normal;
            BuildPerpendicularPair(normal, basis.r, &g_unitXVector, &g_unitZVector);
            angles.y = zero;
            angles.x = zero;
            angles.z = RandomFloatInRange(zero, 6.2831855f);
            BuildEulerRotationMatrix(&angles, &turn);
            {
                Mat02 r;
                Vec02 x;
                Vec02 y;
                Vec02 z;
                Vu0::Q(x) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[0]));
                r.r[0] = x;
                Vu0::Q(y) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[1]));
                r.r[1] = y;
                Vu0::Q(z) = Vu0::RotateUntied(basis, Vu0::Q(turn.r[2]));
                r.r[2] = z;
                e->rot50[0] = r.r[0];
                e->rot50[1] = r.r[1];
                e->rot50[2] = r.r[2];
            }
            if (__builtin_fabsf(normal->z) < 0.7f) {
                Vec02 up = *normal;
                Mat02 arc;
                up.z = zero;
                BuildShortestArcRotation(&up, normal, &arc);
                Vu0::Q(e->qA0) = Vu0::Rotate(arc, Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-50.0f)));
            }
        }
    }
    if (out != 0) {
        *out = e;
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 460/468, checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): same size and frame; the registers and the order of the 18 stores of the rotated rows differ: retail loads the effect's second and third rows through a base register (addiu v1, s1, 0x50; lqc2 16(v1)) after the first row's stores, where here all three are loaded first from s1 (MulRotation's form, reference or pointer, const or not, changes nothing), and numbers the matrix rows vf3, vf6, vf4 (here vf1, vf4, vf2).
#include "common.h"
#include "mul_rotation.h"
#include "effect.h"
#include "globals.h"

extern f32 g_gameTime;
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void RemoveEffect(Effect* node);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

void UpdateEmitterEffect(Effect* self, f32 dt)
{
    Mat02 axisRot;
    Mat02 m;
    BuildAxisAngleMatrix(&g_unitZVector, &axisRot, *(f32*)((u8*)self + 0xA4) * dt);
    MulRotation(&m, axisRot, *(Mat02*)self->rot50);
    s32 fire = 0;
    Vec02* cam = (Vec02*)&g_camera->g80;
    if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->rot50[0]), Vu0::Q(*cam))) &&
        Vu0::ToFloat(Vu0::Dot(Vu0::Q(m.r[0]), Vu0::Q(*cam))) <= 0.0f && 0.5f < g_gameTime - self->start) {
        fire = 1;
    }
    if (fire) {
        Vec02 pos;
        Vu0::Set(pos, Vu0::Add(Vu0::Rotate(m, Vu0::Q(self->q80)), Vu0::Q(((PlacedObject*)self->p120)->v140)));
        Effect* e = CreateEffect(0x10, 0);
        if (e != 0) {
            e->vt->m00(e, &pos, 1.0f, 0);
            e->life = 0.25f;
        }
        if (--self->i124 <= 0) {
            RemoveEffect(self);
            return;
        }
    }
    self->rot50[0] = m.r[0];
    self->rot50[2] = m.r[2];
    self->rot50[1] = m.r[1];
}

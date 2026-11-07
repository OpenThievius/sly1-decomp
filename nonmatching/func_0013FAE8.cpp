// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 560/568, checked 2026-11-07
// NEAR: about 80% of the instructions equal; the first loop keeps the zone in $s0 and the 0x7C0 cursor in $s1 (retail the other way round) and the call is laid out inline after the second test where retail jumps back to a shared call. The dot products and branches match.
#include "common.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "vu0.h"

void TransformPointBetweenFrames(void* frame, void* other, void* in, void* out);
void TransformDirectionBetweenFrames(void* frame, void* other, void* in, void* out);
void FreePooledContactChain(World* w, void* chain);
Contact03* CreatePooledContact(void* self, s32 a, void* pos, void* plane, s32 kind, s32 b, s32 c, void* chain, f32 depth);

void func_0013FAE8(TriggerZone* self)
{
    Vec02 v[2];
    Vec02 w[2];
    Vec02 p;
    Vec02* where;
    f32 fa;
    f32 fb;
    f32 ga;
    f32 gb;
    s32 i;

    if (self->f7B4 == 0 && self->count7E0 == 0) {
        return;
    }
    if (self->contacts4B4 != 0) {
        FreePooledContactChain(self->world, self->contacts4B4);
        self->contacts4B4 = 0;
    }
    for (i = 0; i < 2; i++) {
        if (i < self->f7B4) {
            TransformPointBetweenFrames(self->parent, 0, (u8*)self + 0x7C0 + i * 16, &v[i]);
        }
        TransformDirectionBetweenFrames(self->parent, 0, (u8*)self + 0x860 + i * 16, &w[i]);
    }
    if (self->state == 0) {
        where = &self->v140;
        fa = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[0])));
        ga = Vu0::ToFloat(Vu0::Dot(Vu0::Q(v[0]), Vu0::Q(w[0])));
        gb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(v[1]), Vu0::Q(w[1])));
        fb = -fa;
    } else {
        where = &p;
        TransformPointBetweenFrames(self, 0, (u8*)self + 0x850, &p);
        ga = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[0])));
        gb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v140), Vu0::Q(w[1])));
        fb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(p), Vu0::Q(w[1])));
        fa = Vu0::ToFloat(Vu0::Dot(Vu0::Q(p), Vu0::Q(w[0])));
    }
    f32 x = fa - ga;
    Vec02* plane;
    if (x < -1e-4f) {
        plane = &w[0];
    } else {
        x = fb - gb;
        if (!(x < -1e-4f)) {
            return;
        }
        plane = &w[1];
    }
    Contact03* c = CreatePooledContact(self, 0, where, plane, 10, 0, 0, &self->contacts4B4, x);
    c->f98 = 0.0f;
}


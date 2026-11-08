// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 324/1324 (24.5%), checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): PlacedObject's slot 36 (0xA0), the base draw: the
// culling by the camera's planes and distance fades (into the transform's two scales), the world
// node's level, the parent's unscaling, the attachment's matrix, slot 37, then each child drawn
// with its transform. The code is retail's in every block (tools/regdiff.py: code, 85.2%) but
// for the frame: retail keeps one more saved register (s7, the child's world matrix, whose two
// products then share one call by cross-jumping) and its child-loop locals sit 16 bytes higher;
// the distance offset d is a u128 spilled across the calls, as retail's slot at 0x1C0 shows, but
// retail passes it to the first fade call from the VU0 register PlaneSigns read it into.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"
#include "camera.h"

struct ScaledTransform {
    Quad16 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};

void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);

s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, void* out);
void InvertRigidTransform(const Vec02* pos, const Mat02* rot, void* out);
void MultiplyMatrices(void* out, void* a, void* b);
void func_00125BF0(PlacedObject* self, Camera* cam, ScaledTransform* xf);

void func_00125C90(PlacedObject* self, Camera* cam, ScaledTransform* xf)
{
    ScaledTransform t;
    if (self->flags & ((u64)0x8000 << 17)) {
        return;
    }
    if ((self->flags & 0xC000000) == 0x8000000) {
        if ((self->f88 & cam->f21C) != cam->f21C) {
            return;
        }
    }
    if ((self->flags & 0x30000000) == 0x20000000) {
        Vec02 r;
        f32 fade;
        Vec02* p = &self->v140;
        if (xf != 0) {
            p = (Vec02*)&xf->q[3];
        }
        u128 d = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*(Vec02*)cam->f40));
        u128 ones = Vu0::Ones();
        Vu0::Q(r) = Vu0::FromFloat(self->f2A8);
        if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
            return;
        }
        if (ComputeCameraDistanceFade(cam, d, &fade, self->f2A8, self->f80) == 0) {
            return;
        }
        if (fade != 1.0f) {
            BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
            xf = &t;
            t.f40 *= fade;
        }
        if (self->f84 < self->f80) {
            if (ComputeCameraDistanceFade(cam, d, &fade, self->f2A8, self->f84) == 0) {
                fade = 0.0f;
            }
            if (fade != 1.0f) {
                BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
                xf = &t;
                t.f44 *= fade;
            }
        }
    }
    if (self->f298 != 0) {
        BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
        xf = &t;
        t.f40 *= self->f298->level;
    }
    if (xf != 0) {
        Rec2195_224* rec = self->f224;
        if (rec != 0 && (rec->fB0 & 0x80) && rec->fA0 != 0) {
            PlacedObject* parent = (PlacedObject*)self->parent;
            if (parent != 0) {
                Attachment* a = (Attachment*)parent->f1F4;
                if (a != 0 && parent->f224 != 0 && (parent->f224->fB0 & 0x80)) {
                    Mat02 m;
                    Mat02 rot;
                    a->vt->getMatrix(a, &m);
                    m.r[0].x = 1.0f / m.r[0].x;
                    m.r[1].y = 1.0f / m.r[1].y;
                    m.r[2].z = 1.0f / m.r[2].z;
                    BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
                    MulRotationRowsX(&rot, m, *(Mat02*)&t);
                    BuildMatrixFromRotationAndTranslation((Vec02*)&t.q[3], &rot, &t);
                    xf = &t;
                }
            }
        }
    }
    Attachment* a = (Attachment*)self->f1F4;
    if (a != 0) {
        Mat02 m;
        Mat4A m4;
        Mat4A out;
        a->vt->getMatrix(a, &m);
        BuildMatrixFromRotationAndTranslation(&D_00248D30, &m, &m4);
        BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
        MultiplyMatrices(&out, &t, &m4);
        xf = &t;
        *(Mat4A*)&t = out;
    }
    self->desc02()->m25(self, cam, xf);
    PlacedObject* o = (PlacedObject*)self->children.head;
    if (xf == 0) {
        for (; o != 0; o = (PlacedObject*)o->next) {
            if (o->desc->flags & 1) {
                o->desc02()->m24(o, cam, 0);
            }
        }
    } else {
        for (; o != 0; o = (PlacedObject*)o->next) {
            if (o->desc->flags & 1) {
                ScaledTransform ct;
                Mat4A local;
                ScaledTransform inv;
                Mat4A world;
                Mat4A rel;
                if (o->f224 != 0 && (o->f224->fB0 & 0xC)) {
                    BuildMatrixFromRotationAndTranslation(&o->v140, &o->m110, &local);
                    InvertRigidTransform(&self->v140, &self->m110, &inv);
                    MultiplyMatrices(&rel, xf, &inv);
                    MultiplyMatrices(&world, &rel, &local);
                } else {
                    BuildMatrixFromRotationAndTranslation(&o->pos, &o->rot, &local);
                    MultiplyMatrices(&world, xf, &local);
                }
                *(Mat4A*)&ct = world;
                ct.f40 = xf->f40;
                ct.f44 = xf->f44;
                o->desc02()->m24(o, cam, &ct);
            }
        }
    }
    if (0.0f < self->f28C) {
        func_00125BF0(self, cam, xf);
    }
}

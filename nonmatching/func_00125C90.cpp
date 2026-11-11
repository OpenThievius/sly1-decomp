// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1320/1324 (99.7%), checked 2026-11-10
// NEAR (2026-11-10, worker w11-125C90): PlacedObject's slot 36 (0xA0), the base draw: the
// culling by the camera's planes and distance fades (into the transform's two scales), the world
// node's level, the parent's unscaling, the attachment's matrix, slot 37, then each child drawn
// with its transform. Every instruction is retail's but one. The child's matrix is
// MultiplyMatrices by value (matrix.cpp returns it by g++'s named return value; retail's callee
// starts `move v0,a0`), nested where the child is relative to its parent:
// `MultiplyMatrices(MultiplyMatrices(*xf, inv), local)`. The outer call's return slot is a
// temporary whose address is used by the call and by the copy into ct, so loop.c moves it
// (retail's s7); a `world` local passed by pointer has one use, which loop.c's single-use rule
// folds back into the call, and cross-jumping merges the two arms' calls only when both
// temporaries share 0x130. The frame: the parent's rotation product has the 112-byte inline
// frame of MulRotationIntoWorld (func_00125138, this file), its fourth row w never set, so the
// child walk's temporaries start at 0x130 (docs/TOOLCHAIN.md, "Stack slots").
// Still differs: retail passes d to the first fade call with `qmfc2 a1,$vf6`, the VU0 register
// PlaneSigns's input reload left it in; ours loads it from d's spill slot (`lq a1,0x1C0(sp)`).
// Our (set a1 d) takes movti's memory alternative, whose source class is NO_REGS, so reload
// makes no optional reload and cannot inherit vf6; retail's must have had a second pseudo for d
// (the asm and the first call) with vf6 as its hard register. Not it: d as Vu0::Vec, as a Vec02
// in memory, through Vu0::Q, an inline helper taking d (u128 or Vec) for PlaneSigns and the
// first call, a named radius (that moves the cull's registers).
// Also ruled out (w15, 2026-11-10; docs/toolchain/stack-slots.md): movti's constraints make the
// GPR-from-memory alternative free, and reload_cse will not swap the lq for vf6 (VU0 to GPR
// does not cost 2). d forced into the frame lands at 0x1C0 after fade, retail's offsets, but
// cse2 forwards its store (vsub into vf6, no reload); a Vec02 d is forwarded by cse1; a
// `const u128&` to d (local, or an inline helper's parameter) is purged back to one pseudo.
// w19 (2026-11-10, tools/globalalloc.py): not caller-saves. d has 4 refs over 2 calls, so
// global-alloc spills it; `--set 136:refs=9` gives vf6 by caller-saves, which is how
// func_00126270 and func_0018F9D8 (loops) get their qmfc2 a1,$vf6, but there the difference is
// written straight into vf6. Here retail writes it to vf3, stores it at 0x1C0 and loads vf6: a
// memory d whose one load serves the asm and the first call, the second call reading memory,
// with cse1 and cse2 both leaving that load alone (docs/toolchain/stack-slots.md).
// w20 (2026-11-10): not the regclass wall of the dots (docs/toolchain/vu0-helpers.md, "A GPR operand
// that leaves the class to the producer"): ToFloatMoved's "*r" and every conversion as ToFloatMoved leave
// the one line (retail's `qmfc2 a1,$vf6` for the call argument, ours `lq a1,448(sp)`): d reaches the call
// as a memory variable, not through a conversion helper.
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
Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);
void func_00125BF0(PlacedObject* self, Camera* cam, ScaledTransform* xf);

// The parent's rotation, its scale divided out, times the transform's (MulRotationRowsX), with
// the fourth row w that MulRotationIntoWorld's frame shows: never set, it makes the saved frame
// 112 bytes, and the child walk's locals sit after it (docs/TOOLCHAIN.md, "Stack slots").
static inline void MulRotationRowsXW(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vec02 w;    // the fourth row: never set
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    *out = r;
}

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
                    MulRotationRowsXW(&rot, m, *(Mat02*)&t);
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
        a->vt->getMatrix(a, &m);
        BuildMatrixFromRotationAndTranslation(&D_00248D30, &m, &m4);
        BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
        *(Mat4A*)&t = MultiplyMatrices(*(Mat4A*)&t, m4);
        xf = &t;
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
                if (o->f224 != 0 && (o->f224->fB0 & 0xC)) {
                    BuildMatrixFromRotationAndTranslation(&o->v140, &o->m110, &local);
                    InvertRigidTransform(&self->v140, &self->m110, &inv);
                    *(Mat4A*)&ct = MultiplyMatrices(MultiplyMatrices(*(Mat4A*)xf, *(Mat4A*)&inv), local);
                } else {
                    BuildMatrixFromRotationAndTranslation(&o->pos, &o->rot, &local);
                    *(Mat4A*)&ct = MultiplyMatrices(*(Mat4A*)xf, local);
                }
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

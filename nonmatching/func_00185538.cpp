// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 411/540 (76.1%), checked 2026-11-09
// NIGHT-DECLS (2026-11-08): ComputeObjectFrameAtTime declared void as defined (func_00125750): 397 -> 411 bytes; the stack address of the next call moves with it. Still differs as above.
// W9 (2026-11-09): the yaw clamp. As a local clamped in place and stored once at the join
// (`f32 yaw = ...; if (yaw < lo) yaw = lo; else if (hi < yaw) yaw = hi; angles[0] = yaw;`) the
// arms are retail's (mov.s, bc1tl, mov.s), but sched1 sinks the store below the pitch block's
// loads (priority 1, no dependent in its block; .sched block 10 puts it at cycle 6), so the yaw
// lives into the pitch and global-alloc gives it f4 (lo f5, hi f0). Retail's store is first in
// its block, which needs a dependent (a load that may alias it) or a block of its own: the store
// in each arm, merged by jump2's cross-jumping after reload, keeps it first (36 lines differ),
// but combine folds `yaw = lo` into the first arm's store (swc1 $f4). A reference clamp inline,
// ClampAim for the yaw, and separate yaw/pitch scalars are worse (50, 69, 38).
// NEAR: GetAimRotation. The calls, the frame and the VU0 part are retail's. The two clamps differ: retail keeps the yaw in f3 (the polynomial's sum is added into f3, compared with the low limit in f4, the high limit loaded in the delay slot) and stores it once after the clamp; the pitch is clamped in f13/f3 as a separate result. Ours with the yaw as a local gives f4/f5 registers; with the yaw in the angles array it stores it in each arm of the clamp. The pitch through an inline ClampAim is right.
#include "common.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "attachment.h"
#include "globals.h"
#include "placed_object.h"

s32 ResolveAimTarget(T2195_790* a0);

void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void GetVectorAngles(Vec02* v, f32* yaw, f32* pitch);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);

static inline f32 ClampAim(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void GetAimRotation(T2195_790* self, f32 dt, Mat02* rot, Vec02* vec)
{
    Vec02 pos;
    Vec02 d;
    Mat02 m;
    f32 angles[2];
    PlacedObject* owner = self->owner;
    *vec = D_00248D30;
    if (self->hold != 0) {
        *rot = owner->rot;
        return;
    }
    ComputeObjectFrameAtTime((void*)ResolveAimTarget(self), 0, &pos, &m, 0, 0, dt);
    Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(m, Vu0::Q(self->point)), Vu0::Q(pos));
    TransformPointBetweenFrames(0, self->owner->parent, &pos, &pos);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->owner->pos));
    s32 outside = self->f40 < Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    if (outside) {
        *rot = owner->m1A0;
        return;
    }
    GetVectorAngles(&d, &angles[0], &angles[1]);
    f32* p = (f32*)&self->v50;
    angles[0] = self->v50.x + angles[0] * (p[1] + angles[0] * p[2]);
    if (angles[0] < *(f32*)&self->p60) {
        angles[0] = *(f32*)&self->p60;
    } else if (*((f32*)&self->p60 + 1) < angles[0]) {
        angles[0] = *((f32*)&self->p60 + 1);
    }
    f32* q = (f32*)&self->v70;
    angles[1] = ClampAim(self->v70.x + angles[1] * (q[1] + angles[1] * q[2]), *(f32*)&self->p80, *((f32*)&self->p80 + 1));
    BuildYawPitchMatrix(rot, angles[0], angles[1]);
}

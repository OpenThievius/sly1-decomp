// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 375/444 (84.5%), checked 2026-11-07
// NEAR: vector part scheduled differently: retail loads the point (lqc2 vf4,0(sp)) before the cross product's operands and the float 0x844 (lw, qmtc2) after the cross product, keeping the point in vf4 and the path follower's position in vf3 (loaded after the square root); ours loads the point late into vf3 and the position into vf4. The weight is stored to the local the next curve call writes (Set), as retail shares the slot. Everything after the arctangent matches (min.s through <?, sqrt.s through Fpu::Sqrt, the ComputeAngleBetweenVectors call).
// In the context of its file, src/main/file_1D62E0.cpp.
// From 0x1D62E0 to 0x1DDCE0: classes 0x07 and 0x3F, the output buffer, class 0x19, the world
// (class 0x6C) and its script functions. Its .data runs from 0x275140 to the zeroed globals
// D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the "%s" of
// func_001D72C8, the float of func_001D8470 and the pairs of func_001DCD28. One file between
// two edges with no evidence inside it: it could be several.
#include "common.h"
#include "vu0.h"
#include "fpu.h"
#include "globals.h"
#include "path_curve_object.h"

f32 ArctangentOfRatio(f32 a, f32 b);
float D_002751D0 = 850.0f;
f32 D_002754DC = 750.0f;
f32 D_002754E0[2] = { 1.0f, 0.0f };
f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);

void ComputePathFollowerHeadingTarget(PathFollower* self)
{
    Vec02 pos;
    Vec02 tangent;
    Vec02 side;
    Vec02 w;
    Vec02 ahead;
    if (self->f830 != 0) {
        PathCurve* o = self->f830->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->f83C + D_002751D0, &pos, &tangent);
        }
        u128 base = Vu0::Q(pos);
        u128 c = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
        u128 k = Vu0::FromFloatAt(self->f844);
        Vu0::Q(side) = Vu0::DivX(c, Vu0::Length(c));
        Vu0::Set(ahead, k);
        u128 p2 = Vu0::MulAddX(base, Vu0::Q(side), k);
        Vu0::Q(w) = Vu0::Sub(p2, Vu0::Q(*(Vec02*)((u8*)self + 0x100)));
        Vu0::Q(pos) = p2;
        self->f694 = ArctangentOfRatio(w.y, w.x);
        o = self->f830->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->f83C + D_002751D0 + D_002754DC, 0, &ahead);
        }
        f32 turn = ComputeAngleBetweenVectors(&tangent, &ahead, 0);
        self->f698 = self->f85C * self->f618;
        u8* limit = *(u8**)((u8*)self + 0xAFC);
        if (limit != 0) {
            self->f698 = *(f32*)(limit + 0x1C) <? self->f698;
        }
        if (0.0f < turn) {
            f32 v = Fpu::Sqrt(D_002754E0[0] * (D_002754DC / turn) * self->f868 * -*(f32*)((u8*)self + 0x358));
            if (v < self->f698) {
                self->f698 = v;
            }
        }
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 592/572, checked 2026-11-07
// NEAR: the whole body is retail's (quadword helper calls, the clamp, both branches); 20 bytes longer because GCC keeps the addresses of the two quadword locals (0x50, 0x60) in callee-saved registers (s2, s4) across the helper calls, where retail recomputes them with addiu at each use and holds only the one passed to the steer calls (s3). Storing the helper's result in a local before StoreQuadword, and a pointer variable for the steer argument, did not stop the sharing.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"

extern f32 g_gameClock[];
extern f32 D_00275188, D_0027518C;
extern float D_00275190[4], D_002751A0[4], D_002751B0[4], D_002751C0[4];

typedef int Quadword128 __attribute__((mode(TI)));
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
void StepCollider(void* self);
void RotateMatrixUpright(Mat02* rot, s32 zero, Mat02* out);
void SteerColliderTowardRotation(StandIn* self, Mat02* rot, Vec02* a, Vec02* b, Vec02* c, f32 t);
void SteerColliderTowardPosition(StandIn* self, s32 a, s32 b, Vec02* pos, Vec02* c, f32 t);
extern Quad16 D_00275C40;

void func_001D6DD8(StandIn* self, f32 t)
{
    Mat02 upright;
    Vec02 push;
    Vec02 spin;
    Vec02 q50;
    Vec02 q60;
    Vec02 k;
    Quadword128 t1;
    Quadword128 u1;
    Quadword128 t2;
    Quadword128 u2;
    Quadword128 t3;
    Quadword128 u3;
    f32 age;
    StepCollider(self);
    f32 since = g_gameClock[1] - self->f690;
    f32 ease = D_002751C0[0] + since * (D_002751C0[1] + since * D_002751C0[2]);
    ValueRange* lim = &g_unitRange;
    f32 lo = lim->lo;
    f32 hi = lim->hi;
    if (ease < lo) {
        age = lo;
    } else if (hi < ease) {
        age = hi;
    } else {
        age = ease;
    }
    RotateMatrixUpright(&self->rot, 0, &upright);
    u8* p1 = (u8*)D_00275190;
    StoreFloatAsQuadword(&t1, age);
    Quadword128 a1 = t1;
    CopyQuadword(&u1, p1);
    Quadword128 v1 = ScaleQuadword(a1, u1);
    StoreQuadword(&q50, v1);
    u8* p2 = (u8*)D_002751A0;
    StoreFloatAsQuadword(&t2, age);
    Quadword128 a2 = t2;
    CopyQuadword(&u2, p2);
    Quadword128 v2 = ScaleQuadword(a2, u2);
    StoreQuadword(&q60, v2);
    if (self->f694 != 0) {
        Vu0::Q(k) = Vu0::FromFloat(D_00275188);
        Vu0::Q(spin) = Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::Q(k));
    } else {
        spin = D_00248D30;
        q50 = *(Vec02*)&D_00275C40;
    }
    Vec02* c = &q60;
    SteerColliderTowardRotation(self, &upright, &q50, &spin, c, t);
    if (self->f694 != 0) {
        Vu0::Q(k) = Vu0::FromFloat(D_0027518C);
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(self->rot.r[0]), Vu0::Q(k));
    } else {
        push = D_00248D30;
    }
    u8* p3 = (u8*)D_002751B0;
    StoreFloatAsQuadword(&t3, age);
    Quadword128 a3 = t3;
    CopyQuadword(&u3, p3);
    Quadword128 v3 = ScaleQuadword(a3, u3);
    StoreQuadword(&q60, v3);
    SteerColliderTowardPosition(self, 0, 0, &push, c, t);
}

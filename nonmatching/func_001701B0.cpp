// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 608/604, checked 2026-11-07
// NEAR: the whole dispatch matches (frame, jump table, cases in retail's order, the shared Mat02 scratch); 4 bytes longer: GCC computes the address of the third quadword local (sp+16) into s0 once and reuses it for the steer call's last argument, where retail recomputes it with addiu in the delay slot of each call, and the prologue saves ra and s1 before 'mov.s f20,f12' in ours (after it in retail).
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"

extern f32 g_frameDt[];
extern f32 g_gameClock[];
extern f32 D_00262E28;
extern f32 D_00263780[4], D_00263790[4], D_002637A0[4];

typedef int Quadword128 __attribute__((mode(TI)));
void StepCollider(void* self);
void func_0016FD70(Player* self);
void func_0017D248(Player* self);
void TurnPlayerTowardLinkedObject(Player* self);
void StepPlayerOnPath(Player* self);
void StepPlayerRequestState(Player* self);
void StepPlayerAlongTarget(Player* self);
void ComputePolarOffset(Vec02* out, f32 angle, f32 dist, f32 z);
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
void SteerColliderTowardRotation(Player* self, s32 a, s32 b, Vec02* offset, Vec02* c, f32 t);
void SteerColliderTowardPosition(Player* self, s32 a, s32 b, const Vec02* pos, void* c, f32 t);
void TurnColliderTowardRotation(Player* self, f32 t, void* rot, void* data);
void AddColliderForce(void* a, void* b);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
extern f32 g_gameClock[];

void func_001701B0(Player* self, f32 t)
{
    Mat02 m;
    Quadword128 qa;
    Quadword128 a;
    Quadword128 b;
    StepCollider(self);
    switch (self->f2220) {
    case 2:
        func_0017D248(self);
        break;
    case 3:
        TurnPlayerTowardLinkedObject(self);
        break;
    case 7:
        StepPlayerOnPath(self);
        break;
    case 4:
        StepPlayerRequestState(self);
        break;
    case 6:
        StepPlayerAlongTarget(self);
        break;
    case 13:
        switch (self->f2228) {
        case 0x38:
            BuildAxisAngleMatrix(&g_unitZVector, &m, self->f638);
            TurnColliderTowardRotation(self, g_frameDt[0], &m, D_00263780);
            break;
        case 0x36:
        case 0x37: {
            ComputePolarOffset(&m.r[0], self->f638 + 1.5707964f, self->f634 * D_00262E28 / self->radius3CC, 0.0f);
            u8* table = (u8*)D_00263790;
            StoreFloatAsQuadword(&a, self->f634);
            qa = a;
            CopyQuadword(&b, table);
            Quadword128 prod = ScaleQuadword(qa, b);
            StoreQuadword(&m.r[1], prod);
            SteerColliderTowardRotation(self, 0, 0, &m.r[0], (Vec02*)((u8*)&m + 0x10), t);
            break;
        }
        }
        break;
    case 9:
        if (g_gameClock[1] - *(f32*)&self->f2224 > 0.25f) {
            Vu0::Q(m.r[1]) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(m.r[1]));
            AddColliderForce(self, &m.r[0]);
            SteerColliderTowardPosition(self, 0, 0, &D_00248D30, D_002637A0, t);
            TurnColliderTowardRotation(self, g_gameClock[2], (u8*)self + 0x660, (u8*)self + 0x6E0);
        } else {
            func_0016FD70(self);
        }
        break;
    default:
        func_0016FD70(self);
        break;
    case 11:
        break;
    }
}

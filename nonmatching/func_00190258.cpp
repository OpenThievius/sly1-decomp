// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 400/404, checked 2026-11-07
// NEAR: frame (0x50, three Vec02 locals) and every instruction of the cases match, but the control flow differs: retail shares one ArctangentOfRatio call and one SetAgentFacingAngles tail among the cases 2, 13 and 8 (a jump back into case 2's code) while ours repeats them per case, and retail's default and case-2 UpdateAgentState calls are two separate sites. The jump table is rebuilt by the compiler. About 8 shapes of the switch tried.
#include "common.h"
#include "switched_collider.h"
#include "vu0.h"
extern void* g_camera;
void* GetActiveSwitchedCollider(void);

void FaceAgentTowardGoalPoint(SeekingAgent* self);
void UpdateAgentState(SeekingAgent* self);
void SetAgentFacingAngles(SeekingAgent* self, f32 a, f32 b);
f32 WrapAngle(f32 x);
f32 ArctangentOfRatio(f32 y, f32 x);
s32 GetObjectWorldRotation(void* self, Vec02* out);

void func_00190258(SeekingAgent* self)
{
    Vec02 tmp;
    Vec02 second;
    Vec02 third;
    f32 a;

    switch (self->f724) {
    case 7:
        FaceAgentTowardGoalPoint(self);
        break;
    case 2:
        if (self->f754 != 0) {
            UpdateAgentState(self);
            break;
        }
        if (self->fC24 != 0) {
            GetObjectWorldRotation(self->fC24, &tmp);
        } else {
            SwitchedCollider* other = (SwitchedCollider*)GetActiveSwitchedCollider();
            if (other == 0 || other == self) {
                break;
            }
            Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
        }
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 13:
        if (self->fC28 == 0) {
            break;
        }
        GetObjectWorldRotation(self->fC28, &tmp);
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 8:
        if (*(void**)((u8*)self->f7E0 + 8) != self->f5F0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)g_camera + 0x40)), Vu0::Q(self->v140));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    case 11:
    case 16:
        if (self->fC34 == 0) {
            break;
        }
        Vu0::Q(tmp) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self->fC2C + 0x140)));
        a = ArctangentOfRatio(tmp.y, tmp.x);
        if (self->f724 == 0x10) {
            a = WrapAngle(a + 4.0f);
        } else {
            a = WrapAngle(a + 4.7f);
        }
        SetAgentFacingAngles(self, a, 0.0f);
        break;
    default:
        UpdateAgentState(self);
        break;
    }
}


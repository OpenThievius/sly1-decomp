// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: D_0026F5A0.f260 is at 0x570 (US 0x260) and D_002701F8.f324 at 0x5B0 (US 0x324).
struct Glob_150790_eu { u8 pad0[0x570]; StepSequence* f260; };
struct __attribute__((packed)) Blk_150790_eu { u8 pad0[0x5B0]; s32 f5B0; };

void SetStepSequenceState(StepSequence* self, s32 next)
{
    s32 cur = self->state2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (((Glob_150790_eu*)&D_0026F5A0)->f260 == self) {
            ((Glob_150790_eu*)&D_0026F5A0)->f260 = 0;
        }
        break;
    case 1:
        if (self->mode2D0 != cur) {
            D_00261D38 = D_00261D38 - 1;
        }
        break;
    case 3:
        *(s32*)self->target304 = 1;
        StopStreamVoice();
        TriggerScriptEvent(self, 0x15, 0, 0);
        if (self->mode2D0 == 2) {
            RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, 0, 0);
            ReleasePadSelectFlag(g_currentWorld);
        }
        (void)PopStackValue(&g_camera->ctl460);
        if ((self->waitFlags & 0x10) != 0 && self->player2F8 != 0) {
            StopAnimationPlayer(self->player2F8);
        }
        if (self->mode2D0 == 2 && self->f330 != 0) {
            f32 f = 1.0f;
            SetVolumeChannelFactor(9, 0, f);
            SetVolumeChannelFactor(9, 1, f);
        }
        break;
    case 4:
        ((Blk_150790_eu*)&g_typedTextCaptionBox)->f5B0 = 0;
        SetTextPanelState(&g_typedTextCaptionBox, 0);
        break;
    }
    switch (next) {
    case 5:
        if (((Glob_150790_eu*)&D_0026F5A0)->f260 != 0) {
            SetStepSequenceState(((Glob_150790_eu*)&D_0026F5A0)->f260, 0);
        }
        ((Glob_150790_eu*)&D_0026F5A0)->f260 = self;
        self->state2D4 = next;
        break;
    case 1:
        if (self->mode2D0 != next) {
            D_00261D38 = D_00261D38 + 1;
        }
        self->state2D4 = next;
        break;
    case 3:
        self->step2E4 = -1;
        self->waitFlags = 0;
        if (self->mode2D0 == 2) {
            PushStackValue(&g_camera->ctl460, 4);
            PushCameraController(g_camera, 6, &g_camera->ctl460, 0, 0);
            AcquirePadSelectFlag(g_currentWorld);
            SetTextPanelSubject(&g_typedTextCaptionBox, 0);
            if (self->f330 != 0) {
                f32 f = 0.6f;
                SetVolumeChannelFactor(9, 0, f);
                SetVolumeChannelFactor(9, 1, f);
            }
        } else {
            PushStackValue(&g_camera->ctl460, 3);
            if (self->mode2D0 == 0) {
                if (self->second300 != -1) {
                    g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, self->second300, 0);
                } else {
                    g_camera->ctl460.anchorObject = 0;
                }
            }
        }
        self->state2D4 = next;
        break;
    case 4:
        SetArcTarget(&D_002708E0, 0);
        SetArcSpecialObject(&D_002708E0, 0);
        SetArcTarget(&D_00271558, 0);
        SetArcSpecialObject(&D_00271558, 0);
        self->state2D4 = next;
        break;
    default:
        self->state2D4 = next;
        break;
    }
    self->time2D8 = g_gameTime[0];
}

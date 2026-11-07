// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the Gl_150AE8 global has f260 at 0x570 and f26C at 0x57C (US 0x260, 0x26C).
struct Gl_150AE8_eu { u8 pad0[0x570]; s32 f570; u8 pad1[8]; s32 f57C; };

void UpdateStepSequence(StepSequence* self)
{
    s32 q[2];
    s32 s1;
    Ent65* s2;

    UpdatePlacedObject(self);
    if (!(((Gl_150AE8_eu*)&g_timerCaption)->f570 < 2 && ((Gl_150AE8_eu*)&g_timerCaption)->f57C == 0 && IsStreamVoiceLocked() == 0 && D_00275F84 != 1)) {
        s32 st = self->state2D4;
        switch (st) {
        case 1:
        case 5:
        case 6:
            SetStepSequenceState(self, 0);
            return;
        }
    }
    FillMemory(q, 0, 8);
    s2 = GetActiveSwitchedCollider();
    if (IsTopCameraController(&((Camera*)g_camera)->ctl454) != 0) {
        q[1] = 0;
        q[0] = 0;
    } else if (s2 != 0) {
        s2->vt->f154(s2, self, q);
    } else {
        q[1] = 1;
    }
    s1 = self->state2D4;
    switch (s1) {
    case 0:
        if (self->f324 != 0) {
            if (D_00275F84 == 0 && q[1] != 0) {
                self->f324 = 0;
                ChooseStepSequenceState(self);
                s1 = self->state2D4;
            }
        }
        break;
    case 5:
        if (q[0] == 0) {
            s1 = 6;
            break;
        }
        goto timer;
    case 6:
        if (q[0] != 0) {
            s1 = 5;
            break;
        }
        goto timer;
    case 1:
        if (q[1] != 0) {
            StepSequence* o = (StepSequence*)D_0027051C;
            if (o == 0) {
                ShowStepSequenceText(self, s2);
                s1 = self->state2D4;
            } else if (o != self) {
                if (o->f328 == 0 && o->state2D4 == 3) {
                    SkipRemainingSteps(o);
                }
            }
            break;
        }
    timer:
        if (g_gameTime[0] - self->time2D8 >= 5.0f) s1 = 0;
        break;
    case 3:
        if (self->mode2D0 != 2) {
            if (!(self->step2E4 < self->count2DC) || D_00275F84 == 1) {
                PopStackElement(g_elementStack);
                s1 = self->state2D4;
            }
        }
        break;
    case 4:
        if (D_00270B30 == 0) {
            if (D_002717A8 == 0) s1 = 0;
        }
        break;
    }
    SetStepSequenceState(self, s1);
    switch (self->state2D4) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    case 3:
        RunStepSequence(self);
        break;
    }
}


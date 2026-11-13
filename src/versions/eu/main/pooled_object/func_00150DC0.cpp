// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the name is a 16-bit string (measured by func_eu_001E3018), and the HUD fields sit at 0x57C/0x580.
struct Vt_150DC0_eu { u8 pad[0x20]; void (*f20)(void*, u16*); };
struct Hud_150DC0_eu {
    Vt_150DC0_eu* vt;
    u8 pad0[0x57C - 4];
    f32 f2F0;
    u32 f2F4;
};

u32 GetWideStringLength(u16* a);
void SetTextPanelValuePercent(Hud_150DC0_eu* a, f32 b);
void SetTextPanelSubject(Hud_150DC0_eu* a, s32 b);

void HandleStepSequenceMessage(StepSequence* self, SequenceMessage* msg)
{
    CaptionSpeaker* s2;
    CaptionSpeaker* s4;
    s32 a2;
    s32 a0;
    f32 f20;
    u16* nm;
    switch (msg->type) {
    case 0:
        OpenKeyRecord(msg->f4.i);
        self->f2E8 |= 1;
        break;
    case 1:
    case 2:
        if (msg->f4.i != -1) {
            s2 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f4.i, self->root ? self->root : self);
        } else {
            s2 = 0;
        }
        if (msg->f8.i != -1) {
            s4 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f8.i, self->root ? self->root : self);
        } else {
            s4 = 0;
        }
        if (s2 && s2->f334) {
            SetStateWalkerTarget(s2->f334, 0x34C);
        }
        switch (msg->type) {
        case 1:
            SetArcTarget(&D_002708E0, s2);
            SetArcSpecialObject(&D_002708E0, s4);
            self->p2F0 = s2;
            if (s2) {
                self->f2E8 |= 2;
            }
            break;
        case 2:
            SetArcTarget(&D_00271558, s2);
            SetArcSpecialObject(&D_00271558, s4);
            self->p2F4 = s2;
            if (s2) {
                self->f2E8 |= 4;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (self->p2F0 && MatchesObjectId((CaptionSpeaker*)self->p2F0, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F0;
            SetArcFade(&D_002708E0, 1);
            SetArcFade(&D_00271558, 0);
        } else if (self->p2F4 && MatchesObjectId((CaptionSpeaker*)self->p2F4, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F4;
            SetArcFade(&D_00271558, 1);
            SetArcFade(&D_002708E0, 0);
        } else {
            s2 = 0;
        }
        a2 = msg->f1C;
        a0 = 0;
        if (a2 != -1) {
            a0 = FindFirstObjectById(self->world, 2, a2, self);
            self->f2E8 |= 0x10;
        } else {
            if (s2) {
                a0 = FindFirstObjectById(self->world, 1, 0x54A, s2);
            }
        }
        if (a0) {
            CreateAnimationPlayerWithoutPresetTargets(0.0f, 1.0f, (CaptionSpeaker*)a0, (s32)s2, 1, &self->player2F8);
            AddAnimationPlayerRecordCallback(self->player2F8, self);
        }
        nm = (u16*)msg->f14;
        if (nm && *nm) {
            (*(Hud_150DC0_eu*)&g_typedTextCaptionBox).vt->f20(&(*(Hud_150DC0_eu*)&g_typedTextCaptionBox), nm);
            if (s2) {
                *(Rgba4*)&(*(Hud_150DC0_eu*)&g_typedTextCaptionBox).f2F4 = s2->f2D0;
            } else {
                (*(Hud_150DC0_eu*)&g_typedTextCaptionBox).f2F4 = 0x80808080;
            }
            if (self->player2F8) {
                if (msg->f1C == -1) {
                    f20 = msg->f8.f;
                } else {
                    f20 = self->player2F8->anim->length;
                }
            } else {
                f20 = msg->f8.f;
            }
            if (0.0f < f20) {
                (*(Hud_150DC0_eu*)&g_typedTextCaptionBox).f2F0 = (f32)(GetWideStringLength((u16*)msg->f14) + 10) / f20;
            } else {
                Hud_150DC0_eu* h3 = &(*(Hud_150DC0_eu*)&g_typedTextCaptionBox);
                h3->f2F0 = 15.0f;
            }
            self->f2E8 |= 0x20;
        }
        if (msg->f4.f >= 0.0f) {
            SetTextPanelValuePercent(&(*(Hud_150DC0_eu*)&g_typedTextCaptionBox), msg->f4.f + 1.0f);
            self->f2E8 |= 0x40;
        }
        if (msg->f8.f >= 0.0f) {
            self->f2E8 |= 0x80;
            self->f2FC = g_gameTime[0] + msg->f8.f;
        }
        if (msg->f20 != -1) {
            s32 r = FindFirstObjectById(self->world, 0x104, msg->f20, self->root ? self->root : self);
            SetTextPanelSubject(&(*(Hud_150DC0_eu*)&g_typedTextCaptionBox), r);
        }
        if (msg->f24 != -1) {
            g_camera->ctl460.f5C = FindFirstObjectByIdMode4(self->world, msg->f24, 0);
        } else if (self->second300 != -1) {
            g_camera->ctl460.f5C = FindFirstObjectByIdMode4(self->world, self->second300, 0);
        } else {
            g_camera->ctl460.f5C = 0;
        }
        if (msg->fC) {
            self->f2E8 |= 0x100;
            self->f2EC = msg->f10;
        }
        self->f2E8 |= 8;
        break;
    case 4: {
        void* tmp = &msg->f4;
        TriggerScriptEvent(self, 0x10, 1, &tmp);
        break;
    }
    case 5:
        ShowCountedScreenElement(self->world);
        break;
    case 6:
        HideCountedScreenElement(self->world);
        break;
    case 7:
        QueueMovie(g_moviePlayer, msg->f4.i);
        break;
    }
}

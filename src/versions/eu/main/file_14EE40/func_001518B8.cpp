// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_0026E9F8.f260 and f26C are at 0x570 and 0x57C (US 0x260, 0x26C).
struct Gl_0026E9F8_eu { u8 pad0[0x570]; s32 f570; u8 pad1[8]; s32 f57C; };

void ChooseStepSequenceState(StepSequence* self)
{
    Gl_0026E9F8_eu* g = (Gl_0026E9F8_eu*)&g_timerCaption;
    if (g->f570 >= 2 || g->f57C != 0)
        return;
    if (IsStreamVoiceLocked() != 0)
        return;
    if (D_00275F84 == 1)
        return;
    if (self == D_0027051C)
        return;
    s32 mode = 1;
    if (*(s32*)self->target304 != 0) {
        mode = (self->mode2D0 == 2) ? self->state2D4 : 5;
    } else {
        s32 n = self->f310;
        if (n > 0) {
            for (s32 i = 0; i < n; i++) {
                if (*(s32*)self->f314[i] != 0) {
                    mode = 5;
                    break;
                }
            }
        }
    }
    SetStepSequenceState(self, mode);
}


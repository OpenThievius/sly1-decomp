// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f270, f274, f278 and f290 sit 784 (0x310) bytes further on than in US.
struct Self_001AB600_eu {
    u8 p0[4];
    void* p4;
    u8 p8[0x270 - 8 + 0x310];
    s32 f270;
    s32 f274;
    f32 f278;
    u8 p27C[0x290 - 0x27C];
    s32 f290;
};

void SetupScreenElementText(Self_001AB600_eu* self);
void SetTimerState(Self_001AB600_eu* self, s32 state);

void InitTimerElement(Self_001AB600_eu* self)
{
    SetupScreenElementText(self);
    self->p4 = (void*)GetFontById(2);
    self->f274 = self->f270 = -1;
    self->f278 = 3.4028235e+38f;
    self->f290 = 1;
    SetTimerState(self, 0);
}

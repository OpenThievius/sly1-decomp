// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: value sits 784 (0x310) bytes further on than in US.
struct Flag_1AB958_eu { u8 pad[0x290 + 0x310]; s32 value; };

void SetTimerState(void* self, s32 v);

void StopTimer(Flag_1AB958_eu* self)
{
    self->value = 1;
    SetTimerState(self, 0);
}

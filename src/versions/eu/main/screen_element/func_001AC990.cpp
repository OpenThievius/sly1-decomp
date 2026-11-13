// SPDX-License-Identifier: AGPL-3.0-or-later
// When +0x570 is set and the argument is 0, calls func_eu_001AB2B0 with +0x574 and clears +0x570; then calls func_001AA998 (PAL 001AB790) on self.
struct Obj_eu_001AD6E8 {
    u8 pad000[0x570];
    s32 flag;
    s32 value;
};

void SetScreenElementWideText(void* self, s32 v);
void SetScreenElementMode(void* self, s32 a1);

void SetElementModeApplyingPendingText(Obj_eu_001AD6E8* self, s32 a1)
{
    s32 v;

    if (self->flag != 0) {
        if (a1 == 0) {
            v = self->value;
            self->flag = 0;
            SetScreenElementWideText(self, v);
            a1 = 1;
        }
    }
    SetScreenElementMode(self, a1);
}

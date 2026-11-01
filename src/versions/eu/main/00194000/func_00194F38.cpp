// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: mode250 sits at 0x560, f274 and f278 at 0x584 and 0x588 (not 0x250, 0x274 and 0x278).
struct Ctl_194F38_eu { u8 pad[0x560]; s32 mode560; u8 pad2[0x20]; s32 f584; s32 f588; };

void func_00194F38(Ctl_194F38_eu* self)
{
    if (self->mode560 == 3 && self->f584 != 0) {
        self->f584 = 0;
        self->f588 = -1;
        return;
    }
    func_001AA958((Ctl_194F38*)self);
}

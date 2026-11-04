// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: mode250 sits at 0x560 and f274 at 0x584 (not 0x250 and 0x274).
struct Ctl_194F00_eu { u8 pad[0x560]; s32 mode560; u8 pad2[0x20]; s32 f584; };

void func_00194F00(Ctl_194F00_eu* self)
{
    if (self->mode560 == 3 && self->f584 != 0) return;
    func_001AA8F0((Ctl_194F00*)self);
}

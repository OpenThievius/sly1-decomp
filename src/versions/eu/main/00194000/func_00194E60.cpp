// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object is laid out 0x310 further on: f250 at 0x560, f260 at 0x570, f274 and f278 at 0x584 and 0x588.
struct Ctl_194E60_eu {
    u8 pad0[0x560];
    s32 f560;
    u8 pad1[0x0C];
    s32 f570;
    u8 pad2[0x10];
    s32 f584;
    s32 f588;
};

void func_00194E60(Ctl_194E60_eu* self, s32 v)
{
    s32 flag = v;

    if (self->f560 == v) return;
    if (self->f560 == 0 && self->f570 == 0) {
        func_001936A0((Ctl_194E60*)self);
    }
    if (v == 0) {
        if (self->f584 != 0) {
            func_00195928(self, self->f588);
            flag = 1;
            self->f584 = 0;
            self->f588 = -1;
        } else {
            if (self->f570 == 0) {
                func_001936A0((Ctl_194E60*)self);
            }
        }
    }
    func_001AA998(self, flag);
}

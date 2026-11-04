// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f260 sits at 0x570 (not 0x260).
struct Ctl_195928_eu { u8 pad[0x570]; s32 f570; };

void func_00195928(Ctl_195928_eu* self, s32 v)
{
    if (self->f570 != v) {
        self->f570 = v;
        if (v != -1) func_001936A0(self, v);
    }
}

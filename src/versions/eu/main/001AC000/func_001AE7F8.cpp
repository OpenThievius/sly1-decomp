// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the flag field is at 0x570 (US 0x260).
struct Obj_1AE7F8_eu { u8 pad[0x570]; s32 f570; };

void func_001AA998(Obj_1AE7F8_eu* self, s32 flag);

void func_001AE7F8(Obj_1AE7F8_eu* self, s32 flag)
{
    if (flag == 0) {
        self->f570 = 0;
    }
    func_001AA998(self, flag);
}

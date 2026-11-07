// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the flag field is at 0x570 (US 0x260).
struct Obj_1AE7F8_eu { u8 pad[0x570]; s32 f570; };

void SetScreenElementMode(Obj_1AE7F8_eu* self, s32 flag);

void SetElementModeClearingFlag(Obj_1AE7F8_eu* self, s32 flag)
{
    if (flag == 0) {
        self->f570 = 0;
    }
    SetScreenElementMode(self, flag);
}

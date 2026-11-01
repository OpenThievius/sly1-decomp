// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the four fields are at 0x578, 0x580, 0x584 and 0x1190 (US 0x268, 0x270, 0x274, 0xC70).
struct Obj_1E8840_eu { u8 pad0[0x578]; s32 f578; s32 pad1; s32 f580; s32 f584; u8 pad2[0x1190 - 0x588]; s32 f1190; };

void func_001AA8C8(void* self);

void func_001E8840(Obj_1E8840_eu* self)
{
    func_001AA8C8(self);
    self->f1190 = 0;
    self->f584 = 0;
    self->f580 = 0;
    self->f578 = 3;
}

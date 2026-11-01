// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: value sits 784 (0x310) bytes further on than in US.
struct Flag_1AB958_eu { u8 pad[0x290 + 0x310]; s32 value; };

void func_001ABE20(void* self, s32 v);

void func_001AB958(Flag_1AB958_eu* self)
{
    self->value = 1;
    func_001ABE20(self, 0);
}

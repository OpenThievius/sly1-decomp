// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Node_1363D0_eu { u8 pad0[0x5B0]; void* child; };

void func_001363D0(Node_1363D0_eu* self)
{
    func_001AA8C8(self);
    if (self->child != 0) {
        func_00150790(self->child, 2);
    }
}

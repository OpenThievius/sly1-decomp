// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Node_1363D0_eu { u8 pad0[0x5B0]; void* child; };

void func_001363D0(Node_1363D0_eu* self)
{
    ResetScreenElement(self);
    if (self->child != 0) {
        SetStepSequenceState(self->child, 2);
    }
}

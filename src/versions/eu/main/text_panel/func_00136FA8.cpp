// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Owner_136FA8_eu { u8 pad[0x5B0]; void* child; };

void SetTextPanelState(Owner_136FA8_eu* self, s32 mode);

void EndTextPanelState(Owner_136FA8_eu* self)
{
    if (self->child != 0) {
        SetStepSequenceState((StepSequence*)self->child, 4);
    } else {
        SetTextPanelState(self, 0);
    }
}

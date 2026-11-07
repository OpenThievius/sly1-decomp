// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Owner_136EF8_eu { u8 pad0[0x5B0]; StepSequence* child; };

void SetTextPanelState(Owner_136EF8_eu* self, s32 mode);

void ChooseTextPanelState(Owner_136EF8_eu* self)
{
    if (self->child != 0) {
        switch (self->child->mode2D0) {
        case 0:
            SetTextPanelState(self, 2);
            break;
        case 1:
            SetTextPanelState(self, 3);
            break;
        case 2:
            SetTextPanelState(self, 4);
            break;
        }
        SetStepSequenceState(self->child, 3);
    } else {
        SetTextPanelState(self, 1);
    }
}

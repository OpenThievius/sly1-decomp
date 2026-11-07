// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields at 0x590/0x594 and y offset 168.305f
struct State_00136EC8_eu { u8 pad[0x590]; f32 x; f32 y; };
void GetTextPanelCenter(State_00136EC8_eu* self, f32* x, f32* y)
{
    *x = self->x + 320.0f;
    *y = self->y + 168.30508422851562f;
}

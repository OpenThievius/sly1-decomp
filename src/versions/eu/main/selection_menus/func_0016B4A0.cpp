// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's constructor tail of an object: sets its colour, speed fields and a bound-handle slot.
struct Obj_16B4A0_eu {
    u8 pad0[0x518];
    u8 f518[4];
    u8 pad51C[4];
    s32* f520;
    u8 pad524[0x570 - 0x524];
    s32 f570;
    s32 f574;
    f32 f578;
};

void SetupScreenElementText(Obj_16B4A0_eu* self);
void SetScreenElementHoldTime(Obj_16B4A0_eu* self, f32 zero);

void InitSelectionCaption(Obj_16B4A0_eu* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->f520 = (s32*)&g_selectionCaptionFrame;
        *self->f520 = (s32)GetFontById(2);
    }
    SetScreenElementHoldTime(self, 0.0f);
    self->f570 = 0;
    *(u32*)self->f518 = 0xDF7F7F7F;
    self->f574 = 0;
    self->f578 = -g_choiceSoundGap;
}

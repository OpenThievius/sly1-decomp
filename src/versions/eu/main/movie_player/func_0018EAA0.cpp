// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two fields sit at 0xA0 and 0xA4 (not 0x8C and 0x90), and the second call passes 16 (not 8).
struct Obj_18EAA0_eu {
    s32 f00;
    u8 pad04[0x9C];
    s32 fA0;
    s32 fA4;
};

void StopMovieStream(MovieStream* self_)
{
    Obj_18EAA0_eu* self = (Obj_18EAA0_eu*)self_;
    self->f00 = 0;
    StopIopMovieStream();
    SetIopVolumeChannel(2, self->fA0);
    SetIopVolumeChannel(16, self->fA4);
    PopIopChannel2Setting(g_currentWorld);
    ResumeIopVoices(0xFFFFFFFF);
}

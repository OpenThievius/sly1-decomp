// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: no 0x6000 allocation or third sub-object; fields at 0xA0/0xA4, channel 0x10 instead of 8, 0x20000 buffer, returns nothing.
struct Obj_18E940_eu {
    s32 f00;
    s32 f04;
    s32 f08[10];
    u8 sub30[0x20];
    u8 sub50[0x50];
    s32 fA0;
    s32 fA4;
};

s32 func_0018E940(MovieStream* self_)
{
    Obj_18E940_eu* self = (Obj_18E940_eu*)self_;
    func_0011D6A8(0xFFFFFFFF);
    PushIopChannel2Setting(g_currentWorld, 0, 0);
    func_0011E010();
    while (PollIopCommands() != 0) {
    }
    func_0011E110(1);
    SyncDiscRead(0);
    self->fA0 = GetIopVolumeChannel(2);
    self->fA4 = GetIopVolumeChannel(0x10);
    SetIopVolumeChannel(2, 0x400);
    SetIopVolumeChannel(0x10, 0x200);
    self->f00 = 1;
    self->f04 = -1;
    InitRingBuffer(self->sub30, 0x28, self->f08);
    InitRingBuffer(self->sub50, 0x20000, D_002CBB40);
}

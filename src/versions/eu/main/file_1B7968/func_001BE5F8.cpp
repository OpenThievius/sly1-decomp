// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_0011E048 takes one more argument (a tenth, zero).
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);

void func_001BE5F8(KeyRecord* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    if (self == 0) {
        return;
    }
    KeyId l;
    KeyId* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 b = self->wordB ^ self->maskB;
    p->second = b;
    p->first = self->wordA ^ self->maskA;
    if (b == 0) {
        return;
    }
    s32 h = StartStreamedVoice(p->first, 0, 0, 0, 0x400, 0, 2, 0, 0, 0);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoiceLocked = 1;
    g_streamVoicePending = 0;
    SetVolumeChannelFactor(8, 1, 0.5f);
    SetVolumeChannelFactor(8, 0, 0.5f);
    SetVolumeChannelFactor(8, 3, 0.5f);
}

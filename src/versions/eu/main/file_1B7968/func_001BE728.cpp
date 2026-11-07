// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's func_0011E048 takes one more argument (a 0 before the final 1).
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);

void func_001BE728(KeyRecord* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    KeyId l;
    KeyId* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 r = 0;
    if (self != 0) {
        s32 b = self->wordB ^ self->maskB;
        p->second = b;
        l.first = self->wordA ^ self->maskA;
        r = b != 0;
    }
    if (r == 0) {
        return;
    }
    s32 h = StartStreamedVoice(l.first, 0, 0, 0, 0x400, 0, 2, 0, 0, 1);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoicePending = 1;
    RequestStreamCallback(h, ClearStreamVoicePending, (u32)h);
}

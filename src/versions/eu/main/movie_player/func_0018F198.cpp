// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: same flow with a stop flag after the device test
void func_0018F198(Self_18F198* self, IdentityKey* key)
{
    StreamReader loc;
    KeyId pr;
    func_00191E70(4);
    self->mode = FindKeyIndex(key);
    InitStreamReader(&loc, D_002C3B00);
    if (Fill_18F198::Of(&pr, key) && OpenSectorStreamRange(&loc, &pr)) {
        InitMoviePlayback((Obj_18F448*)self, &loc);
        while (!func_0020B0B0(self->list)) {
            AdvanceGameClockElapsed(((u8*)g_gameClock));
            UpdatePadConnection(&g_padRecord);
            s32 flag = 0;
            if (Same_18F198::Of(key, &D_00248490)) flag = g_keyedMovieWatched != 0;
            u32 m;
            if (self->mode >= 16) m = 0;
            else m = 1u << self->mode;
            if (g_saveData->f19F8 & m) flag = 1;
            if (flag) {
                s32 stop = 0;
                if (RestoreFadeRequest(g_screenFade, &g_padRecord, 2)) {
                    stop = 1;
                } else if (g_padRecord.flags & 0x91F) {
                    ClearPadPressedBits(&g_padRecord, 0x91F);
                    stop = 1;
                }
                if (stop) break;
            }
            StepDiscSectorCheck();
            if (g_discSectorCheckState != 3) break;
            StepMovieFrame((Obj_18F6E8*)self);
        }
        if (Same_18F198::Of(key, &D_00248490)) g_keyedMovieWatched = 1;
        FinishMovie((Obj_18F7D0*)self);
        CloseStreamReader(&loc);
    } else {
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    func_00191EB0(4);
    DestroyStreamReader(&loc, 2);
}

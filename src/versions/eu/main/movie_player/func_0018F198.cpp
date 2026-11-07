// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: same flow with a stop flag after the device test
void PlayMovie(MoviePlayer* self, IdentityKey* key)
{
    StreamReader loc;
    KeyId pr;
    SetScreenOwner(4);
    self->movieIndex = FindKeyIndex(key);
    InitStreamReader(&loc, D_002C3B00);
    if (KeyIdOfMovie::Of(&pr, key) && OpenSectorStreamRange(&loc, &pr)) {
        InitMoviePlayback(self, &loc);
        while (!GetMpegDecoderStatus(&self->decoder)) {
            AdvanceGameClockElapsed(((u8*)g_gameClock));
            UpdatePadConnection(&g_padRecord);
            s32 flag = 0;
            if (SameMovieKey::Of(key, &D_00248490)) flag = g_keyedMovieWatched != 0;
            u32 m;
            if (self->movieIndex >= 16) m = 0;
            else m = 1u << self->movieIndex;
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
            StepMovieFrame(self);
        }
        if (SameMovieKey::Of(key, &D_00248490)) g_keyedMovieWatched = 1;
        FinishMovie(self);
        CloseStreamReader(&loc);
    } else {
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    ClearScreenOwner(4);
    DestroyStreamReader(&loc, 2);
}

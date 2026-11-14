// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL definition: same code as US, PAL data addresses.
struct Ctx_eu_16BBA8 { u8 pad0[0x570]; s32 f570; };
void HandleGridSelectorInput(Ctx_eu_16BBA8* ctx, PadRecord* o)
{
    s32 s1;
    s32 r2;

    if ((o->flags & 0x9B0) != 0 || (o->connectionMode == 1 && 5.0f <= g_gameTime[0])) {
        ClearPadPressedBits(o, 0x9B0);
        PopStackElement((ElementStack*)g_elementStack);
        return;
    }
    if ((o->flags & 0x40) != 0) {
        ClearPadPressedBits(o, 0x40);
        if (TestGridEntryBit(ctx->f570) != 0) {
            QueueMovieByIndex(ctx->f570);
            return;
        }
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s1 = GetPadHorizontalStep(o);
    r2 = GetPadVerticalStep(o);
    if (s1 == 0 && r2 == 0) {
        return;
    }
    o->nextStepTimeX = g_gameClock[4] + o->stepDelayX;
    o->nextStepTimeY = g_gameClock[4] + o->stepDelayY;

    {
        s32 n = ctx->f570;
        s32 q = n / 4;
        s32 r = n % 4;
        if (s1 < 0 && r == 0)
            r2 = -1;
        if (s1 > 0 && r == 3)
            r2 = 1;
        s32 dy = r2 + 4;
        s32 dx = s1 + 4;
        q = (q + dy) % 4;
        r = (r + dx) % 4;
        ctx->f570 = q * 4 + r;
    }
    StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

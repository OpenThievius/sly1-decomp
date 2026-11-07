// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the text is element D_eu_00263710 (32 bytes each) of the table at D_00247AB0
extern s32 D_eu_00263710;
void StartPauseMenuExitFade(void)
{
    FadeRequest args;
    args.kind = 1;
    args.text = D_00247AB0 + D_eu_00263710 * 32;
    args.f08 = -1;
    args.f0C = -1;
    args.flags = 4;
    StartScreenFade(&g_screenFade, &args, 0);
}

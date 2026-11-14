// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the same initialiser as US's, its first two array constructions 0x45 entries long where
// US's are 0x39.
void ConstructScreenTextStyles(s32 initialize, s32 priority)
{
    if (priority == 0xFFFF && initialize) {
        s32 i;
        for (i = 0x44; i != -1; i--) {
        }
        for (i = 0x44; i != -1; i--) {
        }
        for (i = 3; i != -1; i--) {
        }
        FillMemory(&g_framedElementStyle, 0, 0x1C);
        g_framedElementStyle.f04 = 0x2D;
        g_framedElementStyle.f08 = 2.0f;
        g_framedElementStyle.f0C = 1.0f;
        g_framedElementStyle.f14 = g_framedElementStyle.f10 = 0.3f;
        g_framedElementStyle.color = 0xFF7D4B00;
        FillMemory(&g_pointerCaptionStyle, 0, 0x1C);
        g_pointerCaptionStyle.f04 = 0x2D;
        g_pointerCaptionStyle.f08 = 2.0f;
        g_pointerCaptionStyle.f0C = -4.0f;
        g_pointerCaptionStyle.f14 = g_pointerCaptionStyle.f10 = 0.3f;
        g_pointerCaptionStyle.color = 0xFF7D4B00;
        FillMemory(&g_copiedCaptionStyle, 0, 0x1C);
        g_copiedCaptionStyle.f04 = 0x3D;
        g_copiedCaptionStyle.f08 = 2.0f;
        g_copiedCaptionStyle.f0C = -4.0f;
        g_copiedCaptionStyle.f14 = g_copiedCaptionStyle.f10 = 0.3f;
        g_copiedCaptionStyle.color = 0xFF7D4B00;
        FillMemory(&g_titleStyle, 0, 0x1C);
        g_titleStyle.f04 = 0x2D;
        g_titleStyle.f08 = 2.0f;
        g_titleStyle.f0C = -4.0f;
        g_titleStyle.f14 = g_titleStyle.f10 = 0.3f;
        g_titleStyle.color = 0xFF7D4B00;
        FillMemory(&g_promptStyle, 0, 0x1C);
        g_promptStyle.f04 = 0x2D;
        g_promptStyle.f08 = 2.0f;
        g_promptStyle.f0C = -4.0f;
        g_promptStyle.f14 = g_promptStyle.f10 = 0.3f;
        g_promptStyle.color = 0xFF7D4B00;
    }
}

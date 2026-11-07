// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's overlay height is 468.61017 where US has 492.80002.
void DrawScreenFade(ScreenFade* self)
{
    if (g_currentWorld != 0 && g_screenFade.mode != 0) {
        s32 mode = self->style;
        if (mode != 1) {
            if (mode < 2) {
                if (mode == 0) goto draw;
            }
            return;
        }
        if (g_coloredTriangleSet != 0) {
        DrawColoredTriangles(g_coloredTriangleSet, self->opacity);
            return;
        }
        draw:
    f32 v = self->opacity * 255.0f;
    WriteColoredSpritePacket(0, 0, 0, (s32)v, &g_gsPacketWriter, 0.0f, 0.0f, 640.0f, 468.61017f);
    }
}

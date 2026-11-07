// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws the 620-wide HUD bar (two coloured segments) with PAL's own constants.
void DrawLoadProgressBar(LoadProgress* o)
{
    BarPacket buf;
    s32 n1;
    s32 n2;
    BarColor c;

    n1 = (s32)((f32)o->total * 620.0f / (f32)o->scale);
    n2 = (s32)((f32)n1 * (f32)(o->total - o->current) / (f32)o->total);
    InitGifPacket(&buf.f);
    UsePacketBufferMemory(&buf.f, 0x40, &buf);
    BeginDmaTag(&buf.f);
    {
        u8 r = o->barColor.r;
        u8 g = o->barColor.g;
        u8 b = o->barColor.b;
        f32 y = TruncateFloat(471.037048f) * 0.915254235f;
        f32 z = (f32)(n2 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, 10.0f, y, z, TruncateFloat(471.037048f) * 0.915254235f + 5.49152565f);
    }
    if (o->stalls <= 0) {
        c = o->color0;
    } else if (o->stalls == 1) {
        c = o->color1;
    } else {
        c = o->color2;
    }
    {
        u8 r = c.r;
        u8 g = c.g;
        u8 b = c.b;
        f32 x = (f32)(n2 + 10);
        f32 y = TruncateFloat(471.037048f) * 0.915254235f;
        f32 z = (f32)(n1 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, x, y, z, TruncateFloat(471.037048f) * 0.915254235f + 5.49152565f);
    }
    EndGifPacket(&buf.f);
    AddDmaEndTag(&buf.f);
    CloseDmaTag(&buf.f);
    DetachPacketBuffer(&buf.f, 0, 0);
    SendPacketToBothBuffers(&buf);
}

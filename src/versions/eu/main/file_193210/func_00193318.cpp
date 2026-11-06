// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws the 620-wide HUD bar (two coloured segments) with PAL's own constants.
void func_00193318(Obj_193318* o)
{
    Buf_193318 buf;
    s32 n1;
    s32 n2;
    Col_193318 c;

    n1 = (s32)((f32)o->w * 620.0f / (f32)o->h);
    n2 = (s32)((f32)n1 * (f32)(o->w - o->x) / (f32)o->w);
    InitGifPacket(&buf.f);
    UsePacketBufferMemory(&buf.f, 0x40, &buf);
    BeginDmaTag(&buf.f);
    {
        u8 r = o->r;
        u8 g = o->g;
        u8 b = o->b;
        f32 y = TruncateFloat(471.037048f) * 0.915254235f;
        f32 z = (f32)(n2 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, 10.0f, y, z, TruncateFloat(471.037048f) * 0.915254235f + 5.49152565f);
    }
    if (o->cnt <= 0) {
        c = o->c0;
    } else if (o->cnt == 1) {
        c = o->c1;
    } else {
        c = o->c2;
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
    func_00168A48(&buf);
}

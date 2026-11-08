// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the arc's position and size 0x310 further on, and PAL's screen height, scale and centre.
struct Arc_eu_1E83E0 {
    u8 pad0[0x52C]; f32 x; f32 y;
    u8 pad1[0x544 - 0x534]; f32 w; f32 h;
};

struct ArcDrawRequest_eu {
    u8 pad00[0x60];
    Arc_eu_1E83E0* arc;     // 0x60
};

void GetArcVisibleRange(Arc_eu_1E83E0* self, s32* first, s32* last);

#define SX_eu_1E83E0(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define SY_eu_1E83E0(y) ((s32)(((y) * 0.5462963f + 1920.0f) * 16.0f))

void DrawArcTickPacket(ArcDrawRequest_eu* request)
{
    PacketWriter buf;
    s32 first, last;
    Arc_eu_1E83E0* self = request->arc;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    PushBackMemoryMark();
    InitGifPacket(&buf);
    AllocateTempPacketBuffer(&buf, 0x200);
    f32 zero = 0.0f;
    f32 right = 640.0f;
    f32 bottom = 468.61017f;
    f32 x0 = zero >? self->x;
    f32 y0 = zero >? self->y;
    f32 x1 = right <? self->x + self->w;
    f32 y1 = bottom <? self->y + self->h;
    BeginGifTag(&buf, 6, 3, 0x44E);
    AddGifRegisterWrite(&buf, 0x47, 0x32001);
    s32 ax = SX_eu_1E83E0(x0);
    s32 ay = SY_eu_1E83E0(y0);
    AddGifXyzfEntry(&buf, ax, ay, 0, 0);
    s32 bx = SX_eu_1E83E0(x1);
    s32 by = SY_eu_1E83E0(y1);
    AddGifXyzfEntry(&buf, bx, by, 0, 0);
    BeginGifTag(&buf, 6, 3, 0x44E);
    AddGifRegisterWrite(&buf, 0x47, 0x3E001);
    AddGifXyzfEntry(&buf, ax, ay, 0xFFFFFF0, 0);
    AddGifXyzfEntry(&buf, bx, by, 0xFFFFFF0, 0);
    BeginGifTag(&buf, 0x46, 5, 0x441EE);
    AddGifRegisterWrite(&buf, 0x47, 0x31001);
    AddGifRegisterWrite(&buf, 0x42, 0x5A);
    AddGifRgbaEntry(&buf, 0x80000000);
    AddGifXyzfEntry(&buf, ax, ay, 0, 0);
    AddGifXyzfEntry(&buf, bx, by, 0, 0);
    BeginGifTag(&buf, 0, 1, 0xE);
    AddGifRegisterWrite(&buf, 0x40, 0xFF0000027F0000ULL);
    EndGifPacket(&buf);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifDirectFromWriter(&g_vifPacketWriter, &buf);
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}

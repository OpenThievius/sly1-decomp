// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the arc's fields 0x310 further on, and PAL's screen height, scale and centre.
struct Arc_eu_1E80D8 {
    u8 pad0[0x52C]; f32 x; f32 y;
    u8 pad1[0x544 - 0x534]; f32 w; f32 h;
    u8 pad2[0x584 - 0x54C]; void* current;
};

struct ArcDrawRequest_eu_1E80D8 {
    u8 pad00[0x60];
    Arc_eu_1E80D8* arc;     // 0x60
};

void GetArcVisibleRange(Arc_eu_1E80D8* self, s32* first, s32* last);
void WriteArcOutlineVertices(Arc_eu_1E80D8* self, PacketWriter* buf, s32 a);

void DrawArcOutlinePacket(ArcDrawRequest_eu_1E80D8* request)
{
    PacketWriter buf;
    s32 first, last;
    Arc_eu_1E80D8* self = request->arc;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    if (D_00270458 != 4) {
        if (AreFloatsNearlyEqual(g_camera->zoom, *(f32*)((u8*)self->current + 0x2D4), 1e-4f) == 0) {
            f32 zoom = g_camera->zoom;
            f32 f1C8 = g_camera->zoomGoal;
            SnapCameraZoom(g_camera, *(f32*)((u8*)self->current + 0x2D4));
            WriteCameraMatricesPacket(g_camera);
            SnapCameraZoom(g_camera, zoom);
            g_camera->zoomGoal = f1C8;
        }
    }
    PushBackMemoryMark();
    InitGifPacket(&buf);
    AllocateTempPacketBuffer(&buf, 0x100);
    f32 zero = 0.0f;
    f32 right = 640.0f;
    f32 bottom = 468.61017f;
    f32 x0 = zero >? self->x;
    f32 y0 = zero >? self->y;
    f32 x1 = right <? self->x + self->w;
    f32 y1 = bottom <? self->y + self->h;
    BeginGifTag(&buf, 0, 1, 0xE);
    s32 px = (s32)x0;
    s32 pw = (s32)x1 - 1;
    y0 *= 0.5462963f;
    y1 *= 0.5462963f;
    s32 py = (s32)y0;
    s32 pz = (s32)y1 - 1;
    AddGifRegisterWrite(&buf, 0x40, (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48));
    BeginGifTag(&buf, 6, 5, 0x441EE);
    AddGifRegisterWrite(&buf, 0x47, 0x30000);
    AddGifRegisterWrite(&buf, 0x42, 0x5A);
    AddGifRgbaEntry(&buf, 0);
    AddGifXyzfEntry(&buf, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 + 1920.0f) * 16.0f), 0xFFFFFF0, 0);
    AddGifXyzfEntry(&buf, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 + 1920.0f) * 16.0f), 0xFFFFFF0, 0);
    BeginGifTag(&buf, 0, 1, 0xE);
    AddGifRegisterWrite(&buf, 0x47, 0x32001);
    BeginGifTag(&buf, 4, 1, 4);
    WriteArcOutlineVertices(self, &buf, 0);
    EndGifPacket(&buf);
    BeginDmaTag(&g_vifPacketWriter);
    WriteVifFlushE(&g_vifPacketWriter);
    WriteVifDirectFromWriter(&g_vifPacketWriter, &buf);
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}

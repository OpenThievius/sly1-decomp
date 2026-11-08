// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 698/704 (99.1%), checked 2026-11-07
// NEAR: identical to retail but for the order of two hoisted constants before the loop (1728.0 into f24 then 16.0 into f20 in retail; here 16.0 first).
#include "common.h"
#include "screen_element.h"
#include "camera.h"
#include "packet_writer.h"
#include "globals.h"
#include "vu0.h"
#include "shapes.h"
extern f32 D_002641B8[3];
extern f32 D_002641C4;
extern f32 D_002641C8[10];
extern f32 D_002641F0[16];
extern f32 g_gameTime;

struct SpritePackets {
    s32 count;
    s32 data;
};

struct SpriteIcon {
    u8 pad00[0x1C];
    SpritePackets* packets;     // 0x1C
};

extern f32 g_frameStep;
s32 AreMenusAndFadeClear(void);
f32 ApproachValueWithRamp(void* tune, s32 zero, f32 cur, f32 target, f32 dt);
void AppendPacketQuadwords(PacketWriter* w, s32 count, s32 data);
void BeginGifTag(PacketWriter* b, s32 a, s32 c, u64 d);
void AddGifRegisterWrite(PacketWriter* b, s32 reg, u64 v);
void AddGifStEntry(PacketWriter* b, f32 x, f32 y, f32 z);
void AddGifRgbaEntry(PacketWriter* b, u32 c);
void AddGifXyzfEntry(PacketWriter* b, s32 x, s32 y, s32 z, s32 f);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

void DrawSpinningSpriteElement(T217D_BF0* self)
{
    Rgba4 col;
    Mat02 m;
    Vec02 p;
    if (self->icon == 0) {
        return;
    }
    f32 target = AreMenusAndFadeClear() != 0 ? 1.0f : 0.0f;
    if (g_camera->f224 != 0) {
        self->f288 = target;
    } else {
        self->f288 = ApproachValueWithRamp(D_002641B8, 0, self->f288, target, g_frameStep);
    }
    if (self->f288 == 0.0f) {
        return;
    }
    AppendPacketQuadwords(&g_gsPacketWriter, ((SpriteIcon*)self->icon)->packets->count - 1, ((SpriteIcon*)self->icon)->packets->data + 0x10);
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x30000);
    *(u32*)&col = 0x80FFFFFF;
    BuildAxisAngleMatrix(&g_unitZVector, &m, g_gameTime * D_002641C4);
    BeginGifTag(&g_gsPacketWriter, 0x5C, 3, 0x412);
    col.a = (u8)(s32)(self->f288 * (f32)col.a);
    for (u32 i = 0; i < 4; i++) {
        f32 sx = self->f270 * 320.0f + 320.0f;
        f32 sy = self->f274 * -246.400009f + 246.400009f;
        Vu0::Q(p) = Vu0::Rotate(m, Vu0::Q(D_002641F0[i * 4]));
        p.x = p.x + sx;
        p.y = p.y + sy;
        AddGifStEntry(&g_gsPacketWriter, D_002641C8[i * 2], D_002641C8[i * 2 + 1], 1.0f);
        AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
        s32 px = (s32)((p.x + 1728.0f) * 16.0f);
        s32 py = (s32)((p.y * 0.45454547f + 1936.0f) * 16.0f);
        AddGifXyzfEntry(&g_gsPacketWriter, px, py, 0, 0);
    }
}

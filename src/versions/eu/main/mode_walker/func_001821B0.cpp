// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the element's fields lie 0x310 later (aim at 0x580, icon 0x594, fade 0x598) and the
// screen is 640 by 468.6 (scale 0.5463, centre 234.3 and 1920).
struct SpinningSprite_eu {
    u8 pad0[0x580];
    f32 aim[4];
    u8 pad1[0x594 - 0x590];
    s32 icon;
    f32 f288;
};
void DrawSpinningSpriteElement(SpinningSprite_eu* self)
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
        self->f288 = ApproachValueWithRamp(self->f288, target, g_frameStep, D_002641B8, 0);
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
        f32 sx = self->aim[0] * 320.0f + 320.0f;
        f32 sy = self->aim[1] * -234.305084f + 234.305084f;
        Vu0::Q(p) = Vu0::Rotate(m, Vu0::Q(D_002641F0[i * 4]));
        p.x = p.x + sx;
        p.y = p.y + sy;
        AddGifStEntry(&g_gsPacketWriter, D_002641C8[i * 2], D_002641C8[i * 2 + 1], 1.0f);
        AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
        f32 left = 1728.0f;
        s32 px = (s32)((p.x + left) * 16.0f);
        s32 py = (s32)((p.y * 0.546296298f + 1920.0f) * 16.0f);
        AddGifXyzfEntry(&g_gsPacketWriter, px, py, 0, 0);
    }
}

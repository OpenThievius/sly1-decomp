// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a framed rectangle around the owner's bounds using the GS-style draw helpers (positions in 12.4 fixed point).
struct Inner_eu_1AEA90 { u16 x; u16 y; };
struct Link_eu_1AEA90 { u8 pad0[0xC]; Inner_eu_1AEA90** rect; };
struct Peer_eu_1AEA90 { u8 pad0[0x14]; Link_eu_1AEA90* link; };
struct Obj_eu_1AEA90 {
    u8 pad0[0x52C]; f32 f52C; f32 f530; u8 pad1[0x544 - 0x534]; f32 f544; f32 f548;
    u8 pad2[0x570 - 0x54C]; Peer_eu_1AEA90* peer;
};
extern u8 D_eu_00263590[];
void DrawScreenElementText(void* self);
s32 GetTextureRegisterBits(void* p, s32 a, s32 b);

void DrawTitleElement(Obj_eu_1AEA90* self)
{
    s32 tmp[4];
    if (self->peer != 0) {
        Inner_eu_1AEA90* r = *self->peer->link->rect;
        s32 id = GetTextureRegisterBits(self->peer->link, 0, 0);
        PacketWriter* ctx = (PacketWriter*)D_eu_00263590;
        BeginGifTag(ctx, 0x156, 10, 0x43431EEEEEULL);
        AddGifRegisterWrite(ctx, 0x47, 0x33001);
        AddGifRegisterWrite(ctx, 0x42, 0x44);
        AddGifRegisterWrite(ctx, 6, id);
        AddGifRegisterWrite(ctx, 0x14, 0x60);
        AddGifRegisterWrite(ctx, 8, 5);
        tmp[0] = (s32)0x80808080;
        AddGifRgbaEntry(ctx, tmp[0]);
        AddGifUvEntry(ctx, 0, r->y << 4);
        AddGifXyzfEntry(ctx, (s32)((self->f52C + 1728.0f) * 16.0f),
                         (s32)((self->f530 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        AddGifUvEntry(ctx, r->x << 4, 0);
        AddGifXyzfEntry(ctx, (s32)(((self->f52C + self->f544) + 1728.0f) * 16.0f),
                         (s32)(((self->f530 + self->f548) * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    } else {
        DrawScreenElementText(self);
    }
}

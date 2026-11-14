// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws an object and its child through a draw list, scaled by a pulsing factor.
struct __attribute__((packed)) Pk4_16B860 { s32 v; };
struct Obj_16B860_eu {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 pad9[0x518 - 0xA];
    Pk4_16B860 f518;
    f32 f51c;
    void* f520;
    u8 pad524[0x52C - 0x524];
    f32 f52c;
    f32 f530;
    u8 pad534[0x544 - 0x534];
    f32 f544;
    f32 f548;
    f32 f54c;
    u8 pad550[0x570 - 0x550];
    s32 f570;
};

extern f32 g_elapsedTime;
f32 Sine(f32 x);
void PushFontScale(s32 handle, f32 a, f32 b);
void* InitTextReader(TextReader* self, char* text, Font* font);
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);
void PopFontScale(s32 handle);

void InitWideTextReader(void* out, void* p, s32 handle, s32 z);
void DrawWrappedAlignedText(void* a, void* b, s32 c, void* d);
void SetTextLayoutVerticalPlacement(CaptionLayout* out, s32 v);
struct Out_eu_16B860 : CaptionLayout {
    void Mode(s32 v) { SetTextLayoutVerticalPlacement(this, v); }
    void Draw(void* loc, s32 z, void* tbl) { DrawWrappedAlignedText(loc, this, z, tbl); }
};

void DrawSelectionCaption(Obj_16B860_eu* self)
{
    Pk4_16B860 tmp;
    Out_eu_16B860 out;
    Pk4_16B860 slot;
    u8 loc[0xC0];

    if (self->f570 != 0 && self->f8 != 0) {
        tmp = self->f518;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->f54c);
        f32 p = self->f544;
        f32 q = self->f548;
        s32 held = tmp.v;
        out.Pos(self->f52c, self->f530);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(0);
        out.FlagB(1);
        out.Mode(1);

        u8* h = (u8*)self->f520;
        if (h != 0) {
            slot = *(Pk4_16B860*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->f54c);
            CaptionDrawer::Draw((Font**)self->f520, &out, &g_gsPacketWriter);
            *(Pk4_16B860*)((u8*)self->f520 + 0x18) = slot;
        }
        f32 r = Sine(g_elapsedTime * 10.0f);
        f32 t = r * 0.5f + 0.5f;
        f32 k = (1.0f - t) * 0.9f + t;
        f32 v = self->f51c * k;
        PushFontScale(self->f4, v, v);
        InitWideTextReader(loc, &self->f8, self->f4, 0);
        out.Draw(loc, 0, &g_gsPacketWriter);
        PopFontScale(self->f4);
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields moved (+0x310), u16 flag at +8, extra func_eu_001374E0 call, PAL-only name lookup DrawFontString and a buffer built by func_eu_0015DCB8/func_eu_0015E7E0.
struct Actor_001AB710_eu { u8 pad0[4]; Font* p4; u16 f08; u8 pad1[0x518 - 0xA]; s32 f518; f32 f51C; void* f520; u8 pad2[8]; f32 f52C; f32 f530; u8 pad3[0x10]; f32 f544; f32 f548; u8 pad4[0x40]; T217D_Word w58C; u8 pad5[4]; s32 f594; };

void SetTextLayoutVerticalPlacement(void* out, s32 v);
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
void InitWideTextReader(void* buf, void* name, void* p, s32 zero);
void DrawWrappedAlignedText(void* buf, void* out, s32 zero, void* d);

void DrawTimerElement(Actor_001AB710_eu* self)
{
    Layout_137228 L;
    Quad4 tag;
    T217D_Word warn;
    u8 buf[0xC0];
    if (self->f08 != 0) {
        f32 f544 = self->f544;
        f32 f548 = self->f548;
        s32 s0v = self->f518;
        ((Layout_137228*)&L)->Pos(self->f52C, self->f530);
        ((Layout_137228*)&L)->Size(f544, f548);
        tag.w[0] = s0v;
        ((Layout_137228*)&L)->Color(&tag.w[0]);
        ((Layout_137228*)&L)->SetF14(0);
        ((Layout_137228*)&L)->SetF18(0);
        SetTextLayoutVerticalPlacement(&L, 0);
        void* obj = self->f520;
        if (obj != 0) {
            Font* sub = *(Font**)obj;
            if (sub != 0) {
                const FontVt* d = sub->vt;
                d->drawBox((Font*)((u8*)sub + d->adj9), obj, &L, &g_gsPacketWriter);
            }
        }
        f32 v = self->f51C;
        u8* dp = (u8*)&g_gsPacketWriter;
        PushFontScale(self->p4, v, v);
        ((u8*)&tag)[0] = 0x54;
        ((u8*)&tag)[1] = 0;
        DrawFontString(self->p4, (const char*)&tag, (StringLayout*)&L, 0, (PacketWriter*)dp);
        f32 r = MeasureFontString(self->p4, (const char*)&tag);
        f32 a = self->f52C + r;
        L.y = self->f530;
        L.x = a;
        if (self->f594 != 0) {
            warn = self->w58C;
            *(T217D_Word*)&L.color = warn;
        }
        InitWideTextReader(buf, (u8*)self + 10, self->p4, 0);
        DrawWrappedAlignedText(buf, &L, 0, dp);
        PopFontScale(self->p4);
    }
}

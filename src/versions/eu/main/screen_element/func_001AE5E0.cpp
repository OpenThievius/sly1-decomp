// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the text moves 0x310 bytes later in the element, and the text reader is built by a PAL-only
// function that takes a fourth word (func_eu_0015DCB8). PAL never sets the size it hands to
// SetTextLayoutSize: its two floats are read before they are written (they sit in $f20 and $f21).

struct Element_eu_1AE5E0 {
    u8 pad0[4];
    Font* font;                 // 0x04
    char text[0x510];           // 0x08
    s32 color;                  // 0x518
    f32 scale;                  // 0x51C
    u8 pad520[0x52C - 0x520];
    f32 x;                      // 0x52C
    f32 y;                      // 0x530
    u8 pad534[0x564 - 0x534];
    f32 since;                  // 0x564
};

void func_eu_0015DCB8(void* reader, const char* text, Font* font, s32 zero);
void func_eu_001374E0(void* layout, s32 flag);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);

struct LayoutBuilder_eu_1AE5E0 : LayoutBuilder {
    void FlagC(s32 f) { func_eu_001374E0(this, f); }
};

void func_001AE5E0(Element_eu_1AE5E0* self)
{
    PopCurve curve;
    u8 reader[0xC0];
    LayoutBuilder_eu_1AE5E0 out;
    s32 tmp;
    f32 w;
    f32 h;
    f32 size = 1.0f;
    curve.start = D_002744A8;
    curve.none = 0;
    curve.k = (1.0f - D_002744A8) / (D_002744A4 * D_002744A4);
    f32 peak = Fpu::Sqrt(D_002744A8 / curve.k);
    f32 age = g_elapsedTime - self->since;
    if (!(peak + D_002744A4 < age)) {
        f32 t = age - peak;
        size = (curve.floor >? curve.start + t * (t * curve.k));
    }
    size *= self->scale;
    if (!(size <= 0.0f)) {
        PushFontScale(self->font, size, size);
        func_eu_0015DCB8(reader, self->text, self->font, 0);
        s32 held = self->color;
        out.Pos(self->x, self->y);
        out.Size(w, h);
        tmp = held;
        out.Color(&tmp);
        out.FlagA(0);
        out.FlagB(0);
        out.FlagC(0);
        func_eu_0015E7E0(reader, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

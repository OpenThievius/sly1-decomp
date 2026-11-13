// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: a label's name is read into a text reader (0xC0 bytes, func_eu_0015DCB8)
// and laid out into the panel's line record at 0x408 (func_eu_0015E4A8), whose height (0x410)
// places and sizes the label; the layout carries that record in its word at 0x14 and has a fourth
// word to clear (func_eu_001374E0); the reader is drawn (func_eu_0015E7E0), and the screen is PAL's
// 512 lines high. The frame shows the order of the body's locals: the layout at 0xB0, the style at
// 0xD0 and the reader at 0xF0, though the style is filled after the reader is read, so the three
// are declared together and the style assigned where US constructs it. The colour's quadword sits
// in the slot the first loop's temporaries freed (0xA0) and its address is formed at the call:
// its word is written through Words() as it is passed, where US's form hoists the address.
struct TextLines_eu_134CE0 {
    u8 pad0[8];
    f32 height;                 // 0x08: the lines' height
    u8 padC[0x110 - 0xC];
};

struct Obj_eu_134CE0 {
    u8 pad0[4];
    Font* font;                 // 0x004
    u8 pad8[0x408 - 8];
    TextLines_eu_134CE0 lines;  // 0x408
    u8 pad518[0x520 - 0x518];
    Font** frame;               // 0x520
};

struct TextReader_eu_134CE0 { u8 bytes[0xC0]; };

void func_eu_0015DCB8(TextReader_eu_134CE0* out, u8* text, Font* font, s32 zero);
void func_eu_0015E4A8(TextReader_eu_134CE0* reader, TextLines_eu_134CE0* lines, f32 w);
void func_eu_0015E7E0(TextReader_eu_134CE0* reader, Layout_137228* layout, s32 zero, PacketWriter* gs);
void func_eu_001374E0(Layout_137228* layout, s32 value);

struct Gfx_eu_134CE0 {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
    }
};

struct ScreenLayout_eu_134CE0 {
    static s32* Words(Quad4& q)
    {
        return q.w;
    }

    static void Reset(Layout_137228* l)
    {
        Quad4 col;
        l->Pos(0.0f, 0.0f);
        l->Size(640.0f, 468.610168f);
        Words(col)[0] = 0xFF808080;
        l->Color(Words(col));
        l->SetF14(0);
        l->SetF18(0);
        func_eu_001374E0(l, 0);
    }
};

void DrawTextPanelMarkers(Obj_eu_134CE0* self, PacketWriter* q)
{
    TextPointObject* objs[32];
    Vec02 pos;
    Vec02 screen;
    s32 i;
    s32 shown = 0;
    TextPointObject* nearest = 0;
    s32 count = GatherObjectsById(*(s32*)g_currentWorld, 5, 0x82, 0, 0x20, objs);
    SortElements(objs, count, 4, CompareEntriesFarthestFirst);
    f32 best = 3.4028235e+38f;
    for (i = 0; i < count; i++) {
        TextPointObject* obj = objs[i];
        ConvertPositionToWorld(obj, &pos);
        Camera* cam = (Camera*)g_camera;
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(cam->f40));
        if (4000.0f < Vu0::ToFloat(Vu0::Length(d))) {
            continue;
        }
        u128 ones = Vu0::Ones();
        Vu0::Vec r = Vu0::Vec::Scalar(0.0f);
        if ((Vu0::PlaneSigns(Vu0::Vec::Of(cam->planes[0]).q, Vu0::Vec::Of(cam->planes[1]).q, Vu0::Vec::Of(cam->planes[2]).q, d.q, ones, r.q) ^ 0xF0) != 0) {
            ResetTextPointToHalf(obj);
        } else {
            objs[shown++] = obj;
            ProjectPointToCamera((Camera*)g_camera, &pos, &screen);
            Vu0::Vec e = Vu0::Sub(Vu0::Vec::Of(screen), Vu0::Vec::Of(D_00261190));
            f32 c = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
            if (c < best) {
                nearest = obj;
                best = c;
            }
        }
    }
    for (i = 0; i < shown; i++) {
        TextPointObject* obj = objs[i];
        ConvertPositionToWorld(obj, &pos);
        Layout_137228 layout;
        PanelStyle style;
        TextReader_eu_134CE0 reader;
        const f32* k = D_002611A0;
        const ValueRange* lim = &g_unitRange;
        ProjectPointToCamera((Camera*)g_camera, &pos, &screen);
        Vu0::Vec e = Vu0::Vec::Of(screen);
        f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(e.q, e.q)));
        f32 scale = k[0] + len * (k[1] + len * k[2]);
        f32 alpha = lim->Limit(scale);
        if (obj != nearest) {
            alpha *= D_002611BC;
        }
        obj->f54 = ApproachValueWithRamp(obj->f54, alpha, g_gameClock[5], D_002611B0, 0);
        obj->f58 = ApproachValueWithRamp(obj->f58, obj == nearest ? D_00261184 : D_00261188, g_gameClock[5], D_002611C0, 0);
        PushFontScale(self->font, obj->f58, obj->f58);
        ScreenLayout_eu_134CE0::Reset(&layout);
        func_eu_0015DCB8(&reader, obj->text, self->font, 0);
        func_eu_0015E4A8(&reader, &self->lines, D_002611CC * obj->f58);
        f32 h = self->lines.height;
        f32 x = screen.x * 320.0f + 320.0f + D_002611D0 * obj->f58;
        f32 y = screen.y * -234.305084f + 234.305084f + D_002611D4 * obj->f58 - h;
        layout.x = x;
        layout.y = y;
        layout.w = D_002611CC * obj->f58;
        layout.h = h;
        layout.f14 = (s32)&self->lines;
        style = D_00261168;
        Font* font = GetFontById(2);
        style.f0 = (s32)font;
        ((u8*)&style.f18)[3] = (s32)(alpha * (f32)((u8*)&style.f18)[3]);
        style.f8 *= obj->f58;
        style.fC *= obj->f58;
        StyleDrawer::Draw((Font**)&style, &layout, q);
        ((u8*)&layout.color)[3] = (s32)(alpha * (f32)((u8*)&layout.color)[3]);
        func_eu_0015E7E0(&reader, &layout, 0, q);
        BeginGifTag(q, 0xC1, 3, 0x441);
        AddGifRgbaEntry(q, ((u32*)self->frame)[6]);
        AddGifXyzfEntry(q, Gfx_eu_134CE0::ScreenX(x + D_002611D8 * obj->f58), Gfx_eu_134CE0::ScreenY(y + self->lines.height + D_002611DC * obj->f58), 0, 0);
        y = screen.y * -234.305084f + 234.305084f;
        x = screen.x * 320.0f + 320.0f;
        AddGifXyzfEntry(q, Gfx_eu_134CE0::ScreenX(x), Gfx_eu_134CE0::ScreenY(y), 0, 0);
        PopFontScale(self->font);
    }
}

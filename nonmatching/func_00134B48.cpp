// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1712/1756 (97.5%), checked 2026-11-09
#include "common.h"
#include "layout_137228.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"
#include "shapes.h"
#include "pad_record.h"
#include "vu0.h"
#include "camera.h"
#include "point_object.h"
// NEAR (2026-11-09, w10): registers and spill slots are retail's; two runs of the second
// loop's preheader are in another order (sched2): retail has `sw a1,0x21C(sp)` (&pos's spill)
// between the 1728.0 and 16.0 constants and `sw a2,0x220(sp)` before 1936.0, where ours puts
// the four constant loads first. sched1 decides it: in the preheader, the three loop-invariant
// %hi/%lo pairs (D_002611A0's, the clock's and g_unitRange's) rank before &pos (a %lo that ends
// its %hi has register weight 0), so &pos is the seventh ALU insn, beside the third constant;
// retail's order needs it fifth, beside the first: only two pairs. The likely missing one is
// g_unitRange's: its %lo (Limit's this, life 4 in loop.c's second pass, threshold about 85
// against 234 insns) is moved; with a life of 2 it would not be. No form of the clamp tried
// keeps it in the loop with retail's code (Clamp, a range pointer outside or at the top of the
// body change the code). Measured (2026-11-09, w10): loop.c's threshold here is 79, so any
// inline `this` (life >= 3: the contour's two notes) is moved. A clamp reading `hi` only in
// its else arm stays in the loop (maybe_never) and gives retail's preheader order exactly, but
// then g_unitRange's %hi pseudo (5 refs over 466) outranks the clock's address (5 over 486)
// and takes s4. Retail fits only a hoisted `this` whose %hi was set in an earlier block (its
// %lo then not raised by adjust_priority); no form found (docs/TOOLCHAIN.md, func_001316E8).
// What landed here (2026-11-09): the five setters in an inline helper (ScreenLayout::Reset,
// as PAL's func_001316E8: the layout's address formed at each call, the colour buffer's from a
// spill slot), the font's box through the file family's StyleDrawer::Draw (retail forms &layout
// for drawBox and passes &style from a spill slot), the length of `screen` as a Vec (T = 189
// buckets: retail's spill-slot order and s4/s8), the coefficient table read through a pointer
// named before the projection (its %lo moves in loop.c's first pass, before the clock's, as
// retail's preheader has them), ToFloatMoved for that length (the polynomial's mul.s before
// the range's lo load), the clock's step read at each call, the screen positions through
// CenterFrameMath::ScreenX/ScreenY.

struct CameraHeading { u8 pad0[0x40]; s32 f40[4]; u8 pad[0x468 - 0x50]; f32 heading; u8 pad46C[0x478 - 0x46C]; f32 f478; };
extern CameraHeading* g_camera;
extern f32 g_gameClock[];
extern u8 g_currentWorld[];
struct PanelStyle {
    s32 f0;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
};
extern PanelStyle D_00261168;
extern f32 D_00261184;
extern f32 D_00261188;
extern f32 D_00261190[4];
extern f32 D_002611A0[4];
extern f32 D_002611B0[3];
extern f32 D_002611BC;
extern f32 D_002611C0[3];
extern f32 D_002611CC;
extern f32 D_002611D0;
extern f32 D_002611D4;
extern f32 D_002611D8;
extern f32 D_002611DC;
s32 GatherObjectsById(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void ResetTextPointToHalf(void* p);
void ConvertPositionToWorld(void* obj, Vec02* out);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);
void BeginGifTag(PacketWriter* q, s32 a, s32 b, u64 c);
void AddGifRgbaEntry(PacketWriter* q, u32 v);
void AddGifXyzfEntry(PacketWriter* q, s32 a, s32 b, s32 c, s32 d);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
void DrawFontString(Font* font, const char* text, Layout_137228* layout, s32 zero, PacketWriter* gs);
s32 func_00134AA0(void** a, void** b);

void SortElements(void* base, s32 n, s32 size, s32 (*cmp)(void**, void**));
void ProjectPointToCamera(Camera* cam, Vec02* pos, Vec02* out);
f32 MeasureFontStringHeight(Font* font, const char* text, f32 w);
Font* GetFontById(s32 k);

struct CenterFrameMath {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
    }
};

struct StyleDrawer {
    static void Draw(Font** h, Layout_137228* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

struct ScreenLayout {
    static s32* Words(Quad4& q)
    {
        return q.w;
    }

    static void Reset(Layout_137228* l)
    {
        Quad4 col;
        l->Pos(0.0f, 0.0f);
        l->Size(640.0f, 492.800018f);
        col.w[0] = 0xFF808080;
        l->Color(Words(col));
        l->SetF14(0);
        l->SetF18(0);
    }
};

// The labels of the text points (class 0x82) in view: each gathered point the camera sees
// within 4000 is drawn at its place on the screen, its name with spaces for underscores, the
// one nearest the screen's centre larger and opaque; the rest are reset (ResetTextPointToHalf).
void func_00134B48(T217D_440* self, PacketWriter* q)
{
    TextPointObject* objs[32];
    Vec02 pos;
    Vec02 screen;
    s32 i;
    s32 shown = 0;
    TextPointObject* nearest = 0;
    s32 count = GatherObjectsById(*(s32*)g_currentWorld, 5, 0x82, 0, 0x20, objs);
    SortElements(objs, count, 4, func_00134AA0);
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
        char buf[0x100];
        Layout_137228 layout;
        const char* s = (const char*)obj->text;
        char* t = buf;
        for (; *s != 0; s++) {
            if (*s == '_') {
                *t = ' ';
            } else {
                *t = *s;
            }
            t++;
            if ((u32)(t - buf) >= 0xFF) {
                break;
            }
        }
        *t = 0;
        const f32* k = D_002611A0;
        ProjectPointToCamera((Camera*)g_camera, &pos, &screen);
        Vu0::Vec e = Vu0::Vec::Of(screen);
        f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(e.q, e.q)));
        f32 scale = k[0] + len * (k[1] + len * k[2]);
        f32 alpha = g_unitRange.Limit(scale);
        if (obj != nearest) {
            alpha *= D_002611BC;
        }
        obj->f54 = ApproachValueWithRamp(obj->f54, alpha, g_gameClock[5], D_002611B0, 0);
        obj->f58 = ApproachValueWithRamp(obj->f58, obj == nearest ? D_00261184 : D_00261188, g_gameClock[5], D_002611C0, 0);
        PushFontScale(self->font, obj->f58, obj->f58);
        ScreenLayout::Reset(&layout);
        f32 h = MeasureFontStringHeight(self->font, buf, D_002611CC * obj->f58);
        f32 x = screen.x * 320.0f + 320.0f + D_002611D0 * obj->f58;
        f32 y = screen.y * -246.400009f + 246.400009f + D_002611D4 * obj->f58 - h;
        layout.x = x;
        layout.y = y;
        layout.w = D_002611CC * obj->f58;
        layout.h = h;
        PanelStyle style(D_00261168);
        Font* font = GetFontById(2);
        style.f0 = (s32)font;
        ((u8*)&style.f18)[3] = (s32)(alpha * (f32)((u8*)&style.f18)[3]);
        style.f8 *= obj->f58;
        style.fC *= obj->f58;
        StyleDrawer::Draw((Font**)&style, &layout, q);
        ((u8*)&layout.color)[3] = (s32)(alpha * (f32)((u8*)&layout.color)[3]);
        DrawFontString(self->font, buf, &layout, 0, q);
        BeginGifTag(q, 0xC1, 3, 0x441);
        AddGifRgbaEntry(q, ((u32*)self->frame)[6]);
        AddGifXyzfEntry(q, CenterFrameMath::ScreenX(x + D_002611D8 * obj->f58), CenterFrameMath::ScreenY(y + h + D_002611DC * obj->f58), 0, 0);
        y = screen.y * -246.400009f + 246.400009f;
        x = screen.x * 320.0f + 320.0f;
        AddGifXyzfEntry(q, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y), 0, 0);
        PopFontScale(self->font);
    }
}

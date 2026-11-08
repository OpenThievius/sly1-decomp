// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1764/1756, checked 2026-11-08
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
// NEAR (2026-11-08, night-large7): the first loop is retail's to the register (its Vec values and
// the array indexed by i and by the count shown give retail's 81-insn loop, the givs and the
// reversed counter; i is one variable for both loops). The second loop differs only in its
// allocation: retail keeps &g_gameClock in s4 (both steps read through it) and spills &layout
// (DrawFontString's), forming it again (addiu a0, sp, 0x1B0) for each method call; here &layout
// takes s2 for every use and the clock's address is formed at each read, two more insns.

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

// The game clock as this function reads it: its step at 0x14.
struct PanelClock { u8 pad0[0x14]; f32 step; };
void SortElements(void* base, s32 n, s32 size, s32 (*cmp)(void**, void**));
void ProjectPointToCamera(Camera* cam, Vec02* pos, Vec02* out);
f32 MeasureFontStringHeight(Font* font, const char* text, f32 w);
Font* GetFontById(s32 k);

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
    PanelClock* clock = (PanelClock*)g_gameClock;
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
        ProjectPointToCamera((Camera*)g_camera, &pos, &screen);
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(screen), Vu0::Q(screen))));
        f32 scale = D_002611A0[0] + len * (D_002611A0[1] + len * D_002611A0[2]);
        f32 alpha = g_unitRange.Limit(scale);
        if (obj != nearest) {
            alpha *= D_002611BC;
        }
        obj->f54 = ApproachValueWithRamp(obj->f54, alpha, clock->step, D_002611B0, 0);
        obj->f58 = ApproachValueWithRamp(obj->f58, obj == nearest ? D_00261184 : D_00261188, clock->step, D_002611C0, 0);
        PushFontScale(self->font, obj->f58, obj->f58);
        layout.Pos(0.0f, 0.0f);
        layout.Size(640.0f, 492.800018f);
        {
            Quad4 col;
            col.w[0] = 0xFF808080;
            layout.Color(col.w);
        }
        layout.SetF14(0);
        layout.SetF18(0);
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
        if (font != 0) {
            font->vt->drawBox((Font*)((u8*)font + font->vt->adj9), &style, &layout, q);
        }
        ((u8*)&layout.color)[3] = (s32)(alpha * (f32)((u8*)&layout.color)[3]);
        DrawFontString(self->font, buf, &layout, 0, q);
        BeginGifTag(q, 0xC1, 3, 0x441);
        AddGifRgbaEntry(q, ((u32*)self->frame)[6]);
        AddGifXyzfEntry(q, (s32)((x + D_002611D8 * obj->f58 + 1728.0f) * 16.0f), (s32)(((y + h + D_002611DC * obj->f58) * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        y = screen.y * -246.400009f + 246.400009f;
        x = screen.x * 320.0f + 320.0f;
        AddGifXyzfEntry(q, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        PopFontScale(self->font);
    }
}

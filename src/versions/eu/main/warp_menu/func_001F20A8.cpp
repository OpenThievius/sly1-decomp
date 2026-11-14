// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the warp map reads its label sizes from PAL's own addresses (D_eu_0027FDAC and D_eu_0027FDB0 are
// US D_00276648 and D_00276650).
// PAL's warp menu: its fields lie 0x2EC (blend, rgba) and 0x310 (current) later.
struct WarpMenu_eu {
    u8 pad0[0x518];
    T217D_Rgba rgba;
    u8 pad1[0x54C - 0x518 - sizeof(T217D_Rgba)];
    f32 blend;
    u8 pad2[0x570 - 0x550];
    WarpPage* current;
};
extern f32 D_eu_0027FDA0[];
extern char D_eu_0024FAF8[];
extern char D_eu_0024FB00[];
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);

void DrawWarpMenu(WarpMenu_eu* self)
{
    if (self->current == 0) {
        return;
    }
    f32 one = 1.0f;
    Camera* cam = g_camera;
    f32 keep1 = cam->zoom;
    f32 keep2 = cam->zoomGoal;
    SnapCameraZoom(cam, one);
    if (g_coloredTriangleSet != 0) {
        Vec02 v;
        f32 out[2];
        WarpColor inner;
        WarpColor outer;
        f32 b2 = self->blend * self->blend;
        Vu0::Q(v) = Vu0::Q(self->current->smoothPoint);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->rotation, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->position), Vu0::Q(v));
        ProjectPointToCamera(g, &v, out);
        out[0] = out[0] * 320.0f + 320.0f;
        out[1] = out[1] * -234.305084f + 234.305084f;
        inner.r = 0;
        inner.g = 0;
        inner.b = 0;
        inner.a = (u8)(s32)(b2 * 145.0f);
        outer.r = 0;
        outer.g = 0;
        outer.b = 0;
        outer.a = 0;
        DrawColoredCircle(out[0], out[1], 40.0f, WrapAngle(g_gameClock.elapsed), 12, (s32*)&inner, (s32*)&outer, 2);
        f32 s = Sine(g_gameClock.elapsed * 10.0f);
        DrawTriangleGroups(g_coloredTriangleSet, out[0], out[1], s * 0.2f + one, b2);
    }
    for (s32 i = 0; i < 11; i++) {
        WarpEntry* e = &self->current->entries[i];
        if (e->reachable == 0) {
            continue;
        }
        WarpColor c0, c1, c2;
        if (e->f20 != 0) {
            c0 = WarpColor(0x9F, 0xFF, 0xE8, 0x4B);
            c1 = WarpColor(0x5C, 0xFF, 0xB6, 0);
            c2 = WarpColor(0x19, 0xFF, 0x64, 0);
        } else {
            c0 = WarpColor(0xE8, 0xE8, 0xE8, 0x4B);
            c1 = WarpColor(0xB6, 0xB6, 0xB6, 0);
            c2 = WarpColor(0x4B, 0x4B, 0x4B, 0);
        }
        f32 pos[2];
        ProjectWarpEntryToScreen(self->current, i, 0, pos);
        f32 size = e->dim * self->blend;
        if (AreFloatsNearlyEqual(size, 1.0f, 0.0001f) && i < 9) {
            s32 slot = self->current->slot;
            if ((GetEntryFlags((slot << 8) | i) & 2)
                && !(*(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10) & 2)) {
                size = Sine(g_gameClock.elapsed * 20.0f) * 0.2f + 0.8f;
            }
        }
        WarpColor a = c0;
        WarpColor b = c1;
        DrawColoredCircle(pos[0], pos[1], size * D_eu_0027FDAC, e->phase, 14, (s32*)&a, (s32*)&b, 3);
        b = c0;
        a = c1;
        DrawColoredCircle(pos[0], pos[1], size * D_eu_0027FDB0, -e->phase, 10, (s32*)&b, (s32*)&a, 3);
        if (i < 9) {
            s32 slot = self->current->slot;
            if (GetEntryFlags((slot << 8) | i) & 2) {
                f32 scale = e->dim;
                s32 flags = *(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10);
                Font* font = GetFontById(3);
                f32 k = D_eu_0027FDA0[0] * scale;
                PushFontScale(font, k, k);
                WarpLabelLayout L;
                f32 x = pos[0];
                f32 y = pos[1];
                b = *(WarpColor*)&self->rgba;
                b.SetAlpha(0xFF);
                s32 held = *(s32*)&b;
                L.Pos(x, y);
                L.Size(0.0f, 0.0f);
                T217D_Word tmp;
                tmp.v = held;
                L.Color(&tmp.v);
                L.FlagA(0);
                L.FlagB(1);
                L.FlagC(1);
                DrawFontString(font, (flags & 2) ? D_eu_0024FAF8 : D_eu_0024FB00, (StringLayout*)&L, 0, &g_gsPacketWriter);
                PopFontScale(font);
            }
        }
    }
    SnapCameraZoom(g_camera, keep1);
    g_camera->zoomGoal = keep2;
}

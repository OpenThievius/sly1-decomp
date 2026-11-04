// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws the striped banner with its waving colour fringes (PAL).
struct Obj_eu_132500 {
    u8 pad0[0x570];
    s32 f570;
    u8 pad1[0x598 - 0x574];
    f32 f598;
    u8 pad2[0x5AC - 0x59C];
    s32 f5AC;
};

void func_00136EC8(Obj_eu_132500* self, f32* x, f32* y);

struct Gfx_eu_132500 {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
    }
};

void func_00132500(Obj_eu_132500* self, Gs_132500* gs)
{
    Rgba_130F48 c0;
    Rgba_130F48 c1;
    f32 k;
    Pad_132500* pad;
    u8 alpha;
    f32 posX;
    f32 posY;
    f32 scale;
    f32 offX;
    f32 offY;

    func_001613C0(gs, 0, 1, 0xE);
    func_00161708(gs, 0x47, 0x31001);
    func_00161708(gs, 0x42, 0x44);
    func_00161708(gs, 0x40, 0xBE0004027F0000);

    pad = (D_00262C68 & 2) ? &D_00262C70 : &D_00262D38;
    k = 3.0f;
    if (0.0f < pad->f78) {
        k = 6.0f;
    } else if (pad->f78 < 0.0f) {
        k = -6.0f;
    }
    self->f598 = func_001EA408(self->f598 + D_00261860 * k);

    alpha = (s32)(D_00261990->f478 * 24.999f) + 0x30;
    switch (self->f5AC) {
    case 0:
        if (self->f570 == 5) {
            Rgba_130F48 t = D_00261110;
            t.a = alpha;
            c0 = t;
            t = D_00261108;
            t.a = alpha;
            c1 = t;
        } else {
            Rgba_130F48 t = (*(Rgba_130F48*)&D_002610E0);
            t.a = alpha;
            c0 = t;
            t = (*(Rgba_130F48*)&D_002610D8);
            t.a = alpha;
            c1 = t;
        }
        break;
    case 1: {
        Rgba_130F48 t = D_00261100;
        t.a = alpha;
        c0 = t;
        t = D_002610F8;
        t.a = alpha;
        c1 = t;
        break;
    }
    case 2: {
        Rgba_130F48 t = D_002610F0;
        t.a = alpha;
        c0 = t;
        t = D_002610E8;
        t.a = alpha;
        c1 = t;
        break;
    }
    }

    func_00136EC8(self, &posX, &posY);
    scale = D_00261990->f478 + 1.0f;

    {
        f32 step = 1.0f / 24.0f;
        f32 period = 256.0f;
        f32 wide = 512.0f;
        f32 s = Gfx_132500::Wave(-8.0f, period, self->f598);
        Rgba_130F48 colA = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
        s = Gfx_132500::Wave(-18.0f, period, self->f598);
        Rgba_130F48 colB = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
        f32 x0 = posX - scale * 35.0f;
        f32 x1 = x0 + scale * 70.0f;
        f32 u;
        s32 i;

        func_001613C0(gs, 0x4C, 2, 0x41);

        func_00161458(gs, *(u32*)&colB);
        func_00161670(gs, Gfx_eu_132500::ScreenX(x0), Gfx_eu_132500::ScreenY(posY + scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_00161670(gs, Gfx_eu_132500::ScreenX(x0), Gfx_eu_132500::ScreenY(posY + scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY + scale * func_00131000(&D_002612E0, i);
            y2 = y + scale * 5.0f;
            func_00161458(gs, *(u32*)&colB);
            func_001615F0(gs, Gfx_eu_132500::ScreenX(x), Gfx_eu_132500::ScreenY(y), 0, 0);
            func_00161458(gs, *(u32*)&colA);
            func_001615F0(gs, Gfx_eu_132500::ScreenX(x), Gfx_eu_132500::ScreenY(y2), 0, 0);
        }
        func_00161458(gs, *(u32*)&colB);
        func_001615F0(gs, Gfx_eu_132500::ScreenX(x1), Gfx_eu_132500::ScreenY(posY + scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_001615F0(gs, Gfx_eu_132500::ScreenX(x1), Gfx_eu_132500::ScreenY(posY + scale * -4.0f), 0, 0);

        func_00161458(gs, *(u32*)&colB);
        func_00161670(gs, Gfx_eu_132500::ScreenX(x0), Gfx_eu_132500::ScreenY(posY - scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_00161670(gs, Gfx_eu_132500::ScreenX(x0), Gfx_eu_132500::ScreenY(posY - scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY - scale * func_00131000(&D_002612E0, i);
            y2 = y - scale * 5.0f;
            func_00161458(gs, *(u32*)&colB);
            func_001615F0(gs, Gfx_eu_132500::ScreenX(x), Gfx_eu_132500::ScreenY(y), 0, 0);
            func_00161458(gs, *(u32*)&colA);
            func_001615F0(gs, Gfx_eu_132500::ScreenX(x), Gfx_eu_132500::ScreenY(y2), 0, 0);
        }
        func_00161458(gs, *(u32*)&colB);
        func_001615F0(gs, Gfx_eu_132500::ScreenX(x1), Gfx_eu_132500::ScreenY(posY - scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_001615F0(gs, Gfx_eu_132500::ScreenX(x1), Gfx_eu_132500::ScreenY(posY - scale * -4.0f), 0, 0);

        if (self->f570 != 5) {
            s32 n;

            offX = 41.0f;
            offY = -5.0f;
            func_001613C0(gs, 0xC6, 5, 0x44441);
            for (n = 0; n < 64; n++) {
                f32 px, py;
                f32 s = Gfx_132500::Wave(offX, wide, self->f598);
                px = posX + scale * offX;
                py = posY + scale * offY;
                Rgba_130F48 col = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
                func_00161458(gs, *(u32*)&col);
                func_00161670(gs, Gfx_eu_132500::ScreenX(px), Gfx_eu_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_eu_132500::ScreenX(px + scale * 2.0f), Gfx_eu_132500::ScreenY(py + scale * 10.0f), 0, 0);
                py = posY + scale * offY;
                px = posX - scale * offX;
                func_00161670(gs, Gfx_eu_132500::ScreenX(px), Gfx_eu_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_eu_132500::ScreenX(px - scale * 2.0f), Gfx_eu_132500::ScreenY(py + scale * 10.0f), 0, 0);
                offX += 8.0f;
            }

            offX = -5.0f;
            offY = 24.0f;
            for (n = 0; n < 32; n++) {
                f32 px, py;
                f32 s = Gfx_132500::Wave(offY, period, self->f598);
                px = posX + scale * offX;
                py = posY + scale * offY;
                Rgba_130F48 col = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
                func_00161458(gs, *(u32*)&col);
                func_00161670(gs, Gfx_eu_132500::ScreenX(px), Gfx_eu_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_eu_132500::ScreenX(px + scale * 10.0f), Gfx_eu_132500::ScreenY(py + scale * 2.0f), 0, 0);
                py = posY - scale * offY;
                px = posX + scale * offX;
                func_00161670(gs, Gfx_eu_132500::ScreenX(px), Gfx_eu_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_eu_132500::ScreenX(px + scale * 10.0f), Gfx_eu_132500::ScreenY(py - scale * 2.0f), 0, 0);
                offY += 8.0f;
            }
        }
    }

    func_001613C0(gs, 0, 1, 0xE);
    func_00161708(gs, 0x40, 0xFF0000027F0000);
}

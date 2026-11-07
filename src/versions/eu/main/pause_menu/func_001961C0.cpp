// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the state is at +0x570, a case 33 (same as case 0) is added, and the two floats are PAL's own D_eu_0026BB38/3C.
struct Self_1961C0_eu {
    u8 pad0[0x570];
    s32 state;
};
void SetPauseMenuLayerPage(Self_1961C0_eu* self, s32 a, s32 b);
extern f32 D_eu_0026BB38;
extern f32 D_eu_0026BB3C;

void CancelPauseMenuPage(Self_1961C0_eu* self)
{
    switch (self->state) {
    case 0:
        SetPauseMenuLayerPage(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            SetPauseMenuLayerPage(self, 0, -1);
            break;
        }
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 24: {
        DisplayRegs* g = &D_00262490;
        s32 v = ConvertFloatToU32(D_eu_0026BB38);
        DisplayReg64 a = g->f40;
        DisplayReg32 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = ConvertFloatToU32(D_eu_0026BB3C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    }
    case 2:
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 33:
        SetPauseMenuLayerPage(self, 0, -1);
        break;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    case 14:
    case 18:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    }
}

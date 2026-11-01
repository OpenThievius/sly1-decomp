// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the state is at +0x570, a case 33 (same as case 0) is added, and the two floats are PAL's own D_eu_0026BB38/3C.
struct Self_1961C0_eu {
    u8 pad0[0x570];
    s32 state;
};
void func_00194D30(Self_1961C0_eu* self, s32 a, s32 b);
extern f32 D_eu_0026BB38;
extern f32 D_eu_0026BB3C;

void func_001961C0(Self_1961C0_eu* self)
{
    switch (self->state) {
    case 0:
        func_00194D30(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            func_00194D30(self, 0, -1);
            break;
        }
        func_00194D30(self, 0, 0);
        break;
    case 24: {
        Gs_1961C0* g = &D_00262490;
        s32 v = func_001FD7A0(D_eu_0026BB38);
        Reg_1961C0 a = g->f40;
        RegA_1961C0 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = func_001FD7A0(D_eu_0026BB3C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        func_00194D30(self, 0, 0x17);
        break;
    }
    case 2:
        func_00194D30(self, 0, 0);
        break;
    case 33:
        func_00194D30(self, 0, -1);
        break;
    case 13:
        func_00194D30(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        func_00194D30(self, 0, 0x17);
        break;
    case 14:
    case 18:
        func_00194D30(self, 1, -1);
        break;
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the packed word of D_002701F8 is at 0x5B0 (not 0x324) and the two slots of D_0026D0C8 are at 0x574 and 0x578 (not 0x264 and 0x268).
struct __attribute__((packed)) Packed_1A4EF0_eu { u8 pad[0x5B0]; s32 v __attribute__((packed)); };
struct Glob_1A4EF0_eu { u8 pad[0x5B0]; s32 v; };
struct Tab_1A4EF0_eu { u8 pad[0x574]; void* f574; void* f578; };

void func_001A4EF0(Obj_1A4EF0* self, s32 state)
{
    Obj_1A4EF0* o;
    s32 v;
    s32 scratch[4]; (void)scratch;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = D_0026185C[0];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (((Step_1A4EF0*)D_002623C8)->f14) {
                    W(self, 0x658) = 0;
                } else {
                    W(self, 0x658) = func_0015A418(self->f14, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            ((Packed_1A4EF0_eu*)&D_002701F8)->v = w;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        break;
    }
    case 2: {
        ((Tab_1A4EF0_eu*)&D_0026D0C8)->f574 = self->f3C4;
        ((Tab_1A4EF0_eu*)&D_0026D0C8)->f578 = self->f3B8;
        func_001DDC38(self->f14, self);
        break;
    }
    case 5:
        v = func_0015A418(self->f14, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&D_002701F8)->v = v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) func_001A6BE0(o, 8);
        func_00151FC8(D_00261EF0);
        break;
    case 3:
        v = func_0015A418(self->f14, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&D_002701F8)->v = v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            Link_1A4EF0* l = (Link_1A4EF0*)P(o, 0x55C);
            if (l == 0 || l->f18 != o) func_001A6BE0(o, 7);
        }
        func_00151E20(D_00261EF0, 1.0f);
        break;
    case 4:
        func_00194D30(D_0026FF68, 0, 0x1A);
        break;
    case 6:
        func_001A4070(P(self, 0x354), 3);
        D_0026EC70.vt->f3C(&D_0026EC70);
        break;
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL uses its own floats at 0x26BB30..3C, keeps f288 at 0x598 and has a case 20 that calls func_eu_001DE018(6) and stores func_001BE980().
struct Self_193EE8_eu {
    u8 pad[0x598];
    s32 f288;
};
extern f32 D_eu_0026BB30;
extern f32 D_eu_0026BB34;
extern f32 D_eu_0026BB38;
extern f32 D_eu_0026BB3C;
s32 func_001BE980(void);
void func_001BE728(void* slot);
void* func_eu_001DE018(s32 n);

void func_00193EE8(Self_193EE8_eu* self, s32 a, s32 b)
{
    if (a == b) {
        return;
    }
    if (self->f288 != 0) {
        func_001BE998();
        self->f288 = 0;
    }
    if (a == 11) {
        goto call;
    }
    if (a > 10) {
        if (a < 18) {
            if (a > 15) {
            call:
                ((VFn_193EE8)D_0026EC70.vt[15])(&D_0026EC70);
            }
        }
    }
    switch (b) {
    case 11:
    case 16:
    case 17: {
        Obj_193EE8* o = &D_0026EC70;
        func_001AA8B8(o, 0.0f);
        func_001AA788(o, 0.6f);
        break;
    }
    case 20:
        if (func_001BE980() != 0) {
            return;
        }
        func_001BE728(func_eu_001DE018(6));
        self->f288 = func_001BE980();
        break;
    case 24: {
        D_eu_0026BB30 = D_eu_0026BB38 = (f32)(u32)D_00262490.a.x;
        D_eu_0026BB34 = D_eu_0026BB3C = (f32)((u32)(D_00262490.q18 >> 12) & 0x7FF);
        break;
    }
    case -1:
        ((VFn_193EE8)D_0026C6C8.vt[15])(&D_0026C6C8);
        ((VFn_193EE8)D_0026C948.vt[15])(&D_0026C948);
        ((VFn_193EE8)D_0026CBC8.vt[15])(&D_0026CBC8);
        ((VFn_193EE8)D_0026CE48.vt[15])(&D_0026CE48);
        ((VFn_193EE8)D_00274118.vt[15])(&D_00274118);
        break;
    }
}

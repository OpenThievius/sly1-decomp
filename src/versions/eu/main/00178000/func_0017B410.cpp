// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Sys_17B410 fields f260 to f278 are at 0x570 to 0x588 (US 0x260 to 0x278).
struct Sys_17B410_eu { Fn_17B410* vtbl; u8 pad0[0x570 - 4]; s32 f570; s32 f574; u8 pad1[0x57C - 0x578]; s32 f57C; s32 f580; s32 f584; f32 f588; };

void func_0017B410(Obj_17B410* self, s32 mode)
{
    void* x;
    if (mode == self->f550) {
        goto done;
    }
    x = 0;
    if (mode != 0) {
        if (mode == 1) {
            x = self->f5C0;
        }
    } else {
        x = self->f58C;
    }
    if (mode >= 0) {
        if (mode < 2) {
            Sys_17B410_eu* sys = (Sys_17B410_eu*)D_0026E248;
            sys->f588 = 1.0f;
            sys->f57C = sys->f570;
            sys->f580 = sys->f574;
            sys->f584 = 0;
            func_001DDC38(self->f14, self);
        } else if (mode < 4) {
            Sys_17B410_eu* sys = (Sys_17B410_eu*)D_0026E248;
            sys->vtbl[15](sys);
            func_001DDC38(self->f14, 0);
        }
    }
    (void)func_0012C918(x, self, 1, self->f558, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->f554 = D_0026185C;
done:
    return;
}


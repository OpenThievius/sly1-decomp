// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Sys_17B410 fields f260 to f278 are at 0x570 to 0x588 (US 0x260 to 0x278).
struct Sys_17B410_eu { Fn_17B410* vtbl; u8 pad0[0x570 - 4]; s32 f570; s32 f574; u8 pad1[0x57C - 0x578]; s32 f57C; s32 f580; s32 f584; f32 f588; };

void func_0017B410(GaugeModeObject* self, s32 mode)
{
    void* x;
    if (mode == self->mode) {
        goto done;
    }
    x = 0;
    if (mode != 0) {
        if (mode == 1) {
            x = self->mode1Handle;
        }
    } else {
        x = self->mode0Handle;
    }
    if (mode >= 0) {
        if (mode < 2) {
            Sys_17B410_eu* sys = (Sys_17B410_eu*)&g_gaugeBarElement;
            sys->f588 = 1.0f;
            sys->f57C = sys->f570;
            sys->f580 = sys->f574;
            sys->f584 = 0;
            SetWorldActiveFollower(self->world, self);
        } else if (mode < 4) {
            Sys_17B410_eu* sys = (Sys_17B410_eu*)&g_gaugeBarElement;
            sys->vtbl[15](sys);
            SetWorldActiveFollower(self->world, 0);
        }
    }
    (void)ReplaceAnimationPlayer(x, self, 1, self->modePlayer, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->modeTime = g_gameTime;
done:
    return;
}


// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: mode, flag, timer and extra sit 784 (0x310) bytes further on than in US.
extern f32 D_0026185C;
extern f32 D_00261860;

typedef void (*VFn_1AB660)(void* self);

void func_001AA298(void* self);
void func_001AB980(void* self, f32 value);

struct Obj_1AB660_eu {
    VFn_1AB660* vtbl;
    u8 pad[0x250 - 4 + 0x310];
    s32 mode;
    u8 pad2[0x260 - 0x254];
    s32 flag;
    f32 timer;
    u8 pad3[0x290 - 0x268];
    s32 extra;
};

void func_001AB660(Obj_1AB660_eu* self)
{
    func_001AA298(self);
    if (self->mode == 0) {
        return;
    }
    if (self->flag == 0) {
        s32 close = (1.0f <= D_0026185C - self->timer);
        if ((u32)(self->mode - 1) < 2) {
            if (self->extra != 0 || close) {
                self->vtbl[15](self);
            }
        }
    } else {
        func_001AB980(self, D_00261860);
    }
}

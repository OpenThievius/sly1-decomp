// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: mode sits 784 (0x310) bytes further on than in US.
struct Obj_1AA958_eu {
    void** vtbl;
    u8 pad0[0x250 - 4 + 0x310];
    s32 mode;
};

void func_001AA958(Obj_1AA958_eu* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            ((void (*)(Obj_1AA958_eu*, s32))self->vtbl[16])(self, 3);
        }
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: shifts a block of values in its object (mode-dependent copy, then the tail words move down by one word).
struct __attribute__((packed)) W_eu_15DDA0 { s32 v; };
struct Obj_eu_15DDA0 {
    s32 mode;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    u8 pad14[0x8C];
    s32 fA0;
    W_eu_15DDA0 a4;
    W_eu_15DDA0 a8;
    W_eu_15DDA0 aC;
};

void RewindTextReader(Obj_eu_15DDA0* self)
{
    if (self->mode == 0) {
        self->f8 = self->f4;
    } else if (self->mode == 1) {
        self->f8 = self->f4;
    }
    self->fC = self->f10;
    self->a8 = self->aC;
    self->a4 = self->a8;
    self->fA0 = 0;
}

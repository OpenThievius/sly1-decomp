// SPDX-License-Identifier: AGPL-3.0-or-later
// Recomputes the ring position fields from the current time, per kind.
struct Obj_eu_18F210 {
    u8 pad0[4];
    s32 kind;
    u8 pad8[4];
    s32 cols;
    u8 pad10[4];
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
};
s32 func_eu_0011E628(void);
s32 func_0011E4F8(void);

void func_eu_0018F210(Obj_eu_18F210* self)
{
    if (self->kind == 0x10) {
        s32 t = func_eu_0011E628() * self->cols;
        if (t >= 0 && self->f18 >= t) {
            s32 r = t % self->f18;
            self->f20 = r;
            if (r == self->f1C) {
                self->f24 = self->f18;
            } else {
                self->f24 = r - self->f1C + self->f18;
                self->f24 = self->f24 % self->f18;
            }
        }
        self->f28 = self->f18 - self->f24;
    } else {
        s32 t = GetIopRingPosition() & 0xFFFFFF;
        s32 base = self->f14;
        s32 pos = self->f1C;
        s32 size = self->f18;
        s32 v = t - base - pos - 0x400;
        self->f24 = v + size;
        self->f24 = self->f24 % size;
        self->f28 = size - self->f24;
        self->f20 = pos - self->f28 + size;
        self->f20 = self->f20 % size;
    }
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 72/76 (94.7%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015DDA0.cpp func_eu_0015DDA0 --unit src/main/0015C000.cpp
// Still differs: Mode-dependent copy then packed lwl/lwr shift of tail words; first lwl/lwr copy still uses v1 where retail uses v0 (6 variants tried).
// Only in PAL: shifts a block of values in its object (mode-dependent copy, then the tail words move down by one word).
struct Obj_eu_15DDA0 {
    s32 mode;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    u8 pad14[0x8C];
    s32 fA0;
};

struct __attribute__((packed)) Packed_eu_15DDA0 {
    u8 pad0[0xA4];
    s32 a4;
    s32 a8;
    s32 aC;
};

void func_eu_0015DDA0(Obj_eu_15DDA0* self)
{
    Packed_eu_15DDA0* p = (Packed_eu_15DDA0*)self;
    s32 m = self->mode;
    if (m == 0) {
        self->f8 = self->f4;
    } else if (m == 1) {
        self->f8 = self->f4;
    }
    self->fC = self->f10;
    s32 t = p->aC;
    p->a8 = t;
    s32 u = p->a8;
    p->a4 = u;
    self->fA0 = 0;
}

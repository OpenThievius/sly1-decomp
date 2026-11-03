// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 742/792 (93.7%), checked 2026-11-02
// NEAR (normal flags, Fpu::Sqrt): 14 lines differ. Loop body, hoisting and registers match.
// Left: 160.0f/125.4f land in f1/f0 (retail f0/f1), and the p init (addiu s0) is scheduled
// before the hoisted 0x30000000/0x1A instead of after them. 'step' as a pre-loop local is
// what makes loop.c hoist 0x30000000 and 0x1A as retail does.
#include "fpu.h"

struct Elem_1E5E70 {
    u8 pad0[4];
    f32 f4;
    u8 pad1[4];
    f32 fC;
    u8 pad2[0x2C - 0x10];
    f32 f2C;
    u8 pad3[4];
    f32 f34;
    u8 pad4[4];
    u32 f3C;
    u32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
};

struct Obj_1E5E70 {
    u8 pad0[0x214];
    s32 mode;
    u8 pad1[0x234 - 0x218];
    f32 f234;
    f32 f238;
    u8 pad2[0x254 - 0x23C];
    u8 elems[0xC24 - 0x254];
    s32 fC24;
    u8 padC28[4];
    f32 fC2C;
    u8 padC30[0xC4C - 0xC30];
    f32 fC4C;
    f32 fC50;
    f32 fC54;
    f32 fC58;
    u8 padC5C[0xC64 - 0xC5C];
    f32 fC64;
    f32 fC68;
    f32 fC6C;
};

void func_001AA1F0(Obj_1E5E70* self);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E5E70(Obj_1E5E70* self, s32 kind)
{
    self->f234 = 160.0f;
    self->f238 = 125.4f;
    self->fC54 = self->fC58 = 3.3000002f;
    func_001AA1F0(self);
    f32 sign;
    if (kind == 0x1A) {
        self->fC50 = 0.0f;
        self->fC4C = self->f234 - 62.7f;
        sign = 1.0f;
    } else {
        self->fC50 = self->f234;
        self->fC4C = 62.7f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 57.0f;
    Elem_1E5E70* p;
    s32 i;
    for (i = 0, p = (Elem_1E5E70*)self->elems; i < 0x39; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->f34 = y;
        p->f2C = sign * Fpu::Sqrt(1.0f - y * y);
        p->f3C = p->f40 = (i & 1) ? 0x30000000 : 0x30808080;
        p->f44 = p->f48 = 0.0f;
        if (self->mode == 0x1A) {
            p->f4C = func_001EAAE0(0.6f, 0.8f);
            p->f50 = func_001EAAE0(0.4f, 0.6f);
            p->f54 = func_001EAAE0(0.05f, 0.2f);
        } else {
            p->f4C = func_001EAAE0(0.3f, 0.4f);
            p->f50 = func_001EAAE0(0.2f, 0.3f);
            p->f54 = func_001EAAE0(0.1f, 0.4f);
        }
        if (i != 0) {
            p->fC = p->f34;
            p->f4 = p->f2C;
        }
        p = (Elem_1E5E70*)((u8*)p + 0x2C);
    }
    self->fC2C = 1.0f;
    self->fC24 = 0;
    if (self->mode == 0x1A) {
        self->fC64 = func_001EAAE0(1.0f, 1.4f);
        self->fC68 = func_001EAAE0(0.6f, 0.8f);
        self->fC6C = func_001EAAE0(0.1f, 0.2f);
    } else {
        self->fC64 = func_001EAAE0(0.5f, 0.7f);
        self->fC68 = func_001EAAE0(0.2f, 0.3f);
        self->fC6C = func_001EAAE0(0.3f, 0.5f);
    }
}

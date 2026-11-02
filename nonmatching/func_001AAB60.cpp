// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 849/864 (98.3%), checked 2026-11-02
#include "common.h"
// NEAR: 8 lines: loop preheader order/registers. Retail hoists 0.0 after the constants 1,2 (second loop pass) and gives D_002486B0->s6, D_0026C3E0->s5, 1->s7; ours combines the four 0.0 loads and hoists them in the first loop pass, so 1->s5, D_002486B0->s7, D_0026C3E0->s6.
// j40o04 (loop dump): pass 1 sees 60 insns; the four 0.0 loads match (savings 4, life 4) and move
// in pass 1 ahead of 1/2, which only move in pass 2. Retail needs 1 and 2 moved before 0.0: either
// pass 1 with <= ~54 insns, or 0.0 left to pass 2. A 'f32 z = 0.0f;' inside the if(m48) block
// (57 insns) gives retail's s5/s6/s7/s8 exactly but z is then never hoisted (set in another block
// after the call branch: unsafe for loop.c), so mtc1 zero stays in the loop and float regs shift.
// Also tried: if (o->f234), 0.0f on the left, 0.0 double (soft-float), while/goto/continue shapes,
// z per case block, z at the top of the body (moved in pass 1 before 1).

struct Self_1AAB60;
struct Vt_1AAB60 { u8 p[0x48]; s32 (*m48)(Self_1AAB60*, Self_1AAB60*); };
struct Rec_1AAB60 { f32 f0; f32 f4; s32 f8; s32 fC; s32 f10; };
struct Self_1AAB60 {
    Vt_1AAB60* vt;
    u8 p0[0x218 - 4];
    Rec_1AAB60* f218;
    f32 f21C; f32 f220; f32 f224; f32 f228; f32 f22C; f32 f230; f32 f234; f32 f238;
    u8 p1[0x250 - 0x23C];
    s32 f250;
};

extern Self_1AAB60* D_002486B0[];
extern Rec_1AAB60 D_0026C3E0[];
f32 func_001EAF28(f32 x);
void func_001AAEC0(Self_1AAB60* self);

void func_001AAB60(Self_1AAB60* self) {
    Rec_1AAB60* r = self->f218;
    f32 x0 = 0.0f;
    f32 x1 = 640.0f;
    f32 y1 = 492.80002f;
    f32 y0 = x0;

    if (r->fC != -1) {
        do {
            Self_1AAB60* o = D_002486B0[r->fC];
            if (o->vt->m48(o, self)) {
                switch (r->f10) {
                case 0:
                    if (o->f234 != 0.0f) x0 = o->f21C + o->f234;
                    break;
                case 1:
                    if (o->f234 != 0.0f) x1 = o->f21C;
                    break;
                case 2:
                    if (o->f238 != 0.0f) y0 = o->f220 + o->f238;
                    break;
                case 3:
                    if (o->f238 != 0.0f) y1 = o->f220;
                    break;
                }
                break;
            }
            r = &D_0026C3E0[r->fC];
        } while (r->fC != -1);
    }
    f32 a = self->f218->f0;
    if (a == 0.0f) {
        self->f224 = (x1 - x0 - self->f234) * 0.5f;
    } else if (0.0f < a) {
        self->f224 = x0 + a;
    } else {
        self->f224 = x1 + a - self->f234;
    }
    f32 b = self->f218->f4;
    if (b == 0.0f) {
        self->f228 = (y1 - y0 - self->f238) * 0.5f;
    } else if (0.0f < b) {
        self->f228 = y0 + b;
    } else {
        self->f228 = y1 + b - self->f238;
    }
    f32 t = func_001EAF28(self->f228 * 0.9090909f) * 1.1f;
    self->f22C = self->f224;
    self->f228 = t;
    self->f230 = t;
    switch (self->f218->f8) {
    case 0: self->f22C = -self->f234; break;
    case 1: self->f22C = 640.0f; break;
    case 2: self->f230 = -self->f238; break;
    case 3: self->f230 = 492.80002f; break;
    }
    s32 m = self->f250;
    if (m != 0) {
        if (m == 2) {
            self->f21C = self->f224;
            self->f220 = self->f228;
        }
    } else {
        self->f21C = self->f22C;
        self->f220 = self->f230;
    }
    func_001AAEC0(self);
}

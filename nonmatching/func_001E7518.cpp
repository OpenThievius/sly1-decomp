// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 446/452 (98.7%), checked 2026-11-02
// NEAR (normal flags): 2 lines differ. Cases are laid out 0, 2, 1, 3 as retail's; func_001BFCD8
// takes its five floats before its last two ints (that orders the argument moves as retail's).
// Left: before the loop, retail loads %hi(D_00261858) into s4 before `li s1, 56`; here after.
// Tried: the counter and pointer declared in every order, a do-while, the index form (worse),
// and tools/permute.py over the call, the loop set-up and the body (no closer).
#include "common.h"

struct Elem_1E77C0 {
    u8 pad00[0x18];
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
};

struct Obj_1E77C0 {
    void* vtbl;
    u8 pad004[0x264];
    s32 f268;
    f32 f26C;
    u8 pad270[0x10];
    Elem_1E77C0 elems[57];
    u8 padC4C[0x24];
    f32 fC70;
};

struct Obj_1E7460;
void func_001E7460(Obj_1E7460* self);
extern f32 D_00261858[];
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);

void func_001E7518(Obj_1E77C0* self, s32 mode)
{
    if (mode == self->f268) {
        return;
    }
    switch (mode) {
    case 0: {
        func_001BFCD8(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        s32 i = 56;
        Elem_1E77C0* e = self->elems;
        for (; i >= 0; i--) {
            e->f18 = 1.0f;
            e->f1C = func_001EAAE0(0.0f, 0.05f);
            e->f20 = 1.0f;
            e->f24 = 0.6f;
            e->f28 = 0.2f;
            e++;
        }
        break;
    }
    case 2:
        func_001BFCD8(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->fC70 = 1.0f;
        break;
    case 3:
        self->fC70 = 0.0f;
        func_001E7460((Obj_1E7460*)self);
        break;
    }
    self->f268 = mode;
    self->f26C = D_00261858[4];
}

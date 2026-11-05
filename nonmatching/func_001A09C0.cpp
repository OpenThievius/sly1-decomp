// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 176/180 (97.8%), checked 2026-11-04
#include "common.h"
// NEAR: the US build differs only in two register choices of the last 128-bit copy (retail loads D_0026B5A0 through v1 and stores through v0, ours the reverse); the frame and every call match
#include "t219c.h"
#include "c6c.h"
#include "globals.h"

typedef int V128_1A09C0 __attribute__((mode(TI)));
void func_0019EB28(T219C* self, f32 f);
void func_00118CF0(void* out, f32 f);
void func_00118D10(void* out, void* in);
V128_1A09C0 func_00118D30(V128_1A09C0 a, V128_1A09C0 b);
void func_00118D20(void* dst, V128_1A09C0 v);
extern f32 D_0026B590[4];
extern f32 D_0026B5A0[4];

void func_001A09C0(T219C* self, f32 f)
{
    func_0019EB28(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B590;
    s32 v = (s32)D_00275710->slot1CE8[8];
    self->life = 0.25f;
    self->i20 = v;
    V128_1A09C0 t;
    func_00118CF0(&t, f);
    V128_1A09C0 tv = t;
    V128_1A09C0 u;
    func_00118D10(&u, p);
    func_00118D20(sub, func_00118D30(tv, u));
    u8* q = (u8*)D_0026B5A0;
    self->q40 = *(Quad219C*)q;
}

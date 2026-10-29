// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the local stores and stack address calculations are scheduled differently.
#include "common.h"
struct Quad_00107CB0 { s32 a, b, c, d; };
struct Frame_00107CB0 { Quad_00107CB0 q; Quad_00107CB0 t; s32 n; s32 out; };
void func_0011B008(Quad_00107CB0*);
void func_0011B018(void*, Quad_00107CB0*);
void func_0011B060(Quad_00107CB0*, s32);
void func_0011B0A8(Quad_00107CB0*, Quad_00107CB0*);
void func_0011B538(Quad_00107CB0*, s32);
void func_001C23B0(Quad_00107CB0*, s32, s32, void*, void*);
void func_0017CFF0(void*, s32);
void* func_00107CB0(void* self, void* x, s32 unused, s32 c)
{
    Frame_00107CB0 f;
    func_0011B008(&f.q);
    s32* n = &f.n;
    s32* out = &f.out;
    f.n = 6;
    func_001C23B0(&f.t, 1, c, n, out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017CFF0(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

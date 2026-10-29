// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the size store is emitted before retail's two stack address calculations.
#include "common.h"

struct Quad_101208 { s32 a, b, c, d; };
void func_0011B008(Quad_101208* q);
void func_0011B018(void* out, Quad_101208* q);
void func_0011B060(Quad_101208* q, int mode);
void func_0011B0A8(Quad_101208* a, Quad_101208* b);
void func_0011B538(Quad_101208* q, int n);
void func_001C23B0(Quad_101208* t, int mode, int c, s32* size, f32* out);
void func_00126CB8(void* self, f32 value);

void* func_00101208(void* self, void* x, int unused, int c)
{
    Quad_101208 q, t;
    s32 size;
    f32 out;
    func_0011B008(&q);
    size = 1;
    func_001C23B0(&t, 1, c, &size, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00126CB8(x, out);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the constant store precedes retail's two stack address calculations.
#include "common.h"

struct Quad_108498 { s32 a, b, c, d; };
void func_0011B008(Quad_108498* q);
void func_0011B018(void* out, Quad_108498* q);
void func_0011B060(Quad_108498* q, int mode);
void func_0011B0A8(Quad_108498* a, Quad_108498* b);
void func_0011B538(Quad_108498* q, int n);
void func_001C23B0(Quad_108498* t, int mode, int c, s32* size, f32* out);
void func_0017D1E8(void* self, f32 value);

void* func_00108498(void* self, void* x, int unused, int c)
{
    Quad_108498 q, t;
    s32 size;
    f32 out;
    func_0011B008(&q);
    size = 1;
    func_001C23B0(&t, 1, c, &size, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017D1E8(x, out);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

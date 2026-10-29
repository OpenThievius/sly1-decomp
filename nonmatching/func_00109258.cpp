// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the size store precedes retail's two stack address calculations.
#include "common.h"

struct Quad_109258 { s32 a, b, c, d; };
void func_0011B008(Quad_109258* q);
void func_0011B018(void* out, Quad_109258* q);
void func_0011B060(Quad_109258* q, int mode);
void func_0011B0A8(Quad_109258* a, Quad_109258* b);
void func_0011B538(Quad_109258* q, int n);
void func_001C23B0(Quad_109258* t, int mode, int c, s32* size, s32* out);
void func_001C4180(void* self, s32 value);

void* func_00109258(void* self, void* x, int unused, int c)
{
    Quad_109258 q, t;
    s32 size;
    s32 out;
    func_0011B008(&q);
    size = 0x2000;
    func_001C23B0(&t, 1, c, &size, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001C4180(x, out);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

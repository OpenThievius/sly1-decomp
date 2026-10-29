// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the size store is emitted before the two stack address calculations.
#include "common.h"

struct Quad_100FA8 { s32 a, b, c, d; };
struct Init_100FA8 { Quad_100FA8 q; s32 size; f32 value; };

void func_0011B008(Quad_100FA8* q);
void func_0011B018(void* out, Quad_100FA8* q);
void func_0011B060(Quad_100FA8* q, int mode);
void func_0011B0A8(Quad_100FA8* a, Quad_100FA8* b);
void func_0011B538(Quad_100FA8* q, int n);
void func_001C23B0(Quad_100FA8* t, int mode, int c, s32* size, f32* value);
void func_0012AAE8(void* self, f32 value);

void* func_00100FA8(void* out, void* self, int unused, int c)
{
    Quad_100FA8 q;
    Init_100FA8 t;
    func_0011B008(&q);
    t.size = 1;
    func_001C23B0(&t.q, 1, c, &t.size, &t.value);
    func_0011B0A8(&q, &t.q);
    func_0011B060(&t.q, 2);
    func_0012AAE8(self, t.value);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

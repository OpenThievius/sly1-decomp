// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_1085E8 { s32 a, b, c, d; };

void func_0011B008(Quad_1085E8* q);
void func_0011B018(void* out, Quad_1085E8* q);
void func_0011B060(Quad_1085E8* q, int mode);
void func_0011B0A8(Quad_1085E8* a, Quad_1085E8* b);
void func_0011B538(Quad_1085E8* q, int n);
void func_001C23B0(Quad_1085E8* t, int mode, int c, void* z);
void func_00159ED0(void* x);

void* func_001085E8(void* self, void* x, int unused, int c)
{
    Quad_1085E8 q;
    Quad_1085E8 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00159ED0(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

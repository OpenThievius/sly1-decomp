// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the size store is emitted before retail's two stack address calculations.
#include "common.h"

struct Quad_1091A8 { s32 a, b, c, d; };
void func_0011B008(Quad_1091A8* q);
void func_0011B018(void* out, Quad_1091A8* q);
void func_0011B060(Quad_1091A8* q, int mode);
void func_0011B0A8(Quad_1091A8* a, Quad_1091A8* b);
void func_0011B538(Quad_1091A8* q, int n);
void func_001C23B0(Quad_1091A8* t, int mode, int c, s32* size, s32* out);
void func_001C3F68(void* self, s32 value);

void* func_001091A8(void* self, void* x, int unused, int c)
{
    Quad_1091A8 q, t;
    s32 size, out;
    func_0011B008(&q);
    size = 0x2000;
    func_001C23B0(&t, 1, c, &size, &out);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001C3F68(x, out);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

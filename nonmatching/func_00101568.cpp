// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the initialized size local is stored before retail calculates
// the two stack addresses passed to func_001C23B0; attempts to alter local
// initialization order did not move those instructions into retail order.
#include "common.h"

struct Quad_101568 { s32 a, b, c, d; };
void func_0011B008(Quad_101568* q);
void func_0011B018(void* out, Quad_101568* q);
void func_0011B060(Quad_101568* q, int mode);
void func_0011B0A8(Quad_101568* a, Quad_101568* b);
void func_0011B538(Quad_101568* q, int n);
void func_001C23B0(Quad_101568* t, int mode, int c, s32* size, s32* value);

void* func_00101568(void* out, void* object, int unused, int c)
{
    Quad_101568 q, t;
    s32 size = 0x2000, value;
    func_0011B008(&q);
    func_001C23B0(&t, 1, c, &size, &value);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    ((void (*)(void*, int))*((void (**)(void*, int))(*(void**)object) + 0x23))(object, value);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

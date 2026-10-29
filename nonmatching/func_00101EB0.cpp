// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: calls, frame size, and data flow match, but the constant store
// is scheduled before retail's stack address setup for func_001C23B0.
#include "common.h"

struct Quad_101EB0 { s32 a, b, c, d; };
void func_0011B008(Quad_101EB0* q);
void func_0011B018(void* out, Quad_101EB0* q);
void func_0011B060(Quad_101EB0* q, int mode);
void func_0011B0A8(Quad_101EB0* a, Quad_101EB0* b);
void func_0011B538(Quad_101EB0* q, int n);
void func_001C23B0(Quad_101EB0* t, int mode, int c, s32* size, s32* value);
void func_0012F190(void* self, s32 value);

void* func_00101EB0(void* out, void* object, int unused, int c)
{
    Quad_101EB0 q, t;
    s32 size = 5, value;
    func_0011B008(&q);
    func_001C23B0(&t, 1, c, &size, &value);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012F190(object, value);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the pointer loads use different temporary registers.
#include "common.h"

struct Quad_114740 { s32 a, b, c, d; };
struct Child_114740 { u8 pad[8]; void* ptr; };
struct Parent_114740 { u8 pad[4]; Child_114740* child; };

void func_0011B008(Quad_114740* q);
void func_0011B018(void* out, Quad_114740* q);
void func_0011B060(Quad_114740* q, int mode);
void func_0011B538(Quad_114740* q, int n);
void func_0011B6C0(Quad_114740* q);

void* func_00114740(void* out, void* unused, Parent_114740* self)
{
    Quad_114740 q;
    func_0011B008(&q);
    Child_114740* child = self->child;
    if (child->ptr)
        func_0011B6C0(&q);
    else
        func_0011B538(&q, 0);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

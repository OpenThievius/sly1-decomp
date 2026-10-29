// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: this constructor-style wrapper still differs in argument/register
// mapping for the indirect call and in local allocation; stop after useful
// structural changes no longer moved the remaining instructions.
#include "common.h"

struct Quad_100438 { s32 a, b, c, d; };
struct Frame_100438 { Quad_100438 q; Quad_100438 t; };
void func_0011B008(Quad_100438* q);
void func_0011B018(void* out, Quad_100438* q);
void func_0011B060(Quad_100438* q, int mode);
void func_0011B0A8(Quad_100438* a, Quad_100438* b);
void func_0011B538(Quad_100438* q, int n);
void func_001C23B0(Quad_100438* t, int mode, int c);
void* func_00100438(void* self, void* object, int unused, int c)
{
    Frame_100438 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 1, c);
    *(s32*)((u8*)&f + 0x20) = 0x2000;
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    ((void (*)(void*, int))*((void (**)(void*, int))(*(void**)object) + 0x19))(object, *(s32*)((u8*)&f + 0x24));
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

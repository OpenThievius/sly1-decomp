// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1ED198 { u8 pad0[0x14]; void* f14; u8 pad1[0x28]; s32 f40; };

void func_00182C58(void);
s32 func_0015A838(void* a, s32 b, s32 c, s32 d);

void func_001ED198(Obj_1ED198* self)
{
    func_00182C58();
    self->f40 = func_0015A838(self->f14, 5, 0x13, 0);
}

struct Inner_1ED1D8 { u8 pad[0xC70]; s32 c70; };
struct Obj_1ED1D8 { u8 pad0[0x3C]; s32 f3C; Inner_1ED1D8* f40; s32 f44; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_001ED1D8(Obj_1ED1D8* self)
{
    self->f3C = 0;
    self->f44 = self->f40->c70;
    func_001837E0(self, 0x1A, 0, 0);
}

struct Inner_1ED210 { u8 pad[0xC3C]; s32 c3C; };
struct Obj_1ED210 { u8 pad0[0x40]; Inner_1ED210* f40; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_001ED318(Obj_1ED210* self, s32* p);

void func_001ED210(Obj_1ED210* self)
{
    s32 n;
    func_001837E0(self, 0x1C, 0, 0);
    n = 5;
    func_001ED318(self, &n);
    if (self->f40->c3C) {
        n = 3;
        func_001ED318(self, &n);
    }
}

struct Item_1ED558 { s32 kind; s32 p; f32 f8; s32 fC; };

Item_1ED558* func_001ED4C8(void* self, s32 kind, s32 p);

void func_001ED558(void* self, s32 p, s32 val)
{
    func_001ED4C8(self, 0, p)->fC = val;
}



void func_001ED588(void* self, s32 p, s32 val)
{
    func_001ED4C8(self, 1, p)->fC = val;
}


void func_001ED5B8(void* self, s32 p)
{
    func_001ED4C8(self, 2, p);
}


void func_001ED5D8(void* self, s32 p)
{
    func_001ED4C8(self, 3, p);
}


void func_001ED5F8(void* self, s32 p)
{
    func_001ED4C8(self, 4, p);
}


void func_001ED618(void* self, s32 p)
{
    func_001ED4C8(self, 5, p);
}

struct Out_1ED650 { f32 x; f32 y; f32 z; };
struct Pair_1ED650 { f32 a; f32 b; };

void func_001EAD88(f32* a, f32* b);

void func_001ED650(Out_1ED650* out, f32 unused, f32 scale, f32 z)
{
    Pair_1ED650 p;
    func_001EAD88(&p.a, &p.b);
    out->x = p.b * scale;
    out->y = p.a * scale;
    out->z = z;
}

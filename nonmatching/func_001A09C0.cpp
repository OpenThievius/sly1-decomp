// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the frame and helper-call sequence match, but the compiler saves
// the constant-data register after the constructor call and orders the prologue
// and scale store differently from retail.
#include "common.h"

typedef u64 Quad_1A09C0 __attribute__((mode(TI)));
struct Obj_1A09C0 { u8 pad0[0x1C]; f32 scale; u32 handle; u8 pad28[8]; u8 pad30[0x10]; Quad_1A09C0 value40; };
extern u8* D_00275710;
extern Quad_1A09C0 D_0026B590;
extern Quad_1A09C0 D_0026B5A0;
void func_00118CF0(Quad_1A09C0* out, f32 value);
Quad_1A09C0* func_00118D10(Quad_1A09C0* out, void* src);
Quad_1A09C0 func_00118D30(Quad_1A09C0 a, Quad_1A09C0 b);
Quad_1A09C0* func_00118D20(Quad_1A09C0* out, Quad_1A09C0 value);

void func_001A09C0(Obj_1A09C0* self, f32 value)
{
    Quad_1A09C0 first;
    Quad_1A09C0 second;
    Quad_1A09C0* constant = &D_0026B590;
    func_0019EB28(self);
    Quad_1A09C0* output = (Quad_1A09C0*)((u8*)self + 0x30);
    self->scale = 0.25f;
    self->handle = *(u32*)(D_00275710 + 0x1D08);
    func_00118CF0(&first, value);
    Quad_1A09C0 firstValue = first;
    func_00118D10(&second, constant);
    func_00118D20(output, func_00118D30(firstValue, second));
    self->value40 = D_0026B5A0;
}

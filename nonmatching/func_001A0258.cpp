// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the frame and calls match, but the global loads, float-register
// allocation, and store scheduling before func_00118CF0 still differ.
#include "common.h"

typedef u64 Quad_1A0258 __attribute__((mode(TI)));
struct Obj_1A0258 { u8 pad0[0x1C]; f32 scale; u32 handle; u8 pad28[0x18]; Quad_1A0258 value40; u8 pad50[0x60]; f32 valueB0; };
extern u8* D_00275710;
extern Quad_1A0258 D_0026B570;
extern Quad_1A0258 D_0026B580;
void func_00118CF0(Quad_1A0258* out, f32 value);
Quad_1A0258* func_00118D10(Quad_1A0258* out, void* src);
Quad_1A0258 func_00118D30(Quad_1A0258 a, Quad_1A0258 b);
Quad_1A0258* func_00118D20(Quad_1A0258* out, Quad_1A0258 value);

void func_001A0258(Obj_1A0258* self, f32 value)
{
    Quad_1A0258 q0;
    Quad_1A0258 q1;
    Quad_1A0258* constant = &D_0026B580;
    func_0019EB28(self);
    Quad_1A0258* output = (Quad_1A0258*)((u8*)self + 0x30);
    u8* context = D_00275710;
    u32 handle = *(u32*)(context + 0x1D04);
    f32 low = -15.0f;
    f32 factor = 0.35f;
    self->valueB0 = low;
    self->handle = handle;
    self->value40 = D_0026B570;
    self->scale = factor;
    func_00118CF0(&q0, value);
    Quad_1A0258 first = q0;
    func_00118D10(&q1, constant);
    func_00118D20(output, func_00118D30(first, q1));
}

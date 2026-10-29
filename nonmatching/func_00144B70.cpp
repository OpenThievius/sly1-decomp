// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the helper calls are modeled, but the compiler uses a larger
// stack frame and does not emit retail's quadword copy from the matrix data.
#include "common.h"

void func_00144AA0(void* a0, void* a1, void* a2, f32 f12, f32 f13, f32 f14);
void func_00144978(void* a0, void* a1, void* a2, f32* a3, f32* a4, f32* a5);
typedef f32 Vec4_00144B70 __attribute__((vector_size(16)));

void func_00144B70(void* self, void* matrix, void* output)
{
    f32* values = (f32*)((u8*)self + 0x2B0);
    void* transform = (u8*)self + 0x40;
    u8 temp[0x10];
    func_00144AA0((u8*)self + 0x2D0, transform, output,
                  values[0], values[1], values[2]);
    func_00144978(matrix, transform, temp, values, values + 1, values + 2);
    *(Vec4_00144B70*)((u8*)self + 0x2D0) = *(Vec4_00144B70*)matrix;
}

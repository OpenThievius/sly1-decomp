// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: all frame and helper instructions match; the two argument moves around func_001DD6D0 differ in order.
#include "common.h"
struct Quad_1036F0 { s32 a, b, c, d; };
struct Frame_1036F0 { Quad_1036F0 q, t; s32 count; void* value; };
void func_0011B008(Quad_1036F0* q);
void func_0011B018(void* out, Quad_1036F0* q);
void func_0011B060(Quad_1036F0* q, s32 mode);
void func_0011B0A8(Quad_1036F0* q, Quad_1036F0* t);
void func_0011B5F0(Quad_1036F0* q, s32 value);
void func_001C23B0(Quad_1036F0* t, s32 mode, s32 c, s32* count, void** value);
s32 func_001DD6D0(void* object, void* value);
void* func_001036F0(void* self, void* object, s32 unused, s32 c)
{
    Frame_1036F0 f;
    func_0011B008(&f.q);
    f.count = 0xF;
    func_001C23B0(&f.t, 1, c, &f.count, &f.value);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 result = func_001DD6D0(object, f.value);
    func_0011B5F0(&f.q, result);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

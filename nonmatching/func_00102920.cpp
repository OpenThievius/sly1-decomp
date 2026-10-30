// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: constructor and float callback match; the count store and two stack-address calculations are reordered.
#include "common.h"
struct Quad_102920 { s32 a, b, c, d; };
struct Frame_102920 { Quad_102920 q, t; s32 count; f32 value; };
void func_0011B008(Quad_102920* q);
void func_0011B018(void* out, Quad_102920* q);
void func_0011B060(Quad_102920* q, s32 mode);
void func_0011B0A8(Quad_102920* q, Quad_102920* t);
void func_0011B538(Quad_102920* q, s32 n);
void func_001C23B0(Quad_102920* t, s32 mode, s32 c, s32* count, f32* value);
void func_00155F78(void* object, f32 value);
void* func_00102920(void* self, void* object, s32 unused, s32 c)
{
    Frame_102920 f;
    func_0011B008(&f.q);
    s32* count = &f.count;
    f32* value = &f.value;
    f.count = 1;
    func_001C23B0(&f.t, 1, c, count, value);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00155F78(object, f.value);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

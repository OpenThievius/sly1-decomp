// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: retail frame and call flow match; the two argument moves around func_0011B8A8 are reversed.
#include "common.h"

struct Quad_101418 { s32 a, b, c, d; };
struct Frame_101418 { Quad_101418 q; Quad_101418 t; s32 count; s32 value; };
void func_0011B008(Quad_101418* q);
void func_0011B018(void* out, Quad_101418* q);
void func_0011B060(Quad_101418* q, s32 mode);
void func_0011B0A8(Quad_101418* q, Quad_101418* t);
void func_0011B8A8(Quad_101418* q, void* value);
void func_001C23B0(Quad_101418* t, s32 mode, s32 c, s32* count, s32* value);
void* func_00129B98(void* object, s32 value);
void* func_00101418(void* self, void* object, s32 unused, s32 c)
{
    Frame_101418 f;
    func_0011B008(&f.q);
    f.count = 6;
    func_001C23B0(&f.t, 1, c, &f.count, &f.value);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    void* value = (void*)func_00129B98(object, f.value);
    func_0011B8A8(&f.q, value);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

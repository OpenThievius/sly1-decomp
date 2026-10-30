// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: retail frame and call flow match; the two argument moves around func_0011B5F0 are reversed.
#include "common.h"

struct Quad_1005A0 { s32 a, b, c, d; };
struct Frame_1005A0 { Quad_1005A0 q; Quad_1005A0 t; s32 count; s32 value; };
void func_0011B008(Quad_1005A0* q);
void func_0011B018(void* out, Quad_1005A0* q);
void func_0011B060(Quad_1005A0* q, s32 mode);
void func_0011B0A8(Quad_1005A0* q, Quad_1005A0* t);
void func_0011B5F0(Quad_1005A0* q, s32 value);
void func_001C23B0(Quad_1005A0* t, s32 mode, s32 c, s32* count, s32* value);
s32 func_001833F0(void* object, s32 value);
void* func_001005A0(void* self, void* object, s32 unused, s32 c)
{
    Frame_1005A0 f;
    func_0011B008(&f.q);
    f.count = 6;
    func_001C23B0(&f.t, 1, c, &f.count, &f.value);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 value = func_001833F0(object, f.value);
    func_0011B5F0(&f.q, value);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

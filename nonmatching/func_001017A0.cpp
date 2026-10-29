// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: retail frame, data setup, and helper flow match; the two argument moves around func_0011B5F0 are reversed.
#include "common.h"
struct Quad_1017A0 { s32 a, b, c, d; };
struct Frame_1017A0 { Quad_1017A0 q, data, t; s32 count; };
void func_0011B008(Quad_1017A0* q);
void func_0011B018(void* out, Quad_1017A0* q);
void func_0011B060(Quad_1017A0* q, s32 mode);
void func_0011B0A8(Quad_1017A0* q, Quad_1017A0* t);
void func_0011B5F0(Quad_1017A0* q, void* value);
void func_001C23B0(Quad_1017A0* t, s32 mode, s32 c, s32* count, Quad_1017A0* data);
void* func_001BC670(void* object, Quad_1017A0* data);
void* func_001017A0(void* self, void* object, s32 unused, s32 c)
{
    Frame_1017A0 f;
    func_0011B008(&f.q);
    f.count = 2;
    func_001C23B0(&f.t, 1, c, &f.count, &f.data);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B5F0(&f.q, func_001BC670(object, &f.data));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

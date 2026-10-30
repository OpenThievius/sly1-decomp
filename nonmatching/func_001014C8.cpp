// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the frame and helper sequence match; the two argument moves around func_0011B8A8 are reversed.
#include "common.h"
struct Quad_1014C8 { s32 a, b, c, d; };
struct Frame_1014C8 { Quad_1014C8 q, t; };
void func_0011B008(Quad_1014C8* q);
void func_0011B018(void* out, Quad_1014C8* q);
void func_0011B060(Quad_1014C8* q, s32 mode);
void func_0011B0A8(Quad_1014C8* q, Quad_1014C8* t);
void func_0011B8A8(Quad_1014C8* q, void* value);
void func_001C23B0(Quad_1014C8* t, s32 mode, s32 c, void* z);
void* func_00129CA8(void* object);
void* func_001014C8(void* self, void* object, s32 unused, s32 c)
{
    Frame_1014C8 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    void* value = func_00129CA8(object);
    func_0011B8A8(&f.q, value);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

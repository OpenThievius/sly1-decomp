// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 164/192, checked 2026-11-01
// NEAR: check.py reports DIFFER; candidate scalar initialization does not reproduce retail pextlw/pcpyld MMI vector construction and sq stores.
#include "common.h"

struct __attribute__((aligned(16))) Float4_1C0F30 { f32 x, y, z, w; };
struct Obj_1C0F30 {
    u8 pad00[0x2D0];
    u32 mask;
    f32 f2D4;
    f32 f2D8;
    f32 f2DC;
    f32 f2E0;
    u8 pad2E4[0xC];
    Float4_1C0F30 v2F0;
    Float4_1C0F30 v300;
    u8 pad310[0x10];
    f32 f320;
    f32 f324;
    u8 pad328[4];
    s32 f32C;
};
void func_00123ED0(void*);

void func_001C0F30(Obj_1C0F30* self)
{
    func_00123ED0(self);
    self->mask = 0x80808080;
    self->f2D8 = 400.0f;
    self->f320 = 0.3f;
    self->f324 = 0.5f;
    self->f32C = -1;
    self->v2F0.x = 0.0f;
    self->v2F0.y = 0.0f;
    self->v2F0.z = 50.0f;
    self->v2F0.w = 0.0f;
    self->v300.x = 100.0f;
    self->v300.y = 0.0f;
    self->v300.z = 80.0f;
    self->v300.w = 0.0f;
    self->f2D4 = 0.5f;
    self->f2DC = 0.5f;
    self->f2E0 = 0.5f;
}

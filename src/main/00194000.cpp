// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001AA8F0(void* self);

struct Ctl_194F00 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; };

void func_00194F00(Ctl_194F00* self)
{
    if (self->mode250 == 3 && self->f274 != 0) return;
    func_001AA8F0(self);
}

void func_001AA958(void* self);

struct Ctl_194F38 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; s32 f278; };

void func_00194F38(Ctl_194F38* self)
{
    if (self->mode250 == 3 && self->f274 != 0) {
        self->f274 = 0;
        self->f278 = -1;
        return;
    }
    func_001AA958(self);
}

void func_001936A0(void* self, s32 v);

struct Ctl_195928 { u8 pad[0x260]; s32 f260; };

void func_00195928(Ctl_195928* self, s32 v)
{
    if (self->f260 != v) {
        self->f260 = v;
        if (v != -1) func_001936A0(self, v);
    }
}

struct Obj_1963D8 { u8 pad0[0x14]; u8* f14; };

void func_00123ED0(Obj_1963D8* self);
void func_00152470(u8* dst, Obj_1963D8* src);

void func_001963D8(Obj_1963D8* self)
{
    func_00123ED0(self);
    func_00152470(self->f14 + 0x1C3C, self);
}

struct Obj_196900 { void** vtbl; };

void func_00124A48(Obj_196900* self);

void func_00196900(Obj_196900* self)
{
    func_00124A48(self);
    ((void (*)(Obj_196900*))self->vtbl[7])(self);
}

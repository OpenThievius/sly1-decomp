// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls PAL-only func_eu_001AAFB0, replaces f4 with the result of the callback at +0xC of the object at f4 + 0x4C (given f4 + f8 and 0.9, 0.9), sets f518, and when func_0015C188(2) is set stores func_0015C1C0(2) through the pointer at f520 (= D_002743F0).
extern u8 D_002743F0[];
void func_eu_001AAFB0(void* self);
s32 func_0015C188(s32 k);

typedef void* (*FnF_eu_001AD5E0)(void* p, f32 a, f32 b);
struct Sub_eu_001AD5E0 { u8 pad[8]; s16 f8; u8 pad2[2]; FnF_eu_001AD5E0 fC; };
struct Inner_eu_001AD5E0 { u8 pad[0x4C]; Sub_eu_001AD5E0* f4C; };
struct Obj_eu_001AD5E0 { u8 pad0[4]; void* f4; u8 pad1[0x48]; u8 pad2[0x518 - 0x50]; s32 f518; u8 pad3[4]; void** f520; };

void func_eu_001AD5E0(Obj_eu_001AD5E0* self)
{
    func_eu_001AAFB0(self);
    Inner_eu_001AD5E0* a = (Inner_eu_001AD5E0*)self->f4;
    Sub_eu_001AD5E0* b = a->f4C;
    self->f4 = b->fC((u8*)a + b->f8, 0.9f, 0.9f);
    self->f518 = 0xDF7F7F7F;
    if (func_0015C188(2) != 0) {
        self->f520 = (void**)D_002743F0;
        *self->f520 = func_0015C1C0(2);
    }
}

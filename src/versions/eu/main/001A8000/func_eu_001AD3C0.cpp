// SPDX-License-Identifier: AGPL-3.0-or-later
// Runs the sub-object's update with 1.25 twice, stores the result in the object, and sets the pointer at 0x520 when the test passes.
extern u8 D_eu_0027DB20[];

struct SubInfo_eu_1AD3C0 {
    u8 pad[8];
    s16 off;
    u8 pad2[2];
    s32 (*fn)(void* self, f32 a, f32 b);
};
struct Sub_eu_1AD3C0 {
    u8 pad[0x4C];
    SubInfo_eu_1AD3C0* info;
};
struct Obj_eu_1AD3C0 {
    u8 pad0[4];
    Sub_eu_1AD3C0* sub;
    u8 pad8[0x518];
    s32* f520;
};

void func_eu_001AAFB0(Obj_eu_1AD3C0* self);
s32 func_0015C188(s32 a);
struct In_1AA5A0;
struct In_1AA5A0* func_0015C1C0(s32 a);

void func_eu_001AD3C0(Obj_eu_1AD3C0* self)
{
    func_eu_001AAFB0(self);
    Sub_eu_1AD3C0* sub = self->sub;
    self->sub = (Sub_eu_1AD3C0*)sub->info->fn((u8*)sub + sub->info->off, 1.25f, 1.25f);
    if (func_0015C188(2) != 0) {
        self->f520 = (s32*)D_eu_0027DB20;
        *self->f520 = (s32)func_0015C1C0(2);
    }
}

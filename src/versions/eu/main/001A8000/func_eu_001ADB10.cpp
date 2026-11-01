// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: sets up the object's float fields, calls a method of its sub-object with two 1.0 floats, and stores a result through the pointer at 0x520.
typedef s32 (*Method_eu_1ADB10)(void* self, f32 a, f32 b);

struct Sub_eu_1ADB10 {
    u8 pad0[8];
    s16 off8;
    u8 pad0A[2];
    Method_eu_1ADB10 fnC;
};

struct Self_eu_1ADB10 {
    s32 f0;
    s32 f4;
    u8 pad8[0x51C - 8];
    f32 f51C;
    s32* f520;
    u8 pad524[0x558 - 0x524];
    f32 f558;
};

extern s32 D_eu_0027DB60[];
void func_eu_001AAFB0(void* self);
s32 func_0015C188(s32 i);

void func_eu_001ADB10(Self_eu_1ADB10* self)
{
    func_eu_001AAFB0(self);
    In_1AA5A0* o = func_0015C1C0(0);
    Sub_eu_1ADB10* sub = (Sub_eu_1ADB10*)o->vt;
    self->f4 = sub->fnC((u8*)o + sub->off8, 1.0f, 1.0f);
    self->f51C = 0.8f;
    self->f558 = 0.5f;
    if (func_0015C188(2) != 0) {
        self->f520 = D_eu_0027DB60;
        s32 r = (s32)func_0015C1C0(2);
        *self->f520 = r;
    }
}

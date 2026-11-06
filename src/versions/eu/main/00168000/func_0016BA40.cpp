// SPDX-License-Identifier: AGPL-3.0-or-later
// Constructor tail of an object holding a child: refreshes the child pointer, its colour and layout position.
void func_001AA268(void* self);
void func_001AAB20(void* self, f32 x, f32 y);
void func_0015C8B8(void* a, f32 x, f32 y);
void func_0015C900(void* h);
struct Vt_16BA40_eu {
    u8 pad0[0x8];
    s16 off8;
    u8 pad1[0x2];
    void* (*fn0C)(void* self, f32 a, f32 b);
    u8 pad2[0x8];
    s16 off18;
    u8 pad3[0x2];
    f32 (*fn1C)(void* self, s32 a);
};

struct Node_16BA40_eu {
    u8 pad0[0x8];
    s32 i8;
    u8 pad1[0x3C];
    f32 f48;
    Vt_16BA40_eu* vt4C;
};

struct Self_16BA40_eu {
    u8 pad0[0x4];
    Node_16BA40_eu* f4;
    u8 pad1[0x510];
    s32 f518;
    u8 pad2[0x4];
    void** f520;
};

void func_0016BA40(Self_16BA40_eu* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->f520 = (void**)D_002629A8;
        *self->f520 = (void*)GetFontById(2);
    }
    Node_16BA40_eu* a1 = self->f4;
    f32 f20 = 60.0f;
    f32 f21 = 90.0f;
    Vt_16BA40_eu* vt = a1->vt4C;
    Node_16BA40_eu* n = (Node_16BA40_eu*)vt->fn0C((u8*)a1 + vt->off8, 1.0f, 1.0f);
    self->f4 = n;
    self->f518 = (s32)0xDF7F7F7F;
    f20 = (f32)n->i8 * n->f48 + f20;
    Node_16BA40_eu* s0 = (Node_16BA40_eu*)GetFontById(4);
    PushFontScale(s0, 1.3f, 1.3f);
    Vt_16BA40_eu* v = s0->vt4C;
    f32 r = v->fn1C((u8*)s0 + v->off18, 0x5F);
    f21 = r * 4.0f + f21;
    f20 = f20 + (f32)s0->i8 * s0->f48 * 4.0f;
    PopFontScale(s0);
    SetScreenElementSize(self, f21, f20);
}

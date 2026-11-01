// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: phase at 0x598, and the 512-line screen: other y scale and offset, other line positions.
struct Self_133B58_eu
{
    u8 pad000[0x598];
    f32 phase;
};

void func_00133B58(Self_133B58_eu* self, Gs_133B58* gs)
{
    Rgba_133B58 c0;
    Rgba_133B58 c1;
    Rgba_133B58 c2;
    f32 step = 1.0f / 24.0f;
    f32 t;
    t = 0.5f - func_00205210(self->phase) * 0.5f;
    c0 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->phase + 1.5707964f) * 0.5f;
    c1 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->phase + 3.1415927f) * 0.5f;
    c2 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    s32 i;
    f32 x;

    func_001613C0(gs, 0x8C, 2, 0x41);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x7ABB, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7ADE, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x7ABB, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7ADE, 0, 0);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x80C2, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80A0, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x80C2, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80A0, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7ADE, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x7B01, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v = r + 4.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7ADE, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x7B01, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80A0, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x807D, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v = r - 4.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80A0, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x807D, 0, 0);
}

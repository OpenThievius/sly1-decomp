// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL changes the y scale (0.5462963f) and the y offset (1920.0f).

void func_0015D338(Self_15D338* self, u32 color, Strm_15D338* s, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1)
{
    color = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
    func_001617E8(s, color, 0.0f);
    func_00161860(s, (s32)(u0 * 16.0f), (s32)(v0 * 16.0f));
    func_001618C0(s, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.5462963f + 1920.0f) * 16.0f), self->f40, 0);
    func_00161860(s, (s32)(u1 * 16.0f), (s32)(v1 * 16.0f));
    func_001618C0(s, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.5462963f + 1920.0f) * 16.0f), self->f40, 0);
}

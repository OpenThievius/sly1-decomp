// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: key is an unsigned 16-bit glyph, 576-line screen (468.6 limit, 0.5463 scale, 1920 offset)
Entry_15CF70* func_0015DAB8(Self_15CF70* self, u16 key);
extern s32 D_eu_00263564;
extern s32 D_eu_00263568;

void func_0015CF70(Self_15CF70* self, u16 key, u32 color, Strm_15CF70* s, f32 x, f32 y)
{
    Entry_15CF70* e = func_0015DAB8(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->m60 >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->m8 * self->f48;
        f32 w = (f32)e->a6 * self->f44;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 468.61017f) {
            s32 u0 = (e->a2 << 4) + D_eu_00263564;
            s32 v0 = ((s4 - e->a4) << 4) + D_eu_00263568;
            s32 u1 = ((e->a2 + e->a6) << 4) + D_eu_00263564;
            s32 v1 = ((s4 - (e->a4 + self->m8)) << 4) + D_eu_00263568;
            s32 ok = func_0015CAB8(self, s);
            func_001613C0(s, 6, 1, 0xE);
            if (ok != 0) {
                func_00161708(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->f30 != 0) {
                v = self->f38;
            }
            func_00161708(s, 0x47, (u64)v);
            func_00161708(s, 0x42, (u64)0x44);
            func_00161708(s, 6, (u64)self->m60);
            func_00161708(s, 0x14, (u64)0x60);
            func_00161708(s, 8, (u64)5);
            func_00161708(s, 0, (u64)0x1D4);
            func_00161768(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            func_001617E8(s, tag, 0.0f);
            func_00161860(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.5462963f + 1920.0f) * 16.0f);
            func_001618C0(s, sx, sy, self->m40, 0);
            func_00161860(s, u1, v0);
            s32 sy2 = (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
            func_001618C0(s, sx, sy2, self->m40, 0);
            func_00161860(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            func_001618C0(s, sx2, sy, self->m40, 0);
            func_00161860(s, u1, v1);
            func_001618C0(s, sx2, sy2, self->m40, 0);
            self->disp->fn((u8*)self + self->disp->offset, 0, D_00262280);
        }
    }
}

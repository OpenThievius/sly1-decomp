// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the line is built as a 16-bit string: the percentage formatted as "%d%% - " on the
// stack, widened into dst, then the translated name of the level key appended; PAL drops
// the time. Its retail counterpart is PAL's func_00194120, not func_00194190 (which is
// PAL's func_00193598, a text lookup that grew a switch): PAL's caller of func_00194190
// calls this one.
extern const char D_eu_0024D940[]; // "%d%% - "
u16* func_eu_00160750(s32 key);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
u16* func_eu_001E3140(u16* dst, char* src);
u16* func_eu_001E30A0(u16* dst, u16* src);

void func_001935B0(Obj_1935B0* self, u16* dst)
{
    char pct[16];
    void* percent = func_00160B28(self);
    func_001E1FD0(pct, D_eu_0024D940, percent);
    func_eu_001E3140(dst, pct);
    func_eu_001E30A0(dst, func_eu_00160750((self->f19D8 << 8) | self->f19DC));
}

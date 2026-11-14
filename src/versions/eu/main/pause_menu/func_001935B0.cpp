// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the line is built as a 16-bit string: the percentage formatted as "%d%% - " on the
// stack, widened into dst, then the translated name of the level key appended; PAL drops
// the time. Its retail counterpart is PAL's func_00194120, not func_00194190 (which is
// PAL's func_00193598, a text lookup that grew a switch): PAL's caller of func_00194190
// calls this one.
extern const char D_eu_0024D940[]; // "%d%% - "
s32 FormatToString(char* dst, const char* fmt, ...);
u16* CopyStringToWide(u16* dst, char* src);
u16* AppendWideString(u16* dst, u16* src);

void FormatGameSummary(GameProgress* self, u16* dst)
{
    char pct[16];
    s32 percent = ComputeCompletionPercent(self);
    FormatToString(pct, D_eu_0024D940, percent);
    CopyStringToWide(dst, pct);
    AppendWideString(dst, (u16*)GetEntryName((self->levelIndex << 8) | self->entryIndex));
}

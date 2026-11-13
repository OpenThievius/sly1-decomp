// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's lookup advances the pointer from FindEntryById by D_eu_00263710 32-byte entries, or 0.
// The shared file declares the result s32; the cast keeps that declaration.
extern s32 D_eu_00263710;

s32 LookupEntryById(void)
{
    u8* p = (u8*)FindEntryById();
    if (p == 0) {
        return 0;
    }
    return (s32)(p + (D_eu_00263710 << 5));
}

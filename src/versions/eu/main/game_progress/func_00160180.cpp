// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's lookup advances the pointer from FindEntryById by D_eu_00263710 32-byte entries, or 0.
extern s32 D_eu_00263710;

void* LookupEntryById(s32 id)
{
    u8* p = (u8*)FindEntryById(id);
    if (p == 0) {
        return 0;
    }
    return p + (D_eu_00263710 << 5);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the field at 0xA8 of the object FindEntryById gives, or 0 when it gives none.
s32 GetEntryFlags(s32 id)
{
    u8* p = (u8*)FindEntryById(id);
    s32 v = 0;
    if (p) {
        v = *(s32*)(p + 0xA8);
    }
    return v;
}

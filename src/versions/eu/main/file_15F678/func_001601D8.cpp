// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the field at 0xA8 of the object FindEntryById gives, or 0 when it gives none.
void* FindEntryById(void);
s32 GetEntryFlags(void)
{
    u8* p = (u8*)FindEntryById();
    s32 v = 0;
    if (p) {
        v = *(s32*)(p + 0xA8);
    }
    return v;
}

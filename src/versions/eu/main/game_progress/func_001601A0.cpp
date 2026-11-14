// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the s32 at +0xA0 of the object func_eu_00160680 gives, or -1 when there is none.
u8* FindKeyEntryByAnyKey(u8* a0);

s32 GetEntryIdByKey(KeyedEntry* key)
{
    u8* o = FindKeyEntryByAnyKey((u8*)key);
    s32 r;

    if (o != 0) {
        r = *(s32*)(o + 0xA0);
    } else {
        r = -1;
    }
    return r;
}

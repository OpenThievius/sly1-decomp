// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the text id 0xA4 of the object FindEntryById gives (passing its key through), or PAL's empty string D_eu_0027F0B0 when there is none.
extern char D_eu_0027F0B0[];
struct Obj_eu_00160750 { u8 pad[0xA4]; s32 fA4; };
void* FindEntryById(s32 key);
char* GetTextTableEntry(s32 id);

void* GetEntryName(s32 key)
{
    Obj_eu_00160750* o = (Obj_eu_00160750*)FindEntryById(key);
    if (o != 0) {
        return GetTextTableEntry(o->fA4);
    }
    return D_eu_0027F0B0;
}

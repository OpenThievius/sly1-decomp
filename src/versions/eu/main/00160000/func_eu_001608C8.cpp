// SPDX-License-Identifier: AGPL-3.0-or-later
// ANDs a mask over the 46 entries of D_00247AF0 (0xAC apart), keyed through func_00160810, then clears bit 1 once for each of 5 entries of D_002623C0 (0x44C apart) whose flag 0x20 is clear.
extern u8 D_00247AF0[];

struct Ent_eu_001608C8 { u8 pad[0xA0]; s32 key; u8 pad2[4]; s32 flags; };
struct Row_eu_001608C8 { s32 f0; u8 pad[0x448]; };

s32 func_eu_001608C8(void)
{
    Ent_eu_001608C8* e = (Ent_eu_001608C8*)D_00247AF0;
    Ent_eu_001608C8* end = (Ent_eu_001608C8*)(D_00247AF0 + 0x1EE8);
    s32 mask = 0xE;
    do {
        s32* p = (s32*)func_00160810(e->key);
        mask &= (~e->flags | *p);
        e++;
    } while (e < end);
    s32 keep = ~2;
    u8* base = (u8*)D_002623C0;
    Row_eu_001608C8* r = (Row_eu_001608C8*)(base + 0x8A4);
    for (s32 i = 4; i >= 0; i--) {
        if ((r->f0 & 0x20) == 0) {
            mask &= keep;
        }
        r++;
    }
    return mask;
}

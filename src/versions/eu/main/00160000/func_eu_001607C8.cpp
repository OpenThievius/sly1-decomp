// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the s32 at +0xA0 of the object func_eu_00160680 gives, or -1 when there is none.
void* func_eu_00160680(void);

s32 func_eu_001607C8(void)
{
    u8* o = (u8*)func_eu_00160680();
    s32 r;

    if (o != 0) {
        r = *(s32*)(o + 0xA0);
    } else {
        r = -1;
    }
    return r;
}

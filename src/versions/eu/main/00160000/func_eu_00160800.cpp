// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns the field at 0xA8 of the object func_eu_00160718 gives, or 0 when it gives none.
void* func_eu_00160718(void);
s32 func_eu_00160800(void)
{
    u8* p = (u8*)func_eu_00160718();
    s32 v = 0;
    if (p) {
        v = *(s32*)(p + 0xA8);
    }
    return v;
}

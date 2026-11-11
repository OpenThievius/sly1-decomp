// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: returns the pointer from func_eu_00160718 advanced by D_eu_00263710 32-byte entries, or 0.
extern s32 D_eu_00263710;
void* func_eu_00160718(void);

void* func_eu_00160788(void)
{
    u8* p = (u8*)func_eu_00160718();
    if (p == 0) {
        return 0;
    }
    return p + (D_eu_00263710 << 5);
}

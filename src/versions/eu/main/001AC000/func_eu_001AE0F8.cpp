// SPDX-License-Identifier: AGPL-3.0-or-later
// When the state at 0x560 is 3 and the flag at 0x570 is set, clears the flag; otherwise calls func_001AA958.
void func_001AA958(u8* a0);
void func_eu_001AE0F8(u8* a0)
{
    if (*(s32*)(a0 + 0x560) == 3) {
        if (*(s32*)(a0 + 0x570) != 0) {
            *(s32*)(a0 + 0x570) = 0;
            return;
        }
    }
    func_001AA958(a0);
}

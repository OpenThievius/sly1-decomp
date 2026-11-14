// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object is element D_eu_00263710 (32 bytes each) of the table at D_00247AB0
extern s32 D_eu_00263710;
void ResetGameSessionAndFade(void)
{
    ResetGameSession();
    StartObjectFade((IdentityKey*)((u8*)&D_00247AB0 + D_eu_00263710 * 32), -1, 0);
}

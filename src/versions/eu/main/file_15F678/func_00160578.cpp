// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL picks the object from a table of 32-byte entries indexed by a global, not a fixed one.
extern u8 D_eu_00249050[];
extern s32 D_eu_00263710;

void func_00160578(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    func_001F0428((Obj_160578*)(D_eu_00249050 + D_eu_00263710 * 32), -1, 1);
    if (s0 != -1) {
        func_0018E4F0(s0, 0xF);
    }
}

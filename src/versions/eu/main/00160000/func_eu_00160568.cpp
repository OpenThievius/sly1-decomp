// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies a 7-word table to the stack and stores in D_eu_00263710 the index of the first of five entries (via D_eu_002636D8) matching the argument.
struct Table_eu_00160568 {
    s32 v[7];
};
extern Table_eu_00160568 D_eu_0024CB00;
extern s32 D_eu_002636D8[];
extern s32 D_eu_00263710;

void func_eu_00160568(s32 key)
{
    Table_eu_00160568 t = D_eu_0024CB00;
    for (u32 i = 0; i < 5; i++) {
        if (key == t.v[D_eu_002636D8[i]]) {
            D_eu_00263710 = i;
            break;
        }
    }
}

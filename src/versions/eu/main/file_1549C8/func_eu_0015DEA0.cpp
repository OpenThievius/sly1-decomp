// SPDX-License-Identifier: AGPL-3.0-or-later
// Reads entry i of a table: a byte table for kind 0, a halfword table for kind 1, 0 otherwise.
struct Table_eu_0015DEA0 { s32 kind; s32 f4; u8* data; };
s32 func_eu_0015DEA0(Table_eu_0015DEA0* t, s32 i)
{
    switch (t->kind) {
    case 0:
        return t->data[i];
    case 1:
        return ((u16*)t->data)[i];
    }
    return 0;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: case 3 calls func_eu_001387C8 (a 16-bit string reader) instead of func_001384A0.
void func_eu_001387C8(Rd_150570* r, void* out);

void func_00150570(void* unused, Rd_150570* rd, s32* outCount, Ent_150570** outArr)
{
    s32 i = 0;
    *outCount = func_00137CC0(rd);
    *outArr = (Ent_150570*)func_0018D5C0(*outCount * 0x28);
    for (i = 0; i < *outCount; i++) {
        Ent_150570* e = (Ent_150570*)((u8*)*outArr + i * 0x28);
        e->type = func_00137CC0(rd);
        switch (e->type) {
        case 0:
        case 7:
            func_00138550(rd, &e->w4);
            break;
        case 1:
        case 2:
            e->w4 = func_00137D10(rd);
            e->w8 = func_00137D10(rd);
            break;
        case 3:
            *(f32*)&e->w4 = func_00137DF8(rd);
            *(f32*)&e->w8 = func_00137DF8(rd);
            e->wC = func_00137B90(rd);
            e->w10 = func_00137B90(rd);
            e->w18 = func_00137D10(rd);
            e->w1C = func_00137D10(rd);
            e->w20 = func_00137D10(rd);
            e->w24 = func_00137D10(rd);
            func_eu_001387C8(rd, e->w14);
            break;
        case 4:
            e->w4 = func_00137D10(rd);
            break;
        }
    }
}

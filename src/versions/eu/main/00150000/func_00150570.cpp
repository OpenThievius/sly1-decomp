// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: case 3 calls func_eu_001387C8 (a 16-bit string reader) instead of func_001384A0.
void func_eu_001387C8(BufferedStream* r, void* out);

void func_00150570(void* unused, BufferedStream* rd, s32* outCount, Ent_150570** outArr)
{
    s32 i = 0;
    *outCount = ReadBufferedS8(rd);
    *outArr = (Ent_150570*)AllocateZeroedFrontMemory(*outCount * 0x28);
    for (i = 0; i < *outCount; i++) {
        Ent_150570* e = (Ent_150570*)((u8*)*outArr + i * 0x28);
        e->type = ReadBufferedS8(rd);
        switch (e->type) {
        case 0:
        case 7:
            ReadOptionalBufferedBlock(rd, &e->w4);
            break;
        case 1:
        case 2:
            e->w4 = ReadBufferedS16(rd);
            e->w8 = ReadBufferedS16(rd);
            break;
        case 3:
            *(f32*)&e->w4 = ReadBufferedFloat(rd);
            *(f32*)&e->w8 = ReadBufferedFloat(rd);
            e->wC = ReadBufferedU8(rd);
            e->w10 = ReadBufferedU8(rd);
            e->w18 = ReadBufferedS16(rd);
            e->w1C = ReadBufferedS16(rd);
            e->w20 = ReadBufferedS16(rd);
            e->w24 = ReadBufferedS16(rd);
            func_eu_001387C8(rd, e->w14);
            break;
        case 4:
            e->w4 = ReadBufferedS16(rd);
            break;
        }
    }
}

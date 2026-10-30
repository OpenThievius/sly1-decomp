// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the table-driven CRC scan and error flag are modeled. The
// compiler assigns the running checksum, table base, and count differently,
// producing a 204-byte C function versus retail's 196 bytes.
#include "common.h"

extern u32 D_002C3B00[];
extern s32 D_00262310;
extern u8 func_00100000[];
extern u8 D_00148D74[];

void func_0015EDB8(void)
{
    s32 remaining = (s32)D_00148D74;
    const u32* table = D_002C3B00;
    const u32* data = (const u32*)func_00100000;
    u32 crc = 0xFFFFFFFF;
    while (remaining > 0) {
        u32 word = *data++;
        u32 index = (crc ^ (word & 0xFF)) & 0xFF;
        crc = table[index] ^ (crc >> 8);
        index = (crc ^ ((word >> 8) & 0xFF)) & 0xFF;
        crc = table[index] ^ (crc >> 8);
        index = (crc ^ ((word >> 16) & 0xFF)) & 0xFF;
        crc = table[index] ^ (crc >> 8);
        index = (crc ^ (word >> 24)) & 0xFF;
        crc = table[index] ^ (crc >> 8);
        remaining -= 4;
    }
    if (crc != 0) {
        D_00262310 = 1;
    }
}

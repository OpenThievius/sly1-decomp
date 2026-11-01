// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL takes the character unsigned (andi 0xff instead of sign extension).
s32 func_001E0EF8(u8 c)
{
    switch (c) {
    case 0x64:
    case 0x69:
    case 0x75:
        return 10;
    case 0x42:
    case 0x62:
        return 2;
    case 0x6F:
        return 8;
    case 0x78:
        return 16;
    }
    return 10;
}

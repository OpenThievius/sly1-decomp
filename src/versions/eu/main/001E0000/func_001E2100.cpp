// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: reads the characters as unsigned bytes
s32 func_001E2100(const u8* s) { s32 length = 0; while (*s) { s++; length++; } return length; }

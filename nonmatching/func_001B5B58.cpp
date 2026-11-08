// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 215/232 (92.7%), checked 2026-11-07
// NEAR: registers only: every instruction lines up once the last test is `if (base == 0)` and the
//       table is read through a pointer local; temporaries differ in the two table paths. The
//       tables are SjisCharEntry in state_walker.cpp.
#include "common.h"

struct SjisCharEntry { u16 sjis; u16 ascii; };
extern SjisCharEntry D_00274588[];
extern SjisCharEntry D_00274610[];
u16 MapCharToCode(u8 ch)
{
    s32 base = 0;
    s32 idx;
    if (ch >= 0x20 && ch < 0x30) {
        base = 1;
    } else if (ch >= 0x30 && ch < 0x3A) {
        idx = 0;
    } else if (ch >= 0x3A && ch < 0x41) {
        base = 0xB;
    } else if (ch >= 0x41 && ch < 0x5B) {
        idx = 1;
    } else if (ch >= 0x5B && ch < 0x61) {
        base = 0x25;
    } else if (ch >= 0x61 && ch < 0x7B) {
        idx = 2;
    } else if (ch >= 0x7B && ch < 0x7F) {
        base = 0x3F;
    } else {
        return 0;
    }
    if (base == 0) {
        return D_00274610[idx].sjis + ch - D_00274610[idx].ascii;
    }
    SjisCharEntry* e = &D_00274588[ch - (base + 0x1F)];
    return e->sjis;
}

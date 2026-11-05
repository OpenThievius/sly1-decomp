// SPDX-License-Identifier: AGPL-3.0-or-later
// A texture's header as func_00169B18 (00168000.cpp) and func_00152E48 (00150000.cpp) read it:
// the width and height, and a doubleword of GS bits at 0x18 (the layout of the GS's TEX0
// register: func_00169B18 takes the width and height exponents out of bits 26 to 33). Written
// for this project from what retail's code does (build/swarm/st3/groups.tsv, g1697).
#ifndef TEXTURE_HEADER_H
#define TEXTURE_HEADER_H

#include "common.h"

struct TextureHeader {
    u16 w;                  // 0x00: func_00152E48
    u16 h;                  // 0x02
    u8 pad04[0x18 - 0x04];
    u64 tex0;               // 0x18: func_00152E48, func_00169B18
};


#endif

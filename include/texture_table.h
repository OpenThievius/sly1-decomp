// SPDX-License-Identifier: AGPL-3.0-or-later
// The texture table func_001B2988 and func_001B29E0 (001B0000.cpp) take as the first parameter: a
// word of flags, then three arrays (per-entry register words, sizes, cells). func_001ADD28 hands one on. Written for this project from what
// retail's code does (build/swarm/st3/groups.tsv, g2800).
#ifndef TEXTURE_TABLE_H
#define TEXTURE_TABLE_H

#include "common.h"

struct TextureTable {
    u8 pad00[0x02];
    u16 flags;              // 0x02: func_001B29E0
    u8 pad04[0x08 - 0x04];
    u8* singleCell;         // 0x08: func_001B2988 (zero: three cells per entry, else one)
    union {
        void** entries;     // 0x0C: func_001B2988
        void** p0c;         // 0x0C: func_001ADD28 (pairs)
    };
    void** cells;           // 0x10: func_001B2988
};

#endif

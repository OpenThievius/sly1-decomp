// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x14-byte texture table an AnimRecord keeps nelem of (func_001B2F00 reads them; func_001B2988
// and func_001B29E0, src/main/anim_record.cpp, take one as the first parameter): flags, two counts,
// the record it belongs to, then the entries (first image records) and cells (second image records). func_001ADD28 hands one on. Written for this project from what
// retail's code does (build/swarm/st3/groups.tsv, g2800).
#ifndef TEXTURE_TABLE_H
#define TEXTURE_TABLE_H

#include "common.h"

struct AnimRecord;

struct TextureTable {
    u8 pad00[0x02];
    u16 flags;              // 0x02: func_001B29E0
    u8 entryCount;          // 0x04: the entries at 0x0C (func_001B2F00)
    u8 cellCount;           // 0x05: the cells at 0x10 (func_001B2F00)
    u8 pad06[0x08 - 0x06];
    AnimRecord* record;     // 0x08: the record it belongs to; of kind 0, three cells per entry, else one (func_001B2988)
    union {
        void** entries;     // 0x0C: func_001B2988
        void** p0c;         // 0x0C: func_001ADD28 (pairs)
    };
    void** cells;           // 0x10: func_001B2988
};

#endif

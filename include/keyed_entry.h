// SPDX-License-Identifier: AGPL-3.0-or-later
// An entry of the table D_00247AF0 (00160000.cpp defines its 46 entries): a key, an id, a name
// and flags. func_001600A0 returns the entry whose key is the same as its argument's (stride
// 0x2C, 46 entries: it stops at D_00247AF0 + 0x7E8), func_00160110 the one with an id,
// func_001601A0 and func_00160208 read the id and the flags (func_00160208 counts the flags
// of the entries whose id >> 8 is a given value). Written for this project from what retail's
// code does (g4680).
#ifndef KEYED_ENTRY_H
#define KEYED_ENTRY_H

#include "identity_key.h"

struct KeyedEntry {
    IdentityKey key;            // 0x00: func_001600A0 compares its words 2 and 6
    s32 id;                 // 0x20: func_001601A0, func_00160208
    union {
        const char* name;   // 0x24: 00160000.cpp's initialisers
        s32 i24;            // 0x24: Ent_1600A0 (as a word)
    };
    union {
        u32 flags;          // 0x28: Entry_247AF0
        s32 i28;            // 0x28: func_00160208 (bits 2, 4 and 8)
    };
};

typedef char check_KeyedEntry[sizeof(KeyedEntry) == 0x2C ? 1 : -1];

extern const KeyedEntry g_keyedEntries[];   // 00160000.cpp: 46 entries

#endif

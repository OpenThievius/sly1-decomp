// SPDX-License-Identifier: AGPL-3.0-or-later
// A 32-byte key: eight words, of which two (the third and the seventh) identify it. Two keys
// are the same when they are one, or when both exist and (w[2] ^ w[6]) of each agree: the test
// func_001600A0 runs over D_00247AF0 and that Key_18F198::Same, Key_1F00F0::Same and
// Key_160948::Same inline. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g2307 and g4680).
//
// func_0018E410, func_0018F0E8 and func_0018F198 (file_18D8E0.cpp) take one as a parameter;
// D_00248490 is one (0018C000.cpp defines it), D_00275B04 another (its label is 0x1C bytes: its
// readers stop at the seventh word), and every entry of D_00247AF0 begins with one (s1600a0.h).
// The same-key test stays with its views: their forms differ (Key_160948 also tests this).
#ifndef S18E410_H
#define S18E410_H

#include "common.h"

struct S18E410 {
    union {
        u32 w[8];           // 0x00: Key_18F198, Entry_247AF0 (u32)
        s32 i[8];           // 0x00: Ent_18E410, Key_1F00F0, Key_160948, Ent_1600A0 (s32 words 2 and 6)
    };
};

typedef char check_S18E410[sizeof(S18E410) == 0x20 ? 1 : -1];

extern S18E410 D_00248490;      // 0018C000.cpp
extern S18E410 D_00275B04;      // 001F0000.cpp, file_15F678.cpp (label of 0x1C bytes)

#endif

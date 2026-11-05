// SPDX-License-Identifier: AGPL-3.0-or-later
// A texture's header as func_00169B18 (00168000.cpp) and func_00152E48 (00150000.cpp) read it:
// the width and height, and a doubleword of GS bits at 0x18. Written for this project from what
// retail's code does (build/swarm/st3/groups.tsv, g1697).
#ifndef S169B18_H
#define S169B18_H

#include "common.h"

struct S169B18 {
    u16 w;                  // 0x00: func_00152E48
    u16 h;                  // 0x02
    u8 pad04[0x18 - 0x04];
    u64 bits;               // 0x18: func_00152E48, func_00169B18
};


#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// The text block func_0015DB28(blk, a, font) sets up (0015C000.cpp): a word, the text cursor,
// the current font and the default one, an inline font (V24A2, v24a2.h) the parser changes,
// and four colours (0xFF808080 at set-up). func_0015DB80, func_0015DBB8, func_0015DBE0,
// func_0015DFF8, func_0015E1B0, func_0015E290 and func_0015E318 take it as the first parameter;
// func_001AA4F0, func_001AB058 and func_00194F80 keep one on their stacks. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g1818 and g1822).
//
// No code shows its size: the callers' frames give it 0xB0 bytes, which is what its fields
// come to (V24A2 is 0x88 bytes).
#ifndef S15DB28_H
#define S15DB28_H

#include "common.h"
#include "shapes.h"
#include "v24a2.h"

struct S15DB28 {
    union {
        s32 f00;            // 0x00: the second argument (func_0015DB28), func_0015DB80
        u32 u00;            // 0x00
    };
    char* cur;              // 0x04: func_0015DBE0
    V24A2* font;            // 0x08: func_0015DBE0, func_0015DFF8, func_0015E318
    V24A2* deffont;         // 0x0C: the third argument; func_0015DBE0, func_0015E1B0, func_0015E290
    V24A2 inl;              // 0x10: func_0015DBE0, func_0015E318; func_0015DB28 sets its word 0x4C
    s32 fontChanged;        // 0x98: func_0015DB80, func_0015DBE0, func_0015E318
    union {
        u32 c9C;            // 0x9C: func_0015DB28, func_0015DBE0
        Rgba4 rgba9C;       // 0x9C
    };
    union {
        u32 cA0;            // 0xA0
        Rgba4 rgbaA0;       // 0xA0
    };
    union {
        u32 cA4;            // 0xA4
        Rgba4 rgbaA4;       // 0xA4
    };
    union {
        u32 cA8;            // 0xA8
        Rgba4 rgbaA8;       // 0xA8
    };
};


#endif

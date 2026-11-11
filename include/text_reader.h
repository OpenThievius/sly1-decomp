// SPDX-License-Identifier: AGPL-3.0-or-later
// The text reader func_0015DB28(reader, text, font) sets up (font.cpp): the text, the
// cursor in it, the current font and the default one, an inline font (Font, font.h) the
// text's font codes change, and four colours (0xFF808080 at set-up). func_0015DBE0 reads
// the next character, acting on the codes in the text (~ colour, & font, ^ scale);
// func_0015DB80, func_0015DBB8, func_0015DFF8, func_0015E1B0, func_0015E290 and func_0015E318
// take it as the first parameter; func_001AA4F0, func_001AB058 and func_00194F80 keep one on
// their stacks. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g1818 and g1822).
//
// No code shows its size: the callers' frames give it 0xB0 bytes, which is what its fields
// come to (Font is 0x88 bytes).
#ifndef TEXT_READER_H
#define TEXT_READER_H

#include "common.h"
#include "shapes.h"
#include "font.h"

struct TextReader {
    union {
        s32 text;           // 0x00: the second argument (func_0015DB28), func_0015DB80
        u32 u00;            // 0x00
        char* start;        // 0x00: the text's start, as func_0015E068 backs up to it
    };
    char* cur;              // 0x04: func_0015DBE0
    Font* font;            // 0x08: func_0015DBE0, func_0015DFF8, func_0015E318
    Font* defaultFont;      // 0x0C: the third argument; func_0015DBE0, func_0015E1B0, func_0015E290
    Font inlineFont;        // 0x10: func_0015DBE0, func_0015E318; func_0015DB28 sets its word 0x4C
    s32 fontChanged;        // 0x98: func_0015DB80, func_0015DBE0, func_0015E318
    union {
        u32 colorBits;      // 0x9C: the colour characters are drawn in (func_0015DB28, func_0015DBE0)
        Rgba4 color;        // 0x9C
    };
    union {
        u32 baseColorBits;  // 0xA0: the colour a ~RRGGBB code set
        Rgba4 baseColor;    // 0xA0
    };
    union {
        u32 defaultColorBits; // 0xA4: the colour ~. and the end of a code go back to
        Rgba4 defaultColor; // 0xA4
    };
    union {
        u32 inlineFontColorBits; // 0xA8: the colour (with the current alpha) an inline font draws in
        Rgba4 inlineFontColor; // 0xA8
    };
};


#endif

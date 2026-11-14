/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C library's character class table (0x24E878 to 0x24E979): one byte of class bits for the
 * end-of-file value and each of the 256 characters, read from +1 (g_charClassFlags, D_0024E879)
 * by the game's text code (UppercaseString, the text formatter, number parsing). A file with no
 * code (an empty range in config/us/files.tsv), its .rodata at 0x24E878: the first of the
 * libraries' data, after oscillator.cpp's jump tables and before library_state.c's string at
 * 0x24E980, which the 7 bytes of zeros pad to 8. The table is one object of 257 bytes, the label
 * at +1 inside it: nothing reads the first byte by itself. Built like the C library's other files
 * (config/cflags.tsv). Written for this project from retail's data; the bits' names are ours,
 * from the characters that have them. */
#include "common.h"

#define CC_UPPER 0x01   /* A to Z */
#define CC_LOWER 0x02   /* a to z */
#define CC_DIGIT 0x04   /* 0 to 9 */
#define CC_SPACE 0x08   /* tab, line feed, vertical tab, form feed, carriage return, space */
#define CC_PUNCT 0x10   /* the printable characters that are neither letters nor digits */
#define CC_CTRL  0x20   /* the control characters */
#define CC_HEX   0x40   /* A to F, a to f */
#define CC_BLANK 0x80   /* space */

#define C CC_CTRL
#define S (CC_CTRL | CC_SPACE)
#define P CC_PUNCT
#define D CC_DIGIT
#define UX (CC_UPPER | CC_HEX)
#define U CC_UPPER
#define LX (CC_LOWER | CC_HEX)
#define L CC_LOWER

const u8 D_0024E878[257] = {
    0,
    C, C, C, C, C, C, C, C, C, S, S, S, S, S, C, C,
    C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
    CC_SPACE | CC_BLANK, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P,
    D, D, D, D, D, D, D, D, D, D, P, P, P, P, P, P,
    P, UX, UX, UX, UX, UX, UX, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, P, P, P, P, P,
    P, LX, LX, LX, LX, LX, LX, L, L, L, L, L, L, L, L, L,
    L, L, L, L, L, L, L, L, L, L, L, P, P, P, P, C,
};

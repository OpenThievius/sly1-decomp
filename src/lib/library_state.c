/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C library's state record and the pointer to it (g_libraryState, D_0027696C), which the
 * library's functions read: the error number (errno.c), the random seed (random.cpp), the signal
 * table (signal.c). A file with no code (an empty range in config/us/files.tsv), its .data from
 * 0x276680 and its .rodata, the string "C" the record points to at +0x34, at 0x24E980. That
 * string proves the file: a literal is emitted in the object that uses it, and 0x24E980 lies after
 * oscillator.cpp's .rodata (from 0x24E840), so the record cannot be in warp_menu.cpp, whose
 * .rodata ends before it; it is a later file, of the libraries, whose .data comes after
 * warp_menu.cpp's and before system_calls.cpp's. Where it starts in .data is a choice: the
 * strings from 0x276658 to 0x27667C, which nothing reads, could be the end of warp_menu.cpp or
 * the start of this file; they stay in warp_menu.cpp. Its place among the libraries' code is a
 * choice too (any point from 0x1F59C4 to 0x1F6900 links the same; its range is at 0x1F6900).
 * Between oscillator.cpp's jump tables and the string lies the character class table
 * (0x24E878 to 0x24E979, read through g_charClassFlags), which could be the end of
 * oscillator.cpp, the start of this file or a file of its own; it stays in oscillator.cpp's
 * range, from the disassembly. C, built by the Linux cc1 of 2.9-ee-991111-01 like the C library's
 * other files (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * data. */
#include "common.h"

/* One of the three stream records at the record's end (0x58 bytes each, at +0x1E4, +0x23C and
 * +0x294), which its words at +4, +8 and +0xC point at. No code of the game reads their fields
 * and retail holds them as zeros: a byte array of each one's size. */
typedef struct {
    u8 b[0x58];
} LibraryStream;

/* The error number, the three stream pointers after it, the string "C" at +0x34 and the random
 * seed at +0x58; the three streams at the end. */
typedef struct {
    void* words[121];
    LibraryStream streams[3];
} LibraryState;

LibraryState g_libraryStateStorage = { { 0, &g_libraryStateStorage.streams[0], &g_libraryStateStorage.streams[1], &g_libraryStateStorage.streams[2],
                              0, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"C", 0, 0, 0, 0, 0, 0, 0, 0, (void*)1 } };
void* g_libraryState = &g_libraryStateStorage;

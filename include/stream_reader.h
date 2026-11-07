// SPDX-License-Identifier: AGPL-3.0-or-later
// A double-buffered stream reader, set up by InitStreamReader (func_0012FCF0)(rec, buffer): it aligns
// the buffer address to 64 at 0x14, sets 0x04 to -1, clears the rest and returns rec: func_0012FD30, func_0012FD78, func_0012FDE8, func_0012FE70,
// func_0012FF10, func_0012FF20 and func_0012FFE8 (placed_object.cpp) work on it, func_0018F198 keeps one
// on its stack. Written for this project from what retail's code does (build/swarm/st3/groups.tsv,
// g1158). No code shows its size: the set-up and the views end at 0x2C.
#ifndef STREAM_READER_H
#define STREAM_READER_H

#include "common.h"

struct StreamReader {
    s32 sourceKind;         // 0x00: 0 reads through a file handle, 1 through a sector stream, -1 closed
    union {
        s32 fileHandle;     // 0x04: the file handle of kind 0; -1 at set-up and when closed
        void* fileRef;      // 0x04: the same word handed to func_001F8DB8
    };
    union {
        s32 sector;         // 0x08: the next sector of kind 1, advanced by 1 per 2048 bytes read
        void* sectorRef;    // 0x08: the same word handed to func_00140CC8
    };
    s32 pendingLength;      // 0x0C: bytes of the read in flight (at most 0x4000), 0 when none
    s32 pendingDest;        // 0x10: where that read lands: one of the buffer's two 0x4000-byte halves
    s32 buffer;             // 0x14: the buffer's address (the set-up argument aligned to 64)
    s32 readyLength;        // 0x18: bytes the last finished read delivered
    s32 readyStart;         // 0x1C: where they are (the buffer's first half, or the second)
    s32 usedLength;         // 0x20: how many of them have been consumed
    s32 remaining;          // 0x24: bytes still to read
    s32 total;              // 0x28: bytes to read in all
};

#endif

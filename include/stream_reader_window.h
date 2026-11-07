// SPDX-License-Identifier: AGPL-3.0-or-later
// The consumer's view of a StreamReader (stream_reader.h), the first parameter of PumpStreamReader
// (func_00130070) and ConsumeStreamBytes (func_001300D8, 00130000.cpp): its source kind and the three
// fields that say which bytes are ready. func_0018F890 (movie_player.cpp) reads one. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g1249).
#ifndef STREAM_READER_WINDOW_H
#define STREAM_READER_WINDOW_H

#include "common.h"

struct StreamReaderWindow {
    s32 sourceKind;         // 0x00: func_00130070
    u8 pad04[0x18 - 0x04];
    s32 readyLength;        // 0x18: func_0018F890
    s32 readyStart;         // 0x1C
    s32 usedLength;         // 0x20: func_001300D8, func_0018F890
};

#endif

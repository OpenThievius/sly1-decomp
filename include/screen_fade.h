// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x40-byte record at D_00275F80 (.data) and the 0x14-byte request it holds twice.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g3602
// and g3641).
//
// D_00275F80 is not an object of class 0x67 (0x570 bytes): its label is a word, the next one
// (D_00275F84, which file_14EE40.cpp reads) runs to D_00275FC0, and every reader stays inside
// those 0x40 bytes. Its functions are func_001EFCE8, func_001EFD10, func_001EFEE0, func_001EFFA0
// (file_1E88D0.cpp), func_001F00C0, func_001F00F0 and func_001F0220 (file_1E88D0.cpp), each taking it
// as the first parameter; func_001AD970, func_001F3C38 and func_001F4408 name it.
// file_1E88D0.cpp defines it whole, as zeros; D_00275F84 is its mode.
//
// A black fade over the screen: `opacity` goes from 0 to 1 over the time since
// modeStartTime (func_001EFD10), func_001EFEE0 draws the black rectangle with it, and the
// request it was started for is carried out (func_001F0220, mode 2) once the fade is done.
#ifndef SCREEN_FADE_H
#define SCREEN_FADE_H

#include "common.h"
#include "identity_key.h"

// A request: func_001EFFA0 takes one as its second parameter and copies it into the record
// (its callers build it on their stacks: func_00160DA0, func_001F4408, func_001F4A30), and
// func_001F00F0 copies the saved one over the current one as 0x14 bytes (Blk20_1F00F0: two
// unaligned doublewords and a word).
struct FadeRequest {
    s32 kind;               // 0x00
    union {
        IdentityKey* key;       // 0x04: func_001EFFA0 (Text_1EFFA0 reads words 2 and 6), func_001F00F0
        u8* text;           // 0x04: func_00160DA0
    };
    s32 f08;                // 0x08
    s32 f0C;                // 0x0C
    s32 flags;              // 0x10: func_001EFFA0 and func_001F00F0 set 8 when there is no key or it is D_00275B04, clear it otherwise
};

struct ScreenFade {
    s32 f00;                // 0x00: func_001AD970, func_001EFFA0
    s32 mode;               // 0x04: func_001AD970, func_001EFCE8, func_001EFD10, func_001F0220, func_001F3C38
    f32 modeStartTime;      // 0x08: func_001EFD10, func_001F0220 (the clock when mode was set)
    union {
        f32 opacity;        // 0x0C: func_001EFD10, func_001EFEE0
        s32 opacityWord;    // 0x0C: func_001F0220
    };
    FadeRequest active;     // 0x10: func_001EFFA0 (args), func_001F00F0 (pair, flags)
    s32 style;              // 0x24: func_001EFEE0, func_001EFFA0 (its count), func_001F3C38; func_001F00F0 copies queuedStyle into it
    FadeRequest queued;     // 0x28: func_001F00C0, func_001F00F0 (spair, mid)
    s32 queuedStyle;        // 0x3C: func_001F00C0, func_001F00F0
};

typedef char check_FadeRequest[sizeof(FadeRequest) == 0x14 ? 1 : -1];
typedef char check_ScreenFade[sizeof(ScreenFade) == 0x40 ? 1 : -1];

extern ScreenFade g_screenFade;

#endif

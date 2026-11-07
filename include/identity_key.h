// SPDX-License-Identifier: AGPL-3.0-or-later
// A 32-byte key: eight words, of which two (the third and the seventh) identify it. Two keys
// are the same when they are one, or when both exist and (w[2] ^ w[6]) of each agree: the test
// func_001600A0 runs over D_00247AF0 and that Key_18F198::Same, Key_1F00F0::Same and
// SessionKey::Same inline. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g2307 and g4680).
//
// func_0018E410, func_0018F0E8 and func_0018F198 (movie_player.cpp) take one as a parameter;
// D_00248490 is one (global_tables.cpp defines it), D_00275B04 another (its label is 0x1C bytes: its
// readers stop at the seventh word), and every entry of D_00247AF0 begins with one (s1600a0.h).
// The same-key test stays with its views: their forms differ (SessionKey also tests this).
#ifndef IDENTITY_KEY_H
#define IDENTITY_KEY_H

#include "common.h"

struct IdentityKey {
    union {
        u32 words[8];           // 0x00: Key_18F198, Entry_247AF0 (u32)
        s32 signedWords[8];           // 0x00: Ent_18E410, Key_1F00F0, SessionKey, Ent_1600A0 (s32 words 2 and 6)
    };
};

typedef char check_IdentityKey[sizeof(IdentityKey) == 0x20 ? 1 : -1];

extern const IdentityKey D_00248490;    // global_tables.cpp
extern IdentityKey D_00275B04;      // file_1E88D0.cpp, file_1F2758.cpp, file_15F678.cpp (label of 0x1C bytes)

#endif

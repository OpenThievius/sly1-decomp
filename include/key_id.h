// SPDX-License-Identifier: AGPL-3.0-or-later
// Two words func_0018D410 clears (func_001F5C0C, 8 bytes), and which func_0012FD78 and
// func_001373B0 take as their second parameter: the identity of an IdentityKey (identity_key.h),
// words 0 ^ 5 and 1 ^ 7 of it (Pair_18CC20::Set and Pair_18F198::Set inline the filling).
// func_0018CC20, func_0018F198, func_001BE268 and func_001E4EA8 keep one on their stacks.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g1273).
#ifndef KEY_ID_H
#define KEY_ID_H

#include "common.h"

struct KeyId {
    union {
        s32 first;          // 0x00: func_0018CC20, func_001BE268 (s32)
        u32 k0;             // 0x00: func_0018F198 (u32)
        void* p0;           // 0x00: func_001373B0
    };
    union {
        s32 second;         // 0x04
        u32 k1;             // 0x04
    };
};

typedef char check_KeyId[sizeof(KeyId) == 8 ? 1 : -1];

#endif

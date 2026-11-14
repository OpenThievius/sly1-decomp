// SPDX-License-Identifier: AGPL-3.0-or-later
// The spr block record.
#ifndef SPR_BLOCK_H
#define SPR_BLOCK_H

#include "common.h"

struct SprTransfer {
    void* tags;             // 0x00
    s32 base;               // 0x04
    u32 addrs[8];           // 0x08: each block's scratchpad address
    s32 sizes[8];           // 0x28
    s32 count;              // 0x48
    s32 state;              // 0x4C: 2 while its parts are drawn
};
extern s32 g_sprTransferIndex;
extern SprTransfer g_sprTransfers[2];
struct SprBlock {
    static u32 Of(s32 n)
    {
        return g_sprTransfers[g_sprTransferIndex].addrs[n];
    }
};

#endif

// SPDX-License-Identifier: AGPL-3.0-or-later
// The spr block record.
#ifndef SPR_BLOCK_H
#define SPR_BLOCK_H

#include "common.h"
#include "spr_transfer.h"

extern s32 g_sprTransferIndex;
extern SprTransfer g_sprTransfers[2];
struct SprBlock {
    static u32 Of(s32 n)
    {
        return g_sprTransfers[g_sprTransferIndex].addrs[n];
    }
};

#endif

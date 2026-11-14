// SPDX-License-Identifier: AGPL-3.0-or-later
// One of the two scratchpad transfer buffers (D_002748F0; D_00274990 picks the current one):
// a chain of up to 8 blocks sent into the scratchpad by DMA and sent back to memory, as the
// object properties, the point graph and the world's listed objects use it.
#ifndef SPR_TRANSFER_H
#define SPR_TRANSFER_H

#include "common.h"

struct DmaTag;

struct SprTransfer {
    DmaTag* tags;           // 0x00: the chain's tags
    s32 base;               // 0x04: the scratchpad address of the first block's tag
    u32 addrs[8];           // 0x08: each block's address, after its 16-byte tag
    s32 sizes[8];           // 0x28: each block's size, rounded up to 16
    s32 count;              // 0x48: the number of blocks
    s32 state;              // 0x4C: 1 sent in, 3 sending back (StartFromSprChain), 2 while its parts or blocks are worked on, 0 done
};

#endif

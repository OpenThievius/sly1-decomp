// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 121/136 (89.0%), checked 2026-11-11
// NEAR: in its file, src/lib/mpeg_demultiplexer.cpp (Sony's 2.9-ee-991111). The unused entry
//       gives retail's 16-byte frame and the key's copy at the top. The code is now retail's
//       instruction for instruction; only the registers differ (regdiff: registers). The full
//       mask's case written first makes its compare the right leaf after the root's `>` test,
//       directly followed by its body: jump.c turns `if (mask != full) goto end; sh = 0;` into
//       a conditional move `sh = mask != full ? sh : 0`, which CSE folds to `(c ? 0 : 0)` but does
//       not delete as a no-op, so the set survives into the bnezl's slot and the third compare
//       disappears (docs/toolchain/cse.md). Left: the mask constant takes $a2 where retail has
//       $a0, and the chain follows (entry offset $a3 for $a2, key $t0 for $a3, %hi $t1 for $t0).
//       Mechanism: global-alloc's pass 0 skips $a0 for the mask because the key and sh, lower in
//       its order and conflicting with it, prefer $a0 (the key dies in the dsllv whose result
//       local-alloc put in $a0: set_preference); with $a0 to the mask, the rest falls out as
//       retail's. Tried: sh as u32/u8, a named mask, a pointer to the entry, the shift as its
//       own local, `r |=` after loading the entry, the operands of the or swapped, early returns,
//       r set in an else, the key copied into a local.
//       Written for this project from retail's code.
// w22 (2026-11-11): globalalloc.py --check agrees with the dumps. The mask (r129, pass 0, $a2) skips $a0 because r117 (key)
// and r119 (sh) conflict with it, are lower in the order and prefer $a0 (4 5); retail's mask takes $a0, so in retail the key
// and sh did not both carry the $a0 preference through the dsllv. No source form found for that; not retried blindly.
#include "common.h"

struct Pair_20A538 { u64 a; u64 b; };
extern Pair_20A538 g_streamIds[10];

u64 GetStreamId(u32 idx, u64 key)
{
    u64 r = 0;
    s32 sh = 0;
    if (idx < 10) {
        Pair_20A538 e;
        switch (g_streamIds[idx].b) {
        case 0xFFFFFFFFFFULL:
            sh = 0;
            break;
        case 0xFFFF000000ULL:
            sh = 24;
            break;
        case 0xFF00000000ULL:
            sh = 32;
            break;
        }
        r = g_streamIds[idx].a | (key << sh);
    }
    return r;
}

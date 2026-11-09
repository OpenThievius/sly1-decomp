// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 119/136 (87.5%), checked 2026-11-08
// NEAR: in its file, src/lib/mpeg_demultiplexer.cpp (Sony's 2.9-ee-991111). The unused entry
//       gives retail's 16-byte frame and the key's copy at the top; the three cases give its
//       compare tree. Left: the full mask's `sh = 0` is deleted (CSE knows sh is 0 there), where
//       retail keeps it and puts it in a bnezl's slot; the key is in $t1 (retail $a3), the
//       entry offset in $a3 ($a2), the first mask in $a2 ($a0). Tried: no initial sh and a
//       default, the full mask sharing the default, the entry copied into the local, idx as s32;
//       2026-11-09 (docs/TOOLCHAIN.md, "A switch case that repeats the variable's value"): every
//       case order and default placement, sh of every integer type (64-bit keeps the set but adds
//       a truncation), an inline returning the shift (value, pointer, reference), a GNU range for
//       the full mask (no third compare, but CSE still deletes the set), the result computed per
//       case, an early return. Mechanism: CSE follows `> mask` then `== full` from the top `sh = 0`
//       and deletes the case's set, then the compare; reorg's redundant_insn would drop it too.
//       Retail's bnezl keeps it, so its RTL had a different pattern, a label or an a1 set before
//       that test; the key's $a3 suggests the shift appeared on several paths (4+ key refs).
//       Written for this project from retail's code.
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
        case 0xFFFF000000ULL:
            sh = 24;
            break;
        case 0xFF00000000ULL:
            sh = 32;
            break;
        case 0xFFFFFFFFFFULL:
            sh = 0;
            break;
        }
        r = g_streamIds[idx].a | (key << sh);
    }
    return r;
}

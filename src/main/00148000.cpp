// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Glob_148178 {
    u8 pad0[0x19E0];
    s32 f19E0;
};

extern Glob_148178* D_002623C0;

void func_00148178(void)
{
    Glob_148178* g = D_002623C0;
    s32 r = 99;
    if (g->f19E0 + 1 <= 98) r = g->f19E0 + 1;
    g->f19E0 = r;
}

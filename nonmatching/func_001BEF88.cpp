// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER (212-byte candidate vs 188-byte retail); guard frame and linked-record walk stride differ.
#include "common.h"
extern s32 D_00275710;
extern s32 D_0027B314;
extern s32 D_00274734;
s32 func_00152720(void*, void*);
struct Guard_1BEF88 { s32* previous; s32* current; s32 value; };
void func_001BEF88()
{
    s32* cur = (s32*)((u8*)D_00275710 + 0x1BC4);
    Guard_1BEF88 g;
    g.previous = (s32*)D_0027B314;
    g.current = cur;
    g.value = cur[2];
    D_0027B314 = (s32)&g;
    if (func_00152720(cur, g.previous)) D_00274734 = 0;
    else {
        D_00274734 = -20;
        for (s32* p = cur; *p; p += *p / 4) {
            if (D_00274734 < *p) D_00274734 = *p;
        }
    }
    D_0027B314 = (s32)g.previous;
}

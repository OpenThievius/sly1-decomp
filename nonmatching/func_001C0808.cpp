// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER (188-byte candidate vs 164-byte retail); guard frame is 96 bytes vs retail 64, and loop layout differs.
#include "common.h"
extern s32 D_00275710, D_0027B314;
void func_001BF788(void*, void*);
void func_0011CE30();
struct Guard_C0808 { s32* prev; s32* cur; s32 step; };
void func_001C0808(void* item)
{
    if (D_00275710) {
        s32* cur = (s32*)((u8*)D_00275710 + 0x1bac);
        Guard_C0808 g; g.prev=(s32*)D_0027B314; g.cur=cur; g.step=cur[2];
        D_0027B314=(s32)&g;
        for (s32* p=cur; *p; p += *p/4) func_001BF788(p,item);
        D_0027B314=(s32)g.prev;
    }
    func_0011CE30();
}

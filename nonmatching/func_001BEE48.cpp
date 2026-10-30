// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: stack-chain setup/restore and prologue/frame sequence still differ from retail.
#include "common.h"
struct StackNode_1BEE48 { StackNode_1BEE48* next; };
struct Global_1BEE48 { u8 pad[0x1BC4]; s32 count; };
extern Global_1BEE48* D_00275710;
extern void* D_0027B314;
extern s32 D_002748EC;
extern s32 D_00274738;
extern s32 D_00274734;
void func_001BEDF8(void*);
void func_0011D928(s32);
void func_001BEE48(void)
{
    StackNode_1BEE48* node = (StackNode_1BEE48*)&D_00275710->count;
    StackNode_1BEE48* it = node;
    while (it->next) { func_001BEDF8(it->next); it = it->next; }
    func_0011D928(20);
    D_002748EC = 0;
    D_0027B314 = *(void**)0;
    D_00274738 = 0;
    D_00274734 = 0;
}

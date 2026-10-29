// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: step-based traversal and qualifying-index behavior are modeled, but frame spills and control/register scheduling differ.
#include "common.h"
extern void* D_0027B314;
s32 func_001300E8(void*, s32);
s32 func_0016A758(void* self)
{
    u8* list=(u8*)self+0x34;
    void* old=D_0027B314;
    D_0027B314=&old;
    u32 step=*(u32*)(list+8);
    u8* slot=list;
    void* node=*(void**)slot;
    s32 index=0;
    s32 best=0;
    while(node) {
        s32 nextIndex=index+1;
        if(func_001300E8(node,0x46)) {
            u32 value=(u32)(*(s32*)((u8*)node+0x550)-3);
            if(value>1) best=nextIndex;
        }
        index=nextIndex;
        slot+=step;
        node=*(void**)slot;
    }
    D_0027B314=old;
    return best;
}

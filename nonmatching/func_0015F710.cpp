// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 192/200, checked 2026-11-01
// NEAR: step-based list traversal and node updates are modeled, but frame, spills, register scheduling, and loop sequencing differ.
#include "common.h"
extern void* D_0027B314;
void func_00152600(void*, void*);
void func_0015F678(void*, void*);
struct List_15F710 { void* first; u32 unknown; u32 step; };
void func_0015F710(void* self, u8* base)
{
    List_15F710* list=(List_15F710*)(base+0x60);
    void* old=D_0027B314;
    D_0027B314=&old;
    u32 step=list->step;
    u8* slot=(u8*)list;
    void* node=*(void**)slot;
    while (node) {
        if (node != base) {
            func_00152600(list,node);
            *(void**)((u8*)node+0x54)=node;
            *(void**)((u8*)node+0x64)=node;
            *(void**)((u8*)node+0x60)=node;
        }
        func_0015F678(self,node);
        slot += step;
        node=*(void**)slot;
    }
    D_0027B314=old;
}

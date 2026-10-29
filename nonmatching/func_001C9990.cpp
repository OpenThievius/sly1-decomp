// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate frame and stack-built request object layout differ from retail.
#include "common.h"
typedef s32 (*Predicate_C9990)(void*, s32);
struct Quad_C9990 { s32 a,b,c,d; } __attribute__((aligned(16)));
struct Self_C9990 { void** vtbl; u8 pad[0x13c-4]; };
struct Input_C9990 { s32 code; void* data; };
void func_001F5C0C(void*, s32, s32);
s32 func_00177838(void*, s32, s32, Quad_C9990);
s32 func_001C9990(Self_C9990* s, Input_C9990* p)
{
    if (((Predicate_C9990)s->vtbl[0x13c/4])(s,p->code)) return 0;
    u8 buf[0x40]; func_001F5C0C(buf,0,0x40);
    s32 kind=4;
    if(p->code!=4) kind=p->data ? ((*(u32*)p->data & 0x20)?16:2):2;
    *(s32*)(buf+0)=p->code; *(void**)(buf+4)=s; *(s32*)(buf+16)=kind;
    Quad_C9990 q=*(Quad_C9990*)((u8*)s+0x140);
    return func_00177838(buf,0,0,q)!=0;
}

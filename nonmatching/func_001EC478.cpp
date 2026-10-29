// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate frame is 0x30 vs retail 0x40, and helper/state ordering differs.
#include "common.h"
void func_001C9008(void*); void func_001B6598(void*,void*); void func_001B64D8(void*,s32);
struct Self_EC478 { u8 pad[0x724]; s32 state; u8 pad2[0x52c]; s32 code; };
void func_001EC478(Self_EC478* s)
{ func_001C9008(s); if(s->state==14||s->state==16){s32 value=0; if(s->state==16){*(s32*)((u8*)s+0xc94)=0;func_001B6598(*(void**)((u8*)s+0xc54),&value);
 s32 event=value==0x4f1?0x4f2:value==0x4ee?0x4ef:value==0x4f4?0x4f5:-1; if(event!=-1)func_001B64D8(*(void**)((u8*)s+0xc54),event);}
 else *(s32*)((u8*)s+0xc94)=0; }}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate frame is 0x20 vs retail 0x30, and dispatch/helper argument setup differs.
#include "common.h"
extern u8 D_00275AF0[];
void func_001C05D0(s32,f32); void func_00140ED0(void*);
void func_001E4E80(void*,void*,s32,s32,s32);
void func_001E5278(s32 code)
{ s32 v=0; func_001C05D0(code,0.0f); if(code==1){func_00140ED0((void*)0x00261420);return;}
 if(code==0)v=2; else if(code==2)v=4; else if(code==3)v=2; else if(code==4)v=4;
 func_001E4E80(D_00275AF0,D_00275AF0+0x14,-1,-1,v); }

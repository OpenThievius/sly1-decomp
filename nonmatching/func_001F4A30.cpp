// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER (176-byte candidate vs 172-byte retail); initial instruction schedule and stack argument block differ.
#include "common.h"
extern s32 D_002623C8; extern u8 D_00275F80[];
s32 func_001601A0(s32); s32 func_00160850(s32); void func_001EFFA0(void*,void*);
struct Self_F4A30 { u8 pad[0x2fc]; s32 a; s32 b; s32 c; s32 d; u8 pad2[8]; s32 e; };
void func_001F4A30(Self_F4A30*s)
{ s32 on=0; if(s->c==1) on=(*(s32*)D_002623C8>>1)&1; else if(s->c==0) on=(func_00160850(func_001601A0(s->a))>>1)&1;
 s32 args[8]; args[0]=on? s->d:s->b; args[1]=on?s->e:s->a; args[2]=-1;args[3]=0;args[4]=s->e;func_001EFFA0(D_00275F80,args); }

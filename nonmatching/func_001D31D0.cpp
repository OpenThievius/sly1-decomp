// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; 0x450-byte frame matches, but compare operand order and pointer/field load register schedule differ.
#include "common.h"
extern f32 D_00261858[2];
s32 func_0015A4F0(void*,s32,s32,s32,s32,void*);
void func_0012F0A0(void*,s32,f32,f32);
struct Self_D31D0 { u8 pad[0x2758]; f32 value; s32 state; };
void func_001D31D0(Self_D31D0* s,s32 state)
{
 if(s->state!=state){ void* list[0x100]; s32 n=func_0015A4F0(*(void**)((u8*)s+0x14),0x105,8,0,0x100,list);
  for(s32 i=0;i<n;i++) if(*(s32*)((u8*)list[i]+0x7e0)) func_0012F0A0(list[i],1,0.0f,state?0.0f:1.0f);
  s->state=state; s->value=D_00261858[1]; }
}

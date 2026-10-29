// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; 0x40-byte frame matches, but branch layout and callback stack parameters differ.
#include "common.h"
extern s32 D_00275710; extern f32 D_0026185C;
void func_0013ECB0(void*,s32,void*,void*,s32); typedef void(*Method_EF900)(void*,s32,void*);
struct Self_EF900 { void** vtbl; u8 pad[0x2d0-4]; s32 state; u32 p2e4; u8 pad2[0x2e8-0x2e8]; };
void func_001EF900(Self_EF900*s,s32 state)
{ s32 old=s->state; if(old==state)return; if(state==2)func_0013ECB0((u8*)D_00275710, s->p2e4,(u8*)s+0x2e8,s,1); else if(state==0&&old==2)func_0013ECB0((u8*)D_00275710,s->p2e4,(u8*)s+0x2e8,s,0);
 s->state=state; *(f32*)((u8*)s+0x2d4)=D_0026185C; ((Method_EF900)s->vtbl[0x48/4])(s,0x16,&old); }

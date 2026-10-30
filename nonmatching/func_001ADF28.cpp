// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; frame and early calls match, but the indirect float callback and subsequent state/global updates differ in register and instruction scheduling.
#include "common.h"
extern f32 D_0027446C,D_00274470;
extern s32 D_00262C84,D_00269988;
void func_001AA268(void*); s32 func_0015C1C0(s32); void func_001ADFF0(void*);
typedef s32(*Method_ADF28)(void*,f32,f32);
struct Self_ADF28 { u8 pad[4]; void* object; u8 gap[0x20c]; void* pointer; s32 state; s32 enabled; s32 result; };
void func_001ADF28(Self_ADF28* self)
{
 func_001AA268(self); void* obj=self->object; s16 off=*(s16*)((u8*)*(void**)((u8*)obj+0x4c)+8);
 void** vt=*(void***)((u8*)obj+0x4c); self->object=(void*)((Method_ADF28)vt[3])((u8*)obj+off,D_0027446C,D_00274470);
 if(func_0015C1C0(2)){ self->pointer=(void*)0x00274488; *(s32*)self->pointer=func_0015C1C0(2); }
 self->result=0; self->enabled=(D_00262C84==3);
 self->result=D_00269988 && *(f32*)((u8*)D_00269988+0xc)==0.0f;
 func_001ADFF0(self);
}

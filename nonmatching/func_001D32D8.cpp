// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; 0x30-byte frame matches, but control flow and mixed float argument setup differ.
#include "common.h"
typedef void (*Method_D32D8)(void*,s32,void*);
struct Self_D32D8 { void** vtbl; u8 pad[0x550-4]; s32 count; u8 pad2[4]; void* resource; };
void func_00158730(void*); void func_001BFCD8(s32,s32,s32,void*,f32,f32,f32,f32,f32);
void func_001837E0(void*,s32,s32,void*);
void func_001D32D8(Self_D32D8* s,s32 value,s32 skip)
{ if(!skip){s32 result=0; ((Method_D32D8)s->vtbl[0x48/4])(s,0x17,&result); if(--s->count>0)return;}
 func_00158730(s->resource); func_001BFCD8(0x67,0,0,(u8*)s+0x140,0.0f,1000.0f,1.0f,0.0f,0.0f); func_001837E0(s,2,0,0); ((void(*)(void*))s->vtbl[7])(s); }

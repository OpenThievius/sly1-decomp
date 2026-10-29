// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate frame is 0x40 vs retail 0x30, and helper argument setup plus source/destination register allocation differ.
#include "common.h"
s32 func_001EE5C8(void*,void*,s32,s32,void*,void*);
void func_001EE668(void* dst,void* arg1,s32 a2,void* src,s32 count)
{
 s32 words=func_001EE5C8(dst,arg1,a2,count,&count,(u8*)&count+4);
 s32 prefix=(words+3)/4*4;
 for(s32 i=0;i<prefix;i++) ((s32*)dst)[i]=((s32*)src)[i];
}

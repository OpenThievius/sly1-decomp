// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: descriptor creation and cursor update are modeled, but packed field/register scheduling and frame layout differ.
#include "common.h"
struct V_1612F8 { u8 pad[8]; s16 offset; u8 padA[2]; u32 fn; };
struct O_1612F8 { u8 pad[0x0c]; u32 cursor; u8 pad10[8]; };
s32 func_001612F8(O_1612F8* self, s32 a, s32 b, s32 c, u64 d, s32 e) {
 V_1612F8* v=(V_1612F8*)*(void**)((u8*)self+0x18); ((void(*)(void*,s32))v->fn)((u8*)self+v->offset,0);
 u8* p=(u8*)self->cursor; u32 next=(u32)p+16; u64 x=((u64)(u32)c<<60)|((u64)0x80000000<<32)|((u64)(u32)e<<47)|((u32)b);
 *(u32*)((u8*)self+0x0c)=next; *(u64*)p=d; *(u64*)(p+8)=x; if(e) *(u32*)e=next; self->cursor=next+((u32)c*(u32)e<<4); return self->cursor;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: descriptor creation and object updates are modeled, but argument-register assignment, operation order, and code size differ.
#include "common.h"
struct O_1613C0 { u8 pad[0x0C]; u32 cursor; u8 pad10[8]; s32 offset; u32 block; s32 type; s32 zero; };
struct V_1613C0 { u8 pad[8]; s16 offset; u8 padA[2]; u32 fn; };
void func_001613C0(O_1613C0* self, s32 a, s32 b, s32 c);
void func_001613C0(O_1613C0* self, s32 a, s32 b, s32 c) {
 V_1613C0* v=(V_1613C0*)*(void**)((u8*)self+0x18); ((void(*)(void*,s32))v->fn)((u8*)self+v->offset,0);
 u32 p=self->cursor; u64 x=((u64)(u32)b<<60)|((u64)0x80000000<<32)|((u64)(u32)a<<47);
 *(u32*)((u8*)self+0x0c)=p+16; *(u64*)p=x; *(u64*)(p+8)=(u32)c; self->type=b; self->block=p; self->zero=0;
}

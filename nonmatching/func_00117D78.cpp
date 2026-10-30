// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the output pointer is now passed in the call delay slot; the two remaining argument moves are reversed around func_00117AF0.
#include "common.h"
extern u8* D_00275710;
struct Quad_117D78 { s32 w[4]; };
struct Source_117D78 { u8 pad0[4]; s32 b; u8 pad8[4]; s32 c; };
void func_0011B008(void*);
void func_0011B0A8(void*,void*);
void func_0011B060(void*,s32);
void func_0011B018(void*,void*);
s32 func_0015A198(void*,s32,s32,s32,s32,void*);
void func_00117AF0(Quad_117D78*,s32,s32);
void* func_00117D78(void* self,void*,Source_117D78* src)
{
    Quad_117D78 q;
    u8 input[0x100];
    u8 output[0x10];
    func_0011B008(&q);
    s32 n=func_0015A198(D_00275710,0x104,src->b,src->c,0x40,input);
    func_00117AF0((Quad_117D78*)output,n,(s32)(u32)input);
    func_0011B0A8(&q,output);
    func_0011B060(output,2);
    func_0011B018(self,&q);
    func_0011B060(&q,2);
    return self;
}

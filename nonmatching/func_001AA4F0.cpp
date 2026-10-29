// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: candidate frame is 0x120 versus retail 0xF0, with differing saved-register allocation and call sequence.
#include "common.h"
struct Obj_1AA4F0 { u8 pad[8]; void* data; u8 pad0C[0x200]; f32 scale; };
s32 func_001E2100(void*);
void func_001E2138(void*, void*);
void func_0015C8B8(void*, f32, f32);
void func_0015DB28(void*, void*);
void func_0015E290(void*, f32, f32*);
void func_001AAB20(void*, f32, f32);
void func_0015C900(void*);
void func_001AA4F0(Obj_1AA4F0* self, void* arg)
{
    void* data = (u8*)self + 8;
    if (arg && func_001E2100(arg)) { func_001E2138(data,arg); }
    else self->data = 0;
    func_0015C8B8(*(void**)((u8*)self + 4), self->scale, self->scale);
    u8 tmp[0xB8];
    func_0015DB28(tmp,data);
    f32 x=0,y=0;
    func_0015E290(tmp,0,&x);
    func_001AAB20(self,x,y);
    func_0015C900(*(void**)((u8*)self+4));
}

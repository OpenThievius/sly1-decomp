// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: retail passes a 0x20 stack field and its following word to
// func_001C23B0, then consumes the output word. Modelling that helper call as
// a simple wrapper does not reproduce retail's 0x70 frame and call sequence.
#include "common.h"

struct Quad_101C88 { s32 a, b, c, d; };
void func_0011B008(Quad_101C88* q);
void func_0011B018(void* out, Quad_101C88* q);
void func_0011B060(Quad_101C88* q, int mode);
void func_0011B0A8(Quad_101C88* a, Quad_101C88* b);
void func_001C23B0(Quad_101C88* t, int mode, int c, s32* size, s32* value);
void* func_0012CCC0(void* object, s32 value);
void* func_0011B5B0(void* object, f32 value);

void* func_00101C88(void* out, void* object, int unused, int c)
{
    Quad_101C88 q, t;
    s32 size = 6, value;
    func_0011B008(&q);
    func_001C23B0(&t,1,c,&size,&value);
    func_0011B0A8(&q,&t); func_0011B060(&t,2);
    f32 result=(f32)(s32)func_0012CCC0(object,value);
    func_0011B5B0(&q,result);
    func_0011B018(out,&q); func_0011B060(&q,2); return out;
}

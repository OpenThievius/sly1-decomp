// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The callback is close; instruction scheduling around the result store
//        and global flag still differs.
#include "common.h"

extern void* volatile D_00269990;
extern s32 D_00275960;
extern void func_001F6B60(void*);
extern void func_001F6B40(void*);
extern void func_001F6A30(void);

struct State_0018B600 { s32 first; s32 state; s32 (*callback)(void*); s32 argument; s32 result; };

void func_0018B600(void)
{
    State_0018B600* self = (State_0018B600*)&D_00269990;
    func_001F6B60(D_00269990);
    s32 result = self->callback((void*)self->argument);
    volatile s32* flag = &D_00275960;
    self->result = result;
    *flag = -1;
    self->state = -1;
    self->argument = 0;
    self->callback = 0;
    func_001F6B40(D_00269990);
    func_001F6A30();
}

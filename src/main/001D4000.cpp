// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_D5418)(void* self);
struct Obj_D5418 {
    VFn_D5418* vtbl;
};

s32 func_00160C58(void* a);
void func_00175170(void* a, s32 b, s32 c);

void func_001D5418(Obj_D5418* a0)
{
    if (func_00160C58(a0)) {
        a0->vtbl[84](a0);
    } else {
        func_00175170(a0, 4, 0x2D);
    }
}

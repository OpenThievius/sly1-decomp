// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_00208FE8 { u8 pad[8]; s64 f8; };
typedef s64 Key_00208FE8;
s32 func_001FD308(Key_00208FE8 a, Key_00208FE8 b);

s32 func_00208FE8(Obj_00208FE8* obj)
{
    Key_00208FE8 v = obj->f8;
    (void)func_001FD308(v, v);
    return 0;
}

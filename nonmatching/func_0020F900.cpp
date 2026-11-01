// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 200/196, checked 2026-11-01
// NEAR: field updates and helper calls are modeled, but argument setup, branch register, and saved-register opcodes differ from retail.
// NEAR: the field updates and helper calls are modeled. GCC emits one extra argument setup before the tail call, uses a different unsigned-branch register, and saves registers with sq/lq instead of sd/ld (three attempts).
#include "common.h"

struct Object_20F900 { u8 pad00[0x150]; s32 type; s32 next; s32 aux; s32 aux2; s32 aux3; };
extern s32 func_0020F5B8(Object_20F900*, s32);
extern void func_0020FCE0(Object_20F900*);
extern void func_0020F9C8(Object_20F900*);
extern s32 func_0020FD28(Object_20F900*, s32);

s32 func_0020F900(Object_20F900* self)
{
    s32 value = func_0020F5B8(self, 10);
    self->type = func_0020F5B8(self, 3);
    func_0020F5B8(self, 16);
    if ((u32)(self->type - 2) < 2) {
        self->next = func_0020F5B8(self, 1);
        self->aux = func_0020F5B8(self, 3);
    }
    if (self->type == 3) {
        self->aux2 = func_0020F5B8(self, 1);
        self->aux3 = func_0020F5B8(self, 3);
    }
    func_0020FCE0(self);
    func_0020F9C8(self);
    return func_0020FD28(self, value);
}

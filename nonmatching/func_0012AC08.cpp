// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the subobject offsets and helper calls are understood, but this
// attempt's modeled subobject arguments produce the wrong ABI registers and
// an oversized frame compared with retail.
#include "common.h"

struct Owner_12AC08 { u8 pad[0x2AC]; void* sub; };
void func_0012ABA8(Owner_12AC08* self);
void func_001BF788(s32 value, s32 unused);
void func_001BFCD8(s32 type, void* data, void* a2, s32 a3, f32 f12, f32 f13,
                   f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_0012AC08(Owner_12AC08* self, void* value)
{
    func_0012ABA8(self);
    struct Sub { s32 field0; f32 f4, f8, fC, f10; u8 pad[4]; f32 f20; s32 field24; u8 pad2[4]; f32 f2C; };
    Sub* sub = (Sub*)self->sub;
    func_001BF788(sub->field0, 0);
    sub->field0 = (s32)value;
    func_001BFCD8(sub->field0, self, self, 0, sub->f4, sub->f8, sub->fC, sub->f10, sub->f20, 0, 0);
}

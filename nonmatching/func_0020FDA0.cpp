// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: retail uses 64-bit saves, schedules two field stores around calls,
// and tail-jumps to func_0020F9C8; this C emits a call and full epilogue.
#include "common.h"

struct Obj_20FDA0 {
    u8 pad0[0x84C];
    s32 sequence;
    s32 f850;
    s32 f854;
};
s32 func_0020F5B8(Obj_20FDA0* self, s32 value);
s32 func_0020F9C8(Obj_20FDA0* self);

s32 func_0020FDA0(Obj_20FDA0* self)
{
    *(s32*)((u8*)self + 0xE8) = 0;
    self->f854 = 1;
    self->sequence = self->f850 + 1;
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 5);
    func_0020F5B8(self, 6);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 6);
    func_0020F5B8(self, 6);
    func_0020F5B8(self, 1);
    *(s32*)((u8*)self + 0x1A4) = func_0020F5B8(self, 1);
    *(s32*)((u8*)self + 0x1A8) = func_0020F5B8(self, 1);
    return func_0020F9C8(self);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the float counter and callback loop are modeled. A 0x50-byte
// local scratch block reproduces retail's 0x90 frame, but shifts saved-register
// slots and leaves callback register allocation different.
#include "common.h"

struct Obj_1A3A18 { void** vtbl; u8 pad0[0x120 - sizeof(void*)]; s32 target; f32 step; f32 progress; };
void func_0019F560(void* self);
void func_001A3A18(Obj_1A3A18* self, f32 amount)
{
    struct Frame { u8 pad[0x20]; u64 payload[2]; u8 scratch[0x30]; };
    func_0019F560(self);
    if (self->target == 0) return;
    self->progress = self->progress + amount * self->step;
    if (self->progress < 1.0f) return;
    s32 count = 4;
    Frame frame;
    do {
        typedef void (*Callback)(void*, Frame*);
        ((Callback)self->vtbl[31])(self, &frame);
        self->progress = self->progress - 1.0f;
    } while (self->progress >= 1.0f);
    (void)count;
}

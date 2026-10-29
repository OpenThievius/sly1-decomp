// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: vtable slots 6 and 11 are identified, but the callback's mixed
// float/integer argument ABI was modeled incorrectly and produces a 16-byte
// oversized frame. The parameter mapping needs further work.
#include "common.h"

struct Obj_14ED98 { void** vtbl; };
s32 func_0014ED98(Obj_14ED98* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    typedef void (*Setup)(void* self);
    typedef s32 (*Callback)(void* self, s32 a1, f32 value, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
    ((Setup)self->vtbl[6])(self);
    Callback callback = (Callback)self->vtbl[11];
    if (callback) return callback(self, a1, 0.0f, a2, a3, a4, a5, a6, a7);
    return 0;
}

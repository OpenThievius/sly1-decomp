// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The frame and call arguments are close, but register-save order and
//        the float constant base register differ.
#include "common.h"

extern f32 D_002649C4;
s32 func_0018D608(void*);
s32 func_001DC238(s32, s32, void*, void*, void*, void*, s32*, s32*);
s32 func_0018A6C0(s32, void*, void*, f32, s32, s32, void*);
s32 func_0018D6F0(void);
extern void func_0018A830(void);

struct State_0018A910 { u8 pad[0x14]; s32 handle; };

s32 func_0018A910(State_0018A910* state, void* a, void* b)
{
    u8 scratch[0x78];
    func_0018D608(state);
    func_001DC238(state->handle, 0, a, b, (void*)func_0018A830, state,
                  (s32*)(scratch + 0x70), (s32*)(scratch + 0x74));
    s32 result = func_0018A6C0(0, a, b, D_002649C4, *(s32*)(scratch + 0x70),
                               *(s32*)(scratch + 0x74), scratch);
    func_0018D6F0();
    return result != 0;
}

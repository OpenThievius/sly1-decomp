// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 172/176, checked 2026-11-01
// NEAR: request setup and completion callback are modeled, but result reload order and saved-register opcodes differ from retail.
// NEAR: the request setup and completion callback are modeled. After the callback GCC reloads the result directly into v0 instead of retail loading v1 then moving it; saved-register opcodes also differ.
#include "common.h"

struct Request_204C38 { s32 count; s32 owner; s32 channel; s32 data; s32 state; };
extern Request_204C38 D_0062ACC0;
extern u8 D_0062AA80[];
extern s32 func_001F8290(void*, s32, s32, void*, s32, void*, s32, s32, s32);
extern s32 func_00204610(s32, s32, s32);

s32 func_00204C38(s32 owner, s32 channel, s32 data)
{
    Request_204C38* request = &D_0062ACC0;
    request->data = data;
    request->count = 10;
    request->owner = owner;
    request->channel = channel;
    s32 status = func_001F8290(D_0062AA80, 1, 0, request, 0x80, request, 0x80, 0, 0);
    if (status < 0)
        return 0;
    s32 state = request->state;
    if (state != 1)
        return state;
    func_00204610(owner, channel, 2);
    return request->state;
}

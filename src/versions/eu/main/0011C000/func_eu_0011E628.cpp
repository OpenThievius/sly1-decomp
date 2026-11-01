// SPDX-License-Identifier: AGPL-3.0-or-later
// Sends the message 0x5B with no data through func_0011D968 (PAL address 0011D9D8).
s32 func_0011D968(s32 id, s32 size, void* data);

void func_eu_0011E628(void)
{
    func_0011D968(0x5B, 0, 0);
}

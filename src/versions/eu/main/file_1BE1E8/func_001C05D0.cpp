// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the first argument of func_0011D480 is 16 (US 8).
void SetIopVolumeChannel8(f32 x)
{
    SetIopVolumeChannel(16, (s32)(x * 1024.0f));
}

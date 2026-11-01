// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two fields are at 0x570 and 0x574 (US 0x260, 0x264).
struct Obj_E7440_eu { u8 pad[0x570]; s32 f570; f32 f574; };

void func_001E7440(Obj_E7440_eu* a0, s32 a1)
{
    if (a1 != a0->f570) {
        a0->f570 = a1;
        a0->f574 = D_00261868;
    }
}

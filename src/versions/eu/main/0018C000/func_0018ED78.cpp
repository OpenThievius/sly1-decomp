// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: also calls func_0018EB98 on the block at a2 + 0x80
void func_0018EB98(void* p);
s32 func_0018ED78(void* a0, s32 a1, void* a2)
{
    func_0018F890(a2, 0);
    func_0018EB98((u8*)a2 + 0x80);
    return 1;
}

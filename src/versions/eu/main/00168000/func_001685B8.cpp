// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_00201A18 is called with 3 where US passes 2.

void func_001685B8(void)
{
    D_002BE470 = 1;
    func_00168AF8();
    func_001683B8();
    D_002BE470 = 0;
    func_00201A18(0, 1, 3, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = D_002626C0;
    D_002626CC = 0;
    D_00262484 = 0;
    D_002626C8 = flag;
    D_002626C4 = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    func_00202098(ptr, 0x800, 0x800, half);
    func_001F6C20(0);
    D_002626C0 = D_002626C0 + 1;
    func_00201FF8(D_00262490, D_002626C0);
}


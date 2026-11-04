// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: initialises the IOP command buffers and RPC channels; takes a flags word (bit 1 sets D_eu_0025D6B8) that is passed on to the IOP.
extern s32 D_eu_0025D6B8;

void func_0011CBB8(s32 flags)
{
    s32 n;
    s32 args[2];

    D_0025C360[0] = (s32*)D_0025C540;
    D_0025C360[1] = (s32*)D_0025D540;
    D_0025C378[0] = D_00260540;
    D_0025C378[1] = D_00260980;
    ((s32**)&D_0025C370)[0] = D_0025E540;
    ((s32**)&D_0025C370)[1] = D_0025F540;
    if (flags & 2) {
        D_eu_0025D6B8 = 1;
    } else {
        D_eu_0025D6B8 = 0;
    }
    func_001F7BE8(0);
    do {
        ASSERT_0011CBB8(func_001F80C0((Rpc_0011CBB8*)D_0027B4C8, 0x123456, 0) >= 0, 0xAF);
        for (n = 10000; --n != -1;) {
        }
    } while (((Rpc_0011CBB8*)D_0027B4C8)->f24 == 0);
    D_0025C388.busy = 0;
    D_0025C390.fn = 0;
    D_0025C390.arg = 0;
    D_00260E00.result = 0;
    do {
        ASSERT_0011CBB8(func_001F80C0((Rpc_0011CBB8*)D_0027B4F0, 0x123457, 0) >= 0, 0xC4);
        for (n = 10000; --n != -1;) {
        }
    } while (((Rpc_0011CBB8*)D_0027B4F0)->f24 == 0);
    D_00260DC0.f00 = 0;
    D_0025C540[0] = 0;
    D_0025D540[0] = 0;
    D_0025C368[0] = 0xFFC;
    D_0025C368[1] = 0xFFC;
    D_00260DC0.f10 = 0;
    args[0] = (s32)&D_00260DC0;
    args[1] = flags;
    func_0011D968(0, 8, args);
}

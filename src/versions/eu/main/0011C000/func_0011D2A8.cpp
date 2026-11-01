// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: each debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

void func_0011D2A8(void* a0, s32 a1, s32 a2, s64 a3)
{
    D_0025C348 = 0;
    if (D_0025C388 != 0) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((Ctx_0011D2A8*)D_00249570);
        }
        return;
    }
    if (func_0011E1F8(1) == 1) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((Ctx_0011D2A8*)D_002495A0);
        }
        return;
    }
    (*(u32*)&D_00260E00) = 0xFFFFFFFF;
    (*(Pair_11D2A8*)&D_00260E40).a = (s32)a0;
    (*(Pair_11D2A8*)&D_00260E40).b = a1;
    (*(Args_11D2A8*)&D_0025C390).a = a2;
    (*(Args_11D2A8*)&D_0025C390).c = a3;
    while (func_001F8480((Ctx_0011D2A8*)D_0027B4F0)) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((Ctx_0011D2A8*)D_002494E8);
        }
        func_0011CE30();
        func_001F6C20(0);
    }
    D_0025C388 = 1;
    func_001F8290((Ctx_0011D2A8*)D_0027B4F0, 3, 1, ((Pair_11D2A8*)&D_00260E40), 8, ((u32*)&D_00260E00), 4, 0, 0);
}

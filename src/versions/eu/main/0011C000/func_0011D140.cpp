// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: each debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

s32 func_0011D140(s32 a0, s32 a1)
{
    s32 v;
    s32 w;
    s32 v1;
    u32 m;

    D_0025C348 = 0;
    if (D_0025C388 != 0) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((struct Ptr_11D140 *)D_00249570);
        }
        return 0;
    }
    v = func_0011E1F8(1);
    if (v == 1) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((struct Ptr_11D140 *)D_002495A0);
        }
        return 0;
    }
    s32* p = &D_00260E00;
    m = 0xFFFFFFFFu;
    *p = (s32)m;
    D_00260E40[1] = a1;
    D_00260E40[0] = a0;
    while (func_001F8480((struct Ptr_11D140 *)D_0027B4F0)) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((struct Ptr_11D140 *)D_002494E8);
        }
        func_0011CE30();
        func_001F6C20(0);
    }
    w = func_001F8290((struct Ptr_11D140 *)D_0027B4F0, 3, 1, D_00260E40, 8, &D_00260E00, 4, 0, 0);
    v1 = D_00260E00;
    if (w < 0) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((struct Ptr_11D140 *)D_002495C0);
        }
        D_0025C348 = 0x106;
        return 0;
    }
    if ((u32)v1 == 0xFFFFFFFFu) {
        do {
            func_001F6C20(0);
        } while ((u32)D_00260E00 == 0xFFFFFFFFu);
    }
    return D_00260E00;
}

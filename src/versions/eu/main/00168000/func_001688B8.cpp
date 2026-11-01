// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_00201A18 is called with 3 (US 2) and func_00201D60 with 0x100 (US 0xE0).

void func_001688B8(void)
{
    Quad_1688B8 k;
    Quad_1688B8 t;

    func_00201A18(0, 1, 3, 1);
    u8* s0 = D_00262490;
    func_00201D60(s0, 0, 0x280, 0x100, 3, 0x30, 0);
    u8* p = s0;
    s32 end = (s32)s0 + 0x50;
    do {
        *(s32*)p &= -2;
        p[1] = 0x80;
        *(s32*)p |= 0x20;
        p += 0x28;
    } while ((s32)p < end);
    k.b0 = 0;
    k.b1 = 0;
    k.b2 = 0;
    k.b3 = 0x80;
    t = k;
    func_00168770(D_002BDC20, &t, 0);
    t = k;
    func_00168770(D_002BE1A0, &t, 0);
    t = k;
    func_00168770(D_002BDEE0, &t, 1);
    D_002BE460 = func_001E2268((void*)0, (void*)1);
    D_002BE464 = func_001E2268((void*)0, (void*)1);
    func_001F6950(2, func_001682C0, 0);
    func_001F6DA8(2);
    func_001F6950(0, func_00168698, 0);
    func_001F6DA8(0);
    func_00168D00();
    func_001685B8();
}


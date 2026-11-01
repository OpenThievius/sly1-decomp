// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL prints the RPC collision message only while a PAL-only flag is clear.
extern s32 D_eu_0025D6B8;

s32 func_0011D968(s32 id, s32 size, u8* data)
{
    s32 i;
    s32 r;
    for (i = 0; i < size; i++)
        D_0025C400[i] = data[i];
    while ((s32)D_0025C340) {
        func_0011CE30();
        func_001F6C20(0);
    }
    func_0011D110(&D_0025C3C0, 1);
    while (func_001F8480(D_0027B4C8)) {
        if (D_eu_0025D6B8 == 0)
            func_001E1F10(D_002494E8);
        func_0011CE30();
        func_001F6C20(0);
    }
    if (size)
        func_001F8290(D_0027B4C8, id, 1, D_0025C400, size, &D_0025C3C0, 0xC, 0, 0);
    else
        func_001F8290(D_0027B4C8, id, 1, 0, 0, &D_0025C3C0, 0xC, 0, 0);
    while (!func_0011D078()) {
    }
    r = D_0025C3C0.result;
    if (*D_0025C360[D_0025C380] != 0 && D_0025C384 == 0)
        func_0011DE18();
    return r;
}

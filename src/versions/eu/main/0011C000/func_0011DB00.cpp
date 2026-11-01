// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the three debug messages are only printed while a global (US 0x25C3B8) is zero
extern s32 D_0025C3B8;

void func_0011DB00(s32 cmd, s32 len, u8* data, s32 arg, u64 val)
{
    s32 flag = 0;
    s32 i;

    if (D_0025C384 == 0 && D_0025C340 == 0 && len == 0 && arg == 0) {
        func_0011D110((&D_0025C3C0), 1);
        while (func_001F8480(D_0027B4C8) != 0) {
            if (D_0025C3B8 == 0)
                func_001E1F10("989snd.c: RPC collision!\n");
            func_0011CE30();
            func_001F6C20(0);
        }
        func_001F8290(D_0027B4C8, cmd, 1, 0, 0, (&D_0025C3C0), 12, 0, 0);
        return;
    }

    s32 size = len + 4;
    i = 0;
    if ((size & 3) != 0)
    {
        s32 t = len + 8;
        size = t - size % 4;
    }

    for (;; i++) {
        if (*D_0025C360[D_0025C380] != 0x100 && D_0025C368[D_0025C380] >= size)
            break;
        if (D_0025C384 != 0) {
            D_0025C384 = 0;
            flag = 1;
        }
        func_0011CE30();
        if (i == 1 && D_0025C3B8 == 0)
            func_001E1F10("snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP comands to finish!\n", D_0025C380, *D_0025C360[D_0025C380]);
    }
    if (i != 0 && D_0025C3B8 == 0)
        func_001E1F10("snd_SendIOPCommandNoWait: continuing (%d).\n", i);
    if (flag != 0)
        D_0025C384 = 1;

    {
        s16* p = (s16*)(((u8*)D_0025C360[D_0025C380]) - (D_0025C368[D_0025C380] - 0x1000));
        s32 j;
        *p = cmd;
        p++;
        *p = len;
        p++;
        for (j = 0; j < len; j++)
            ((u8*)p)[j] = data[j];
    }
    {
        s32 k = D_0025C380;
        D_0025C368[k] -= size;
        *(s32*)(((u8**)&D_0025C370)[k] + *D_0025C360[k] * 16) = arg;
        *(u64*)(((u8**)&D_0025C370)[k] + *D_0025C360[k] * 16 + 8) = val;
    }
    func_0011DDD8();
}

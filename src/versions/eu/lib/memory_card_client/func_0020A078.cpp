// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with func_eu_001F7738, a function only PAL has, where US calls func_00201720
s32 func_eu_001F7738(s8* dst, s8* src, s32 n);

s32 RequestCardSpaceForPath(s32 a0, s32 a1, s8* a2)
{
    Reg_0020A078* reg;
    Buf_0020A078* buf;
    Buf_0020A078* res;

    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    reg = ((Reg_0020A078*)&g_cardClient);
    if (reg->f24 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    buf = ((Buf_0020A078*)&D_0062ADF0);
    buf->f0 = a0;
    buf->f4 = a1;
    func_eu_001F7738(buf->text14, a2, 0x3FF);
    buf->text14[0x3FF] = 0;
    res = CallRemoteService(reg, 0x12, 1, buf, 0x414, ((u32*)&D_0062C300), 4, 0, 0);
    if (res == 0) {
        g_cardRequestInFlight = 0x12;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return (s32)res;
}

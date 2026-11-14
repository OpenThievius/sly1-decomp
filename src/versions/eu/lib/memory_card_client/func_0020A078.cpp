// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
void* CopyStringBounded(s8* dst, const char* src, s32 n);

s32 RequestCardSpaceForPath(s32 a0, s32 a1, const char* a2)
{
    RemoteCallClient* reg;
    CardPathRequest* buf;
    s32 res;

    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    reg = ((RemoteCallClient*)&g_cardClient);
    if (reg->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    buf = ((CardPathRequest*)&D_0062ADF0);
    buf->f0 = a0;
    buf->f4 = a1;
    CopyStringBounded(buf->text14, a2, 0x3FF);
    buf->text14[0x3FF] = 0;
    res = CallRemoteService(reg, 0x12, 1, buf, 0x414, ((u32*)&D_0062C300), 4, 0, 0);
    if (res == 0) {
        g_cardRequestInFlight = 0x12;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return res;
}

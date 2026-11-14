// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
s32 RequestCardSpaceForPath(s32 a0, s32 a1, const char* a2)
{
    RemoteCallClient* reg;
    CardNameRequest* buf;
    s32 res;

    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    reg = &g_cardClient;
    if (reg->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    buf = &g_cardPathRequestBuffer;
    buf->port = a0;
    buf->slot = a1;
    CopyStringBounded(buf->name, a2, 0x3FF);
    buf->name[0x3FF] = 0;
    res = CallRemoteService(reg, 0x12, 1, buf, 0x414, &g_cardReplyBuffer, 4, 0, 0);
    if (res == 0) {
        g_cardRequestInFlight = 0x12;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return res;
}

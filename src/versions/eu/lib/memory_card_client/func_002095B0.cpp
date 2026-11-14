// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
s32 OpenCardFile(s32 a0, s32 a1, const char* a2, s32 a3)
{
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    RemoteCallClient* pool = &g_cardClient;
    if (pool->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    // The name is addressed first and the request through it: the original's pointer was the
    // name's, and the words before it the request's.
    char* name = g_cardPathRequestBuffer.name;
    CopyStringBounded(name, a2, 0x3FF);
    ((s32*)name)[-5] = a0;
    CardNameRequest* r = (CardNameRequest*)(name - 0x14);
    r->f08 = a3;
    r->slot = a1;
    r->name[0x3FF] = 0;
    s32 result = CallRemoteService(pool, 2, 1, r, 0x414, &g_cardReplyBuffer, 4, 0, 0);
    if (result == 0) {
        g_cardRequestInFlight = 2;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return result;
}

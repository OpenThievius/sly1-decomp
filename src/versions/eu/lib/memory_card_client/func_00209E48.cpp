// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
s32 ReadCardDirectory(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, void* a5)
{
    s32 status = TrySemaphore(g_cardSemaphore);
    if (status < 0) {
        return -200;
    }
    RemoteCallClient* mgr = &g_cardClient;
    if (g_cardClient.server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (name == 0 || *name == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    CardNameRequest* rec = &D_0062ADF0;
    rec->port = a0;
    rec->slot = a1;
    rec->f08 = a3;
    rec->entryCount = a4;
    rec->entries = (s32)a5;
    CopyStringBounded(rec->name, name, 0x3FF);
    rec->name[0x3FF] = 0;
    if (a4 >= 0) {
        WriteBackDataCacheRange(a5, a4 << 6);
    }
    s32 r = CallRemoteService(mgr, 0xD, 1, rec, 0x414, &D_0062C300, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 0xD;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return r;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL copies the name with its own copy of CopyStringBounded (func_001F7738, the same bytes), placed elsewhere
void* CopyStringBounded(u8* dst, const char* src, s32 max);

s32 ReadCardDirectory(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, void* a5)
{
    s32 status = TrySemaphore(g_cardSemaphore);
    if (status < 0) {
        return -200;
    }
    Mgr_9E48* mgr = (Mgr_9E48*)g_cardClient;
    if (*(s32*)(g_cardClient + 0x24) == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (name == 0 || *name == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    Rec_9E48* rec = (Rec_9E48*)g_cardPathRequestBuffer;
    rec->f0 = a0;
    rec->f4 = a1;
    rec->f8 = a3;
    rec->fC = a4;
    rec->f10 = (s32)a5; // the address the IOP writes the entries to
    CopyStringBounded((u8*)rec + 0x14, name, 0x3FF);
    ((u8*)rec)[0x413] = 0;
    if (a4 >= 0) {
        WriteBackDataCacheRange(a5, a4 << 6);
    }
    s32 r = CallRemoteService((RemoteCallClient*)mgr, 0xD, 1, rec, 0x414, g_cardReplyBuffer, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 0xD;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return r;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py src/versions/eu/lib/iop_file_client/func_eu_001F9D40.cpp func_eu_001F9D40 --version eu
// Still differs: the same instructions in the same order but for the loop's test, which retail makes with an sll of the loaded byte, and the allocation: retail keeps the name in s0 and the request block in s1 (the high half in $fp), here they swap.
// Only in PAL: opens a file on the IOP. Claims a handle of the file table (ClaimFreeFileHandle),
// sends the open request (the flags without their top bits, the mode, the name up to 0x400
// bytes) and waits for the reply; the handle's id and flags are set from it. Returns the handle's
// index, or a negative error.
struct Open_1F9D40 {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 flags;
    s32 mode;
    u8 name[0x400];
    s32 index;
};

s32 IsFileServiceVersionUnknown(void);

s32 OpenFile(const u8* name, u32 flags, ...)
{
    Open_1F9D40* g = (Open_1F9D40*)D_00627880;
    Handle_1F84D8* p;
    s32 mode;
    s32 h;
    s32 i;
    s32 first;
    s32 index;
    s32 out;
    s32* reply;
    SemaphoreParams ctor;

    LockFileRequests(0);
    if (g_fileClientOpen == 0) {
        OpenFileClient();
    }
    if (IsFileServiceVersionUnknown() != 0) {
        UnlockFileRequests();
        return 0xFFFEFFFC;
    }
    p = ClaimFreeFileHandle();
    if (p == 0) {
        UnlockFileRequests();
        return -0x13;
    }
    mode = *(s32*)((char*)__builtin_next_arg(flags) - 48);
    for (i = 0; i < 0x400; i++) {
        g->name[i] = name[i];
        if ((s8)name[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        g->name[0x3FF] = 0;
    }
    index = ((s32)p - (s32)D_00628940) >> 4;
    g->flags = flags & 0x6FFFFFFF;
    g->mode = mode;
    ctor.maxCount = 1;
    ctor.initCount = 0;
    ctor.option = 0;
    g->index = index;
    h = NewSemaphore(&ctor);
    g->result = (s32)&out;
    g->sema = h;
    g->result_size = 4;
    if (CallRemoteService((RemoteCallClient*)g_fileClient, 0, 0, D_00627880, 0x418, D_006284C0, 4, 0, 0) < 0) {
        FreeSemaphore(h);
        UnlockFileRequests();
        return -0xB;
    }
    reply = (s32*)((s32)D_006284C0 | 0x20000000);
    first = *reply;
    UnlockFileRequests();
    if (first == 0) {
        FreeSemaphore(h);
        return -0xB;
    }
    AwaitSemaphore(h);
    FreeSemaphore(h);
    if (out < 0) {
        AwaitSemaphore(D_002771C4);
        p->used = 0;
        PostSemaphore(D_002771C4);
        return out;
    }
    AwaitSemaphore(D_002771C4);
    p->used |= flags;
    p->id = out;
    PostSemaphore(D_002771C4);
    return index;
}

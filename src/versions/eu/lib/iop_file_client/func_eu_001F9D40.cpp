// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: opens a file on the IOP. Claims a handle of the file table (ClaimFreeFileHandle),
// sends the open request (the flags without their top bits, the mode, the name up to 0x400
// bytes) and waits for the reply; the handle's id and flags are set under the table's lock
// (D_002771C0, the one ClaimFreeFileHandle takes). Returns the handle's index, or a negative error.
// The name is copied as chars and the copy's value tested, so the test sign-extends the stored
// byte (retail's sll by 24). As CloseFile does with its reply, one variable holds the reply word
// and then the index returned (retail's copy into s1 before the last lock).
struct FileOpenRequest {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 flags;
    s32 mode;
    char name[0x400];
    s32 index;
};

s32 IsFileServiceVersionUnknown(void);

s32 OpenFile(const char* name, u32 flags, ...)
{
    FileOpenRequest* g = (FileOpenRequest*)&g_fileRequestBuffer;
    FileHandleEntry* p;
    s32 mode;
    s32 h;
    s32 i;
    s32 result;
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
        if ((g->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        g->name[0x3FF] = 0;
    }
    index = ((s32)p - (s32)g_fileHandleTable) >> 4;
    g->flags = flags & 0x6FFFFFFF;
    g->mode = mode;
    g->index = index;
    ctor.maxCount = 1;
    ctor.initCount = 0;
    ctor.option = 0;
    h = NewSemaphore(&ctor);
    g->result = (s32)&out;
    g->sema = h;
    g->result_size = 4;
    if (CallRemoteService(&g_fileClient, 0, 0, &g_fileRequestBuffer, 0x418, g_fileCallResult, 4, 0, 0) < 0) {
        FreeSemaphore(h);
        UnlockFileRequests();
        return -0xB;
    }
    reply = (s32*)((s32)g_fileCallResult | 0x20000000);
    result = *reply;
    UnlockFileRequests();
    if (result == 0) {
        FreeSemaphore(h);
        return -0xB;
    }
    AwaitSemaphore(h);
    FreeSemaphore(h);
    if (out < 0) {
        AwaitSemaphore(g_fileHandleTableSemaphore);
        p->used = 0;
        PostSemaphore(g_fileHandleTableSemaphore);
        return out;
    }
    result = index;
    AwaitSemaphore(g_fileHandleTableSemaphore);
    p->id = out;
    p->used |= flags;
    PostSemaphore(g_fileHandleTableSemaphore);
    return result;
}

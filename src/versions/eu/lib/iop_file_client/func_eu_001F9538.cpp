// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: claims the first free handle of the file table (marking it used) and returns it, or 0 when all 32 are in use.
FileHandleEntry* ClaimFreeFileHandle(void)
{
    CreateFileTableLock();
    AwaitSemaphore(g_fileHandleTableSemaphore);
    for (FileHandleEntry* p = g_fileHandleTable; p < g_fileHandleTable + 32; p++) {
        if (p->used == 0) {
            p->used = 0x10000000;
            PostSemaphore(g_fileHandleTableSemaphore);
            return p;
        }
    }
    PostSemaphore(g_fileHandleTableSemaphore);
    return 0;
}

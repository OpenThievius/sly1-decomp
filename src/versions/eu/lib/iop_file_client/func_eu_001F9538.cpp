// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: claims the first free handle of the file table (marking it used) and returns it, or 0 when all 32 are in use.
Handle_1F84D8* ClaimFreeFileHandle(void)
{
    CreateFileTableLock();
    AwaitSemaphore(g_fileHandleTableSemaphore);
    for (u8* p = g_fileHandleTable; p < g_fileHandleTable + 0x200; p += 0x10) {
        if (((Handle_1F84D8*)p)->used == 0) {
            ((Handle_1F84D8*)p)->used = 0x10000000;
            PostSemaphore(g_fileHandleTableSemaphore);
            return (Handle_1F84D8*)p;
        }
    }
    PostSemaphore(g_fileHandleTableSemaphore);
    return 0;
}

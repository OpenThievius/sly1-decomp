// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: claims the first free handle of the file table (marking it used) and returns it, or 0 when all 32 are in use.
FileHandleEntry* ClaimFreeFileHandle(void)
{
    CreateFileTableLock();
    AwaitSemaphore(D_002771C0);
    for (FileHandleEntry* p = D_00628940; p < D_00628940 + 32; p++) {
        if (p->used == 0) {
            p->used = 0x10000000;
            PostSemaphore(D_002771C0);
            return p;
        }
    }
    PostSemaphore(D_002771C0);
    return 0;
}

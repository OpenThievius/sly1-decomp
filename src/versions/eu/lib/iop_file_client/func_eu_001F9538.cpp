// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: claims the first free handle of the file table (marking it used) and returns it, or 0 when all 32 are in use.
Handle_1F84D8* ClaimFreeFileHandle(void)
{
    CreateFileTableLock();
    AwaitSemaphore(D_002771C0);
    for (u8* p = D_00628940; p < D_00628940 + 0x200; p += 0x10) {
        if (((Handle_1F84D8*)p)->used == 0) {
            ((Handle_1F84D8*)p)->used = 0x10000000;
            PostSemaphore(D_002771C0);
            return (Handle_1F84D8*)p;
        }
    }
    PostSemaphore(D_002771C0);
    return 0;
}

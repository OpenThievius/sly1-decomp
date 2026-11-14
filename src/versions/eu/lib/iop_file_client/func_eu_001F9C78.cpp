// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: true when the file service's answer (D_00628B68, the word the client got from the
// IOP) differs from both words this client knows: the library's version word (D_eu_002800DC,
// "2430") and the word D_002771C8 points at, which also differ from each other. CompareMemory
// returns 0 for equal words, so a known answer gives 0.
extern u8 D_eu_002800DC[];
s32 CompareMemory(const void* a, const void* b, s32 n);

s32 IsFileServiceVersionUnknown(void)
{
    const void* version = D_eu_002800DC;
    const void* reply = &g_fileClientResult;
    s32 ok = 0;
    if (CompareMemory(reply, version, 4) != 0) {
        if (CompareMemory(reply, D_002771C8, 4) != 0) {
            ok = CompareMemory(version, D_002771C8, 4) != 0;
        }
    }
    return ok;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001387C8.cpp func_eu_001387C8 --unit src/main/00138000.cpp
// Still differs: Allocates a halfword table of count+1, fills it and zero-terminates it; only the prologue order of the sq s2/s3 and move s2,a0/move s3,a1 differs (retail handles a0 first).
// Allocates a halfword table of the entry count plus one, fills it and zero-terminates it.
s32 func_00137BE0(void);
void func_00137A60(void* self, s32 bytes, void* buf);
void* func_0018D500(s32 size);
void func_eu_001387C8(void* a0, void** a1)
{
    s32 n = func_00137BE0();
    u16* buf = (u16*)func_0018D500((n + 1) * 2);
    *a1 = buf;
    func_00137A60(a0, n * 2, buf);
    buf[n] = 0;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001DDA10.cpp func_eu_001DDA10 --unit src/main/001DC000.cpp
// Still differs: Stores a count into D_eu_0027EE8C, allocates words into D_eu_0027ED80 (declared s32* as in the landed func_eu_001DDAB0) and fills each; retail keeps the index in s2 from the prologue and two extra saved registers (s5 for the count address), ours has frame 96 vs 112.
// Takes a count from func_00137BE0 into D_eu_0027EE8C, allocates that many words into D_eu_0027ED80 and fills each through func_eu_001387C8; returns the buffer.
extern s32 D_eu_0027EE8C;
extern s32* D_eu_0027ED80;
s32 func_00137BE0(void);
void* func_0018D500(s32 size);
void func_eu_001387C8(void* a0, void** a1);
s32* func_eu_001DDA10(void* a0)
{
    s32 i;
    D_eu_0027EE8C = func_00137BE0();
    D_eu_0027ED80 = (s32*)func_0018D500(D_eu_0027EE8C * 4);
    i = 0;
    while (i < D_eu_0027EE8C) {
        func_eu_001387C8(a0, (void**)(D_eu_0027ED80 + i));
        i++;
    }
    return D_eu_0027ED80;
}

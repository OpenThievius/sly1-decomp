// SPDX-License-Identifier: AGPL-3.0-or-later
// Reads the text table: a count from the stream into D_eu_0027EE8C, a word per entry allocated into
// D_eu_0027ED80, and each entry read through func_eu_001387C8.
extern s32 D_eu_0027EE8C;
extern s32* D_eu_0027ED80;
s32 ReadBufferedU16(void* self);
void* AllocateFrontMemory(s32 size);
void ReadBufferedWideString(void* a0, void** a1);
void LoadTextTable(void* a0)
{
    D_eu_0027EE8C = ReadBufferedU16(a0);
    D_eu_0027ED80 = (s32*)AllocateFrontMemory(D_eu_0027EE8C * 4);
    for (s32 i = 0; i < D_eu_0027EE8C; i++) {
        ReadBufferedWideString(a0, (void**)&D_eu_0027ED80[i]);
    }
}

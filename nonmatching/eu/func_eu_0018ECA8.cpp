// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 136/144 (94.4%), checked 2026-11-04
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0018ECA8.cpp func_eu_0018ECA8 --unit src/main/file_18D8E0.cpp
// Still differs: Fills a 0x30-byte record with callback and two tables and registers it; only scheduling differs (li a2 vs sw f144 order, lui order and a0 move around the record stores).
// Only in PAL: sets up two words of a global record, clears a 0x30-byte record, fills it with a callback and two tables, and registers it.
struct Rec_eu_18ECA8 {
    u32 f0;
    void* f4;
    void* f8;
    s32 fC;
    void* f10;
    s32 f14;
    u8 tail[0x30 - 0x18];
};

extern u8 D_eu_002CC280[];
extern u8 D_eu_0028CA70[];
extern void* D_eu_0027F0DC;
void func_eu_0018EBE8(void);
s32 func_001E2268(s32 a, s32 b);
void* func_001F5C0C(void* p, s32 c, s32 n);
void* func_001F6A10(void* rec);
void func_001F6A20(void* p, s32 c);

void func_eu_0018ECA8(void)
{
    Rec_eu_18ECA8 rec;
    D_eu_0026AC60.f144 = func_001E2268(0, 1);
    *(s32*)((u8*)&D_eu_0026AC60 + 0xC) = 0;
    func_001F5C0C(&rec, 0, 0x30);
    rec.f8 = D_eu_002CC280;
    rec.f4 = (void*)func_eu_0018EBE8;
    rec.f10 = D_eu_0028CA70;
    rec.fC = 0x1000;
    rec.f14 = 2;
    void* r = func_001F6A10(&rec);
    D_eu_0027F0DC = r;
    func_001F6A20(r, 0);
}

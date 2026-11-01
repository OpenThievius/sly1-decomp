// SPDX-License-Identifier: AGPL-3.0-or-later
// BROKEN, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ADE38.cpp func_eu_001ADE38 --unit src/main/001AC000.cpp
// Still differs: Builds key/record, calls helpers and virtual slot 8; only the delay-slot order of move a0,sp / move a1,v0 before the call to func_eu_001E3050 differs.
// Looks up a record and a text by two keys, builds two local buffers from them, and passes the first to the object's virtual at slot 8.
extern u8* D_eu_002636F0;
extern char D_eu_0024E2E0[];

struct Frame_eu_1ADE38 {
    u8 first[0x100];
    u8 second[0x40];
};

s32 func_eu_00160800(s32 key);
s32 func_eu_00160750(s32 key);
void func_eu_001E3050(void* out, s32 v);
void func_001ACEE0(void* a, u8* rec, s32 c);
s32 func_001E2100(const void* s);
void func_eu_001E3178(void* a, const void* b);

void func_eu_001ADE38(void* self, s32 a1, s32 a2)
{
    Frame_eu_1ADE38 f;
    u8* out = f.first;
    s32 key = (a1 << 8) | a2;
    u8* rec = (D_eu_002636F0 + (a1 * 0x44C + 0x10)) + a2 * 0x78;
    s32 s2 = func_eu_00160800(key);
    func_eu_001E3050(out, func_eu_00160750(key));
    u8* text = f.second;
    func_001ACEE0(text, rec, s2);
    if (func_001E2100(text) != 0) {
        func_eu_001E3178(f.first, D_eu_0024E2E0);
        func_eu_001E3178(f.first, text);
    }
    void** vt = *(void***)self;
    ((void (*)(void*, void*))vt[8])(self, f.first);
}

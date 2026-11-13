// SPDX-License-Identifier: AGPL-3.0-or-later
// BROKEN, checked 2026-11-01
// Still differs: Builds key/record, calls helpers and virtual slot 8; only the delay-slot order of move a0,sp / move a1,v0 before the call to func_eu_001E3050 differs.
// Looks up a record and a text by two keys, builds two local buffers from them, and passes the first to the object's virtual at slot 8.
struct Game_eu_1AE6D0;
extern Game_eu_1AE6D0* D_eu_002636F0;
extern char D_eu_0024E2E0[];

struct Frame_eu_1ADE38 {
    u8 first[0x100];
    u8 second[0x40];
};

s32 GetEntryFlags(s32 key);
s32 GetEntryName(s32 key);
void* CopyWideString(void* out, s32 v);
void FormatFlagGlyphs(void* a, u8* rec, s32 c);
s32 GetStringLength(const void* s);
void AppendStringToWide(void* a, const void* b);

void SetElementWideTextFromEntry(void* self, s32 a1, s32 a2)
{
    Frame_eu_1ADE38 f;
    s32 key = (a1 << 8) | a2;
    u8* rec = ((u8*)D_eu_002636F0 + (a1 * 0x44C + 0x10)) + a2 * 0x78;
    s32 s2 = GetEntryFlags(key);
    s32 name = GetEntryName(key);
    CopyWideString(f.first, name);
    u8* text = f.second;
    FormatFlagGlyphs(text, rec, s2);
    if (GetStringLength(text) != 0) {
        AppendStringToWide(f.first, D_eu_0024E2E0);
        AppendStringToWide(f.first, text);
    }
    void** vt = *(void***)self;
    ((void (*)(void*, void*))vt[8])(self, f.first);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ADF10.cpp func_eu_001ADF10 --unit src/main/001AC000.cpp
// Still differs: Formats up to three texts into buf1 then names into buf2 and calls virtual slot 8; still differs in t0 vs v0 for the b/c tests and a0/a1 move order before func_eu_001E3050 (6 lines).
// Formats up to three PAL-only texts from record id of the table at D_002623C0 (0x44C apart, from +0x10) into buf1, then the name of id goes through func_eu_001DDAB0 into buf2 and self's virtual slot 8 receives it.
extern u8 D_eu_0024E2E8[];
extern u8 D_eu_0024E308[];
extern u8 D_eu_0024E2E0[];
extern u8 D_eu_0024E238[];
extern u8 D_eu_0024E328[];
extern s32 D_eu_0027DB80[];

void func_eu_00160830(s32 id, s32* a, s32* b, s32* c);
s32 func_eu_001E2DD0(char* buf, const char* fmt, s32 a2, s32 a3);
void func_eu_001E3050(char* buf, const char* text);
void func_eu_001E3178(char* dst, char* src);
const char* func_eu_001DDAB0(s32 id);

struct Row_eu_001ADF10 { u8 pad[0x438]; s32 f438; s32 f43C; s32 f440; };
typedef void (*VFnB_eu_001ADF10)(void* self, char* text);
struct Obj_eu_001ADF10 { VFnB_eu_001ADF10* vtbl; };

void func_eu_001ADF10(Obj_eu_001ADF10* self, s32 id)
{
    char buf1[0x80];
    char buf2[0x100];
    s32 abc[3];
    func_eu_00160830(id, &abc[0], &abc[1], &abc[2]);
    Row_eu_001ADF10* r = (Row_eu_001ADF10*)((u8*)D_002623C0 + 0x10 + id * 0x44C);
    char* s0 = buf1;
    buf1[0] = 0;
    if (abc[0] != 0) {
        s0 += func_eu_001E2DD0(s0, (const char*)D_eu_0024E2E8, r->f438, abc[0]);
    }
    if (abc[1] != 0) {
        s0 += func_eu_001E2DD0(s0, (const char*)D_eu_0024E308, (s32)(abc[0] != 0 ? D_eu_0024E2E0 : D_eu_0024E238), r->f43C);
    }
    if (abc[2] != 0) {
        func_eu_001E2DD0(s0, (const char*)D_eu_0024E328, (s32)((abc[0] != 0 || abc[1] != 0) ? D_eu_0024E2E0 : D_eu_0024E238), r->f440);
    }
    func_eu_001E3050(buf2, func_eu_001DDAB0(D_eu_0027DB80[id]));
    func_eu_001E3178(buf2, buf1);
    self->vtbl[8](self, buf2);
}

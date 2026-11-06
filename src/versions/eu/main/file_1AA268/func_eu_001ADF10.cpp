// SPDX-License-Identifier: AGPL-3.0-or-later
// Formats up to three PAL-only texts from record id of the table at D_002623C0 (0x44C apart, from +0x10) into buf1, then the name of id goes through func_eu_001DDAB0 into buf2 and self's virtual slot 8 receives it.
extern u8 D_eu_0024E2E8[];
extern u8 D_eu_0024E308[];
extern u8 D_eu_0024E238[];
extern u8 D_eu_0024E328[];
extern s32 D_eu_0027DB80[];

void func_eu_00160830(s32 id, s32* a, s32* b, s32* c);
s32 func_eu_001E2DD0(char* buf, const char* fmt, ...);
const char* func_eu_001DDAB0(s32 id);

struct Row_eu_001ADF10 { u8 pad[0x438]; s32 f438; s32 f43C; s32 f440; };
typedef void (*VFnB_eu_001ADF10)(void* self, char* text);
struct Obj_eu_001ADF10 { VFnB_eu_001ADF10* vtbl; };

void func_eu_001ADF10(Obj_eu_001ADF10* self, s32 id)
{
    char buf1[0x80];
    char buf2[0x100];
    s32 a, b, c;
    func_eu_00160830(id, &a, &b, &c);
    Row_eu_001ADF10* r = (Row_eu_001ADF10*)((u8*)g_saveData + 0x10 + id * 0x44C);
    char* s0 = buf1;
    buf1[0] = 0;
    if (a != 0) {
        s0 += func_eu_001E2DD0(s0, (const char*)D_eu_0024E2E8, r->f438, a);
    }
    if (b != 0) {
        s0 += func_eu_001E2DD0(s0, (const char*)D_eu_0024E308, (s32)(a != 0 ? (const char*)D_eu_0024E2E0 : (const char*)D_eu_0024E238), r->f43C, b);
    }
    if (c != 0) {
        func_eu_001E2DD0(s0, (const char*)D_eu_0024E328, (s32)((a != 0 || b != 0) ? (const char*)D_eu_0024E2E0 : (const char*)D_eu_0024E238), r->f440, c);
    }
    func_eu_001E3050(buf2, (s32)func_eu_001DDAB0(D_eu_0027DB80[id]));
    func_eu_001E3178(buf2, buf1);
    self->vtbl[8](self, buf2);
}

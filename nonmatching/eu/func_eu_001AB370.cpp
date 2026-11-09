// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 428/480 (89.2%), checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AB370.cpp func_eu_001AB370 --unit src/main/file_1A7FE8.cpp
// Still differs: only the s/cur registers (retail cur $s0, s $s1) and the three hoisted high parts' registers. global-alloc places s first (weighted refs 44 over 93 insns, priority 2.37) against cur (35 over 91, 1.92) and gives it $s0 in pass 1; no consistent loop-depth weighting of these statements flips that (s has more references than cur at every depth), and no hard register or local-alloc pseudo can keep $s0 from s alone, so retail's RTL must differ in references or lives that the final code does not show (2026-11-09, w9).
// Rewrites a string into a local buffer: characters the font lacks become escape codes and "/digits" runs get wrapped, then hands it to func_eu_001AB238.
struct Vt_eu_1AB370 { u8 pad0[0x10]; s16 off; u8 pad1[2]; s32 (*has)(void* at, s32 ch); };
struct Font_eu_1AB370 { u8 pad0[0x4C]; Vt_eu_1AB370* vt; };
struct Self_eu_1AB370 { u8 pad0[4]; Font_eu_1AB370* font; };
extern u8 D_eu_00263550[];
extern char D_eu_0024E0A0[];
extern char D_eu_0024E0A8[];
extern char D_eu_0024E0B8[];
extern u8 D_eu_0024FB49[];
s32 FormatToString(char* dst, const char* fmt, ...);
void func_eu_001AB238(void* self, char* buf);

void func_eu_001AB370(Self_eu_1AB370* self, u8* s)
{
    char buf[0x200];
    char* cur = buf;
    u8 c;
    while (*s != 0) {
        Font_eu_1AB370* f = self->font;
        if (f->vt->has((u8*)f + f->vt->off, *s) == 0) {
            Font_eu_1AB370* f3 = (Font_eu_1AB370*)GetFontById(3);
            u32 code;
            if (f3->vt->has((u8*)f3 + f3->vt->off, *s) != 0) {
                code = D_eu_00263550[3];
            } else {
                Font_eu_1AB370* f4 = (Font_eu_1AB370*)GetFontById(4);
                if (f4->vt->has((u8*)f4 + f4->vt->off, *s) == 0) {
                    goto plain;
                }
                code = D_eu_00263550[4];
            }
            cur += FormatToString(cur, D_eu_0024E0A0, code, *s);
            goto next;
        }
    plain:
        c = *s;
        if (c == 0x2F && (D_eu_0024FB49[s[1]] & 4) != 0) {
            cur += FormatToString(cur, D_eu_0024E0A8);
            s++;
            while (*s != 0 && (D_eu_0024FB49[*s] & 4) != 0) {
                *cur++ = *s++;
            }
            cur += FormatToString(cur, D_eu_0024E0B8);
            s--;
        } else {
            *cur++ = c;
        }
    next:
        s++;
    }
    *cur = 0;
    func_eu_001AB238(self, buf);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// Rewrites a string into a local buffer: a character the element's font lacks becomes an escape code
// naming font 3 or font 4 (whichever has it), and a "/digits" run is wrapped in two markers; then hands
// it to func_eu_001AB238. Each escape and each plain copy is written in its own arm (jump2's
// cross-jumping merges them after reload, but global-alloc counts both): with one shared tail the
// hoisted format addresses and the string and buffer pointers take other registers.
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

void SubstituteScreenElementGlyphs(Self_eu_1AB370* self, u8* s)
{
    char buf[0x200];
    char* cur = buf;
    u8 c;
    while (*s != 0) {
        Font_eu_1AB370* f = self->font;
        if (f->vt->has((u8*)f + f->vt->off, *s) == 0) {
            Font_eu_1AB370* f3 = (Font_eu_1AB370*)GetFontById(3);
            if (f3->vt->has((u8*)f3 + f3->vt->off, *s) != 0) {
                cur += FormatToString(cur, D_eu_0024E0A0, D_eu_00263550[3], *s);
                goto next;
            }
            Font_eu_1AB370* f4 = (Font_eu_1AB370*)GetFontById(4);
            if (f4->vt->has((u8*)f4 + f4->vt->off, *s) != 0) {
                cur += FormatToString(cur, D_eu_0024E0A0, D_eu_00263550[4], *s);
                goto next;
            }
        }
        c = *s;
        if (c == 0x2F) {
            if ((D_eu_0024FB49[s[1]] & 4) != 0) {
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
        } else {
            *cur++ = c;
        }
    next:
        s++;
    }
    *cur = 0;
    func_eu_001AB238(self, buf);
}

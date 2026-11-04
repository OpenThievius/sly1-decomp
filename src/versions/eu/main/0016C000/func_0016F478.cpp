// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the decoded string is formatted with a PAL-only function and handed to func_eu_001AB238, then the object's size is set and its virtual at 0x38 called.
extern u8 D_eu_0024AFF8[];
void func_eu_001AB238(void* self, const char* s);

void func_0016F478(void)
{
    char text[0x40];
    u8 buf[0x10];

    if ((D_002623C0->f19D8 << 8 | D_002623C0->f19DC) == 0x400) {
        if ((func_001602A0() & 6) == 6) {
            if (D_002623C0->f19E8 == 99 && D_002623C0->f19E0 == 0) {
                u8* p = buf;
                func_001E2138((char*)p, D_eu_0024AFF8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                func_001E1FD0(text, (const u8*)D_0024A848, buf);
                func_eu_001AB238(&D_0026EC70, text);
                func_001AA8B8(&D_0026EC70, 10.0f);
                D_0026EC70.vt->f38(&D_0026EC70);
            }
        }
    }
}

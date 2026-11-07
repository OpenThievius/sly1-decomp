// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the decoded string is formatted with a PAL-only function and handed to func_eu_001AB238, then the object's size is set and its virtual at 0x38 called.
extern u8 D_eu_0024AFF8[];
void func_eu_001AB238(void* self, const char* s);

void func_0016F478(void)
{
    char text[0x40];
    u8 buf[0x10];

    if ((g_saveData->f19D8 << 8 | g_saveData->f19DC) == 0x400) {
        if ((ComputeCompletionMask() & 6) == 6) {
            if (g_saveData->f19E8 == 99 && g_saveData->f19E0 == 0) {
                u8* p = buf;
                CopyString((char*)p, D_eu_0024AFF8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                FormatToString(text, (const u8*)D_0024A848, buf);
                func_eu_001AB238(&g_buttonHintElement, text);
                SetScreenElementHoldTime(&g_buttonHintElement, 10.0f);
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            }
        }
    }
}

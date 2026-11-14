// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the decoded string is formatted with a PAL-only function and handed to func_eu_001AB238, then the object's size is set and its virtual at 0x38 called.
extern u8 D_eu_0024AFF8[];
void SetScreenElementByteText(void* self, const char* s);

void ShowPasswordMessage(void)
{
    char text[0x40];
    u8 buf[0x10];

    if ((g_saveData->levelIndex << 8 | g_saveData->entryIndex) == 0x400) {
        if ((ComputeCompletionMask() & 6) == 6) {
            if (g_saveData->pickupCount == 99 && g_saveData->reserveCount == 0) {
                u8* p = buf;
                CopyString((char*)p, (const char*)D_eu_0024AFF8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                FormatToString(text, (const char*)D_0024A848, buf);
                SetScreenElementByteText(&g_buttonHintElement, text);
                SetScreenElementHoldTime(&g_buttonHintElement, 10.0f);
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            }
        }
    }
}

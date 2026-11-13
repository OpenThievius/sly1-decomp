// SPDX-License-Identifier: AGPL-3.0-or-later
// Initialises the object, runs func_eu_0015DF58 up to n times until it returns 0, then clears with func_eu_0015DEE0.
s32 ReadTextCharAnyWidth(void* self);
void StoreTextReaderChar(void* self, s32 v);
void RewindTextReader(void* self);
void SeekTextReader(void* self, s32 n)
{
    RewindTextReader(self);
    while (ReadTextCharAnyWidth(self) != 0) {
        if (n == 0) {
            break;
        }
        n--;
    }
    StoreTextReaderChar(self, 0);
}

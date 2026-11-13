// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets the text of an object: a string that is set is passed to the inner object, otherwise its id is cleared; then the virtual at slot 8 is called.
s32 GetStringLength(const char* s);
void CopyStringToWide(void* inner, const char* s);

void SetScreenElementByteText(void* self, const char* s)
{
    if (s != 0) {
        if (GetStringLength(s) != 0) {
            CopyStringToWide((u8*)self + 8, s);
            goto call;
        }
    }
    *(u16*)((u8*)self + 8) = 0;
call:
    void** vt = *(void***)self;
    ((void (*)(void*, void*))vt[8])(self, (u8*)self + 8);
}

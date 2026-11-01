// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets the text of an object: a string that is set is passed to the inner object, otherwise its id is cleared; then the virtual at slot 8 is called.
s32 func_001E2100(const char* s);
void func_eu_001E3140(void* inner, const char* s);

void func_eu_001AB238(void* self, const char* s)
{
    if (s != 0) {
        if (func_001E2100(s) != 0) {
            func_eu_001E3140((u8*)self + 8, s);
            goto call;
        }
    }
    *(u16*)((u8*)self + 8) = 0;
call:
    void** vt = *(void***)self;
    ((void (*)(void*, void*))vt[8])(self, (u8*)self + 8);
}

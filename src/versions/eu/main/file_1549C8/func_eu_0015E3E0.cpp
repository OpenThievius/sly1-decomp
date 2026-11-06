// SPDX-License-Identifier: AGPL-3.0-or-later
// Initialises the object, runs func_eu_0015DF58 up to n times until it returns 0, then clears with func_eu_0015DEE0.
s32 func_eu_0015DF58(void* self);
void func_eu_0015DEE0(void* self, s32 v);
void func_eu_0015DDA0(void* self);
void func_eu_0015E3E0(void* self, s32 n)
{
    func_eu_0015DDA0(self);
    while (func_eu_0015DF58(self) != 0) {
        if (n == 0) {
            break;
        }
        n--;
    }
    func_eu_0015DEE0(self, 0);
}

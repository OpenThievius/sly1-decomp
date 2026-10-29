// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001B9F30(void);

void func_001DAE48(void)
{
    func_001B9F30();
}

void func_001C0C08(void* a, void* b);

void func_001DBAC0(void* self, void* a, void* b)
{
    func_001C0C08(a, b);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

void* func_001DBBD8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B14);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

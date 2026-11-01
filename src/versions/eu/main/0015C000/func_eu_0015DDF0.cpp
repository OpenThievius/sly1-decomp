// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies a 4-byte word from src to self+0xAC and then to self+0xA4, both unaligned.
struct __attribute__((packed)) Word_eu_0015DDF0 {
    s32 v;
};

void func_eu_0015DDF0(void* self, void* src)
{
    u8* o = (u8*)self;
    *(Word_eu_0015DDF0*)(o + 0xAC) = *(Word_eu_0015DDF0*)src;
    *(Word_eu_0015DDF0*)(o + 0xA4) = *(Word_eu_0015DDF0*)(o + 0xAC);
}

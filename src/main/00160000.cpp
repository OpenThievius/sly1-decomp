// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_002623D0[];

void* func_00160110();

void* func_00160148()
{
    void* p = func_00160110();
    if (p == 0)
    {
        return D_002623D0;
    }
    return *(void**)((u8*)p + 0x24);
}

s32* func_00160810();

s32 func_00160850()
{
    s32* p = func_00160810();
    s32 value = 0;
    if (p)
    {
        value = *p;
    }
    return value;
}

struct Refs_160D00
{
    u8 pad[4];
    s32 refs;
};

void func_00160D00(Refs_160D00* self)
{
    self->refs--;
}

struct Stream_161458 {
    u8 pad0[0xC];
    u32* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_00161458(Stream_161458* self, u32 value)
{
    func_001612E8(self, 1, 1);
    u32* p = self->cur;
    self->cur = p + 4;
    p[0] = value & 0xFF;
    p[1] = (value & 0xFF00) >> 8;
    p[2] = (value >> 16) & 0xFF;
    p[3] = value >> 24;
}

struct Stream_161670 {
    u8 pad0[0xC];
    u32* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_00161670(Stream_161670* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    func_001612E8(self, 1, 4);
    u32* p = self->cur;
    self->cur = p + 4;
    p[0] = a1;
    p[1] = a2;
    p[2] = (a3 & 0xFFFFFF) << 4;
    p[3] = ((a4 & 0xFF) << 4) | 0x8000;
}

struct Stream_1618C0 {
    u8 pad0[0xC];
    u64* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_001618C0(Stream_1618C0* self, s32 a1, s32 a2, u32 a3, u32 a4)
{
    func_001612E8(self, 0, 4);
    u64 lo = (u64)a1 | (u64)(a2 << 16);
    u64 mid = a3 & 0xFFFFFF;
    u64* p = self->cur;
    self->cur = p + 1;
    *p = (lo | (mid << 32)) | ((u64)a4 << 56);
}

struct __attribute__((packed)) Unaligned_1626A8 { u32 value; };

void func_001626A8(u8* dst, u8* src)
{
    *(Unaligned_1626A8*)(dst + 0x114) = *(Unaligned_1626A8*)src;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_00262708[];

void func_001B7B78(void* self);
void func_00152600(void* data, void* self);

void func_0016A4C8(void* self)
{
    func_001B7B78(self);
    func_00152600(D_00262708, self);
}

struct Packed_16A500 {
    u64 value;
} __attribute__((packed));

void func_001BA130(void* self);

void func_0016A500(u8* self)
{
    Packed_16A500 tmp = *(Packed_16A500*)(self + 0x558);
    func_001BA130(self);
    *(Packed_16A500*)(self + 0x558) = tmp;
}

extern void* D_00262E10;

struct Owner_16A548 {
    u8 pad0[0x23B0];
    void* field;
};

s32 func_001B8A08(void* a, void* b);

s32 func_0016A548(void* a0, Owner_16A548* a1)
{
    if (a1 == D_00262E10 && a0 == a1->field) {
        return 1;
    }
    return func_001B8A08(a0, a1);
}

extern void* D_00275710;

struct Obj_16B520 {
    u8 pad0[0x25C];
    s32 field25C;
};

void* func_0015A448(void* obj, s32 id, s32 flags);
void func_001F4ED0(void* p);

void func_0016B520(Obj_16B520* self)
{
    if (self->field25C != 0) {
        void* p = func_0015A448(D_00275710, 0x4FD, 0);
        if (p != 0) {
            func_001F4ED0(p);
        }
    }
}

void func_001AA298(void* self);

void func_0016B560(void* self)
{
    func_001AA298(self);
}

extern u8* D_002623C0;

u32 func_0016BB78(u32 bit)
{
    u32 mask;
    if (bit >= 16) {
        mask = 0;
    } else {
        mask = 1 << bit;
    }
    return *(u32*)(D_002623C0 + 0x19F4) & mask;
}

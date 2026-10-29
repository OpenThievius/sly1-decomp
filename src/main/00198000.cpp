// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Actor_198980 { u8 pad0[0x554]; s32 flag554; };

void func_001B7968(void* self);

void func_00198980(Actor_198980* self)
{
    func_001B7968(self);
    self->flag554 = 1;
}

struct Actor_198A88 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x55C - 0x18];
    s32 n55C;
    void* arr560[4];
    s32 n570;
    void* arr574[1];
};

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);

void func_00198A88(Actor_198A88* self)
{
    s32 i;

    func_001249A8(self);
    for (i = 0; i < self->n55C; i++) {
        void* r = func_0015A448(self->f14, self->arr560[i], self);
        if (r != 0) {
            self->arr574[self->n570++] = r;
        }
    }
}

typedef s32 (*VFn_198B28)(void* self);
struct Actor_198B28 {
    VFn_198B28* vtbl;
    u8 pad0[0x558 - 4];
    s32 flag558;
    u8 pad1[0x570 - 0x55C];
    s32 n570;
    void* arr574[1];
};

void func_00124A48(void* self);
s32 func_0012C9A8(void* node);
void func_00182ED8(void* node);

void func_00198B28(Actor_198B28* self)
{
    s32 i;

    func_00124A48(self);
    for (i = 0; i < self->n570; i++) {
        void* node = self->arr574[i];
        if (func_0012C9A8(node)) {
            self->flag558 = 1;
        }
        func_00182ED8(node);
    }
    if (self->vtbl[76](self) == 0) {
        self->vtbl[7](self);
    }
}

struct Bits_199C10 { u8 pad[0x5A0]; s32 index; };

extern u8* D_002623C8;

void func_00199C10(Bits_199C10* self, s32* out)
{
    s32 n = self->index;
    s32 byte = n / 8;
    s32 bit = n & 7;
    u8 b = (D_002623C8 + byte)[0x68];
    s32 mask = 1;
    mask <<= bit;
    *out = (b & mask) != 0;
}

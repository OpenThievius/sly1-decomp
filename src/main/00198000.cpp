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

typedef void (*VFn_198DA8)(void* self);

struct Actor_198DA8 {
    VFn_198DA8* vtbl;
    u8 pad_04[0x570 - 4];
    s32 count_570;
    void* items_574[1];
};

void func_0012C8F8(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00198DA8(Actor_198DA8* self)
{
    VFn_198DA8 fn = self->vtbl[7];
    fn(self);
    s32 i = self->count_570;
    i--;
    for (; i >= 0; i--) {
        (void)func_0012C8F8(self->items_574[i], 0, 0.0f, 1, 1.0f, 0);
    }
    self->vtbl[78](self);
    (void)func_001837E0(self, 2, 0, 0);
}

typedef void (*VFn_198E58)(void* self, void* msg);

struct Msg_198E58 {
    s32 kind;
    void* owner;
    u8 pad_08[0x50 - 8];
};

struct Target_198E58 {
    VFn_198E58* vtbl;
};

struct Actor_198E58 {
    u8 pad_00[0x584];
    Target_198E58* target_584;
};

void func_00198E58(Actor_198E58* self)
{
    Target_198E58* t = self->target_584;
    if (t != 0) {
        Msg_198E58 msg;
        msg.kind = 1;
        msg.owner = self;
        t->vtbl[31](t, &msg);
    }
}

struct Actor_198E98 {
    u8 pad_00[0x554];
    s32 slot_554;
};

s32 func_00182FC8(void* self);

s32 func_00198E98(Actor_198E98* self)
{
    if (func_00182FC8(self)) {
        return (self->slot_554 != 0) ? 1 : 2;
    }
    return 0;
}

typedef void (*VFn_198EF8)(void* self, void* other);

struct Msg_198EF8 {
    u8 pad_00[8];
    s32 key_08;
};

struct Ctx_198EF8 {
    VFn_198EF8* vtbl;
    u8 pad_04[0x2230 - 4];
    Msg_198EF8* watched_2230;
};

struct Actor_198EF8 {
    u8 pad_00[0x570];
    s32 count_570;
    s32 ids_574[5];
    s32 marks_588[4];
    s32 done_598;
};

extern Ctx_198EF8* D_00262E10;

void func_00127378(Actor_198EF8* self, s32 msg, Msg_198EF8* m);

void func_00198EF8(Actor_198EF8* self, s32 msg, Msg_198EF8* m)
{
    (void)func_00127378(self, msg, m);
    if (msg == 5) {
        for (s32 i = 0; i < self->count_570; i++) {
            if (m->key_08 == self->ids_574[i]) {
                self->marks_588[i] = 1;
            }
        }
        Ctx_198EF8* g = D_00262E10;
        if (g != 0) {
            if (m == g->watched_2230) {
                g->vtbl[28](g, self);
                self->done_598 = 1;
            }
        }
    }
}

struct Rec_19A088 { s32 flags; u8 rest[0x74]; };
struct Sys_19A088 { u8 pad0[0x19D8]; s32 cur19D8; };
extern Sys_19A088* D_002623C0;

void func_0019A088(s32 index)
{
    if (index == -1) index = D_002623C0->cur19D8;
    u8* base = (u8*)D_002623C0 + (index * 0x44C + 0x10);
    Rec_19A088* p = (Rec_19A088*)base;
    Rec_19A088* end = (Rec_19A088*)(base + 0x438);
    do {
        p->flags |= 1;
        p++;
    } while ((s32)p < (s32)end);
    *(s32*)(base + 0x448) |= 0x1F;
}

struct Obj_19A0F0 { u8 pad0[0x30]; s32 f30; };
extern Obj_19A0F0 D_00275BC0;
void func_0019A088(s32 index);
void func_001E5278(s32 mode);

void func_0019A0F0()
{
    for (s32 i = 0; i < 6; i++) func_0019A088(i);
    if (D_00275BC0.f30 == 2) func_001E5278(0);
}

struct Obj_19A148 { u8 pad0[0x644]; s32 f644; u8 pad1[0x4]; s32 f64C; };
void func_001921A8(Obj_19A148* self);

void func_0019A148(Obj_19A148* self)
{
    func_001921A8(self);
    self->f64C = -1;
    self->f644 = -1;
}

struct Obj_19A178 { s32 f0; s32 f4; s32 f8; };
extern s32 D_00275710;
s32 func_0015A418(s32 a, s32 b, s32 c, s32 d);
void func_00182ED8(s32 a);
s32 func_001B6290(s32 a, s32 b, s32 c, s32 d);

void func_0019A178(Obj_19A178* self, s32 x)
{
    self->f4 = func_0015A418(D_00275710, 0x101, 0x37A, self->f0);
    func_00182ED8(self->f4);
    self->f8 = func_001B6290(self->f4, self->f0, x, 0);
}

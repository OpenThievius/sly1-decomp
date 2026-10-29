// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Buf_19DF48 { u8 raw[0x30]; };
typedef void (*Fn_19DF48)(void);
struct Row_19DF48 { Fn_19DF48 fn; u8 pad0[8 - 4]; s32 x8; u8 pad1[0x80 - 12]; };

extern u8 D_0026AC20[];
extern u8 D_0026AC30[];

void func_001611B8(void* self);
void func_001529C8(void* self, s32 a, void* b);
void func_001612F8(void* self, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_0019DA30(void);
void func_0019DA60(void);
void func_0019DAD8(void);
void func_0019DB20(void);
void func_0019DB68(void);
void func_0019DBB0(void);

void func_0019DF48(void)
{
    Buf_19DF48 buf;
    Row_19DF48* rows;
    u8* p;
    s32 i;

    func_001611B8(buf.raw);
    func_001529C8(buf.raw, 1, D_0026AC20);
    func_001612F8(buf.raw, 0x7D, 0, 3, 0x412, 0);
    rows = (Row_19DF48*)D_0026AC30;

    rows[0].fn = func_0019DA30;
    rows[1].fn = func_0019DA60;
    rows[2].fn = func_0019DAD8;
    rows[3].fn = func_0019DB20;
    rows[4].fn = func_0019DB20;
    rows[5].fn = func_0019DB68;
    rows[6].fn = func_0019DB20;
    rows[7].fn = func_0019DB20;
    rows[8].fn = func_0019DB20;
    rows[9].fn = func_0019DB68;
    rows[12].fn = func_0019DB20;
    rows[11].fn = func_0019DB20;
    rows[10].fn = func_0019DB20;
    rows[13].fn = func_0019DB20;
    rows[14].fn = func_0019DB68;
    rows[15].fn = func_0019DB68;
    rows[16].fn = func_0019DB20;
    rows[17].fn = func_0019DBB0;

    p = D_0026AC30 + 0x888;
    i = 17;
    do {
        *(s32*)p = -1;
        i--;
        p -= 0x80;
    } while (i >= 0);
}

typedef void (*VFn_19E040)(void* self);
struct Node_19E040 { VFn_19E040* vtbl; u8 pad0[0x550 - 4]; s32 f550; u8 pad1[0x564 - 0x554]; Node_19E040* next564; };
struct Pool_19E040 { u8 pad0[0x1B38]; Node_19E040* head1B38; Node_19E040* last1B3C; };

Node_19E040* func_0019E040(Pool_19E040* self, s32 flag)
{
    if (flag == 0 && self->last1B3C != 0) {
        return self->last1B3C;
    }
    Node_19E040* n = self->head1B38;
    if (n != 0) {
        self->head1B38 = n->next564;
        n->f550 = flag;
        n->vtbl[6](n);
        if (flag == 0) {
            self->last1B3C = n;
        }
    }
    return n;
}

struct Obj_19E0B8 {
    u8 pad0[0x80];
    f32 f80;
    u8 pad84[0x2C8 - 0x84];
    u64 q2C8;
    u8 pad2D0[0x538 - 0x2D0];
    u64 q538;
    u8 pad540[0x558 - 0x540];
};

void func_001B7968(Obj_19E0B8* self);
void func_00152438(void* p, s32 n);

void func_0019E0B8(Obj_19E0B8* self)
{
    func_001B7968(self);
    func_00152438((u8*)self + 0x558, 0x10);
    u64 flags = self->q2C8;
    flags &= (u64)(s64)(s32)0xCFFFFFFF;
    flags |= 0x20000000ULL;
    u64 wide = self->q538;
    wide |= (u64)1 << 42;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    wide |= (u64)1 << 51;
    f32 k = 1e10f;
    flags |= (u64)1 << 40;
    self->q538 = wide;
    self->f80 = k;
    self->q2C8 = flags;
}

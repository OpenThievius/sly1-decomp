// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001F3A40(void);

void func_0016C4B8(void)
{
    func_001F3A40();
}

extern s32 D_002629C8;

void func_0016DCF0(s32 value)
{
    D_002629C8 = value;
}

struct Obj_16DF30 { u8 pad0[0x6E8]; s32 f6e8; u8 pad1[0x7A0 - 0x6EC]; s32 f7a0; u8 pad2[0x7A8 - 0x7A4]; s32 f7a8; };

void func_001400A8(void* self);

void func_0016DF30(Obj_16DF30* self)
{
    func_001400A8(self);
    self->f6e8 = 0;
    self->f7a0 = -1;
    self->f7a8 = -1;
}

struct Obj_16EC38 { u8 pad0[0x14]; s32 f14; s32 f18; u8 pad1[0xBC - 0x1C]; void* fBC; void* fC0; };

void func_001A7CE8(void* p);

void func_0016EC38(Obj_16EC38* self)
{
    if (self->fC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    func_001A7CE8(self->fBC);
}

struct Obj_16F7B0 { u8 pad0[0x21C8]; f32 f21c8; u8 pad1[0x2284 - 0x21CC]; f32 f2284; };

extern void* D_00262E10;
extern u8 D_00262E40[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
void func_00159478(void* a, void* b);

void func_0016F7B0(Obj_16F7B0* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 0x97, D_00262E40);
    func_00159478((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21c8 = -1.0f;
    D_00262E10 = self;
}

extern u8 D_00262A80[];
extern u8 D_00262AB8[];
extern u8 D_00262AF0[];
extern u8 D_00262B28[];
extern u8 D_00262B60[];
extern u8 D_00262B98[];
extern u8 D_00262BD0[];
extern u8 D_00262C08[];
extern u8 D_00262C48[];

void func_0016F188(void* entry);

void func_0016F588(void)
{
    func_0016F188(D_00262A80);
    func_0016F188(D_00262AB8);
    func_0016F188(D_00262AF0);
    func_0016F188(D_00262B28);
    func_0016F188(D_00262B60);
    func_0016F188(D_00262B98);
    func_0016F188(D_00262BD0);
    func_0016F188(D_00262C08);
    func_0016F188(D_00262C48);
}

struct Packet_0016DA00 {
    u8 pad0[0x8];
    s32 code;
};

void func_00127378(void* self, s32 type, void* packet);
void func_0016D490(void* self);
void func_0016D828(void* self);
void func_0016D928(void* self);
void func_0016DAC0(void* self, s32 mode);

void func_0016DA00(void* self, s32 type, Packet_0016DA00* packet)
{
    func_00127378(self, type, packet);
    if (type != 0x13) {
        return;
    }
    s32 code = packet->code;
    if (code == 0x2FE) {
        goto call928;
    }
    if (code < 0x2FF) {
        if (code == 0x2FD) {
            goto call490;
        }
        return;
    }
    if (code == 0x2FF) {
        goto callDAC0;
    }
    if (code == 0x300) {
        func_0016D828(self);
    }
    return;
call490:
    func_0016D490(self);
    return;
callDAC0:
    func_0016DAC0(self, 2);
    return;
call928:
    func_0016D928(self);
}

extern s32 D_002629C8;

void func_0016DD00(void)
{
    D_002629C8 = 0;
}

struct Tune_0016DD10 {
    u8 pad0[0x31C];
    f32 f31C;
    f32 f320;
    f32 f324;
    f32 f328;
    f32 f32C;
    f32 f330;
    f32 f334;
};

void func_00123ED0(void* self);

void func_0016DD10(Tune_0016DD10* self)
{
    func_00123ED0(self);
    self->f31C = 2.25f;
    self->f320 = 2.0f;
    self->f324 = 0.8f;
    self->f328 = 4.0f;
    self->f32C = 0.5f;
    self->f330 = 1000.0f;
    self->f334 = 2000.0f;
}

void func_001289C0(void* self);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);

void func_0016DD90(u8* self)
{
    func_001289C0(self);
    s32 r = func_0015A4F0(*(s32*)(self + 0x14), 0x201, 0x73, self, 0x10, self + 0x2D0);
    *(s32*)(self + 0x310) = r;
    if ((u32)r >= 0x11) {
        *(s32*)(self + 0x310) = 0x10;
    }
}

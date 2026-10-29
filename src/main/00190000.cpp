// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_192498 {
    void** vtbl;
};

void func_00192498(Obj_192498* self, s32* out)
{
    *out = ((s32 (*)(Obj_192498*, s32*))self->vtbl[0x144 / 4])(self, out);
}

extern s32 D_00269BCC;
extern void* D_00269C98[];

void* func_001925F0()
{
    s32 i = D_00269BCC;
    if (i < 0) return 0;
    return D_00269C98[i];
}

struct Obj_1926D0 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x18 - 0xC];
    s32 f18;
    u8 pad2[0x550 - 0x1C];
    s32 f550;
};

extern s32 D_00269C90;
extern Obj_1926D0* D_00262E10;
s32 func_00182FC8();
s32 func_00192688(Obj_1926D0* value);

void func_001926D0(Obj_1926D0* self)
{
    if (self->f550 == 0) return;
    if (self->f18 != 0) return;
    if (!func_00182FC8()) return;
    if (func_00192688(self) >= 0) return;
    s32 n = D_00269C90;
    if ((u32)n < 16) {
        D_00269C98[n] = self;
        D_00269C90 = n + 1;
    } else if (self->f8 == 5 && D_00262E10 == 0) {
        D_00269C98[0] = self;
    }
}

extern s32 D_00269BCC;
extern s32 D_00269C90;
extern void* D_00269C98[];
s32 func_00192688(void* value);
void func_00192880(s32 index);
void func_001F5B08(void* dst, void* src, s32 size);

void func_00192780(void* value)
{
    s32 idx = func_00192688(value);
    if (idx < 0) return;
    if (idx == D_00269BCC) func_00192880(-1);
    s32 n = D_00269C90;
    func_001F5B08(&D_00269C98[idx], &D_00269C98[idx + 1], (n - idx) * 4 - 4);
    if (idx < D_00269BCC) D_00269BCC = D_00269BCC - 1;
    D_00269C90 = D_00269C90 - 1;
}

void func_001B7A98(void* self);
void func_001926D0(void* self);

void func_00192820(void* self)
{
    func_001B7A98(self);
    func_001926D0(self);
}

void func_001B7B78(void* self);
void func_00192780(void* self);

void func_00192850(void* self)
{
    func_001B7B78(self);
    func_00192780(self);
}

struct Obj_192990 {
    u8 pad[0x550];
    s32 f550;
};

void func_001926D0(Obj_192990* self);
void func_00192780(Obj_192990* self);

void func_00192990(Obj_192990* self, s32 value)
{
    if (self->f550 == value) return;
    self->f550 = value;
    if (value) func_001926D0(self);
    else func_00192780(self);
}

s32 func_00192688(void* value);
void func_00192880(s32 index);

void func_001929D0(void* value)
{
    func_00192880(func_00192688(value));
}

extern u8 D_00604700[];
void* func_001925F0();

void* func_001929F8()
{
    void* r = func_001925F0();
    if (r) return (u8*)r + 0x580;
    return D_00604700;
}

struct Pair_192A28 {
    s32 a;
    s32 b;
};

void func_00192A28(s32, s32, Pair_192A28* out)
{
    out->b = 1;
    out->a = 1;
}

typedef s32 (*VFn_190450)(void* self, s32 value);

struct Mid_190450 { u8 pad0[0x618]; void* p618; };

struct Obj_190450 {
    VFn_190450* vtbl;
    u8 pad0[0xC2C - 4];
    Mid_190450* mid;
    s32 c30;
    s32 c34;
};

s32 func_001A8820(void* p, s32 v);
s32 func_001C9990(void* self, s32* arg);

s32 func_00190450(Obj_190450* self, s32* arg)
{
    if (self->vtbl[79](self, arg[0])) {
        return 0;
    }
    self->c34 = 0;
    self->c30 = arg[0];
    if (arg[0] == 0 && arg[1] != 0) {
        if (func_001A8820(self->mid->p618, arg[1])) {
            self->c34 = 1;
        }
    }
    return func_001C9990(self, arg);
}

struct Obj_1906E8 { u8 pad0[0xC28]; s32 c28; };

void func_001906E8(Obj_1906E8* self, s32 value)
{
    self->c28 = value;
}

u32 func_001907E0(u32 x)
{
    return (x & 1) ? 0 : x;
}

extern s32 D_00269BA4;

void func_00191EB0(void)
{
    D_00269BA4 = 0;
}

struct Obj_191FD8 {
    u8 pad0[0x14];
    s32 c14;
    s32 c18_pad;
    u8 pad1[0x64 - 0x1C];
    s32 c64;
    s32 c68;
};

void func_00182C58(void* self);
s32 func_0015A418(s32 a0, s32 a1, s32 a2, void* a3);

void func_00191FD8(Obj_191FD8* self)
{
    func_00182C58(self);
    if (self->c64 != -1) {
        self->c68 = func_0015A418(self->c14, 4, self->c64, self);
    }
}

s32 func_00128018(void* a0, s32 a1, void* a2, void* a3);

s32 func_00192128(u8* self, void* other)
{
    void* p = self + 0x40;
    return func_00128018(other, 0, p, p);
}

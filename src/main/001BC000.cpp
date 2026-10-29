// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1BC748 { u8 pad[0x538]; u64 flags; };

void func_001BC748(Obj_1BC748* self, u32* out)
{
    u32 bit = (u32)(self->flags >> 52) & 1;
    *out = bit;
}

extern s32 D_00274744;

void func_001BE998(void);

void func_001BE708(void)
{
    D_00274744 = 0;
    func_001BE998();
}

extern s32 D_00274720;
extern s32 D_00274728;
extern s32 D_0027473C;

void func_001BEB10(void* self);
s32 func_0011CE30(void);
void func_001F6C20(s32 a);
s32 func_0011D598(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

void func_001BEC58(void* self)
{
    func_001BEB10(self);
    if (self == 0) return;
    while (func_0011CE30() != 0 && D_00274720 == 1) {
        func_001F6C20(0);
    }
    if (D_00274720 == 2) {
        s32 h = func_0011D598(D_0027473C, 0, 0x400, -1, 0, 0);
        D_00274728 = h;
        if (h == 0) return;
        D_00274720 = 3;
    }
}

extern u8* D_00275710;

void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);

void func_001BEDF8(void* self)
{
    func_00152600(D_00275710 + 0x1BC4, self);
    func_001B5F28(D_00275710 + 0x1BB8, self);
}

extern u8 D_00604790[];

void func_001F5C0C(u8* p, s32 a, s32 b);
void func_0011CBB8(void);
void func_001BE268(s32 a);
void func_0011DF58(s32 a, s32 b, s32 c, s32 d);
void func_0011D928(s32 a);
void func_001C06D8(void);
void func_0011D520(s32 a, s32 b);
void func_0011D558(s32 a, s32 b, s32 c);
void func_0011E3A0(s32 a, s32 b);

void func_001BF130(void)
{
    func_001F5C0C(D_00604790, 0, 0x1C);
    func_0011CBB8();
    func_001BE268(0);
    func_0011DF58(1, 0x2000, 1, 1);
    func_0011D928(0x14);
    func_001C06D8();
    func_0011D520(0, 1);
    func_0011D558(0, 0, 0x2F);
    func_0011D558(1, 0x18, 0x2F);
    func_0011D558(3, 0x18, 0x2F);
    func_0011D558(2, 0x18, 0x2F);
    func_0011E3A0(2, 4);
}

void* func_001B5EA0(void* p);
void func_001F5C0C(void* p, s32 zero, s32 size);
void func_00152470(void* list, void* item);

void* func_001BF6B8(void)
{
    void* s = func_001B5EA0(D_00275710 + 0x1BA0);
    if (s) {
        func_001F5C0C(s, 0, 0x90);
        func_00152470(D_00275710 + 0x1BAC, s);
    }
    return s;
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_0062C568[];
void func_001B5F28(void* list, void* item);

void func_0011C720(void* item)
{
    func_001B5F28(D_0062C568, item);
}

// The array D_0025C360 is addressed as one symbol; indexing its address keeps retail's lui/addu form.
extern s32 D_0025C380;
extern s32 D_0025C360;
s32 func_0011CE30(void);

void func_0011DDD8()
{
    s32* p = (s32*)((&D_0025C360)[D_0025C380]);
    p[0]++;
    func_0011CE30();
}

extern s32 D_0025C34C;
extern s32 D_0025C388;
s32 func_0011CE30(void);
s32 func_0011E1F8(s32 flag);
s32 func_0011D968(s32 id, s32 size, void* data);

s32 func_0011DF58(s32 a, s32 b, s32 c, s32 d)
{
    s32 buf[4];
    s32 r;
    if (D_0025C34C == 1)
        return 0;
    if (D_0025C388) {
        do {
        } while (func_0011CE30());
    }
    func_0011E1F8(0);
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d;
    r = func_0011D968(0x2A, 0x10, buf);
    D_0025C34C = r;
    return r;
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E010()
{
    func_0011DB00(0x34, 0, 0, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E0B0(s32 a0)
{
    s32 buf = a0;
    func_0011DB00(0x2E, 4, &buf, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E0E0(s32 a0, s32 a1, s32 a2)
{
    s32 buf = a0;
    func_0011DB00(0x4F, 4, &buf, a1, a2);
}

s32 func_0011D968(s32 id, s32 size, void* data);

void func_0011E110(s32 a0)
{
    s32 buf = a0;
    func_0011D968(0x36, 4, &buf);
}

extern s32 D_0025C34C;
s32 func_00203E28(void);
s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

s32 func_0011E2A0()
{
    if (D_0025C34C == 0)
        return func_00203E28();
    func_0011DB00(0x37, 0, 0, 0, 0);
    return 1;
}

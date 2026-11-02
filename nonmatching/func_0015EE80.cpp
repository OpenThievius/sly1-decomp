// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 256/264 (97.0%), checked 2026-11-02
#include "common.h"

struct Frame_15EE80 { u8 pad0[0x4]; s32 f4; u8 pad8[0x4]; s32 fC; u8 pad10[0x38]; };

extern s32 D_002623B8;
extern void* D_002623B0;
extern void* D_002623B4;
extern u32 D_00262314;
extern Frame_15EE80 D_00262320[];
extern Frame_15EE80* D_0026231C;
extern s32 D_00261F18;
extern s32 D_00261F1C;
extern s32 D_002626CC;

void func_0015EDB8(void);
void func_001F6B60(void* p);
void func_0015ED50(Frame_15EE80* f);
void func_001684E8(void);
void func_001686E8(s32 a, s32 b);
void func_0015F320(void);
void func_00202C38(s32 a, s32 b, s32 c);
void func_001F6B40(void* p);
void func_001683E8(void);

void func_0015EE80(void)
{
    func_0015EDB8();
    for (;;) {
        D_002623B8 = 1;
        func_001F6B60(D_002623B0);
        D_002623B8 = 0;
        D_0026231C = &D_00262320[D_00262314];
        D_00262314++;
        if (D_00262314 >= 2) {
            D_00262314 = 0;
        }
        func_0015ED50(D_0026231C);
        func_001684E8();
        func_001686E8(D_00261F18, D_0026231C->fC);
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(D_00261F1C, D_0026231C->f4);
        func_0015F320();
        func_00202C38(D_00261F18, 0, 0);
        func_001F6B40(D_002623B4);
        func_001683E8();
        D_002626CC = 1;
    }
}

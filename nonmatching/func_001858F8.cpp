// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 346/348 (99.4%), checked 2026-11-02
#include "common.h"

extern const u8 D_0024B248[];
extern const u8* D_002647A8[];
void func_00140B60(void* buf, const u8* name, s32 n);
void func_001F7BE8(s32 a);
void func_00203548(s32 a);
s32 func_00140968();
void func_001409A8();
void func_001F8BF8();
s32 func_001F9C50(void* buf);
s32 func_001F9C18();
void func_001F9820();
void func_00203828(s32 a);
void func_00140D68(s32 a);
s32 func_001F9A90(void* buf, s32 a, s32 b);

void func_001858F8()
{
    u8 buf[0x100];
    func_00140B60(buf, D_0024B248, 1);
    func_001F7BE8(0);
    func_00203548(0);
    if (func_00140968() == 0) {
        for (;;) {
        }
    }
    func_001409A8();
    func_001F8BF8();
    while (func_001F9C50(buf) == 0) {
    }
    while (func_001F9C18() == 0) {
    }
    func_001F7BE8(0);
    func_001F9820();
    func_00203548(0);
    if (func_00140968() == 0) {
        for (;;) {
        }
    }
    func_001409A8();
    func_001F8BF8();
    func_00203828(0);
    func_00140D68(1);
    for (u32 i = 0; i < 6; i++) {
        func_00140B60(buf, D_002647A8[i], 1);
        while (func_001F9A90(buf, 0, 0) < 0) {
        }
    }
}

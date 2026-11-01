// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 188/176, checked 2026-11-01
// NEAR: candidate is 188 bytes versus retail 176; saved-register allocation and struct/callback setup still differ.
#include "common.h"

struct Object_18B670 { u8 pad00[4]; s32 handle; void* first; void* second; s32 size; };
struct Config_18B670 { u8 pad00[4]; void (*callback)(void); void* state; s32 size; void* table; s32 mode; u8 pad18[0x18]; };
extern u8 D_002BEA10[];
extern u8 D_002832F0[];
extern s32 D_00275960;
void func_0018B720(Object_18B670*);
void func_001F5C0C(void*, s32, s32);
s32 func_001F6A10(Config_18B670*, s32, s32, s32);
void func_001F6A20(s32, Object_18B670*);
void func_0018B600(void);

void func_0018B670(Object_18B670* self, void* first, void* second)
{
    Config_18B670 config;
    func_0018B720(self);
    self->first = first;
    self->second = second;
    self->size = 0x20;
    func_001F5C0C(&config, 0, 0x30);
    config.callback = func_0018B600;
    config.state = D_002BEA10;
    config.size = 0x4000;
    config.table = D_002832F0;
    config.mode = 3;
    self->handle = func_001F6A10(&config, 0, 0x4000, 3);
    D_00275960 = self->handle;
    func_001F6A20(self->handle, self);
}

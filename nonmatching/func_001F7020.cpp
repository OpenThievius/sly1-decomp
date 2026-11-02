// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 192/216 (88.9%), checked 2026-11-02
#include "common.h"

struct Entry_1F7020 { u8 kind; u8 arg; };
struct Queue_1F7020 { u32 head; u32 pad; Entry_1F7020 e[0x200]; };

extern s32 D_00625B70;
void func_001F6B60(s32 h);
void func_001F6A70(u8 v);
void func_001F6AC0(u8 v);
void func_001F6AF0(u8 v);
extern const char D_0024E988[];
s32 func_001F7B50(const char* fmt, ...);

void func_001F7020(Queue_1F7020* q)
{
    for (;;) {
        func_001F6B60(D_00625B70);
        u32 i = q->head & 0x1FF;
        q->head = i + 1;
        switch (q->e[i].kind) {
        case 0:
            func_001F6AC0(q->e[i].arg);
            break;
        case 1:
            func_001F6A70(q->e[i].arg);
            break;
        case 2:
            func_001F6AF0(q->e[i].arg);
            break;
        default:
            func_001F7B50(D_0024E988);
            break;
        }
    }
}

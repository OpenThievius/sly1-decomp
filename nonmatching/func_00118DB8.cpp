// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the wrapper's frame, helper calls and object accesses match, but
// retail routes the node pointer through v1 and saves the loaded node in s1;
// the current C expression instead uses v0 for the intermediate pointer.
#include "common.h"
struct Quad_118DB8 { s32 w[4]; };
struct Frame_118DB8 { Quad_118DB8 first; Quad_118DB8 second; };
void func_0011B008(Quad_118DB8* q);
void func_0011B018(void* dst, Quad_118DB8* q);
void func_0011B060(Quad_118DB8* q, s32 mode);
void func_0011B0A8(void* dst, void* src);
void func_0011A080(Quad_118DB8* q, void* value, s32 flags);
void* func_0011A400(void* q, void* table, void* key, void* output);
void* func_00118DB8(void* self, void* source, s32 flags)
{
    Frame_118DB8 f;
    func_0011B008(&f.first);
    void* owner = *(void**)((u8*)source + 4);
    void* node = *(void**)((u8*)owner + 8);
    func_0011A080(&f.second, *(void**)((u8*)node + 8), flags);
    func_0011B0A8(&f.first, &f.second);
    func_0011B060(&f.second, 2);
    func_0011A400(&f.second, (void*)flags, *(void**)((u8*)node + 4), &f.first);
    func_0011B0A8(&f.first, &f.second);
    func_0011B060(&f.second, 2);
    func_0011B018(self, &f.first);
    func_0011B060(&f.first, 2);
    return self;
}

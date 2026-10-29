// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: this wrapper's body and calls match, but the source-node pointer
// handoff differs in two registers (retail loads through v1 and saves the node
// in s1). A C-level expression that fixes that allocation is not established.
#include "common.h"
struct Quad_118E80 { s32 w[4]; };
struct Frame_118E80 { Quad_118E80 first; Quad_118E80 second; };
struct Link_118E80 { s32 pad[2]; struct Link_118E80* next; };
struct Owner_11A358 { u8 pad[0x14]; void* head; };
void func_0011B008(Quad_118E80* q);
void func_0011B018(void* dst, Quad_118E80* q);
void func_0011B060(Quad_118E80* q, s32 mode);
void func_0011B0A8(void* dst, void* src);
void func_0011A080(Quad_118E80* q, void* value, s32 flags);
void* func_0011A358(void* self, Owner_11A358* owner, s32 kind, void* body);
void func_0011B0A8(void* dst, void* src);
void* func_00118E80(void* self, void* source, s32 flags)
{
    Frame_118E80 f;
    func_0011B008(&f.first);
    void* owner = *(void**)((u8*)source + 4);
    Link_118E80* node = *(Link_118E80**)((u8*)owner + 8);
    func_0011A080(&f.second, *(void**)((u8*)node + 8), flags);
    func_0011B0A8(&f.first, &f.second);
    func_0011B060(&f.second, 2);
    func_0011A358(&f.second, (Owner_11A358*)flags, *(s32*)((u8*)node + 4), &f.first);
    func_0011B0A8(&f.first, &f.second);
    func_0011B060(&f.second, 2);
    func_0011B018(self, &f.first);
    func_0011B060(&f.first, 2);
    return self;
}

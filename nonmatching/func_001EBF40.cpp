// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 98/108 (90.7%), checked 2026-11-08
// NEAR: order: 25 of 27 instructions line up; s2 and s3 (self and the loop counter) are swapped.
//       Eight source variants did not move them.
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
// Tried (order-class pass): a local for the out pointer, a do/while, pointer walks over both arrays, i declared outside, a result local: s2/s3 stay swapped.
#include "common.h"
#include "switched_collider.h"

s32 D_00275CF8[4] = { 1247, 1248, 1249, 1250 };
s32 ResolveAgentClip(void* self, s32 id);
void LoadAgent(void* self);
void LoadTempoAgent(TempoAgent* self)
{
    LoadAgent(self);
    for (s32 i = 0; i < 4; i++) {
        self->fC10[i] = ResolveAgentClip(self, D_00275CF8[i]);
    }
}

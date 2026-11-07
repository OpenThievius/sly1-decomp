// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 232/184, checked 2026-11-06
// NEAR: append/copy behavior is modeled, but the candidate is larger and its frame and argument scheduling differ.
#include "common.h"

struct Header_13F1D8 { s32 words[12]; };
struct Object_13F1D8 { u8 pad000[0x7E0]; s32 count; u8 pad7E4[0xC]; u8 entries[1]; };
s32 MatchesObjectId(void*, s32);
void MoveMemory(void*, void*, s32);
void AddTriggerZoneRotation(Object_13F1D8* self, void* input, Header_13F1D8* header)
{
    s32 index = self->count;
    s32 available = MatchesObjectId(input, 0x200);
    if (available && index > 0) {
        MoveMemory(self->entries, self->entries, index * 0x30);
        index = 0;
    }
    Header_13F1D8* slot = (Header_13F1D8*)(self->entries + index * 0x30);
    *slot = *header;
    ++self->count;
}

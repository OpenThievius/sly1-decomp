// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the first entry is 0x574 in and the entries are 0x570 apart (US 0x264 and 0x260).
typedef void (*VFn2_14AD00)(void* self, s32 arg);
void SetScreenElementClock(void* self, s32 arg);
void UpdateItemColumn(u8* self, s32 arg)
{
    SetScreenElementClock(self, arg);
    self += 0x574;
    for (u32 i = 0; i < 4; i++) {
        (*(VFn2_14AD00**)self)[17](self, arg);
        self += 0x570;
    }
}

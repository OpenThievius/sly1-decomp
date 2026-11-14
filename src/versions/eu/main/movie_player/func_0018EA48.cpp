// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: sets a second field to -1, blocks at 0x30/0x50 and ResetIopRingSink at 0x70
struct Obj_18EA48_eu { s32 flag; s32 f4; u8 pad0[0x30 - 8]; };
void ResetIopRingSink(void* self);
void ResetMovieStream(MovieStream* self_)
{
    Obj_18EA48_eu* self = (Obj_18EA48_eu*)self_;
    if (self->flag != 0) {
        ResetIopRing();
        self->flag = 1;
        self->f4 = -1;
        ResetRingBuffer((RingBuffer*)((u8*)self + 0x30));
        ResetRingBuffer((RingBuffer*)((u8*)self + 0x50));
        ResetIopRingSink((u8*)self + 0x70);
    }
}

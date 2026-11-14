// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields moved (block at 0x50, count at 0x94), a 0x10 type case with an extra start call, and a PAL-only call in state 3.
struct Self_18EB98_eu {
    s32 state;
    u8 pad4[0x50 - 4];
    RingBuffer f50;
    u8 pad70[4];
    s32 f74;
    s32 f78;
    s32 f7C;
    u8 pad80[4];
    s32 f84;
    s32 f88;
    u8 pad8C[8];
    s32 f94;
};

struct Obj_eu_18F210;
void UpdateIopRingSinkByKind(Obj_eu_18F210* p);

void UpdateMovieStream(MovieStream* self_)
{
    Self_18EB98_eu* self = (Self_18EB98_eu*)self_;
    switch (self->state) {
    case 2:
        DrainRingBuffer(&self->f50, self->f94, (StreamSink*)((u8*)&self->f50 + 0x20));
        if (self->f94 != 0) {
            break;
        }
        if (self->f74 == 0x10) {
            UpdateIopMovieStream(self->f84, 0x1000, 0, self->f78, self->f7C);
        } else {
            UpdateIopMovieStream(self->f84, self->f88, self->f84, 0, 0);
        }
        self->state = 3;
        break;
    case 3: {
        void* s0 = (u8*)&self->f50 + 0x20;
        UpdateIopRingSinkByKind((Obj_eu_18F210*)s0);
        DrainRingBuffer(&self->f50, self->f94, (StreamSink*)s0);
        break;
    }
    }
}

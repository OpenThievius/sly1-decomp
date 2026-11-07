// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the read loop also handles status 1 (func_0018EB98 on the object at +0x80) and stops on status 2.

s32 func_0018ECA8(void* u0, void* u1, MoviePlayer* self)
{
    while (self->videoRing.filled < 0x1000) {
        s32 r = FeedMovieDecoder(self, 1);
        if (r == 2) {
            u8 zero[0x40];
            func_001F5C0C(zero, 0, 0x40);
            s32 k = self->videoRing.filled;
            FillRingBufferFromMemory(&self->videoRing, 0x40 - (k % 32), zero);
            break;
        }
        if (r == 1) {
            UpdateMovieStream(&self->stream);
        }
    }
    {
        IpuDmaSink dma;
        ConsumeSpan(&self->videoRing, 0);
        DrainRingBuffer(&self->videoRing, 0, &dma);
    }
    return 1;
}

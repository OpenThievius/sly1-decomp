// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the read loop also handles status 1 (func_0018EB98 on the object at +0x80) and stops on status 2.

s32 func_0018ECA8(void* u0, void* u1, Obj_18ECA8* self)
{
    while (self->f74 < 0x1000) {
        s32 r = func_0018F890((Object_18F890*)self, 1);
        if (r == 2) {
            u8 zero[0x40];
            func_001F5C0C(zero, 0, 0x40);
            s32 k = self->f74;
            func_0013CC00(&self->sub, 0x40 - (k % 32), zero);
            break;
        }
        if (r == 1) {
            func_0018EB98((Self_18EB98*)((u8*)self + 0x80));
        }
    }
    {
        Dma_18E8C8 dma;
        func_0013CC48(&self->sub, 0);
        func_0013CAD8(&self->sub, 0, &dma);
    }
    return 1;
}

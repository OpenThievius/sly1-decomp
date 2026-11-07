// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL runs at 50 Hz (50.0f) and uses a 468.61017f screen height.
void func_00168B68(f32 t)
{
    Frame_168B68 f;
    s32 i = 0;
    s32 n;

    InitGifPacket(&f);
    n = (s32)(t * 50.0f);
    SignalDisplaySync();
    D_002626CC = 0;
    if (n > 0) {
        do {
            f32 x = ((f32)i + 1.0f) / (f32)n;
            f32 y = x * 255.0f;
            s32 v = (s32)(x * y);
            i++;
            UsePacketBufferMemory(&f, 0x40, &f.value);
            BeginDmaTag(&f);
            WriteColoredSpritePacket(0.0f, 0.0f, 640.0f, 468.61017f, 0, 0, 0, v, &f);
            BeginGifTag(&f, 0, 1, 0xE);
            AddGifRegisterWrite(&f, 0x61, 0);
            EndGifPacket(&f);
            AddDmaEndTag(&f);
            DetachPacketBuffer(&f, 0, 0);
            SendGsPacketAndWait(g_gifChannel, &f.value);
            FlipDisplayFrame();
        } while (i < n);
    }
}

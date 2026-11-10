// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the blit covers a 256-line field where US's covers 224: the two SCISSOR heights, the
// sprite's Y coordinates and its texture's V differ.

void BlitFrameToDisplay(void)
{
    PacketWriter w;
    Quad16 buf[100];
    InitGifPacket(&w);
    UsePacketBufferMemory(&w, 100, buf);
    BeginDmaTag(&w);
    BeginGifTag(&w, 0, 1, 0xE);
    u64 frame = *(u64*)((g_displayFrameCounter & 1) ? D_002625F0 : D_00262500);
    AddGifRegisterWrite(&w, 0x3F, (u64)0);
    AddGifRegisterWrite(&w, 0x4E, FrameBits(frame) | ((u64)1 << 32));
    u64 disp = *(u64*)((g_displayFrameCounter & 1) ? D_002624F0 : D_002625E0);
    AddGifRegisterWrite(&w, 6, ((disp & 0x1FF) << 5) | (((disp >> 16) & 0x3F) << 14) | (((disp >> 24) & 0x3F) << 20) | 0x2A8000000ULL);
    AddGifRegisterWrite(&w, 0x14, (u64)0x61);
    AddGifRegisterWrite(&w, 8, (u64)5);
    AddGifRegisterWrite(&w, 0x47, (u64)0x30002);
    AddGifRegisterWrite(&w, 0x42, 0x3000000064ULL);
    AddGifRegisterWrite(&w, 1, 0x3F80000080808080ULL);
    AddGifRegisterWrite(&w, 0x40, 0xFE0001027F0000ULL);
    BeginGifTag(&w, 0x156, 2, 0x43);
    s32 v = (D_002626C8 & 1) ? 0 : 8;
    for (s32 x = 0; x < 0x280; x += 0x20) {
        AddGifUvEntry(&w, x << 4, v);
        AddGifXyzfEntry(&w, (x + 0x6C0) << 4, 0x7800, 0, 0);
        AddGifUvEntry(&w, (x + 0x20) << 4, v + 0x1000);
        AddGifXyzfEntry(&w, (x + 0x6E0) << 4, 0x8800, 0, 0);
    }
    BeginGifTag(&w, 0, 1, 0xE);
    AddGifRegisterWrite(&w, 0x4E, FrameBits(frame));
    AddGifRegisterWrite(&w, 0x40, 0xFF0000027F0000ULL);
    BeginGifTag(&w, 0, 1, 0xE);
    AddGifRegisterWrite(&w, 0x61, (u64)0);
    EndGifPacket(&w);
    AddDmaEndTag(&w);
    CloseDmaTag(&w);
    SendGsPacketAndWait(g_gifChannel, (s32)buf);
}

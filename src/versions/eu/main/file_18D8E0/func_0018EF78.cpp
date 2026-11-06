// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two func_001615F0 calls pass 0x7800 and 0x8800 where US passes 0x7900 and 0x8700.
void func_0018EF78(void* self, s32 a1, s32 a2)
{
    Local_18EF78 buf;
    InitGifPacket(&buf);
    UsePacketBufferMemory(&buf, 0x12, self);
    BeginDmaTag(&buf);
    BeginGifTag(&buf, 6, 1, 0xE);
    AddGifRegisterWrite(&buf, 6, 0x0AA8029E00ULL);
    AddGifRegisterWrite(&buf, 0x14, 0x61);
    AddGifRegisterWrite(&buf, 8, 5);
    AddGifRegisterWrite(&buf, 0x42, 0x44);
    AddGifRegisterWrite(&buf, 0x47, 0x31001);
    BeginGifTag(&buf, 0x116, 5, 0xE4343);
    AddGifUvEntry(&buf, 8, 8);
    AddGifXyzfEntry(&buf, 0x6C00, 0x7800, 0, 0);
    AddGifUvEntry(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    AddGifXyzfEntry(&buf, 0x9400, 0x8800, 0, 0);
    AddGifRegisterWrite(&buf, 0x61, 0);
    EndGifPacket(&buf);
    AddDmaEndTag(&buf);
    DetachPacketBuffer(&buf, 0, 0);
}

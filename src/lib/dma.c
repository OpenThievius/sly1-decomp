/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The DMA library, one object in retail from 0x202768 to 0x202D08: the table of the EE's ten
 * DMA channels, the reset of the controller and its settings, the start of a channel's transfer
 * and the wait for its end. Its .data holds the table of channels, the library's identification
 * string, which channels the reset clears, the controller's priority codes and the last
 * settings; its .rodata the one message of its three waits. The linker stripped three of its
 * functions and left remnants of them. C, built by the cc1 of 2.9-ee-991111 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "asm_func.h"

/* A channel's register block: CHCR, MADR, QWC, TADR and the address registers after them,
 * every 0x10 bytes; CHCR's bit 8 (STR) is set while the channel transfers. */
typedef struct DmaChannel {
    volatile s32 chcr;
    u8 pad04[0x0C];
    s32 madr;
    u8 pad14[0x0C];
    s32 qwc;
    u8 pad24[0x0C];
    u32 tadr;
    u8 pad34[0x0C];
    s32 asr0;
    u8 pad44[0x0C];
    s32 asr1;
    u8 pad54[0x2C];
    s32 sadr;
} DmaChannel;

/* The controller's settings, as the reset gives them and the last set keeps them. */
typedef struct DmaSettings {
    u8 release;
    u8 mfifo;
    u8 stall;
    u8 stall_drain;
    u16 e;
    u16 f;
    u16 g;
    u16 h;
    void* ring;
    u32 hold;
} DmaSettings;

DmaChannel* g_dmaChannels[10] = {
    (DmaChannel*)0x10008000, (DmaChannel*)0x10009000, (DmaChannel*)0x1000A000, (DmaChannel*)0x1000B000,
    (DmaChannel*)0x1000B400, (DmaChannel*)0x1000C000, (DmaChannel*)0x1000C400, (DmaChannel*)0x1000C800,
    (DmaChannel*)0x1000D000, (DmaChannel*)0x1000D400,
};
/* On 16 bytes, as retail has it after the table's 8 bytes of padding. */
char D_00279370[16] __attribute__((aligned(16))) = "PsIIlibdma  2400";
s32 g_dmaChannelsToReset[10] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
u8 D_002793A8[16] = { 0, 0, 0, 3, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };
u8 D_002793B8[16] = { 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
u8 D_002793C8[16] = { 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
DmaSettings g_dmaSettings = { 0 };
u32 D_002793F0[4] = { 0 };

s32 PrintFormatted(const char* format, ...);
s32 SetDmaSettings(DmaSettings* c);

void ClearBytes(u8* p, s32 n)
{
    s32 i = n - 1;
    if (n != 0) {
        do {
            *p = 0;
            i--;
            p++;
        } while (i != -1);
    }
}

DmaChannel* GetDmaChannel(u32 index)
{
    if (index < 10)
        return g_dmaChannels[index];
    return 0;
}

s32 ResetDmaController(s32 mode)
{
    DmaSettings settings;
    s32 flag = *(volatile u32*)0x1000E000 & 1;
    s32 i;
    u32 m;

    for (i = 0; i < 10; i++) {
        if (g_dmaChannelsToReset[i] != 0) {
            DmaChannel* p = g_dmaChannels[i];
            p->chcr = 0;
            p->tadr = 0;
            p->madr = 0;
            p->asr1 = 0;
            p->asr0 = 0;
            p->sadr = 0;
        }
    }
    *(volatile u32*)0x1000E010 = 0xFF1F;
    m = *(volatile u32*)0x1000E010 & 0xFF1F0000;
    *(u32*)0x1000E010 = m;
    ClearBytes((u8*)&settings, 0x14);
    SetDmaSettings(&settings);
    if (mode == 1) {
        volatile u32* p = (volatile u32*)0x1000E000;
        *p |= 1;
    }
    return flag;
}

s32 SetDmaSettings(DmaSettings* c)
{
    u32 r = *(volatile u32*)0x1000E000;
    u32 w20 = *(volatile u32*)0x1000E020;
    u32 w30 = *(volatile u32*)0x1000E030;
    u32 w50 = *(volatile u32*)0x1000E050;
    u32 w40 = *(volatile u32*)0x1000E040;
    if (c->release >= 10) return -1;
    if (c->mfifo >= 10) return -2;
    if (c->stall >= 10) return -3;
    if (c->stall_drain >= 7) return -4;
    r = (r & ~0x30u) | (D_002793A8[c->release] << 4);
    r = (r & ~0xC0u) | (D_002793B8[c->mfifo] << 6);
    r = (r & ~0xCu) | (D_002793C8[c->stall] << 2);
    if (c->stall_drain) {
        r |= 2;
        r = (r & ~0x300u) | ((c->stall_drain - 1) << 8);
    } else {
        r &= ~2u;
    }
    w20 = (c->e << 16) | c->f;
    w30 = (c->h << 16) | c->g;
    w40 = c->hold;
    *(volatile u32*)0x1000E000 = r;
    *(volatile u32*)0x1000E020 = w20;
    w50 = (u32)c->ring;
    *(volatile u32*)0x1000E030 = w30;
    *(volatile u32*)0x1000E050 = w50;
    *(volatile u32*)0x1000E040 = w40;
    g_dmaSettings = *c;
    return 0;
}

void StartDmaChain(DmaChannel* ch, u32 tadr)
{
    s32 timeout = 0x1000000;
    s32 cur;
    s32 next;

    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            PrintFormatted("libdma: sync timeout\n");
            cur = ch->chcr;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    if (ch->tadr != 0xFFFFFFFF) {
        ch->tadr = tadr;
    }
    ch->qwc = 0;
    ch->chcr = (ch->chcr & ~0xC) | 0x105;
}

LINKER_REMNANT(func_00202B58);

void StartDmaChainToMemory(DmaChannel* ch)
{
    s32 timeout = 0x1000000;
    s32 cur;
    s32 next;

    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            PrintFormatted("libdma: sync timeout\n");
            cur = ch->chcr;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    ch->qwc = 0;
    ch->chcr = ((((ch->chcr & ~0xC) | 0x4) & ~0x1) | 0x100);
}

LINKER_REMNANT(func_00202C30);

s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout)
{
    s32 cur;
    s32 next;

    if (mode == 1) {
        return ((u32)ch->chcr >> 8) & 1;
    }
    if (timeout == 0) {
        timeout = 0x1000000;
    }
    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            PrintFormatted("libdma: sync timeout\n");
            cur = ch->chcr;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    return 0;
}

LINKER_REMNANT(func_00202D00);

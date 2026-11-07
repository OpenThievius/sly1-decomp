// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: thread body that loops forever, stepping the frame state and running a three-phase update, with every third pass skipping the final one.
struct Glob_eu_18EBE8 {
    u8 pad0[0x128];
    s32 f128;
    s32 f12C;
    u8 pad130[0x144 - 0x130];
    s32 f144;
    volatile s32 f148;  // state word another thread reads
};

extern Glob_eu_18EBE8 D_eu_0026AC60;
extern s32 D_eu_0026321C;
s32 AwaitSemaphore(s32 a);
void SendGsPacketAndWait(s32 a, s32 b);
void ApplyPendingDisplayFlip(void);
void FlipDisplayFrame(void);

void func_eu_0018EBE8(void)
{
    s32 i = 0;
    Glob_eu_18EBE8* g = &D_eu_0026AC60;
    for (;;) {
        i++;
        g->f148 = 0;
        AwaitSemaphore(g->f144);
        g->f148 = 1;
        SendGsPacketAndWait(D_eu_0026321C, g->f128);
        g->f148 = 2;
        ApplyPendingDisplayFlip();
        SendGsPacketAndWait(D_eu_0026321C, g->f12C);
        FlipDisplayFrame();
        if (i % 3 != 0) {
            SendGsPacketAndWait(D_eu_0026321C, g->f12C);
            FlipDisplayFrame();
        }
    }
}

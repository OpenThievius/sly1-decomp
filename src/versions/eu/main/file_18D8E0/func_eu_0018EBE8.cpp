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
s32 func_001F6B60(s32 a);
void func_001686E8(s32 a, s32 b);
void func_001684E8(void);
void func_001683E8(void);

void func_eu_0018EBE8(void)
{
    s32 i = 0;
    Glob_eu_18EBE8* g = &D_eu_0026AC60;
    for (;;) {
        i++;
        g->f148 = 0;
        func_001F6B60(g->f144);
        g->f148 = 1;
        func_001686E8(D_eu_0026321C, g->f128);
        g->f148 = 2;
        func_001684E8();
        func_001686E8(D_eu_0026321C, g->f12C);
        func_001683E8();
        if (i % 3 != 0) {
            func_001686E8(D_eu_0026321C, g->f12C);
            func_001683E8();
        }
    }
}

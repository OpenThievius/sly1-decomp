// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: sets up two words of the movie object, clears a 0x30-byte record, fills it with a callback and two tables, and registers it.
struct Head_eu_18ECA8 { u8 pad0[0xC]; s32 f0C; };

extern u8 D_eu_002CC280[];
extern u8 D_eu_0028CA70[];
extern s32 D_eu_0027F0DC;
void RunMovieDecodeThread(void);

void CreateMovieDecodeThread(void)
{
    ThreadParams l;
    s32 v;

    D_eu_0026AC60.f144 = CreateLockSemaphore(0, (void*)1);
    ((Head_eu_18ECA8*)&D_eu_0026AC60)->f0C = 0;
    (void)FillMemory(&l, 0, sizeof(l));
    l.entry = RunMovieDecodeThread;
    l.stack = D_eu_002CC280;
    l.gp = D_eu_0028CA70;
    l.stackSize = 0x1000;
    l.priority = 2;
    v = MakeThread(&l);
    D_eu_0027F0DC = v;
    RunThread(v, 0);
}

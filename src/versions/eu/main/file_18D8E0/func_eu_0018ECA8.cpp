// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: sets up two words of the movie object, clears a 0x30-byte record, fills it with a callback and two tables, and registers it.
struct Head_eu_18ECA8 { u8 pad0[0xC]; s32 f0C; };

extern u8 D_eu_002CC280[];
extern u8 D_eu_0028CA70[];
extern s32 D_eu_0027F0DC;
void func_eu_0018EBE8(void);

void func_eu_0018ECA8(void)
{
    Init_18E5E8 l;
    s32 v;

    D_eu_0026AC60.f144 = func_001E2268((Init_18E5E8*)0, (void*)1);
    ((Head_eu_18ECA8*)&D_eu_0026AC60)->f0C = 0;
    (void)func_001F5C0C(&l, 0, sizeof(l));
    l.f04 = func_eu_0018EBE8;
    l.f08 = (s32)D_eu_002CC280;
    l.f10 = (s32)D_eu_0028CA70;
    l.f0C = 0x1000;
    l.f14 = 2;
    v = func_001F6A10(&l);
    D_eu_0027F0DC = v;
    func_001F6A20((Mgr_18E5E8*)v, 0);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: picks a sound through func_eu_001DE018 (by id) where US takes a slot address from a table.
// D_eu_00275374 is US D_0026FCF4, at an address the tools do not pair.

struct Gl_eu_16B300 { u8 pad[0x578]; f32 f578; };
extern s32 D_eu_00263BC0[];
extern s32 D_eu_00275374;
ChoiceSound* func_eu_001DE018(s32 id);

void func_0016B300(Self_16B300* self, s32 a, s32 b)
{
    if (a == self->f2D0 && b == self->f2D4) return;
    if (a != self->f300 && a > 0) {
        ChoiceSound* slot = 0;
        if (g_saveData->levels[a].f448 & 1) {
            if (!(g_saveData->f19EC & 2)) {
                slot = func_eu_001DE018(5);
                g_saveData->f19EC |= 2;
            }
        } else {
            Gl_eu_16B300* gp = (Gl_eu_16B300*)&D_0026FA90;
            if (D_00262970 <= g_gameClock[1] - gp->f578) {
                slot = func_eu_001DE018(D_eu_00263BC0[a]);
                gp->f578 = g_gameClock[1];
            }
        }
        if (slot) {
            OpenKeyRecord(slot);
            D_eu_00275374 = HasStreamVoice();
        }
    }
    void* h = self->f2E0;
    if (h) {
        if (self->f2D0 == -1) {
            if (a != 0) {
                TeleportStateWalker(h, D_00262860[a].targetKey);
                SetStateWalkerTarget(self->f2E0, D_00262860[a].walkerKey);
            }
        } else {
            SetStateWalkerTarget(h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->f2D0 = a;
    self->f2D4 = b;
    self->f2D8 = g_gameClock[1];
}

// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: picks a sound through func_eu_001DE018 (by id) where US takes a slot address from a table.
// D_eu_00275374 is US D_0026FCF4, at an address the tools do not pair.

struct Gl_eu_16B300 { u8 pad[0x578]; f32 f578; };
extern s32 D_eu_00263BC0[];
extern s32 D_eu_00275374;
ChoiceSound* GetLoadedKeyRecord(s32 id);

void SetCurrentObjectChoice(CurrentPlacedObject* self, s32 a, s32 b)
{
    if (a == self->choice && b == self->keyIndex) return;
    if (a != self->walkerChoice && a > 0) {
        ChoiceSound* slot = 0;
        if (g_saveData->levels[a].f448 & 1) {
            if (!(g_saveData->optionFlags & 2)) {
                slot = GetLoadedKeyRecord(5);
                g_saveData->optionFlags |= 2;
            }
        } else {
            Gl_eu_16B300* gp = (Gl_eu_16B300*)&D_0026FA90;
            if (D_00262970 <= g_gameClock[1] - gp->f578) {
                slot = GetLoadedKeyRecord(D_eu_00263BC0[a]);
                gp->f578 = g_gameClock[1];
            }
        }
        if (slot) {
            OpenKeyRecord((KeyRecord*)slot);
            D_eu_00275374 = HasStreamVoice();
        }
    }
    void* h = self->walkers[0].walker;
    if (h) {
        if (self->choice == -1) {
            if (a != 0) {
                TeleportStateWalker((StateWalker*)h, D_00262860[a].targetKey);
                SetStateWalkerTarget(self->walkers[0].walker, D_00262860[a].walkerKey);
            }
        } else {
            SetStateWalkerTarget((StateWalker*)h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->choice = a;
    self->keyIndex = b;
    self->choiceTime = g_gameClock[1];
}

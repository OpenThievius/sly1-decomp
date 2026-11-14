// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f328 is at 0x5B4 (US 0x328).
extern const f32 D_00249CFC;  // the FLT_MAX US writes as a literal, at its PAL address
struct Self_135F48_eu {
    u8 pad000[0x5B4];
    s32 f5B4;
};

void ReleasePanelEntries(Self_135F48_eu* self, s32 state, s32 flag);
void CollectPanelEntriesOfClass(Self_135F48_eu* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);

void RefreshPanelEntries(Self_135F48_eu* self, PadRecord* pad)
{
    LevelBit flag;
    GetCurrentLevelBit((u32*)&flag);
    if ((MaskWorldBitsBySave() & flag.v) == 0) {
        ReleasePanelEntries(self, 0, 1);
        return;
    }
    ReleasePanelEntries(self, 1, 0);
    if (self->f5B4 == 1) {
        f32 k = D_00249CFC;
        World* world = g_currentWorld;
        CollectPanelEntriesOfClass(self, 0x2E, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)world->slot1CE8[23], k);
        CollectPanelEntriesOfClass(self, 0x21, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)(g_currentWorld)->slot1CE8[27], k);
    }
}

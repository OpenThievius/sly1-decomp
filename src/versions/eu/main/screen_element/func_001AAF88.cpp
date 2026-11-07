// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields from f214 on sit 784 (0x310) bytes further on than in US.
struct Obj_1AAF88_eu {
    u8 pad000[4];
    u32 f004;
    u8 pad008[0x20C + 0x310];
    s32 f214;
    u8 pad218[0x48];
    s32 f260;
    void* f264;
    void* f268;
    f32 f26C;
};

void func_001AA268(Obj_1AAF88_eu* self);

void func_001AAF88(Obj_1AAF88_eu* self)
{
    SetupScreenElementText(self);
    self->f004 = (u32)GetFontById(2);
    self->f260 = -1;
    self->f26C = 6000.0f;
    switch (self->f214) {
    case 3:
        self->f264 = &g_saveData->f19E0;
        break;
    case 4:
        self->f264 = &g_currentEntry->count64;
        self->f268 = &g_currentWorld->count2300;
        break;
    case 5:
        self->f264 = &g_currentLevelRecord->f438;
        break;
    case 6:
        self->f264 = &g_saveData->f19E8;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->f264 = &self->f260;
        break;
    }
}

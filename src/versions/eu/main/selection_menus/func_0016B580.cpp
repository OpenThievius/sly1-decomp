// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f250, p260 and f264 sit 784 (0x310) bytes further on than in US; from f2D0 on nothing moves.
struct Obj_16B580_eu {
    u8 pad0[0x2D0];
    s32 f2D0;
    s32 f2D4;
    f32 f2D8;
    u8 pad2DC[4];
    StateWalker* f2E0;
    u8 pad2E4[0x308 - 0x2E4];
    void* f308;
    u8 pad30C[0x33C - 0x30C];
    void* f33C;
    u8 pad340[0x250 + 0x310 - 0x340];
    s32 f250;
    u8 pad254[0xC];
    Obj_16B580_eu* p260;
    s32 f264;
};

void ShowCurrentObjectCaptions(Obj_16B580_eu* o);
void ConfirmCurrentObjectChoice(Obj_16B580_eu* o);
void MoveCurrentObjectChoice(Obj_16B580_eu* o, PadRecord* a);

void HandleSelectionCaptionInput(Obj_16B580_eu* self, PadRecord* arg)
{
    if (self->p260 == 0) {
        return;
    }
    if (self->p260->f2E0 == 0) {
        return;
    }
    if (self->f264 != 0) {
        if (CheckStreamVoicePending() != 0) {
            PollIopCommands();
        }
        self->f264 = HasStreamVoice();
    }
    if (D_00272420 != 0) {
        return;
    }
    if (D_0027051C != 0) {
        return;
    }
    self = self->p260;
    StateWalker* p = self->f2E0;
    if (self->f308 != 0) {
        if (self->f308 == self->f33C) {
            StartMemoryCardSave((MemoryCard*)g_memoryCard);
        }
        ChooseStepSequenceState((StepSequence*)self->f308);
        self->f308 = 0;
    }
    ShowCurrentObjectCaptions(self);
    f32 delay = 0.3f;
    if (self->f2D4 == 1 && (p->currentEntry == p->index || delay <= g_gameTime[0] - self->f2D8)) {
        s32 idx = self->f2D0;
        if (idx == 0) {
            Obj_16B580_eu* g = (Obj_16B580_eu*)&D_0026FD00;
            if (g->f250 != 0) {
                return;
            }
            PushStackElement((ElementStack*)g_elementStack, &D_0026FD00);
            return;
        }
        Obj_16B580_eu* g = (Obj_16B580_eu*)&g_mapScreenList;
        if (g->f250 != 0) {
            return;
        }
        g->p260 = *(Obj_16B580_eu**)((u8*)&g_mapScreenList + idx * 4 + 0x264 + 0x310);
        PushStackElement((ElementStack*)g_elementStack, &g_mapScreenList);
        return;
    }
    if (p->currentEntry != p->index) {
        return;
    }
    if ((arg->flags & 0x800) || (arg->connectionMode == 1 && 5.0f <= g_gameTime[0])) {
        ClearPadPressedBits(arg, 0x800);
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x17);
        return;
    }
    if ((arg->flags & 0x140) != 0) {
        ClearPadPressedBits(arg, 0x140);
        ConfirmCurrentObjectChoice(self);
        return;
    }
    MoveCurrentObjectChoice(self, arg);
}

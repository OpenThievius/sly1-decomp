// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the last choice open counts down while the record before it lacks 0x20 and its own lacks 1
// (US looks one record lower), the start choice falls back one record at most, and the walkers
// always start at choice 0.
void SetupCurrentObjectChoices(CurrentPlacedObject* self)
{
    if (self->walkers[0].graph) self->walkers[0].walker = CreateStateWalker((StateGraph*)self->walkers[0].graph, 0, -1, 0);
    if (self->walkers[1].graph) self->walkers[1].walker = CreateStateWalker((StateGraph*)self->walkers[1].graph, 0, -1, 0);
    if (self->walkers[2].graph) self->walkers[2].walker = CreateStateWalker((StateGraph*)self->walkers[2].graph, 0, -1, 0);
    if (self->walkers[3].graph) self->walkers[3].walker = CreateStateWalker((StateGraph*)self->walkers[3].graph, 0, -1, 1);
    self->lastChoice = 5;
    for (;;) {
        s32 c = self->lastChoice;
        if (c < 2) break;
        s32 d = c - 1;
        if (g_saveData->levels[d].f448 & 0x20) break;
        if (g_saveData->levels[c].f448 & 1) break;
        self->lastChoice = d;
    }
    for (s32 i = 1; i <= self->lastChoice; i++) {
        StateTrigger* o = self->levelObjects[i - 1];
        if (o && (g_saveData->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->pendingSequence = 0;
    for (s32 i = 0; i < 4; i++) {
        ChoiceSequence* c = self->sequences[i];
        if (c && *c->flagp == 0) {
            s32 v = 0;
            switch (i) {
            case 0: v = 1; break;
            case 1: v = ComputeCompletionMask() >> 1; v &= 1; break;
            case 2: v = ComputeCompletionMask() >> 2; v &= 1; break;
            case 3: v = ComputeCompletionMask() >> 3; v &= 1; break;
            }
            if (v) {
                self->pendingSequence = c;
                break;
            }
        }
    }
    s32 idx;
    if (self->pendingSequence) {
        idx = 0;
    } else if (g_previousLevelIndex != -1 && (g_saveData->levels[g_previousLevelIndex].f448 & 1)) {
        idx = g_previousLevelIndex;
    } else {
        s32 c = self->lastChoice;
        idx = c;
        if ((g_saveData->levels[c].f448 & 1) == 0) idx = c - 1;
    }
    SetCurrentObjectChoice(self, idx, 0);
    if (self->walkers[2].walker || self->walkers[3].walker) {
        self->walkerChoice = 0;
        if (self->walkers[2].walker) {
            s32 key = D_00262860[self->walkerChoice].walkerKey;
            TeleportStateWalker(self->walkers[2].walker, key);
        }
        if (self->walkers[3].walker) {
            s32 key = D_00262860[self->walkerChoice].walkerKey;
            TeleportStateWalker(self->walkers[3].walker, key);
        }
    }
    PushStackElement((ElementStack*)g_elementStack, &D_0026FA90);
}

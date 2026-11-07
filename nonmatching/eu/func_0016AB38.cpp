// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 808/812 (99.5%), checked 2026-11-06
// NEAR (PAL, func_0016AB38 at PAL 0x16B190): PAL's own definition, built in src/main/file_16AA18.cpp's unit
// (python3 tools/check.py nonmatching/eu/func_0016AB38.cpp func_0016AB38 --unit src/main/file_16AA18.cpp).
// 2 instructions differ: GCSE hoists the high halves of D_00275BC0 and D_0026FA90 (the last
// call's arguments) to the entry, and retail has D_00275BC0's first, in s7. The two pseudos tie
// in global allocation (one use each), so the lower pseudo number wins s7, and GCSE numbers and
// places them by the hash of the symbols' name strings modulo a table sized by the function:
// this form puts D_00275BC0's in s7 but second; without the `cap` local it comes first but in fp
// (5 lines). 32 combinations of natural rewrites elsewhere did not give both.
void func_0016AB38(CurrentPlacedObject* self)
{
    if (self->walkers[0].graph) self->walkers[0].walker = func_001B6290(self->walkers[0].graph, 0, -1, 0);
    if (self->walkers[1].graph) self->walkers[1].walker = func_001B6290(self->walkers[1].graph, 0, -1, 0);
    if (self->walkers[2].graph) self->walkers[2].walker = func_001B6290(self->walkers[2].graph, 0, -1, 0);
    if (self->walkers[3].graph) self->walkers[3].walker = func_001B6290(self->walkers[3].graph, 0, -1, 1);
    self->lastChoice = 5;
    for (;;) {
        s32 c = self->lastChoice;
        if (c < 2) break;
        s32 d = c - 1;
        if (D_002623C0->levels[d].f448 & 0x20) break;
        if (D_002623C0->levels[c].f448 & 1) break;
        self->lastChoice = d;
    }
    for (s32 i = 1; i <= self->lastChoice; i++) {
        StateTrigger* o = self->levelObjects[i - 1];
        if (o && (D_002623C0->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->pendingSequence = 0;
    for (s32 i = 0; i < 4; i++) {
        ChoiceSequence* c = self->sequences[i];
        if (c && *c->flagp == 0) {
            s32 v = 0;
            switch (i) {
            case 0: v = 1; break;
            case 1: v = func_001602A0() >> 1; goto mask;
            case 2: v = func_001602A0() >> 2; goto mask;
            case 3: v = func_001602A0() >> 3;
            mask: v &= 1; break;
            default: break;
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
    } else {
        s32 a = D_002623CC;
        if (a != -1 && (D_002623C0->levels[a].f448 & 1)) {
            idx = a;
        } else {
            s32 c = self->lastChoice;
            idx = c;
            if ((D_002623C0->levels[c].f448 & 1) == 0) idx = c - 1;
        }
    }
    func_0016B300(self, idx, 0);
    if (self->walkers[2].walker || self->walkers[3].walker) {
        self->walkerChoice = 0;
        if (self->walkers[2].walker) func_001B6628(self->walkers[2].walker, D_00262860[self->walkerChoice].walkerKey);
        if (self->walkers[3].walker) func_001B6628(self->walkers[3].walker, D_00262860[self->walkerChoice].walkerKey);
    }
    u8* cap = (u8*)&D_0026FA90;
    func_001E9498(D_00275BC0, cap);
}

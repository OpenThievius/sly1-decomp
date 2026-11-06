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
void func_0016AB38(Self_16AB38* self)
{
    if (self->p[0].src) self->p[0].dst = func_001B6290(self->p[0].src, 0, -1, 0);
    if (self->p[1].src) self->p[1].dst = func_001B6290(self->p[1].src, 0, -1, 0);
    if (self->p[2].src) self->p[2].dst = func_001B6290(self->p[2].src, 0, -1, 0);
    if (self->p[3].src) self->p[3].dst = func_001B6290(self->p[3].src, 0, -1, 1);
    self->cur = 5;
    for (;;) {
        s32 c = self->cur;
        if (c < 2) break;
        s32 d = c - 1;
        if (D_002623C0->levels[d].f448 & 0x20) break;
        if (D_002623C0->levels[c].f448 & 1) break;
        self->cur = d;
    }
    for (s32 i = 1; i <= self->cur; i++) {
        StateTrigger* o = self->objs[i - 1];
        if (o && (D_002623C0->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->chosen = 0;
    for (s32 i = 0; i < 4; i++) {
        Cand_16AB38* c = self->cands[i];
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
                self->chosen = c;
                break;
            }
        }
    }
    s32 idx;
    if (self->chosen) {
        idx = 0;
    } else {
        s32 a = D_002623CC;
        if (a != -1 && (D_002623C0->levels[a].f448 & 1)) {
            idx = a;
        } else {
            s32 c = self->cur;
            idx = c;
            if ((D_002623C0->levels[c].f448 & 1) == 0) idx = c - 1;
        }
    }
    func_0016B300(self, idx, 0);
    if (self->p[2].dst || self->p[3].dst) {
        self->sel = 0;
        if (self->p[2].dst) func_001B6628(self->p[2].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
        if (self->p[3].dst) func_001B6628(self->p[3].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
    }
    u8* cap = (u8*)&D_0026FA90;
    func_001E9498(D_00275BC0, cap);
}

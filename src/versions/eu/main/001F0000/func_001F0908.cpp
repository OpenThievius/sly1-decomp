// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: resets the two engines after a pending change and restores the slot's pose.
struct Eng_eu_1F0908 {
    EngVt_1F0908* vt;
    u8 pad4[0x56C];
    s32 i570;
    u8 pad574[0x400];
    s32 i974;
};

void func_001F0908(Obj_1F0908* self)
{
    if (D_00276250[0] == -1) return;
    func_001AA8B8(&D_002721D0, (((*(Cfg_1F0908**)&D_002623C0)->hi << 8) | (*(Cfg_1F0908**)&D_002623C0)->lo) == 4 ? 0.5f : 2.0f);
    D_002721D0.vt->set(&D_002721D0, 2);
    Eng_eu_1F0908* e = ((Eng_eu_1F0908*)&D_0026F138);
    e->i570 = 0;
    e->vt->set((Eng_1F0908*)e, 0);
    func_001AD0D0((Eng_1F0908*)e, (*(Cfg_1F0908**)&D_002623C0)->hi, (*(Cfg_1F0908**)&D_002623C0)->lo);
    e->i974 = 1;
    func_001AA8B8((Eng_1F0908*)e, 0.0f);
    e->vt->set((Eng_1F0908*)e, 2);
    Slot_1F0908* sl = self->slots[D_00276250[0]].s;
    if (sl != 0) {
        f32 f = 0.0f;
        if (D_00276654 == 0) f = sl->f34;
        func_0012C918(sl, self, 0, self->f2F0, f, 0.0f);
    }
    if (self->tbl != 0) {
        for (s32 i = 0; i < self->tbl->count; i++) {
            Ent_1F0908* en = &self->tbl->ents[i];
            if (en->type == 10) {
                Body_1F0908* n = func_0015A418(self->f14, 0x104, en->id, self);
                if (n != 0) n->vt->fn(n);
            }
        }
    }
    D_00276250[0] = -1;
}

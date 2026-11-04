// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: field at 0x560 (US 0x250); fades the 0x105/0x495 group's items out or in when the value goes to or from zero.
struct Obj_135550_eu { u8 pad0[0x560]; s32 f560; };
void func_001AA998(Obj_135550_eu* self, s32 value);

void func_00135550(Obj_135550_eu* self, s32 value)
{
    if (value == self->f560) {
        return;
    }
    if (self->f560 == 0) {
        Group_135550* g = func_0015A418((*(Host_135550**)&D_00275710), 0x105, 0x495, 0);
        if (g != 0) {
            Iter_135550 it;
            Begin_135550::Of(&it, &g->list);
            Item_135550* obj;
            while ((obj = Next_135550::Of(&it)) != 0) {
                func_0012F6B0(obj, 0.0f);
            }
            D_0027B314 = (ListFrame*)it.saved;
        }
    }
    if (value == 0) {
        Group_135550* g = func_0015A418((*(Host_135550**)&D_00275710), 0x105, 0x495, 0);
        if (g != 0) {
            Iter_135550 it;
            Begin_135550::Of(&it, &g->list);
            Item_135550* obj;
            while ((obj = Next_135550::Of(&it)) != 0) {
                func_0012F6B0(obj, 1.0f);
            }
            D_0027B314 = (ListFrame*)it.saved;
        }
    }
    func_001AA998(self, value);
}

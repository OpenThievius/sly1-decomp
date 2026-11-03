// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the instrument pointer is at 0x58C (US 0x27C).
struct Obj_1E6188_eu { u8 pad[0x58C]; Inst_1E6188* p58C; };

void func_001E6188(Obj_1E6188_eu* self)
{
    func_001AA268(self);
    self->p58C = (Inst_1E6188*)func_0011E580(0x51, D_00275710, 0, 0x201, -1);
    func_00184768(self->p58C, 1);
    func_001847F0(self->p58C, D_00275640);
    func_00184858(self->p58C, D_00275650);
    func_00184818(self->p58C, D_00275654);
    func_00184878(self->p58C, D_00275658);
    func_00184838(self->p58C, D_0027565C);
    func_00184898(self->p58C, D_00275660);
    func_00184990(self->p58C, D_00275B58);
    func_00184968(self->p58C, 1);
    self->p58C->vtbl[7](self->p58C);
}

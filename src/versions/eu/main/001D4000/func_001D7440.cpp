// SPDX-License-Identifier: AGPL-3.0-or-later
// Spawns the boss arena effects and sounds for its object (PAL timing and addresses).
struct Blk_eu_1D7440 {
    u8 pad0[0x574];
    void* p574;
    u8 pad578[0x58C - 0x578];
    s32 f58C;
};
struct __attribute__((packed)) BlkP_eu_1D7440 { u8 pad[0x58C]; s32 v; };

void func_001D7440(C19* self)
{
    Ent_1D7440* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    func_00124A48(self);
    func_00124DF8(self, 0x14, D_002752A0);
    self->f694 = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    if (((Snd_1D7440*)self->fB44) != 0) {
        Emit_1D7440* v = func_001B6290(((Snd_1D7440*)self->fB44), self, -1, 0);
        self->fB48 = v;
        func_001B64D8(v, self->fB30 == 1 ? 0x484 : 0x384);
    }
    switch (D_00275710->f1D70) {
    case 3:
        id0 = self->f550 ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->f550 ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->f550 ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        func_001BFCD8(id0, self->fB80, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        func_001BFCD8(id1, self->fB84, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        func_001BFCD8(id2, self->fB7C, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = func_001EAAE0(-0.1f, 0.1f);
            self->fB8C = self->fB90 = self->fB94 = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = func_0015A418(D_00275710, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->fB78 = c;
            self->f598 = c;
        }
    }
    if (self->fB30 == 1) {
        s32 n = func_0015A198(((Grp_1D7440*)self->world), 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->vt->fn6C(buf[i], self);
        }
        ((BlkP_eu_1D7440*)D_00272430)->v = 0;
        ((BlkP_eu_1D7440*)D_002726B0)->v = 0;
        ((Blk_eu_1D7440*)D_00272430)->p574 = &((Blk_eu_1D7440*)D_00272430)->f58C;
        ((Blk_eu_1D7440*)D_002726B0)->p574 = &((Blk_eu_1D7440*)D_002726B0)->f58C;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot_1D7440* s = (Slot_1D7440*)&self->f6B0[k];
        s->q = s->p->q;
    }
    func_001DB290(self);
}

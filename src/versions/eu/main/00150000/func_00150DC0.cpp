// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the name is a 16-bit string (measured by func_eu_001E3018), and the HUD fields sit at 0x57C/0x580.
struct Vt_150DC0_eu { u8 pad[0x20]; void (*f20)(void*, u16*); };
struct Hud_150DC0_eu {
    Vt_150DC0_eu* vt;
    u8 pad0[0x57C - 4];
    f32 f2F0;
    u32 f2F4;
};

u32 func_eu_001E3018(u16* a);
void func_001365A8(Hud_150DC0_eu* a, f32 b);
void func_001365A0(Hud_150DC0_eu* a, s32 b);

void func_00150DC0(Self_150DC0* self, Msg_150DC0* msg)
{
    Slot_150DC0* s2;
    Slot_150DC0* s4;
    s32 a2;
    s32 a0;
    f32 f20;
    u16* nm;
    switch (msg->type) {
    case 0:
        func_001BE728(msg->f4.i);
        self->f2E8 |= 1;
        break;
    case 1:
    case 2:
        if (msg->f4.i != -1) {
            s2 = (Slot_150DC0*)func_0015A418(self->f14, 0x104, msg->f4.i, self->f50 ? self->f50 : self);
        } else {
            s2 = 0;
        }
        if (msg->f8.i != -1) {
            s4 = (Slot_150DC0*)func_0015A418(self->f14, 0x104, msg->f8.i, self->f50 ? self->f50 : self);
        } else {
            s4 = 0;
        }
        if (s2 && s2->f334) {
            func_001B64D8(s2->f334, 0x34C);
        }
        switch (msg->type) {
        case 1:
            func_001E86E0(D_002708E0, s2);
            func_001E87F0(D_002708E0, s4);
            self->f2F0 = s2;
            if (s2) {
                self->f2E8 |= 2;
            }
            break;
        case 2:
            func_001E86E0(D_00271558, s2);
            func_001E87F0(D_00271558, s4);
            self->f2F4 = s2;
            if (s2) {
                self->f2E8 |= 4;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (self->f2F0 && func_001833F0(self->f2F0, msg->f18)) {
            s2 = self->f2F0;
            func_001E7440(D_002708E0, 1);
            func_001E7440(D_00271558, 0);
        } else if (self->f2F4 && func_001833F0(self->f2F4, msg->f18)) {
            s2 = self->f2F4;
            func_001E7440(D_00271558, 1);
            func_001E7440(D_002708E0, 0);
        } else {
            s2 = 0;
        }
        a2 = msg->f1C;
        a0 = 0;
        if (a2 != -1) {
            a0 = func_0015A418(self->f14, 2, a2, self);
            self->f2E8 |= 0x10;
        } else {
            if (s2) {
                a0 = func_0015A418(self->f14, 1, 0x54A, (Self_150DC0*)s2);
            }
        }
        if (a0) {
            func_0012C7B0(0.0f, 1.0f, (Slot_150DC0*)a0, (s32)s2, 1, &self->f2F8);
            func_0012F810(self->f2F8, self);
        }
        nm = (u16*)msg->f14;
        if (nm && *nm) {
            (*(Hud_150DC0_eu*)&D_002701F8).vt->f20(&(*(Hud_150DC0_eu*)&D_002701F8), nm);
            if (s2) {
                *(Raw4_150DC0*)&(*(Hud_150DC0_eu*)&D_002701F8).f2F4 = s2->f2D0;
            } else {
                (*(Hud_150DC0_eu*)&D_002701F8).f2F4 = 0x80808080;
            }
            if (self->f2F8) {
                if (msg->f1C == -1) {
                    f20 = msg->f8.f;
                } else {
                    f20 = self->f2F8->f8->f34;
                }
            } else {
                f20 = msg->f8.f;
            }
            if (0.0f < f20) {
                (*(Hud_150DC0_eu*)&D_002701F8).f2F0 = (f32)(func_eu_001E3018((u16*)msg->f14) + 10) / f20;
            } else {
                Hud_150DC0_eu* h3 = &(*(Hud_150DC0_eu*)&D_002701F8);
                h3->f2F0 = 15.0f;
            }
            self->f2E8 |= 0x20;
        }
        if (msg->f4.f >= 0.0f) {
            func_001365A8(&(*(Hud_150DC0_eu*)&D_002701F8), msg->f4.f + 1.0f);
            self->f2E8 |= 0x40;
        }
        if (msg->f8.f >= 0.0f) {
            self->f2E8 |= 0x80;
            self->f2FC = D_0026185C[0] + msg->f8.f;
        }
        if (msg->f20 != -1) {
            s32 r = func_0015A418(self->f14, 0x104, msg->f20, self->f50 ? self->f50 : self);
            func_001365A0(&(*(Hud_150DC0_eu*)&D_002701F8), r);
        }
        if (msg->f24 != -1) {
            D_00261990->f4BC = (s32)func_0015A448(self->f14, msg->f24, 0);
        } else if (self->f300 != -1) {
            D_00261990->f4BC = (s32)func_0015A448(self->f14, self->f300, 0);
        } else {
            D_00261990->f4BC = 0;
        }
        if (msg->fC) {
            self->f2E8 |= 0x100;
            self->f2EC = msg->f10;
        }
        self->f2E8 |= 8;
        break;
    case 4: {
        void* tmp = &msg->f4;
        func_001837E0(self, 0x10, 1, &tmp);
        break;
    }
    case 5:
        func_001DDB58(self->f14);
        break;
    case 6:
        func_001DDBB8(self->f14);
        break;
    case 7:
        func_0018F0E8(D_00269A00, msg->f4.i);
        break;
    }
}

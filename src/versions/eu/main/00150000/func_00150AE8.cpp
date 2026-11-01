// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the Gl_150AE8 global has f260 at 0x570 and f26C at 0x57C (US 0x260, 0x26C).
struct Gl_150AE8_eu { u8 pad0[0x570]; s32 f570; u8 pad1[8]; s32 f57C; };

void func_00150AE8(Obj_150AE8* self)
{
    s32 q[2];
    s32 s1;
    Ent_150AE8* s2;

    func_00124FC0(self);
    if (!(((Gl_150AE8_eu*)D_0026E9F8)->f570 < 2 && ((Gl_150AE8_eu*)D_0026E9F8)->f57C == 0 && func_001BE5E8() == 0 && D_00275F84 != 1)) {
        s32 st = self->f2D4;
        switch (st) {
        case 1:
        case 5:
        case 6:
            func_00150790(self, 0);
            return;
        }
    }
    func_001F5C0C(q, 0, 8);
    s2 = func_001925F0();
    if (func_001493A0((Bf_150AE8*)&((Mgr_150AE8*)D_00261990)->f454) != 0) {
        q[1] = 0;
        q[0] = 0;
    } else if (s2 != 0) {
        s2->vt->f154(s2, self, q);
    } else {
        q[1] = 1;
    }
    s1 = self->f2D4;
    switch (s1) {
    case 0:
        if (self->f324 != 0) {
            if (D_00275F84 == 0 && q[1] != 0) {
                self->f324 = 0;
                func_001518B8(self);
                s1 = self->f2D4;
            }
        }
        break;
    case 5:
        if (q[0] == 0) {
            s1 = 6;
            break;
        }
        goto timer;
    case 6:
        if (q[0] != 0) {
            s1 = 5;
            break;
        }
        goto timer;
    case 1:
        if (q[1] != 0) {
            Obj_150AE8* o = (Obj_150AE8*)D_0027051C;
            if (o == 0) {
                func_00151860(self, s2);
                s1 = self->f2D4;
            } else if (o != self) {
                if (o->f328 == 0 && o->f2D4 == 3) {
                    func_001516C0(o);
                }
            }
            break;
        }
    timer:
        if (D_0026185C[0] - self->f2D8 >= 5.0f) s1 = 0;
        break;
    case 3:
        if (self->f2D0 != 2) {
            if (!(self->f2E4 < self->f2DC) || D_00275F84 == 1) {
                func_001E9570(D_00275BC0);
                s1 = self->f2D4;
            }
        }
        break;
    case 4:
        if (D_00270B30 == 0) {
            if (D_002717A8 == 0) s1 = 0;
        }
        break;
    }
    func_00150790(self, s1);
    switch (self->f2D4) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    case 3:
        func_001517C0(self);
        break;
    }
}


// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has the object fields 0x310 bytes later (0x570..0x57C) and calls func_eu_001AB238 where US calls vt->m20.
struct Obj_1E00B0_eu { VT_1E00B0* vt; u8 pad04[0x56C]; s32 f570; u8 pad574[4]; f32 f578; s32 f57C; };
void func_eu_001AB238(Obj_1E00B0_eu* q, void* p);
void func_001AA298(Obj_1E00B0_eu* q);
void func_001AA8B8(Obj_1E00B0_eu* q, f32 v);
void func_001E02C8(Obj_1E00B0_eu* q, s32 n);
void func_001AB920(Obj_1E00B0_eu* q, f32 v);

void func_001E00B0(Obj_1E00B0_eu* self)
{
    func_001AA298(self);
    switch (self->f570) {
    case 0:
    case 1:
    {
        if (self->f57C != 0) {
        if (D_00262C70.fAA & 4) {
            func_0016EC20(&D_00262C70, 4);
            func_001BE5F8(D_00275710->f2310);
            if (D_00275710->f2314 != 0) {
                func_001AA8B8(self, 15.0f);
                func_eu_001AB238(self, D_00275710->f2314);
            } else {
                self->vt->m3C(self);
            }
            self->f57C = 0;
        } else if (D_0026185C >= 5.0f) {
            self->vt->m3C(self);
            self->f57C = 0;
        }
        }
    break;
    }
    case 2:
    {
        Obj_1E00B0_eu* o = (Obj_1E00B0_eu*)&D_0026E760;
        s32 r;
        if (o->f570 == 0) {
            func_001E02C8(self, 3);
            return;
        }
        func_001AB920(o, -func_00205C78(2.0f, (f32)D_002623DC));
        r = func_001E9970();
        if (r) o->vt->m38(o); else o->vt->m3C(o);
        if (D_002623C8->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && D_002623C8->f08 < ((Obj_1E00B0_eu*)&D_0026E760)->f578) b = 1;
            if (b) D_0026E9F8.vt->m38(&D_0026E9F8); else D_0026E9F8.vt->m3C(&D_0026E9F8);
        }
    }
    break;
    }
}
